#ifndef _HbgPlatform_h_
#define _HbgPlatform_h_


extern SIZE_T HbgNullIdx;				// -1


extern LPCWSTR HbgFmtAddrStr_8byte;		// L"0x%016I64X"
extern LPCWSTR HbgFmtAddrStr_4byte;		// L"0x%08I32X"
extern LPCWSTR HbgFmtAddrStr_2byte;		// L"0x%04X"
extern LPCWSTR HbgFmtAddrStr_1byte;		// L"0x%02X"
extern LPCWSTR HbgFmtAddrStr_4bit;		// L"0x%1X"

extern LPCWSTR HbgFmtValStr_8byte;		// L"%016I64X"
extern LPCWSTR HbgFmtValStr_4byte;		// L"%08I32X"
extern LPCWSTR HbgFmtValStr_2byte;		// L"%04X"
extern LPCWSTR HbgFmtValStr_1byte;		// L"%02X"
extern LPCWSTR HbgFmtValStr_4bit;		// L"%1X"

extern LPCWSTR HbgFmtValStr_fpu;		// L"%+1.17Le"
extern LPCWSTR HbgFmtValStr_mmx;		// L"%08I32X %08I32X"
extern LPCWSTR HbgFmtValStr_xmm;		// L"%08I32X %08I32X %08I32X %08I32X"


#if defined(_WIN64)
#	include "HbgPlatform_x64.inl"
#	define HBGDEFFMT_ADDRSTR	HbgFmtAddrStr_8byte
#	define HBGDEFFMT_VALSTR		HbgFmtValStr_8byte
#elif defined(_WIN32)
#	include "HbgPlatform_Win32.inl"
#	define HBGDEFFMT_ADDRSTR	HbgFmtAddrStr_4byte
#	define HBGDEFFMT_VALSTR		HbgFmtValStr_4byte
#endif


enum _HbgReg
{
#if defined(_WIN64)
	_HbgReg_rax = 0,
	_HbgReg_rbx,
	_HbgReg_rcx,
	_HbgReg_rdx,
	_HbgReg_rsp,
	_HbgReg_rbp,
	_HbgReg_rsi,
	_HbgReg_rdi,
	_HbgReg_rip,
	_HbgReg_r8,
	_HbgReg_r9,
	_HbgReg_r10,
	_HbgReg_r11,
	_HbgReg_r12,
	_HbgReg_r13,
	_HbgReg_r14,
	_HbgReg_r15,
	_HbgReg_efl,
#elif defined(_WIN32)
	_HbgReg_eax = 0,
	_HbgReg_ebx,
	_HbgReg_ecx,
	_HbgReg_edx,
	_HbgReg_esp,
	_HbgReg_ebp,
	_HbgReg_esi,
	_HbgReg_edi,
	_HbgReg_eip,
	_HbgReg_es,
	_HbgReg_cs,
	_HbgReg_ss,
	_HbgReg_ds,
	_HbgReg_fs,
	_HbgReg_gs,
	_HbgReg_eflC,
	_HbgReg_eflP,
	_HbgReg_eflA,
	_HbgReg_eflZ,
	_HbgReg_eflS,
	_HbgReg_eflI,
	_HbgReg_eflD,
	_HbgReg_eflO,
	_HbgReg_efl,
	_HbgReg_st0,
	_HbgReg_st1,
	_HbgReg_st2,
	_HbgReg_st3,
	_HbgReg_st4,
	_HbgReg_st5,
	_HbgReg_st6,
	_HbgReg_st7,
	_HbgReg_ctrl,
	_HbgReg_stat,
	_HbgReg_tags,
	_HbgReg_feip,
	_HbgReg_fedo,
	_HbgReg_mm0,
	_HbgReg_mm1,
	_HbgReg_mm2,
	_HbgReg_mm3,
	_HbgReg_mm4,
	_HbgReg_mm5,
	_HbgReg_mm6,
	_HbgReg_mm7,
#endif

	_HbgReg_COUNT,		// total count
};


struct IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const = 0;
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const = 0;
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const = 0;
};


struct _HbgRegItem
{
	_HbgReg idx;
	IHbgRegProc* pObj;
};


_HbgRegItem* HbgGetRegItem(SIZE_T idx);


BOOL HbgPrintHex8byte(std::wstring& text, const DWORD64& value);
BOOL HbgScanHex8byte(const std::wstring& text, DWORD64& value);
BOOL HbgPrintHex4byte(std::wstring& text, const DWORD& value);
BOOL HbgScanHex4byte(const std::wstring& text, DWORD& value);
BOOL HbgPrintHex2byte(std::wstring& text, const WORD& value);
BOOL HbgScanHex2byte(const std::wstring& text, WORD& value);
BOOL HbgPrintHex1byte(std::wstring& text, const unsigned char& value);
BOOL HbgScanHex1byte(const std::wstring& text, unsigned char& value);
BOOL HbgPrintHex4bit(std::wstring& text, const unsigned char& value);
BOOL HbgScanHex4bit(const std::wstring& text, unsigned char& value);


extern "C" void _cdecl HbgREAL10toDOUBLE(/*in*/LONGLONG* pCurFpuReg, /*out*/double* pVal);


#endif // _HbgPlatform_h_
