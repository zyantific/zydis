unit Zydis.InstructionEditor;

interface

uses
  System.Classes, System.Generics.Collections, SynCrossPlatformJSON;

type
  TInstructionEditor = class;
  TInstructionDefinition = class;
  TDefinitionContainer = class;

  TExtInstructionMode = (
    imNeutral,
    imRequire64BitMode,
    imExclude64BitMode
  );

  TExtMandatoryPrefix = (
    mpNone,
    mpPrefix66,
    mpPrefixF3,
    mpPrefixF2
  );

  TExtModrmMod = (
    mdNeutral,
    mdMemory,
    mdRegister
  );

  TExtModrmReg = (
    rgNeutral,
    rg0,
    rg1,
    rg2,
    rg3,
    rg4,
    rg5,
    rg6,
    rg7
  );

  TExtModrmRm = (
    rmNeutral,
    rm0,
    rm1,
    rm2,
    rm3,
    rm4,
    rm5,
    rm6,
    rm7
  );

  TExtOperandSize = (
    osNeutral,
    os16Bit,
    os32Bit
  );

  TExtAddressSize = (
    asNeutral,
    as16Bit,
    as32Bit,
    as64Bit
  );

  TExtBitFilter = (
    bfRexW,
    bfVexL,
    bfEvexL2,
    bfEvexB
  );

  TExtBitFilters = set of TExtBitFilter;

  TOpcodeExtensions = class(TPersistent)
  strict private
    FDefinition: TInstructionDefinition;
  strict private
    FMode: TExtInstructionMode;
    FMandatoryPrefix: TExtMandatoryPrefix;
    FModrmMod: TExtModrmMod;
    FModrmReg: TExtModrmReg;
    FModrmRm: TExtModrmRm;
    FOperandSize: TExtOperandSize;
    FAddressSize: TExtAddressSize;
    FBitFilters: TExtBitFilters;
  strict private
    procedure SetMode(const Value: TExtInstructionMode); inline;
    procedure SetMandatoryPrefix(const Value: TExtMandatoryPrefix); inline;
    procedure SetModrmMod(const Value: TExtModrmMod); inline;
    procedure SetModrmReg(const Value: TExtModrmReg); inline;
    procedure SetModrmRm(const Value: TExtModrmRm); inline;
    procedure SetOperandSize(const Value: TExtOperandSize); inline;
    procedure SetAddressSize(const Value: TExtAddressSize); inline;
    procedure SetBitFilters(const Value: TExtBitFilters); inline;
  private
    procedure Changed; inline;
  private
    procedure LoadFromJSON(JSON: PJSONVariantData; const FieldName: String);
    procedure SaveToJSON(JSON: PJSONVariantData; const FieldName: String);
    procedure SetPrefix(const Value: TExtMandatoryPrefix);
  protected
    procedure AssignTo(Dest: TPersistent); override;
  protected
    constructor Create(Definition: TInstructionDefinition);
  public
    function Equals(const Value: TOpcodeExtensions): Boolean; reintroduce;
  published
    property Mode: TExtInstructionMode read FMode write SetMode default imNeutral;
    property MandatoryPrefix: TExtMandatoryPrefix read FMandatoryPrefix write
      SetMandatoryPrefix default mpNone;
    property ModrmMod: TExtModrmMod read FModrmMod write SetModrmMod default mdNeutral;
    property ModrmReg: TExtModrmReg read FModrmReg write SetModrmReg default rgNeutral;
    property ModrmRm: TExtModrmRm read FModrmRm write SetModrmRm default rmNeutral;
    property OperandSize: TExtOperandSize read FOperandSize write SetOperandSize default osNeutral;
    property AddressSize: TExtAddressSize read FAddressSize write SetAddressSize default asNeutral;
    property BitFilters: TExtBitFilters read FBitFilters write SetBitFilters default [];
  end;

  TCPUIDFeatureFlag = (
    cf3DNOW,
    cfADX,
    cfAESNI,
    cfAVX,
    cfAVX2,
    cfAVX512BW,
    cfAVX512CD,
    cfAVX512DQ,
    cfAVX512ER,
    cfAVX512F,
    cfAVX512PF,
    cfAVX512VL,
    cfBMI1,
    cfBMI2,
    cfCMOV,
    cfCMPXCHG16B,
    cfF16C,
    cfFMA,
    cfFMA4,
    cfFSGSBASE,
    cfHLE,
    cfLZCNT,
    cfMMX,
    cfMOVBE,
    cfMPX,
    cfMWAITX,
    cfPCLMUL,
    cfPOPCNT,
    cfPREFETCHW,
    cfRDRAND,
    cfRDSEED,
    cfRTM,
    cfSHA,
    cfSSE1,
    cfSSE2,
    cfSSE3,
    cfSSE41,
    cfSSE42,
    cfSSE4A,
    cfSSSE3,
    cfTBM,
    cfTSX,
    cfXOP,
    cfFXSR,
    cfLAHFSAHF,
    cfXSAVE,
    cfXSAVES,
    cfXSAVEC,
    cfXSAVEOPT,
    cfMFENCE,
    cfVBMI,
    cfIFMA,
    cfVMX,
    cfSMX,
    cfOSPKE
  );

  TCPUIDFeatureFlagSet = set of TCPUIDFeatureFlag;

  TCPUIDFeatureFlags = class(TPersistent)
  strict private
    FDefinition: TInstructionDefinition;
    FFeatureFlags: TCPUIDFeatureFlagSet;
  strict private
    procedure SetFeatureFlags(const Value: TCPUIDFeatureFlagSet); inline;
  strict private
    procedure Changed; inline;
  private
    procedure LoadFromJSON(JSON: PJSONVariantData; const FieldName: String);
    procedure SaveToJSON(JSON: PJSONVariantData; const FieldName: String);
  protected
    procedure AssignTo(Dest: TPersistent); override;
  protected
    constructor Create(Definition: TInstructionDefinition);
  public
    function Equals(const Value: TCPUIDFeatureFlags): Boolean; reintroduce;
  public
    property FeatureFlags: TCPUIDFeatureFlagSet read FFeatureFlags write SetFeatureFlags;
  end;

  TX86Register = (
    regNone,
    // General purpose registers 64-bit
    regRAX,    regRCX,    regRDX,   regRBX,    regRSP,     regRBP,       regRSI,   regRDI,
    regR8,     regR9,     regR10,   regR11,    regR12,     regR13,       regR14,   regR15,
    // General purpose registers 32-bit
    regEAX,    regECX,    regEDX,   regEBX,    regESP,     regEBP,       regESI,   regEDI,
    regR8D,    regr9D,    regR10D,  regR11D,   regR12D,    regR13D,      regR14D,  regR15D,
    // General purpose registers 16-bit
    regAX,     regCX,     regDX,    regBX,     regSP,      regBP,        regSI,    regDI,
    regR8W,    regR9W,    regR10W,  regR11W,   regR12W,    regR13W,      regR14W,  regR15W,
    // General purpose registers  8-bit
    regAL,     regCL,     regDL,    regBL,     regAH,      regCH,        regDH,    regBH,
    regSPL,    regBPL,    regSIL,   regDIL,
    regR8B,    regR9B,    regR10B,  regR11B,   regR12B,    regR13B,      regR14B,  regR15B,
    // Floating point legacy registers
    regST0,    regST1,    regST2,   regST3,    regST4,     regST5,       regST6,   regST7,
    // Floating point multimedia registers
    regMM0,    regMM1,    regMM2,   regMM3,    regMM4,     regMM5,       regMM6,   regMM7,
    // Floating point vector registers 512-bit
    regZMM0,   regZMM1,   regZMM2,  regZMM3,   regZMM4,    regZMM5,      regZMM6,  regZMM7,
    regZMM8,   regZMM9,   regZMM10, regZMM11,  regZMM12,   regZMM13,     regZMM14, regZMM15,
    regZMM16,  regZMM17,  regZMM18, regZMM19,  regZMM20,   regZMM21,     regZMM22, regZMM23,
    regZMM24,  regZMM25,  regZMM26, regZMM27,  regZMM28,   regZMM29,     regZMM30, regZMM31,
    // Floating point vector registers 256-bit
    regYMM0,   regYMM1,   regYMM2,  regYMM3,   regYMM4,    regYMM5,      regYMM6,  regYMM7,
    regYMM8,   regYMM9,   regYMM10, regYMM11,  regYMM12,   regYMM13,     regYMM14, regYMM15,
    regYMM16,  regYMM17,  regYMM18, regYMM19,  regYMM20,   regYMM21,     regYMM22, regYMM23,
    regYMM24,  regYMM25,  regYMM26, regYMM27,  regYMM28,   regYMM29,     regYMM30, regYMM31,
    // Floating point vector registers 128-bit
    regXMM0,   regXMM1,   regXMM2,  regXMM3,   regXMM4,    regXMM5,      regXMM6,  regXMM7,
    regXMM8,   regXMM9,   regXMM10, regXMM11,  regXMM12,   regXMM13,     regXMM14, regXMM15,
    regXMM16,  regXMM17,  regXMM18, regXMM19,  regXMM20,   regXMM21,     regXMM22, regXMM23,
    regXMM24,  regXMM25,  regXMM26, regXMM27,  regXMM28,   regXMM29,     regXMM30, regXMM31,
    // Special registers
    regRFLAGS, regEFLAGS, regFLAGS, regRIP,    regEIP,     regIP,        regMXCSR, regPKRU,
    regXCR0,
    // Segment registers
    regES,     regCS,     regSS,    regDS,     regGS,      regFS,
    // Table registers
    regGDTR,   regLDTR,   regIDTR,  regTR,
    // Test registers
    regTR0,    regTR1,    regTR2,   regTR3,    regTR4,     regTR5,       regTR6,   regTR7,
    // Control registers
    regCR0,    regCR1,    regCR2,   regCR3,    regCR4,     regCR5,       regCR6,   regCR7,
    regCR8,    regCR9,    regCR10,  regCR11,   regCR12,    regCR13,      regCR14,  regCR15,
    // Debug registers
    regDR0,    regDR1,    regDR2,   regDR3,    regDR4,     regDR5,       regDR6,   regDR7,
    regDR8,    regDR9,    regDR10,  regDR11,   regDR12,    regDR13,      regDR14,  regDR15,
    // Mask registers
    regK0,     regK1,     regK2,    regK3,     regK4,      regK5,        regK6,    regK7,
    // Bounds registers
    regBND0,   regBND1,   regBND2,  regBND3,   regBNDCFG,  regBNDSTATUS
  );

  TX86RegisterSet = set of TX86Register;

  TX86Registers = class(TPersistent)
  strict private
    FDefinition: TInstructionDefinition;
    FRegisters: TX86RegisterSet;
  strict private
    procedure SetRegisters(const Value: TX86RegisterSet); inline;
  strict private
    procedure Changed; inline;
  private
    procedure LoadFromJSON(JSON: PJSONVariantData; const FieldName: String);
    procedure SaveToJSON(JSON: PJSONVariantData; const FieldName: String);
  protected
    procedure AssignTo(Dest: TPersistent); override;
  protected
    constructor Create(Definition: TInstructionDefinition);
  public
    function Equals(const Value: TX86Registers): Boolean; reintroduce;
  public
    property Registers: TX86RegisterSet read FRegisters write SetRegisters;
  end;

  TX86FlagBehavior = (
    fvTested,
    fvModified,
    fvReset,
    fvSet,
    fvUndefined
  );
  TX86FlagBehaviorSet = set of TX86FlagBehavior;

  TX86Flags = class(TPersistent)
  strict private
    type PX86FlagBehaviorSet = ^TX86FlagBehaviorSet;
  strict private
    FDefinition: TInstructionDefinition;
  strict private
    FFlags: array[0..16] of TX86FlagBehaviorSet;
  strict private
    function GetValue(Index: Integer): TX86FlagBehaviorSet; inline;
    procedure SetValue(Index: Integer; const Value: TX86FlagBehaviorSet); inline;
  strict private
    procedure Changed; inline;
  strict private
    function GetConflictState: Boolean;
  strict private
    function GetFlagCount: Integer; inline;
    function GetFlagPointer(Index: Integer): PX86FlagBehaviorSet; inline;
  public // TODO: Make private again
    procedure LoadFromJSON(JSON: PJSONVariantData; const FieldName: String);
    procedure SaveToJSON(JSON: PJSONVariantData; const FieldName: String);
  protected
    procedure AssignTo(Dest: TPersistent); override;
  protected
    constructor Create(Definition: TInstructionDefinition);
  public
    function GetFlagName(Index: Integer): String; inline;
  public
    function Equals(const Value: TX86Flags): Boolean; reintroduce;
  public
    property HasConflicts: Boolean read GetConflictState;
    property Flags[Index: Integer]: TX86FlagBehaviorSet read GetValue write SetValue;
    property FlagCount: Integer read GetFlagCount;
  published
    { FLAGS }
    property FlagCF  : TX86FlagBehaviorSet index  0 read GetValue write SetValue default [];
    property FlagPF  : TX86FlagBehaviorSet index  1 read GetValue write SetValue default [];
    property FlagAF  : TX86FlagBehaviorSet index  2 read GetValue write SetValue default [];
    property FlagZF  : TX86FlagBehaviorSet index  3 read GetValue write SetValue default [];
    property FlagSF  : TX86FlagBehaviorSet index  4 read GetValue write SetValue default [];
    property FlagTF  : TX86FlagBehaviorSet index  5 read GetValue write SetValue default [];
    property FlagIF  : TX86FlagBehaviorSet index  6 read GetValue write SetValue default [];
    property FlagDF  : TX86FlagBehaviorSet index  7 read GetValue write SetValue default [];
    property FlagOF  : TX86FlagBehaviorSet index  8 read GetValue write SetValue default [];
    property FlagIOPL: TX86FlagBehaviorSet index  9 read GetValue write SetValue default [];
    property FlagNT  : TX86FlagBehaviorSet index 10 read GetValue write SetValue default [];
    { EFLAGS }
    property FlagRF  : TX86FlagBehaviorSet index 11 read GetValue write SetValue default [];
    property FlagVM  : TX86FlagBehaviorSet index 12 read GetValue write SetValue default [];
    property FlagAC  : TX86FlagBehaviorSet index 13 read GetValue write SetValue default [];
    property FlagVIF : TX86FlagBehaviorSet index 14 read GetValue write SetValue default [];
    property FlagVIP : TX86FlagBehaviorSet index 15 read GetValue write SetValue default [];
    property FlagID  : TX86FlagBehaviorSet index 16 read GetValue write SetValue default [];
  end;

  TEVEXEncodingContext = (
    // EVEX.B = 1 is forbidden for this instruction and will cause UD
    ecUD,
    // EVEX.B = 1 broadcast
    ecBC,
    // EVEX.B = 1 rounding-control
    ecRC,
    // EVEX.B = 1 suppress all exceptions
    ecSAE
  );

  TEVEXMaskPolicy = (
    // The instruction can not encode a mask register
    mpMaskInvalid,
    // The instruction accepts mask registers other than the default-mask (K0), but does not
    // require them
    mpMaskAccepted,
    // The instruction requires a mask register other than the default-mask (K0)
    mpMaskRequired,
    // The instruction does not allow mask registers other than the default-mask (K0)
    mpMaskForbidden
  );

  {TEVEXEncodingContext = (
    ecNone,
    ecBroadcast,
    ecRoundingControl,
    ecSuppressAllExceptions
  );

  TEVEXInformation = class(TPersistent)
  strict private
    FDefinition: TInstructionDefinition;
  strict private
    procedure Changed; inline;
  strict private
    function GetConflictState: Boolean;
  private
    procedure LoadFromJSON(JSON: PJSONVariantData; const FieldName: String);
    procedure SaveToJSON(JSON: PJSONVariantData; const FieldName: String);
  protected
    procedure AssignTo(Dest: TPersistent); override;
  protected
    constructor Create(Definition: TInstructionDefinition);
  public
    function Equals(const Value: TX86Flags): Boolean; reintroduce;
  public
    property HasConflicts: Boolean read GetConflictState;
  published
    property EncodingContext: TEVEXEncodingContext;
    property HasEvexAAA: Boolean;
    property HasEvexZ: Boolean;
    property CD8Scale: Cardinal;
  end;}

  TInstructionOperands = class;

  TOperandType = (
    optUnused,
    optGPR8,
    optGPR16,
    optGPR32,
    optGPR64,
    optFPR,
    optVR64,
    optVR128,
    optVR256,
    optVR512,
    optTR,
    optCR,
    optDR,
    optSREG,
    optMSKR,
    optBNDR,
    optMem,
    optMem8,
    optMem16,
    optMem32,
    optMem64,
    optMem80,
    optMem128,
    optMem256,
    optMem512,
    optMem32Bcst2,
    optMem32Bcst4,
    optMem32Bcst8,
    optMem32Bcst16,
    optMem64Bcst2,
    optMem64Bcst4,
    optMem64Bcst8,
    optMem64Bcst16,
    optMem32VSIBX,
    optMem32VSIBY,
    optMem32VSIBZ,
    optMem64VSIBX,
    optMem64VSIBY,
    optMem64VSIBZ,
    optMem1616,
    optMem1632,
    optMem1664,
    optMem112,
    optMem224,
    optImm8,
    optImm8U,
    optImm16,
    optImm32,
    optImm64,
    optRel8,
    optRel16,
    optRel32,
    optRel64,
    optPtr1616,
    optPtr1632,
    optPtr1664,
    optMoffs16,
    optMoffs32,
    optMoffs64,
    optSrcIndex8,
    optSrcIndex16,
    optSrcIndex32,
    optSrcIndex64,
    optDstIndex8,
    optDstIndex16,
    optDstIndex32,
    optDstIndex64,
    optFixed1,
    optFixedAL,
    optFixedCL,
    optFixedAX,
    optFixedDX,
    optFixedEAX,
    optFixedECX,
    optFixedRAX,
    optFixedST0,
    optFixedES,
    optFixedSS,
    optFixedCS,
    optFixedDS,
    optFixedFS,
    optFixedGS
  );

  TOperandEncoding = (
    opeNone,
    opeModrmReg,
    opeModrmRm,
    opeModrmRmCD1,
    opeModrmRmCD2,
    opeModrmRmCD4,
    opeModrmRmCD8,
    opeModrmRmCD16,
    opeModrmRmCD32,
    opeModrmRmCD64,
    opeOpcodeBits,
    opeVexVVVV,
    opeEvexAAA,
    opeImm8Lo,
    opeImm8Hi,
    opeImm8,
    opeImm16,
    opeImm32,
    opeImm64
  );

  TOperandAction = (
    opaRead,
    opaWrite,
    opaReadWrite,
    opaCondRead,
    opaCondWrite,
    opaReadCondWrite,
    opaWriteCondRead
  );

  TInstructionOperand = class(TPersistent)
  strict private
    FOperands: TInstructionOperands;
    FType: TOperandType;
    FEncoding: TOperandEncoding;
    FAction: TOperandAction;
  strict private
    function GetConflictState: Boolean;
    procedure SetType(const Value: TOperandType); inline;
    procedure SetEncoding(const Value: TOperandEncoding); inline;
    procedure SetAction(const Value: TOperandAction); inline;
  strict private
    procedure Changed; inline;
  private
    procedure LoadFromJSON(JSON: PJSONVariantData; const FieldName: String);
    procedure SaveToJSON(JSON: PJSONVariantData; const FieldName: String);
  protected
    procedure AssignTo(Dest: TPersistent); override;
  protected
    constructor Create(Operands: TInstructionOperands);
  public
    function Equals(const Value: TInstructionOperand): Boolean; reintroduce;
  public
    function GetDescription(IncludeAccessMode: Boolean = true): String;
  public
    property HasConflicts: Boolean read GetConflictState;
  published
    property OperandType: TOperandType read FType write SetType default optUnused;
    property Encoding: TOperandEncoding read FEncoding write SetEncoding default opeNone;
    property Action: TOperandAction read FAction write SetAction default opaRead;
  end;

  TInstructionOperands = class(TPersistent)
  strict private
    FDefinition: TInstructionDefinition;
    FOperands: array[0..4] of TInstructionOperand;
  strict private
    function GetOperandCount: Integer; inline;
    function GetOperandsUsed: Integer; inline;
    function GetConflictState: Boolean;
  private
    procedure Changed; inline;
  private
    function GetOperandById(Id: Integer): TInstructionOperand; inline;
  private
    procedure LoadFromJSON(JSON: PJSONVariantData; const FieldName: String);
    procedure SaveToJSON(JSON: PJSONVariantData; const FieldName: String);
  protected
    procedure AssignTo(Dest: TPersistent); override;
  protected
    constructor Create(Definition: TInstructionDefinition);
  public
    function Equals(const Value: TInstructionOperands): Boolean; reintroduce;
  public
    destructor Destroy; override;
  public
    property Operands[Index: Integer]: TInstructionOperand read GetOperandById;
    property OperandCount: Integer read GetOperandCount;
    property OperandsUsed: Integer read GetOperandsUsed;
    property HasConflicts: Boolean read GetConflictState;
  published
    property OperandA: TInstructionOperand index 0 read GetOperandById;
    property OperandB: TInstructionOperand index 1 read GetOperandById;
    property OperandC: TInstructionOperand index 2 read GetOperandById;
    property OperandD: TInstructionOperand index 3 read GetOperandById;
    property OperandE: TInstructionOperand index 4 read GetOperandById;
  end;

  TInstructionDefinitionConflict = (
    // This conflict is enforced by the user
    idcForcedConflict,
    // The instruction-operands configuration is invalid
    idcOperands,
    // The prefix-flags are invalid
    idcPrefixFlags,
    // The FLAGS/EFLAGS/RFLAGS registers in the ImplicitRead or ImplicitWrite property do not
    // match the given X86Flags configuration
    idcX86Flags
  );
  TInstructionDefinitionConflicts = set of TInstructionDefinitionConflict;

  TInstructionEncoding = (
    ieDefault,
    ie3DNow,
    ieXOP,
    ieVEX,
    ieEVEX
  );

  TOpcodeMap = (
    omDefault,
    om0F,
    om0F38,
    om0F3A,
    omXOP8,
    omXOP9,
    omXOPA
  );

  TOpcodeByte = type Byte;

  TPrefixFlag = (
    pfAcceptsLock,
    pfAcceptsREP,
    pfAcceptsREPEREPNE,
    pfAcceptsBOUND,
    pfAcceptsXACQUIRE,
    pfAcceptsXRELEASE,
    pfAcceptsHLEWithoutLock,
    pfAcceptsBranchHints
  );
  TPrefixFlags = set of TPrefixFlag;

  TInstructionDefinitionFlag = (
    ifForceConflict,
    ifAcceptsEVEXAAA,
    ifAcceptsEVEXZ,
    ifIsPrivileged,
    ifHasEVEXBC,
    ifHasEVEXRC,
    ifHasEVEXSAE
  );
  TInstructionDefinitionFlags = set of TInstructionDefinitionFlag;

  TInstructionDefinition = class(TPersistent)
  strict private
    FEditor: TInstructionEditor;
    FParent: TDefinitionContainer;
    FConflicts: TInstructionDefinitionConflicts;
    FData: Pointer;
    FUpdateCount: Integer;
    FDoUpdatePosition: Boolean;
    FDoUpdateValues: Boolean;
  strict private
    FMnemonic: String;
    FEncoding: TInstructionEncoding;
    FOpcodeMap: TOpcodeMap;
    FOpcode: TOpcodeByte;
    FExtensions: TOpcodeExtensions;
    FCPUID: TCPUIDFeatureFlags;
    FOperands: TInstructionOperands;
    FPrefixFlags: TPrefixFlags;
    FFlags: TInstructionDefinitionFlags;
    FImplicitRead: TX86Registers;
    FImplicitWrite: TX86Registers;
    FX86Flags: TX86Flags;
    FEVEXCD8Scale: Cardinal;
    FComment: String;
  strict private
    function GetConflictState: Boolean; inline;
  strict private
    procedure SetMnemonic(const Value: String); inline;
    procedure SetEncoding(const Value: TInstructionEncoding); inline;
    procedure SetOpcodeMap(const Value: TOpcodeMap); inline;
    procedure SetOpcode(const Value: TOpcodeByte); inline;
    procedure SetPrefixFlags(const Value: TPrefixFlags); inline;
    procedure SetFlags(const Value: TInstructionDefinitionFlags); inline;
    procedure SetComment(const Value: String); inline;
  strict private
    procedure UpdateConflictFlags;
  private
    procedure UpdatePosition; inline;
    procedure UpdateValues; inline;
    procedure SetParent(Parent: TDefinitionContainer); inline;
  protected
    procedure AssignTo(Dest: TPersistent); override;
  public
    procedure BeginUpdate; inline;
    procedure Update; inline;
    procedure EndUpdate; inline;
  public
    function Equals(const Value: TInstructionDefinition;
      CheckComment: Boolean = false;
      CheckFilterRelatedAttributes: Boolean = true): Boolean; reintroduce;
  public
    procedure LoadFromJSON(JSON: PJSONVariantData);
    procedure SaveToJSON(JSON: PJSONVariantData);
  public
    constructor Create(Editor: TInstructionEditor; const Mnemonic: String);
    destructor Destroy; override;
  public
    property Editor: TInstructionEditor read FEditor;
    property Parent: TDefinitionContainer read FParent;
    property HasConflicts: Boolean read GetConflictState;
    property Data: Pointer read FData write FData;
  published
    property Mnemonic: String read FMnemonic write SetMnemonic;
    property Encoding: TInstructionEncoding read FEncoding write SetEncoding default ieDefault;
    property OpcodeMap: TOpcodeMap read FOpcodeMap write SetOpcodeMap default omDefault;
    property Opcode: TOpcodeByte read FOpcode write SetOpcode;
    property OpcodeExtensions: TOpcodeExtensions read FExtensions;
    property CPUID: TCPUIDFeatureFlags read FCPUID;
    property Operands: TInstructionOperands read FOperands;
    property PrefixFlags: TPrefixFlags read FPrefixFlags write SetPrefixFlags default [];
    property Flags: TInstructionDefinitionFlags read FFlags write SetFlags default [];
    property ImplicitRead: TX86Registers read FImplicitRead;
    property ImplicitWrite: TX86Registers read FImplicitWrite;
    property X86Flags: TX86Flags read FX86Flags;
    property EVEXCD8Scale: Cardinal read FEVEXCD8Scale default 0;
    property Comment: String read FComment write SetComment;
    property Conflicts: TInstructionDefinitionConflicts read FConflicts;
  end;

  TInstructionFilterFlag = (
    // This is the root table
    iffIsRootTable,
    // This is a static filter that should not be removed.
    // Warning: Never create static tables as child of non-static ones. The code assumes that the
    //          parent of a static-table is always another static table.
    iffIsStaticFilter,
    // This is a definition container and not an actual filter
    iffIsDefinitionContainer
  );
  TInstructionFilterFlags = set of TInstructionFilterFlag;

  TNeutralElementType = (
    // The neutral "zero" element is not supported
    netNotAvailable,
    // The neutral "zero" element is supported and used as a placeholder. The filter will signal a
    // conflict, if the neutral element AND at least one regular value is set.
    netPlaceholder,
    // The neutral "zero" element is supported and can be used as a regular value
    netValue
  );

  TInstructionFilterConflict = (
    // This filter is affected by a conflict of one or more child-filters
    ifcInheritedConflict,
    // This definition-container holds more than one instruction definition
    ifcDefinitionCount,
    // The neutral element and at least one regular value is set
    ifcNeutralElement
  );
  TInstructionFilterConflicts = set of TInstructionFilterConflict;

  TInstructionFilterClass = class of TInstructionFilter;

  PInstructionFilterList = ^TInstructionFilterList;
  TInstructionFilterList = array of TInstructionFilterClass;

  TInstructionFilter = class(TPersistent)
  strict private
    FEditor: TInstructionEditor;
    FParent: TInstructionFilter;
    FItems: TArray<TInstructionFilter>;
    FDefinitions: TList<TInstructionDefinition>;
    FConflicts: TInstructionFilterConflicts;
    FInheritedConflicts: Integer;
    FItemCount: Integer;
    FData: Pointer;
  strict private
    FFilterFlags: TInstructionFilterFlags;
  strict private
    function GetItem(const Index: Integer): TInstructionFilter; inline;
    function GetDefinition(const Index: Integer): TInstructionDefinition; inline;
    function GetDefinitionCount: Integer; inline;
    function GetConflictState: Boolean; inline;
    procedure SetParent(Parent: TInstructionFilter); inline;
    procedure SetConflicts(const Value: TInstructionFilterConflicts); inline;
  strict private
    procedure Changed; inline;
  private
    procedure SetItem(const Index: Integer; const Value: TInstructionFilter); inline;
  private
    procedure IncInheritedConflictCount; inline;
    procedure DecInheritedConflictCount; inline;
  private
    procedure CreateFilterAtIndex(Index: Integer; FilterClass: TInstructionFilterClass;
      IsRootTable, IsStaticFilter: Boolean);
    procedure InsertDefinition(Definition: TInstructionDefinition);
    procedure RemoveDefinition(Definition: TInstructionDefinition);
  protected
    constructor Create(Editor: TInstructionEditor; Parent: TInstructionFilter;
      IsRootTable, IsStaticFilter: Boolean); virtual;
  protected
    property Definitions[const Index: Integer]: TInstructionDefinition read GetDefinition;
    property DefinitionCount: Integer read GetDefinitionCount;
  public
    class function IsDefinitionContainer: Boolean; virtual;
    class function GetNeutralElementType: TNeutralElementType; virtual;
    class function GetCapacity: Cardinal; virtual;
    class function GetInsertPosition(const Definition: TInstructionDefinition): Integer; virtual;
    class function GetDescription: String; virtual;
    class function GetItemDescription(Index: Integer): String; virtual;
  public
    function IndexOf(const Filter: TInstructionFilter): Integer;
  public
    destructor Destroy; override;
  public
    property Editor: TInstructionEditor read FEditor;
    property Parent: TInstructionFilter read FParent;
    property Items[const Index: Integer]: TInstructionFilter read GetItem;
    property HasConflicts: Boolean read GetConflictState;
    property Data: Pointer read FData write FData;
  published
    property FilterFlags: TInstructionFilterFlags read FFilterFlags;
    property NeutralElementType: TNeutralElementType read GetNeutralElementType;
    property Capacity: Cardinal read GetCapacity;
    property Conflicts: TInstructionFilterConflicts read FConflicts;
    property ItemCount: Integer read FItemCount;
  end;

  TDefinitionContainer = class(TInstructionFilter)
  public
    class function IsDefinitionContainer: Boolean; override;
  public
    property Definitions;
  published
    property DefinitionCount;
  end;

  TEditorWorkStartEvent =
    procedure(Sender: TObject; MinWorkCount, MaxWorkCount: Integer) of Object;
  TEditorWorkEvent =
    procedure(Sender: TObject; WorkCount: Integer) of Object;
  TEditorFilterEvent =
    procedure(Sender: TObject; Filter: TInstructionFilter) of Object;
  TEditorDefinitionEvent =
  procedure(Sender: TObject; Definition: TInstructionDefinition) of Object;

  TInstructionEditor = class(TObject)
  strict private
    class var FilterOrderDef: TInstructionFilterList;
    class var FilterOrderXOP: TInstructionFilterList;
    class var FilterOrderVEX: TInstructionFilterList;
    class var FilterOrderEVEX: TInstructionFilterList;
  strict private
    class function GetFilterList(Encoding: TInstructionEncoding): PInstructionFilterList; inline;
  strict private
    FDefinitions: TList<TInstructionDefinition>;
    FRootTable: TInstructionFilter;
    FFilterCount: Integer;
    FUpdateCount: Integer;
    FPreventDefinitionRemoval: Boolean;
  strict private
    FOnWorkStart: TEditorWorkStartEvent;
    FOnWork: TEditorWorkEvent;
    FOnWorkEnd: TNotifyEvent;
    FOnBeginUpdate: TNotifyEvent;
    FOnEndUpdate: TNotifyEvent;
    FOnFilterCreated: TEditorFilterEvent;
    FOnFilterInserted: TEditorFilterEvent;
    FOnFilterChanged: TEditorFilterEvent;
    FOnFilterRemoved: TEditorFilterEvent;
    FOnFilterDestroyed: TEditorFilterEvent;
    FOnDefinitionCreated: TEditorDefinitionEvent;
    FOnDefinitionInserted: TEditorDefinitionEvent;
    FOnDefinitionChanged: TEditorDefinitionEvent;
    FOnDefinitionRemoved: TEditorDefinitionEvent;
    FOnDefinitionDestroyed: TEditorDefinitionEvent;
  strict private
    function GetDefinition(const Index: Integer): TInstructionDefinition; inline;
    function GetDefinitionCount: Integer; inline;
  strict private
    function GetDefinitionTopLevelFilter(Definition: TInstructionDefinition): TInstructionFilter;
  private
    procedure RegisterDefinition(Definition: TInstructionDefinition); inline;
    procedure InsertDefinition(Definition: TInstructionDefinition);
    procedure RemoveDefinition(Definition: TInstructionDefinition); inline;
    procedure UnregisterDefinition(Definition: TInstructionDefinition); inline;
  private
    procedure FilterCreated(Filter: TInstructionFilter); inline;
    procedure FilterInserted(Filter: TInstructionFilter); inline;
    procedure FilterChanged(Filter: TInstructionFilter); inline;
    procedure FilterRemoved(Filter: TInstructionFilter); inline;
    procedure FilterDestroyed(Filter: TInstructionFilter); inline;
    procedure DefinitionInserted(Definition: TInstructionDefinition); inline;
    procedure DefinitionChanged(Definition: TInstructionDefinition); inline;
    procedure DefinitionRemoved(Definition: TInstructionDefinition); inline;
  public
    class constructor Create;
  public
    procedure BeginUpdate; inline;
    procedure EndUpdate; inline;
  public
    procedure LoadFromJSON(JSON: PJSONVariantData);
    procedure SaveToJSON(JSON: PJSONVariantData);
    procedure LoadFromFile(const Filename: String);
    procedure SaveToFile(const Filename: String);
    procedure Reset;
  public
    function CreateDefinition(const Mnemonic: String): TInstructionDefinition; inline;
  public
    constructor Create;
    destructor Destroy; override;
  public
    property RootTable: TInstructionFilter read FRootTable;
    property FilterCount: Integer read FFilterCount;
    property Definitions[const Index: Integer]: TInstructionDefinition read GetDefinition;
    property DefinitionCount: Integer read GetDefinitionCount;
  public
    property OnWorkStart: TEditorWorkStartEvent read FOnWorkStart write FOnWorkStart;
    property OnWork: TEditorWorkEvent read FOnWork write FOnWork;
    property OnWorkEnd: TNotifyEvent read FOnWorkEnd write FOnWorkEnd;
    property OnBeginUpdate: TNotifyEvent read FOnBeginUpdate write FOnBeginUpdate;
    property OnEndUpdate: TNotifyEvent read FOnEndUpdate write FOnEndUpdate;
    property OnFilterCreated: TEditorFilterEvent read FOnFilterCreated write FOnFilterCreated;
    property OnFilterInserted: TEditorFilterEvent read FOnFilterInserted write FOnFilterInserted;
    property OnFilterChanged: TEditorFilterEvent read FOnFilterChanged write FOnFilterChanged;
    property OnFilterRemoved: TEditorFilterEvent read FOnFilterRemoved write FOnFilterRemoved;
    property OnFilterDestroyed: TEditorFilterEvent read FOnFilterDestroyed write FOnFilterDestroyed;
    property OnDefinitionCreated: TEditorDefinitionEvent read FOnDefinitionCreated write
      FOnDefinitionCreated;
    property OnDefinitionInserted: TEditorDefinitionEvent read FOnDefinitionInserted write
      FOnDefinitionInserted;
    property OnDefinitionChanged: TEditorDefinitionEvent read FOnDefinitionChanged write
      FOnDefinitionChanged;
    property OnDefinitionRemoved: TEditorDefinitionEvent read FOnDefinitionRemoved write
      FOnDefinitionRemoved;
    property OnDefinitionDestroyed: TEditorDefinitionEvent read FOnDefinitionDestroyed write
      FOnDefinitionDestroyed;
  end;

