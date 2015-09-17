#include "stdafx.h"
#include "HbgPlatform.h"
#include "HbgRegProc_x64.inl"


static _HbgRegItem s_regTables[_HbgReg_COUNT] = {
	{ _HbgReg_rax,	&s_hbgRegProc_RAX },
	{ _HbgReg_rbx,	&s_hbgRegProc_RBX },
	{ _HbgReg_rcx,	&s_hbgRegProc_RCX },
	{ _HbgReg_rdx,	&s_hbgRegProc_RDX },
	{ _HbgReg_rsp,	&s_hbgRegProc_RSP },
	{ _HbgReg_rbp,	&s_hbgRegProc_RBP },
	{ _HbgReg_rsi,	&s_hbgRegProc_RSI },
	{ _HbgReg_rdi,	&s_hbgRegProc_RDI },
	{ _HbgReg_rip,	&s_hbgRegProc_RIP },
	{ _HbgReg_r8,	&s_hbgRegProc_R8 },
	{ _HbgReg_r9,	&s_hbgRegProc_R9 },
	{ _HbgReg_r10,	&s_hbgRegProc_R10 },
	{ _HbgReg_r11,	&s_hbgRegProc_R11 },
	{ _HbgReg_r12,	&s_hbgRegProc_R12 },
	{ _HbgReg_r13,	&s_hbgRegProc_R13 },
	{ _HbgReg_r14,	&s_hbgRegProc_R14 },
	{ _HbgReg_r15,	&s_hbgRegProc_R15 },
	{ _HbgReg_efl,	&s_hbgRegProc_EFL },
};

_HbgRegItem* HbgGetRegItem(SIZE_T idx)
{
	if (idx < _HbgReg_COUNT)
		return &(s_regTables[idx]);

	return NULL;
}
