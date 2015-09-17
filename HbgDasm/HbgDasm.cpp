// HbgDasm.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "HbgDasmDefs.h"


HBGDASM_DLL void HbgDasmInit(HbgDasmInfo& dasmInfo, BYTE option/*= HBGDASM_OPT_RETLENGTH*/, LPBYTE bytes/*= NULL*/, SIZE_T len/*= 0*/, DWORD_PTR address/*= 0*/)
{
	dasmInfo.option = option;
	dasmInfo.bytes = bytes;
	dasmInfo.len = len;
	dasmInfo.address = address;

	*dasmInfo.dasm = L'\0';
	*dasmInfo.opcode = L'\0';
	dasmInfo.chars = HBGDASM_CHAR_GENERAL;
}


HBGDASM_DLL SIZE_T HbgDasmParse(HbgDasmInfo& dasmInfo)
{
	if (!dasmInfo.bytes || !dasmInfo.len)
		return 0;

	CHbgDasmInnerInfo info(dasmInfo);
	HBGINSTR* pInstr = NULL;

	// 1) prefix
	HbgDasmPrefix(info);

#if defined(_WIN64)
	// 1-5) REX prefix
	HbgDasmREXPrefix(info);
#endif

	// 2) instruction
	BYTE opcode = *(info.ptrBytes)++;
	switch (opcode) {
		case 0x0F:
			opcode = *(info.ptrBytes)++;

			switch (opcode) {
				case 0x38:		// 3-byte (OF38) opcode
					opcode = *(info.ptrBytes)++;
					pInstr = &g_Hbg_3Byte38OpcodeTable[opcode][info.prefix];
					break;
				case 0x3A:		// 3-byte (OF3A) opcode
					opcode = *(info.ptrBytes)++;
					pInstr = &g_Hbg_3Byte3AOpcodeTable[opcode][info.prefix];
					break;
				default:		// 2-byte (OF) opcode
					pInstr = &g_Hbg_2ByteOpcodeTable[opcode][info.prefix];
					break;
			}
			break;
		default:				// 1-byte opcode
			pInstr = &g_Hbg_1ByteOpcodeTable[opcode];
			break;
	}

	// 3) group inctruction
	HBGINSTR tmpGrpInstr;
	if ((pInstr->mm >= HBGMM_Group16) && (pInstr->mm <= HBGMM_Group1)) {
		HbgDasmGrpInstr(pInstr->mm, opcode, info, tmpGrpInstr);
		pInstr = &tmpGrpInstr;
	}

	// 4) Escape inctruction
	if (pInstr->mm == HBGMM_Escape)
		HbgDasmEscInstr(opcode, info, pInstr);

	// 5) mnemonic
	switch (pInstr->mm) {
		case HBGMM_Undef:
			{
				// 알 수 없는 opcode
				//_ASSERT(FALSE);
				//#ifdef _DEBUG
				//	WCHAR tmp[_MAX_PATH];
				//	swprintf_s(tmp, L"[HbgDasm] 0x%08X: Undefined Opcode.\n", info.address);
				//	OutputDebugString(tmp);
				//#endif // _DEBUG
				HbgDasmStrCopy(info, L"???");
				HbgAddCharacters(info, HBGDASM_CHAR_UNKNOWN);
			}
			break;
		default:
			{
				HbgDasmStrCopy(info, g_Hbg_MnemonicTable[pInstr->mm].str);
				if (pInstr->mm == HBGMM_CALL)
					HbgAddCharacters(info, HBGDASM_CHAR_CALL);

				// 6) operands

				// - 1st operand
				HBGOPR opr1st = pInstr->opr[HBGOPRIDX_1ST];
				if (opr1st != HBGOPR_Undef) {
					HbgDasmStrCopy(info, g_HbgStr_Blank);
					g_Hbg_OperandOperationTable[opr1st].func(info);

					// - 2nd operand
					HBGOPR opr2nd = pInstr->opr[HBGOPRIDX_2ND];
					if (opr2nd != HBGOPR_Undef) {
						HbgDasmStrCopy(info, g_HbgStr_CommaBlank);
						g_Hbg_OperandOperationTable[opr2nd].func(info);

						// - 3rd operand
						HBGOPR opr3rd = pInstr->opr[HBGOPRIDX_3RD];
						if (opr3rd != HBGOPR_Undef) {
							HbgDasmStrCopy(info, g_HbgStr_CommaBlank);
							g_Hbg_OperandOperationTable[opr3rd].func(info);
						}
					}
				}
			}
			break;
	}

	SIZE_T opLen = 0;
	if ((info.ptrBytes - info.ptrEnd) > 1) {
		if (info.ptrDasm) {
			*dasmInfo.dasm = L'\0';
			*dasmInfo.opcode = L'\0';
			dasmInfo.chars = HBGDASM_CHAR_GENERAL;
		}
	} else {
		HbgDasmStrCopy(info, L"\0");

		opLen = info.ptrBytes - dasmInfo.bytes;
		HbgOpcodeStrCopy(info, dasmInfo.bytes, opLen);
	}

	return opLen;
}
