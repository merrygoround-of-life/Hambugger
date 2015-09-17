
//////////////////////////////
// Register

enum HBGREGTYPE1 {
	HBGREGTYPE1_R8 = 0,		// r8(/r)
	HBGREGTYPE1_R16,		// r16(/r)
	HBGREGTYPE1_R32,		// r32(/r)
	HBGREGTYPE1_R64,		// r64(/r)
	HBGREGTYPE1_MM,		// mm(/r)
	HBGREGTYPE1_XMM,		// xmm(/r)
	HBGREGTYPE1_REXR8,		// REX.R8(/r)
	HBGREGTYPE1_REXR16,		// REX.R16(/r)
	HBGREGTYPE1_REXR32,		// REX.R32(/r)
	HBGREGTYPE1_REXR64,		// REX.R64(/r)
	
	HBGREGTYPE1_COUNT,		// (= 10)
};


enum HBGREGTYPE2 {
	HBGREGTYPE2_0 = 0,		// AL/AX/EAX/RAX/MM0/XMM0
	HBGREGTYPE2_1,		// CL/CX/ECX/RCX/MM1/XMM1
	HBGREGTYPE2_2,		// DL/DX/EDX/RDX/MM2/XMM2
	HBGREGTYPE2_3,		// BL/BX/EBX/RBX/MM3/XMM3
	HBGREGTYPE2_4,		// AH/SP/ESP/RSP/MM4/XMM4
	HBGREGTYPE2_5,		// CH/BP/EBP/RBP/MM5/XMM5
	HBGREGTYPE2_6,		// DH/SI/ESI/RSI/MM6/XMM6
	HBGREGTYPE2_7,		// BH/DI/EDI/RDI/MM7/XMM7

	HBGREGTYPE2_COUNT,		// (= 8)
};


enum HBGSREG {
	HBGSREG_Undef = -1,		// Undefined

	HBGSREG_ES = 0,		// ES
	HBGSREG_CS,		// CS
	HBGSREG_SS,		// SS
	HBGSREG_DS,		// DS
	HBGSREG_FS,		// FS
	HBGSREG_GS,		// GS
	HBGSREG_Reserved6,		// Reserved
	HBGSREG_Reserved7,		// Reserved
};


enum HBGCREG {
	HBGCREG_CR0 = 0,		// CR0
	HBGCREG_Reserved1,		// Reserved
	HBGCREG_CR2,		// CR2
	HBGCREG_CR3,		// CR3
	HBGCREG_CR4,		// CR4
	HBGCREG_Reserved5,		// Reserved
	HBGCREG_Reserved6,		// Reserved
	HBGCREG_Reserved7,		// Reserved
};


enum HBGDREG {
	HBGDREG_DR0 = 0,		// DR0
	HBGDREG_DR1,		// DR1
	HBGDREG_DR2,		// DR2
	HBGDREG_DR3,		// DR3
	HBGDREG_Reserved4,		// Reserved
	HBGDREG_Reserved5,		// Reserved
	HBGDREG_DR6,		// DR6
	HBGDREG_DR7,		// DR7
};


enum HBGSTREG {
	HBGSTREG_0 = 0,		// ST0
	HBGSTREG_1,		// ST1
	HBGSTREG_2,		// ST2
	HBGSTREG_3,		// ST3
	HBGSTREG_4,		// ST4
	HBGSTREG_5,		// ST5
	HBGSTREG_6,		// ST6
	HBGSTREG_7,		// ST7
};


//////////////////////////////
// operand.address size

enum HBGPTRTYPE {
	HBGPTRTYPE_8bit = 0,		// 8 bit (byte ptr)
	HBGPTRTYPE_16bit,		// 16 bit (word ptr)
	HBGPTRTYPE_32bit,		// 32 bit (dword ptr)
	HBGPTRTYPE_48bit,		// 48 bit (fword ptr)
	HBGPTRTYPE_64bit,		// 64 bit (qword ptr)
	HBGPTRTYPE_80bit,		// 80 bit (tbyte ptr)
	HBGPTRTYPE_128bit,		// 128 bit (dqword ptr)
};


//////////////////////////////
// Mnemonic

enum HBGMM {
	HBGMM_Escape = -19,		// Escape(x87 FPU)
	HBGMM_Group16 = -18,		// Group16
	HBGMM_Group15 = -17,		// Group15
	HBGMM_Group14 = -16,		// Group14
	HBGMM_Group13 = -15,		// Group13
	HBGMM_Group12 = -14,		// Group12
	HBGMM_Group11 = -13,		// Group11
	HBGMM_Group10 = -12,		// Group10
	HBGMM_Group9 = -11,		// Group9
	HBGMM_Group8 = -10,		// Group8
	HBGMM_Group7 = -9,		// Group7
	HBGMM_Group6 = -8,		// Group6
	HBGMM_Group5 = -7,		// Group5
	HBGMM_Group4 = -6,		// Group4
	HBGMM_Group3 = -5,		// Group3
	HBGMM_Group2 = -4,		// Group2
	HBGMM_Group1A = -3,		// Group1A
	HBGMM_Group1 = -2,		// Group1
	HBGMM_Undef = -1,		// Undefined

