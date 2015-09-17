
inline void _HbgDasmTrace(LPCWSTR oprTypeStr, CHbgDasmInnerInfo& info)
{
	if (!info.ptrDasm) {
		WCHAR tmp[_MAX_PATH];
		swprintf_s(tmp, L"[HbgDasm] 0x%08I32X: Oprand Operation \"%s\" 미구현\n", info.address, oprTypeStr);
		OutputDebugString(tmp);
	}
}

#ifdef _DEBUG
#	define _HBGTRACE(str, info)	_HbgDasmTrace(str, info)
#else
#	define _HBGTRACE(str, info)
#endif //_DEBUG

inline HBGREGTYPE1 _HbgGetRegTypeByOperandSize(HBGPTRTYPE operandSize)
{
	HBGREGTYPE1 regType = HBGREGTYPE1_R32;

	switch (operandSize) {
		case HBGPTRTYPE_8bit:
			regType = HBGREGTYPE1_R8;
			break;
		case HBGPTRTYPE_16bit:
			regType = HBGREGTYPE1_R16;
			break;
		case HBGPTRTYPE_32bit:
			regType = HBGREGTYPE1_R32;
			break;
		case HBGPTRTYPE_64bit:
			regType = HBGREGTYPE1_R64;
			break;
	}

	return regType;
}

// AL
void HbgOprOprAL(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = HBGREGTYPE1_R8;
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_0]);
}

// CL
void HbgOprOprCL(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = HBGREGTYPE1_R8;
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_1]);
}

// DL
void HbgOprOprDL(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = HBGREGTYPE1_R8;
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_2]);
}

// BL
void HbgOprOprBL(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = HBGREGTYPE1_R8;
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_3]);
}

// AH
void HbgOprOprAH(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = HBGREGTYPE1_R8;
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_4]);
}

// CH
void HbgOprOprCH(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = HBGREGTYPE1_R8;
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_5]);
}

// DH
void HbgOprOprDH(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = HBGREGTYPE1_R8;
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_6]);
}

// BH
void HbgOprOprBH(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = HBGREGTYPE1_R8;
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_7]);
}

// AX
void HbgOprOprAX(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = HBGREGTYPE1_R16;
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_0]);
}

// CX
void HbgOprOprCX(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = HBGREGTYPE1_R16;
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_1]);
}

// DX
void HbgOprOprDX(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = HBGREGTYPE1_R16;
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_2]);
}

// BX
void HbgOprOprBX(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = HBGREGTYPE1_R16;
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_3]);
}

// SP
void HbgOprOprSP(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = HBGREGTYPE1_R16;
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_4]);
}

// BP
void HbgOprOprBP(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = HBGREGTYPE1_R16;
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_5]);
}

// SI
void HbgOprOprSI(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = HBGREGTYPE1_R16;
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_6]);
}

// DI
void HbgOprOprDI(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = HBGREGTYPE1_R16;
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_7]);
}

// rAX
void HbgOprOprrAX(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = _HbgGetRegTypeByOperandSize(info.operandSize);
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_0]);
}

// rCX
void HbgOprOprrCX(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = _HbgGetRegTypeByOperandSize(info.operandSize);
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_1]);
}

// rDX
void HbgOprOprrDX(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = _HbgGetRegTypeByOperandSize(info.operandSize);
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_2]);
}

// rBX
void HbgOprOprrBX(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = _HbgGetRegTypeByOperandSize(info.operandSize);
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_3]);
}

// rSP
void HbgOprOprrSP(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = _HbgGetRegTypeByOperandSize(info.operandSize);
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_4]);
}

// rBP
void HbgOprOprrBP(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = _HbgGetRegTypeByOperandSize(info.operandSize);
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_5]);
}

// rSI
void HbgOprOprrSI(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = _HbgGetRegTypeByOperandSize(info.operandSize);
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_6]);
}

// rDI
void HbgOprOprrDI(CHbgDasmInnerInfo& info)
{
	HBGREGTYPE1 regType = _HbgGetRegTypeByOperandSize(info.operandSize);
	if (info.rexPrefix & HBGREXPFX_REXB)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	HbgDasmStrCopy(info, g_Hbg_RegTable[regType][HBGREGTYPE2_7]);
}

