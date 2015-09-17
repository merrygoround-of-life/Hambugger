
// HbgMainDoc.cpp : CHbgMainDoc 클래스의 구현
//

#include "stdafx.h"
#include "HbgMain.h"

#include "HbgEngine/HbgEngine.h"
#include "HbgDoc/HbgDocument.h"
#include "HbgMainDoc.h"
#include "HbgMainView.h"


// CHbgMainDoc

IMPLEMENT_DYNCREATE(CHbgMainDoc, CDocument)

BEGIN_MESSAGE_MAP(CHbgMainDoc, CDocument)
END_MESSAGE_MAP()


// CHbgMainDoc 생성/소멸

CHbgMainDoc::CHbgMainDoc()
:	m_pMainView(NULL), m_pDoc(NULL)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	NewDocument();
}

CHbgMainDoc::~CHbgMainDoc()
{
	if (m_pDoc) {
		delete m_pDoc;
		m_pDoc = NULL;
	}
}

BOOL CHbgMainDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CHbgMainDoc serialization

void CHbgMainDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// CHbgMainDoc 진단

#ifdef _DEBUG
void CHbgMainDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHbgMainDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

void CHbgMainDoc::NewDocument(LPCWSTR strFilePath/*= NULL*/, DWORD processId/*= 0*/)
{
	if (m_pDoc)
		delete m_pDoc;

	m_pDoc = new CHbgDocument;

	CString tmpTitle;
	if (strFilePath) {
		m_filePath = strFilePath;
		tmpTitle = strFilePath;
	} else {
		m_filePath.Empty();

		if (processId)
			tmpTitle.Format(L"프로세스 %d", processId);
		else
			tmpTitle = L"제목 없음";
	}

	m_processId = processId;
	
	SetTitle(tmpTitle);
	
#ifdef _DEBUG
	CString tmpDebug(L"[HbgMain] Document: ");
	tmpDebug.Append(tmpTitle);
	tmpDebug.Append(L"\n");
	OutputDebugString(tmpDebug);
#endif //_DEBUG
	
}

LPCWSTR CHbgMainDoc::GetFilePath() const
{
	if (!m_filePath.IsEmpty())
		return m_filePath;

	return NULL;
}

DWORD CHbgMainDoc::GetProcessID() const
{
	return m_processId;
}

void CHbgMainDoc::AddPage(HbgUpdate_Module* pUpdatePage)
{
	m_pDoc->AddPage(pUpdatePage->addressStart, pUpdatePage->addressCodeStart, pUpdatePage->addressCodeEnd);
}

void CHbgMainDoc::RemovePage(DWORD_PTR addrStart)
{
	m_pDoc->RemovePage(addrStart);
}

CHbgPage* CHbgMainDoc::FindPage(DWORD_PTR addr) const
{
	return m_pDoc->FindPage(addr);
}

BOOL CHbgMainDoc::SetCurEIP(DWORD_PTR eip, CHbgPage*& pCurPage, SIZE_T& curIdx)
{
	return m_pDoc->SetCurEIP(eip, pCurPage, curIdx);
}

CHbgDocument* CHbgMainDoc::GetImpl()
{
	return m_pDoc;
}

void CHbgMainDoc::SetMainView(CHbgMainView* pView)
{
	m_pMainView = pView;
}
