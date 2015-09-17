#include "stdafx.h"
#include "HbgDasmDefs.h"


//////////////////////
// CHbgDasmInnerInfo Implementation
CHbgDasmInnerInfo::CHbgDasmInnerInfo(HbgDasmInfo& dasmInfo)
{
	ptrBytes = dasmInfo.bytes;
	ptrStart = ptrBytes;
	ptrEnd = ptrBytes + (dasmInfo.len - 1);
	ptrModRM = NULL;
	ptrSIB = NULL;
	ptrDisp8 = NULL;
	ptrDisp32 = NULL;
	mod = 0;
	regop = 0;
	rm = 0;
	scale = 0;
	index = 0;
	base = 0;
	address = dasmInfo.address;
	segOverride = HBGSREG_Undef;
	operandSize = HBGPTRTYPE_32bit;
#if defined(_WIN64)
	addressSize = HBGPTRTYPE_64bit;
#elif defined(_WIN32)
	addressSize = HBGPTRTYPE_32bit;
#endif
	prefix = HBGPFX_None;
	rexPrefix = HBGREXPFX_NONE;
	ptrDasm = (dasmInfo.option & HBGDASM_OPT_GETDASM) ? dasmInfo.dasm : NULL;
	ptrOpcode = (dasmInfo.option & HBGDASM_OPT_GETOPCODE) ? dasmInfo.opcode : NULL;
	ptrChars = (dasmInfo.option & HBGDASM_OPT_GETCHARS) ? &dasmInfo.chars : NULL;
}

CHbgDasmInnerInfo::~CHbgDasmInnerInfo()
{
}


LPCWSTR g_HbgStr_Blank = L" ";
LPCWSTR g_HbgStr_AddrOpen = L"[";
LPCWSTR g_HbgStr_AddrClose = L"]";
LPCWSTR g_HbgStr_Col = L":";
LPCWSTR g_HbgStr_Add = L"+";
LPCWSTR g_HbgStr_Mul = L"*";
LPCWSTR g_HbgStr_CommaBlank = L", ";
LPCWSTR g_HbgStr_1 = L"1";


//////////////////////

static void _HbgStrReg(CHbgDasmInnerInfo& info, HBGREGTYPE1 type1, HBGREGTYPE2 type2)
{
	HbgDasmStrCopy(info, g_Hbg_RegTable[type1][type2]);
}

static void _HbgStrSReg(CHbgDasmInnerInfo& info, HBGSREG sreg)
{
	if (sreg == HBGSREG_Undef)
		sreg = HBGSREG_DS;

	HbgDasmStrCopy(info, g_Hbg_SRegTable[sreg]);
}

static void _HbgStrCReg(CHbgDasmInnerInfo& info, HBGCREG creg)
{
	HbgDasmStrCopy(info, g_Hbg_CRegTable[creg]);
}

static void _HbgStrDReg(CHbgDasmInnerInfo& info, HBGDREG dreg)
{
	HbgDasmStrCopy(info, g_Hbg_DRegTable[dreg]);
}

static void _HbgStrSTReg(CHbgDasmInnerInfo& info, HBGSTREG streg)
{
	HbgDasmStrCopy(info, g_Hbg_STRegTable[streg]);
}

static void _HbgStrSIB(CHbgDasmInnerInfo& info)
{
#if defined(_WIN64)
	HBGREGTYPE1 type = HBGREGTYPE1_R64;
#elif defined(_WIN32)
	HBGREGTYPE1 type = HBGREGTYPE1_R32;
#endif

	BYTE scale = info.scale;
	BYTE index = info.index;
	BYTE base = info.base;

	// 1) index
	if (index != 0x04) {
		HBGREGTYPE1 typeX = type;
		if (info.rexPrefix & HBGREXPFX_REXX)
			typeX = (HBGREGTYPE1)(typeX + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));
		HbgDasmStrCopy(info, g_Hbg_RegTable[typeX][index]);
	}

	// 2) scale
	if (scale != 0x00) {
		HbgDasmStrCopy(info, g_HbgStr_Mul);
		WCHAR tmpBuf[HBGDASM_BUFLEN] = {0, };
		UINT scaleVal = (UINT)pow(2.0, (int)scale);
		swprintf_s(tmpBuf, HbgFmtAddrStr_4bit, scaleVal);
		HbgDasmStrCopy(info, tmpBuf);
	}

	if (index != 0x04 || scale != 0x00)
		HbgDasmStrCopy(info, g_HbgStr_Add);

	HBGREGTYPE1 typeB = type;
	if (info.rexPrefix & HBGREXPFX_REXB)
		typeB = (HBGREGTYPE1)(typeB + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	// 3) base
	if (base == 0x05) {
		WCHAR tmpBuf[HBGDASM_BUFLEN] = {0, };

		if (info.mod == 0x00) {
			// 다음은 무조건 있어야 한다.
			_ASSERT(info.ptrDisp32);
			if (info.ptrDisp32) {
				swprintf_s(tmpBuf, HbgFmtAddrStr_4byte, *info.ptrDisp32);
				HbgDasmStrCopy(info, tmpBuf);
			}
		} else {
			if (info.ptrDisp8)
				swprintf_s(tmpBuf, HbgFmtAddrStr_1byte, *info.ptrDisp8);
			else /*if (info.ptrDisp32)*/
				swprintf_s(tmpBuf, HbgFmtAddrStr_4byte, *info.ptrDisp32);

			HbgDasmStrCopy(info, tmpBuf);
			HbgDasmStrCopy(info, g_HbgStr_Add);

			HbgDasmStrCopy(info, g_Hbg_RegTable[typeB][base]);
		}
	} else {
		HbgDasmStrCopy(info, g_Hbg_RegTable[typeB][base]);
	}
};