// CS
void HbgOprOprCS(CHbgDasmInnerInfo& info)
{
	_HbgStrSReg(info, HBGSREG_CS);
}

// SS
void HbgOprOprSS(CHbgDasmInnerInfo& info)
{
	_HbgStrSReg(info, HBGSREG_SS);
}

// DS
void HbgOprOprDS(CHbgDasmInnerInfo& info)
{
	_HbgStrSReg(info, HBGSREG_DS);
}

// ES
void HbgOprOprES(CHbgDasmInnerInfo& info)
{
	_HbgStrSReg(info, HBGSREG_ES);
}

// FS
void HbgOprOprFS(CHbgDasmInnerInfo& info)
{
	_HbgStrSReg(info, HBGSREG_FS);
}

// GS
void HbgOprOprGS(CHbgDasmInnerInfo& info)
{
	_HbgStrSReg(info, HBGSREG_GS);
}

// ST0
void HbgOprOprST0(CHbgDasmInnerInfo& info)
{
	_HbgStrSTReg(info, HBGSTREG_0);
}

// ST1
void HbgOprOprST1(CHbgDasmInnerInfo& info)
{
	_HbgStrSTReg(info, HBGSTREG_1);
}

// ST2
void HbgOprOprST2(CHbgDasmInnerInfo& info)
{
	_HbgStrSTReg(info, HBGSTREG_2);
}

// ST3
void HbgOprOprST3(CHbgDasmInnerInfo& info)
{
	_HbgStrSTReg(info, HBGSTREG_3);
}

// ST4
void HbgOprOprST4(CHbgDasmInnerInfo& info)
{
	_HbgStrSTReg(info, HBGSTREG_4);
}

// ST5
void HbgOprOprST5(CHbgDasmInnerInfo& info)
{
	_HbgStrSTReg(info, HBGSTREG_5);
}

// ST6
void HbgOprOprST6(CHbgDasmInnerInfo& info)
{
	_HbgStrSTReg(info, HBGSTREG_6);
}

// ST7
void HbgOprOprST7(CHbgDasmInnerInfo& info)
{
	_HbgStrSTReg(info, HBGSTREG_7);
}

// 1
void HbgOprOpr1(CHbgDasmInnerInfo& info)
{
	HbgDasmStrCopy(info, g_HbgStr_1);
}

// Ap
void HbgOprOprAp(CHbgDasmInnerInfo& info)
{
	_HbgStrPtr16_16or32or64(info);
}

// Cd
void HbgOprOprCd(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrCReg(info, (HBGCREG)info.regop);
}

// Dd
void HbgOprOprDd(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrDReg(info, (HBGDREG)info.regop);
}

// Eb
void HbgOprOprEb(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_8bit);

	_HbgStrModRMDisp(info, HBGREGTYPE1_R8);
}

// Ed
void HbgOprOprEd(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	
	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_32bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_R32);
}

// Ep
void HbgOprOprEp(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_48bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_R32);
}

// Ev
void HbgOprOprEv(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, info.operandSize);

	HBGREGTYPE1 typeW = (info.rexPrefix & HBGREXPFX_REXW) ? HBGREGTYPE1_R64 : HBGREGTYPE1_R32;
	if (typeW == HBGREGTYPE1_R32) {
		if (info.prefix == HBGPFX_0x66)
			typeW = HBGREGTYPE1_R16;
	}
	_HbgStrModRMDisp(info, typeW);
}

// Ew
void HbgOprOprEw(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	
	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_16bit);

	_HbgStrModRMDisp(info, HBGREGTYPE1_R16);
}

// Ey
void HbgOprOprEy(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	
	if (info.mod != 0x03)
		_HbgStrPtr(info, info.operandSize);
	
	HBGREGTYPE1 typeW = (info.rexPrefix & HBGREXPFX_REXW) ? HBGREGTYPE1_R64 : HBGREGTYPE1_R32;
	_HbgStrModRMDisp(info, typeW);
}

