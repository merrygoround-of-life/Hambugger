
// HbgMainDoc.h : CHbgMainDoc 클래스의 인터페이스
//


#pragma once

class CHbgDocument;
class CHbgMainView;
class CHbgPage;
struct HbgUpdate_Module;

class CHbgMainDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CHbgMainDoc();
	DECLARE_DYNCREATE(CHbgMainDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 구현입니다.
public:
	virtual ~CHbgMainDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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


