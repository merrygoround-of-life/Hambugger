#pragma once


// input options
#define HBGDASM_OPT_RETLENGTH	0x00		// default
#define HBGDASM_OPT_GETDASM		0x01
#define HBGDASM_OPT_GETOPCODE	0x02
#define HBGDASM_OPT_GETCHARS	0x04
#define HBGDASM_OPT_GETREMARK	0x08		// ¹Ì±¸Çö


// output characters
#define HBGDASM_CHAR_GENERAL	0x00		// default
#define HBGDASM_CHAR_UNKNOWN	0x01		// unknown instruction
#define HBGDASM_CHAR_CALL		0x02		// call


#define HBGDASM_BUFLEN			100


typedef struct HBGDASM_DLL _HbgDasmInfo
{
	// [in]
	BYTE option;
	LPBYTE bytes;
	SIZE_T len;
	DWORD_PTR address;

	// [out]
	WCHAR dasm[HBGDASM_BUFLEN];
	WCHAR opcode[HBGDASM_BUFLEN];
	BYTE chars;
} HbgDasmInfo;


HBGDASM_DLL void HbgDasmInit(HbgDasmInfo& dasmInfo, BYTE option = HBGDASM_OPT_RETLENGTH, LPBYTE bytes = NULL, SIZE_T len = 0, DWORD_PTR address = 0);
HBGDASM_DLL SIZE_T HbgDasmParse(HbgDasmInfo& dasmInfo);
