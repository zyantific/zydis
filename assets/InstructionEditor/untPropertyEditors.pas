unit untPropertyEditors;

interface

uses
  cxOI;

type
  TOpcodeByteProperty = class(TcxOrdinalProperty)
  public
    function GetValue: String; override;
    procedure SetValue(const Value: String); override;
  end;

  TCPUIDFeatureFlagsProperty = class(TcxClassProperty)
  public
    procedure Edit; override;
    function GetAttributes: TcxPropertyAttributes; override;
    function GetValue: String; override;
    procedure SetValue(const Value: String); override;
    function IsDefaultValue: Boolean; override;
  end;

  TX86RegistersProperty = class(TcxClassProperty)
  public
    procedure Edit; override;
    function GetAttributes: TcxPropertyAttributes; override;
    function GetValue: String; override;
    procedure SetValue(const Value: String); override;
    function IsDefaultValue: Boolean; override;
  end;

  TInstructionOperandProperty = class(TcxClassProperty)
  public
    function GetAttributes: TcxPropertyAttributes; override;
    function GetValue: String; override;
    procedure SetValue(const Value: String); override;
    function IsDefaultValue: Boolean; override;
  end;

implementation

uses
  System.SysUtils, System.TypInfo, System.Classes, Vcl.Forms, Zydis.InstructionEditor,
  untHelperClasses, formEditorCPUIDFeatureFlags, formEditorX86Registers, cxButtonEdit;

{ TOpcodeByteProperty }

function TOpcodeByteProperty.GetValue: String;
begin
  Result := IntToHex(GetOrdValue, 2);
end;

procedure TOpcodeByteProperty.SetValue(const Value: String);
var
  V: Integer;
begin
  if (not TryStrToInt('$' + Value, V)) then
  begin
    raise Exception.CreateFmt('"%s" is not a valid hexadecimal value.', [Value]);
  end;
  if (V < 0) or (V > 255) then
  begin
    raise Exception.Create('Value has to be between 0 and 255.');
  end;
  SetOrdValue(V);
end;

{ TCPUIDFeatureFlagsProperty }

procedure TCPUIDFeatureFlagsProperty.Edit;
var
  Form: TfrmEditorCPUIDFeatureFlags;
begin
  Form := TfrmEditorCPUIDFeatureFlags.Create(Application);
  try
    Form.Caption := GetComponent(0).GetNamePath + '.' + GetName;
    Form.FeatureFlags := TCPUIDFeatureFlags(GetOrdValue).FeatureFlags;
    Form.ShowModal;
    if (Form.ApplyChanges) then
    begin
      TCPUIDFeatureFlags(GetOrdValue).FeatureFlags := Form.FeatureFlags;
      PostChangedNotification;
    end;
  finally
    Form.Free;
  end;
end;

function TCPUIDFeatureFlagsProperty.GetAttributes: TcxPropertyAttributes;
begin
  Result := [ipaDialog];
end;

function TCPUIDFeatureFlagsProperty.GetValue: String;
var
  CPUIDFeatureFlags: TCPUIDFeatureFlagSet;
  CPUIDFeatureFlag: TCPUIDFeatureFlag;
  S: String;
begin
  Result := 'NONE';
  CPUIDFeatureFlags := TCPUIDFeatureFlags(GetOrdValue).FeatureFlags;
  if (CPUIDFeatureFlags <> []) then
  begin
    Result := '';
    for CPUIDFeatureFlag in CPUIDFeatureFlags do
    begin
      S := GetEnumName(TypeInfo(TCPUIDFeatureFlag), Ord(CPUIDFeatureFlag));
      Delete(S, 1, 2);
      Result := Result + S + ', ';
    end;
    if (Result <> '') then
    begin
      Delete(Result, Length(Result) - 1, 2);
    end;
  end;
end;

function TCPUIDFeatureFlagsProperty.IsDefaultValue: Boolean;
begin
  Result := (TCPUIDFeatureFlags(GetOrdValue).FeatureFlags = []);
end;

procedure TCPUIDFeatureFlagsProperty.SetValue(const Value: String);
var
  S: String;
  I: Integer;
  C: Char;
  A: TArray<String>;
  F: TCPUIDFeatureFlag;
  FeatureFlags: TCPUIDFeatureFlagSet;
begin
  if (Value = '') then
  begin
    TCPUIDFeatureFlags(GetOrdValue).FeatureFlags := [];
    Exit;
  end;
  SetLength(S, Length(Value));
  I := 1;
  for C in Value do
  begin
    if (CharInSet(C, ['a'..'z', 'A'..'Z', '0'..'9', ','])) then
    begin
      S[I] := C;
      Inc(I);
    end;
  end;
  SetLength(S, I - 1);
  TStringHelper.AnsiLowerCase(S);
  A := S.Split([',']);
  FeatureFlags := [];
  for F := Low(TCPUIDFeatureFlag) to High(TCPUIDFeatureFlag) do
  begin
    S := GetEnumName(TypeInfo(TCPUIDFeatureFlag), Ord(F));
    Delete(S, 1, 2);
    TStringHelper.AnsiLowerCase(S);
    for I := Low(A) to High(A) do
    begin
      if (A[I] = S) then
      begin
        Include(FeatureFlags, F);
      end;
    end;
  end;
  TCPUIDFeatureFlags(GetOrdValue).FeatureFlags := FeatureFlags;
end;

{ TX86RegistersProperty }

procedure TX86RegistersProperty.Edit;
var
  Form: TfrmEditorX86Registers;