	HBGMM_AAA = 0,		// AAA
	HBGMM_AAD,		// AAD
	HBGMM_AAM,		// AAM
	HBGMM_AAS,		// AAS
	HBGMM_ADC,		// ADC
	HBGMM_ADD,		// ADD
	HBGMM_ADDPD,		// ADDPD
	HBGMM_ADDPS,		// ADDPS
	HBGMM_ADDSD,		// ADDSD
	HBGMM_ADDSS,		// ADDSS
	HBGMM_ADDSUBPD,		// ADDSUBPD
	HBGMM_ADDSUBPS,		// ADDSUBPS
	HBGMM_AESDEC,		// AESDEC
	HBGMM_AESDECLAST,		// AESDECLAST
	HBGMM_AESENC,		// AESENC
	HBGMM_AESENCLAST,		// AESENCLAST
	HBGMM_AESIMC,		// AESIMC
	HBGMM_AESKEYGENASSIST,		// AESKEYGENASSIST
	HBGMM_AND,		// AND
	HBGMM_ANDPD,		// ANDPD
	HBGMM_ANDPS,		// ANDPS
	HBGMM_ANDNPD,		// ANDNPD
	HBGMM_ANDNPS,		// ANDNPS
	HBGMM_ARPL,		// ARPL
	HBGMM_BLENDPD,		// BLENDPD
	HBGMM_BLENDPS,		// BLENDPS
	HBGMM_BLENDVPD,		// BLENDVPD
	HBGMM_BLENDVPS,		// BLENDVPS
	HBGMM_BOUND,		// BOUND
	HBGMM_BSF,		// BSF
	HBGMM_BSR,		// BSR
	HBGMM_BSWAP,		// BSWAP
	HBGMM_BT,		// BT
	HBGMM_BTC,		// BTC
	HBGMM_BTR,		// BTR
	HBGMM_BTS,		// BTS
	HBGMM_CALL,		// CALL
	HBGMM_CBW,		// CBW
	HBGMM_CWDE,		// CWDE
	HBGMM_CDQE,		// CDQE
	HBGMM_CLC,		// CLC
	HBGMM_CLD,		// CLD
	HBGMM_CLFLUSH,		// CLFLUSH
	HBGMM_CLI,		// CLI
	HBGMM_CLTS,		// CLTS
	HBGMM_CMC,		// CMC
	HBGMM_CMOVA,		// CMOVA
	HBGMM_CMOVAE,		// CMOVAE
	HBGMM_CMOVB,		// CMOVB
	HBGMM_CMOVBE,		// CMOVBE
	HBGMM_CMOVC,		// CMOVC
	HBGMM_CMOVE,		// CMOVE
	HBGMM_CMOVG,		// CMOVG
	HBGMM_CMOVGE,		// CMOVGE
	HBGMM_CMOVL,		// CMOVL
	HBGMM_CMOVLE,		// CMOVLE
	HBGMM_CMOVNA,		// CMOVNA
	HBGMM_CMOVNAE,		// CMOVNAE
	HBGMM_CMOVNB,		// CMOVNB
	HBGMM_CMOVNBE,		// CMOVNBE
	HBGMM_CMOVNC,		// CMOVNC
	HBGMM_CMOVNE,		// CMOVNE
	HBGMM_CMOVNG,		// CMOVNG
	HBGMM_CMOVNGE,		// CMOVNGE
	HBGMM_CMOVNL,		// CMOVNL
	HBGMM_CMOVNLE,		// CMOVNLE
	HBGMM_CMOVNO,		// CMOVNO
	HBGMM_CMOVNP,		// CMOVNP
	HBGMM_CMOVNS,		// CMOVNS
	HBGMM_CMOVNZ,		// CMOVNZ
	HBGMM_CMOVO,		// CMOVO
	HBGMM_CMOVP,		// CMOVP
	HBGMM_CMOVPE,		// CMOVPE
	HBGMM_CMOVPO,		// CMOVPO
	HBGMM_CMOVS,		// CMOVS
	HBGMM_CMOVZ,		// CMOVZ
	HBGMM_CMP,		// CMP
	HBGMM_CMPPD,		// CMPPD
	HBGMM_CMPPS,		// CMPPS
	HBGMM_CMPS,		// CMPS
	HBGMM_CMPSB,		// CMPSB
	HBGMM_CMPSW,		// CMPSW
	HBGMM_CMPSD,		// CMPSD
	HBGMM_CMPSQ,		// CMPSQ
	HBGMM_CMPSS,		// CMPSS
	HBGMM_CMPXCHG,		// CMPXCHG
	HBGMM_CMPXCHG8B,		// CMPXCHG8B
	HBGMM_CMPXCHG16B,		// CMPXCHG16B
	HBGMM_COMISD,		// COMISD
	HBGMM_COMISS,		// COMISS
	HBGMM_CPUID,		// CPUID
	HBGMM_CRC32,		// CRC32
	HBGMM_CVTDQ2PD,		// CVTDQ2PD
	HBGMM_CVTDQ2PS,		// CVTDQ2PS
	HBGMM_CVTPD2DQ,		// CVTPD2DQ
	HBGMM_CVTPD2PI,		// CVTPD2PI
	HBGMM_CVTPD2PS,		// CVTPD2PS
	HBGMM_CVTPI2PD,		// CVTPI2PD
	HBGMM_CVTPI2PS,		// CVTPI2PS
	HBGMM_CVTPS2DQ,		// CVTPS2DQ
	HBGMM_CVTPS2PD,		// CVTPS2PD
	HBGMM_CVTPS2PI,		// CVTPS2PI
	HBGMM_CVTSD2SI,		// CVTSD2SI
	HBGMM_CVTSD2SS,		// CVTSD2SS
	HBGMM_CVTSI2SD,		// CVTSI2SD
	HBGMM_CVTSI2SS,		// CVTSI2SS
	HBGMM_CVTSS2SD,		// CVTSS2SD
	HBGMM_CVTSS2SI,		// CVTSS2SI
	HBGMM_CVTTPD2DQ,		// CVTTPD2DQ
	HBGMM_CVTTPD2PI,		// CVTTPD2PI
	HBGMM_CVTTPS2DQ,		// CVTTPS2DQ
	HBGMM_CVTTPS2PI,		// CVTTPS2PI
	HBGMM_CVTTSD2SI,		// CVTTSD2SI
	HBGMM_CVTTSS2SI,		// CVTTSS2SI
	HBGMM_CWD,		// CWD
	HBGMM_CDQ,		// CDQ
	HBGMM_CQO,		// CQO
	HBGMM_DAA,		// DAA
	HBGMM_DAS,		// DAS
	HBGMM_DEC,		// DEC
	HBGMM_DIV,		// DIV
	HBGMM_DIVPD,		// DIVPD
	HBGMM_DIVPS,		// DIVPS
	HBGMM_DIVSD,		// DIVSD
	HBGMM_DIVSS,		// DIVSS
	HBGMM_DPPD,		// DPPD
	HBGMM_DPPS,		// DPPS
	HBGMM_EMMS,		// EMMS
	HBGMM_ENTER,		// ENTER
	HBGMM_EXTRACTPS,		// EXTRACTPS
	HBGMM_F2XM1,		// F2XM1
	HBGMM_FABS,		// FABS
	HBGMM_FADD,		// FADD
	HBGMM_FADDP,		// FADDP
	HBGMM_FIADD,		// FIADD
	HBGMM_FBLD,		// FBLD
	HBGMM_FBSTP,		// FBSTP
	HBGMM_FCHS,		// FCHS
	HBGMM_FCLEX,		// FCLEX
	HBGMM_FNCLEX,		// FNCLEX
	HBGMM_FCMOVB,		// FCMOVB
	HBGMM_FCMOVE,		// FCMOVE
	HBGMM_FCMOVBE,		// FCMOVBE
	HBGMM_FCMOVU,		// FCMOVU
	HBGMM_FCMOVNB,		// FCMOVNB
	HBGMM_FCMOVNE,		// FCMOVNE
	HBGMM_FCMOVNBE,		// FCMOVNBE
	HBGMM_FCMOVNU,		// FCMOVNU
	HBGMM_FCOM,		// FCOM
	HBGMM_FCOMP,		// FCOMP
	HBGMM_FCOMPP,		// FCOMPP
	HBGMM_FCOMI,		// FCOMI
	HBGMM_FCOMIP,		// FCOMIP
	HBGMM_FUCOMI,		// FUCOMI
	HBGMM_FUCOMIP,		// FUCOMIP
	HBGMM_FCOS,		// FCOS
	HBGMM_FDECSTP,		// FDECSTP
	HBGMM_FDIV,		// FDIV
	HBGMM_FDIVP,		// FDIVP
	HBGMM_FIDIV,		// FIDIV
	HBGMM_FDIVR,		// FDIVR
	HBGMM_FDIVRP,		// FDIVRP
	HBGMM_FIDIVR,		// FIDIVR
	HBGMM_FFREE,		// FFREE
	HBGMM_FICOM,		// FICOM
	HBGMM_FICOMP,		// FICOMP
	HBGMM_FILD,		// FILD
	HBGMM_FINCSTP,		// FINCSTP
	HBGMM_FINIT,		// FINIT
	HBGMM_FNINIT,		// FNINIT
	HBGMM_FIST,		// FIST
	HBGMM_FISTP,		// FISTP
	HBGMM_FISTTP,		// FISTTP
	HBGMM_FLD,		// FLD
	HBGMM_FLD1,		// FLD1
	HBGMM_FLDL2T,		// FLDL2T
	HBGMM_FLDL2E,		// FLDL2E
	HBGMM_FLDPI,		// FLDPI
	HBGMM_FLDLG2,		// FLDLG2
	HBGMM_FLDLN2,		// FLDLN2
	HBGMM_FLDZ,		// FLDZ
	HBGMM_FLDCW,		// FLDCW
	HBGMM_FLDENV,		// FLDENV
	HBGMM_FMUL,		// FMUL
	HBGMM_FMULP,		// FMULP
	HBGMM_FIMUL,		// FIMUL
	HBGMM_FNOP,		// FNOP
	HBGMM_FPATAN,		// FPATAN
	HBGMM_FPREM,		// FPREM
	HBGMM_FPREM1,		// FPREM1
	HBGMM_FPTAN,		// FPTAN
	HBGMM_FRNDINT,		// FRNDINT
	HBGMM_FRSTOR,		// FRSTOR
	HBGMM_FSAVE,		// FSAVE
	HBGMM_FNSAVE,		// FNSAVE
	HBGMM_FSCALE,		// FSCALE
	HBGMM_FSIN,		// FSIN
	HBGMM_FSINCOS,		// FSINCOS
	HBGMM_FSQRT,		// FSQRT
	HBGMM_FST,		// FST
	HBGMM_FSTP,		// FSTP
	HBGMM_FSTCW,		// FSTCW
	HBGMM_FNSTCW,		// FNSTCW
	HBGMM_FSTENV,		// FSTENV
	HBGMM_FNSTENV,		// FNSTENV
	HBGMM_FSTSW,		// FSTSW
	HBGMM_FNSTSW,		// FNSTSW
	HBGMM_FSUB,		// FSUB
	HBGMM_FSUBP,		// FSUBP
	HBGMM_FISUB,		// FISUB
	HBGMM_FSUBR,		// FSUBR
	HBGMM_FSUBRP,		// FSUBRP
	HBGMM_FISUBR,		// FISUBR
	HBGMM_FTST,		// FTST
	HBGMM_FUCOM,		// FUCOM
	HBGMM_FUCOMP,		// FUCOMP
	HBGMM_FUCOMPP,		// FUCOMPP
	HBGMM_FXAM,		// FXAM
	HBGMM_FXCH,		// FXCH
	HBGMM_FXRSTOR,		// FXRSTOR
	HBGMM_FXSAVE,		// FXSAVE
	HBGMM_FXTRACT,		// FXTRACT
	HBGMM_FYL2X,		// FYL2X
	HBGMM_FYL2XP1,		// FYL2XP1
	HBGMM_HADDPD,		// HADDPD
	HBGMM_HADDPS,		// HADDPS
	HBGMM_HLT,		// HLT
	HBGMM_HSUBPD,		// HSUBPD
	HBGMM_HSUBPS,		// HSUBPS
	HBGMM_IDIV,		// IDIV
	HBGMM_IMUL,		// IMUL
	HBGMM_IN,		// IN
	HBGMM_INC,		// INC
	HBGMM_INS,		// INS
	HBGMM_INSB,		// INSB
	HBGMM_INSW,		// INSW
	HBGMM_INSD,		// INSD
	HBGMM_INSERTPS,		// INSERTPS
	HBGMM_INT,		// INT
	HBGMM_INTO,		// INTO
	HBGMM_INT3,		// INT3
	HBGMM_INVD,		// INVD
	HBGMM_INVLPG,		// INVLPG
	HBGMM_IRET,		// IRET
	HBGMM_IRETD,		// IRETD
	HBGMM_JA,		// JA
	HBGMM_JAE,		// JAE
	HBGMM_JB,		// JB
	HBGMM_JBE,		// JBE
	HBGMM_JC,		// JC
	HBGMM_JCXZ,		// JCXZ
	HBGMM_JECXZ,		// JECXZ
	HBGMM_JRCXZ,		// JRCXZ
	HBGMM_JE,		// JE
	HBGMM_JG,		// JG
	HBGMM_JGE,		// JGE
	HBGMM_JL,		// JL
	HBGMM_JLE,		// JLE
	HBGMM_JNA,		// JNA
	HBGMM_JNAE,		// JNAE
	HBGMM_JNB,		// JNB
	HBGMM_JNBE,		// JNBE
	HBGMM_JNC,		// JNC
	HBGMM_JNE,		// JNE
	HBGMM_JNG,		// JNG
	HBGMM_JNGE,		// JNGE
	HBGMM_JNL,		// JNL
	HBGMM_JNLE,		// JNLE
	HBGMM_JNO,		// JNO
	HBGMM_JNP,		// JNP
	HBGMM_JNS,		// JNS
	HBGMM_JNZ,		// JNZ
	HBGMM_JO,		// JO
	HBGMM_JP,		// JP
	HBGMM_JPE,		// JPE
	HBGMM_JPO,		// JPO
	HBGMM_JS,		// JS
	HBGMM_JZ,		// JZ
	HBGMM_JMP,		// JMP
	HBGMM_LAHF,		// LAHF
	HBGMM_LAR,		// LAR
	HBGMM_LDDQU,		// LDDQU
	HBGMM_LDMXCSR,		// LDMXCSR
	HBGMM_LDS,		// LDS
	HBGMM_LES,		// LES
	HBGMM_LFS,		// LFS
	HBGMM_LGS,		// LGS
	HBGMM_LSS,		// LSS
	HBGMM_LEA,		// LEA
	HBGMM_LEAVE,		// LEAVE
	HBGMM_LFENCE,		// LFENCE
	HBGMM_LGDT,		// LGDT
	HBGMM_LIDT,		// LIDT
	HBGMM_LLDT,		// LLDT
	HBGMM_LMSW,		// LMSW
	HBGMM_LOCK,		// LOCK
	HBGMM_LODS,		// LODS
	HBGMM_LODSB,		// LODSB
	HBGMM_LODSW,		// LODSW
	HBGMM_LODSD,		// LODSD
	HBGMM_LODSQ,		// LODSQ
	HBGMM_LOOP,		// LOOP
	HBGMM_LOOPE,		// LOOPE
	HBGMM_LOOPNE,		// LOOPNE
	HBGMM_LSL,		// LSL
	HBGMM_LTR,		// LTR
	HBGMM_MASKMOVDQU,		// MASKMOVDQU
	HBGMM_MASKMOVQ,		// MASKMOVQ
	HBGMM_MAXPD,		// MAXPD
	HBGMM_MAXPS,		// MAXPS
	HBGMM_MAXSD,		// MAXSD
	HBGMM_MAXSS,		// MAXSS
	HBGMM_MFENCE,		// MFENCE
	HBGMM_MINPD,		// MINPD
	HBGMM_MINPS,		// MINPS
	HBGMM_MINSD,		// MINSD
	HBGMM_MINSS,		// MINSS
	HBGMM_MONITOR,		// MONITOR
	HBGMM_MOV,		// MOV
	HBGMM_MOVAPD,		// MOVAPD
	HBGMM_MOVAPS,		// MOVAPS
	HBGMM_MOVBE,		// MOVBE
	HBGMM_MOVD,		// MOVD
	HBGMM_MOVQ,		// MOVQ
	HBGMM_MOVDDUP,		// MOVDDUP
	HBGMM_MOVDQA,		// MOVDQA
	HBGMM_MOVDQU,		// MOVDQU
	HBGMM_MOVDQ2Q,		// MOVDQ2Q
	HBGMM_MOVHLPS,		// MOVHLPS
	HBGMM_MOVHPD,		// MOVHPD
	HBGMM_MOVHPS,		// MOVHPS
	HBGMM_MOVLHPS,		// MOVLHPS
	HBGMM_MOVLPD,		// MOVLPD
	HBGMM_MOVLPS,		// MOVLPS
	HBGMM_MOVMSKPD,		// MOVMSKPD
	HBGMM_MOVMSKPS,		// MOVMSKPS
	HBGMM_MOVNTDQA,		// MOVNTDQA
	HBGMM_MOVNTDQ,		// MOVNTDQ
	HBGMM_MOVNTI,		// MOVNTI
	HBGMM_MOVNTPD,		// MOVNTPD
	HBGMM_MOVNTPS,		// MOVNTPS
	HBGMM_MOVNTQ,		// MOVNTQ
	HBGMM_MOVQ2DQ,		// MOVQ2DQ
	HBGMM_MOVS,		// MOVS
	HBGMM_MOVSB,		// MOVSB
	HBGMM_MOVSW,		// MOVSW
	HBGMM_MOVSD,		// MOVSD
	HBGMM_MOVSQ,		// MOVSQ
	HBGMM_MOVSHDUP,		// MOVSHDUP
	HBGMM_MOVSLDUP,		// MOVSLDUP
	HBGMM_MOVSS,		// MOVSS
	HBGMM_MOVSX,		// MOVSX
	HBGMM_MOVSXD,		// MOVSXD
	HBGMM_MOVUPD,		// MOVUPD
	HBGMM_MOVUPS,		// MOVUPS
	HBGMM_MOVZX,		// MOVZX
	HBGMM_MPSADBW,		// MPSADBW
	HBGMM_MUL,		// MUL
	HBGMM_MULPD,		// MULPD
	HBGMM_MULPS,		// MULPS
	HBGMM_MULSD,		// MULSD
	HBGMM_MULSS,		// MULSS
	HBGMM_MWAIT,		// MWAIT
	HBGMM_NEG,		// NEG
	HBGMM_NOP,		// NOP
	HBGMM_NOT,		// NOT
	HBGMM_OR,		// OR
	HBGMM_ORPD,		// ORPD
	HBGMM_ORPS,		// ORPS
	HBGMM_OUT,		// OUT
	HBGMM_OUTS,		// OUTS
	HBGMM_OUTSB,		// OUTSB
	HBGMM_OUTSW,		// OUTSW
	HBGMM_OUTSD,		// OUTSD
	HBGMM_PABSB,		// PABSB
	HBGMM_PABSW,		// PABSW
	HBGMM_PABSD ,		// PABSD 
	HBGMM_PACKSSWB,		// PACKSSWB
	HBGMM_PACKSSDW,		// PACKSSDW
	HBGMM_PACKUSDW,		// PACKUSDW
	HBGMM_PACKUSWB,		// PACKUSWB
	HBGMM_PADDB,		// PADDB
	HBGMM_PADDW,		// PADDW
	HBGMM_PADDD,		// PADDD
	HBGMM_PADDQ,		// PADDQ
	HBGMM_PADDSB,		// PADDSB
	HBGMM_PADDSW,		// PADDSW
	HBGMM_PADDUSB,		// PADDUSB
	HBGMM_PADDUSW,		// PADDUSW
	HBGMM_PALIGNR,		// PALIGNR
	HBGMM_PAND,		// PAND
	HBGMM_PANDN,		// PANDN
	HBGMM_PAUSE,		// PAUSE
	HBGMM_PAVGB,		// PAVGB
	HBGMM_PAVGW,		// PAVGW
	HBGMM_PBLENDVB,		// PBLENDVB
	HBGMM_PBLENDW,		// PBLENDW
	HBGMM_PCLMULQDQ,		// PCLMULQDQ
	HBGMM_PCMPEQB,		// PCMPEQB
	HBGMM_PCMPEQW,		// PCMPEQW
	HBGMM_PCMPEQD,		// PCMPEQD
	HBGMM_PCMPEQQ,		// PCMPEQQ
	HBGMM_PCMPESTRI,		// PCMPESTRI
	HBGMM_PCMPESTRM,		// PCMPESTRM
	HBGMM_PCMPGTB,		// PCMPGTB
	HBGMM_PCMPGTW,		// PCMPGTW
	HBGMM_PCMPGTD,		// PCMPGTD
	HBGMM_PCMPGTQ,		// PCMPGTQ
	HBGMM_PCMPISTRI,		// PCMPISTRI
	HBGMM_PCMPISTRM,		// PCMPISTRM
	HBGMM_PEXTRB,		// PEXTRB
	HBGMM_PEXTRD,		// PEXTRD
	HBGMM_PEXTRQ,		// PEXTRQ
	HBGMM_PEXTRW,		// PEXTRW
	HBGMM_PHADDW,		// PHADDW
	HBGMM_PHADDD,		// PHADDD
	HBGMM_PHADDSW,		// PHADDSW
	HBGMM_PHMINPOSUW,		// PHMINPOSUW
	HBGMM_PHSUBW,		// PHSUBW
	HBGMM_PHSUBD,		// PHSUBD
	HBGMM_PHSUBSW,		// PHSUBSW
	HBGMM_PINSRB,		// PINSRB
	HBGMM_PINSRD,		// PINSRD
	HBGMM_PINSRQ,		// PINSRQ
	HBGMM_PINSRW,		// PINSRW
	HBGMM_PMADDUBSW,		// PMADDUBSW
	HBGMM_PMADDWD,		// PMADDWD
	HBGMM_PMAXSB,		// PMAXSB
	HBGMM_PMAXSD,		// PMAXSD
	HBGMM_PMAXSW,		// PMAXSW
	HBGMM_PMAXUB,		// PMAXUB
	HBGMM_PMAXUD,		// PMAXUD
	HBGMM_PMAXUW,		// PMAXUW
	HBGMM_PMINSB,		// PMINSB
	HBGMM_PMINSD,		// PMINSD
	HBGMM_PMINSW,		// PMINSW
	HBGMM_PMINUB,		// PMINUB
	HBGMM_PMINUD,		// PMINUD
	HBGMM_PMINUW,		// PMINUW
	HBGMM_PMOVMSKB,		// PMOVMSKB
	HBGMM_PMOVSXBW,		// PMOVSXBW
	HBGMM_PMOVSXBD,		// PMOVSXBD
	HBGMM_PMOVSXBQ,		// PMOVSXBQ
	HBGMM_PMOVSXWD,		// PMOVSXWD
	HBGMM_PMOVSXWQ,		// PMOVSXWQ
	HBGMM_PMOVSXDQ,		// PMOVSXDQ
	HBGMM_PMOVZXBW,		// PMOVZXBW
	HBGMM_PMOVZXBD,		// PMOVZXBD
	HBGMM_PMOVZXBQ,		// PMOVZXBQ
	HBGMM_PMOVZXWD,		// PMOVZXWD
	HBGMM_PMOVZXWQ,		// PMOVZXWQ
	HBGMM_PMOVZXDQ,		// PMOVZXDQ
	HBGMM_PMULDQ,		// PMULDQ
	HBGMM_PMULHRSW,		// PMULHRSW
	HBGMM_PMULHUW,		// PMULHUW
	HBGMM_PMULHW,		// PMULHW
	HBGMM_PMULLD,		// PMULLD
	HBGMM_PMULLW,		// PMULLW
	HBGMM_PMULUDQ,		// PMULUDQ
	HBGMM_POP,		// POP
	HBGMM_POPA,		// POPA
	HBGMM_POPAD,		// POPAD
	HBGMM_POPCNT,		// POPCNT
	HBGMM_POPF,		// POPF
	HBGMM_POPFD,		// POPFD
	HBGMM_POPFQ,		// POPFQ
	HBGMM_POR,		// POR
	HBGMM_PREFETCH0,		// PREFETCH0
	HBGMM_PREFETCH1,		// PREFETCH1
	HBGMM_PREFETCH2,		// PREFETCH2
	HBGMM_PREFETCHNTA,		// PREFETCHNTA
	HBGMM_PSADBW,		// PSADBW
	HBGMM_PSHUFB,		// PSHUFB
	HBGMM_PSHUFD,		// PSHUFD
	HBGMM_PSHUFHW,		// PSHUFHW
	HBGMM_PSHUFLW,		// PSHUFLW
	HBGMM_PSHUFW,		// PSHUFW
	HBGMM_PSIGNB,		// PSIGNB
	HBGMM_PSIGNW,		// PSIGNW
	HBGMM_PSIGND,		// PSIGND
	HBGMM_PSLLDQ,		// PSLLDQ
	HBGMM_PSLLW,		// PSLLW
	HBGMM_PSLLD,		// PSLLD
	HBGMM_PSLLQ,		// PSLLQ
	HBGMM_PSRAW,		// PSRAW
	HBGMM_PSRAD,		// PSRAD
	HBGMM_PSRLDQ,		// PSRLDQ
	HBGMM_PSRLW,		// PSRLW
	HBGMM_PSRLD,		// PSRLD
	HBGMM_PSRLQ,		// PSRLQ
	HBGMM_PSUBB,		// PSUBB
	HBGMM_PSUBW,		// PSUBW
	HBGMM_PSUBD,		// PSUBD
	HBGMM_PSUBQ,		// PSUBQ
	HBGMM_PSUBSB,		// PSUBSB
	HBGMM_PSUBSW,		// PSUBSW
	HBGMM_PSUBUSB,		// PSUBUSB
	HBGMM_PSUBUSW,		// PSUBUSW
	HBGMM_PTEST,		// PTEST
	HBGMM_PUNPCKHBW,		// PUNPCKHBW
	HBGMM_PUNPCKHWD,		// PUNPCKHWD
	HBGMM_PUNPCKHDQ,		// PUNPCKHDQ
	HBGMM_PUNPCKHQDQ,		// PUNPCKHQDQ
	HBGMM_PUNPCKLBW,		// PUNPCKLBW
	HBGMM_PUNPCKLWD,		// PUNPCKLWD
	HBGMM_PUNPCKLDQ,		// PUNPCKLDQ
	HBGMM_PUNPCKLQDQ,		// PUNPCKLQDQ
	HBGMM_PUSH,		// PUSH
	HBGMM_PUSHA,		// PUSHA
	HBGMM_PUSHAD,		// PUSHAD
	HBGMM_PUSHF,		// PUSHF
	HBGMM_PUSHFD,		// PUSHFD
	HBGMM_PXOR,		// PXOR
	HBGMM_RCL,		// RCL
	HBGMM_RCR,		// RCR
	HBGMM_ROL,		// ROL
	HBGMM_ROR,		// ROR
	HBGMM_RCPPS,		// RCPPS
	HBGMM_RCPSS,		// RCPSS
	HBGMM_RDMSR,		// RDMSR
	HBGMM_RDPMC,		// RDPMC
	HBGMM_RDTSC,		// RDTSC
	HBGMM_RDTSCP,		// RDTSCP
	HBGMM_REP,		// REP
	HBGMM_REPE,		// REPE
	HBGMM_REPZ,		// REPZ
	HBGMM_REPNE,		// REPNE
	HBGMM_REPNZ,		// REPNZ
	HBGMM_RET,		// RET
	HBGMM_ROUNDPD,		// ROUNDPD
	HBGMM_ROUNDPS,		// ROUNDPS
	HBGMM_ROUNDSD,		// ROUNDSD
	HBGMM_ROUNDSS,		// ROUNDSS
	HBGMM_RSM,		// RSM
	HBGMM_RSQRTPS,		// RSQRTPS
	HBGMM_RSQRTSS,		// RSQRTSS
	HBGMM_SAHF,		// SAHF
	HBGMM_SAL,		// SAL
	HBGMM_SAR,		// SAR
	HBGMM_SHL,		// SHL
	HBGMM_SHR,		// SHR
	HBGMM_SBB,		// SBB
	HBGMM_SCAS,		// SCAS
	HBGMM_SCASB,		// SCASB
	HBGMM_SCASW,		// SCASW
	HBGMM_SCASD,		// SCASD
	HBGMM_SETA,		// SETA
	HBGMM_SETAE,		// SETAE
	HBGMM_SETB,		// SETB
	HBGMM_SETBE,		// SETBE
	HBGMM_SETC,		// SETC
	HBGMM_SETE,		// SETE
	HBGMM_SETG,		// SETG
	HBGMM_SETGE,		// SETGE
	HBGMM_SETL,		// SETL
	HBGMM_SETLE,		// SETLE
	HBGMM_SETNA,		// SETNA
	HBGMM_SETNAE,		// SETNAE
	HBGMM_SETNB,		// SETNB
	HBGMM_SETNBE,		// SETNBE
	HBGMM_SETNC,		// SETNC
	HBGMM_SETNE,		// SETNE
	HBGMM_SETNG,		// SETNG
	HBGMM_SETNGE,		// SETNGE
	HBGMM_SETNL,		// SETNL
	HBGMM_SETNLE,		// SETNLE
	HBGMM_SETNO,		// SETNO
	HBGMM_SETNP,		// SETNP
	HBGMM_SETNS,		// SETNS
	HBGMM_SETNZ,		// SETNZ
	HBGMM_SETO,		// SETO
	HBGMM_SETP,		// SETP
	HBGMM_SETPE,		// SETPE
	HBGMM_SETPO,		// SETPO
	HBGMM_SETS,		// SETS
	HBGMM_SETZ,		// SETZ
	HBGMM_SFENCE,		// SFENCE
	HBGMM_SGDT,		// SGDT
	HBGMM_SHLD,		// SHLD
	HBGMM_SHRD,		// SHRD
	HBGMM_SHUFPD,		// SHUFPD
	HBGMM_SHUFPS,		// SHUFPS
	HBGMM_SIDT,		// SIDT
	HBGMM_SLDT,		// SLDT
	HBGMM_SMSW,		// SMSW
	HBGMM_SQRTPS,		// SQRTPS
	HBGMM_SQRTSD,		// SQRTSD
	HBGMM_SQRTSS,		// SQRTSS
	HBGMM_STC,		// STC
	HBGMM_STD,		// STD
	HBGMM_STI,		// STI
	HBGMM_STMXCSR,		// STMXCSR
	HBGMM_STOS,		// STOS
	HBGMM_STOSB,		// STOSB
	HBGMM_STOSW,		// STOSW
	HBGMM_STOSD,		// STOSD
	HBGMM_STOSQ,		// STOSQ
	HBGMM_STR,		// STR
	HBGMM_SUB,		// SUB
	HBGMM_SUBPD,		// SUBPD
	HBGMM_SUBPS,		// SUBPS
	HBGMM_SUBSD,		// SUBSD
	HBGMM_SUBSS,		// SUBSS
	HBGMM_SWAPGS,		// SWAPGS
	HBGMM_SYSCALL,		// SYSCALL
	HBGMM_SYSENTER,		// SYSENTER
	HBGMM_SYSEXIT,		// SYSEXIT
	HBGMM_SYSRET,		// SYSRET
	HBGMM_TEST,		// TEST
	HBGMM_UCOMISD,		// UCOMISD
	HBGMM_UCOMISS,		// UCOMISS
	HBGMM_UD2,		// UD2
	HBGMM_UNPCKHPD,		// UNPCKHPD
	HBGMM_UNPCKHPS,		// UNPCKHPS
	HBGMM_UNPCKLPD,		// UNPCKLPD
	HBGMM_UNPCKLPS,		// UNPCKLPS
	HBGMM_VERR,		// VERR
	HBGMM_VERW,		// VERW
	HBGMM_WAIT,		// WAIT
	HBGMM_FWAIT,		// FWAIT
	HBGMM_WBINVD,		// WBINVD
	HBGMM_WRMSR,		// WRMSR
	HBGMM_XADD,		// XADD
	HBGMM_XCHG,		// XCHG
	HBGMM_XGETBV,		// XGETBV
	HBGMM_XLAT,		// XLAT
	HBGMM_XLATB,		// XLATB
	HBGMM_XOR,		// XOR
	HBGMM_XORPD,		// XORPD
	HBGMM_XORPS,		// XORPS
	HBGMM_XRSTOR,		// XRSTOR
	HBGMM_XSAVE,		// XSAVE
	HBGMM_XSETBV,		// XSETBV
	HBGMM_INVEPT,		// INVEPT
	HBGMM_INVVPID,		// INVVPID
	HBGMM_VMCALL,		// VMCALL
	HBGMM_VMCLEAR,		// VMCLEAR
	HBGMM_VMLAUNCH,		// VMLAUNCH
	HBGMM_VMRESUME,		// VMRESUME
	HBGMM_VMPTRLD,		// VMPTRLD
	HBGMM_VMPTRST,		// VMPTRST
	HBGMM_VMREAD,		// VMREAD
	HBGMM_VMWRITE,		// VMWRITE
	HBGMM_VMXOFF,		// VMXOFF
	HBGMM_VMXON,		// VMXON
};