// Fv
void HbgOprOprFv(CHbgDasmInnerInfo& /*info*/)
{
	// EFLAGS 레지스터: 처리 불필요
}

// Gb
void HbgOprOprGb(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	HBGREGTYPE1 regType = HBGREGTYPE1_R8;
	if (info.rexPrefix & HBGREXPFX_REXR)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));
	_HbgStrReg(info, regType, (HBGREGTYPE2)info.regop);
}

// Gd
void HbgOprOprGd(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	HBGREGTYPE1 regType = HBGREGTYPE1_R32;
	if (info.rexPrefix & HBGREXPFX_REXR)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));
	_HbgStrReg(info, regType, (HBGREGTYPE2)info.regop);
}

// Gv
void HbgOprOprGv(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	
	HBGREGTYPE1 regType = _HbgGetRegTypeByOperandSize(info.operandSize);
	if (info.rexPrefix & HBGREXPFX_REXR)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));

	_HbgStrReg(info, regType, (HBGREGTYPE2)info.regop);
}

// Gw
void HbgOprOprGw(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	HBGREGTYPE1 regType = HBGREGTYPE1_R16;
	if (info.rexPrefix & HBGREXPFX_REXR)
		regType = (HBGREGTYPE1)(regType + (HBGREGTYPE1_REXR64 - HBGREGTYPE1_R64));
	_HbgStrReg(info, regType, (HBGREGTYPE2)info.regop);
}

// Gy
void HbgOprOprGy(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrReg(info, HBGREGTYPE1_R32, (HBGREGTYPE2)info.regop);
}

// Gz
void HbgOprOprGz(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	
	HBGREGTYPE1 regType = _HbgGetRegTypeByOperandSize(info.operandSize);
	if (info.operandSize == HBGPTRTYPE_64bit)
		regType = HBGREGTYPE1_R32;

	_HbgStrReg(info, regType, (HBGREGTYPE2)info.regop);
}

// Ib
void HbgOprOprIb(CHbgDasmInnerInfo& info)
{
	_HbgStrImm(info, HBGPTRTYPE_8bit);
}

// Iv
void HbgOprOprIv(CHbgDasmInnerInfo& info)
{
	_HbgStrImm(info, info.operandSize);
}

// Iw
void HbgOprOprIw(CHbgDasmInnerInfo& info)
{
	_HbgStrImm(info, HBGPTRTYPE_16bit);
}

// Iz
void HbgOprOprIz(CHbgDasmInnerInfo& info)
{
	HBGPTRTYPE ptrType = info.operandSize;
	if (info.operandSize == HBGPTRTYPE_64bit)
		ptrType = HBGPTRTYPE_32bit;

	_HbgStrImm(info, ptrType);
}

// Jb
void HbgOprOprJb(CHbgDasmInnerInfo& info)
{
	_HbgStrRel(info, HBGPTRTYPE_8bit);
}

// Jz
void HbgOprOprJz(CHbgDasmInnerInfo& info)
{
	HBGPTRTYPE ptrType = info.operandSize;
	if (info.operandSize == HBGPTRTYPE_64bit)
		ptrType = HBGPTRTYPE_32bit;

	_HbgStrRel(info, ptrType);
}

// M
void HbgOprOprM(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	HBGREGTYPE1 typeW = (info.rexPrefix & HBGREXPFX_REXW) ? HBGREGTYPE1_R64 : HBGREGTYPE1_R32;
	_HbgStrModRMDisp(info, typeW, TRUE);
}

// Ma
void HbgOprOprMa(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, (info.operandSize == HBGPTRTYPE_32bit) ? HBGPTRTYPE_64bit : HBGPTRTYPE_32bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_R32);
}

// Mb
void HbgOprOprMb(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_8bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_R32);
}

// Md
void HbgOprOprMd(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_32bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_R32);
}

// Mdq
void HbgOprOprMdq(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_128bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_XMM);
}

// Mp
void HbgOprOprMp(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_48bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_R32, TRUE);
}

// Mpd
void HbgOprOprMpd(CHbgDasmInnerInfo& info)
{
	_HBGTRACE(L"Mpd", info);	// 미구현
}