static void _HbgStrModRMDisp(CHbgDasmInnerInfo& info, HBGREGTYPE1 type1, BOOL bDisableSeg = FALSE)
{
	BYTE mod = info.mod;
	BYTE rm = info.rm;

	if (mod == 0x03) {
		HBGREGTYPE1 typeB = type1;
		if (info.rexPrefix & HBGREXPFX_REXB)
			typeB = (HBGREGTYPE1)(typeB + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));
		HbgDasmStrCopy(info, g_Hbg_RegTable[typeB][rm]);
	} else {
#if defined(_WIN64)
	HBGREGTYPE1 type = HBGREGTYPE1_R64;
#elif defined(_WIN32)
	HBGREGTYPE1 type = HBGREGTYPE1_R32;
#endif
		HBGREGTYPE1 typeB = type;
		if (info.rexPrefix & HBGREXPFX_REXB)
			typeB = (HBGREGTYPE1)(typeB + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

		if (!bDisableSeg) {
			// - default segment
			_HbgStrSReg(info, info.segOverride);
			HbgDasmStrCopy(info, g_HbgStr_Col);
		}
		HbgDasmStrCopy(info, g_HbgStr_AddrOpen);

		WCHAR tmpBuf[HBGDASM_BUFLEN] = {0, };
		if (mod == 0x00 && rm == 0x05) {
			swprintf_s(tmpBuf, HbgFmtAddrStr_4byte, *info.ptrDisp32);
		} else {
			if (info.ptrSIB)
				_HbgStrSIB(info);
			else
				HbgDasmStrCopy(info, g_Hbg_RegTable[typeB][rm]);

			if (mod == 0x01 || mod == 0x02) {
				if (info.ptrDisp8) {
					HbgDasmStrCopy(info, g_HbgStr_Add);
					swprintf_s(tmpBuf, HbgFmtAddrStr_1byte, *info.ptrDisp8);
				} else /*if (info.ptrDisp32)*/ {
					HbgDasmStrCopy(info, g_HbgStr_Add);
					swprintf_s(tmpBuf, HbgFmtAddrStr_4byte, *info.ptrDisp32);
				}
			}
		}

		if (*tmpBuf)
			HbgDasmStrCopy(info, tmpBuf);
		
		HbgDasmStrCopy(info, g_HbgStr_AddrClose);
	}
}

static void _HbgStrImm(CHbgDasmInnerInfo& info, HBGPTRTYPE type)
{
	WCHAR tmpBuf[HBGDASM_BUFLEN] = {0, };

	switch (type) {
		case HBGPTRTYPE_8bit:
			{
				LPBYTE pImm = (info.ptrBytes)++;
				swprintf_s(tmpBuf, HbgFmtAddrStr_1byte, (DWORD_PTR)(*pImm));
			}
			break;
		case HBGPTRTYPE_16bit:
			{
				LPWORD pImm = (LPWORD)info.ptrBytes;
				info.ptrBytes += 2;
				swprintf_s(tmpBuf, HbgFmtAddrStr_2byte, (DWORD_PTR)(*pImm));
			}
			break;
		case HBGPTRTYPE_32bit:
			{
				LPDWORD pImm = (LPDWORD)info.ptrBytes;
				info.ptrBytes += 4;
				swprintf_s(tmpBuf, HbgFmtAddrStr_4byte, (DWORD_PTR)(*pImm));
			}
			break;
		case HBGPTRTYPE_64bit:
			{
				PDWORD64 pImm = (PDWORD64)info.ptrBytes;
				info.ptrBytes += 8;
				swprintf_s(tmpBuf, HbgFmtAddrStr_8byte, (DWORD_PTR)(*pImm));
			}
			break;
	}
	HbgDasmStrCopy(info, tmpBuf);
}

