#include "HbgBase/HbgPlatform.h"


// RAX
class CHbgRegProcRax : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"RAX"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex8byte(text, context.Rax); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex8byte(text, context.Rax); }
};
static CHbgRegProcRax s_hbgRegProc_RAX;


// RBX
class CHbgRegProcRbx : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"RBX"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex8byte(text, context.Rbx); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex8byte(text, context.Rbx); }
};
static CHbgRegProcRbx s_hbgRegProc_RBX;

// RCX
class CHbgRegProcRcx : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"RCX"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex8byte(text, context.Rcx); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex8byte(text, context.Rcx); }
};
static CHbgRegProcRcx s_hbgRegProc_RCX;


// RDX
class CHbgRegProcRdx : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"RDX"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex8byte(text, context.Rdx); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex8byte(text, context.Rdx); }
};
static CHbgRegProcRdx s_hbgRegProc_RDX;

// RSP
class CHbgRegProcRsp : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"RSP"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex8byte(text, context.Rsp); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex8byte(text, context.Rsp); }
};
static CHbgRegProcRsp s_hbgRegProc_RSP;

// RBP
class CHbgRegProcRbp : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"RBP"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex8byte(text, context.Rbp); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex8byte(text, context.Rbp); }
};
static CHbgRegProcRbp s_hbgRegProc_RBP;

// RSI
class CHbgRegProcRsi : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"RSI"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex8byte(text, context.Rsi); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex8byte(text, context.Rsi); }
};
static CHbgRegProcRsi s_hbgRegProc_RSI;

// RDI
class CHbgRegProcRdi : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"RDI"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex8byte(text, context.Rdi); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex8byte(text, context.Rdi); }
};
static CHbgRegProcRdi s_hbgRegProc_RDI;

// RIP
class CHbgRegProcRip : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"RIP"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex8byte(text, context.Rip); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex8byte(text, context.Rip); }
};
static CHbgRegProcRip s_hbgRegProc_RIP;

// R8
class CHbgRegProcR8 : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"R8"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex8byte(text, context.R8); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex8byte(text, context.R8); }
};
static CHbgRegProcR8 s_hbgRegProc_R8;

// R9
class CHbgRegProcR9 : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"R9"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex8byte(text, context.R9); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex8byte(text, context.R9); }
};
static CHbgRegProcR9 s_hbgRegProc_R9;

// R10
class CHbgRegProcR10 : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"R10"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex8byte(text, context.R10); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex8byte(text, context.R10); }
};
static CHbgRegProcR10 s_hbgRegProc_R10;

// R11
class CHbgRegProcR11 : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"R11"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex8byte(text, context.R11); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex8byte(text, context.R11); }
};
static CHbgRegProcR11 s_hbgRegProc_R11;

// R12
class CHbgRegProcR12 : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"R12"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex8byte(text, context.R12); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex8byte(text, context.R12); }
};
static CHbgRegProcR12 s_hbgRegProc_R12;

// R13
class CHbgRegProcR13 : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"R13"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex8byte(text, context.R13); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex8byte(text, context.R13); }
};
static CHbgRegProcR13 s_hbgRegProc_R13;

// R14
class CHbgRegProcR14 : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"R14"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex8byte(text, context.R14); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex8byte(text, context.R14); }
};
static CHbgRegProcR14 s_hbgRegProc_R14;

// R15
class CHbgRegProcR15 : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"R15"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex8byte(text, context.R15); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex8byte(text, context.R15); }
};
static CHbgRegProcR15 s_hbgRegProc_R15;

// EFlags
class CHbgRegProcEfl : public IHbgRegProc
{
public:
	virtual LPCWSTR GetName() const											{ return L"EFL"; }
	virtual BOOL Read(std::wstring& text, const CONTEXT& context) const		{ return HbgPrintHex4byte(text, context.EFlags); }
	virtual BOOL Write(const std::wstring& text, CONTEXT& context) const	{ return HbgScanHex4byte(text, context.EFlags); }
};
static CHbgRegProcEfl s_hbgRegProc_EFL;
