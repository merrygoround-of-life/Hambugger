#include "HbgBase/HbgPlatform.h"


static BOOL _HbgPrintSegReg(std::wstring& text, const DWORD& value)
{
	WORD wValue = (WORD)value;
	return HbgPrintHex2byte(text, wValue);
}

static BOOL _HbgScanSegReg(const std::wstring& text, DWORD& value)
{
	WORD wValue = 0;
	if (HbgScanHex2byte(text, wValue)) {
		value = (DWORD)wValue;
		return TRUE;
	}

	return FALSE;
}


static BOOL _HbgPrintFlagsReg(std::wstring& text, const DWORD& value, DWORD bFlag)
{
	unsigned char bValue = !!(value & bFlag);
	return HbgPrintHex4bit(text, bValue);
}

static BOOL _HbgScanFlagsReg(const std::wstring& text, DWORD& value, DWORD bFlag)
{
	unsigned char bValue = 0;
	if (HbgScanHex4bit(text, bValue)) {
		value |= bFlag;
		return TRUE;
	}

	return FALSE;
}


static BOOL _HbgPrintFpuReg(std::wstring& text, const FLOATING_SAVE_AREA& value, DWORD idxST)
{
	LONGLONG* pCurFpuReg = (LONGLONG*)(&(value.RegisterArea[idxST * 10]));
	
	double tmpVal = 0.0;
	HbgREAL10toDOUBLE(pCurFpuReg, &tmpVal);

	WCHAR tmp[_MAX_PATH] = {0, };
	if (swprintf_s(tmp, HbgFmtValStr_fpu, tmpVal) > 0) {
		text = tmp;
		return TRUE;
	}

	return FALSE;
}

BOOL _HbgScanFpuReg(const std::wstring& /*text*/, FLOATING_SAVE_AREA& /*value*/, DWORD /*idxST*/)
{
	// 미구현
	_ASSERT(FALSE);
	::MessageBox(NULL, L"미구현", L"Hambugger", MB_OK | MB_ICONWARNING);
	return FALSE;
}


static BOOL _HbgPrintMMXReg(std::wstring& text, const FLOATING_SAVE_AREA& value, DWORD idxMMX)
{
	DWORD dw0 = *((DWORD*)(value.RegisterArea + (10 * idxMMX) + 4));
	DWORD dw1 = *((DWORD*)(value.RegisterArea + (10 * idxMMX)));

	WCHAR tmp[_MAX_PATH] = {0, };
	if (swprintf_s(tmp, HbgFmtValStr_mmx, dw0, dw1) > 0) {
		text = tmp;
		return TRUE;
	}

	return FALSE;
}

static BOOL _HbgScanMMXReg(const std::wstring& /*text*/, FLOATING_SAVE_AREA& /*value*/, DWORD /*idxMMX*/)
{
	// 미구현
	_ASSERT(FALSE);
	::MessageBox(NULL, L"미구현", L"Hambugger", MB_OK | MB_ICONWARNING);
	return FALSE;
}


//static BOOL _HbgPrintXMMReg(std::wstring& text, const CONTEXT& value, DWORD idxXMM)
//{
//	DWORD dw0 = *((DWORD*)(value.ExtendedRegisters + (16 * idxXMM) + 172));
//	DWORD dw1 = *((DWORD*)(value.ExtendedRegisters + (16 * idxXMM) + 168));
//	DWORD dw2 = *((DWORD*)(value.ExtendedRegisters + (16 * idxXMM) + 164));
//	DWORD dw3 = *((DWORD*)(value.ExtendedRegisters + (16 * idxXMM) + 160));
//
//	WCHAR tmp[_MAX_PATH] = {0, };
//	if (swprintf_s(tmp, HbgFmtValStr_xmm, dw0, dw1, dw2, dw3) > 0) {
//		text = tmp;
//		return TRUE;
//	}
//
//	return FALSE;
//}
//
//static BOOL _HbgScanXMMReg(const std::wstring& /*text*/, CONTEXT& /*value*/, DWORD /*idxXMM*/)
//{
//	// 미구현
//	_ASSERT(FALSE);
//	::MessageBox(NULL, L"미구현", L"Hambugger", MB_OK | MB_ICONWARNING);
//	return FALSE;
//}


// EAX
class CHbgRegProcEax : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"EAX"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex4byte(text, context.Eax); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.Eax); }
};
static CHbgRegProcEax s_hbgRegProc_EAX;


// EBX
class CHbgRegProcEbx : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"EBX"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex4byte(text, context.Ebx); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.Ebx); }
};
static CHbgRegProcEbx s_hbgRegProc_EBX;

// ECX
class CHbgRegProcEcx : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"ECX"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex4byte(text, context.Ecx); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.Ecx); }
};
static CHbgRegProcEcx s_hbgRegProc_ECX;


// EDX
class CHbgRegProcEdx : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"EDX"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex4byte(text, context.Edx); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.Edx); }
};
static CHbgRegProcEdx s_hbgRegProc_EDX;