implementation

uses
  System.SysUtils, System.Variants, System.TypInfo, System.Generics.Defaults, untHelperClasses,
  Zydis.InstructionFilters;

{$REGION 'Const: JSON strings for TOpcodeExtensions'}
const
  SExtInstructionMode: array[TExtInstructionMode] of String = (
    'neutral',
    'require64',
    'exclude64'
  );

  SExtMandatoryPrefix: array[TExtMandatoryPrefix] of String = (
    'none',
    '66',
    'f3',
    'f2'
  );

  SExtModrmMod: array[TExtModrmMod] of String = (
    'neutral',
    'memory',
    'register'
  );

  SExtModrmReg: array[TExtModrmReg] of String = (
    'neutral',
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7'
  );

  SExtModrmRm: array[TExtModrmRm] of String = (
    'neutral',
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7'
  );

  SExtOperandSize: array[TExtOperandSize] of String = (
    'default',
    '16',
    '32'
  );

  SExtAddressSize: array[TExtAddressSize] of String = (
    'default',
    '16',
    '32',
    '64'
  );

  SExtBitFilter: array[TExtBitFilter] of String = (
    'rex_w',
    'vex_l',
    'evex_l2',
    'evex_b'
  );
{$ENDREGION}

{$REGION 'Const: JSON strings for TCPUIDFeatureFlags'}
const
  SCPUIDFeatureFlag: array[TCPUIDFeatureFlag] of String = (
    '3dnow',
    'adx',
    'aesni',
    'avx',
    'avx2',
    'avx512bw',
    'avx512cd',
    'avx512dq',
    'avx512er',
    'avx512f',
    'avx512pf',
    'avx512vl',
    'bmi1',
    'bmi2',
    'cmov',
    'cmpxchg16b',
    'f16c',
    'fma',
    'fma4',
    'fsgsbase',
    'hle',
    'lzcnt',
    'mmx',
    'movbe',
    'mpx',
    'mwaitx',
    'pclmul',
    'popcnt',
    'prefetchw',
    'rdrand',
    'rdseed',
    'rtm',
    'sha',
    'sse1',
    'sse2',
    'sse3',
    'sse41',
    'sse42',
    'sse4a',
    'ssse3',
    'tbm',
    'tsx',
    'xop',
    'fxsr',
    'lahfsahf',
    'xsave',
    'xsaves',
    'xsavec',
    'xsaveopt',
    'mfence',
    'vbmi',
    'ifma',
    'vmx',
    'smx',
    'ospke'
  );
{$ENDREGION}

