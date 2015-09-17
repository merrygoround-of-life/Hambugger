
// HbgMainDoc.h : CHbgMainDoc Ŭ������ �������̽�
//


#pragma once

class CHbgDocument;
class CHbgMainView;
class CHbgPage;
struct HbgUpdate_Module;

class CHbgMainDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CHbgMainDoc();
	DECLARE_DYNCREATE(CHbgMainDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CHbgMainDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

public:
	void NewDocument(LPCWSTR strFilePath = NULL, DWORD processId = 0);
	LPCWSTR GetFilePath() const;
	DWORD GetProcessID() const;

	void AddPage(HbgUpdate_Module* pUpdatePage);
	void RemovePage(DWORD_PTR addrStart);
	CHbgPage* FindPage(DWORD_PTR addr) const;
	BOOL SetCurEIP(DWORD_PTR eip, CHbgPage*& pCurPage, SIZE_T& curIdx);
	
	CHbgDocument* GetImpl();
	void SetMainView(CHbgMainView* pView);

private:
	CHbgDocument* m_pDoc;
	CString m_filePath;
	DWORD m_processId;

	CHbgMainView* m_pMainView;
};


