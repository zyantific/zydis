unit untTableGenerator;

interface

uses
  System.Classes, System.Generics.Collections, untInstructionEditor;

type
  TTableGeneratorInfo = record
  public
    FilterCount: Integer;
    DefinitionCount: Integer;
    MnemonicCount: Integer;
    FilterSize: Cardinal;
    DefinitionSize: Cardinal;
    MnemonicSize: Cardinal;
  end;

  TWorkOperation = (
    woIndexingFilters,
    woIndexingDefinitions,
    woGeneratingFilterFiles,
    woGeneratingDefinitionFiles
  );

  TWorkStartEvent = procedure(Sender: TObject; Operation: TWorkOperation;
                      MinWorkCount, MaxWorkCount: Integer) of Object;
  TWorkEvent      = procedure(Sender: TObject; WorkCount: Integer) of Object;

  TTableGenerator = class(TObject)
  strict private type
    TInstructionFilterMap = TObjectDictionary<TInstructionFilterClass, TList<TInstructionFilter>>;
  strict private
    FFilterMap: TInstructionFilterMap;
    FFilterCount: Integer;
    FDefinitionCount: Integer;
    FMnemonicCount: Integer;
    FFilterSize: Cardinal;
    FDefinitionSize: Cardinal;
    FMnemonicSize: Cardinal;
  strict private
    FOnWorkStart: TWorkStartEvent;
    FOnWork: TWorkEvent;
    FOnWorkEnd: TNotifyEvent;
  strict private
    procedure EditorFilterCreated(Sender: TObject; Filter: TInstructionFilter);
  strict private
    procedure WorkStart(Operation: TWorkOperation; MinWorkCount, MaxWorkCount: Integer); inline;
    procedure Work(WorkCount: Integer); inline;
    procedure WorkEnd; inline;
  strict private
    procedure FinalizeFilterTables(Editor: TInstructionEditor);

    function GetNameForTable(FilterClass: TInstructionFilterClass): String; inline;
    function GetNameForType(FilterClass: TInstructionFilterClass): String; inline;
    procedure GenerateFilterFiles(const OutputDirectory: String;
      FilterMap: TInstructionFilterMap; Definitions: TList<TInstructionDefinition>;
      FilterCount: Integer);
    procedure GenerateDefinitionFiles(const OutputDirectory: String;
      Definitions: TList<TInstructionDefinition>);
  public
    procedure GenerateFiles(Editor: TInstructionEditor; const OutputDirectory: String);
  public
    property FilterCount: Integer read FFilterCount;
    property DefinitionCount: Integer read FDefinitionCount;
    property MnemonicCount: Integer read FMnemonicCount;
    property FilterSize: Cardinal read FFilterSize;
    property DefinitionSize: Cardinal read FDefinitionSize;
    property MnemonicSize: Cardinal read FMnemonicSize;
  public
    property OnWorkStart: TWorkStartEvent read FOnWorkStart write FOnWorkStart;
    property OnWork: TWorkEvent read FOnWork write FOnWork;
    property OnWorkEnd: TNotifyEvent read FOnWorkEnd write FOnWorkEnd;
  end;

implementation

uses
  System.SysUtils, System.Generics.Defaults, untInstructionFilters, untHelperClasses;

const
  FILENAME_FILTERTABLES = 'InstructionTable.inc';
  FILTERARRAY_PREFIX_NAME = 'filter';
  FILTERARRAY_PREFIX_TYPENAME = 'ZYDIS_NODETYPE_FILTER_';
  FILTERARRAY_ITEMTYPE = 'ZydisInstructionTableNode';
  FILTERARRAY_MACRO_INVALID = 'ZYDIS_INVALID';
  FILTERARRAY_MACRO_FILTER  = 'ZYDIS_FILTER';
  FILTERARRAY_MACRO_DEFINITION = 'ZYDIS_DEFINITION';
  FILTERARRAY_ITEM_SIZE = 3;

{ TTableGenerator }

procedure TTableGenerator.EditorFilterCreated(Sender: TObject; Filter: TInstructionFilter);
var
  List: TList<TInstructionFilter>;
begin
  if (Filter.IsDefinitionContainer) or (Filter is TEncodingFilter) then Exit;
  if (FFilterMap.ContainsKey(TInstructionFilterClass(Filter.ClassType))) then
  begin
    List := FFilterMap[TInstructionFilterClass(Filter.ClassType)];
  end else
  begin
    List := TList<TInstructionFilter>.Create;
    FFilterMap.Add(TInstructionFilterClass(Filter.ClassType), List);
  end;
  Filter.Data := Pointer(List.Count);
  List.Add(Filter);
  Inc(FFilterCount);
  if (Filter.NeutralElementType in [netNotAvailable, netValue]) then
  begin
    Inc(FFilterSize, Filter.GetCapacity * FILTERARRAY_ITEM_SIZE);
  end else
  begin
    Inc(FFilterSize, (Filter.GetCapacity - 1) * FILTERARRAY_ITEM_SIZE);
  end;