{$REGION 'Const: JSON strings for TX86Registers'}
const
  SX86Register: array[TX86Register] of String = (
    'none',
    // General purpose registers 64-bit
    'rax',    'rcx',    'rdx',   'rbx',    'rsp',   'rbp',   'rsi',   'rdi',
    'r8',     'r9',     'r10',   'r11',    'r12',   'r13',   'r14',   'r15',
    // General purpose registers 32-bit
    'eax',    'ecx',    'edx',   'ebx',    'esp',   'ebp',   'esi',   'edi',
    'r8d',    'r9d',    'r10d',  'r11d',   'r12d',  'r13d',  'r14d',  'r15d',
    // General purpose registers 16-bit
    'ax',     'cx',     'dx',    'bx',     'sp',    'bp',    'si',    'di',
    'r8w',    'r9w',    'r10w',  'r11w',   'r12w',  'r13w',  'r14w',  'r15w',
    // General purpose registers  8-bit
    'al',     'cl',     'dl',    'bl',     'ah',    'ch',    'dh',    'bh',
    'spl',    'bpl',    'sil',   'dil',
    'r8b',    'r9b',    'r10b',  'r11b',   'r12b',  'r13b',  'r14b',  'r15b',
    // Floating point legacy registers
    'st0',    'st1',    'st2',   'st3',    'st4',   'st5',   'st6',   'st7',
    // Floating point multimedia registers
    'mm0',    'mm1',    'mm2',   'mm3',    'mm4',   'mm5',   'mm6',   'mm7',
    // Floating point vector registers 512-bit
    'zmm0',   'zmm1',   'zmm2',  'zmm3',   'zmm4',  'zmm5',  'zmm6',  'zmm7',
    'zmm8',   'zmm9',   'zmm10', 'zmm11',  'zmm12', 'zmm13', 'zmm14', 'zmm15',
    'zmm16',  'zmm17',  'zmm18', 'zmm19',  'zmm20', 'zmm21', 'zmm22', 'zmm23',
    'zmm24',  'zmm25',  'zmm26', 'zmm27',  'zmm28', 'zmm29', 'zmm30', 'zmm31',
    // Floating point vector registers 256-bit
    'ymm0',   'ymm1',   'ymm2',  'ymm3',   'ymm4',  'ymm5',  'ymm6',  'ymm7',
    'ymm8',   'ymm9',   'ymm10', 'ymm11',  'ymm12', 'ymm13', 'ymm14', 'ymm15',
    'ymm16',  'ymm17',  'ymm18', 'ymm19',  'ymm20', 'ymm21', 'ymm22', 'ymm23',
    'ymm24',  'ymm25',  'ymm26', 'ymm27',  'ymm28', 'ymm29', 'ymm30', 'ymm31',
    // Floating point vector registers 128-bit
    'xmm0',   'xmm1',   'xmm2',  'xmm3',   'xmm4',  'xmm5',  'xmm6',  'xmm7',
    'xmm8',   'xmm9',   'xmm10', 'xmm11',  'xmm12', 'xmm13', 'xmm14', 'xmm15',
    'xmm16',  'xmm17',  'xmm18', 'xmm19',  'xmm20', 'xmm21', 'xmm22', 'xmm23',
    'xmm24',  'xmm25',  'xmm26', 'xmm27',  'xmm28', 'xmm29', 'xmm30', 'xmm31',
    // Special registers
    'rflags', 'eflags', 'flags', 'rip',    'eip',   'ip',    'mxcsr',  'pkru',
    'xcr0',
    // Segment registers
    'es',     'cs',     'ss',    'ds',     'gs',    'fs',
    // Table registers
    'gdtr',   'ldtr',   'idtr',  'tr',
    // Test registers
    'tr0',    'tr1',    'tr2',   'tr3',    'tr4',   'tr5',   'tr6',   'tr7',
    // Control registers
    'cr0',    'cr1',    'cr2',   'cr3',    'cr4',   'cr5',   'cr6',   'cr7',
    'cr8',    'cr9',    'cr10',  'cr11',   'cr12',  'cr13',  'cr14',  'cr15',
    // Debug registers
    'dr0',    'dr1',    'dr2',   'dr3',    'dr4',   'dr5',   'dr6',   'dr7',
    'dr8',    'dr9',    'dr10',  'dr11',   'dr12',  'dr13',  'dr14',  'dr15',
    // Mask registers
    'k0',     'k1',     'k2',    'k3',     'k4',    'k5',     'k6',   'k7',
    // Bounds registers
    'bnd0',   'bnd1',   'bnd2',  'bnd3', 'bndcfg', 'bndstatus'
  );
{$ENDREGION}

{$REGION 'Const: JSON strings for TX86Flags'}
const
  SX86FlagBehavior: array[TX86FlagBehavior] of String = (
    'tested',
    'modified',
    'reset',
    'set',
    'undefined'
  );
{$ENDREGION}

{$REGION 'Const: JSON strings for TInstructionOperand'}
const
  SOperandType: array[TOperandType] of String = (
    'unused',
    'gpr8',
    'gpr16',
    'gpr32',
    'gpr64',
    'fpr',
    'vr64',
    'vr128',
    'vr256',
    'vr512',
    'tr',
    'cr',
    'dr',
    'sreg',
    'mskr',
    'bndr',
    'mem',
    'mem8',
    'mem16',
    'mem32',
    'mem64',
    'mem80',
    'mem128',
    'mem256',
    'mem512',
    'mem32bcst2',
    'mem32bcst4',
    'mem32bcst8',
    'mem32bcst16',
    'mem64bcst2',
    'mem64bcst4',
    'mem64bcst8',
    'mem64bcst16',
    'mem32vsibx',
    'mem32vsiby',
    'mem32vsibz',
    'mem64vsibx',
    'mem64vsiby',
    'mem64vsibz',
    'mem1616',
    'mem1632',
    'mem1664',
    'mem112',
    'mem224',
    'imm8',
    'imm8u',
    'imm16',
    'imm32',
    'imm64',
    'rel8',
    'rel16',
    'rel32',
    'rel64',
    'ptr1616',
    'ptr1632',
    'ptr1664',
    'moffs16',
    'moffs32',
    'moffs64',
    'srcidx8',
    'srcidx16',
    'srcidx32',
    'srcidx64',
    'dstidx8',
    'dstidx16',
    'dstidx32',
    'dstidx64',
    '1',
    'al',
    'cl',
    'ax',
    'dx',
    'eax',
    'ecx',
    'rax',
    'st0',
    'es',
    'ss',
    'cs',
    'ds',
    'fs',
    'gs'
  );

  SOperandEncoding: array[TOperandEncoding] of String = (
    'none',
    'modrm_reg',
    'modrm_rm',
    'modrm_rm_cd1',
    'modrm_rm_cd2',
    'modrm_rm_cd4',
    'modrm_rm_cd8',
    'modrm_rm_cd16',
    'modrm_rm_cd32',
    'modrm_rm_cd64',
    'opcode',
    'vex_vvvv',
    'evex_aaa',
    'imm8lo',
    'imm8hi',
    'imm8',
    'imm16',
    'imm32',
    'imm64'
  );

  SOperandAction: array[TOperandAction] of String = (
    'read',
    'write',
    'readwrite',
    'cond_read',
    'cond_write',
    'read_cond_write',
    'write_cond_read'
  );
{$ENDREGION}

{$REGION 'Const: JSON strings for TInstructionDefinition'}
const
  SInstructionEncoding: array[TInstructionEncoding] of String = (
    'default',
    '3dnow',
    'xop',
    'vex',
    'evex'
  );

  SOpcodeMap: array[TOpcodeMap] of String = (
    'default',
    '0f',
    '0f38',
    '0f3a',
    'xop8',
    'xop9',
    'xopa'
  );

  SPrefixFlag: array[TPrefixFlag] of String = (
    'accepts_lock',
    'accepts_rep',
    'accepts_reperepne',
    'accepts_bound',
    'accepts_xacquire',
    'accepts_xrelease',
    'accepts_hle_without_lock',
    'accepts_branch_hints'
  );

  SInstructionDefinitionFlag: array[TInstructionDefinitionFlag] of String = (
    'conflict',
    'accepts_evex_aaa',
    'accepts_evex_z',
    'privileged',
    'has_evex_bc',
    'has_evex_rc',
    'has_evex_sae'
  );
{$ENDREGION}

{$REGION 'Class: TJSONEnumHelper'}
type
  TJSONEnumHelper<TEnum> = record
  strict private
    class function ReadString(JSON: PJSONVariantData; const Name, Default: String;
      const LowerCase: Boolean = true): String; static; inline;
  public
    class function ReadValue(JSON: PJSONVariantData; const Name: String;
      const ElementStrings: array of String): TEnum; static;
  end;

class function TJSONEnumHelper<TEnum>.ReadValue(JSON: PJSONVariantData; const Name: String;
  const ElementStrings: array of String): TEnum;
var
  V: Integer;
begin
  Assert(PTypeInfo(TypeInfo(TEnum))^.Kind = tkEnumeration, 'Invalid generic type.');
  V := TStringHelper.IndexStr(ReadString(JSON, Name, ElementStrings[0]), ElementStrings);
  if (V < 0) then
  begin
    // TODO: Maybe make this a warning instead of an exception
    raise Exception.CreateFmt('The "%s" field contains an invalid enum value.', [Name]);
  end;
  Result := TEnum(Pointer(@V)^);
end;

class function TJSONEnumHelper<TEnum>.ReadString(JSON: PJSONVariantData;
  const Name, Default: String; const LowerCase: Boolean): String;
var
  V: Variant;
begin
  V := JSON^.Value[Name];
  if (VarIsEmpty(V)) then
  begin
    Exit(Default);
  end;
  Result := V;
  if (LowerCase) then
  begin
    TStringHelper.AnsiLowerCase(Result);
  end;
end;
{$ENDREGION}

{$REGION 'Class: TJSONSetHelper'}
type
  TJSONSetHelper<TSet> = record
  strict private
    class procedure GetEnumBounds(var MinValue, MaxValue: Integer); static; inline;
  public
    class function ReadValue(JSON: PJSONVariantData; const Name: String;
      const ElementStrings: array of String): TSet; static;
    class procedure WriteValue(JSON: PJSONVariantData; const Name: String;
      const ElementStrings: array of String; Value: TSet); static;
  end;