begin
  Form := TfrmEditorX86Registers.Create(Application);
  try
    Form.Caption := GetComponent(0).GetNamePath + '.' + GetName;
    Form.Registers := TX86Registers(GetOrdValue).Registers;
    Form.ShowModal;
    if (Form.ApplyChanges) then
    begin
      TX86Registers(GetOrdValue).Registers := Form.Registers;
      PostChangedNotification;
    end;
  finally
    Form.Free;
  end;
end;

function TX86RegistersProperty.GetAttributes: TcxPropertyAttributes;
begin
  Result := [ipaDialog];
end;

function TX86RegistersProperty.GetValue: String;
var
  X86Registers: TX86RegisterSet;
  X86Register: TX86Register;
  S: String;
begin
  Result := 'NONE';
  X86Registers := TX86Registers(GetOrdValue).Registers;
  if (TX86Registers(GetOrdValue).Registers <> []) and
    (TX86Registers(GetOrdValue).Registers <> [regNone]) then
  begin
    Result := '';
    for X86Register in X86Registers do
    begin
      S := GetEnumName(TypeInfo(TX86Register), Ord(X86Register));
      Delete(S, 1, 3);
      Result := Result + S + ', ';
    end;
    if (Result <> '') then
    begin
      Delete(Result, Length(Result) - 1, 2);
    end;
  end;
end;

function TX86RegistersProperty.IsDefaultValue: Boolean;
begin
  Result := (TX86Registers(GetOrdValue).Registers = []) or
    (TX86Registers(GetOrdValue).Registers = [regNone])
end;

procedure TX86RegistersProperty.SetValue(const Value: String);
var
  S: String;
  I: Integer;
  C: Char;
  A: TArray<String>;
  R: TX86Register;
  Registers: TX86RegisterSet;
begin
  if (Value = '') then
  begin
    TX86Registers(GetOrdValue).Registers := [];
    Exit;
  end;
  SetLength(S, Length(Value));
  I := 1;
  for C in Value do
  begin
    if (CharInSet(C, ['a'..'z', 'A'..'Z', '0'..'9', ','])) then
    begin
      S[I] := C;
      Inc(I);
    end;
  end;
  SetLength(S, I - 1);
  TStringHelper.AnsiLowerCase(S);
  A := S.Split([',']);
  Registers := [];
  for R := Low(TX86Register) to High(TX86Register) do
  begin
    S := GetEnumName(TypeInfo(TX86Register), Ord(R));
    Delete(S, 1, 3);
    TStringHelper.AnsiLowerCase(S);
    for I := Low(A) to High(A) do
    begin
      if (A[I] = S) then
      begin
        Include(Registers, R);
      end;
    end;
  end;
  TX86Registers(GetOrdValue).Registers := Registers;
end;

{ TInstructionOperandProperty }

function TInstructionOperandProperty.GetAttributes: TcxPropertyAttributes;
begin
  Result := [ipaSubProperties];
end;

function TInstructionOperandProperty.GetValue: String;
begin
  Result := TInstructionOperand(GetOrdValue).GetDescription;
  if (TInstructionOperand(GetOrdValue).OperandType = optUnused) then
  begin
    Result := 'unused';
  end;
end;

function TInstructionOperandProperty.IsDefaultValue: Boolean;
begin
  Result := (TInstructionOperand(GetOrdValue).OperandType = optUnused);
end;

procedure TInstructionOperandProperty.SetValue(const Value: String);
var
  S, R: String;
  I: Integer;
  C: Char;
  A: TArray<String>;
  T: TOperandType;
begin
  if (Value = '') then
  begin
    TInstructionOperand(GetOrdValue).OperandType := optUnused;
    Exit;
  end;
  SetLength(S, Length(Value));
  I := 1;
  for C in Value do
  begin
    if (CharInSet(C, ['a'..'z', 'A'..'Z', '0'..'9', '('])) then
    begin
      S[I] := C;
      Inc(I);
    end;
  end;
  SetLength(S, I - 1);
  TStringHelper.AnsiLowerCase(S);
  A := S.Split(['(']);
  for T := Low(TOperandType) to High(TOperandType) do
  begin
    R := GetEnumName(TypeInfo(TOperandType), Ord(T));
    Delete(R, 1, 3);
    TStringHelper.AnsiLowerCase(R);
    if (A[0] = R) then
    begin
      TInstructionOperand(GetOrdValue).OperandType := T;
      Break;
    end;
  end;
  if (Length(A) >= 1) then
  begin
    if      (A[1] = 'r')  then TInstructionOperand(GetOrdValue).AccessMode := opaRead
    else if (A[1] = 'w')  then TInstructionOperand(GetOrdValue).AccessMode := opaWrite
    else if (A[1] = 'rw') then TInstructionOperand(GetOrdValue).AccessMode := opaReadWrite;
  end;
end;

initialization
  // Register custom property editor for hexadecimal display of TOpcodeByte values
  cxRegisterPropertyEditor(TypeInfo(TOpcodeByte), nil, '', TOpcodeByteProperty);

  // Register custom property editors for easy modification of the instruction-operands
  cxRegisterPropertyEditor(TypeInfo(TInstructionOperand), nil, '', TInstructionOperandProperty);

  // Delphi does not allow sets > 4 bytes as published values, so we have to use a wrapper class
  // and a custom editor
  cxRegisterPropertyEditor(TypeInfo(TCPUIDFeatureFlags), nil, '', TCPUIDFeatureFlagsProperty);
  cxRegisterEditPropertiesClass(TCPUIDFeatureFlagsProperty, TcxButtonEditProperties);
  cxRegisterPropertyEditor(TypeInfo(TX86Registers), nil, '', TX86RegistersProperty);
  cxRegisterEditPropertiesClass(TX86RegistersProperty, TcxButtonEditProperties);

end.