// Mps
void HbgOprOprMps(CHbgDasmInnerInfo& info)
{
	_HBGTRACE(L"Mps", info);	// 미구현
}

// Mq
void HbgOprOprMq(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_64bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_R32);
}

// Ms
void HbgOprOprMs(CHbgDasmInnerInfo& info)
{
	_HBGTRACE(L"Ms", info);	// 미구현
}

// Mw
void HbgOprOprMw(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_16bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_R32);
}

// My
void HbgOprOprMy(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_32bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_R32);
}

// Nq
void HbgOprOprNq(CHbgDasmInnerInfo& info)
{
	_HBGTRACE(L"Nq", info);	// 미구현
}

// Ob
void HbgOprOprOb(CHbgDasmInnerInfo& info)
{
	_HbgStrPtr(info, HBGPTRTYPE_8bit);
	_HbgStrSReg(info, info.segOverride);
	HbgDasmStrCopy(info, g_HbgStr_Col);
	HbgDasmStrCopy(info, g_HbgStr_AddrOpen);
	_HbgStrImm(info, info.operandSize);
	HbgDasmStrCopy(info, g_HbgStr_AddrClose);
}

// Ov
void HbgOprOprOv(CHbgDasmInnerInfo& info)
{
	_HbgStrPtr(info, info.operandSize);
	_HbgStrSReg(info, info.segOverride);
	HbgDasmStrCopy(info, g_HbgStr_Col);
	HbgDasmStrCopy(info, g_HbgStr_AddrOpen);
	_HbgStrImm(info, info.operandSize);
	HbgDasmStrCopy(info, g_HbgStr_AddrClose);
}

// Pd
void HbgOprOprPd(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrReg(info, HBGREGTYPE1_MM, (HBGREGTYPE2)info.regop);
}

// Ppi
void HbgOprOprPpi(CHbgDasmInnerInfo& info)
{
	_HBGTRACE(L"Ppi", info);	// 미구현
}

// Pq
void HbgOprOprPq(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrReg(info, HBGREGTYPE1_MM, (HBGREGTYPE2)info.regop);
}

// Qd
void HbgOprOprQd(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_32bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_MM);
}

// Qpi
void HbgOprOprQpi(CHbgDasmInnerInfo& info)
{
	_HBGTRACE(L"Qpi", info);	// 미구현
}

// Qq
void HbgOprOprQq(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_64bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_MM);
}

// Rd
void HbgOprOprRd(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrReg(info, HBGREGTYPE1_R32, (HBGREGTYPE2)info.rm);
}

// Rv
void HbgOprOprRv(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrReg(info, HBGREGTYPE1_R32, (HBGREGTYPE2)info.rm);
}

// Ry
void HbgOprOprRy(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrReg(info, HBGREGTYPE1_R32, (HBGREGTYPE2)info.rm);
}

// Sw
void HbgOprOprSw(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrSReg(info, (HBGSREG)info.regop);
}

// Udq
void HbgOprOprUdq(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrReg(info, HBGREGTYPE1_XMM, (HBGREGTYPE2)info.rm);
}

// Upd
void HbgOprOprUpd(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrReg(info, HBGREGTYPE1_XMM, (HBGREGTYPE2)info.rm);
}

// Ups
void HbgOprOprUps(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrReg(info, HBGREGTYPE1_XMM, (HBGREGTYPE2)info.rm);
}

// Uq
void HbgOprOprUq(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrReg(info, HBGREGTYPE1_XMM, (HBGREGTYPE2)info.rm);
}

// Vdq
void HbgOprOprVdq(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrReg(info, HBGREGTYPE1_XMM, (HBGREGTYPE2)info.regop);
}

// Vpd
void HbgOprOprVpd(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrReg(info, HBGREGTYPE1_XMM, (HBGREGTYPE2)info.regop);
}

// Vps
void HbgOprOprVps(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrReg(info, HBGREGTYPE1_XMM, (HBGREGTYPE2)info.regop);
}

// Vsd
void HbgOprOprVsd(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrReg(info, HBGREGTYPE1_XMM, (HBGREGTYPE2)info.regop);
}

