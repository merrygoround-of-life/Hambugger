#include "stdafx.h"
#include "HbgMain.h"
#include "HbgEngine/HbgEngine.h"
#include "HbgBreakpointWnd.h"
#include "HbgDasm/include/HbgDasmInc.h"
#include "HbgBase/HbgMemPtr.h"
#include "HbgDocument.h"


static const SIZE_T s_dwHbg_LoadFrameWindowSize = 100;


///////////////////////////
// CHbgInstruction Implementation
CHbgInstruction::CHbgInstruction(DWORD_PTR address)
:	m_address(address), m_pData(NULL)
{
}

CHbgInstruction::CHbgInstruction(const CHbgInstruction& item)
:	m_address(0), m_pData(NULL)
{
	m_address = item.m_address;

	if (item.m_pData)
		m_pData = new CHbgInstructionData(*item.m_pData);
}

CHbgInstruction::~CHbgInstruction()
{
	if (m_pData) {
		delete m_pData;
		m_pData = NULL;
	}
}

const CHbgInstruction& CHbgInstruction::operator=(const CHbgInstruction& item)
{
	m_address = item.m_address;

	if (item.m_pData) {
		if (m_pData)
			*m_pData = *item.m_pData;
		else
			m_pData = new CHbgInstructionData(*item.m_pData);
	} else {
		if (m_pData) {
			delete m_pData;
			m_pData = NULL;
		}
	}

	return *this;
}

CHbgInstructionData* CHbgInstruction::CreateData()
{
	_ASSERT(!m_pData);
	if (!m_pData)
		m_pData = new CHbgInstructionData;

	return m_pData;
}


///////////////////////////
// CHbgPage Declaration
CHbgPage::CHbgPage(DWORD_PTR baseAddr, DWORD_PTR firstAddr, DWORD_PTR lastAddr)
:	m_baseAddr(baseAddr), m_firstAddr(firstAddr), m_lastAddr(lastAddr)
{
}

CHbgPage::~CHbgPage()
{
	Clear();
}

BOOL CHbgPage::Include(DWORD_PTR addr) const
{
	if ((m_firstAddr <= addr) && (m_lastAddr >= addr))
		return TRUE;

	return FALSE;
}

SIZE_T CHbgPage::FindOpItemIndex(DWORD_PTR address) const
{
	// m_items 은 항상 address순으로 정렬되어 있으므로 binary_search가 가능
	std::vector<CHbgInstruction>::const_iterator iter = std::lower_bound(m_items.begin(), m_items.end(), CHbgInstruction(address), CHbgInstruction::_fo());
	if (iter != m_items.end() && (address == (*iter).GetAddress()))
		return iter - m_items.begin();

	_ASSERT(FALSE);
	return HbgNullIdx;
}

const CHbgInstruction* CHbgPage::GetOpItem(SIZE_T nIdx) const
{
	if (nIdx < m_items.size())
		return &m_items.at(nIdx);

	_ASSERT(FALSE);
	return NULL;
}

void CHbgPage::LoadInit()
{
	if (m_items.empty())
		_ReadOpItems(m_firstAddr, m_lastAddr);
}

void CHbgPage::LoadRegion(DWORD nIdx)
{
	if (!m_items.empty()) {
		SIZE_T lastIdx = m_items.size() - 1;

		// 주어진 idx 및 idx의 상하 s_dwHbg_LoadFrameWindowSize 개씩 확인한다.
		SIZE_T nCheckFirst = (nIdx > s_dwHbg_LoadFrameWindowSize) ? (nIdx - s_dwHbg_LoadFrameWindowSize) : 0;
		SIZE_T nCheckLast = ((lastIdx - nIdx) > s_dwHbg_LoadFrameWindowSize) ? (nIdx + s_dwHbg_LoadFrameWindowSize) : lastIdx;

		BOOL bNeedRead = FALSE;
		SIZE_T nCheckIdx = nCheckFirst;
		while (nCheckIdx <= nCheckLast) {
			if (!m_items[nCheckIdx].GetData()) {
				bNeedRead = TRUE;
				break;
			}

			++nCheckIdx;
		}

		if (bNeedRead) {
			// Check가 안되었다면, 주어진 idx의 상하 s_dwHbg_LoadFrameWindowSize*2 개씩 캐시한다.
			CWaitCursor wait;

			SIZE_T nReadFirst = (nIdx > (s_dwHbg_LoadFrameWindowSize * 2)) ? (nIdx - (s_dwHbg_LoadFrameWindowSize * 2)) : 0;
			SIZE_T nReadLast = ((lastIdx - nIdx) > (s_dwHbg_LoadFrameWindowSize * 2)) ? (nIdx + (s_dwHbg_LoadFrameWindowSize * 2)) : lastIdx;
			SIZE_T nNeedFirst = nReadFirst;
			SIZE_T nNeedLast = nReadLast;

			BOOL bUpset = FALSE;
			nCheckIdx = nReadFirst;
			while (nCheckIdx <= nReadLast) {
				if (!bUpset) {
					if (!m_items[nCheckIdx].GetData()) {
						nNeedFirst = nCheckIdx;
						bUpset = TRUE;
					}
				} else {
					if (!m_items[nCheckIdx].GetData()) {
						nNeedLast = nCheckIdx;
					} else {
						break;
					}
				}

				++nCheckIdx;
			}

			DWORD_PTR firstAddr = m_items.at(nNeedFirst).GetAddress();
			DWORD_PTR lastAddr = (nNeedLast < (int)(GetItemCount() - 1)) ? (m_items.at(nNeedLast + 1).GetAddress() - 1) : m_lastAddr;

#ifdef _DEBUG
			WCHAR tmp[_MAX_PATH];
			swprintf_s(tmp, L"[HbgMain] Read %d OpItems(0x%08I32X - 0x%08I32X)\n", nNeedLast - nNeedFirst + 1, firstAddr, lastAddr);
			OutputDebugString(tmp);
#endif // _DEBUG

			_ReadOpItems(firstAddr, lastAddr, nNeedFirst, nNeedLast);
		}
	}
}

