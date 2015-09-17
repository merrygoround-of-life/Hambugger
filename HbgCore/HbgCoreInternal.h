#pragma once


class CHbgDebugLoop;
struct IHbgCallback;


class CHbgCoreInternal
{
public:
	CHbgCoreInternal(void);
	~CHbgCoreInternal(void);
	
public:
	BOOL Initialize(LPCWSTR pathDebuggee, IUnknown* pIUnkClbk);
	BOOL InitializeEx(DWORD pidDebuggee, IUnknown* pIUnkClbk);
	BOOL Detach();
	BOOL Go(DWORD_PTR toAddr);
	BOOL Step(DWORD idThread);
	BOOL Break();

	BOOL ToggleBreakpoint(DWORD_PTR addr, BOOL* bSet);
	BOOL ReadMemory(DWORD_PTR addr, SIZE_T size, BYTE* pByte);
	BOOL WriteMemory(DWORD_PTR addr, SIZE_T size, BYTE* pByte);
	BOOL ReadContext(DWORD idThread, SIZE_T size, BYTE* pByte);
	BOOL WriteContext(DWORD idThread, SIZE_T size, BYTE* pByte);
	
private:
	void _Init();
	void _FixBP(DWORD_PTR addr, SIZE_T size, BYTE* pByte, BOOL bRead);

private:
	CHbgDebugLoop* m_pDebugLoop;
	IHbgCallback* m_pICallback;
};