// Vss
void HbgOprOprVss(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrReg(info, HBGREGTYPE1_XMM, (HBGREGTYPE2)info.regop);
}

// Vq
void HbgOprOprVq(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrReg(info, HBGREGTYPE1_XMM, (HBGREGTYPE2)info.regop);
}

// Vy
void HbgOprOprVy(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);
	_HbgStrReg(info, HBGREGTYPE1_XMM, (HBGREGTYPE2)info.regop);
}

// Wdq
void HbgOprOprWdq(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_128bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_XMM);
}

// Wpd
void HbgOprOprWpd(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_128bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_XMM);
}

// Wps
void HbgOprOprWps(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_64bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_XMM);
}

// Wsd
void HbgOprOprWsd(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_128bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_XMM);
}

// Wss
void HbgOprOprWss(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_64bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_XMM);
}

// Wq
void HbgOprOprWq(CHbgDasmInnerInfo& info)
{
	_HbgParseModRMSIBDisp(info);

	if (info.mod != 0x03)
		_HbgStrPtr(info, HBGPTRTYPE_64bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_MM);
}

// Xb
void HbgOprOprXb(CHbgDasmInnerInfo& info)
{
	_HbgStrPtr(info, HBGPTRTYPE_8bit);
	_HbgStrSReg(info, HBGSREG_DS);
	HbgDasmStrCopy(info, g_HbgStr_Col);
	HbgDasmStrCopy(info, g_HbgStr_AddrOpen);
	_HbgStrReg(info, (info.operandSize == HBGPTRTYPE_32bit) ? HBGREGTYPE1_R32 : HBGREGTYPE1_R16, HBGREGTYPE2_6);
	HbgDasmStrCopy(info, g_HbgStr_AddrClose);
}

// Xv
void HbgOprOprXv(CHbgDasmInnerInfo& info)
{
	_HbgStrPtr(info, info.operandSize);
	_HbgStrSReg(info, HBGSREG_DS);
	HbgDasmStrCopy(info, g_HbgStr_Col);
	HbgDasmStrCopy(info, g_HbgStr_AddrOpen);
	
	HBGREGTYPE1 typeW = (info.rexPrefix & HBGREXPFX_REXW) ? HBGREGTYPE1_R64 : HBGREGTYPE1_R32;
	_HbgStrReg(info, typeW, HBGREGTYPE2_6);
	HbgDasmStrCopy(info, g_HbgStr_AddrClose);
}

// Xz
void HbgOprOprXz(CHbgDasmInnerInfo& info)
{
	_HbgStrPtr(info, info.operandSize);
	_HbgStrSReg(info, HBGSREG_DS);
	HbgDasmStrCopy(info, g_HbgStr_Col);
	HbgDasmStrCopy(info, g_HbgStr_AddrOpen);
	
	HBGREGTYPE1 regType = _HbgGetRegTypeByOperandSize(info.operandSize);
	if (info.operandSize == HBGPTRTYPE_64bit)
		regType = HBGREGTYPE1_R32;

	_HbgStrReg(info, regType, HBGREGTYPE2_6);
	HbgDasmStrCopy(info, g_HbgStr_AddrClose);
}

// Yb
void HbgOprOprYb(CHbgDasmInnerInfo& info)
{
	_HbgStrPtr(info, HBGPTRTYPE_8bit);
	_HbgStrSReg(info, HBGSREG_ES);
	HbgDasmStrCopy(info, g_HbgStr_Col);
	HbgDasmStrCopy(info, g_HbgStr_AddrOpen);
	_HbgStrReg(info, (info.operandSize == HBGPTRTYPE_32bit) ? HBGREGTYPE1_R32 : HBGREGTYPE1_R16, HBGREGTYPE2_7);
	HbgDasmStrCopy(info, g_HbgStr_AddrClose);
}

// Yv
void HbgOprOprYv(CHbgDasmInnerInfo& info)
{
	_HbgStrPtr(info, info.operandSize);
	_HbgStrSReg(info, HBGSREG_ES);
	HbgDasmStrCopy(info, g_HbgStr_Col);
	HbgDasmStrCopy(info, g_HbgStr_AddrOpen);
	
	HBGREGTYPE1 typeW = (info.rexPrefix & HBGREXPFX_REXW) ? HBGREGTYPE1_R64 : HBGREGTYPE1_R32;
	_HbgStrReg(info, typeW, HBGREGTYPE2_7);
	HbgDasmStrCopy(info, g_HbgStr_AddrClose);
}