end;

procedure TTableGenerator.FinalizeFilterTables(Editor: TInstructionEditor);
begin
  // Get rid of all encoding-filters as they are only needed in the editor
  // Move LES instruction into the first field of the 3-byte vex-filter
  Assert(not Assigned(Editor.RootTable.Items[$C4].Items[$03].Items[$00]));
  Editor.RootTable.Items[$C4].Items[$03].SetItem($00, Editor.RootTable.Items[$C4].Items[$00]);
  // Move LDS instruction into the first field of the 2-byte vex-filter
  Assert(not Assigned(Editor.RootTable.Items[$C5].Items[$03].Items[$00]));
  Editor.RootTable.Items[$C5].Items[$03].SetItem($00, Editor.RootTable.Items[$C5].Items[$00]);
  // Move BOUND instruction into the first field of the evex-filter
  Assert(not Assigned(Editor.RootTable.Items[$62].Items[$04].Items[$00]));
  Editor.RootTable.Items[$62].Items[$04].SetItem($00, Editor.RootTable.Items[$62].Items[$00]);
  // Move POP instruction into the first field of the xop-filter
  Assert(not Assigned(Editor.RootTable.Items[$8F].Items[$02].Items[$00]));
  Editor.RootTable.Items[$8F].Items[$02].SetItem($00, Editor.RootTable.Items[$8F].Items[$00]);
  // Remove the encoding-filter for 3DNow instructions
  Editor.RootTable.Items[$0F].SetItem($0F, Editor.RootTable.Items[$0F].Items[$0F].Items[$01]);
  // Remove the encoding-filter for 3-byte VEX instructions
  Editor.RootTable.SetItem($C4, Editor.RootTable.Items[$C4].Items[$03]);
  // Remove the encoding-filter for 2-byte VEX instructions
  Editor.RootTable.SetItem($C5, Editor.RootTable.Items[$C5].Items[$03]);
  // Remove the encoding-filter for EVEX instructions
  Editor.RootTable.SetItem($62, Editor.RootTable.Items[$62].Items[$04]);
  // Remove the encoding-filter for XOP instructions
  Editor.RootTable.SetItem($8F, Editor.RootTable.Items[$8f].Items[$02]);
end;

procedure TTableGenerator.GenerateDefinitionFiles(const OutputDirectory: String;
  Definitions: TList<TInstructionDefinition>);
begin
  WorkStart(woGeneratingDefinitionFiles, 0, Definitions.Count);

  WorkEnd;
end;

procedure TTableGenerator.GenerateFiles(Editor: TInstructionEditor; const OutputDirectory: String);
var
  E: TInstructionEditor;
  D: TInstructionDefinition;
  I: Integer;
  Definitions: TList<TInstructionDefinition>;
  Comparison: TComparison<TInstructionDefinition>;
begin
  if (not Assigned(Editor.RootTable)) then
  begin
    raise Exception.Create('The instruction editor does not contain tables.');
  end;
  if (Editor.RootTable.HasConflicts) then
  begin
    //raise Exception.Create('The instruction editor has unresolved conflicts.');
  end;
  FDefinitionCount := Editor.DefinitionCount;
  E := TInstructionEditor.Create;
  try
    E.OnFilterCreated := EditorFilterCreated;
    E.BeginUpdate;
    try
      FFilterMap := TObjectDictionary<TInstructionFilterClass,
        TList<TInstructionFilter>>.Create([doOwnsValues]);
      try
        E.Reset;
        // Create filter indizes by copying all definitions to the internal editor instance
        WorkStart(woIndexingFilters, 0, Editor.DefinitionCount);
        for I := 0 to Editor.DefinitionCount - 1 do
        begin
          D := E.CreateDefinition('unnamed');
          D.Assign(Editor.Definitions[I]);
          Work(I + 1);
        end;
        WorkEnd;
        FinalizeFilterTables(E);
        Definitions := TList<TInstructionDefinition>.Create;
        try
          // Create definition indizes and a sorted definition-list
          WorkStart(woIndexingDefinitions, 0, E.DefinitionCount * 2);
          for I := 0 to E.DefinitionCount - 1 do
          begin
            Definitions.Add(E.Definitions[I]);
            Work(I + 1);
          end;
          Comparison :=
            function(const Left, Right: TInstructionDefinition): Integer
            begin
              Result := CompareStr(Left.Mnemonic, Right.Mnemonic);
            end;
          Definitions.Sort(TComparer<TInstructionDefinition>.Construct(Comparison));
          for I := 0 to Definitions.Count - 1 do
          begin
            Definitions[I].Data := Pointer(I);
            Work(E.DefinitionCount + I + 1);
          end;
          WorkEnd;
          // Generate files
          GenerateFilterFiles(OutputDirectory, FFilterMap, Definitions, E.FilterCount);
          GenerateDefinitionFiles(OutputDirectory, Definitions);
        finally
          Definitions.Free;
        end;
      finally
        FFilterMap.Free;
      end;
    finally
      E.EndUpdate;
    end;
  finally
    E.Free;
  end;