static void _HbgStrRel(CHbgDasmInnerInfo& info, HBGPTRTYPE type)
{
	WCHAR tmpBuf[HBGDASM_BUFLEN] = {0, };
	DWORD_PTR address = info.address;

	switch (type) {
		case HBGPTRTYPE_8bit:
			{
				LPBYTE pImm = (info.ptrBytes)++;
				address += (DWORD_PTR)(*pImm);
				address += (DWORD_PTR)(info.ptrBytes - info.ptrStart);
			}
			break;
		case HBGPTRTYPE_16bit:
			{
				LPWORD pImm = (LPWORD)info.ptrBytes;
				info.ptrBytes += 2;
				address += (DWORD_PTR)(*pImm);
				address += (DWORD_PTR)(info.ptrBytes - info.ptrStart);
			}
			break;
		case HBGPTRTYPE_32bit:
			{
				LPDWORD pImm = (LPDWORD)info.ptrBytes;
				info.ptrBytes += 4;
				address += (DWORD_PTR)(*pImm);
				address += (DWORD_PTR)(info.ptrBytes - info.ptrStart);
			}
			break;
	}

	swprintf_s(tmpBuf, HBGDEFFMT_ADDRSTR, address);
	HbgDasmStrCopy(info, tmpBuf);
}

static void _HbgStrPtr(CHbgDasmInnerInfo& info, HBGPTRTYPE type)
{
	switch (type) {
		case HBGPTRTYPE_8bit:
			HbgDasmStrCopy(info, L"byte ptr ");
			break;
		case HBGPTRTYPE_16bit:
			HbgDasmStrCopy(info, L"word ptr ");
			break;
		case HBGPTRTYPE_32bit:
			HbgDasmStrCopy(info, L"dword ptr ");
			break;
		case HBGPTRTYPE_48bit:
			HbgDasmStrCopy(info, L"fword ptr ");
			break;
		case HBGPTRTYPE_64bit:
			HbgDasmStrCopy(info, L"qword ptr ");
			break;
		case HBGPTRTYPE_80bit:
			HbgDasmStrCopy(info, L"tbyte ptr ");
			break;
		case HBGPTRTYPE_128bit:
			HbgDasmStrCopy(info, L"dqword ptr ");
			break;
	}
}

static void _HbgStrPtr16_16or32or64(CHbgDasmInnerInfo& info)
{
	WCHAR tmpBuf[HBGDASM_BUFLEN] = {0, };

	// 1) ptr16:
	LPWORD pPtr16 = (LPWORD)info.ptrBytes;
	info.ptrBytes += 2;
	swprintf_s(tmpBuf, HbgFmtAddrStr_2byte, *pPtr16);
	HbgDasmStrCopy(info, tmpBuf);
	HbgDasmStrCopy(info, g_HbgStr_Col);

	// 2) 16|32|64
	switch (info.operandSize) {
		case HBGPTRTYPE_16bit:
			{
				LPWORD p16or32or64 = (LPWORD)info.ptrBytes;
				info.ptrBytes += 2;
				swprintf_s(tmpBuf, HbgFmtAddrStr_2byte, *p16or32or64);
				HbgDasmStrCopy(info, tmpBuf);
			}
			break;
		case HBGPTRTYPE_32bit:
			{
				LPDWORD p16or32or64 = (LPDWORD)info.ptrBytes;
				info.ptrBytes += 4;
				swprintf_s(tmpBuf, HbgFmtAddrStr_4byte, *p16or32or64);
				HbgDasmStrCopy(info, tmpBuf);
			}
			break;
		case HBGPTRTYPE_64bit:
			{
				PDWORD64 p16or32or64 = (PDWORD64)info.ptrBytes;
				info.ptrBytes += 8;
				swprintf_s(tmpBuf, HbgFmtAddrStr_8byte, *p16or32or64);
				HbgDasmStrCopy(info, tmpBuf);
			}
			break;
	}
}

static void _HbgParseModRMSIBDisp(CHbgDasmInnerInfo& info)
{
	if (!info.ptrModRM) {
		// 1) ModRM
		LPBYTE& pBytes = info.ptrBytes;
		info.ptrModRM = pBytes++;
		
		BYTE mod = info.mod = ((*info.ptrModRM) & 0xC0) >> 6;
		/*BYTE regop = */info.regop = (*(info.ptrModRM) & 0x38) >> 3;
		BYTE rm = info.rm = (*info.ptrModRM) & 0x07;

		// 2) SIB
		if (mod != 0x03 && rm == 0x04) {
			info.ptrSIB = pBytes++;

			/*BYTE scale = */info.scale = ((*info.ptrSIB) & 0xC0) >> 6;
			/*BYTE index = */info.index = ((*info.ptrSIB) & 0x38) >> 3;
			BYTE base = info.base = (*info.ptrSIB) & 0x07;
			if (base == 0x05) {
				if (mod == 0x01) {
					info.ptrDisp8 = pBytes++;
				} else {
					info.ptrDisp32 = (LPDWORD)pBytes;
					pBytes += 4;
				}
			}

			if (info.segOverride == HBGSREG_Undef)
				info.segOverride = ((base == 0x04) || ((base == 0x05) && (mod != 0x00))) ? HBGSREG_SS : HBGSREG_DS;
		} else {
			if (info.segOverride == HBGSREG_Undef)
				info.segOverride = (mod != 0x00 && rm == 0x05) ? HBGSREG_SS : HBGSREG_DS;
		}

		if (!info.ptrDisp8 && !info.ptrDisp32) {
			// 3) Displacement
			if (mod == 0x01) {
				info.ptrDisp8 = pBytes++;
			} else if ((mod == 0x02) || (mod == 0x00 && rm == 0x05)) {
				info.ptrDisp32 = (LPDWORD)pBytes;
				pBytes += 4;
			}
		}
	}
}

