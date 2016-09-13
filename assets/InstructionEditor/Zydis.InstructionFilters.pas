unit Zydis.InstructionFilters;

interface

uses
  Zydis.InstructionEditor;

type
  TOpcodeFilter = class(TInstructionFilter)
  public
    class function GetCapacity: Cardinal; override;
    class function GetInsertPosition(const Definition: TInstructionDefinition): Integer; override;
    class function GetDescription: String; override;
  end;

  TEncodingFilter = class(TInstructionFilter)
  public
    class function GetNeutralElementType: TNeutralElementType; override;
    class function GetCapacity: Cardinal; override;
    class function GetInsertPosition(const Definition: TInstructionDefinition): Integer; override;
    class function GetItemDescription(Index: Integer): String; override;
    class function GetDescription: String; override;
  end;

  TVEXMapFilter = class(TInstructionFilter)
  public
    class function GetCapacity: Cardinal; override;
    class function GetInsertPosition(const Definition: TInstructionDefinition): Integer; override;
    class function GetItemDescription(Index: Integer): String; override;
    class function GetDescription: String; override;
  end;

  TXOPMapFilter = class(TInstructionFilter)
  public
    class function GetCapacity: Cardinal; override;
    class function GetInsertPosition(const Definition: TInstructionDefinition): Integer; override;
    class function GetItemDescription(Index: Integer): String; override;
    class function GetDescription: String; override;
  end;

  TModeFilter = class(TInstructionFilter)
  public
    class function GetNeutralElementType: TNeutralElementType; override;
    class function GetCapacity: Cardinal; override;
    class function GetInsertPosition(const Definition: TInstructionDefinition): Integer; override;
    class function GetItemDescription(Index: Integer): String; override;
    class function GetDescription: String; override;
  end;

  TMandatoryPrefixFilter = class(TInstructionFilter)
  public
    class function GetNeutralElementType: TNeutralElementType; override;
    class function GetCapacity: Cardinal; override;
    class function GetInsertPosition(const Definition: TInstructionDefinition): Integer; override;
    class function GetItemDescription(Index: Integer): String; override;
    class function GetDescription: String; override;
  end;

  TModrmModFilter = class(TInstructionFilter)
  public
    class function GetNeutralElementType: TNeutralElementType; override;
    class function GetCapacity: Cardinal; override;
    class function GetInsertPosition(const Definition: TInstructionDefinition): Integer; override;
    class function GetItemDescription(Index: Integer): String; override;
    class function GetDescription: String; override;
  end;

  TModrmRegFilter = class(TInstructionFilter)
  public
    class function GetNeutralElementType: TNeutralElementType; override;
    class function GetCapacity: Cardinal; override;
    class function GetInsertPosition(const Definition: TInstructionDefinition): Integer; override;
    class function GetItemDescription(Index: Integer): String; override;
    class function GetDescription: String; override;
  end;

  TModrmRmFilter = class(TInstructionFilter)
  public
    class function GetNeutralElementType: TNeutralElementType; override;
    class function GetCapacity: Cardinal; override;
    class function GetInsertPosition(const Definition: TInstructionDefinition): Integer; override;
    class function GetItemDescription(Index: Integer): String; override;
    class function GetDescription: String; override;
  end;

  TOperandSizeFilter = class(TInstructionFilter)
  public
    class function GetNeutralElementType: TNeutralElementType; override;
    class function GetCapacity: Cardinal; override;
    class function GetInsertPosition(const Definition: TInstructionDefinition): Integer; override;
    class function GetItemDescription(Index: Integer): String; override;
    class function GetDescription: String; override;
  end;

  TAddressSizeFilter = class(TInstructionFilter)
  public
    class function GetNeutralElementType: TNeutralElementType; override;
    class function GetCapacity: Cardinal; override;
    class function GetInsertPosition(const Definition: TInstructionDefinition): Integer; override;
    class function GetItemDescription(Index: Integer): String; override;
    class function GetDescription: String; override;
  end;

  TRexWFilter = class(TInstructionFilter)
  public
    class function GetNeutralElementType: TNeutralElementType; override;
    class function GetCapacity: Cardinal; override;
    class function GetInsertPosition(const Definition: TInstructionDefinition): Integer; override;
    class function GetItemDescription(Index: Integer): String; override;
    class function GetDescription: String; override;
  end;

  TVexLFilter = class(TInstructionFilter)
  public
    class function GetNeutralElementType: TNeutralElementType; override;
    class function GetCapacity: Cardinal; override;
    class function GetInsertPosition(const Definition: TInstructionDefinition): Integer; override;
    class function GetItemDescription(Index: Integer): String; override;
    class function GetDescription: String; override;
  end;

  TEvexL2Filter = class(TInstructionFilter)
  public
    class function GetNeutralElementType: TNeutralElementType; override;
    class function GetCapacity: Cardinal; override;
    class function GetInsertPosition(const Definition: TInstructionDefinition): Integer; override;
    class function GetItemDescription(Index: Integer): String; override;
    class function GetDescription: String; override;
  end;

  TEvexBFilter = class(TInstructionFilter)
  public
    class function GetNeutralElementType: TNeutralElementType; override;
    class function GetCapacity: Cardinal; override;
    class function GetInsertPosition(const Definition: TInstructionDefinition): Integer; override;
    class function GetItemDescription(Index: Integer): String; override;
    class function GetDescription: String; override;
  end;