end;

procedure TTableGenerator.GenerateFilterFiles(const OutputDirectory: String;
  FilterMap: TInstructionFilterMap; Definitions: TList<TInstructionDefinition>;
  FilterCount: Integer);
var
  WorkCount, IndexShift: Integer;
  Buffer: TStringBuffer;
  StringList: TStringList;
  I, J, K: Integer;
  FilterList: TList<TInstructionFilter>;
begin
  Buffer := TStringBuffer.Create;
  try
    WorkCount := 0;
    WorkStart(woGeneratingFilterFiles, 0, FilterCount);
    for I := Low(InstructionFilterClasses) to High(InstructionFilterClasses) do
    begin
      IndexShift := 1;
      if (InstructionFilterClasses[I].GetNeutralElementType in [netNotAvailable, netValue]) then
      begin
        IndexShift := 0;
      end;
      Buffer.AppendLn(Format('const %s %s%s[][%d] = ', [
        FILTERARRAY_ITEMTYPE,
        FILTERARRAY_PREFIX_NAME, GetNameForTable(InstructionFilterClasses[I]),
        Integer(InstructionFilterClasses[I].GetCapacity) - IndexShift]));
      Buffer.AppendLn('{');
      if (FilterMap.ContainsKey(InstructionFilterClasses[I])) then
      begin
        FilterList := FilterMap[InstructionFilterClasses[I]];
        for J := 0 to FilterList.Count - 1 do
        begin
          Buffer.AppendLn('    {');
          for K := IndexShift to FilterList[J].Capacity - 1 do
          begin
            Buffer.Append(Format('        /*%.4x*/ ', [K]));
            if (not Assigned(FilterList[J].Items[K])) then
            begin
              Buffer.Append(FILTERARRAY_MACRO_INVALID);
            end else if (FilterList[J].Items[K] is TDefinitionContainer) then
            begin
              Assert((FilterList[J].Items[K] as TDefinitionContainer).DefinitionCount > 0);
              Buffer.Append(Format('%s(0x%.4x)', [FILTERARRAY_MACRO_DEFINITION,
                Integer((FilterList[J].Items[K] as TDefinitionContainer).Definitions[0].Data)]));
            end else
            begin
              Buffer.Append(Format('%s(%s%s, 0x%.4x)', [FILTERARRAY_MACRO_FILTER,
                FILTERARRAY_PREFIX_TYPENAME,
                GetNameForType(TInstructionFilterClass(FilterList[J].Items[K].ClassType)),
                Integer(FilterList[J].Items[K].Data)]));
            end;
            if (K < Integer(FilterList[J].Capacity - 1)) then
            begin
              Buffer.AppendLn(',');
            end else
            begin
              Buffer.AppendLn('');
            end;
          end;
          Buffer.Append('    }');
          if (J < FilterList.Count - 1) then
          begin
            Buffer.AppendLn(',');
          end else
          begin
            Buffer.AppendLn('');
          end;
          Inc(WorkCount);
          Work(WorkCount);
        end;
      end;
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
      StringList.SaveToFile(IncludeTrailingPathDelimiter(OutputDirectory) + FILENAME_FILTERTABLES);
    finally
      StringList.Free;
    end;
  finally
    Buffer.Free;
  end;
end;

function TTableGenerator.GetNameForTable(FilterClass: TInstructionFilterClass): String;
begin
  Result := FilterClass.GetDescription;
end;

function TTableGenerator.GetNameForType(FilterClass: TInstructionFilterClass): String;
begin
  Result := AnsiUpperCase(FilterClass.GetDescription);
end;

procedure TTableGenerator.Work(WorkCount: Integer);
begin
  if (Assigned(FOnWork)) then
  begin
    FOnWork(Self, WorkCount);
  end;
end;

procedure TTableGenerator.WorkEnd;
begin
  if (Assigned(FOnWorkEnd)) then
  begin
    FOnWorkEnd(Self);
  end;
end;

procedure TTableGenerator.WorkStart(Operation: TWorkOperation; MinWorkCount, MaxWorkCount: Integer);
begin
  if (Assigned(FOnWorkStart)) then
  begin
    FOnWorkStart(Self, Operation, MinWorkCount, MaxWorkCount);
  end;
end;

end.
