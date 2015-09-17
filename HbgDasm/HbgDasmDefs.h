#ifndef _HbgDasmDefs_H_
#define _HbgDasmDefs_H_


#include "User/HbgDasmTypes.inl"


//////////////////////
// CHbgDasmInnerInfo Declaration
class CHbgDasmInnerInfo
{
public:
	CHbgDasmInnerInfo(HbgDasmInfo& dasmInfo);
	~CHbgDasmInnerInfo();

public:
	LPBYTE ptrBytes;
	LPBYTE ptrStart;
	LPBYTE ptrEnd;
	LPBYTE ptrModRM;
	LPBYTE ptrSIB;
	LPBYTE ptrDisp8;
	LPDWORD ptrDisp32;
	BYTE mod;
	BYTE regop;
	BYTE rm;
	BYTE scale;
	BYTE index;
	BYTE base;
	DWORD_PTR address;
	HBGSREG segOverride;
	HBGPTRTYPE operandSize;
	HBGPTRTYPE addressSize;
	HBGPFX prefix;
	BYTE rexPrefix;
	LPWSTR ptrDasm;
	LPWSTR ptrOpcode;
	LPBYTE ptrChars;
};


typedef void (*HBGOPRFUNC)(CHbgDasmInnerInfo&);


typedef struct _HbgMnemonicString
{
	HBGMM _idx;			// for debug
	LPCWSTR str;
} HBGMMSTR;


typedef struct _HbgOperandOperation
{
	HBGOPR _idx;		// for debug
	HBGOPRFUNC func;
} HBGOPROPR;


typedef struct _HbgInstruction
{
	HBGMM mm;
	HBGOPR opr[HBGOPRIDX_COUNT];
} HBGINSTR;


#define	HBGREXPFX_NONE					0x00
#define	HBGREXPFX_REX					0x01
#define	HBGREXPFX_REXW					0x02
#define	HBGREXPFX_REXR					0x04
#define	HBGREXPFX_REXX					0x08
#define	HBGREXPFX_REXB					0x10

#define HBGOPCODE_COUNT					(0xFF - 0x00 + 0x01)		// = 0x0100 (256)

#define HBGESCOPCODE_COUNT				(0xDF - 0xD8 + 0x01)		// = 0x0008 (8)

#define HBGESCWINTHIN_002BF_COUNT		(1 << 3)					// = 0x0008 (8)

#define HBGESCOUTSIDE_002BF_COUNT		(0xFF - 0xC0 + 0x01)		// = 0x0040 (64)

extern LPCWSTR g_Hbg_RegTable[HBGREGTYPE1_COUNT][HBGREGTYPE2_COUNT];

extern LPCWSTR g_Hbg_SRegTable[];

extern LPCWSTR g_Hbg_CRegTable[];

extern LPCWSTR g_Hbg_DRegTable[];

extern LPCWSTR g_Hbg_STRegTable[];

extern HBGMMSTR g_Hbg_MnemonicTable[];

extern HBGINSTR g_Hbg_1ByteOpcodeTable[HBGOPCODE_COUNT];

extern HBGINSTR g_Hbg_2ByteOpcodeTable[HBGOPCODE_COUNT][HBGPFX_COUNT];

extern HBGINSTR g_Hbg_3Byte38OpcodeTable[HBGOPCODE_COUNT][HBGPFX_COUNT];

extern HBGINSTR g_Hbg_3Byte3AOpcodeTable[HBGOPCODE_COUNT][HBGPFX_COUNT];

extern HBGINSTR g_Hbg_EscWithin00HtoBFHOpcodeTable[HBGESCOPCODE_COUNT][HBGESCWINTHIN_002BF_COUNT];

extern HBGINSTR g_Hbg_EscOutside00HtoBFHOpcodeTable[HBGESCOPCODE_COUNT][HBGESCOUTSIDE_002BF_COUNT];

extern HBGOPROPR g_Hbg_OperandOperationTable[];


extern LPCWSTR g_HbgStr_Blank;		// L" "
extern LPCWSTR g_HbgStr_AddrOpen;		// L"["
extern LPCWSTR g_HbgStr_AddrClose;		// L"]"
extern LPCWSTR g_HbgStr_Col;		// L":"
extern LPCWSTR g_HbgStr_Add;		// L"+"
extern LPCWSTR g_HbgStr_Mul;		// L"*"
extern LPCWSTR g_HbgStr_CommaBlank;		// L", "
extern LPCWSTR g_HbgStr_1;		// L"1"


// Utilities
void HbgDasmPrefix(CHbgDasmInnerInfo& info);
void HbgDasmREXPrefix(CHbgDasmInnerInfo& info);
void HbgDasmGrpInstr(HBGMM mm, BYTE opcode, CHbgDasmInnerInfo& info, HBGINSTR& tmpNewInstr);
void HbgDasmEscInstr(BYTE opcode, CHbgDasmInnerInfo& info, HBGINSTR*& pInstr);

inline void HbgDasmStrCopy(CHbgDasmInnerInfo& info, LPCWSTR source)
{
	if (info.ptrDasm) {
		do {
			*(info.ptrDasm)++ = *source++;
		} while (*source);
	}
}

inline void HbgOpcodeStrCopy(CHbgDasmInnerInfo& info, LPBYTE ptrBytes, SIZE_T lenBytes)
{
	if (info.ptrOpcode) {
		BYTE curByte;
		int idxLoop;
		while (lenBytes--) {
			idxLoop = 8;
			while (idxLoop > 0) {
				idxLoop -= 4;
				curByte = (*ptrBytes >> idxLoop) & 0x0F;
				if (curByte >= 0x00 && curByte <= 0x09)
					*(info.ptrOpcode)++ = curByte + L'0';
				else if (curByte >= 0x0A && curByte <= 0x0F)
					*(info.ptrOpcode)++ = curByte - 0x0A + L'A';
			}

			++ptrBytes;
		}

		*(info.ptrOpcode)++ = L'\0';
	}
}

inline void HbgAddCharacters(CHbgDasmInnerInfo& info, BYTE chars)
{
	if (info.ptrChars)
		(*info.ptrChars) |= chars;
}


#endif // _HbgDasmDefs_H_