const
  InstructionFilterClasses: array[0..14] of TInstructionFilterClass =
  (
    TOpcodeFilter,
    TEncodingFilter,
    TVEXMapFilter,
    TXOPMapFilter,
    TModeFilter,
    TMandatoryPrefixFilter,
    TModrmModFilter,
    TModrmRegFilter,
    TModrmRmFilter,
    TOperandSizeFilter,
    TAddressSizeFilter,
    TRexWFilter,
    TVexLFilter,
    TEvexL2Filter,
    TEvexBFilter
  );

implementation

uses
  System.SysUtils, System.TypInfo;

{$REGION 'Class: TOpcodeFilter'}
class function TOpcodeFilter.GetCapacity: Cardinal;
begin
  Result := 256;
end;

class function TOpcodeFilter.GetDescription: String;
begin
  Result := 'Opcode';
end;

class function TOpcodeFilter.GetInsertPosition(const Definition: TInstructionDefinition): Integer;
begin
  Result := Definition.Opcode;
end;
{$ENDREGION}

{$REGION 'Class: TEncodingFilter'}
class function TEncodingFilter.GetCapacity: Cardinal;
begin
  Result := 5;
end;

class function TEncodingFilter.GetDescription: String;
begin
  Result := 'Encoding';
end;

class function TEncodingFilter.GetInsertPosition(const Definition: TInstructionDefinition): Integer;
begin
  Result := Integer(Definition.Encoding);
end;

class function TEncodingFilter.GetItemDescription(Index: Integer): String;
begin
  Assert((Index >= 0) and (Index < Integer(GetCapacity)));
  Result := GetEnumName(TypeInfo(TInstructionEncoding), Index);
end;

class function TEncodingFilter.GetNeutralElementType: TNeutralElementType;
begin
  Result := netValue;
end;
{$ENDREGION}

{$REGION 'Class: TVEXMapFilter'}
class function TVEXMapFilter.GetCapacity: Cardinal;
begin
  Result := 16;
end;

class function TVEXMapFilter.GetDescription: String;
begin
  Result := 'VEX';
end;

class function TVEXMapFilter.GetInsertPosition(const Definition: TInstructionDefinition): Integer;
begin
  Assert(Definition.OpcodeMap < omXOP8);
  Result := (Integer(Definition.OpcodeExtensions.MandatoryPrefix)) * 4 + Byte(Definition.OpcodeMap);
end;

class function TVEXMapFilter.GetItemDescription(Index: Integer): String;
begin
  Assert((Index >= 0) and (Index < Integer(GetCapacity)));
  case (Index div 4) of
    0: Result := '##';
    1: Result := '66';
    2: Result := 'F3';
    3: Result := 'F2';
  end;
  case (Index mod 4) of
    0: Result := Result + ' default';
    1: Result := Result + ' 0F';
    2: Result := Result + ' 0F 38';
    3: Result := Result + ' 0F 3A';
  end;
end;
{$ENDREGION}

{$REGION 'Class: TXOPMapFilter'}
class function TXOPMapFilter.GetCapacity: Cardinal;
begin
  Result := 4;
end;

class function TXOPMapFilter.GetDescription: String;
begin
  Result := 'XOP';
end;

class function TXOPMapFilter.GetInsertPosition(const Definition: TInstructionDefinition): Integer;
begin
  Assert(Definition.Encoding   = ieXOP);
  Assert(Definition.OpcodeMap >= omXOP8);
  Result := Integer(Definition.OpcodeMap) - Integer(omXOP8) + 1;
end;

class function TXOPMapFilter.GetItemDescription(Index: Integer): String;
begin
  Assert((Index >= 0) and (Index < Integer(GetCapacity)));
  if (Index = 0) then
  begin
    Result := 'Non-XOP-Placeholder';
  end else
  begin
    Result := GetEnumName(TypeInfo(TOpcodeMap), Integer(omXOP8) + Index - 1);
  end;
