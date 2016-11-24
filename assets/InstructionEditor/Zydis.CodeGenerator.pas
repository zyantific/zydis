unit Zydis.CodeGenerator;

interface

uses
  System.Classes, System.Generics.Collections, Zydis.InstructionEditor;

type
  TLanguageBinding = class;
  TLanguageBindingClass = class of TLanguageBinding;

  TIndexedInstructionFilter = record
  public
    Id: Integer;
    Filter: TInstructionFilter;
    Items: array of TIndexedInstructionFilter;
    IsRedirect: Boolean;
  end;

  TIndexedInstructionDefinition = record
  public
    Id: Integer;
    Definition: TInstructionDefinition;
  end;

  TIndexedInstructionFilterList     =
    TArray<TPair<TInstructionFilterClass, TArray<TIndexedInstructionFilter>>>;
  TIndexedInstructionDefinitionList = TArray<TIndexedInstructionDefinition>;
  TMnemonicList                     = TArray<String>;
  TOperandList                      = TArray<TInstructionOperands>;
  TOperandMapping                   = array[1..5] of TOperandList;

  TRegisterList                     = TArray<TX86Registers>;
  TFlagsList                        = TArray<TX86Flags>;
  TCPUIDList                        = TArray<TCPUIDFeatureFlags>;

  TCodeGeneratorStatistics = record
  public
    MnemonicCount: Integer;
    MnemonicSize: Cardinal;
    InstructionDefinitionCount: Integer;
    InstructionDefinitionSize: Cardinal;
    OperandDefinitionCount: Integer;
    OperandDefinitionSize: Cardinal;
    InstructionFilterCount: Integer;
    InstructionFilterSize: Cardinal;
    TotalSize: Cardinal;
  end;

  TGeneratorWorkStartEvent =
    procedure(Sender: TObject; const OperationName: String;
      OperationCount, OperationNumber: Integer; MinWorkCount, MaxWorkCount: Integer) of Object;

  TGeneratorWorkEvent =
    procedure(Sender: TObject; WorkCount: Integer) of Object;

  TCodeGenerator = class(TObject)
  strict private
    class var FLanguageBindings: TList<TLanguageBindingClass>;
  strict private
    FCurrentOperationNumber: Integer;
  strict private
    FOnWorkStart: TGeneratorWorkStartEvent;
    FOnWork: TGeneratorWorkEvent;
    FOnWorkEnd: TNotifyEvent;
  strict private
    procedure WorkStart(const OperationName: String; MinWorkCount, MaxWorkCount: Integer); inline;
    procedure Work(WorkCount: Integer); inline;
    procedure WorkEnd; inline;
  strict private
    procedure CreateMnemonicList(Editor: TInstructionEditor; var MnemonicList: TMnemonicList;
      var MnemonicCount: Integer; var MnemonicSize: Cardinal);
    procedure CreateInstructionDefinitionList(Editor: TInstructionEditor;
      var DefinitionList: TIndexedInstructionDefinitionList;
      var InstructionDefinitionCount: Integer; var InstructionDefinitionSize: Cardinal);
    procedure CreateOperandMapping(const DefinitionList: TIndexedInstructionDefinitionList;
      var OperandMapping: TOperandMapping; var OperandDefinitionCount: Integer;
      var OperandDefinitionSize: Cardinal);
    procedure CreateInstructionFilterList(Editor: TInstructionEditor;
      const DefinitionList: TIndexedInstructionDefinitionList;
      var FilterList: TIndexedInstructionFilterList; var InstructionFilterCount: Integer;
      var InstructionFilterSize: Cardinal);

    procedure CreateRegisterList(const DefinitionList: TIndexedInstructionDefinitionList;
      var RegisterList: TRegisterList);
    procedure CreateFlagsList(const DefinitionList: TIndexedInstructionDefinitionList;
      var FlagsList: TFlagsList);
    procedure CreateCPUIDList(const DefinitionList: TIndexedInstructionDefinitionList;
      var CPUIDList: TCPUIDList);

    procedure CreateSnapshot(Editor: TInstructionEditor; var Statistics: TCodeGeneratorStatistics;
      var MnemonicList: TMnemonicList;
      var DefinitionList: TIndexedInstructionDefinitionList; var OperandMapping: TOperandMapping;
      var FilterList: TIndexedInstructionFilterList;
      var RegisterList: TRegisterList; var FlagsList: TFlagsList; var CPUIDList: TCPUIDList);
  strict private
    procedure GenerateInternalStructs(const OutputDirectory: String;
      const MnemonicList: TMnemonicList; const DefinitionList: TIndexedInstructionDefinitionList;
      const OperandMapping: TOperandMapping; const FilterList: TIndexedInstructionFilterList;
      const RegisterList: TRegisterList; const FlagsList: TFlagsList; const CPUIDList: TCPUIDList);
    procedure GenerateMnemonicIncludes(const OutputDirectory: String;
      const MnemonicList: TMnemonicList);
    procedure GenerateInstructionDefinitions(const OutputDirectory: String;
      const DefinitionList: TIndexedInstructionDefinitionList;
      const OperandMapping: TOperandMapping);
    procedure GenerateOperandDefinitions(const OutputDirectory: String;
      const OperandMapping: TOperandMapping);
    procedure GenerateInstructionFilters(const OutputDirectory: String;
      const FilterList: TIndexedInstructionFilterList);
  private
    class procedure RegisterLanguageBinding(Binding: TLanguageBindingClass);
  public
    procedure GenerateCode(Editor: TInstructionEditor; const OutputDirectory: String); overload;
    procedure GenerateCode(Editor: TInstructionEditor; const OutputDirectory: String;
      var Statistics: TCodeGeneratorStatistics); overload;
  public
    class constructor Create;
    class destructor Destroy;
  public
    constructor Create;
  public
    property OnWorkStart: TGeneratorWorkStartEvent read FOnWorkStart write FOnWorkStart;
    property OnWork: TGeneratorWorkEvent read FOnWork write FOnWork;
    property OnWorkEnd: TNotifyEvent read FOnWorkEnd write FOnWorkEnd;
  end;

  TLanguageBinding = class(TObject)
  protected
    class function GetName: String; virtual; abstract;
    class procedure GenerateCode(Generator: TCodeGenerator;
      const OutputDirectory: String); virtual; abstract;
  protected
    constructor Create;
  end;

  TLanguageBindingCPP = class(TLanguageBinding)
  protected
    class function GetName: String; override;
    class procedure GenerateCode(Generator: TCodeGenerator;
      const OutputDirectory: String); override;
  end;

  TLanguageBindingDelphi = class(TLanguageBinding)
  protected
    class function GetName: String; override;
    class procedure GenerateCode(Generator: TCodeGenerator;
      const OutputDirectory: String); override;
  end;

  TLanguageBindingPython = class(TLanguageBinding)
  protected
    class function GetName: String; override;
    class procedure GenerateCode(Generator: TCodeGenerator;
      const OutputDirectory: String); override;
  end;

