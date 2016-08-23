unit untHelperClasses;

interface

uses
  System.Classes, System.Generics.Collections, SynCrossPlatformJSON;

type
  TSizeFormatter = record
  public
    class function Format(Size: UInt64): String; static;
  end;

  TStringHelper = record
  public
    {**
     * Fast alternative to the @c System.StrUtils.IndexStr function
     *
     * @param S       The string to search for.
     * @param Values  The array of strings to search in.
     *
     * @return The index of @c S in the @c Values array or -1, if not found.
     *}
    class function IndexStr(const S: String; const Values: array of String): Integer; static;
    {**
     * Fast alternative to the @c System.SysUtils.AnsiLowerCase function
     *
     * @param S A reference to the target string.
     *}
    class procedure AnsiLowerCase(var S: String); static;
  end;

  TJSONHelper = record
  public
    class function JSONToString(JSON: PJSONVariantData; const Ident: String = ''): String; static;
  end;

  TStringBuffer = class(TObject)
  strict private
    FBuffer: array of Char;
    FPosition: Integer;
    FCapacity: Integer;
    FChunkSize: Integer;
  strict private
    function GetValue: String; inline;
  public
    procedure Append(const S: String);
    procedure AppendLn(const S: String);
  public
    constructor Create;
  public
    property Value: String read GetValue;
    property ChunkSize: Integer read FChunkSize write FChunkSize;
  end;

implementation

uses
  System.SysUtils, System.Variants;

{ TSizeFormatter }

class function TSizeFormatter.Format(Size: UInt64): String;
const
  SZ_KB = 1024;
  SZ_MB = 1024 * 1024;
  SZ_GB = 1024 * 1024;
var
  Format: TFormatSettings;
begin
  Format := System.SysUtils.FormatSettings;
  Format.DecimalSeparator := '.';
  if (Size >= SZ_GB) then
  begin
    Result := FormatFloat('0.00 GiB', Size / SZ_GB, Format);
  end else if (Size >= SZ_MB) then
  begin
    Result := FormatFloat('0.00 MiB', Size / SZ_MB, Format);
  end else if (Size >= SZ_KB) then
  begin
    Result := FormatFloat('0.00 KiB', Size / SZ_KB, Format);
  end else
  begin
    Result := FormatFloat('0.00 Byte', Size, Format);
  end;
end;

{ TStringHelper }

class function TStringHelper.IndexStr(const S: String; const Values: array of String): Integer;
var
  L, I, J: Integer;
  B: Boolean;
begin
  Result := -1;
  L := Length(S);
  for I := Low(Values) to High(Values) do
  begin
    if (L <> Length(Values[I])) then Continue;
    B := true;
    for J := 1 to Length(S) do
    begin
      if (S[J] <> Values[I][J]) then
      begin
        B := false;
        Continue;
      end;
    end;
    if (B) then
    begin
      Result := I;
      Break;
    end;
  end;
end;

class procedure TStringHelper.AnsiLowerCase(var S: String);
const
  Lower: array of Char =
    ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
     't', 'u', 'v', 'w', 'x', 'y', 'z'];
var
  I: Integer;
begin
  for I := 1 to Length(S) do
  begin
    if (CharInSet(S[I], ['A'..'Z'])) then
    begin
      S[I] := Lower[Ord(S[I]) - Ord('A')];
    end;
  end;
end;

{ TJSONHelper }

class function TJSONHelper.JSONToString(JSON: PJSONVariantData; const Ident: String = ''): String;

// TODO: This helper function needs refactoring

procedure JSONToString(Buffer: TStringBuffer; JSON: PJSONVariantData; const Ident: String = '');

procedure ValueToJSON(Buffer: TStringBuffer; const Value: Variant);
var
  I64: Int64;
  B: Boolean;
  S: String;
begin
  if (TVarData(Value).VType = JSONVariantType.VarType) then
  begin
    JSONToString(Buffer, @TJSONVariantData(Value), Ident + '  ');
  end else if (TVarData(Value).VType = varByRef or varVariant) then
  begin
    ValueToJSON(Buffer, PVariant(TVarData(Value).VPointer)^)
  end else if (TVarData(Value).VType <= varNull) then
  begin
    Buffer.Append('null');
  end else if (TVarData(Value).VType = varBoolean) then
  begin
    B := Value;
    Buffer.Append(LowerCase(BoolToStr(B, true)));
  end else if (VarIsOrdinal(Value)) then
  begin
    I64 := Value;
    Buffer.Append(IntToStr(I64));
  end else if (TVarData(Value).VType = varDate) then
  begin
    Buffer.Append(DateTimeToJSON(TVarData(Value).VDouble));
  end else if (VarIsFloat(Value)) then
  begin
    DoubleToJSON(Value, S);
    Buffer.Append(S);
  end else if (VarIsStr(Value)) then
  begin
    Buffer.Append(StringToJSON(Value));
  end else
  begin
    Buffer.Append(Value);
  end;
end;

var
  I: Integer;
begin
  case JSON.Kind of
    jvObject:
      begin
        Buffer.AppendLn('{');
        for I := 0 to JSON.Count - 1 do
        begin
          Buffer.Append(Ident);
          Buffer.Append('  ');
          Buffer.Append(StringToJSON(JSON.Names[I]) + ': ');
          ValueToJSON(Buffer, JSON.Values[I]);
          if (I = JSON.Count - 1) then
          begin
            Buffer.AppendLn('');
          end else
          begin
            Buffer.AppendLn(',');
          end;
        end;
        Buffer.Append(Ident);
        Buffer.Append('}');
      end;
    jvArray:
      begin
        Buffer.AppendLn('[');
        for I := 0 to JSON.Count - 1 do
        begin
          Buffer.Append(Ident);
          Buffer.Append('  ');
          ValueToJSON(Buffer, JSON.Values[I]);
          if (I = JSON.Count - 1) then
          begin
            Buffer.AppendLn('');
          end else
          begin
            Buffer.AppendLn(',');
          end;
        end;
        Buffer.Append(Ident);
        Buffer.Append(']');
      end else
      begin
        Buffer.Append('null');
      end;
  end;
end;

var
  Buffer: TStringBuffer;
begin
  Buffer := TStringBuffer.Create;
  try
    JSONToString(Buffer, JSON, Ident);
    Result := Buffer.Value;
  finally
    Buffer.Free;
  end;
end;

{ TStringBuffer }

procedure TStringBuffer.Append(const S: String);
var
  L: Integer;
begin
  L := Length(S);
  while (FPosition + L > FCapacity) do
  begin
    Inc(FCapacity, FChunkSize);
    SetLength(FBuffer, FCapacity);
  end;
  Move(S[1], FBuffer[FPosition], L * SizeOf(FBuffer[0]));
  Inc(FPosition, L);
end;

procedure TStringBuffer.AppendLn(const S: String);
begin
  Append(S);
  Append(sLineBreak);
end;

constructor TStringBuffer.Create;
begin
  inherited Create;
  FChunkSize := 1024 * 16;
  FCapacity := FChunkSize;
  SetLength(FBuffer, FChunkSize);
end;

function TStringBuffer.GetValue: String;
begin
  SetLength(Result, FPosition);
  Move(FBuffer[0], Result[1], FPosition * SizeOf(FBuffer[0]));
end;

end.