end;
{$ENDREGION}

{$REGION 'Class: TModeFilter'}
class function TModeFilter.GetCapacity: Cardinal;
begin
  Result := 3;
end;

class function TModeFilter.GetDescription: String;
begin
  Result := 'Mode';
end;

class function TModeFilter.GetInsertPosition(const Definition: TInstructionDefinition): Integer;
begin
  Result := Integer(Definition.OpcodeExtensions.Mode);
end;

class function TModeFilter.GetItemDescription(Index: Integer): String;
begin
  Assert((Index >= 0) and (Index < Integer(GetCapacity)));
  Result := GetEnumName(TypeInfo(TExtInstructionMode), Index);
end;

class function TModeFilter.GetNeutralElementType: TNeutralElementType;
begin
  Result := netPlaceholder;
end;
{$ENDREGION}

{$REGION 'Class: TMandatoryPrefixFilter'}
class function TMandatoryPrefixFilter.GetCapacity: Cardinal;
begin
  Result := 4;
end;

class function TMandatoryPrefixFilter.GetDescription: String;
begin
  Result := 'MandatoryPrefix';
end;

class function TMandatoryPrefixFilter.GetInsertPosition(
  const Definition: TInstructionDefinition): Integer;
begin
  Result := Integer(Definition.OpcodeExtensions.MandatoryPrefix);
end;

class function TMandatoryPrefixFilter.GetItemDescription(Index: Integer): String;
begin
  Assert((Index >= 0) and (Index < Integer(GetCapacity)));
  Result := GetEnumName(TypeInfo(TExtMandatoryPrefix), Index);
end;

class function TMandatoryPrefixFilter.GetNeutralElementType: TNeutralElementType;
begin
  Result := netValue;
end;
{$ENDREGION}

{$REGION 'Class: TModrmModFilter'}
class function TModrmModFilter.GetCapacity: Cardinal;
begin
  Result := 3;
end;

class function TModrmModFilter.GetDescription: String;
begin
  Result := 'ModrmMod';
end;

class function TModrmModFilter.GetInsertPosition(const Definition: TInstructionDefinition): Integer;
begin
  Result := Integer(Definition.OpcodeExtensions.ModrmMod);
end;

class function TModrmModFilter.GetItemDescription(Index: Integer): String;
begin
  Assert((Index >= 0) and (Index < Integer(GetCapacity)));
  Result := GetEnumName(TypeInfo(TExtModrmMod), Index);
end;

class function TModrmModFilter.GetNeutralElementType: TNeutralElementType;
begin
  Result := netPlaceholder;
end;
{$ENDREGION}

{$REGION 'Class: TModrmRegFilter'}
class function TModrmRegFilter.GetCapacity: Cardinal;
begin
  Result := 9;
end;

class function TModrmRegFilter.GetDescription: String;
begin
  Result := 'ModrmReg';
end;

class function TModrmRegFilter.GetInsertPosition(const Definition: TInstructionDefinition): Integer;
begin
  Result := Integer(Definition.OpcodeExtensions.ModrmReg);
end;

class function TModrmRegFilter.GetItemDescription(Index: Integer): String;
begin
  Assert((Index >= 0) and (Index < Integer(GetCapacity)));
  Result := GetEnumName(TypeInfo(TExtModrmReg), Index);
end;

class function TModrmRegFilter.GetNeutralElementType: TNeutralElementType;
begin
  Result := netPlaceholder;
end;
{$ENDREGION}

{$REGION 'Class: TModrmRmFilter'}
class function TModrmRmFilter.GetCapacity: Cardinal;
begin
  Result := 9;
end;

class function TModrmRmFilter.GetDescription: String;
begin
  Result := 'ModrmRm';
end;

class function TModrmRmFilter.GetInsertPosition(const Definition: TInstructionDefinition): Integer;
begin
  Result := Integer(Definition.OpcodeExtensions.ModrmRm);
end;

class function TModrmRmFilter.GetItemDescription(Index: Integer): String;
begin
  Assert((Index >= 0) and (Index < Integer(GetCapacity)));
  Result := GetEnumName(TypeInfo(TExtModrmRm), Index);
end;

class function TModrmRmFilter.GetNeutralElementType: TNeutralElementType;
begin
  Result := netPlaceholder;
end;
{$ENDREGION}

{$REGION 'Class: TOperandSizeFilter'}
class function TOperandSizeFilter.GetCapacity: Cardinal;
begin
  Result := 3;
end;

class function TOperandSizeFilter.GetDescription: String;
begin
  Result := 'OperandSize';
end;

class function TOperandSizeFilter.GetInsertPosition(
  const Definition: TInstructionDefinition): Integer;