// ESP
class CHbgRegProcEsp : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"ESP"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex4byte(text, context.Esp); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.Esp); }
};
static CHbgRegProcEsp s_hbgRegProc_ESP;

// EBP
class CHbgRegProcEbp : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"EBP"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex4byte(text, context.Ebp); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.Ebp); }
};
static CHbgRegProcEbp s_hbgRegProc_EBP;

// ESI
class CHbgRegProcEsi : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"ESI"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex4byte(text, context.Esi); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.Esi); }
};
static CHbgRegProcEsi s_hbgRegProc_ESI;

// EDI
class CHbgRegProcEdi : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"EDI"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex4byte(text, context.Edi); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.Edi); }
};
static CHbgRegProcEdi s_hbgRegProc_EDI;

// EIP
class CHbgRegProcEip : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"EIP"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex4byte(text, context.Eip); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.Eip); }
};
static CHbgRegProcEip s_hbgRegProc_EIP;

// ES
class CHbgRegProcEs : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"ES"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintSegReg(text, context.SegEs); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.SegEs); }
};
static CHbgRegProcEs s_hbgRegProc_ES;

// CS
class CHbgRegProcCs : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"CS"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintSegReg(text, context.SegCs); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.SegCs); }
};
static CHbgRegProcCs s_hbgRegProc_CS;

// SS
class CHbgRegProcSs : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"SS"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintSegReg(text, context.SegSs); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.SegSs); }
};
static CHbgRegProcSs s_hbgRegProc_SS;

// DS
class CHbgRegProcDs : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"DS"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintSegReg(text, context.SegDs); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.SegDs); }
};
static CHbgRegProcDs s_hbgRegProc_DS;

// FS
class CHbgRegProcFs : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"FS"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintSegReg(text, context.SegFs); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.SegFs); }
};
static CHbgRegProcFs s_hbgRegProc_FS;

// GS
class CHbgRegProcGs : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"GS"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintSegReg(text, context.SegGs); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.SegGs); }
};
static CHbgRegProcGs s_hbgRegProc_GS;

// EFlags:C
class CHbgRegProcEflC : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"EFL:C"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintFlagsReg(text, context.EFlags, 0x00000001); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanFlagsReg(text, context.EFlags, 0x00000001); }
};
static CHbgRegProcEflC s_hbgRegProc_EFLC;

// EFlags:P
class CHbgRegProcEflP : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"EFL:P"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintFlagsReg(text, context.EFlags, 0x00000004); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanFlagsReg(text, context.EFlags, 0x00000004); }
};
static CHbgRegProcEflP s_hbgRegProc_EFLP;

// EFlags:A
class CHbgRegProcEflA : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"EFL:A"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintFlagsReg(text, context.EFlags, 0x00000010); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanFlagsReg(text, context.EFlags, 0x00000010); }
};
static CHbgRegProcEflA s_hbgRegProc_EFLA;

// EFlags:Z
class CHbgRegProcEflZ : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"EFL:Z"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintFlagsReg(text, context.EFlags, 0x00000040); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanFlagsReg(text, context.EFlags, 0x00000040); }
};
static CHbgRegProcEflZ s_hbgRegProc_EFLZ;

// EFlags:S
class CHbgRegProcEflS : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"EFL:S"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintFlagsReg(text, context.EFlags, 0x00000080); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanFlagsReg(text, context.EFlags, 0x00000080); }
};
static CHbgRegProcEflS s_hbgRegProc_EFLS;

// EFlags:I
class CHbgRegProcEflI : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"EFL:I"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintFlagsReg(text, context.EFlags, 0x000000200); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanFlagsReg(text, context.EFlags, 0x000000200); }
};
static CHbgRegProcEflI s_hbgRegProc_EFLI;

// EFlags:D
class CHbgRegProcEflD : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"EFL:D"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintFlagsReg(text, context.EFlags, 0x000000400); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanFlagsReg(text, context.EFlags, 0x000000400); }
};
static CHbgRegProcEflD s_hbgRegProc_EFLD;

// EFlags:O
class CHbgRegProcEflO : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"EFL:O"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintFlagsReg(text, context.EFlags, 0x000000800); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanFlagsReg(text, context.EFlags, 0x000000800); }
};
static CHbgRegProcEflO s_hbgRegProc_EFLO;

// EFlags
class CHbgRegProcEfl : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"EFL"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex4byte(text, context.EFlags); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.EFlags); }
};
static CHbgRegProcEfl s_hbgRegProc_EFL;

// ST0
class CHbgRegProcSt0 : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"ST0"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintFpuReg(text, context.FloatSave, 0); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanFpuReg(text, context.FloatSave, 0); }
};
static CHbgRegProcSt0 s_hbgRegProc_St0;