//////////////////////////////
// Prefix

enum HBGPFX {
	HBGPFX_None = 0,		// Not exist
	HBGPFX_0x66,		// 0x66
	HBGPFX_0xF3,		// 0xF3
	HBGPFX_0xF2,		// 0xF2
	
	HBGPFX_COUNT,		// (= 4)
};


//////////////////////////////
// Operand

enum HBGOPRIDX {
	HBGOPRIDX_1ST = 0,		// 1st operand
	HBGOPRIDX_2ND,		// 2nd operand
	HBGOPRIDX_3RD,		// 3rd operand
	
	HBGOPRIDX_COUNT,		// (= 3)
};


enum HBGOPR {
	HBGOPR_Undef = -1,		// Undefined

	HBGOPR_AL = 0,		// AL
	HBGOPR_CL,		// CL
	HBGOPR_DL,		// DL
	HBGOPR_BL,		// BL
	HBGOPR_AH,		// AH
	HBGOPR_CH,		// CH
	HBGOPR_DH,		// DH
	HBGOPR_BH,		// BH
	HBGOPR_AX,		// AX
	HBGOPR_CX,		// CX
	HBGOPR_DX,		// DX
	HBGOPR_BX,		// BX
	HBGOPR_SP,		// SP
	HBGOPR_BP,		// BP
	HBGOPR_SI,		// SI
	HBGOPR_DI,		// DI
	HBGOPR_eAX,		// eAX
	HBGOPR_eCX,		// eCX
	HBGOPR_eDX,		// eDX
	HBGOPR_eBX,		// eBX
	HBGOPR_eSP,		// eSP
	HBGOPR_eBP,		// eBP
	HBGOPR_eSI,		// eSI
	HBGOPR_eDI,		// eDI
	HBGOPR_rAX,		// rAX
	HBGOPR_rCX,		// rCX
	HBGOPR_rDX,		// rDX
	HBGOPR_rBX,		// rBX
	HBGOPR_rSP,		// rSP
	HBGOPR_rBP,		// rBP
	HBGOPR_rSI,		// rSI
	HBGOPR_rDI,		// rDI
	HBGOPR_CS,		// CS
	HBGOPR_SS,		// SS
	HBGOPR_DS,		// DS
	HBGOPR_ES,		// ES
	HBGOPR_FS,		// FS
	HBGOPR_GS,		// GS
	HBGOPR_ST0,		// ST0
	HBGOPR_ST1,		// ST1
	HBGOPR_ST2,		// ST2
	HBGOPR_ST3,		// ST3
	HBGOPR_ST4,		// ST4
	HBGOPR_ST5,		// ST5
	HBGOPR_ST6,		// ST6
	HBGOPR_ST7,		// ST7
	HBGOPR_1,		// 1
	HBGOPR_Ap,		// Ap
	HBGOPR_Cd,		// Cd
	HBGOPR_Dd,		// Dd
	HBGOPR_Eb,		// Eb
	HBGOPR_Ed,		// Ed
	HBGOPR_Ep,		// Ep
	HBGOPR_Ev,		// Ev
	HBGOPR_Ew,		// Ew
	HBGOPR_Ey,		// Ey
	HBGOPR_Fv,		// Fv
	HBGOPR_Gb,		// Gb
	HBGOPR_Gd,		// Gd
	HBGOPR_Gv,		// Gv
	HBGOPR_Gw,		// Gw
	HBGOPR_Gy,		// Gy
	HBGOPR_Gz,		// Gz
	HBGOPR_Ib,		// Ib
	HBGOPR_Iv,		// Iv
	HBGOPR_Iw,		// Iw
	HBGOPR_Iz,		// Iz
	HBGOPR_Jb,		// Jb
	HBGOPR_Jz,		// Jz
	HBGOPR_M,		// M
	HBGOPR_Ma,		// Ma
	HBGOPR_Mb,		// Mb
	HBGOPR_Md,		// Md
	HBGOPR_Mdq,		// Mdq
	HBGOPR_Mp,		// Mp
	HBGOPR_Mpd,		// Mpd
	HBGOPR_Mps,		// Mps
	HBGOPR_Mq,		// Mq
	HBGOPR_Ms,		// Ms
	HBGOPR_Mw,		// Mw
	HBGOPR_My,		// My
	HBGOPR_Nq,		// Nq
	HBGOPR_Ob,		// Ob
	HBGOPR_Ov,		// Ov
	HBGOPR_Pd,		// Pd
	HBGOPR_Ppi,		// Ppi
	HBGOPR_Pq,		// Pq
	HBGOPR_Qd,		// Qd
	HBGOPR_Qpi,		// Qpi
	HBGOPR_Qq,		// Qq
	HBGOPR_Rd,		// Rd
	HBGOPR_Rv,		// Rv
	HBGOPR_Ry,		// Ry
	HBGOPR_Sw,		// Sw
	HBGOPR_Udq,		// Udq
	HBGOPR_Upd,		// Upd
	HBGOPR_Ups,		// Ups
	HBGOPR_Uq,		// Uq
	HBGOPR_Vdq,		// Vdq
	HBGOPR_Vpd,		// Vpd
	HBGOPR_Vps,		// Vps
	HBGOPR_Vsd,		// Vsd
	HBGOPR_Vss,		// Vss
	HBGOPR_Vq,		// Vq
	HBGOPR_Vy,		// Vy
	HBGOPR_Wdq,		// Wdq
	HBGOPR_Wpd,		// Wpd
	HBGOPR_Wps,		// Wps
	HBGOPR_Wsd,		// Wsd
	HBGOPR_Wss,		// Wss
	HBGOPR_Wq,		// Wq
	HBGOPR_Xb,		// Xb
	HBGOPR_Xv,		// Xv
	HBGOPR_Xz,		// Xz
	HBGOPR_Yb,		// Yb
	HBGOPR_Yv,		// Yv
	HBGOPR_Yz,		// Yz
	HBGOPR_m16int,		// word integer
	HBGOPR_m32int,		// dword integer
	HBGOPR_m64int,		// qword integer
	HBGOPR_m32fp,		// single real
	HBGOPR_m64fp,		// double real
	HBGOPR_m80fp,		// extended real
	HBGOPR_m2byte,	// 2 bytes
	HBGOPR_m1428byte,	// 14/28 bytes
	HBGOPR_m94108byte,	// 94/108 bytes
	HBGOPR_m80,			// packedBCD
};