begin
  Result := Integer(Definition.OpcodeExtensions.OperandSize);
end;

class function TOperandSizeFilter.GetItemDescription(Index: Integer): String;
begin
  Assert((Index >= 0) and (Index < Integer(GetCapacity)));
  Result := GetEnumName(TypeInfo(TExtOperandSize), Index);
end;

class function TOperandSizeFilter.GetNeutralElementType: TNeutralElementType;
begin
  Result := netPlaceholder;
end;
{$ENDREGION}

{$REGION 'Class: TAddressSizeFilter'}
class function TAddressSizeFilter.GetCapacity: Cardinal;
begin
  Result := 4;
end;

class function TAddressSizeFilter.GetDescription: String;
begin
  Result := 'AddressSize';
end;

class function TAddressSizeFilter.GetInsertPosition(
  const Definition: TInstructionDefinition): Integer;
begin
  Result := Integer(Definition.OpcodeExtensions.AddressSize);
end;

class function TAddressSizeFilter.GetItemDescription(Index: Integer): String;
begin
  Assert((Index >= 0) and (Index < Integer(GetCapacity)));
  Result := GetEnumName(TypeInfo(TExtAddressSize), Index);
end;

class function TAddressSizeFilter.GetNeutralElementType: TNeutralElementType;
begin
  Result := netPlaceholder;
end;
{$ENDREGION}

{$REGION 'Class: TRexWFilter'}
class function TRexWFilter.GetCapacity: Cardinal;
begin
  Result := 2;
end;

class function TRexWFilter.GetDescription: String;
begin
  Result := 'REXW';
end;

class function TRexWFilter.GetInsertPosition(const Definition: TInstructionDefinition): Integer;
begin
  if (bfRexW in Definition.OpcodeExtensions.BitFilters) then
  begin
    Result := 1;
  end else
  begin
    Result := 0;
  end;
end;

class function TRexWFilter.GetItemDescription(Index: Integer): String;
begin
  Result := 'REX.W ' + IntToStr(Index);
end;

class function TRexWFilter.GetNeutralElementType: TNeutralElementType;
begin
  Result := netValue;
end;
{$ENDREGION}

{$REGION 'Class: TVexLFilter'}
class function TVexLFilter.GetCapacity: Cardinal;
begin
  Result := 2;
end;

class function TVexLFilter.GetDescription: String;
begin
  Result := 'VEXL';
end;

class function TVexLFilter.GetInsertPosition(const Definition: TInstructionDefinition): Integer;
begin
  if (bfVexL in Definition.OpcodeExtensions.BitFilters) then
  begin
    Result := 1;
  end else
  begin
    Result := 0;
  end;
end;

class function TVexLFilter.GetItemDescription(Index: Integer): String;
begin
  Result := 'VEX.L ' + IntToStr(Index);
end;

class function TVexLFilter.GetNeutralElementType: TNeutralElementType;
begin
  Result := netValue;
end;
{$ENDREGION}

{$REGION 'Class: TEvexL2Filter'}
class function TEvexL2Filter.GetCapacity: Cardinal;
begin
  Result := 2;
end;

class function TEvexL2Filter.GetDescription: String;
begin
  Result := 'EVEXL2';
end;

class function TEvexL2Filter.GetInsertPosition(const Definition: TInstructionDefinition): Integer;
begin
  if (bfEvexL2 in Definition.OpcodeExtensions.BitFilters) then
  begin
    Result := 1;
  end else
  begin
    Result := 0;
  end;
end;

class function TEvexL2Filter.GetItemDescription(Index: Integer): String;
begin
  Result := 'EVEX.L'' ' + IntToStr(Index);
end;

class function TEvexL2Filter.GetNeutralElementType: TNeutralElementType;
begin
  Result := netValue;
end;
{$ENDREGION}

{$REGION 'Class: TEvexBFilter'}
class function TEvexBFilter.GetCapacity: Cardinal;
begin
  Result := 2;
end;

class function TEvexBFilter.GetDescription: String;
begin
  Result := 'EVEXB';
end;

class function TEvexBFilter.GetInsertPosition(const Definition: TInstructionDefinition): Integer;
begin
  if (bfEvexB in Definition.OpcodeExtensions.BitFilters) then
  begin
    Result := 1;
  end else
  begin
    Result := 0;
  end;
end;

class function TEvexBFilter.GetItemDescription(Index: Integer): String;
begin
  Result := 'EVEX.B ' + IntToStr(Index);
end;

class function TEvexBFilter.GetNeutralElementType: TNeutralElementType;
begin
  Result := netValue;
end;
{$ENDREGION}

end.