class procedure TJSONSetHelper<TSet>.GetEnumBounds(var MinValue, MaxValue: Integer);
var
  TypInfo: PTypeInfo;
  TypData: PTypeData;
begin
  TypInfo := TypeInfo(TSet);
  Assert(TypInfo^.Kind = tkSet, 'Invalid generic type.');
  TypData := GetTypeData(GetTypeData(TypInfo)^.CompType^);
  Assert(TypData^.MinValue  =   0, 'The enum-type needs to be zero-based.');
  Assert(TypData^.MaxValue <= 255, 'The enum-type''s maximum value needs the be lower than 256.');
  MinValue := TypData^.MinValue;
  MaxValue := TypData^.MaxValue;
end;

class function TJSONSetHelper<TSet>.ReadValue(JSON: PJSONVariantData; const Name: String;
  const ElementStrings: array of String): TSet;
type
  TSetType = set of 0..255;
var
  A: PJSONVariantData;
  MinValue,
  MaxValue: Integer;
  I, J: Integer;
begin
  GetEnumBounds(MinValue, MaxValue);
  Assert(MaxValue = High(ElementStrings),
    'The size of the string-array does not match the size of the enum-type');
  FillChar(Pointer(@Result)^, SizeOf(TSet), #0);
  A := JSON^.Data(Name);
  if (Assigned(A)) then
  begin
    if (A^.Kind <> jvArray) then
    begin
      raise Exception.CreateFmt('The "%s" field is not a valid JSON array.', [Name]);
    end;
    for I := 0 to A^.Count - 1 do
    begin
      for J := MinValue to MaxValue do
      begin
        if (LowerCase(A^.Item[I]) = ElementStrings[J]) then
        begin
          Include(TSetType(Pointer(@Result)^), J);
          Break;
        end;
      end;
      // TODO: Show exception (or warning), if an invalid element was found
    end;
  end;
end;

class procedure TJSONSetHelper<TSet>.WriteValue(JSON: PJSONVariantData; const Name: String;
  const ElementStrings: array of String; Value: TSet);
type
  TSetType = set of 0..255;
var
  A: TJSONVariantData;
  MinValue,
  MaxValue: Integer;
  I: Integer;
begin
  GetEnumBounds(MinValue, MaxValue);
  Assert(MaxValue = High(ElementStrings),
    'The size of the string-array does not match the size of the enum-type');
  A.Init;
  for I := MinValue to MaxValue do
  begin
    if (I in TSetType(Pointer(@Value)^)) then
    begin
      A.AddValue(ElementStrings[I]);
    end;
  end;
  if (A.Count > 0) then
  begin
    JSON^.AddNameValue(Name, Variant(A));
  end;
end;
{$ENDREGION}

{$REGION 'Class: TOpcodeExtensions'}
procedure TOpcodeExtensions.AssignTo(Dest: TPersistent);
var
  D: TOpcodeExtensions;
begin
  if (Dest is TOpcodeExtensions) then
  begin
    D := Dest as TOpcodeExtensions;
    D.FMode := FMode;
    D.FMandatoryPrefix := FMandatoryPrefix;
    D.FModrmMod := FModrmMod;
    D.FModrmReg := FModrmReg;
    D.FModrmRm := FModrmRm;
    D.FOperandSize := FOperandSize;
    D.FAddressSize := FAddressSize;
    D.FBitFilters := FBitFilters;
    D.Changed;
  end else inherited;
end;

procedure TOpcodeExtensions.Changed;
begin
  FDefinition.UpdatePosition;
end;

constructor TOpcodeExtensions.Create(Definition: TInstructionDefinition);
begin
  inherited Create;
  FDefinition := Definition;
end;

function TOpcodeExtensions.Equals(const Value: TOpcodeExtensions): Boolean;
begin
  Result :=
    (Value.FMode = FMode) and (Value.FMandatoryPrefix = FMandatoryPrefix) and
    (Value.FModrmMod = FModrmMod) and (Value.FModrmReg = FModrmReg) and
    (Value.FModrmRm = FModrmRm) and (Value.FOperandSize = FOperandSize) and
    (Value.FAddressSize = FAddressSize) and (Value.FBitFilters = FBitFilters);
end;

procedure TOpcodeExtensions.LoadFromJSON(JSON: PJSONVariantData; const FieldName: String);
var
  V: PJSONVariantData;
begin
  V := JSON.Data(FieldName);
  if (Assigned(V)) then
  begin
    if (V^.Kind <> jvObject) then
    begin
      raise Exception.CreateFmt('The "%s" field is not a valid JSON object.', [FieldName]);
    end;
    SetMode(TJSONEnumHelper<TExtInstructionMode>.ReadValue(
      V, 'mode', SExtInstructionMode));
    SetPrefix(TJSONEnumHelper<TExtMandatoryPrefix>.ReadValue(
      V, 'prefix', SExtMandatoryPrefix));
    SetModrmMod(TJSONEnumHelper<TExtModrmMod>.ReadValue(
      V, 'modrm_mod', SExtModrmMod));
    SetModrmReg(TJSONEnumHelper<TExtModrmReg>.ReadValue(
      V, 'modrm_reg', SExtModrmReg));
    SetModrmRm(TJSONEnumHelper<TExtModrmRm>.ReadValue(
      V, 'modrm_rm', SExtModrmRm));
    SetOperandSize(TJSONEnumHelper<TExtOperandSize>.ReadValue(
      V, 'opsize', SExtOperandSize));
    SetAddressSize(TJSONEnumHelper<TExtAddressSize>.ReadValue(
      V, 'adsize', SExtAddressSize));
    SetBitFilters(TJSONSetHelper<TExtBitFilters>.ReadValue(
      V, 'bitfilters', SExtBitFilter));
  end;
end;

procedure TOpcodeExtensions.SaveToJSON(JSON: PJSONVariantData; const FieldName: String);
var
  V: TJSONVariantData;
begin
  V.Init;
  if (FMode <> imNeutral) then
    V.AddNameValue('mode', SExtInstructionMode[FMode]);
  if (FMandatoryPrefix <> mpNone) then
    V.AddNameValue('prefix', SExtMandatoryPrefix[FMandatoryPrefix]);
  if (FModrmMod <> mdNeutral) then
    V.AddNameValue('modrm_mod', SExtModrmMod[FModrmMod]);
  if (FModrmRm <> rmNeutral) then
    V.AddNameValue('modrm_rm', SExtModrmRm[FModrmRm]);
  if (FModrmReg <> rgNeutral) then
    V.AddNameValue('modrm_reg', SExtModrmReg[FModrmReg]);
  if (FOperandSize <> osNeutral) then
    V.AddNameValue('opsize', SExtOperandSize[FOperandSize]);
  if (FAddressSize <> asNeutral) then
    V.AddNameValue('adsize', SExtAddressSize[FAddressSize]);
  TJSONSetHelper<TExtBitFilters>.WriteValue(@V, 'bitfilters', SExtBitFilter, FBitFilters);
  if (V.Count > 0) then
  begin
    JSON^.AddNameValue(FieldName, Variant(V));
  end;
end;

procedure TOpcodeExtensions.SetAddressSize(const Value: TExtAddressSize);
begin
  if (FAddressSize <> Value) then
  begin
    FAddressSize := Value;
    Changed;
  end;
end;

procedure TOpcodeExtensions.SetBitFilters(const Value: TExtBitFilters);
begin
  if (FBitFilters <> Value) then
  begin
    FBitFilters := Value;
    Changed;
  end;
end;

procedure TOpcodeExtensions.SetMandatoryPrefix(const Value: TExtMandatoryPrefix);
begin
  if (FMandatoryPrefix <> Value) then
  begin
    FMandatoryPrefix := Value;
    Changed;
  end;
end;

procedure TOpcodeExtensions.SetMode(const Value: TExtInstructionMode);
begin
  if (FMode <> Value) then
  begin
    FMode := Value;
    Changed;
  end;
end;

procedure TOpcodeExtensions.SetModrmMod(const Value: TExtModrmMod);
begin
  if (FModrmMod <> Value) then
  begin
    FModrmMod := Value;
    Changed;
  end;
end;

procedure TOpcodeExtensions.SetModrmReg(const Value: TExtModrmReg);
begin
  if (FModrmReg <> Value) then
  begin
    FModrmReg := Value;
    Changed;
  end;
end;

procedure TOpcodeExtensions.SetModrmRm(const Value: TExtModrmRm);
begin
  if (FModrmRm <> Value) then
  begin
    FModrmRm := Value;
    Changed;
  end;
end;

procedure TOpcodeExtensions.SetOperandSize(const Value: TExtOperandSize);
begin
  if (FOperandSize <> Value) then
  begin
    FOperandSize := Value;
    Changed;
  end;
end;

procedure TOpcodeExtensions.SetPrefix(const Value: TExtMandatoryPrefix);
begin
  FMandatoryPrefix := Value;
end;
{$ENDREGION}

{$REGION 'Class: TCPUIDFeatureFlags'}
procedure TCPUIDFeatureFlags.AssignTo(Dest: TPersistent);
var
  D: TCPUIDFeatureFlags;
begin
  if (Dest is TCPUIDFeatureFlags) then
  begin
    D := Dest as TCPUIDFeatureFlags;
    D.SetFeatureFlags(FFeatureFlags);
  end else inherited;
end;

procedure TCPUIDFeatureFlags.Changed;
begin
  FDefinition.UpdateValues;
end;

constructor TCPUIDFeatureFlags.Create(Definition: TInstructionDefinition);
begin
  inherited Create;
  FDefinition := Definition;
end;

function TCPUIDFeatureFlags.Equals(const Value: TCPUIDFeatureFlags): Boolean;
begin
  Result := (Value.FFeatureFlags = FFeatureFlags);
end;

procedure TCPUIDFeatureFlags.LoadFromJSON(JSON: PJSONVariantData; const FieldName: String);
begin
  SetFeatureFlags(
    TJSONSetHelper<TCPUIDFeatureFlagSet>.ReadValue(JSON, FieldName, SCPUIDFeatureFlag));
end;

procedure TCPUIDFeatureFlags.SaveToJSON(JSON: PJSONVariantData; const FieldName: String);
begin
  TJSONSetHelper<TCPUIDFeatureFlagSet>.WriteValue(
    JSON, FieldName, SCPUIDFeatureFlag, FFeatureFlags);
end;

procedure TCPUIDFeatureFlags.SetFeatureFlags(const Value: TCPUIDFeatureFlagSet);
begin
  if (FFeatureFlags <> Value) then
  begin
    FFeatureFlags := Value;
    Changed;
  end;
end;
{$ENDREGION}

{$REGION 'Class: TX86Registers'}
procedure TX86Registers.AssignTo(Dest: TPersistent);
var
  D: TX86Registers;
begin
  if (Dest is TX86Registers) then
  begin
    D := Dest as TX86Registers;
    D.SetRegisters(FRegisters);
  end else inherited;
end;

procedure TX86Registers.Changed;
begin
  FDefinition.UpdateValues;
end;

constructor TX86Registers.Create(Definition: TInstructionDefinition);
begin
  inherited Create;
  FDefinition := Definition;
end;

function TX86Registers.Equals(const Value: TX86Registers): Boolean;
begin
  Result := (Value.FRegisters = FRegisters);
end;

procedure TX86Registers.LoadFromJSON(JSON: PJSONVariantData; const FieldName: String);
begin
  SetRegisters(TJSONSetHelper<TX86RegisterSet>.ReadValue(JSON, FieldName, SX86Register));
end;

procedure TX86Registers.SaveToJSON(JSON: PJSONVariantData; const FieldName: String);
begin
  TJSONSetHelper<TX86RegisterSet>.WriteValue(JSON, FieldName, SX86Register, FRegisters);
end;

procedure TX86Registers.SetRegisters(const Value: TX86RegisterSet);
begin
  if (FRegisters <> Value) then
  begin
    FRegisters := Value;
    Changed;
  end;
end;
{$ENDREGION}

{$REGION 'Class: TX86Flags'}
procedure TX86Flags.AssignTo(Dest: TPersistent);
var
  D: TX86Flags;
  I: Integer;
begin
  if (Dest is TX86Flags) then
  begin
    D := Dest as TX86Flags;
    for I := 0 to GetFlagCount - 1 do
    begin
      D.SetValue(I, GetValue(I));
    end;
    D.Changed;
  end else inherited;
end;

procedure TX86Flags.Changed;
begin
  FDefinition.UpdateValues;
end;

constructor TX86Flags.Create(Definition: TInstructionDefinition);
begin
  inherited Create;
  FDefinition := Definition;
  // NOTE: Some instructions clear all flags in the FLAGS/EFLAGS/RFLAGS register except some.
  //       If you add a new flag field to this struct, you have to set it to fvReset for all these
  //       instructions
end;

function TX86Flags.Equals(const Value: TX86Flags): Boolean;
var
  I: Integer;
begin
  Result := true;
  for I := 0 to GetFlagCount - 1 do
  begin
    if (GetValue(I) <> Value.GetValue(I)) then
    begin
      Result := false;
      Break;
    end;
  end;
end;

function TX86Flags.GetConflictState: Boolean;
var
  I: Integer;
  S: TX86FlagBehaviorSet;
  F: TX86FlagBehavior;
  RegsRead,
  RegsWrite: TX86RegisterSet;
  R: TX86Register;
begin
  Result := false;
  RegsRead := [];
  RegsWrite := [];
  for I := 0 to GetFlagCount - 1 do
  begin
    S := GetValue(I);

    // Write operations are mutally exclusive
    if (not (Ord(fvModified in S) + Ord(fvReset in S) + Ord(fvSet in S) + Ord(fvUndefined in S) in
      [Ord(false), Ord(true)])) then
    begin
      Exit(true);
    end;

    for F in S do
    begin
      if (F in [fvTested]) then
      begin
        if (I < 9) then
        begin
          // These flags are in the FLAGS register
          Include(RegsRead, regFLAGS);
        end else
        begin
          // These flags are in the EFLAGS register
          Include(RegsRead, regEFLAGS);
        end;
      end;
      if (F in [fvModified, fvReset, fvSet, fvUndefined]) then
      begin
        if (I < 9) then
        begin
          // These flags are in the FLAGS register
          Include(RegsWrite, regFLAGS);
        end else
        begin
          // These flags are in the EFLAGS register
          Include(RegsWrite, regEFLAGS);
        end;
      end;
    end;
  end;

  if (regEFLAGS in RegsWrite) then Exclude(RegsWrite, regFLAGS);
  if (regEFLAGS in RegsRead)  then Exclude(RegsRead, regFLAGS);

  for R := regRFLAGS to regFLAGS do
  begin
    if ((R in RegsRead) xor (R in FDefinition.ImplicitRead.Registers)) or
      ((R in RegsWrite) xor (R in FDefinition.ImplicitWrite.Registers)) then
    begin
      Exit(true);
    end;
  end;
end;

function TX86Flags.GetFlagCount: Integer;
begin
  Result := Length(FFlags);
end;

function TX86Flags.GetFlagName(Index: Integer): String;
begin
  Result := '';
  case Index of
     0: Result := 'cf';
     1: Result := 'pf';
     2: Result := 'af';
     3: Result := 'zf';
     4: Result := 'sf';
     5: Result := 'tf';
     6: Result := 'if';
     7: Result := 'df';
     8: Result := 'of';
     9: Result := 'iopl';
    10: Result := 'nt';
    11: Result := 'rf';
    12: Result := 'vm';
    13: Result := 'ac';
    14: Result := 'vif';
    15: Result := 'vip';
    16: Result := 'id';
  end;
end;

function TX86Flags.GetFlagPointer(Index: Integer): PX86FlagBehaviorSet;
begin
  Result := @FFlags[Index];
end;

function TX86Flags.GetValue(Index: Integer): TX86FlagBehaviorSet;
begin
  Result := GetFlagPointer(Index)^;
end;

procedure TX86Flags.LoadFromJSON(JSON: PJSONVariantData; const FieldName: String);
var
  C: PJSONVariantData;
  I: Integer;
begin
  C := JSON.Data(FieldName);
  if (Assigned(C)) then
  begin
    if (C^.Kind <> jvObject) then
    begin
      raise Exception.CreateFmt('The "%s" field is not a valid JSON object.', [FieldName]);
    end;
    for I := 0 to GetFlagCount - 1 do
    begin
      GetFlagPointer(I)^ :=
        TJSONSetHelper<TX86FlagBehaviorSet>.ReadValue(C, GetFlagName(I), SX86FlagBehavior);
    end;
    Changed;
  end;
end;

procedure TX86Flags.SaveToJSON(JSON: PJSONVariantData; const FieldName: String);
var
  F: TX86FlagBehavior;
  J, A: TJSONVariantData;
  I: Integer;
begin
  J.Init;
  for I := 0 to GetFlagCount - 1 do
  begin
    A.Init;
    for F in GetValue(I) do
    begin
      A.AddValue(SX86FlagBehavior[F]);
    end;
    if (A.Count > 0) then
    begin
      J.AddNameValue(GetFlagName(I), Variant(A));
    end;
  end;
  if (J.Count > 0) then
  begin
    JSON.AddNameValue(FieldName, Variant(J));
  end;
end;

procedure TX86Flags.SetValue(Index: Integer; const Value: TX86FlagBehaviorSet);
var
  Flag: PX86FlagBehaviorSet;
begin
  Flag := GetFlagPointer(Index);
  if (Flag^ <> Value) then
  begin
    Flag^ := Value;
    Changed;
  end;
end;
{$ENDREGION}

{$REGION 'Class: TInstructionOperand'}
procedure TInstructionOperand.AssignTo(Dest: TPersistent);
var
  D: TInstructionOperand;
begin
  if (Dest is TInstructionOperand) then
  begin
    D := Dest as TInstructionOperand;
    D.FType := FType;
    D.FEncoding := FEncoding;
    D.FAction := FAction;
    D.Changed;
  end else inherited;
end;

procedure TInstructionOperand.Changed;
begin
  FOperands.Changed;
end;

constructor TInstructionOperand.Create(Operands: TInstructionOperands);
begin
  inherited Create;
  FOperands := Operands;
end;

function TInstructionOperand.Equals(const Value: TInstructionOperand): Boolean;
begin
  Result :=
    (Value.FType = FType) and (Value.FEncoding = FEncoding) and (Value.FAction = FAction);
end;

function TInstructionOperand.GetConflictState: Boolean;
begin
  Result := false;
  case FType of
    optGPR8,
    optGPR16:
      Result := not (FEncoding in [opeModrmReg, opeModrmRm, opeOpcodeBits]);
    optGPR32,
    optGPR64:
      Result := not (FEncoding in [opeModrmReg, opeModrmRm, opeOpcodeBits, opeVexVVVV]);
    optFPR:
      Result := not (FEncoding in [opeModrmRm]);
    optVR64:
      Result := not (FEncoding in [opeModrmReg, opeModrmRm]);
    optVR128,
    optVR256,
    optVR512:
      Result := not (FEncoding in [opeModrmReg, opeModrmRm, opeVexVVVV, opeImm8Hi, opeModrmRmCD1,
        opeModrmRmCD2, opeModrmRmCD4, opeModrmRmCD8, opeModrmRmCD16, opeModrmRmCD32,
        opeModrmRmCD64]);
    optTR,
    optCR,
    optDR,
    optSREG:
      Result := not (FEncoding in [opeModrmReg]);
    optMSKR:
      Result := not (FEncoding in [opeModrmReg, opeModrmRm, opeVexVVVV]);
    optBNDR:
      Result := not (FEncoding in [opeModrmReg, opeModrmRm]);
    optMem:
      Result := not (FEncoding in [opeModrmRm]);
    optMem8,
    optMem16,
    optMem32,
    optMem64:
      Result := not (FEncoding in [opeModrmRm, opeModrmRmCD1, opeModrmRmCD2, opeModrmRmCD4,
        opeModrmRmCD8, opeModrmRmCD16, opeModrmRmCD32, opeModrmRmCD64]);
    optMem80:
      Result := not (FEncoding in [opeModrmRm]);
    optMem128,
    optMem256,
    optMem512:
      Result := not (FEncoding in [opeModrmRm, opeModrmRmCD1, opeModrmRmCD2, opeModrmRmCD4,
        opeModrmRmCD8, opeModrmRmCD16, opeModrmRmCD32, opeModrmRmCD64]);
    optMem32Bcst2,
    optMem32Bcst4,
    optMem32Bcst8,
    optMem32Bcst16,
    optMem64Bcst2,
    optMem64Bcst4,
    optMem64Bcst8,
    optMem64Bcst16:
      Result := not (FEncoding in [opeModrmRmCD1, opeModrmRmCD2, opeModrmRmCD4, opeModrmRmCD8,
        opeModrmRmCD16, opeModrmRmCD32, opeModrmRmCD64]);
    optMem32VSIBX,
    optMem32VSIBY,
    optMem32VSIBZ,
    optMem64VSIBX,
    optMem64VSIBY,
    optMem64VSIBZ:
      Result := not (FEncoding in [opeModrmRm, opeModrmRmCD1, opeModrmRmCD2, opeModrmRmCD4,
        opeModrmRmCD8, opeModrmRmCD16, opeModrmRmCD32, opeModrmRmCD64]);
    optMem1616,
    optMem1632,
    optMem1664,
    optMem112,
    optMem224:
      Result := not (FEncoding in [opeModrmRm]);
    optImm8,
    optImm8U:
      Result := not (FEncoding in [opeImm8, opeImm8Lo]);
    optImm16:
      Result := not (FEncoding in [opeImm8, opeImm16]);
    optImm32:
      Result := not (FEncoding in [opeImm8, opeImm32]);
    optImm64:
      Result := not (FEncoding in [opeImm8, opeImm32, opeImm64]);
    optRel8:
      Result := not (FEncoding in [opeImm8]);
    optRel16:
      Result := not (FEncoding in [opeImm8, opeImm16]);
    optRel32:
      Result := not (FEncoding in [opeImm8, opeImm32]);
    optRel64:
      Result := not (FEncoding in [opeImm8, opeImm32, opeImm64]);
    optPtr1616,
    optPtr1632,
    optPtr1664,
    optMoffs16,
    optMoffs32,
    optMoffs64,
    optSrcIndex8,
    optSrcIndex16,
    optSrcIndex32,
    optSrcIndex64,
    optDstIndex8,
    optDstIndex16,
    optDstIndex32,
    optDstIndex64,
    optFixed1,
    optFixedAL,
    optFixedCL,
    optFixedAX,
    optFixedDX,
    optFixedEAX,
    optFixedRAX,
    optFixedST0,
    optFixedES,
    optFixedSS,
    optFixedCS,
    optFixedDS,
    optFixedFS,
    optFixedGS:
      Result := not (FEncoding in [opeNone]);
  end;
end;

function TInstructionOperand.GetDescription(IncludeAccessMode: Boolean): String;
begin
  if (GetConflictState) then
  begin
    Result := 'invalid';
    Exit;
  end;
  Result := '';
  if (FType <> optUnused) then
  begin
    case FType of
      optGPR8      : Result := 'GPR8';
      optGPR16     : Result := 'GPR16';
      optGPR32     : Result := 'GPR32';
      optGPR64     : Result := 'GPR64';
      optFPR       : Result := 'ST(i)';
      optVR64      : Result := 'MM64';
      optVR128     : Result := 'XMM128';
      optVR256     : Result := 'YMM256';
      optVR512     : Result := 'ZMM512';
      optMSKR      : Result := 'MASK';
      optBNDR      : Result := 'BND';
      optTR        : Result := 'TR';
      optCR        : Result := 'CR';
      optDR        : Result := 'DR';
      optMem       : Result := 'mem';
      optMem8      : Result := 'mem8';
      optMem16     : Result := 'mem16';
      optMem32     : Result := 'mem32';
      optMem64     : Result := 'mem64';
      optMem80     : Result := 'mem80';
      optMem128    : Result := 'mem128';
      optMem256    : Result := 'mem256';
      optMem512    : Result := 'mem512';
      optMem32Bcst2: Result := 'mem32bcst2';
      optMem32Bcst4: Result := 'mem32bcst4';
      optMem32Bcst8: Result := 'mem32bcst8';
      optMem32Bcst16: Result := 'mem32bcst16';
      optMem64Bcst2: Result := 'mem64bcst2';
      optMem64Bcst4: Result := 'mem64bcst4';
      optMem64Bcst8: Result := 'mem64bcst8';
      optMem64Bcst16: Result := 'mem64bcst16';
      optMem112    : Result := 'mem112';
      optMem224    : Result := 'mem224';
      optImm8      : Result := 'imm8';
      optImm16     : Result := 'imm16';
      optImm32     : Result := 'imm32';
      optImm64     : Result := 'imm64';
      optImm8U     : Result := 'imm8u';
      optRel8      : Result := 'rel8';
      optRel16     : Result := 'rel16';
      optRel32     : Result := 'rel32';
      optRel64     : Result := 'rel64';
      optPtr1616   : Result := 'ptr16:16';
      optPtr1632   : Result := 'ptr16:32';
      optPtr1664   : Result := 'ptr16:64';
      optMoffs16   : Result := 'moffs16';
      optMoffs32   : Result := 'moffs32';
      optMoffs64   : Result := 'moffs64';
      optSrcIndex8 : Result := 'srcidx8';
      optSrcIndex16: Result := 'srcidx16';
      optSrcIndex32: Result := 'srcidx32';
      optSrcIndex64: Result := 'srcidx64';
      optDstIndex8 : Result := 'dstidx8';
      optDstIndex16: Result := 'dstidx16';
      optDstIndex32: Result := 'dstidx32';
      optDstIndex64: Result := 'dstidx64';
      optSREG      : Result := 'SEG';
      optMem1616   : Result := 'mem16:16';
      optMem1632   : Result := 'mem16:32';
      optMem1664   : Result := 'mem16:64';
      optMem32VSIBX : Result := 'mem32vsibx';
      optMem32VSIBY : Result := 'mem32vsiby';
      optMem32VSIBZ : Result := 'mem32vsibz';
      optMem64VSIBX : Result := 'mem64vsibx';
      optMem64VSIBY : Result := 'mem64vsiby';
      optMem64VSIBZ : Result := 'mem64vsibz';
      optFixed1    : Result := '1';
      optFixedAL   : Result := 'AL';
      optFixedCL   : Result := 'CL';
      optFixedAX   : Result := 'AX';
      optFixedDX   : Result := 'DX';
      optFixedEAX  : Result := 'EAX';
      optFixedECX  : Result := 'ECX';
      optFixedRAX  : Result := 'RAX';
      optFixedES   : Result := 'ES';
      optFixedCS   : Result := 'CS';
      optFixedSS   : Result := 'SS';
      optFixedDS   : Result := 'DS';
      optFixedGS   : Result := 'GS';
      optFixedFS   : Result := 'FS';
      optFixedST0  : Result := 'ST0';
    end;
    if (IncludeAccessMode) then
    begin
      case FAction of
        opaRead         : Result := Result + ' (r)';
        opaWrite        : Result := Result + ' (w)';
        opaReadWrite    : Result := Result + ' (r, w)';
        opaCondRead     : Result := Result + ' (r?)';
        opaCondWrite    : Result := Result + ' (w?)';
        opaReadCondWrite: Result := Result + ' (r, w?)';
        opaWriteCondRead: Result := Result + ' (r?, w)';
      end;
    end;
  end;
end;

procedure TInstructionOperand.LoadFromJSON(JSON: PJSONVariantData; const FieldName: String);
var
  V: PJSONVariantData;
begin
  V := JSON^.Data(FieldName);
  if Assigned(V) then
  begin
    if (V^.Kind <> jvObject) then
    begin
      raise Exception.CreateFmt('The "%s" field is not a valid JSON object.', [FieldName]);
    end;
    SetType(TJSONEnumHelper<TOperandType>.ReadValue(
      V, 'type', SOperandType));
    SetEncoding(TJSONEnumHelper<TOperandEncoding>.ReadValue(
      V, 'encoding', SOperandEncoding));
    SetAction(TJSONEnumHelper<TOperandAction>.ReadValue(
      V, 'action', SOperandAction));
  end;
end;

procedure TInstructionOperand.SaveToJSON(JSON: PJSONVariantData; const FieldName: String);
var
  V: TJSONVariantData;
begin
  if (FType <> optUnused) then
  begin
    V.Init;
    V.AddNameValue('type', SOperandType[FType]);
    if (FEncoding <> opeNone) then
      V.AddNameValue('encoding', SOperandEncoding[FEncoding]);
    if (FAction   <> opaRead) then
      V.AddNameValue('action',   SOperandAction[FAction]);
    JSON^.AddNameValue(FieldName, Variant(V));
  end;
end;

procedure TInstructionOperand.SetAction(const Value: TOperandAction);
begin
  if (FAction <> Value) then
  begin
    FAction := Value;
    Changed;
  end;
end;

procedure TInstructionOperand.SetEncoding(const Value: TOperandEncoding);
begin
  if (FEncoding <> Value) then
  begin
    FEncoding := Value;
    Changed;
  end;
end;

procedure TInstructionOperand.SetType(const Value: TOperandType);
begin
  if (FType <> Value) then
  begin
    case Value of
      optGPR8: ;
      optGPR16: ;
      optGPR32: ;
      optGPR64: ;
      optVR64: ;
      optVR128: ;
      optVR256: ;
      optVR512: ;
      optFPR:
        FEncoding := opeModrmRm;
      optTR,
      optCR,
      optDR:
        FEncoding := opeModrmReg;
      optSREG: ;
      optMSKR: ;
      optBNDR: ;
      optMem: ;
      optMem8: ;
      optMem16: ;
      optMem32: ;
      optMem64: ;
      optMem80: ;
      optMem128: ;
      optMem256: ;
      optMem512: ;
      optMem32Bcst2: ;
      optMem32Bcst4: ;
      optMem32Bcst8: ;
      optMem32Bcst16: ;
      optMem64Bcst2: ;
      optMem64Bcst4: ;
      optMem64Bcst8: ;
      optMem64Bcst16: ;
      optMem32VSIBX: ;
      optMem32VSIBY: ;
      optMem32VSIBZ: ;
      optMem64VSIBX: ;
      optMem64VSIBY: ;
      optMem64VSIBZ: ;
      optMem1616: ;
      optMem1632: ;
      optMem1664: ;
      optMem112: ;
      optMem224: ;
      optImm8: ;
      optImm8U: ;
      optImm16: ;
      optImm32: ;
      optImm64: ;
      optRel8: ;
      optRel16: ;
      optRel32: ;
      optRel64: ;
      optPtr1616: ;
      optPtr1632: ;
      optPtr1664: ;
      optMoffs16: ;
      optMoffs32: ;
      optMoffs64: ;
      optSrcIndex8: ;
      optSrcIndex16: ;
      optSrcIndex32: ;
      optSrcIndex64: ;
      optDstIndex8: ;
      optDstIndex16: ;
      optDstIndex32: ;
      optDstIndex64: ;
      optFixed1: ;
      optFixedAL: ;
      optFixedCL: ;
      optFixedAX: ;
      optFixedDX: ;
      optFixedEAX: ;
      optFixedECX: ;
      optFixedRAX: ;
      optFixedST0: ;
      optFixedES: ;
      optFixedSS: ;
      optFixedCS: ;
      optFixedDS: ;
      optFixedFS: ;
      optFixedGS: ;
    end;
    {case Value of
      optUnused:
        FEncoding := opeNone;
      optGPR8,
      optGPR16,
      optGPR32,
      optGPR64,
      optVR64,
      optVR128,
      optVR256,
      optVR512,
      optBNDR,
      optCR,
      optDR:
        if (FEncoding <> opeModrmRm) then
        begin
          FEncoding := opeModrmReg;
        end;
      optMSKR:
        if (FEncoding <> opeModrmRm) and (FEncoding <> opeVexVVVV) then
        begin
          FEncoding := opeModrmReg;
        end;
      optFPR:
        FEncoding := opeModrmRm;
      optMem,
      optMem8,
      optMem16,
      optMem32,
      optMem64,
      optMem80,
      optMem128,
      optMem256,
      optMem512,
      optMem1616,
      optMem1632,
      optMem1664,
      optMem32VSIBX,
      optMem32VSIBY,
      optMem32VSIBZ,
      optMem64VSIBX,
      optMem64VSIBY,
      optMem64VSIBZ,
      optMem32Bcst2,
      optMem32Bcst4,
      optMem32Bcst8,
      optMem32Bcst16,
      optMem64Bcst2,
      optMem64Bcst4,
      optMem64Bcst8,
      optMem64Bcst16,
      optMem112,
      optMem224:
        if not (FEncoding in [opeModrmRm, opeModrmRmCD1, opeModrmRmCD2, opeModrmRmCD4,
          opeModrmRmCD8, opeModrmRmCD16, opeModrmRmCD32, opeModrmRmCD64]) then
        begin
          FEncoding := opeModrmRm;
        end;
      optImm8:
        FEncoding := opeImm8;
      optImm16:
        FEncoding := opeImm16;
      optImm32:
        FEncoding := opeImm32;
      optImm64:
        if (FEncoding <> opeImm32) then
        begin
          FEncoding := opeImm64;
        end;
      optImm8U:
        FEncoding := opeImm8;
      optRel8:
        FEncoding := opeImm8;
      optRel16:
        FEncoding := opeImm16;
      optRel32:
        FEncoding := opeImm32;
      optRel64:
        if (FEncoding <> opeImm32) then // TODO: ?
        begin
          FEncoding := opeImm64;
        end;
      optPtr1616,
      optPtr1632,
      optPtr1664:
        FEncoding := opeNone;
      optMoffs16,
      optMoffs32,
      optMoffs64:
        FEncoding := opeNone;
      optSREG:
        FEncoding := opeModrmReg;
      optSrcIndex8,
      optSrcIndex16,
      optSrcIndex32,
      optSrcIndex64,
      optDstIndex8,
      optDstIndex16,
      optDstIndex32,
      optDstIndex64,
      optFixed1,
      optFixedAL,
      optFixedCL,
      optFixedAX,
      optFixedDX,
      optFixedEAX,
      optFixedRAX,
      optFixedCS,
      optFixedSS,
      optFixedDS,
      optFixedES,
      optFixedFS,
      optFixedGS,
      optFixedST0:
        FEncoding := opeNone;
    end;}
    FType := Value;
    Changed;
  end;
end;
{$ENDREGION}

{$REGION 'Class: TInstructionOperands'}
procedure TInstructionOperands.AssignTo(Dest: TPersistent);
var
  D: TInstructionOperands;
  I: Integer;
begin
  if (Dest is TInstructionOperands) then
  begin
    D := Dest as TInstructionOperands;
    for I := Low(FOperands) to High(FOperands) do
    begin
      D.FOperands[I].Assign(FOperands[I]);
    end;
    D.Changed;
  end else inherited;
end;

procedure TInstructionOperands.Changed;
begin
  FDefinition.UpdateValues;
end;

constructor TInstructionOperands.Create(Definition: TInstructionDefinition);
var
  I: Integer;
begin
  inherited Create;
  FDefinition := Definition;
  for I := Low(FOperands) to High(FOperands) do
  begin
    FOperands[I] := TInstructionOperand.Create(Self);
  end;
end;

destructor TInstructionOperands.Destroy;
var
  I: Integer;
begin
  for I := Low(FOperands) to High(FOperands) do
  begin
    FOperands[I].Free;
  end;
  inherited;
end;

function TInstructionOperands.Equals(const Value: TInstructionOperands): Boolean;
var
  I: Integer;
begin
  Result := true;
  for I := Low(FOperands) to High(FOperands) do
  begin
    if (not Value.FOperands[I].Equals(FOperands[I])) then
    begin
      Result := false;
      Break;
    end;
  end;
end;

function TInstructionOperands.GetConflictState: Boolean;
var
  I: Integer;
  EncReg, EncRm, EncVVVV, EncAAA: Integer;
begin
  {var
  A: array[0..3] of TInstructionOperand;
  I, J: Integer;
begin
  FHasConflicts := false;

  // Check for invalid operand order
  A[0] := FOperandA; A[1] := FOperandB; A[2] := FOperandC; A[3] := FOperandD;
  for I := High(A) downto Low(A) do
  begin
    if (A[I].OperandType <> otUnused) then
    begin
      for J := I downto Low(A) do
      begin
        if (A[J].OperandType = otUnused) then
        begin
          FHasConflicts := true;
          Break;
        end;
      end;
    end;
    if (FHasConflicts) then
    begin
      Break;
    end;
  end; }
  Result := false;
  for I := Low(FOperands) to High(FOperands) do
  begin
    Result := Result or FOperands[I].HasConflicts;
  end;
  if (not Result) then
  begin
    EncReg := 0; EncRm := 0; EncVVVV := 0; EncAAA := 0;
    for I := 0 to 3 do
    begin
      case GetOperandById(I).Encoding of
        opeModrmReg   : Inc(EncReg);
        opeModrmRm,
        opeModrmRmCD1,
        opeModrmRmCD2,
        opeModrmRmCD4,
        opeModrmRmCD8,
        opeModrmRmCD16,
        opeModrmRmCD32,
        opeModrmRmCD64: Inc(EncRm);
        opeVexVVVV    : Inc(EncVVVV);
        opeEvexAAA    : Inc(EncAAA);
      end;
      if (EncReg > 1) or (EncRm > 1) or (EncVVVV > 1) or (EncAAA > 1) then
      begin
        Result := true;
        Break;
      end;
    end;
    if (FDefinition.OpcodeExtensions.ModrmMod <> mdNeutral) and (EncReg > 0) and (EncRm = 0) then
    begin
      Exit(true)
    end
    // TODO: Check operand order, ...
  end;
end;

function TInstructionOperands.GetOperandById(Id: Integer): TInstructionOperand;
begin
  Result := FOperands[Id];
end;

function TInstructionOperands.GetOperandCount: Integer;
begin
  Result := Length(FOperands);
end;

function TInstructionOperands.GetOperandsUsed: Integer;
begin
  Result := 0;
  while ((Result < Length(FOperands)) and (FOperands[Result].OperandType <> optUnused)) do
  begin
    Inc(Result);
  end;
end;

procedure TInstructionOperands.LoadFromJSON(JSON: PJSONVariantData; const FieldName: String);
var
  V: PJSONVariantData;
  I: Integer;
begin
  V := JSON^.Data(FieldName);
  if Assigned(V) then
  begin
    if (V^.Kind <> jvObject) then
    begin
      raise Exception.CreateFmt('The "%s" field is not a valid JSON object.', [FieldName]);
    end;
    for I := Low(FOperands) to High(FOperands) do
    begin
      FOperands[I].LoadFromJSON(V, 'operand' + IntToStr(I + 1));
    end;
  end;
end;

procedure TInstructionOperands.SaveToJSON(JSON: PJSONVariantData; const FieldName: String);
var
  V: TJSONVariantData;
  I: Integer;
begin
  V.Init;
  for I := Low(FOperands) to High(FOperands) do
  begin
    FOperands[I].SaveToJSON(@V, 'operand' + IntToStr(I + 1));
  end;
  if (V.Count > 0) then
  begin
    JSON^.AddNameValue('operands', Variant(V));
  end;
end;
{$ENDREGION}

{$REGION 'Class: TInstructionDefinition'}
procedure TInstructionDefinition.AssignTo(Dest: TPersistent);
var
  D: TInstructionDefinition;
begin
  if (Dest is TInstructionDefinition) then
  begin
    D := Dest as TInstructionDefinition;
    D.BeginUpdate;
    try
      D.FMnemonic := FMnemonic;
      D.FEncoding := FEncoding;
      D.FOpcodeMap := FOpcodeMap;
      D.FOpcode := FOpcode;
      D.FExtensions.Assign(FExtensions);
      D.FCPUID.Assign(FCPUID);
      D.FOperands.Assign(FOperands);
      D.FFlags := FFlags;
      D.FImplicitRead.Assign(FImplicitRead);
      D.FImplicitWrite.Assign(FImplicitWrite);
      D.FX86Flags.Assign(FX86Flags);
      D.FEVEXCD8Scale := FEVEXCD8Scale;
      D.FComment := FComment;
      D.Update;
    finally
      D.EndUpdate;
    end;
  end else inherited;
end;

procedure TInstructionDefinition.BeginUpdate;
begin
  Inc(FUpdateCount);
end;

constructor TInstructionDefinition.Create(Editor: TInstructionEditor; const Mnemonic: String);
begin
  inherited Create;
  FEditor := Editor;
  if (Mnemonic = '') then
  begin
    raise Exception.Create('Mnemonic can not be empty.');
  end;
  FMnemonic := Mnemonic;
  FExtensions := TOpcodeExtensions.Create(Self);
  FCPUID := TCPUIDFeatureFlags.Create(Self);
  FOperands := TInstructionOperands.Create(Self);
  FImplicitRead := TX86Registers.Create(Self);
  FImplicitWrite := TX86Registers.Create(Self);
  FX86Flags := TX86Flags.Create(Self);
  // Insert definition into the definition list. This method does NOT insert the definition into
  // the table structure
  FEditor.RegisterDefinition(Self);
end;

destructor TInstructionDefinition.Destroy;
begin
  // Remove definition from the filter structure
  if (Assigned(FParent)) then
  begin
    FEditor.RemoveDefinition(Self);
  end;
  // Remove definition from the definition list
  FEditor.UnregisterDefinition(Self);
  FExtensions.Free;
  FCPUID.Free;
  FOperands.Free;
  FImplicitRead.Free;
  FImplicitWrite.Free;
  FX86Flags.Free;
  inherited;
end;

procedure TInstructionDefinition.EndUpdate;
begin
  if (FUpdateCount > 0) then
  begin
    Dec(FUpdateCount);
  end;
  if (FUpdateCount = 0) then
  begin
    if (FDoUpdatePosition) then
    begin
      UpdatePosition;
      FDoUpdatePosition := false;
    end;
    if (FDoUpdateValues) then
    begin
      UpdateValues;
      FDoUpdateValues := false;
    end;
  end;
end;

function TInstructionDefinition.Equals(const Value: TInstructionDefinition;
  CheckComment: Boolean; CheckFilterRelatedAttributes: Boolean): Boolean;
begin
  Result :=
    (Value.FMnemonic = FMnemonic) and ((not CheckFilterRelatedAttributes) or
    ((Value.FEncoding = FEncoding) and (Value.FOpcodeMap = FOpcodeMap) and
    (Value.FOpcode = FOpcode) and (Value.FExtensions.Equals(FExtensions)))) and
    (Value.FCPUID.Equals(FCPUID)) and (Value.FOperands.Equals(FOperands)) and
    (Value.FFlags = FFlags) and (Value.FEVEXCD8Scale = FEVEXCD8Scale) and
    (Value.FImplicitRead.Equals(FImplicitRead)) and
    (Value.FImplicitWrite.Equals(FImplicitWrite)) and (Value.FX86Flags.Equals(FX86Flags)) and
    ((not CheckComment) or (Value.FComment = FComment));
end;

function TInstructionDefinition.GetConflictState: Boolean;
begin
  Result := (FConflicts <> []);
end;

procedure TInstructionDefinition.LoadFromJSON(JSON: PJSONVariantData);
var
  I: Integer;
begin
  BeginUpdate;
  try
    if (VarIsClear(JSON^.Value['mnemonic']) or (JSON^.Value['mnemonic'] = '')) then
    begin
      raise Exception.Create('The "mnemonic" field can not be empty.');
    end;
    SetMnemonic(JSON^.Value['mnemonic']);
    SetEncoding(TJSONEnumHelper<TInstructionEncoding>.ReadValue(
      JSON, 'encoding', SInstructionEncoding));
    SetOpcodeMap(TJSONEnumHelper<TOpcodeMap>.ReadValue(
      JSON, 'map', SOpcodeMap));
    if (VarIsClear(JSON^.Value['opcode']) or
      (not TryStrToInt('$' + JSON^.Value['opcode'], I))) or (I < 0) or (I >= 256) then
    begin
      raise Exception.Create('The "opcode" field does not contain a valid hexadecimal byte value.');
    end;
    SetOpcode(I);

    FEVEXCD8Scale := JSON^.Value['cd8scale'];

    FExtensions.LoadFromJSON(JSON, 'extensions');
    FCPUID.LoadFromJSON(JSON, 'cpuid');
    FOperands.LoadFromJSON(JSON, 'operands');
    FImplicitRead.LoadFromJSON(JSON, 'implicit_read');
    FImplicitWrite.LoadFromJSON(JSON, 'implicit_write');
    SetFlags(TJSONSetHelper<TInstructionDefinitionFlags>.ReadValue(
      JSON, 'flags', SInstructionDefinitionFlag));
    SetPrefixFlags(TJSONSetHelper<TPrefixFlags>.ReadValue(
      JSON, 'prefix_flags', SPrefixFlag));
    FX86Flags.LoadFromJSON(JSON, 'x86flags');
    FComment := JSON^.Value['comment'];
  finally
    EndUpdate;
  end;
end;

procedure TInstructionDefinition.SaveToJSON(JSON: PJSONVariantData);
begin
  JSON^.AddNameValue('mnemonic', FMnemonic);
  JSON^.AddNameValue('opcode', LowerCase(IntToHex(FOpcode, 2)));
  if (FEncoding  <> ieDefault) then JSON^.AddNameValue('encoding', SInstructionEncoding[FEncoding]);
  if (FOpcodeMap <> omDefault) then JSON^.AddNameValue('map',      SOpcodeMap[FOpcodeMap]);
  FExtensions.SaveToJSON(JSON, 'extensions');
  FCPUID.SaveToJSON(JSON, 'cpuid');
  FOperands.SaveToJSON(JSON, 'operands');
  FImplicitRead.SaveToJSON(JSON, 'implicit_read');
  FImplicitWrite.SaveToJSON(JSON, 'implicit_write');
  TJSONSetHelper<TInstructionDefinitionFlags>.WriteValue(JSON, 'flags',
    SInstructionDefinitionFlag, FFlags);
  TJSONSetHelper<TPrefixFlags>.WriteValue(JSON, 'prefix_flags', SPrefixFlag, FPrefixFlags);
  FX86Flags.SaveToJSON(JSON, 'x86flags');
  if (FComment <> '') then
  begin
    JSON^.AddNameValue('comment', FComment);
  end;
  JSON^.AddNameValue('cd8scale', FEVEXCD8Scale);
end;

procedure TInstructionDefinition.SetComment(const Value: String);
begin
  if (FComment <> Value) then
  begin
    FComment := Value;
    UpdateValues;
  end;
end;

procedure TInstructionDefinition.SetEncoding(const Value: TInstructionEncoding);
begin
  if (FEncoding <> Value) then
  begin
    // TODO: Check exception cases
    case Value of
      ieDefault,
      ieVEX,
      ieEVEX:
        begin
          if (not (FOpcodeMap in [omDefault, om0F, om0F38, om0F3A])) then FOpcodeMap := omDefault;
        end;
      ie3DNow:
        begin
          if (FOpcodeMap <> om0F) then FOpcodeMap := om0F;
        end;
      ieXOP:
        begin
          if (not (FOpcodeMap in [omXOP8, omXOP9, omXOPA])) then FOpcodeMap := omXOP8;
        end;
    end;
    FEncoding := Value;
    UpdatePosition;
  end;
end;

procedure TInstructionDefinition.SetFlags(const Value: TInstructionDefinitionFlags);
begin
  if (FFlags <> Value) then
  begin
    FFlags := Value;
    UpdateValues;
  end;
end;

procedure TInstructionDefinition.SetMnemonic(const Value: String);
var
  S: String;
  C: Char;
begin
  S := '';
  for C in Value do
  begin
    if (CharInSet(C, ['a'..'z', 'A'..'Z', '0'..'9'])) then
    begin
      S := S + C;
    end;
  end;
  if (S = '') then
  begin
    raise Exception.Create('Mnemonic can not be empty.');
  end;
  if (FMnemonic <> S) then
  begin
    FMnemonic := LowerCase(S);
    UpdateValues;
  end;
end;

procedure TInstructionDefinition.SetOpcode(const Value: TOpcodeByte);
begin
  if (FOpcode <> Value) then
  begin
    FOpcode := Value;
    UpdatePosition;
  end;
end;

procedure TInstructionDefinition.SetOpcodeMap(const Value: TOpcodeMap);
var
  E: Boolean;
begin
  if (FOpcodeMap <> Value) then
  begin
    E := false;
    case FEncoding of
      ieDefault,
      ieVEX,
      ieEVEX  : E := (Value in [omXOP8, omXOP9, omXOPA]);
      ie3DNow : E := (Value <> om0F);
      ieXOP   : E := (Value in [omDefault, om0F, om0F38, om0F3A]);
    end;
    if (E) then
    begin
      raise Exception.Create('The current instruction encoding does not support this opcode map.');
    end;
    FOpcodeMap := Value;
    UpdatePosition;
  end;
end;

procedure TInstructionDefinition.SetParent(Parent: TDefinitionContainer);
begin
  // This method should ONLY be called by TInstructionDefinition.Create,
  // TInstructionFilter.InsertDefinition and TInstructionFilter.RemoveDefinition
  if (Assigned(FParent)) then
  begin
    if (HasConflicts) then
    begin
      FParent.DecInheritedConflictCount;
    end;
    FEditor.DefinitionRemoved(Self);
  end;
  FParent := Parent;
  if (Assigned(Parent)) then
  begin
    if (HasConflicts) then
    begin
      FParent.IncInheritedConflictCount;
    end;
    FEditor.DefinitionInserted(Self);
  end;
end;

procedure TInstructionDefinition.SetPrefixFlags(const Value: TPrefixFlags);
begin
  if (FPrefixFlags <> Value) then
  begin
    FPrefixFlags := Value;
    UpdateValues;
  end;
end;

procedure TInstructionDefinition.Update;
begin
  UpdatePosition;
  UpdateValues;
end;

procedure TInstructionDefinition.UpdateConflictFlags;
var
  Conflicts: TInstructionDefinitionConflicts;
begin
  Conflicts := [];
  if (ifForceConflict in FFlags) then
  begin
    Include(Conflicts, idcForcedConflict);
  end;
  if (FOperands.HasConflicts) then
  begin
    Include(Conflicts, idcOperands);
  end;

  // TODO: FExtensions.ModrmReg and FExtensions.ModrmRm requires FExtensions.ModrmMod <> mdNeutral

  if ((pfAcceptsXACQUIRE in FPrefixFlags) or (pfAcceptsXRELEASE in FPrefixFlags)) and
    (not ((pfAcceptsLock in FPrefixFlags) or (pfAcceptsHLEWithoutLock in FPrefixFlags))) then
  begin
    Include(Conflicts, idcPrefixFlags);
  end;
  if ((pfAcceptsXACQUIRE in FPrefixFlags) or (pfAcceptsXRELEASE in FPrefixFlags)) and
    ((pfAcceptsREP in FPrefixFlags) or (pfAcceptsREPEREPNE in FPrefixFlags)) then
  begin
    Include(Conflicts, idcPrefixFlags);
  end;
  if ((pfAcceptsLock in FPrefixFlags) or (pfAcceptsXACQUIRE in FPrefixFlags) or
    (pfAcceptsXRELEASE in FPrefixFlags)) and (not (FOperands.Operands[0].OperandType in [
    optMem8, optMem16, optMem32, optMem64, optMem128])) then
  begin
    Include(Conflicts, idcPrefixFlags);
  end;
  if ((pfAcceptsREP in FPrefixFlags) and (pfAcceptsREPEREPNE in FPrefixFlags)) then
  begin
    Include(Conflicts, idcPrefixFlags);
  end;
  if (pfAcceptsBranchHints in FPrefixFlags) and (not (FOperands.Operands[0].OperandType in [
    optRel8, optRel16, optRel32, optRel64])) then
  begin
    Include(Conflicts, idcPrefixFlags);
  end;

  if (FX86Flags.HasConflicts) then
  begin
    //Include(Conflicts, idcX86Flags);
  end;
  // TODO: Check for more conflicts
  if (FConflicts <> Conflicts) then
  begin
    if (Assigned(FParent)) then
    begin
      if (FConflicts = []) and (Conflicts <> []) then
      begin
        FParent.IncInheritedConflictCount;
      end else if (FConflicts <> []) and (Conflicts = []) then
      begin
        FParent.DecInheritedConflictCount;
      end;
    end;
    FConflicts := Conflicts;
  end;
end;

procedure TInstructionDefinition.UpdatePosition;
begin
  UpdateValues;
  if (FUpdateCount > 0) then
  begin
    FDoUpdatePosition := true;
  end else
  begin
    FEditor.InsertDefinition(Self);
  end;
end;

procedure TInstructionDefinition.UpdateValues;
begin
  if (FUpdateCount > 0) then
  begin
    FDoUpdateValues := true;
  end else
  begin
    UpdateConflictFlags;
    FEditor.DefinitionChanged(Self);
  end;
end;
{$ENDREGION}

{$REGION 'Class: TInstructionFilter'}
procedure TInstructionFilter.Changed;
begin
  // TODO: Implement BeginUpdate, EndUpdate to reduce Changed calls
  FEditor.FilterChanged(Self);
end;

constructor TInstructionFilter.Create(Editor: TInstructionEditor; Parent: TInstructionFilter;
  IsRootTable, IsStaticFilter: Boolean);
begin
  inherited Create;

  Assert(Assigned(Editor));
  Assert((not Assigned(Parent)) or
    (Assigned(Parent) and IsStaticFilter and (iffIsStaticFilter in Parent.FilterFlags)) or
    (Assigned(Parent) and (not IsStaticFilter)));

  FEditor := Editor;
  if (IsRootTable) then
  begin
    FFilterFlags := FFilterFlags + [iffIsRootTable];
  end;
  if (IsStaticFilter) then
  begin
    FFilterFlags := FFilterFlags + [iffIsStaticFilter];
  end;
  if (IsDefinitionContainer) then
  begin
    FFilterFlags := FFilterFlags + [iffIsDefinitionContainer];
    FDefinitions := TList<TInstructionDefinition>.Create;
  end else
  begin
    SetLength(FItems, GetCapacity);
  end;
  FEditor.FilterCreated(Self);
  SetParent(Parent);
end;

procedure TInstructionFilter.CreateFilterAtIndex(Index: Integer;
  FilterClass: TInstructionFilterClass; IsRootTable, IsStaticFilter: Boolean);
begin
  SetItem(Index, FilterClass.Create(FEditor, Self, IsRootTable, IsStaticFilter));
end;

procedure TInstructionFilter.DecInheritedConflictCount;
begin
  Dec(FInheritedConflicts);
  if (FInheritedConflicts = 0) then
  begin
    SetConflicts(FConflicts - [ifcInheritedConflict]);
    if (Assigned(FParent)) then
    begin
      FParent.DecInheritedConflictCount;
    end;
  end;
end;

destructor TInstructionFilter.Destroy;
begin
  Assert((FItemCount = 0) and (FParent = nil));
  if (Assigned(FDefinitions)) then
  begin
    Assert(FDefinitions.Count = 0);
    FDefinitions.Free;
  end;
  FEditor.FilterDestroyed(Self);
  inherited;
end;

class function TInstructionFilter.GetCapacity: Cardinal;
begin
  Result := 0;
end;

function TInstructionFilter.GetConflictState: Boolean;
begin
  Result := (FConflicts <> []);
end;

function TInstructionFilter.GetDefinition(const Index: Integer): TInstructionDefinition;
begin
  Assert((Index >= 0) and (Index < FDefinitions.Count));
  Result := FDefinitions[Index];
end;

function TInstructionFilter.GetDefinitionCount: Integer;
begin
  Result := 0;
  if Assigned(FDefinitions) then
  begin
    Result := FDefinitions.Count;
  end;
end;

class function TInstructionFilter.GetDescription: String;
begin
  Result := Self.ClassName;
end;

class function TInstructionFilter.GetInsertPosition(
  const Definition: TInstructionDefinition): Integer;
begin
  Result := -1;
end;

function TInstructionFilter.GetItem(const Index: Integer): TInstructionFilter;
begin
  Assert((Index >= 0) and (Index < Integer(GetCapacity)));
  Result := FItems[Index];
end;

class function TInstructionFilter.GetItemDescription(Index: Integer): String;
begin
  Result := '';
end;

class function TInstructionFilter.GetNeutralElementType: TNeutralElementType;
begin
  Result := netNotAvailable;
end;

procedure TInstructionFilter.IncInheritedConflictCount;
begin
  Inc(FInheritedConflicts);
  if (FInheritedConflicts = 1) then
  begin
    SetConflicts(FConflicts + [ifcInheritedConflict]);
    if (Assigned(FParent)) then
    begin
      FParent.IncInheritedConflictCount;
    end;
  end;
end;

function TInstructionFilter.IndexOf(const Filter: TInstructionFilter): Integer;
var
  I: Integer;
begin
  Result := -1;
  for I := Low(FItems) to High(FItems) do
  begin
    if (FItems[I] = Filter) then
    begin
      Result := I;
      Break;
    end;
  end;
end;

procedure TInstructionFilter.InsertDefinition(Definition: TInstructionDefinition);
begin
  Assert(IsDefinitionContainer);
  FDefinitions.Add(Definition);
  Definition.SetParent(Self as TDefinitionContainer);
  if (FDefinitions.Count = 2) then
  begin
    SetConflicts(FConflicts + [ifcDefinitionCount]);
    if (Assigned(FParent)) then
    begin
      FParent.IncInheritedConflictCount;
    end;
  end;
  Changed;
end;

class function TInstructionFilter.IsDefinitionContainer: Boolean;
begin
  Result := false;
end;

procedure TInstructionFilter.RemoveDefinition(Definition: TInstructionDefinition);
begin
  Assert(IsDefinitionContainer);
  Assert(FDefinitions.IndexOf(Definition) >= 0);
  if (FDefinitions.Count = 2) then
  begin
    SetConflicts(FConflicts - [ifcDefinitionCount]);
    if (Assigned(FParent)) then
    begin
      FParent.DecInheritedConflictCount;
    end;
  end;
  Definition.SetParent(nil);
  FDefinitions.Remove(Definition);
  Changed;
end;

procedure TInstructionFilter.SetConflicts(const Value: TInstructionFilterConflicts);
begin
  if (FConflicts <> Value) then
  begin
    FConflicts := Value;
    Changed;
  end;
end;

procedure TInstructionFilter.SetItem(const Index: Integer; const Value: TInstructionFilter);
begin
  Assert((Index >= 0) and (Index < Length(FItems)));
  if (FItems[Index] <> Value) then
  begin
    if (Assigned(Value) and (not Assigned(FItems[Index]))) then
    begin
      Inc(FItemCount);
    end else if (not Assigned(Value) and (Assigned(FItems[Index]))) then
    begin
      Dec(FItemCount);
    end;
    if (Assigned(FItems[Index])) then
    begin
      FItems[Index].SetParent(nil);
    end;
    FItems[Index] := Value;
    if (Assigned(Value)) then
    begin
      FItems[Index].SetParent(Self);
    end;
    // Update neutral element conflict
    if (GetNeutralElementType in [netPlaceholder]) then
    begin
      if (Assigned(FItems[0])) and (FItemCount > 1) then
      begin
        if (not (ifcNeutralElement in FConflicts)) then
        begin
          SetConflicts(FConflicts + [ifcNeutralElement]);
          if (Assigned(FParent)) then
          begin
            FParent.IncInheritedConflictCount;
          end;
        end;
      end else
      begin
        if (ifcNeutralElement in FConflicts) then
        begin
          SetConflicts(FConflicts - [ifcNeutralElement]);
          if (Assigned(FParent)) then
          begin
            FParent.DecInheritedConflictCount;
          end;
        end;
      end;
    end;
    Changed;
  end;
end;

procedure TInstructionFilter.SetParent(Parent: TInstructionFilter);
begin
  Assert((not Assigned(Parent)) or
    (Assigned(Parent) and (iffIsStaticFilter in FFilterFlags) and
    (iffIsStaticFilter in Parent.FilterFlags)) or (Assigned(Parent) and
    (not (iffIsStaticFilter in FFilterFlags))));
  if (FParent <> Parent) then
  begin
    if (Assigned(FParent)) then
    begin
      FEditor.FilterRemoved(Self);
      if (HasConflicts) then
      begin
        FParent.DecInheritedConflictCount;
      end;
    end;
    FParent := Parent;
    if (Assigned(Parent)) then
    begin
      FEditor.FilterInserted(Self);
      if (HasConflicts) then
      begin
        Parent.IncInheritedConflictCount;
      end;
    end;
    Changed;
  end;
end;
{$ENDREGION}

{$REGION 'Class: TDefinitionContainer'}
class function TDefinitionContainer.IsDefinitionContainer: Boolean;
begin
  Result := true;
end;
{$ENDREGION}

{$REGION 'Class: TInstructionEditor'}
procedure TInstructionEditor.BeginUpdate;
begin
  Inc(FUpdateCount);
  if (FUpdateCount = 1) and Assigned(FOnBeginUpdate) then
  begin
    FOnBeginUpdate(Self);
  end;
end;

constructor TInstructionEditor.Create;
begin
  inherited Create;
  FDefinitions := TList<TInstructionDefinition>.Create;
end;

class constructor TInstructionEditor.Create;
begin
  // Default filter order
  SetLength(FilterOrderDef, 8);
  FilterOrderDef[ 0]  := TModrmModFilter;
  FilterOrderDef[ 1]  := TModrmRegFilter;
  FilterOrderDef[ 2]  := TModrmRmFilter;
  FilterOrderDef[ 3]  := TModeFilter;
  FilterOrderDef[ 4]  := TRexWFilter;
  FilterOrderDef[ 5]  := TOperandSizeFilter;
  FilterOrderDef[ 6]  := TAddressSizeFilter;
  FilterOrderDef[ 7]  := TMandatoryPrefixFilter;
  // Specialized filter order for XOP instruction encoding
  SetLength(FilterOrderXOP, 8);
  FilterOrderXOP[ 0]  := TModrmModFilter;
  FilterOrderXOP[ 1]  := TModrmRegFilter;
  FilterOrderXOP[ 2]  := TModrmRmFilter;
  FilterOrderXOP[ 3]  := TModeFilter;
  FilterOrderXOP[ 4]  := TRexWFilter;
  FilterOrderXOP[ 5]  := TOperandSizeFilter;
  FilterOrderXOP[ 6]  := TAddressSizeFilter;
  FilterOrderXOP[ 7]  := TVexLFilter;
  // Specialized filter order for VEX instruction encoding
  SetLength(FilterOrderVEX, 9);
  FilterOrderVEX[ 0]  := TOpcodeFilter;
  FilterOrderVEX[ 1]  := TModrmModFilter;
  FilterOrderVEX[ 2]  := TModrmRegFilter;
  FilterOrderVEX[ 3]  := TModrmRmFilter;
  FilterOrderVEX[ 4]  := TModeFilter;
  FilterOrderVEX[ 5]  := TRexWFilter;
  FilterOrderVEX[ 6]  := TOperandSizeFilter;
  FilterOrderVEX[ 7]  := TAddressSizeFilter;
  FilterOrderVEX[ 8]  := TVexLFilter;
  // Specialized filter order for EVEX instruction encoding
  SetLength(FilterOrderEVEX, 11);
  FilterOrderEVEX[ 0] := TOpcodeFilter;
  FilterOrderEVEX[ 1] := TModrmModFilter;
  FilterOrderEVEX[ 2] := TModrmRegFilter;
  FilterOrderEVEX[ 3] := TModrmRmFilter;
  FilterOrderEVEX[ 4] := TModeFilter;
  FilterOrderEVEX[ 5] := TRexWFilter;
  FilterOrderEVEX[ 6] := TOperandSizeFilter;
  FilterOrderEVEX[ 7] := TAddressSizeFilter;
  FilterOrderEVEX[ 8] := TEvexBFilter;
  FilterOrderEVEX[ 9] := TVexLFilter;
  FilterOrderEVEX[10] := TEvexL2Filter;
end;

function TInstructionEditor.CreateDefinition(const Mnemonic: String): TInstructionDefinition;
begin
  Result := TInstructionDefinition.Create(Self, Mnemonic);
end;

procedure TInstructionEditor.DefinitionChanged(Definition: TInstructionDefinition);
begin
  if Assigned(FOnDefinitionChanged) then
  begin
    FOnDefinitionChanged(Self, Definition);
  end;
end;

procedure TInstructionEditor.DefinitionInserted(Definition: TInstructionDefinition);
begin
  if Assigned(FOnDefinitionInserted) then
  begin
    FOnDefinitionInserted(Self, Definition);
  end;
end;

procedure TInstructionEditor.DefinitionRemoved(Definition: TInstructionDefinition);
begin
  if Assigned(FOnDefinitionRemoved) then
  begin
    FOnDefinitionRemoved(Self, Definition);
  end;
end;

destructor TInstructionEditor.Destroy;

procedure DestroyChildFilters(Filter: TInstructionFilter);
var
  I: Integer;
  F: TInstructionFilter;
begin
  Assert(iffIsStaticFilter in Filter.FilterFlags);
  if (Filter.ItemCount > 0) then
  begin
    for I := 0 to Filter.Capacity - 1 do
    begin
      if (Assigned(Filter.Items[I])) then
      begin
        DestroyChildFilters(Filter.Items[I]);
        F := Filter.Items[I];
        Filter.SetItem(I, nil);
        F.Free;
      end;
    end;
  end;
end;

var
  I: Integer;
begin
  BeginUpdate;
  try
    if (Assigned(FDefinitions)) then
    begin
      FPreventDefinitionRemoval := true;
      for I := FDefinitions.Count - 1 downto 0 do
      begin
        FDefinitions[I].Free;
      end;
      FDefinitions.Free;
    end;
    if Assigned(FRootTable) then
    begin
      DestroyChildFilters(FRootTable);
      FRootTable.Free;
    end;
  finally
    EndUpdate;
  end;
  inherited;
end;

procedure TInstructionEditor.EndUpdate;
begin
  if (FUpdateCount > 0) then
  begin
    Dec(FUpdateCount);
  end;
  if (FUpdateCount = 0) then
  begin
    if Assigned(FOnEndUpdate) then
    begin
      FOnEndUpdate(Self);
    end;
  end;
end;

procedure TInstructionEditor.FilterChanged(Filter: TInstructionFilter);
begin
  if Assigned(FOnFilterChanged) then
  begin
    FOnFilterChanged(Self, Filter);
  end;
end;

procedure TInstructionEditor.FilterCreated(Filter: TInstructionFilter);
begin
  if Assigned(FOnFilterCreated) then
  begin
    FOnFilterCreated(Self, Filter);
  end;
end;

procedure TInstructionEditor.FilterDestroyed(Filter: TInstructionFilter);
begin
  if Assigned(FOnFilterDestroyed) then
  begin
    FOnFilterDestroyed(Self, Filter);
  end;
end;

procedure TInstructionEditor.FilterInserted(Filter: TInstructionFilter);
begin
  if (not Filter.IsDefinitionContainer) then Inc(FFilterCount);
  if Assigned(FOnFilterInserted) then
  begin
    FOnFilterInserted(Self, Filter);
  end;
end;

procedure TInstructionEditor.FilterRemoved(Filter: TInstructionFilter);
begin
  if (not Filter.IsDefinitionContainer) then Dec(FFilterCount);
  if Assigned(FOnFilterRemoved) then
  begin
    FOnFilterRemoved(Self, Filter);
  end;
end;

function TInstructionEditor.GetDefinition(const Index: Integer): TInstructionDefinition;
begin
  Assert((Index >= 0) and (Index < FDefinitions.Count));
  Result := FDefinitions[Index];
end;

function TInstructionEditor.GetDefinitionCount: Integer;
begin
  Result := FDefinitions.Count;
end;

function TInstructionEditor.GetDefinitionTopLevelFilter(
  Definition: TInstructionDefinition): TInstructionFilter;
begin
  Result := nil;
  case Definition.Encoding of
    ieDefault:
      begin
        case Definition.OpcodeMap of
          omDefault:
            Result := FRootTable;
          om0F:
            Result := FRootTable.Items[$0F];
          om0F38:
            Result := FRootTable.Items[$0F].Items[$38];
          om0F3A:
            Result := FRootTable.Items[$0F].Items[$3A];
          omXOP8,
          omXOP9,
          omXOPA:
            Assert(false);
        end;
      end;
    ie3DNow:
      Result := FRootTable.Items[$0F].Items[$0F].Items[$01];
    ieXOP:
      begin
        case Definition.OpcodeMap of
          omDefault,
          om0F,
          om0F38,
          om0F3A: Assert(false);
          omXOP8:
            Result := FRootTable.Items[$8F].Items[$02].Items[$01];
          omXOP9:
            Result := FRootTable.Items[$8F].Items[$02].Items[$02];
          omXOPA:
            Result := FRootTable.Items[$8F].Items[$02].Items[$03];
        end;
      end;
    ieVEX:
      Result := FRootTable.Items[$C4].Items[$03];
    ieEVEX:
      Result := FRootTable.Items[$62].Items[$04];
  end;
  Assert(Assigned(Result));
end;

class function TInstructionEditor.GetFilterList(
  Encoding: TInstructionEncoding): PInstructionFilterList;
begin
  Result := @FilterOrderDef;
  case Encoding of
    ieXOP:
      Result := @FilterOrderXOP;
    ieVEX:
      Result := @FilterOrderVEX;
    ieEVEX:
      Result := @FilterOrderEVEX;
  end;
end;

procedure TInstructionEditor.InsertDefinition(Definition: TInstructionDefinition);
var
  F, T: TInstructionFilter;
  I, Index: Integer;
  FilterList: PInstructionFilterList;
  IsRequiredFilter: Boolean;
begin
  BeginUpdate;
  try
    // Remove the definition from its old position
    RemoveDefinition(Definition);

    // Skip all static tables. This code assumes that the parent of a static-table is always
    // another static table.
    // There is no need to create a static table as child of a non-static one at the moment.
    F := GetDefinitionToplevelFilter(Definition);
    Index := F.GetInsertPosition(Definition);
    while (Assigned(F.Items[Index])) and (iffIsStaticFilter in F.Items[Index].FilterFlags) do
    begin
      F := F.Items[Index];
      Index := F.GetInsertPosition(Definition);
    end;

    // Create required filters
    FilterList := GetFilterList(Definition.Encoding);
    for I := Low(FilterList^) to High(FilterList^) do
    begin
      // Check if the current definition requires this filter
      IsRequiredFilter := false;
      case FilterList^[I].GetNeutralElementType of
        netNotAvailable:
          IsRequiredFilter := (FilterList^[I].GetInsertPosition(Definition) >= 0);
        netPlaceholder,
        netValue:
          IsRequiredFilter := (FilterList^[I].GetInsertPosition(Definition) >  0);
      end;

      Index := F.GetInsertPosition(Definition);

      // We have to enforce this filter, if a definition in the target-slot already requires the
      // same filter type
      if (not IsRequiredFilter) and (FilterList^[I].GetNeutralElementType <> netNotAvailable) and
        (F.Items[Index] is FilterList^[I]) then
      begin
        IsRequiredFilter := true;
      end;

      if (IsRequiredFilter) then
      begin
        // If the target slot is not occupied, just go ahead and create the new filter
        if (not Assigned(F.Items[Index])) then
        begin
          F.CreateFilterAtIndex(Index, FilterList^[I], false, false);
        end;
        // If the target slot is occupied by a different filter type, we need to save the old
        // filter and insert it into our new one
        if (F.Items[Index] is FilterList^[I]) then
        begin
          F := F.Items[Index];
        end else
        begin
          T := F.Items[Index];
          F.CreateFilterAtIndex(Index, FilterList^[I], false, false);
          F := F.Items[Index];
          F.SetItem(0, T);
        end;
      end;
    end;

    // Create a definition-container and actually insert the definition
    Index := F.GetInsertPosition(Definition);
    if (not Assigned(F.Items[Index])) then
    begin
      F.CreateFilterAtIndex(Index, TDefinitionContainer, false, false);
    end;
    F.Items[Index].InsertDefinition(Definition);
  finally
    EndUpdate;
  end;
end;

procedure TInstructionEditor.LoadFromFile(const Filename: String);
var
  List: TStringList;
  JSON: TJSONVariantData;
begin
  List := TStringList.Create;
  try
    List.LoadFromFile(Filename);
    JSON.Init;
    if (not JSON.FromJSON(List.Text)) or (JSON.Kind <> jvObject) then
    begin
      raise Exception.Create('Could not parse JSON file.');
    end;
    LoadFromJSON(@JSON);
  finally
    List.Free;
  end;
end;

procedure TInstructionEditor.LoadFromJSON(JSON: PJSONVariantData);
var
  JSONDefinitions,
  JSONDefinition: PJSONVariantData;
  I: Integer;
  Definition: TInstructionDefinition;
begin
  BeginUpdate;
  try
    Reset;
    try
      if (JSON^.Kind <> jvObject) then
      begin
        raise Exception.Create('Invalid JSON object.');
      end;
      JSONDefinitions := JSON^.Data('definitions');
      if ((not Assigned(JSONDefinitions)) or (JSONDefinitions^.Kind <> jvArray)) then
      begin
        raise Exception.Create(
          'The JSON object does not contain the required "definitions" array.');
      end;
      if (Assigned(FOnWorkStart)) then
      begin
        FOnWorkStart(Self, 0, JSONDefinitions^.Count);
      end;
      for I := 0 to JSONDefinitions^.Count - 1 do
      begin
        JSONDefinition := JSONVariantDataSafe(JSONDefinitions^.Item[I], jvObject);
        if (not Assigned(JSONDefinition)) then
        begin
          raise Exception.CreateFmt(
            'The definition item #%d is not a valid JSON object.', [I + 1]);
        end;
        // RegisterDefinition and InsertDefinition are indirectly called
        Definition := CreateDefinition('unnamed');
        Definition.BeginUpdate;
        try
          try
            Definition.UpdatePosition;
            Definition.LoadFromJSON(JSONDefinition);
          except
            on E: Exception do
            begin
              raise Exception.CreateFmt(
                'Error while parsing definition #%d: "%s"', [I + 1, E.Message]);
            end;
          end;
        finally
          Definition.EndUpdate;
        end;
        if (Assigned(FOnWork)) then
        begin
          FOnWork(Self, I + 1);
        end;
      end;
      if (Assigned(FOnWorkEnd)) then
      begin
        FOnWorkEnd(Self);
      end;
    except
      Reset;
      raise;
    end;
  finally
    EndUpdate;
  end;
end;

procedure TInstructionEditor.RegisterDefinition(Definition: TInstructionDefinition);
begin
  // This method is automatically called by TInstructionDefinition.Create
  Assert(not FDefinitions.Contains(Definition));
  FDefinitions.Add(Definition);
  if Assigned(FOnDefinitionCreated) then
  begin
    FOnDefinitionCreated(Self, Definition);
  end;
end;

procedure TInstructionEditor.RemoveDefinition(Definition: TInstructionDefinition);
var
  F, P, T: TInstructionFilter;
  I: Integer;
  DoRemove: Boolean;
begin
  if (not Assigned(Definition.Parent)) then
  begin
    Exit;
  end;
  BeginUpdate;
  try
    F := Definition.Parent;
    F.RemoveDefinition(Definition);
    if (F.DefinitionCount > 0) then
    begin
      Exit;
    end;
    // Remove empty filter tables
    DoRemove := true;
    while (DoRemove and Assigned(F) and (not (iffIsRootTable in F.FilterFlags))) do
    begin
      if (F.IsDefinitionContainer) then
      begin
        DoRemove := (F.DefinitionCount = 0);
      end else
      begin
        DoRemove := (not (iffIsStaticFilter in F.FilterFlags)) and
          ((F.ItemCount = 0) or ((F.NeutralElementType <> netNotAvailable) and
          (F.ItemCount = 1) and (Assigned(F.Items[0]))));
      end;
      if (DoRemove) then
      begin
        Assert(Assigned(F.Parent));
        P := F.Parent;
        I := P.IndexOf(F);
        if (not (F.IsDefinitionContainer)) and (Assigned(F.Items[0])) then
        begin
          T := F.Items[0];
          F.SetItem(0, nil);
          P.SetItem(I, T);
        end else
        begin
          P.SetItem(I, nil);
        end;
        F.Free;
        F := P;
      end;
    end;
  finally
    EndUpdate;
  end;
end;

procedure TInstructionEditor.Reset;
var
  I: Integer;
begin
  BeginUpdate;
  try
    FPreventDefinitionRemoval := true;
    for I := FDefinitions.Count - 1 downto 0 do
    begin
      FDefinitions[I].Free;
    end;
    FPreventDefinitionRemoval := false;
    FDefinitions.Clear;
    if (not Assigned(FRootTable)) then
    begin
      FFilterCount := 1;
      // 1, 2 and 3 Byte Opcode Tables
      FRootTable := TOpcodeFilter.Create(Self, nil, true, true);
      FRootTable.CreateFilterAtIndex($0F, TOpcodeFilter, false, true);
      FRootTable.Items[$0F].CreateFilterAtIndex($38, TOpcodeFilter, false, true);
      FRootTable.Items[$0F].CreateFilterAtIndex($3A, TOpcodeFilter, false, true);
      // 3DNow Table
      FRootTable.Items[$0F].CreateFilterAtIndex($0F, TEncodingFilter, false, true);
      FRootTable.Items[$0F].Items[$0F].CreateFilterAtIndex($01, TOpcodeFilter, false, true);
      // 3 Byte VEX Table
      FRootTable.CreateFilterAtIndex($C4, TEncodingFilter, false, true);
      FRootTable.Items[$C4].CreateFilterAtIndex($03, TVEXMapFilter, false, true);
      // 2 Byte VEX Table (we copy the 3 byte VEX table later)
      FRootTable.CreateFilterAtIndex($C5, TEncodingFilter, false, true);
      FRootTable.Items[$C5].CreateFilterAtIndex($03, TVEXMapFilter, false, true);
      // XOP Table
      FRootTable.CreateFilterAtIndex($8F, TEncodingFilter, false, true);
      FRootTable.Items[$8F].CreateFilterAtIndex($02, TXOPMapFilter, false, true);
      for I := 1 to FRootTable.Items[$8F].Items[$02].Capacity - 1 do
      begin
        FRootTable.Items[$8F].Items[$02].CreateFilterAtIndex(I, TOpcodeFilter, false, true);
      end;
      // EVEX Table
      FRootTable.CreateFilterAtIndex($62, TEncodingFilter, false, true);
      FRootTable.Items[$62].CreateFilterAtIndex($04, TVEXMapFilter, false, true);
    end;
  finally
    EndUpdate;
  end;
end;

procedure TInstructionEditor.SaveToFile(const Filename: String);
var
  JSON: TJSONVariantData;
  List: TStringList;
begin
  JSON.Init;
  SaveToJSON(@JSON);
  List := TStringList.Create;
  try
    List.Text := TJSONHelper.JSONToString(@JSON);
    List.SaveToFile(FileName);
  finally
    List.Free;
  end;
end;

procedure TInstructionEditor.SaveToJSON(JSON: PJSONVariantData);
var
  I: Integer;
  JSONDefinitionList, JSONDefinition: TJSONVariantData;
begin
  // Sort definitions with a stable algorithm to ensure deterministic output
  TListHelper<TInstructionDefinition>.BubbleSort(
    FDefinitions, TComparer<TInstructionDefinition>.Construct(
      function(const Left, Right: TInstructionDefinition): Integer
      begin
        Result := CompareStr(Left.Mnemonic, Right.Mnemonic);
        if (Result = 0) then Result := Ord(Left.Encoding)  - Ord(Right.Encoding);
        if (Result = 0) then Result := Ord(Left.OpcodeMap) - Ord(Right.OpcodeMap);
        if (Result = 0) then Result := Ord(Left.Opcode)    - Ord(Right.Opcode);
      end));
  // Save to JSON
  if (Assigned(FOnWorkStart)) then
  begin
    FOnWorkStart(Self, 0, FDefinitions.Count);
  end;
  JSONDefinitionList.Init;
  for I := 0 to FDefinitions.Count - 1 do
  begin
    JSONDefinition.Init;
    FDefinitions[I].SaveToJSON(@JSONDefinition);
    JSONDefinitionList.AddValue(Variant(JSONDefinition));
    if (Assigned(FOnWork)) then
    begin
      FOnWork(Self, I + 1);
    end;
  end;
  JSON^.AddNameValue('definitions', Variant(JSONDefinitionList));
  if (Assigned(FOnWorkEnd)) then
  begin
    FOnWorkEnd(Self);
  end;
end;

procedure TInstructionEditor.UnregisterDefinition(Definition: TInstructionDefinition);
begin
  // This method is automatically called by TInstructionDefinition.Destroy
  Assert(FDefinitions.Contains(Definition));
  if Assigned(FOnDefinitionDestroyed) then
  begin
    FOnDefinitionDestroyed(Self, Definition);
  end;
  if (not FPreventDefinitionRemoval) then
  begin
    FDefinitions.Remove(Definition);
  end;
end;
{$ENDREGION}

end.