implementation

uses
  System.SysUtils, System.Generics.Defaults, Zydis.InstructionFilters, untHelperClasses;

const
  MNEMONIC_ALIASES: array[0..0] of String = (
    'nop'
  );
  SIZEOF_INSTRUCTIONTABLENODE     =  3;
  SIZEOF_INSTRUCTIONDEFINITION    = 10;
  SIZEOF_OPERANDDEFINITION        =  2;
  DIRECTORY_INCLUDE_INTERNAL      = 'include\Zydis\Internal';
  FILENAME_INSTRUCTIONFILTERS     = 'InstructionFilters.inc';
  FILENAME_MNEMONICDEFINES        = 'MnemonicDefines.inc';
  FILENAME_MNEMONICSTRINGS        = 'MnemonicStrings.inc';
  FILENAME_INSTRUCTIONDEFINITIONS = 'InstructionDefinitions.inc';
  FILENAME_OPERANDDEFINITIONS     = 'OperandDefinitions.inc';
  FILENAME_GENERATEDTYPES         = 'GeneratedTypes.inc';

{ TCodeGenerator }

constructor TCodeGenerator.Create;
begin
  inherited Create;

end;

procedure TCodeGenerator.CreateCPUIDList(const DefinitionList: TIndexedInstructionDefinitionList;
  var CPUIDList: TCPUIDList);
var
  List: TList<TCPUIDFeatureFlags>;
  I, J: Integer;
  B: Boolean;
begin
  WorkStart('Creating CPUID list', 0, Length(DefinitionList));
  List := TList<TCPUIDFeatureFlags>.Create;
  try
    for I := Low(DefinitionList) to High(DefinitionList) do
    begin
      B := false;
      for J := 0 to List.Count - 1 do
      begin
        if (DefinitionList[I].Definition.CPUID.Equals(List.List[J])) then
        begin
          B := true;
          Break;
        end;
      end;
      if (not B) then
      begin
        List.Add(DefinitionList[I].Definition.CPUID);
      end;
      Work(I + 1);
    end;
    CPUIDList := List.ToArray;
  finally
    List.Free;
  end;
  WorkEnd;
end;

procedure TCodeGenerator.CreateFlagsList(const DefinitionList: TIndexedInstructionDefinitionList;
  var FlagsList: TFlagsList);
var
  List: TList<TX86Flags>;
  I, J: Integer;
  B: Boolean;
begin
  WorkStart('Creating flags list', 0, Length(DefinitionList));
  List := TList<TX86Flags>.Create;
  try
    for I := Low(DefinitionList) to High(DefinitionList) do
    begin
      B := false;
      for J := 0 to List.Count - 1 do
      begin
        if (DefinitionList[I].Definition.X86Flags.Equals(List.List[J])) then
        begin
          B := true;
          Break;
        end;
      end;
      if (not B) then
      begin
        List.Add(DefinitionList[I].Definition.X86Flags);
      end;
      Work(I + 1);
    end;
    FlagsList := List.ToArray;
  finally
    List.Free;
  end;
  WorkEnd;
end;

procedure TCodeGenerator.CreateInstructionDefinitionList(Editor: TInstructionEditor;
  var DefinitionList: TIndexedInstructionDefinitionList; var InstructionDefinitionCount: Integer;
  var InstructionDefinitionSize: Cardinal);
var
  List: TList<TInstructionDefinition>;
  I, J: Integer;
  B: Boolean;
  Comparison: TComparison<TInstructionDefinition>;
begin
  List := TList<TInstructionDefinition>.Create;
  try
    WorkStart('Indexing instruction definitions', 0, Editor.DefinitionCount * 2);
    for I := 0 to Editor.DefinitionCount - 1 do
    begin
      B := false;
      for J := 0 to List.Count - 1 do
      begin
        if (Editor.Definitions[I].Equals(List[J], false, false)) then
        begin
          B := true;
          Break;
        end;
      end;
      if (not B) then
      begin
        List.Add(Editor.Definitions[I]);
      end;
      Work(I + 1);
    end;
    Comparison :=
      function(const Left, Right: TInstructionDefinition): Integer
      begin
        Result := CompareStr(Left.Mnemonic, Right.Mnemonic);
      end;
    List.Sort(TComparer<TInstructionDefinition>.Construct(Comparison));
    SetLength(DefinitionList, List.Count);
    for I := 0 to List.Count - 1 do
    begin
      DefinitionList[I].Id := I;
      DefinitionList[I].Definition := List[I];
      Work(Editor.DefinitionCount + I + 1);
    end;
    WorkEnd;
  finally
    List.Free;
  end;
  InstructionDefinitionCount := Length(DefinitionList);
  InstructionDefinitionSize := Length(DefinitionList) * SIZEOF_INSTRUCTIONDEFINITION;
end;

procedure TCodeGenerator.CreateInstructionFilterList(Editor: TInstructionEditor;
  const DefinitionList: TIndexedInstructionDefinitionList;
  var FilterList: TIndexedInstructionFilterList; var InstructionFilterCount: Integer;
  var InstructionFilterSize: Cardinal);

var
  IndexDict: TDictionary<TInstructionFilterClass, Integer>;

procedure CreateChildIndizes(var Root: TIndexedInstructionFilter);
var
  I, J: Integer;
