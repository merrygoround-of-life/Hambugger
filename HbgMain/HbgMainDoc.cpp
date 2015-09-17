
// HbgMainDoc.cpp : CHbgMainDoc Ŭ������ ����
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


// CHbgMainDoc ����/�Ҹ�

CHbgMainDoc::CHbgMainDoc()
:	m_pMainView(NULL), m_pDoc(NULL)
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
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

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CHbgMainDoc serialization

void CHbgMainDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CHbgMainDoc ����

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
			tmpTitle.Format(L"���μ��� %d", processId);
		else
			tmpTitle = L"���� ����";
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
