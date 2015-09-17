#ifndef _HbgCore_H_
#define _HbgCore_H_


class CHbgCoreInternal;


class HBGCORE_DLL CHbgCore
{
public:
	CHbgCore(void);
	~CHbgCore(void);

public:
	HRESULT Initialize(LPCWSTR pathDebuggee, IUnknown* pIUnkClbk);
	HRESULT InitializeEx(DWORD pidDebuggee, IUnknown* pIUnkClbk);
	HRESULT Uninitialize(BOOL bKillDebuggee);

	HRESULT Go(DWORD_PTR toAddr);
	HRESULT Step(DWORD idThread);
	HRESULT Break();

	HRESULT ToggleBreakpoint(DWORD_PTR addr, BOOL* bSet);

	HRESULT ReadMemory(DWORD_PTR addr, SIZE_T size, BYTE* pByte);
	HRESULT WriteMemory(DWORD_PTR addr, SIZE_T size, BYTE* pByte);

	HRESULT ReadContext(DWORD idThread, SIZE_T size, BYTE* pByte);
	HRESULT WriteContext(DWORD idThread, SIZE_T size, BYTE* pByte);

private:
	// Core Engine
	CHbgCoreInternal* m_coreInternal;
};


#endif // _HbgCore_H_
