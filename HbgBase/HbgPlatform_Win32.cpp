#include "stdafx.h"
#include "HbgPlatform.h"
#include "HbgRegProc_Win32.inl"


static _HbgRegItem s_regTables[_HbgReg_COUNT] = {
	{ _HbgReg_eax,	&s_hbgRegProc_EAX },
	{ _HbgReg_ebx,	&s_hbgRegProc_EBX },
	{ _HbgReg_ecx,	&s_hbgRegProc_ECX },
	{ _HbgReg_edx,	&s_hbgRegProc_EDX },
	{ _HbgReg_esp,	&s_hbgRegProc_ESP },
	{ _HbgReg_ebp,	&s_hbgRegProc_EBP },
	{ _HbgReg_esi,	&s_hbgRegProc_ESI },
	{ _HbgReg_edi,	&s_hbgRegProc_EDI },
	{ _HbgReg_eip,	&s_hbgRegProc_EIP },
	{ _HbgReg_es,	&s_hbgRegProc_ES },
	{ _HbgReg_cs,	&s_hbgRegProc_CS },
	{ _HbgReg_ss,	&s_hbgRegProc_SS },
	{ _HbgReg_ds,	&s_hbgRegProc_DS },
	{ _HbgReg_fs,	&s_hbgRegProc_FS },
	{ _HbgReg_gs,	&s_hbgRegProc_GS },
	{ _HbgReg_eflC,	&s_hbgRegProc_EFLC },
	{ _HbgReg_eflP,	&s_hbgRegProc_EFLP },
	{ _HbgReg_eflA,	&s_hbgRegProc_EFLA },
	{ _HbgReg_eflZ,	&s_hbgRegProc_EFLZ },
	{ _HbgReg_eflS,	&s_hbgRegProc_EFLS },
	{ _HbgReg_eflI,	&s_hbgRegProc_EFLI },
	{ _HbgReg_eflD,	&s_hbgRegProc_EFLD },
	{ _HbgReg_eflO,	&s_hbgRegProc_EFLO },
	{ _HbgReg_efl,	&s_hbgRegProc_EFL },
	{ _HbgReg_st0,	&s_hbgRegProc_St0 },
	{ _HbgReg_st1,	&s_hbgRegProc_St1 },
	{ _HbgReg_st2,	&s_hbgRegProc_St2 },
	{ _HbgReg_st3,	&s_hbgRegProc_St3 },
	{ _HbgReg_st4,	&s_hbgRegProc_St4 },
	{ _HbgReg_st5,	&s_hbgRegProc_St5 },
	{ _HbgReg_st6,	&s_hbgRegProc_St6 },
	{ _HbgReg_st7,	&s_hbgRegProc_St7 },
	{ _HbgReg_ctrl,	&s_hbgRegProc_Ctrl },
	{ _HbgReg_stat,	&s_hbgRegProc_Stat },
	{ _HbgReg_tags,	&s_hbgRegProc_Tags },
	{ _HbgReg_feip,	&s_hbgRegProc_FEip },
	{ _HbgReg_fedo,	&s_hbgRegProc_FEdo },
	{ _HbgReg_mm0,	&s_hbgRegProc_Mm0 },
	{ _HbgReg_mm1,	&s_hbgRegProc_Mm1 },
	{ _HbgReg_mm2,	&s_hbgRegProc_Mm2 },
	{ _HbgReg_mm3,	&s_hbgRegProc_Mm3 },
	{ _HbgReg_mm4,	&s_hbgRegProc_Mm4 },
	{ _HbgReg_mm5,	&s_hbgRegProc_Mm5 },
	{ _HbgReg_mm6,	&s_hbgRegProc_Mm6 },
	{ _HbgReg_mm7,	&s_hbgRegProc_Mm7 },
};

_HbgRegItem* HbgGetRegItem(SIZE_T idx)
{
	if (idx < _HbgReg_COUNT)
		return &(s_regTables[idx]);

	return NULL;
}
