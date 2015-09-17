#pragma once


struct IHbgDebug;
class CHbgEngineCallback;

class CHbgEngine
{
public:
	CHbgEngine(void);
	~CHbgEngine(void);

public:
	BOOL Running() const;
	void Finalize();

public:
	BOOL Initialize(LPCWSTR pathDebuggee, DWORD pidDebuggee);		// pathDebuggee, pidDebuggee 둘 중 하나만 존재해야 한다.
	BOOL Uninitialize(BOOL bKillDebuggee, BOOL bUserAct = TRUE);
	BOOL Go(DWORD_PTR toAddr);
	BOOL Step(DWORD idThread);
	BOOL Break();

	BOOL ToggleBreakpoint(DWORD_PTR addr, BOOL* bSet);
	BOOL ReadMemory(DWORD_PTR addr, SIZE_T size, BYTE* pByte);
	BOOL WriteMemory(DWORD_PTR addr, SIZE_T size, BYTE* pByte);
	BOOL ReadContext(DWORD idThread, SIZE_T size, BYTE* pByte);
	BOOL WriteContext(DWORD idThread, SIZE_T size, BYTE* pByte);

private:
	IHbgDebug* m_pIHbgDebug;
	IUnknown* m_pIUnkCallback;
	BOOL m_bRun;
};