void HbgDasmPrefix(CHbgDasmInnerInfo& info)
{
	BOOL bEnd = FALSE;

	while (!bEnd) {
		switch (*(info.ptrBytes)) {
			case 0xF0:
				{
					// Lock prefix
					HbgDasmStrCopy(info, g_Hbg_MnemonicTable[HBGMM_LOCK].str);
					HbgDasmStrCopy(info, g_HbgStr_Blank);
					info.ptrBytes++;
					break;
				}
			case 0xF2:
				{
					// mandatory
					info.prefix = HBGPFX_0xF2;

					// REPNE,REPNZ prefix
					HbgDasmStrCopy(info, g_Hbg_MnemonicTable[HBGMM_REPNE].str);
					HbgDasmStrCopy(info, g_HbgStr_Blank);
					info.ptrBytes++;
					break;
				}
			case 0xF3:
				{
					// mandatory
					info.prefix = HBGPFX_0xF3;

					// REPE,REPZ prefix
					HbgDasmStrCopy(info, g_Hbg_MnemonicTable[HBGMM_REPE].str);
					HbgDasmStrCopy(info, g_HbgStr_Blank);
					info.ptrBytes++;
					break;
				}
			case 0x26:
				{
					// ES segment override prefix
					info.segOverride = HBGSREG_ES;
					info.ptrBytes++;
					break;
				}
			case 0x2E:
				{
					// CS segment override prefix
					info.segOverride = HBGSREG_CS;
					info.ptrBytes++;
					break;
				}
			case 0x36:
				{
					// SS segment override prefix
					info.segOverride = HBGSREG_SS;
					info.ptrBytes++;
					break;
				}
			case 0x3E:
				{
					// DS segment override prefix
					info.segOverride = HBGSREG_DS;
					info.ptrBytes++;
					break;
				}
			case 0x64:
				{
					// FS segment override prefix
					info.segOverride = HBGSREG_FS;
					info.ptrBytes++;
					break;
				}
			case 0x65:
				{
					// GS segment override prefix
					info.segOverride = HBGSREG_GS;
					info.ptrBytes++;
					break;
				}
			case 0x66:
				{
					// mandatory
					info.prefix = HBGPFX_0x66;

					// Operand-size override prefix
					info.operandSize = HBGPTRTYPE_16bit;
					info.ptrBytes++;
					break;
				}
			case 0x67:
				{
					// Address-size override prefix
#if defined(_WIN64)
					info.addressSize = HBGPTRTYPE_32bit;
#elif defined(_WIN32)
					info.addressSize = HBGPTRTYPE_16bit;
#endif
					info.ptrBytes++;
					break;
				}
			default:
				{
					bEnd = TRUE;
				}
				break;
		}
	}
}

void HbgDasmREXPrefix(CHbgDasmInnerInfo& info)
{
	BYTE curByte = *info.ptrBytes;

	// REX
	if ((curByte >> 4) == 0x04) {			// 0100B
		info.rexPrefix |= HBGREXPFX_REX;

		// REX.W
		if (curByte & 0x08) {
			info.rexPrefix |= HBGREXPFX_REXW;
			info.operandSize = HBGPTRTYPE_64bit;
		}

		// REX.R
		if (curByte & 0x04)
			info.rexPrefix |= HBGREXPFX_REXR;

		// REX.X
		if (curByte & 0x02)
			info.rexPrefix |= HBGREXPFX_REXX;

		// REX.B
		if (curByte & 0x01)
			info.rexPrefix |= HBGREXPFX_REXB;

		info.ptrBytes++;
	}
}


