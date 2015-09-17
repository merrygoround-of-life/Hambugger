#ifndef _HbgDoc_h_
#define _HbgDoc_h_


///////////////////////////
// CHbgInstructionData Declaration
class CHbgInstructionData
{
public:
	CHbgInstructionData()	:	m_strOpcode(L""), m_strDisasm(L""), m_chars(0x00)		{}
	~CHbgInstructionData()																{}

public:
	LPCWSTR GetOpcode() const				{ return m_strOpcode.c_str(); }
	LPCWSTR GetDisasm() const				{ return m_strDisasm.c_str(); }
	BYTE GetCharacters() const				{ return m_chars; }

	void SetOpcode(LPCWSTR pBuf)			{ if (pBuf && *pBuf) m_strOpcode = pBuf; }
	void SetDIsasm(LPCWSTR pBuf)			{ if (pBuf && *pBuf) m_strDisasm = pBuf; }
	void SetCharacters(BYTE chars)			{ m_chars = chars; }

private:
	std::wstring m_strOpcode;
	std::wstring m_strDisasm;
	BYTE m_chars;
};


///////////////////////////
// CHbgInstruction Declaration
class CHbgInstruction
{
public:
	CHbgInstruction(DWORD_PTR address);
	CHbgInstruction(const CHbgInstruction& item);
	~CHbgInstruction();

public:
	const CHbgInstruction& operator=(const CHbgInstruction& item);

public:
	struct _fo
	{
		bool operator() (const CHbgInstruction& val1, const CHbgInstruction& val2) const	{ return (val1.m_address < val2.m_address) ? true : false; }
	};

public:
	DWORD_PTR GetAddress() const			{ return m_address; }
	CHbgInstructionData* GetData() const	{ return m_pData; }
	CHbgInstructionData* CreateData();

private:
	DWORD_PTR m_address;
	CHbgInstructionData* m_pData;
};


///////////////////////////
// CHbgPage Declaration
class CHbgPage
{
public:
	CHbgPage(DWORD_PTR baseAddr, DWORD_PTR firstAddr, DWORD_PTR lastAddr);
	~CHbgPage();

public:
	BOOL Include(DWORD_PTR addr) const;
	SIZE_T FindOpItemIndex(DWORD_PTR address) const;
	const CHbgInstruction* GetOpItem(SIZE_T nIdx) const;

	void LoadInit();
	void LoadRegion(DWORD nIdx);
	void Clear();

	SIZE_T GetItemCount() const;
	DWORD_PTR GetBaseAddr() const;

private:
	void _ReadOpItems(DWORD_PTR firstAddr, DWORD_PTR lastAddr, SIZE_T nIdxFirst = (SIZE_T)-1, SIZE_T nIdxLast = (SIZE_T)-1);

private:
	DWORD_PTR m_baseAddr;
	DWORD_PTR m_firstAddr;
	DWORD_PTR m_lastAddr;
	std::vector<CHbgInstruction> m_items;
};


///////////////////////////
// CHbgDocument Declaration
class CHbgDocument
{
public:
	CHbgDocument();
	~CHbgDocument();

public:
	void AddPage(DWORD_PTR baseAddr, DWORD_PTR firstAddr, DWORD_PTR lastAddr);	
	void RemovePage(DWORD_PTR baseAddr);
	CHbgPage* FindPage(DWORD_PTR addr) const;

	void AddBP(DWORD_PTR addr);
	void RemoveBP(DWORD_PTR addr);
	BOOL FindBP(DWORD_PTR addr) const;

	const std::vector<DWORD_PTR> & _GetListBPs() const;
	
	BOOL SetCurEIP(DWORD_PTR curEIP, CHbgPage*& pCurPage, SIZE_T& curIdx);
	
private:
	std::vector<CHbgPage*> m_pages;
	std::vector<DWORD_PTR> m_breakpoints;
};


#endif // _HbgDoc_h_