begin
  SetLength(Root.Items, Root.Filter.Capacity);
  FillChar(Root.Items[0], Length(Root.Items) * SizeOf(Root.Items[0]), #0);
  for I := 0 to Root.Filter.Capacity - 1 do
  begin
    Root.Items[I].Id := -1;
    Root.Items[I].Filter := Root.Filter.Items[I];
    if (Assigned(Root.Items[I].Filter)) then
    begin
      if (not IndexDict.ContainsKey(TInstructionFilterClass(Root.Filter.Items[I].ClassType))) then
      begin
        Root.Items[I].Id := 0;
        IndexDict.Add(TInstructionFilterClass(Root.Filter.Items[I].ClassType), 1);
      end else
      begin
        Root.Items[I].Id := IndexDict[TInstructionFilterClass(Root.Filter.Items[I].ClassType)];
        IndexDict[TInstructionFilterClass(Root.Filter.Items[I].ClassType)] := Root.Items[I].Id + 1;
      end;

      if (Root.Items[I].Filter.IsDefinitionContainer) then
      begin
        // Fix mnemonic index
        for J := Low(DefinitionList) to High(DefinitionList) do
        begin
          if (TDefinitionContainer(Root.Items[I].Filter).Definitions[0].Equals(
            DefinitionList[J].Definition, false, false)) then
          begin
            Root.Items[I].Id := DefinitionList[J].Id;
            Break;
          end;
        end;
      end else
      begin
        Inc(InstructionFilterCount);
        Inc(InstructionFilterSize, Root.Items[I].Filter.GetCapacity * SIZEOF_INSTRUCTIONTABLENODE);
        if (Root.Items[I].Filter.NeutralElementType = netPlaceholder) then
        begin
          Dec(InstructionFilterSize, SIZEOF_INSTRUCTIONTABLENODE);
        end;
        Work(InstructionFilterCount);
      end;

      CreateChildIndizes(Root.Items[I]);
    end;
  end;
end;

var
  ListDict: TDictionary<TInstructionFilterClass, TList<TIndexedInstructionFilter>>;

procedure AddFiltersToListDict(const Root: TIndexedInstructionFilter);
var
  FilterList: TList<TIndexedInstructionFilter>;
  I: Integer;
begin
  if (Root.IsRedirect) then Exit;
  if (not ListDict.ContainsKey(TInstructionFilterClass(Root.Filter.ClassType))) then
  begin
    FilterList := TList<TIndexedInstructionFilter>.Create;
    ListDict.Add(TInstructionFilterClass(Root.Filter.ClassType), FilterList);
  end else
  begin
    FilterList := ListDict[TInstructionFilterClass(Root.Filter.ClassType)];
  end;
  FilterList.Add(Root);
  for I := Low(Root.Items) to High(Root.Items) do
  begin
    if (Root.Items[I].Id < 0) or (Root.Items[I].Filter is TEncodingFilter) then Continue;
    AddFiltersToListDict(Root.Items[I]);
  end;
end;

var
  I, J, K: Integer;
  Root, Temp: TIndexedInstructionFilter;
  A: TArray<TPair<TInstructionFilterClass, TList<TIndexedInstructionFilter>>>;
begin
  IndexDict := TDictionary<TInstructionFilterClass, Integer>.Create;
  try
    // Generate internal tree structure
    Root.Id := 0;
    Root.Filter := Editor.RootTable;
    Root.IsRedirect := false;
    IndexDict.Add(TOpcodeFilter, 1);
    InstructionFilterCount := 1;
    InstructionFilterSize := 256 * SIZEOF_INSTRUCTIONTABLENODE;
    WorkStart('Indexing instruction filters', 0, Editor.FilterCount - 1);
    CreateChildIndizes(Root);
    WorkEnd;

    // Unlink encoding filters
    Root.Items[$0F].Items[$0F] := Root.Items[$0F].Items[$0F].Items[$01];
    Temp := Root.Items[$C4].Items[$03];
    Temp.Items[$00] := Root.Items[$C4].Items[$00];
    Root.Items[$C4] := Temp;
    Temp := Root.Items[$C5].Items[$03];
    Temp.Items[$00] := Root.Items[$C5].Items[$00];
    Root.Items[$C5] := Temp;
    Temp := Root.Items[$62].Items[$04];
    Temp.Items[$00] := Root.Items[$62].Items[$00];
    Root.Items[$62] := Temp;
    Temp := Root.Items[$8F].Items[$02];
    Temp.Items[$00] := Root.Items[$8F].Items[$00];
    Root.Items[$8F] := Temp;

    // Initialize 2-byte VEX filter
    Root.Items[$C5].Items[$01] := Root.Items[$C4].Items[$01]; // 0x0F
    Root.Items[$C5].Items[$01].IsRedirect := true;
    Root.Items[$C5].Items[$05] := Root.Items[$C4].Items[$05]; // 0x66 0x0F
    Root.Items[$C5].Items[$05].IsRedirect := true;
    Root.Items[$C5].Items[$09] := Root.Items[$C4].Items[$09]; // 0xF3 0x0F
    Root.Items[$C5].Items[$09].IsRedirect := true;
    Root.Items[$C5].Items[$0D] := Root.Items[$C4].Items[$0D]; // 0xF2 0x0F
    Root.Items[$C5].Items[$0D].IsRedirect := true;

    Dec(InstructionFilterCount, 5);
    Dec(InstructionFilterSize, 5 * TEncodingFilter.GetCapacity * SIZEOF_INSTRUCTIONTABLENODE);

    // Generate filter list
    ListDict := TObjectDictionary<TInstructionFilterClass,
      TList<TIndexedInstructionFilter>>.Create([doOwnsValues]);
    try
      AddFiltersToListDict(Root);
      A := ListDict.ToArray;
      SetLength(FilterList, Length(A));
      for I := Low(A) to High(A) do
      begin
        FilterList[I].Key := A[I].Key;
        FilterList[I].Value := A[I].Value.ToArray;
        // Clear recursive child-item arrays
        for J := Low(FilterList[I].Value) to HigH(FilterList[I].Value) do
        begin
          for K := Low(FilterList[I].Value[J].Items) to High(FilterList[I].Value[J].Items) do
          begin
            SetLength(FilterList[I].Value[J].Items[K].Items, 0);
          end;
        end;
      end;
    finally
      ListDict.Free;
    end;
  finally
    IndexDict.Free;
  end;
end;

procedure TCodeGenerator.CreateMnemonicList(Editor: TInstructionEditor;
  var MnemonicList: TMnemonicList; var MnemonicCount: Integer; var MnemonicSize: Cardinal);
var
  I: Integer;
  List: TList<String>;
  Comparison: TComparison<String>;
begin
  WorkStart('Creating mnemonic list', 0, Editor.DefinitionCount);
  MnemonicSize := 0;
  List := TList<String>.Create;
  try
    for I := 0 to Editor.DefinitionCount - 1 do
    begin
      List.Add(Editor.Definitions[I].Mnemonic);
      Work(I);
    end;
    for I := Low(MNEMONIC_ALIASES) to High(MNEMONIC_ALIASES) do
    begin
      List.Add(MNEMONIC_ALIASES[I]);
    end;
    Comparison :=
      function(const Left, Right: String): Integer
      begin
        Result := CompareStr(Left, Right);
      end;
    List.Sort(TComparer<String>.Construct(Comparison));
    for I := List.Count - 1 downto 1 do
    begin
      if (List[I] = List[I - 1]) then
      begin
        List.Delete(I);
      end;
    end;
    List.Insert(0, 'invalid');
    SetLength(MnemonicList, List.Count);
    for I := 0 to List.Count - 1 do
    begin
      MnemonicList[I] := List[I];
      Inc(MnemonicSize, Length(MnemonicList[I]));
    end;
  finally
    List.Free;
  end;
  MnemonicCount := Length(MnemonicList);
  WorkEnd;
end;

procedure TCodeGenerator.CreateOperandMapping(
  const DefinitionList: TIndexedInstructionDefinitionList; var OperandMapping: TOperandMapping;
  var OperandDefinitionCount: Integer; var OperandDefinitionSize: Cardinal);
var
  I, J: Integer;
  B: Boolean;
  OperandsUsed: Integer;
begin
  WorkStart('Processing instruction operands', Low(DefinitionList), High(DefinitionList));
  for I := Low(DefinitionList) to High(DefinitionList) do
  begin
    OperandsUsed := DefinitionList[I].Definition.Operands.OperandsUsed;
    if (OperandsUsed = 0) then
    begin
      Continue;
    end;
    B := false;
    for J := Low(OperandMapping[OperandsUsed]) to High(OperandMapping[OperandsUsed]) do
    begin
      if (OperandMapping[OperandsUsed][J].Equals(DefinitionList[I].Definition.Operands)) then
      begin
        B := true;
        Break;
      end;
    end;
    if (not B) then
    begin
      SetLength(OperandMapping[OperandsUsed], Length(OperandMapping[OperandsUsed]) + 1);
      OperandMapping[OperandsUsed][High(OperandMapping[OperandsUsed])] :=
        DefinitionList[I].Definition.Operands;
    end;
    Work(I);
  end;
  WorkEnd;
  for I := Low(OperandMapping) to High(OperandMapping) do
  begin
    Inc(OperandDefinitionCount, Length(OperandMapping[I]));
    Inc(OperandDefinitionSize, I * Length(OperandMapping[I]) * SIZEOF_OPERANDDEFINITION);
  end;
end;

procedure TCodeGenerator.CreateRegisterList(const DefinitionList: TIndexedInstructionDefinitionList;
  var RegisterList: TRegisterList);
var
  List: TList<TX86Registers>;
  I, J: Integer;
  B: Boolean;
begin
  WorkStart('Creating register list', 0, Length(DefinitionList));
  List := TList<TX86Registers>.Create;
  try
    for I := Low(DefinitionList) to High(DefinitionList) do
    begin
      // ImplicitRead
      B := false;
      for J := 0 to List.Count - 1 do
      begin
        if (DefinitionList[I].Definition.ImplicitRead.Equals(List.List[J])) then
        begin
          B := true;
          Break;
        end;
      end;
      if (not B) then
      begin
        List.Add(DefinitionList[I].Definition.ImplicitRead);
      end;
      // ImplicitWrite
      B := false;
      for J := 0 to List.Count - 1 do
      begin
        if (DefinitionList[I].Definition.ImplicitWrite.Equals(List.List[J])) then
        begin
          B := true;
          Break;
        end;
      end;
      if (not B) then
      begin
        List.Add(DefinitionList[I].Definition.ImplicitWrite);
      end;
      Work(I + 1);
    end;
    RegisterList := List.ToArray;
  finally
    List.Free;
  end;
  WorkEnd;
end;

class constructor TCodeGenerator.Create;
begin
  FLanguageBindings := TList<TLanguageBindingClass>.Create;
end;

procedure TCodeGenerator.CreateSnapshot(Editor: TInstructionEditor;
  var Statistics: TCodeGeneratorStatistics; var MnemonicList: TMnemonicList;
  var DefinitionList: TIndexedInstructionDefinitionList; var OperandMapping: TOperandMapping;
  var FilterList: TIndexedInstructionFilterList;
  var RegisterList: TRegisterList; var FlagsList: TFlagsList; var CPUIDList: TCPUIDList);
begin
  // Create sorted mnemonic list with all aliases
  CreateMnemonicList(Editor, MnemonicList, Statistics.MnemonicCount, Statistics.MnemonicSize);

  // Create definition indizes and a sorted definition-list
  CreateInstructionDefinitionList(Editor, DefinitionList, Statistics.InstructionDefinitionCount,
    Statistics.InstructionDefinitionSize);

  // Sort operands and eliminate duplicates
  CreateOperandMapping(DefinitionList, OperandMapping, Statistics.OperandDefinitionCount,
    Statistics.OperandDefinitionSize);

  // Create indexed instruction-filter list
  CreateInstructionFilterList(Editor, DefinitionList, FilterList, Statistics.InstructionFilterCount,
    Statistics.InstructionFilterSize);

  // Create implicitly-used registers list
  CreateRegisterList(DefinitionList, RegisterList); // TODO: Add statistics
  // Create FLAGS/EFLAGS/RFLAGS list
  CreateFlagsList(DefinitionList, FlagsList); // TODO: Add statistics
  // Create CPUID list
  CreateCPUIDList(DefinitionList, CPUIDList); // TODO: Add statistics

  Statistics.TotalSize := Statistics.MnemonicSize + Statistics.InstructionDefinitionSize +
    Statistics.OperandDefinitionSize + Statistics.InstructionFilterSize;
end;

class destructor TCodeGenerator.Destroy;
begin
  FLanguageBindings.Free;
end;

procedure TCodeGenerator.GenerateCode(Editor: TInstructionEditor;
  const OutputDirectory: String; var Statistics: TCodeGeneratorStatistics);
var
  FilterList: TIndexedInstructionFilterList;
  DefinitionList: TIndexedInstructionDefinitionList;
  OperandMapping: TOperandMapping;
  MnemonicList: TMnemonicList;
  RegisterList: TRegisterList;
  FlagsList: TFlagsList;
  CPUIDList: TCPUIDList;
  Directory: String;
begin
  // Check error cases
  if (not Assigned(Editor.RootTable)) then
  begin
    raise Exception.Create('The instruction editor does not contain tables.');
  end;
  if (Editor.RootTable.HasConflicts) then
  begin
    raise Exception.Create('The instruction editor has unresolved conflicts.');
  end;

  FCurrentOperationNumber := 0;
  FillChar(Statistics, SizeOf(Statistics), #0);

  CreateSnapshot(Editor, Statistics, MnemonicList, DefinitionList, OperandMapping, FilterList,
    RegisterList, FlagsList, CPUIDList);

  Directory := IncludeTrailingPathDelimiter(OutputDirectory) + DIRECTORY_INCLUDE_INTERNAL;
  ForceDirectories(Directory);
  GenerateMnemonicIncludes(Directory, MnemonicList);
  GenerateInstructionDefinitions(Directory, DefinitionList, OperandMapping);
  GenerateOperandDefinitions(Directory, OperandMapping);
  GenerateInstructionFilters(Directory, FilterList);
  GenerateInternalStructs(Directory, MnemonicList, DefinitionList, OperandMapping, FilterList,
    RegisterList, FlagsList, CPUIDList);
end;

procedure TCodeGenerator.GenerateInstructionDefinitions(const OutputDirectory: String;
  const DefinitionList: TIndexedInstructionDefinitionList; const OperandMapping: TOperandMapping);

procedure AppendInstructionDefinition(Buffer: TStringBuffer; Index: Integer;
  Definition: TInstructionDefinition);
var
  I, O: Integer;
  S, T, U: String;
begin
  O := Definition.Operands.OperandsUsed;
  if (O > 0) then
  begin
    for I := Low(OperandMapping[O]) to High(OperandMapping[O]) do
    begin
      if (OperandMapping[O][I].Equals(Definition.Operands)) then
      begin
        O := I;
        Break;
      end;
    end;
  end;

  S := 'ZYDIS_EVEXB_FUNCTIONALITY_NONE'; T := 'false'; U := 'false';
  if (ifAcceptsEvexAAA in Definition.Flags) then S := 'true';
  if (ifAcceptsEvexZ   in Definition.Flags) then T := 'true';
  if (ifHasEvexBC      in Definition.Flags) then U := 'ZYDIS_EVEXB_FUNCTIONALITY_BC'
  else
  if (ifHasEvexRC      in Definition.Flags) then U := 'ZYDIS_EVEXB_FUNCTIONALITY_RC'
  else
  if (ifHasEvexSAE     in Definition.Flags) then U := 'ZYDIS_EVEXB_FUNCTIONALITY_SAE';

  Buffer.Append(Format('    /*%.4x*/ ', [Index]));
  Buffer.Append(Format('{ ZYDIS_MNEMONIC_%s, 0x%.4x, %s, %s, %s, %d, %d, %d, %d, %d, %d, %d }', [
    AnsiUpperCase(Definition.Mnemonic), O, U, S, T,
    Byte(pfAcceptsLock in Definition.PrefixFlags),
    Byte(pfAcceptsREP in Definition.PrefixFlags),
    Byte(pfAcceptsREPEREPNE in Definition.PrefixFlags),
    Byte(pfAcceptsXACQUIRE in Definition.PrefixFlags),
    Byte(pfAcceptsXRELEASE in Definition.PrefixFlags),
    Byte(pfAcceptsHLEWithoutLock in Definition.PrefixFlags),
    Byte(pfAcceptsBranchHints in Definition.PrefixFlags)]));
end;

var
  Buffer: TStringBuffer;
  List: TStringList;
  I: Integer;
begin
  Buffer := TStringBuffer.Create;
  try
    Buffer.AppendLn('const ZydisInstructionDefinition instructionDefinitions[] =');
    Buffer.AppendLn('{');
    WorkStart('Generating instruction definitions', 0, Length(DefinitionList));
    for I := Low(DefinitionList) to High(DefinitionList) do
    begin
      AppendInstructionDefinition(Buffer, I, DefinitionList[I].Definition);
      if (I <> High(DefinitionList)) then
      begin
        Buffer.AppendLn(',');
      end else
      begin
        Buffer.AppendLn('');
      end;
      Work(I + 1);
    end;
    WorkEnd;
    if (Length(DefinitionList) = 0) then
    begin
      Buffer.AppendLn('    /*0000*/ { ZYDIS_MNEMONIC_INVALID }');
    end;
    Buffer.AppendLn('};');
    List := TStringList.Create;
    try
      List.Text := Buffer.Value;
      List.SaveToFile(IncludeTrailingPathDelimiter(OutputDirectory) +
        FILENAME_INSTRUCTIONDEFINITIONS);
    finally
      List.Free;
    end;
  finally
    Buffer.Free;
  end;
end;

procedure TCodeGenerator.GenerateInstructionFilters(const OutputDirectory: String;
  const FilterList: TIndexedInstructionFilterList);
var
  Buffer: TStringBuffer;
  StringList: TStringList;
  A: ^TArray<TIndexedInstructionFilter>;
  WorkCount,
  IndexShift: Integer;
  I, J, K: Integer;
begin
  Buffer := TStringBuffer.Create;
  try
    WorkCount := 0;
    for I := Low(FilterList) to High(FilterList) do
    begin
      if (FilterList[I].Key = TDefinitionContainer) then Continue;
      Inc(WorkCount, Length(FilterList[I].Value));
    end;
    WorkStart('Generating instruction filters', 0, WorkCount);
    WorkCount := 0;
    for I := Low(InstructionFilterClasses) to High(InstructionFilterClasses) do
    begin
      if (InstructionFilterClasses[I] = TEncodingFilter) then Continue;
      IndexShift := 0;
      if (InstructionFilterClasses[I].GetNeutralElementType = netPlaceholder) then
      begin
        IndexShift := 1;
      end;

      // Open the filter-array
      Buffer.AppendLn(Format('const ZydisInstructionTableNode filter%s[][%d] = ', [
        InstructionFilterClasses[I].GetDescription,
        Integer(InstructionFilterClasses[I].GetCapacity) - IndexShift]));
      Buffer.AppendLn('{');

      A := nil;
      for J := Low(FilterList) to High(FilterList) do
      begin
        if (FilterList[J].Key = InstructionFilterClasses[I]) then
        begin
          A := @FilterList[J].Value;
          Break;
        end;
      end;

      if (Assigned(A)) then
      begin
        // Add all filters of the current type
        for J := Low(A^) to High(A^) do
        begin

          // Open the local filter array
          Buffer.AppendLn('    {');

          // Add all filter values of the current filter
          for K := IndexShift to High(A^[J].Items) do
          begin
            Buffer.Append(Format('        /*%.4x*/ ', [K]));
            if (A^[J].Items[K].Id < 0) then
            begin
              Buffer.Append('ZYDIS_INVALID');
            end else if (A^[J].Items[K].Filter is TDefinitionContainer) then
            begin
              Assert((A^[J].Items[K].Filter as TDefinitionContainer).DefinitionCount = 1);
              Buffer.Append(Format('ZYDIS_DEFINITION_%dOP(0x%.4x)', [
                (A^[J].Items[K].Filter as TDefinitionContainer).Definitions[
                0].Operands.OperandsUsed, A^[J].Items[K].Id]));
            end else
            begin
              Buffer.Append(Format('ZYDIS_FILTER(ZYDIS_NODETYPE_FILTER_%s, 0x%.4x)', [
                AnsiUpperCase(
                TInstructionFilterClass(A^[J].Items[K].Filter.ClassType).GetDescription),
                A^[J].Items[K].Id]));
            end;
            if (K < High(A^[J].Items)) then
            begin
              Buffer.AppendLn(',');
            end else
            begin
              Buffer.AppendLn('');
            end;
          end;

          // Close the local filter array
          Buffer.Append('    }');
          if (J < High(A^)) then
          begin
            Buffer.AppendLn(',');
          end else
          begin
            Buffer.AppendLn('');
          end;

          Inc(WorkCount);
          Work(WorkCount);
        end;
      end else
      begin
        Buffer.AppendLn('    {');
        for J := IndexShift to InstructionFilterClasses[I].GetCapacity - 1 do
        begin
          Buffer.Append(Format('        /*%.4x*/ ZYDIS_INVALID', [J]));
          if (J < Integer(InstructionFilterClasses[I].GetCapacity - 1)) then
          begin
            Buffer.AppendLn(',');
          end else
          begin
            Buffer.AppendLn('');
          end;
        end;
        Buffer.AppendLn('    }');
      end;

      // Close the filter array
      Buffer.AppendLn('};');
      if (I < High(InstructionFilterClasses)) then
      begin
        Buffer.AppendLn('');
      end;

    end;
    WorkEnd;

    StringList := TStringList.Create;
    try
      StringList.Text := Buffer.Value;
      StringList.SaveToFile(
        IncludeTrailingPathDelimiter(OutputDirectory) + FILENAME_INSTRUCTIONFILTERS);
    finally
      StringList.Free;
    end;
  finally
    Buffer.Free;
  end;
end;

procedure TCodeGenerator.GenerateInternalStructs(const OutputDirectory: String;
  const MnemonicList: TMnemonicList; const DefinitionList: TIndexedInstructionDefinitionList;
  const OperandMapping: TOperandMapping; const FilterList: TIndexedInstructionFilterList;
  const RegisterList: TRegisterList; const FlagsList: TFlagsList; const CPUIDList: TCPUIDList);
{var
  HighestMnemonicId,
  HighestInstructionDefinitionId,
  HighestOperandDefinitionId,
  HighestInstructionFilterId,
  HighestRegistersId,
  HighestFlagsId,
  HighestCPUIDId: Integer;
  I: Integer;
begin
  HighestMnemonicId := High(MnemonicList);
  HighestInstructionDefinitionId := High(DefinitionList);
  HighestOperandDefinitionId := 0;
  for I := Low(OperandMapping) to High(OperandMapping) do
  begin
    if (High(OperandMapping[I]) > HighestOperandDefinitionId) then
    begin
      HighestOperandDefinitionId := High(OperandMapping[I]);
    end;
  end;
  HighestInstructionFilterId := 0;
  for I := Low(FilterList) to High(FilterList) do
  begin
    if (High(FilterList[I].Value) > HighestInstructionFilterId) then
    begin
      HighestInstructionFilterId := High(FilterList[I].Value);
    end;
  end;
  HighestRegistersId := High(RegisterList);
  HighestFlagsId := High(FlagsList);
  HighestCPUIDId := High(CPUIDList);}
begin
  // TODO:
end;

procedure TCodeGenerator.GenerateMnemonicIncludes(const OutputDirectory: String;
  const MnemonicList: TMnemonicList);
var
  Buffer: TStringBuffer;
  List: TStringList;
  I: Integer;
begin
  List := TStringList.Create;
  try
    WorkStart('Generating mnemonic defines', Low(MnemonicList), High(MnemonicList));
    Buffer := TStringBuffer.Create;
    try
      for I := Low(MnemonicList) to High(MnemonicList) do
      begin
        Buffer.Append(Format('#define /*%.4x*/ ZYDIS_MNEMONIC_%s 0x%.4x', [
          I, AnsiUpperCase(MnemonicList[I]), I]));
        Buffer.AppendLn('');
        Work(I);
      end;
      List.Text := Buffer.Value;
      List.SaveToFile(IncludeTrailingPathDelimiter(OutputDirectory) + FILENAME_MNEMONICDEFINES);
    finally
      Buffer.Free;
    end;
    WorkEnd;
    WorkStart('Generating mnemonic strings', Low(MnemonicList), High(MnemonicList));
    Buffer := TStringBuffer.Create;
    try
      for I := Low(MnemonicList) to High(MnemonicList) do
      begin
        Buffer.Append(Format('  /*%.4x*/ "%s"', [I, AnsiLowerCase(MnemonicList[I])]));
        if (I = High(MnemonicList)) then
        begin
          Buffer.AppendLn('');
        end else
        begin
          Buffer.AppendLn(',');
        end;
        Work(I);
      end;
      List.Text := Buffer.Value;
      List.SaveToFile(IncludeTrailingPathDelimiter(OutputDirectory) + FILENAME_MNEMONICSTRINGS);
    finally
      Buffer.Free;
    end;
    WorkEnd;
  finally
    List.Free;
  end;
end;

procedure TCodeGenerator.GenerateOperandDefinitions(const OutputDirectory: String;
  const OperandMapping: TOperandMapping);

procedure AppendOperand(Buffer: TStringBuffer; Operand: TInstructionOperand);
var
  OperandType,
  OperandEncoding,
  OperandAccessMode: String;
begin
  OperandType := 'UNUSED';
  case Operand.OperandType of
    optGPR8       : OperandType := 'GPR8';
    optGPR16      : OperandType := 'GPR16';
    optGPR32      : OperandType := 'GPR32';
    optGPR64      : OperandType := 'GPR64';
    optFPR        : OperandType := 'FPR';
    optVR64       : OperandType := 'VR64';
    optVR128      : OperandType := 'VR128';
    optVR256      : OperandType := 'VR256';
    optVR512      : OperandType := 'VR512';
    optTR         : OperandType := 'TR';
    optCR         : OperandType := 'CR';
    optDR         : OperandType := 'DR';
    optMSKR       : OperandType := 'MSKR';
    optBNDR       : OperandType := 'BNDR';
    optMem        : OperandType := 'MEM';
    optMem8       : OperandType := 'MEM8';
    optMem16      : OperandType := 'MEM16';
    optMem32      : OperandType := 'MEM32';
    optMem64      : OperandType := 'MEM64';
    optMem80      : OperandType := 'MEM80';
    optMem128     : OperandType := 'MEM128';
    optMem256     : OperandType := 'MEM256';
    optMem512     : OperandType := 'MEM512';
    optMem32Bcst2 : OperandType := 'MEM32_BCST2';
    optMem32Bcst4 : OperandType := 'MEM32_BCST4';
    optMem32Bcst8 : OperandType := 'MEM32_BCST8';
    optMem32Bcst16: OperandType := 'MEM32_BCST16';
    optMem64Bcst2 : OperandType := 'MEM64_BCST2';
    optMem64Bcst4 : OperandType := 'MEM64_BCST4';
    optMem64Bcst8 : OperandType := 'MEM64_BCST8';
    optMem64Bcst16: OperandType := 'MEM64_BCST16';
    optMem112     : OperandType := 'MEM112';
    optMem224     : OperandType := 'MEM224';
    optImm8       : OperandType := 'IMM8';
    optImm16      : OperandType := 'IMM16';
    optImm32      : OperandType := 'IMM32';
    optImm64      : OperandType := 'IMM64';
    optImm8U      : OperandType := 'IMM8U';
    optRel8       : OperandType := 'REL8';
    optRel16      : OperandType := 'REL16';
    optRel32      : OperandType := 'REL32';
    optRel64      : OperandType := 'REL64';
    optPtr1616    : OperandType := 'PTR1616';
    optPtr1632    : OperandType := 'PTR1632';
    optPtr1664    : OperandType := 'PTR1664';
    optMoffs16    : OperandType := 'MOFFS16';
    optMoffs32    : OperandType := 'MOFFS32';
    optMoffs64    : OperandType := 'MOFFS64';
    optSrcIndex8  : OperandType := 'SRCIDX8';
    optSrcIndex16 : OperandType := 'SRCIDX16';
    optSrcIndex32 : OperandType := 'SRCIDX32';
    optSrcIndex64 : OperandType := 'SRCIDX64';
    optDstIndex8  : OperandType := 'DSTIDX8';
    optDstIndex16 : OperandType := 'DSTIDX16';
    optDstIndex32 : OperandType := 'DSTIDX32';
    optDstIndex64 : OperandType := 'DSTIDX64';
    optSREG       : OperandType := 'SREG';
    optMem1616    : OperandType := 'M1616';
    optMem1632    : OperandType := 'M1632';
    optMem1664    : OperandType := 'M1664';
    optMem32VSIBX : OperandType := 'MEM32_VSIBX';
    optMem32VSIBY : OperandType := 'MEM32_VSIBY';
    optMem32VSIBZ : OperandType := 'MEM32_VSIBZ';
    optMem64VSIBX : OperandType := 'MEM64_VSIBX';
    optMem64VSIBY : OperandType := 'MEM64_VSIBY';
    optMem64VSIBZ : OperandType := 'MEM64_VSIBZ';
    optFixed1     : OperandType := 'FIXED1';
    optFixedAL    : OperandType := 'AL';
    optFixedCL    : OperandType := 'CL';
    optFixedAX    : OperandType := 'AX';
    optFixedDX    : OperandType := 'DX';
    optFixedEAX   : OperandType := 'EAX';
    optFixedECX   : OperandType := 'ECX';
    optFixedRAX   : OperandType := 'RAX';
    optFixedES    : OperandType := 'ES';
    optFixedCS    : OperandType := 'CS';
    optFixedSS    : OperandType := 'SS';
    optFixedDS    : OperandType := 'DS';
    optFixedGS    : OperandType := 'GS';
    optFixedFS    : OperandType := 'FS';
    optFixedST0   : OperandType := 'ST0';
  end;
  OperandEncoding := 'NONE';
  case Operand.Encoding of
    opeModrmReg   : OperandEncoding := 'REG';
    opeModrmRm    : OperandEncoding := 'RM';
    opeModrmRmCD1 : OperandEncoding := 'RM';
    opeModrmRmCD2 : OperandEncoding := 'RM_CD2';
    opeModrmRmCD4 : OperandEncoding := 'RM_CD4';
    opeModrmRmCD8 : OperandEncoding := 'RM_CD8';
    opeModrmRmCD16: OperandEncoding := 'RM_CD16';
    opeModrmRmCD32: OperandEncoding := 'RM_CD32';
    opeModrmRmCD64: OperandEncoding := 'RM_CD64';
    opeOpcodeBits : OperandEncoding := 'OPCODE';
    opeVexVVVV    : OperandEncoding := 'VVVV';
    opeEvexAAA    : OperandEncoding := 'AAA';
    opeImm8Lo     : OperandEncoding := 'IMM8_LO';
    opeImm8Hi     : OperandEncoding := 'IMM8_HI';
    opeImm8       : OperandEncoding := 'IMM8';
    opeImm16      : OperandEncoding := 'IMM16';
    opeImm32      : OperandEncoding := 'IMM32';
    opeImm64      : OperandEncoding := 'IMM64';
  end;
  OperandAccessMode := 'READ';
  case Operand.AccessMode of
    opaWrite      : OperandAccessMode := 'WRITE';
    opaReadWrite  : OperandAccessMode := 'READWRITE';
  end;
  Buffer.Append(Format('ZYDIS_OPERAND_DEFINITION(ZYDIS_SEM_OPERAND_TYPE_%s, ' +
    'ZYDIS_OPERAND_ENCODING_%s, ZYDIS_OPERAND_ACCESS_%s)', [
    OperandType, OperandEncoding, OperandAccessMode]));
end;

var
  Buffer: TStringBuffer;
  I, J, K: Integer;
  WorkCount: Integer;
  List: TStringList;
begin
  Buffer := TStringBuffer.Create;
  try
    WorkCount := 0;
    for I := Low(OperandMapping) to High(OperandMapping) do
    begin
      Inc(WorkCount, Length(OperandMapping[I]));
    end;
    WorkStart('Generating operand definitions', 0, WorkCount);
    WorkCount := 0;
    // Generate operand-definition tables
    for I := Low(OperandMapping) to High(OperandMapping) do
    begin
      Buffer.AppendLn(Format('const ZydisOperandDefinition operandDefinitions%d[][%d] =',
        [I, I]));
      Buffer.AppendLn('{');
      for J := Low(OperandMapping[I]) to High(OperandMapping[I]) do
      begin
        Buffer.Append(Format('    /*%.4x*/ { ', [J]));
        for K := 1 to I do
        begin
          AppendOperand(Buffer, OperandMapping[I][J].Operands[K - 1]);
          if (K <> I) then
          begin
            Buffer.Append(', ');
          end;
        end;
        if (J <> High(OperandMapping[I])) then
        begin
          Buffer.AppendLn(' },');
        end else
        begin
          Buffer.AppendLn(' }');
        end;
        Inc(WorkCount);
        Work(WorkCount);
      end;
      // Add dummy operand-definition, if no definitions are present
      if (Length(OperandMapping[I]) = 0) then
      begin
        Buffer.Append(Format('    /*%.4x*/ { ', [0]));
        for K := 1 to I do
        begin
          Buffer.Append('ZYDIS_OPERAND_DEFINITION(ZYDIS_SEM_OPERAND_TYPE_UNUSED, ' +
            'ZYDIS_OPERAND_ENCODING_NONE, ZYDIS_OPERAND_ACCESS_READ)');
          if (K <> I) then
          begin
            Buffer.Append(', ');
          end else
          begin
            Buffer.AppendLn(' }');
          end;
        end;
      end;
      Buffer.AppendLn('};');
      Buffer.AppendLn('');
    end;
    List := TStringList.Create;
    try
      List.Text := Buffer.Value;
      List.SaveToFile(IncludeTrailingPathDelimiter(OutputDirectory) + FILENAME_OPERANDDEFINITIONS);
    finally
      List.Free;
    end;
    WorkEnd;
  finally
    Buffer.Free;
  end;
end;

procedure TCodeGenerator.GenerateCode(Editor: TInstructionEditor;
  const OutputDirectory: String);
var
  Statistics: TCodeGeneratorStatistics;
begin
  GenerateCode(Editor, OutputDirectory, Statistics);
end;

class procedure TCodeGenerator.RegisterLanguageBinding(Binding: TLanguageBindingClass);
begin
  FLanguageBindings.Add(Binding);
end;

procedure TCodeGenerator.Work(WorkCount: Integer);
begin
  if (Assigned(FOnWork)) then
  begin
    FOnWork(Self, WorkCount);
  end;
end;

procedure TCodeGenerator.WorkEnd;
begin
  if (Assigned(FOnWorkEnd)) then
  begin
    FOnWorkEnd(Self);
  end;
end;

procedure TCodeGenerator.WorkStart(const OperationName: String; MinWorkCount,
  MaxWorkCount: Integer);
begin
  if (Assigned(FOnWorkStart)) then
  begin
    FOnWorkStart(Self, OperationName, 6, FCurrentOperationNumber, MinWorkCount, MaxWorkCount);
    Inc(FCurrentOperationNumber);
  end;
end;

{ TLanguageBinding }

constructor TLanguageBinding.Create;
begin
  inherited Create;

end;

{ TLanguageBindingCPP }

class procedure TLanguageBindingCPP.GenerateCode(Generator: TCodeGenerator;
  const OutputDirectory: String);
begin

end;

class function TLanguageBindingCPP.GetName: String;
begin
  Result := 'C++';
end;

{ TLanguageBindingDelphi }

class procedure TLanguageBindingDelphi.GenerateCode(Generator: TCodeGenerator;
  const OutputDirectory: String);
begin

end;

class function TLanguageBindingDelphi.GetName: String;
begin
  Result := 'Delphi';
end;

{ TLanguageBindingPython }

class procedure TLanguageBindingPython.GenerateCode(Generator: TCodeGenerator;
  const OutputDirectory: String);
begin

end;

class function TLanguageBindingPython.GetName: String;
begin
  Result := 'Python';
end;

initialization
  TCodeGenerator.RegisterLanguageBinding(TLanguageBindingCPP);
  TCodeGenerator.RegisterLanguageBinding(TLanguageBindingDelphi);
  TCodeGenerator.RegisterLanguageBinding(TLanguageBindingPython);

end.