void CHbgPage::Clear()
{
	m_items.clear();
}

SIZE_T CHbgPage::GetItemCount() const
{
	return m_items.size();
}

DWORD_PTR CHbgPage::GetBaseAddr() const
{
	return m_baseAddr;
}

void CHbgPage::_ReadOpItems(DWORD_PTR firstAddr, DWORD_PTR lastAddr, SIZE_T nIdxFirst/*= -1*/, SIZE_T nIdxLast/*= -1*/)
{
	CWaitCursor wait;

	SIZE_T bufSize = lastAddr - firstAddr + 1;
	CHbgMemPtr bufData(bufSize);

	SIZE_T nSetIdx = nIdxFirst;

	// 데이터를 읽어온다.
	if (static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->ReadMemory(firstAddr, bufSize, bufData)) {

		LPBYTE curPtr = bufData;
		LPBYTE endPtr = curPtr + lastAddr - firstAddr;

		DWORD_PTR address = 0;

		HbgDasmInfo dasmInfo;
		while (nSetIdx <= nIdxLast) {
			// 1) address
			address = firstAddr + (DWORD_PTR)curPtr - (DWORD_PTR)(LPBYTE)bufData;

			HbgDasmInit(dasmInfo, HBGDASM_OPT_RETLENGTH, curPtr, bufSize, address);

			if (nIdxFirst != -1)
				dasmInfo.option |= HBGDASM_OPT_GETDASM | HBGDASM_OPT_GETOPCODE | HBGDASM_OPT_GETCHARS;

			curPtr += HbgDasmParse(dasmInfo);

			if (nIdxFirst != -1) {
				// 2) Disasm/Opcode/Chars
				CHbgInstructionData* pData = m_items[nSetIdx].CreateData();

				pData->SetDIsasm(dasmInfo.dasm);
				pData->SetOpcode(dasmInfo.opcode);
				pData->SetCharacters(dasmInfo.chars);

				++nSetIdx;
			} else {
				if (curPtr > endPtr)
					break;

				// 2) 혹은 item adding
				m_items.push_back(CHbgInstruction(address));
			}
		}
	}
}


///////////////////////////
// CHbgDocument Declaration
CHbgDocument::CHbgDocument()
{
}

CHbgDocument::~CHbgDocument()
{
	if (!m_pages.empty()) {
		std::vector<CHbgPage*>::iterator iter = m_pages.begin();
		while (iter != m_pages.end()) {
			delete *iter;
			++iter;
		}

		m_pages.clear();
	}
}

void CHbgDocument::AddPage(DWORD_PTR baseAddr, DWORD_PTR firstAddr, DWORD_PTR lastAddr)
{
	m_pages.push_back(new CHbgPage(baseAddr, firstAddr, lastAddr));
}

void CHbgDocument::RemovePage(DWORD_PTR /*baseAddr*/)
{
	// 참조가 걸려있을 수 있으므로 우선 지우지 않도록.. 차후 다른 처리 구현
	//std::vector<CHbgPage*>::iterator iter = m_pages.begin();
	//while (iter != m_pages.end()) {
	//	if ((*iter)->GetBaseAddr() == baseAddr) {
	//		break;
	//	}

	//	++iter;
	//}
}

CHbgPage* CHbgDocument::FindPage(DWORD_PTR addr) const
{
	std::vector<CHbgPage*>::const_iterator iter = m_pages.begin();
	while (iter != m_pages.end()) {
		if ((*iter)->Include(addr))
			return *iter;

		++iter;
	}

	return  NULL;
}

void CHbgDocument::AddBP(DWORD_PTR addr)
{
	_ASSERT(!FindBP(addr));
	m_breakpoints.push_back(addr);
}

void CHbgDocument::RemoveBP(DWORD_PTR addr)
{
	_ASSERT(FindBP(addr));
	std::vector<DWORD_PTR>::iterator iter = std::find(m_breakpoints.begin(), m_breakpoints.end(), addr);
	if (iter != m_breakpoints.end())
		m_breakpoints.erase(iter);
}

BOOL CHbgDocument::FindBP(DWORD_PTR addr) const
{
	std::vector<DWORD_PTR>::const_iterator iter = std::find(m_breakpoints.begin(), m_breakpoints.end(), addr);
	if (iter != m_breakpoints.end())
		return TRUE;

	return FALSE;
}

const std::vector<DWORD_PTR> &CHbgDocument::_GetListBPs() const
{
	return m_breakpoints;
}

BOOL CHbgDocument::SetCurEIP(DWORD_PTR curEIP, CHbgPage*& pCurPage, SIZE_T& curIdx)
{
	BOOL bOk = FALSE;

	std::vector<CHbgPage*>::iterator iter = m_pages.begin();
	while (iter != m_pages.end()) {
		if ((*iter)->Include(curEIP)) {
			(*iter)->LoadInit();

			pCurPage = *iter;
			curIdx = (*iter)->FindOpItemIndex(curEIP);

			bOk = TRUE;
			break;
		}

		++iter;
	}

	return bOk;
}