// ST1
class CHbgRegProcSt1 : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"ST1"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintFpuReg(text, context.FloatSave, 1); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanFpuReg(text, context.FloatSave, 1); }
};
static CHbgRegProcSt1 s_hbgRegProc_St1;

// ST2
class CHbgRegProcSt2 : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"ST2"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintFpuReg(text, context.FloatSave, 2); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanFpuReg(text, context.FloatSave, 2); }
};
static CHbgRegProcSt2 s_hbgRegProc_St2;

// ST3
class CHbgRegProcSt3 : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"ST3"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintFpuReg(text, context.FloatSave, 3); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanFpuReg(text, context.FloatSave, 3); }
};
static CHbgRegProcSt3 s_hbgRegProc_St3;

// ST4
class CHbgRegProcSt4 : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"ST4"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintFpuReg(text, context.FloatSave, 4); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanFpuReg(text, context.FloatSave, 4); }
};
static CHbgRegProcSt4 s_hbgRegProc_St4;

// ST5
class CHbgRegProcSt5 : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"ST5"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintFpuReg(text, context.FloatSave, 5); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanFpuReg(text, context.FloatSave, 5); }
};
static CHbgRegProcSt5 s_hbgRegProc_St5;

// ST6
class CHbgRegProcSt6 : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"ST6"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintFpuReg(text, context.FloatSave, 6); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanFpuReg(text, context.FloatSave, 6); }
};
static CHbgRegProcSt6 s_hbgRegProc_St6;

// ST7
class CHbgRegProcSt7 : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"ST7"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintFpuReg(text, context.FloatSave, 7); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanFpuReg(text, context.FloatSave, 7); }
};
static CHbgRegProcSt7 s_hbgRegProc_St7;

// CTRL
class CHbgRegProcCtrl : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"CTRL"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintSegReg(text, context.FloatSave.ControlWord); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanSegReg(text, context.FloatSave.ControlWord); }
};
static CHbgRegProcCtrl s_hbgRegProc_Ctrl;

// STAT
class CHbgRegProcStat : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"STAT"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintSegReg(text, context.FloatSave.StatusWord); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanSegReg(text, context.FloatSave.StatusWord); }
};
static CHbgRegProcStat s_hbgRegProc_Stat;

// TAGS
class CHbgRegProcTags: public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"TAGS"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintSegReg(text, context.FloatSave.TagWord); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanSegReg(text, context.FloatSave.TagWord); }
};
static CHbgRegProcTags s_hbgRegProc_Tags;

// fEIP
class CHbgRegProcFEip : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"fEIP"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex4byte(text, context.FloatSave.ErrorOffset); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.FloatSave.ErrorOffset); }
};
static CHbgRegProcFEip s_hbgRegProc_FEip;

// fEDO
class CHbgRegProcFEdo : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"fEDO"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex4byte(text, context.FloatSave.DataOffset); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.FloatSave.DataOffset); }
};
static CHbgRegProcFEdo s_hbgRegProc_FEdo;

// MM0
class CHbgRegProcMm0: public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"MM0"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintMMXReg(text, context.FloatSave, 0); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanMMXReg(text, context.FloatSave, 0); }
};
static CHbgRegProcMm0 s_hbgRegProc_Mm0;

// MM1
class CHbgRegProcMm1: public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"MM1"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintMMXReg(text, context.FloatSave, 1); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanMMXReg(text, context.FloatSave, 1); }
};
static CHbgRegProcMm1 s_hbgRegProc_Mm1;

// MM2
class CHbgRegProcMm2: public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"MM2"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintMMXReg(text, context.FloatSave, 2); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanMMXReg(text, context.FloatSave, 2); }
};
static CHbgRegProcMm2 s_hbgRegProc_Mm2;

// MM3
class CHbgRegProcMm3: public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"MM3"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintMMXReg(text, context.FloatSave, 3); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanMMXReg(text, context.FloatSave, 3); }
};
static CHbgRegProcMm3 s_hbgRegProc_Mm3;

// MM4
class CHbgRegProcMm4: public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"MM4"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintMMXReg(text, context.FloatSave, 4); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanMMXReg(text, context.FloatSave, 4); }
};
static CHbgRegProcMm4 s_hbgRegProc_Mm4;

// MM5
class CHbgRegProcMm5: public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"MM5"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintMMXReg(text, context.FloatSave, 5); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanMMXReg(text, context.FloatSave, 5); }
};
static CHbgRegProcMm5 s_hbgRegProc_Mm5;

// MM6
class CHbgRegProcMm6: public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"MM6"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintMMXReg(text, context.FloatSave, 6); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanMMXReg(text, context.FloatSave, 6); }
};
static CHbgRegProcMm6 s_hbgRegProc_Mm6;

// MM7
class CHbgRegProcMm7: public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"MM7"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return _HbgPrintMMXReg(text, context.FloatSave, 7); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return _HbgScanMMXReg(text, context.FloatSave, 7); }
};
static CHbgRegProcMm7 s_hbgRegProc_Mm7;