void HbgDasmGrpInstr(HBGMM mm, BYTE opcode, CHbgDasmInnerInfo& info, HBGINSTR& tmpNewInstr)
{
	// init
	tmpNewInstr.mm = HBGMM_Undef;
	tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Undef;
	tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Undef;
	tmpNewInstr.opr[HBGOPRIDX_3RD] = HBGOPR_Undef;

	BYTE mod = (*(info.ptrBytes) & 0xC0) >> 6;
	BYTE regop = (*(info.ptrBytes) & 0x38) >> 3;
	BYTE rm = *(info.ptrBytes) & 0x07;
	HBGPFX pfx = info.prefix;

	// 나머지 Group은 현재 미구현.
	switch (mm) {
		case HBGMM_Group1:
			{
				switch (regop) {
					case 0x00:
						tmpNewInstr.mm = HBGMM_ADD;
						break;
					case 0x01:
						tmpNewInstr.mm = HBGMM_OR;
						break;
					case 0x02:
						tmpNewInstr.mm = HBGMM_ADC;
						break;
					case 0x03:
						tmpNewInstr.mm = HBGMM_SBB;
						break;
					case 0x04:
						tmpNewInstr.mm = HBGMM_AND;
						break;
					case 0x05:
						tmpNewInstr.mm = HBGMM_SUB;
						break;
					case 0x06:
						tmpNewInstr.mm = HBGMM_XOR;
						break;
					case 0x07:
						tmpNewInstr.mm = HBGMM_CMP;
						break;
				}

				switch (opcode) {
					case 0x80:
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Eb;
						tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
						break;
					case 0x81:
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ev;
						tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Iz;
						break;
					case 0x82:
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Eb;
						tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
						break;
					case 0x83:
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ev;
						tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
						break;
				}
			}
			break;
		case HBGMM_Group1A:
			{
				switch (regop) {
					case 0x00:
						tmpNewInstr.mm = HBGMM_POP;
						break;
				}

				switch (opcode) {
					case 0x8F:
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ev;
						break;
				}

			}
			break;
		case HBGMM_Group2:
			{
				switch (regop) {
					case 0x00:
						tmpNewInstr.mm = HBGMM_ROL;
						break;
					case 0x01:
						tmpNewInstr.mm = HBGMM_ROR;
						break;
					case 0x02:
						tmpNewInstr.mm = HBGMM_RCL;
						break;
					case 0x03:
						tmpNewInstr.mm = HBGMM_RCR;
						break;
					case 0x04:
						tmpNewInstr.mm = HBGMM_SHL;
						break;
					case 0x05:
						tmpNewInstr.mm = HBGMM_SHR;
						break;
					case 0x06:
						// HBGMM_Undef
						break;
					case 0x07:
						tmpNewInstr.mm = HBGMM_SAR;
						break;
				}

				switch (opcode) {
					case 0xC0:
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Eb;
						tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
						break;
					case 0xC1:
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ev;
						tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
						break;
					case 0xD0:
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Eb;
						tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_1;
						break;
					case 0xD1:
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ev;
						tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_1;
						break;
					case 0xD2:
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Eb;
						tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_CL;
						break;
					case 0xD3:
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ev;
						tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_CL;
						break;
				}
			}
			break;
		case HBGMM_Group3:
			{
				switch (opcode) {
					case 0xF6:
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Eb;
						break;
					case 0xF7:
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ev;
						break;
				}

				switch (regop) {
					case 0x00:
						tmpNewInstr.mm = HBGMM_TEST;
						if (opcode == 0xF6)
							tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
						else	// if (opcode == 0xF7)
							tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Iz;
						break;
					case 0x01:
						// HBGMM_Undef
						break;
					case 0x02:
						tmpNewInstr.mm = HBGMM_NOT;
						break;
					case 0x03:
						tmpNewInstr.mm = HBGMM_NEG;
						break;
					case 0x04:
						tmpNewInstr.mm = HBGMM_MUL;
						break;
					case 0x05:
						tmpNewInstr.mm = HBGMM_IMUL;
						break;
					case 0x06:
						tmpNewInstr.mm = HBGMM_DIV;
						break;
					case 0x07:
						tmpNewInstr.mm = HBGMM_IDIV;
						break;
				}

			}
			break;
		case HBGMM_Group4:
			{
				switch (regop) {
					case 0x00:
						tmpNewInstr.mm = HBGMM_INC;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Eb;
						break;
					case 0x01:
						tmpNewInstr.mm = HBGMM_DEC;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Eb;
						break;
				}
			}
			break;
		case HBGMM_Group5:
			{
				switch (regop) {
					case 0x00:
						tmpNewInstr.mm = HBGMM_INC;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ev;
						break;
					case 0x01:
						tmpNewInstr.mm = HBGMM_DEC;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ev;
						break;
					case 0x02:
						tmpNewInstr.mm = HBGMM_CALL;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ev;
						break;
					case 0x03:
						tmpNewInstr.mm = HBGMM_CALL;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ep;
						break;
					case 0x04:
						tmpNewInstr.mm = HBGMM_JMP;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ev;
						break;
					case 0x05:
						tmpNewInstr.mm = HBGMM_JMP;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ep;
						break;
					case 0x06:
						tmpNewInstr.mm = HBGMM_PUSH;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ev;
						break;
					case 0x07:
						// HBGMM_Undef
						break;
				}
			}
			break;
		case HBGMM_Group6:
			{
				switch (regop) {
					case 0x00:
						tmpNewInstr.mm = HBGMM_SLDT;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Rv;
						break;
					case 0x01:
						tmpNewInstr.mm = HBGMM_STR;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Rv;
						break;
					case 0x02:
						tmpNewInstr.mm = HBGMM_LLDT;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ew;
						break;
					case 0x03:
						tmpNewInstr.mm = HBGMM_LTR;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ew;
						break;
					case 0x04:
						tmpNewInstr.mm = HBGMM_VERR;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ew;
						break;
					case 0x05:
						tmpNewInstr.mm = HBGMM_VERW;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ew;
						break;
				}
			}
			break;
		case HBGMM_Group7:
			{
				switch (regop) {
					case 0x00:
						switch (mod) {
							case 0x03:
								switch (rm) {
									case 0x01:
										tmpNewInstr.mm = HBGMM_VMCALL;
										break;
									case 0x02:
										tmpNewInstr.mm = HBGMM_VMLAUNCH;
										break;
									case 0x03:
										tmpNewInstr.mm = HBGMM_VMRESUME;
										break;
									case 0x04:
										tmpNewInstr.mm = HBGMM_VMXOFF;
										break;
								}
								break;
							default:
								tmpNewInstr.mm = HBGMM_SGDT;
								tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ms;
								break;
						}
						break;
					case 0x01:
						switch (mod) {
							case 0x03:
								switch (rm) {
									case 0x00:
										tmpNewInstr.mm = HBGMM_MONITOR;
										break;
									case 0x01:
										tmpNewInstr.mm = HBGMM_MWAIT;
										break;
								}
								break;
							default:
								tmpNewInstr.mm = HBGMM_SIDT;
								tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ms;
								break;
						}
						break;
					case 0x02:
						switch (mod) {
							case 0x03:
								switch (rm) {
									case 0x00:
										tmpNewInstr.mm = HBGMM_XGETBV;
										break;
									case 0x01:
										tmpNewInstr.mm = HBGMM_XSETBV;
										break;
								}
								break;
							default:
								tmpNewInstr.mm = HBGMM_LGDT;
								tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ms;
								break;
						}
						break;
					case 0x03:
						switch (mod) {
							case 0x03:
								break;
							default:
								tmpNewInstr.mm = HBGMM_LIDT;
								tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ms;
								break;
						}
						break;
					case 0x04:
						tmpNewInstr.mm = HBGMM_SMSW;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Mw;
						break;
					case 0x05:
						// HBGMM_Undef
						break;
					case 0x06:
						tmpNewInstr.mm = HBGMM_LMSW;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ew;
						break;
					case 0x07:
						switch (mod) {
							case 0x03:
								switch (rm) {
									case 0x00:
										tmpNewInstr.mm = HBGMM_SWAPGS;
										break;
									case 0x01:
										tmpNewInstr.mm = HBGMM_RDTSCP;
										break;
								}
								break;
							default:
								tmpNewInstr.mm = HBGMM_INVLPG;
								tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Mb;
								break;
						}
						break;
				}
			}
			break;
		case HBGMM_Group8:
			{
				switch (regop) {
					case 0x00:
						// HBGMM_Undef
						break;
					case 0x01:
						// HBGMM_Undef
						break;
					case 0x02:
						// HBGMM_Undef
						break;
					case 0x03:
						// HBGMM_Undef
						break;
					case 0x04:
						tmpNewInstr.mm = HBGMM_BT;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ev;
						tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
						break;
					case 0x05:
						tmpNewInstr.mm = HBGMM_BTS;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ev;
						tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
						break;
					case 0x06:
						tmpNewInstr.mm = HBGMM_BTR;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ev;
						tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
						break;
					case 0x07:
						tmpNewInstr.mm = HBGMM_BTC;
						tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ev;
						tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
						break;
				}
			}
			break;
		case HBGMM_Group9:
			{
				switch (regop) {
					case 0x00:
						// HBGMM_Undef
						break;
					case 0x01:
						switch (mod) {
							case 0x03:
								// HBGMM_Undef
								break;
							default:
								tmpNewInstr.mm = HBGMM_CMPXCHG16B;
								tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Mdq;
								break;
						}
						break;
					case 0x02:
						// HBGMM_Undef
						break;
					case 0x03:
						// HBGMM_Undef
						break;
					case 0x04:
						// HBGMM_Undef
						break;
					case 0x05:
						// HBGMM_Undef
						break;
					case 0x06:
						switch (mod) {
							case 0x03:
								// HBGMM_Undef
								break;
							default:
								switch (pfx) {
									case HBGPFX_0x66:
										tmpNewInstr.mm = HBGMM_VMCLEAR;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Mq;
										break;
									case HBGPFX_0xF3:
										tmpNewInstr.mm = HBGMM_VMXON;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Mq;
										break;
									default:
										tmpNewInstr.mm = HBGMM_VMPTRLD;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Mq;
										break;
								}
								break;
						}
						break;
					case 0x07:
						switch (mod) {
							case 0x03:
								// HBGMM_Undef
								break;
							default:
								tmpNewInstr.mm = HBGMM_VMPTRST;
								tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Mq;
								break;
						}
						break;
				}
			}
		case HBGMM_Group10:
			{
				// HBGMM_Undef
			}
			break;
		case HBGMM_Group11:
			{
				switch (regop) {
					case 0x00:
						tmpNewInstr.mm = HBGMM_MOV;
						if (opcode == 0xC6) {
							tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Eb;
							tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
						} else {	// if (opcode == 0xC7)
							tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Ev;
							tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Iz;
						}
						break;
				}
			}
			break;
		case HBGMM_Group12:
			{
				switch (regop) {
					case 0x00:
						// HBGMM_Undef
						break;
					case 0x01:
						// HBGMM_Undef
						break;
					case 0x02:
						switch (mod) {
							case 0x03:
								switch (pfx) {
									case HBGPFX_0x66:
										tmpNewInstr.mm = HBGMM_PSRLW;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Udq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
									default:
										tmpNewInstr.mm = HBGMM_PSRLW;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Nq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
								}
								break;
							default:
								// HBGMM_Undef
								break;
						}
						break;
					case 0x03:
						// HBGMM_Undef
						break;
					case 0x04:
						switch (mod) {
							case 0x03:
								switch (pfx) {
									case HBGPFX_0x66:
										tmpNewInstr.mm = HBGMM_PSRAW;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Udq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
									default:
										tmpNewInstr.mm = HBGMM_PSRAW;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Nq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
								}
								break;
							default:
								// HBGMM_Undef
								break;
						}
						break;
					case 0x05:
						// HBGMM_Undef
						break;
					case 0x06:
						switch (mod) {
							case 0x03:
								switch (pfx) {
									case HBGPFX_0x66:
										tmpNewInstr.mm = HBGMM_PSLLW;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Udq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
									default:
										tmpNewInstr.mm = HBGMM_PSLLW;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Nq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
								}
								break;
							default:
								// HBGMM_Undef
								break;
						}
						break;
					case 0x07:
						// HBGMM_Undef
						break;
				}
			}
			break;
		case HBGMM_Group13:
			{
				switch (regop) {
					case 0x00:
						// HBGMM_Undef
						break;
					case 0x01:
						// HBGMM_Undef
						break;
					case 0x02:
						switch (mod) {
							case 0x03:
								switch (pfx) {
									case HBGPFX_0x66:
										tmpNewInstr.mm = HBGMM_PSRLD;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Udq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
									default:
										tmpNewInstr.mm = HBGMM_PSRLD;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Nq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
								}
								break;
							default:
								// HBGMM_Undef
								break;
						}
						break;
					case 0x03:
						// HBGMM_Undef
						break;
					case 0x04:
						switch (mod) {
							case 0x03:
								switch (pfx) {
									case HBGPFX_0x66:
										tmpNewInstr.mm = HBGMM_PSRAD;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Udq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
									default:
										tmpNewInstr.mm = HBGMM_PSRAD;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Nq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
								}
								break;
							default:
								// HBGMM_Undef
								break;
						}
						break;
					case 0x05:
						// HBGMM_Undef
						break;
					case 0x06:
						switch (mod) {
							case 0x03:
								switch (pfx) {
									case HBGPFX_0x66:
										tmpNewInstr.mm = HBGMM_PSLLD;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Udq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
									default:
										tmpNewInstr.mm = HBGMM_PSLLD;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Nq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
								}
								break;
							default:
								// HBGMM_Undef
								break;
						}
						break;
					case 0x07:
						// HBGMM_Undef
						break;
				}
			}
			break;
		case HBGMM_Group14:
			{
				switch (regop) {
					case 0x00:
						// HBGMM_Undef
						break;
					case 0x01:
						// HBGMM_Undef
						break;
					case 0x02:
						switch (mod) {
							case 0x03:
								switch (pfx) {
									case HBGPFX_0x66:
										tmpNewInstr.mm = HBGMM_PSRLQ;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Udq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
									default:
										tmpNewInstr.mm = HBGMM_PSRLQ;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Nq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
								}
								break;
							default:
								// HBGMM_Undef
								break;
						}
						break;
					case 0x03:
						switch (mod) {
							case 0x03:
								switch (pfx) {
									case HBGPFX_0x66:
										tmpNewInstr.mm = HBGMM_PSRLDQ;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Udq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
								}
								break;
							default:
								// HBGMM_Undef
								break;
						}
						break;
					case 0x04:
						switch (mod) {
							case 0x03:
								switch (pfx) {
									case HBGPFX_0x66:
										tmpNewInstr.mm = HBGMM_PSLLQ;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Udq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
									default:
										tmpNewInstr.mm = HBGMM_PSLLQ;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Nq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
								}
								break;
							default:
								// HBGMM_Undef
								break;
						}
						break;
					case 0x05:
						// HBGMM_Undef
						break;
					case 0x06:
						switch (mod) {
							case 0x03:
								switch (pfx) {
									case HBGPFX_0x66:
										tmpNewInstr.mm = HBGMM_PSLLW;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Udq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
									default:
										tmpNewInstr.mm = HBGMM_PSLLW;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Nq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
								}
								break;
							default:
								// HBGMM_Undef
								break;
						}
						break;
					case 0x07:
						switch (mod) {
							case 0x03:
								switch (pfx) {
									case HBGPFX_0x66:
										tmpNewInstr.mm = HBGMM_PSLLDQ;
										tmpNewInstr.opr[HBGOPRIDX_1ST] = HBGOPR_Udq;
										tmpNewInstr.opr[HBGOPRIDX_2ND] = HBGOPR_Ib;
										break;
								}
								break;
							default:
								// HBGMM_Undef
								break;
						}
						break;
				}
			}
			break;
		case HBGMM_Group15:
			{
				switch (regop) {
					case 0x00:
						switch (mod) {
							case 0x03:
								// HBGMM_Undef
								break;
							default:
								tmpNewInstr.mm = HBGMM_FXSAVE;
								break;
						}
						break;
					case 0x01:
						switch (mod) {
							case 0x03:
								// HBGMM_Undef
								break;
							default:
								tmpNewInstr.mm = HBGMM_FXRSTOR;
								break;
						}
						break;
					case 0x02:
						switch (mod) {
							case 0x03:
								// HBGMM_Undef
								break;
							default:
								tmpNewInstr.mm = HBGMM_LDMXCSR;
								break;
						}
						break;
					case 0x03:
						switch (mod) {
							case 0x03:
								// HBGMM_Undef
								break;
							default:
								tmpNewInstr.mm = HBGMM_STMXCSR;
								break;
						}
						break;
					case 0x04:
						switch (mod) {
							case 0x03:
								// HBGMM_Undef
								break;
							default:
								tmpNewInstr.mm = HBGMM_XSAVE;
								break;
						}
						break;
					case 0x05:
						switch (mod) {
							case 0x03:
								tmpNewInstr.mm = HBGMM_LFENCE;
								break;
							default:
								tmpNewInstr.mm = HBGMM_XRSTOR;
								break;
						}
						break;
					case 0x06:
						switch (mod) {
							case 0x03:
								tmpNewInstr.mm = HBGMM_MFENCE;
								break;
							default:
								// HBGMM_Undef
								break;
						}
						break;
					case 0x07:
						switch (mod) {
							case 0x03:
								tmpNewInstr.mm = HBGMM_SFENCE;
								break;
							default:
								tmpNewInstr.mm = HBGMM_CLFLUSH;
								break;
						}
						break;
				}
			}
			break;
		case HBGMM_Group16:
			{
				switch (regop) {
					case 0x00:
						switch (mod) {
							case 0x03:
								// HBGMM_Undef
								break;
							default:
								tmpNewInstr.mm = HBGMM_PREFETCHNTA;
								break;
						}
						break;
					case 0x01:
						switch (mod) {
							case 0x03:
								// HBGMM_Undef
								break;
							default:
								tmpNewInstr.mm = HBGMM_PREFETCH0;
								break;
						}
						break;
					case 0x02:
						switch (mod) {
							case 0x03:
								// HBGMM_Undef
								break;
							default:
								tmpNewInstr.mm = HBGMM_PREFETCH1;
								break;
						}
						break;
					case 0x03:
						switch (mod) {
							case 0x03:
								// HBGMM_Undef
								break;
							default:
								tmpNewInstr.mm = HBGMM_PREFETCH2;
								break;
						}
						break;
					case 0x04:
						// HBGMM_Undef
						break;
					case 0x05:
						// HBGMM_Undef
						break;
					case 0x06:
						// HBGMM_Undef
						break;
					case 0x07:
						// HBGMM_Undef
						break;
				}
			}
			break;
	}
}