// Yz
void HbgOprOprYz(CHbgDasmInnerInfo& info)
{
	_HbgStrPtr(info, info.operandSize);
	_HbgStrSReg(info, HBGSREG_ES);
	HbgDasmStrCopy(info, g_HbgStr_Col);
	HbgDasmStrCopy(info, g_HbgStr_AddrOpen);
	
	HBGREGTYPE1 regType = _HbgGetRegTypeByOperandSize(info.operandSize);
	if (info.operandSize == HBGPTRTYPE_64bit)
		regType = HBGREGTYPE1_R32;

	_HbgStrReg(info, regType, HBGREGTYPE2_7);
	HbgDasmStrCopy(info, g_HbgStr_AddrClose);
}

void HbgOprOprm16int(CHbgDasmInnerInfo& info)
{
	//_HbgParseModRMSIBDisp(info);		// HbgDasmEscInstr 안에서 이미 처리함
	
	_HbgStrPtr(info, HBGPTRTYPE_16bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_R32);
}

void HbgOprOprm32int(CHbgDasmInnerInfo& info)
{
	//_HbgParseModRMSIBDisp(info);		// HbgDasmEscInstr 안에서 이미 처리함
	
	_HbgStrPtr(info, HBGPTRTYPE_32bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_R32);
}

void HbgOprOprm64int(CHbgDasmInnerInfo& info)
{
	//_HbgParseModRMSIBDisp(info);		// HbgDasmEscInstr 안에서 이미 처리함
	
	_HbgStrPtr(info, HBGPTRTYPE_64bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_R32);
}

void HbgOprOprm32fp(CHbgDasmInnerInfo& info)
{
	//_HbgParseModRMSIBDisp(info);		// HbgDasmEscInstr 안에서 이미 처리함
	
	_HbgStrPtr(info, HBGPTRTYPE_32bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_R32);
}

void HbgOprOprm64fp(CHbgDasmInnerInfo& info)
{
	//_HbgParseModRMSIBDisp(info);		// HbgDasmEscInstr 안에서 이미 처리함
	
	_HbgStrPtr(info, HBGPTRTYPE_64bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_R32);
}

void HbgOprOprm80fp(CHbgDasmInnerInfo& info)
{
	//_HbgParseModRMSIBDisp(info);		// HbgDasmEscInstr 안에서 이미 처리함
	
	_HbgStrPtr(info, HBGPTRTYPE_80bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_R32);
}

void HbgOprOprm2byte(CHbgDasmInnerInfo& info)
{
	//_HbgParseModRMSIBDisp(info);		// HbgDasmEscInstr 안에서 이미 처리함
	
	_HBGTRACE(L"m2byte", info);	// 미구현
}

void HbgOprOprm1428byte(CHbgDasmInnerInfo& info)
{
	//_HbgParseModRMSIBDisp(info);		// HbgDasmEscInstr 안에서 이미 처리함
	
	_HBGTRACE(L"m1428byte", info);	// 미구현
}

void HbgOprOprm94108byte(CHbgDasmInnerInfo& info)
{
	//_HbgParseModRMSIBDisp(info);		// HbgDasmEscInstr 안에서 이미 처리함
	
	_HBGTRACE(L"m94108byte", info);	// 미구현
}

void HbgOprOprm80(CHbgDasmInnerInfo& info)
{
	//_HbgParseModRMSIBDisp(info);		// HbgDasmEscInstr 안에서 이미 처리함
	
	_HbgStrPtr(info, HBGPTRTYPE_80bit);
	_HbgStrModRMDisp(info, HBGREGTYPE1_R32);
}