#include "User/HbgDasm_EscOpcTbl.inl"


void HbgDasmEscInstr(BYTE opcode, CHbgDasmInnerInfo& info, HBGINSTR*& pInstr)
{
	if ((opcode >= 0xD8) && (opcode <= 0xDF)) {
		BYTE modrm = *info.ptrBytes;
		if (modrm < 0xC0) {
			BYTE regop = (modrm & 0x38) >> 3;
			pInstr = &g_Hbg_EscWithin00HtoBFHOpcodeTable[opcode - 0xD8][regop];
		} else {
			pInstr = &g_Hbg_EscOutside00HtoBFHOpcodeTable[opcode - 0xD8][modrm - 0xC0];
		}
	}

	if (pInstr->mm != HBGMM_Undef)
		_HbgParseModRMSIBDisp(info);
}


#include "User/HbgDasmTables.inl"


#ifdef _DEBUG

class _CHbgDasmCheckTable
{
public:
	_CHbgDasmCheckTable()
	{
		UINT total = 0;
		UINT nIdx = 0;

		// 1) Mnemonic String 테이블 검사
		total = sizeof(g_Hbg_MnemonicTable) / sizeof(HBGMMSTR);
		nIdx = 0;
		while (nIdx < total) {
			if (((UINT)(g_Hbg_MnemonicTable[nIdx]._idx)) != nIdx) {
				// Mnemonic String 테이블의 순서가 잘못됨.
				_ASSERT(FALSE);
			}

			++nIdx;
		}

		// 2) Operand Operation 테이블 검사
		total = sizeof(g_Hbg_OperandOperationTable) / sizeof(HBGMMSTR);
		nIdx = 0;
		while (nIdx < total) {
			if (((UINT)(g_Hbg_OperandOperationTable[nIdx]._idx)) != nIdx) {
				// Operand Operation 테이블의 순서가 잘못됨.
				_ASSERT(FALSE);
			}

			++nIdx;
		}
	}
};

static _CHbgDasmCheckTable checker;

#endif // _DEBUG