HBGOPROPR g_Hbg_OperandOperationTable[] = {
	{ HBGOPR_AL,	HbgOprOprAL },
	{ HBGOPR_CL,	HbgOprOprCL },
	{ HBGOPR_DL,	HbgOprOprDL },
	{ HBGOPR_BL,	HbgOprOprBL },
	{ HBGOPR_AH,	HbgOprOprAH },
	{ HBGOPR_CH,	HbgOprOprCH },
	{ HBGOPR_DH,	HbgOprOprDH },
	{ HBGOPR_BH,	HbgOprOprBH },
	{ HBGOPR_AX,	HbgOprOprAX },
	{ HBGOPR_CX,	HbgOprOprCX },
	{ HBGOPR_DX,	HbgOprOprDX },
	{ HBGOPR_BX,	HbgOprOprBX },
	{ HBGOPR_SP,	HbgOprOprSP },
	{ HBGOPR_BP,	HbgOprOprBP },
	{ HBGOPR_SI,	HbgOprOprSI },
	{ HBGOPR_DI,	HbgOprOprDI },
	{ HBGOPR_eAX,	HbgOprOprrAX },
	{ HBGOPR_eCX,	HbgOprOprrCX },
	{ HBGOPR_eDX,	HbgOprOprrDX },
	{ HBGOPR_eBX,	HbgOprOprrBX },
	{ HBGOPR_eSP,	HbgOprOprrSP },
	{ HBGOPR_eBP,	HbgOprOprrBP },
	{ HBGOPR_eSI,	HbgOprOprrSI },
	{ HBGOPR_eDI,	HbgOprOprrDI },
	{ HBGOPR_rAX,	HbgOprOprrAX },
	{ HBGOPR_rCX,	HbgOprOprrCX },
	{ HBGOPR_rDX,	HbgOprOprrDX },
	{ HBGOPR_rBX,	HbgOprOprrBX },
	{ HBGOPR_rSP,	HbgOprOprrSP },
	{ HBGOPR_rBP,	HbgOprOprrBP },
	{ HBGOPR_rSI,	HbgOprOprrSI },
	{ HBGOPR_rDI,	HbgOprOprrDI },
	{ HBGOPR_CS,	HbgOprOprCS },
	{ HBGOPR_SS,	HbgOprOprSS },
	{ HBGOPR_DS,	HbgOprOprDS },
	{ HBGOPR_ES,	HbgOprOprES },
	{ HBGOPR_FS,	HbgOprOprFS },
	{ HBGOPR_GS,	HbgOprOprGS },
	{ HBGOPR_ST0,	HbgOprOprST0 },
	{ HBGOPR_ST1,	HbgOprOprST1 },
	{ HBGOPR_ST2,	HbgOprOprST2 },
	{ HBGOPR_ST3,	HbgOprOprST3 },
	{ HBGOPR_ST4,	HbgOprOprST4 },
	{ HBGOPR_ST5,	HbgOprOprST5 },
	{ HBGOPR_ST6,	HbgOprOprST6 },
	{ HBGOPR_ST7,	HbgOprOprST7 },
	{ HBGOPR_1,	HbgOprOpr1 },
	{ HBGOPR_Ap,	HbgOprOprAp },
	{ HBGOPR_Cd,	HbgOprOprCd },
	{ HBGOPR_Dd,	HbgOprOprDd },
	{ HBGOPR_Eb,	HbgOprOprEb },
	{ HBGOPR_Ed,	HbgOprOprEd },
	{ HBGOPR_Ep,	HbgOprOprEp },
	{ HBGOPR_Ev,	HbgOprOprEv },
	{ HBGOPR_Ew,	HbgOprOprEw },
	{ HBGOPR_Ey,	HbgOprOprEy },
	{ HBGOPR_Fv,	HbgOprOprFv },
	{ HBGOPR_Gb,	HbgOprOprGb },
	{ HBGOPR_Gd,	HbgOprOprGd },
	{ HBGOPR_Gv,	HbgOprOprGv },
	{ HBGOPR_Gw,	HbgOprOprGw },
	{ HBGOPR_Gy,	HbgOprOprGy },
	{ HBGOPR_Gz,	HbgOprOprGz },
	{ HBGOPR_Ib,	HbgOprOprIb },
	{ HBGOPR_Iv,	HbgOprOprIv },
	{ HBGOPR_Iw,	HbgOprOprIw },
	{ HBGOPR_Iz,	HbgOprOprIz },
	{ HBGOPR_Jb,	HbgOprOprJb },
	{ HBGOPR_Jz,	HbgOprOprJz },
	{ HBGOPR_M,	HbgOprOprM },
	{ HBGOPR_Ma,	HbgOprOprMa },
	{ HBGOPR_Mb,	HbgOprOprMb },
	{ HBGOPR_Md,	HbgOprOprMd },
	{ HBGOPR_Mdq,	HbgOprOprMdq },
	{ HBGOPR_Mp,	HbgOprOprMp },
	{ HBGOPR_Mpd,	HbgOprOprMpd },
	{ HBGOPR_Mps,	HbgOprOprMps },
	{ HBGOPR_Mq,	HbgOprOprMq },
	{ HBGOPR_Ms,	HbgOprOprMs },
	{ HBGOPR_Mw,	HbgOprOprMw },
	{ HBGOPR_My,	HbgOprOprMy },
	{ HBGOPR_Nq,	HbgOprOprNq },
	{ HBGOPR_Ob,	HbgOprOprOb },
	{ HBGOPR_Ov,	HbgOprOprOv },
	{ HBGOPR_Pd,	HbgOprOprPd },
	{ HBGOPR_Ppi,	HbgOprOprPpi },
	{ HBGOPR_Pq,	HbgOprOprPq },
	{ HBGOPR_Qd,	HbgOprOprQd },
	{ HBGOPR_Qpi,	HbgOprOprQpi },
	{ HBGOPR_Qq,	HbgOprOprQq },
	{ HBGOPR_Rd,	HbgOprOprRd },
	{ HBGOPR_Rv,	HbgOprOprRv },
	{ HBGOPR_Ry,	HbgOprOprRy },
	{ HBGOPR_Sw,	HbgOprOprSw },
	{ HBGOPR_Udq,	HbgOprOprUdq },
	{ HBGOPR_Upd,	HbgOprOprUpd },
	{ HBGOPR_Ups,	HbgOprOprUps },
	{ HBGOPR_Uq,	HbgOprOprUq },
	{ HBGOPR_Vdq,	HbgOprOprVdq },
	{ HBGOPR_Vpd,	HbgOprOprVpd },
	{ HBGOPR_Vps,	HbgOprOprVps },
	{ HBGOPR_Vsd,	HbgOprOprVsd },
	{ HBGOPR_Vss,	HbgOprOprVss },
	{ HBGOPR_Vq,	HbgOprOprVq },
	{ HBGOPR_Vy,	HbgOprOprVy },
	{ HBGOPR_Wdq,	HbgOprOprWdq },
	{ HBGOPR_Wpd,	HbgOprOprWpd },
	{ HBGOPR_Wps,	HbgOprOprWps },
	{ HBGOPR_Wsd,	HbgOprOprWsd },
	{ HBGOPR_Wss,	HbgOprOprWss },
	{ HBGOPR_Wq,	HbgOprOprWq },
	{ HBGOPR_Xb,	HbgOprOprXb },
	{ HBGOPR_Xv,	HbgOprOprXv },
	{ HBGOPR_Xz,	HbgOprOprXz },
	{ HBGOPR_Yb,	HbgOprOprYb },
	{ HBGOPR_Yv,	HbgOprOprYv },
	{ HBGOPR_Yz,	HbgOprOprYz },
	{ HBGOPR_m16int,	HbgOprOprm16int },
	{ HBGOPR_m32int,	HbgOprOprm32int },
	{ HBGOPR_m64int,	HbgOprOprm64int },
	{ HBGOPR_m32fp,	HbgOprOprm32fp },
	{ HBGOPR_m64fp,	HbgOprOprm64fp },
	{ HBGOPR_m80fp,	HbgOprOprm80fp },
	{ HBGOPR_m2byte,	HbgOprOprm2byte },
	{ HBGOPR_m1428byte,	HbgOprOprm1428byte },
	{ HBGOPR_m94108byte,	HbgOprOprm94108byte },
	{ HBGOPR_m80,	HbgOprOprm80 },
};
