/// minimum standand-alone cross-platform JSON process using variants
// - this unit is a part of the freeware Synopse mORMot framework,
// licensed under a MPL/GPL/LGPL tri-license; version 1.18
unit SynCrossPlatformJSON;

{
    This file is part of Synopse mORMot framework.

    Synopse mORMot framework. Copyright (C) 2016 Arnaud Bouchez
      Synopse Informatique - http://synopse.info

  *** BEGIN LICENSE BLOCK *****
  Version: MPL 1.1/GPL 2.0/LGPL 2.1

  The contents of this file are subject to the Mozilla Public License Version
  1.1 (the "License"); you may not use this file except in compliance with
  the License. You may obtain a copy of the License at
  http://www.mozilla.org/MPL

  Software distributed under the License is distributed on an "AS IS" basis,
  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
  for the specific language governing rights and limitations under the License.

  The Original Code is Synopse mORMot framework.

  The Initial Developer of the Original Code is Arnaud Bouchez.

  Portions created by the Initial Developer are Copyright (C) 2016
  the Initial Developer. All Rights Reserved.

  Contributor(s):
  - Witya
  
  Alternatively, the contents of this file may be used under the terms of
  either the GNU General Public License Version 2 or later (the "GPL"), or
  the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
  in which case the provisions of the GPL or the LGPL are applicable instead
  of those above. If you wish to allow use of your version of this file only
  under the terms of either the GPL or the LGPL, and not to allow others to
  use your version of this file under the terms of the MPL, indicate your
  decision by deleting the provisions above and replace them with the notice
  and other provisions required by the GPL or the LGPL. If you do not delete
  the provisions above, a recipient may use your version of this file under
  the terms of any one of the MPL, the GPL or the LGPL.

  ***** END LICENSE BLOCK *****

  
  Version 1.18
  - first public release, corresponding to mORMot Framework 1.18
  - would compile with Delphi for any platform (including NextGen for mobiles),
    with FPC 2.7 or Kylix, and with SmartMobileStudio 2+
  - FPC prior to 2.7.1 has some issues with working with variants: UTF-8
    encoding is sometimes lost, and TInvokeableVariantType.SetProperty is broken

}

{$i SynCrossPlatform.inc} // define e.g. HASINLINE

interface

uses
  SysUtils,
  Classes,
{$ifdef NEXTGEN}
  System.Generics.Collections,
{$else}
  Contnrs,
{$endif}
  Variants,
  TypInfo;

type
  TStringDynArray = array of string;
  TVariantDynArray = array of variant;
  TIntegerDynArray = array of integer;

  /// this type is used to store BLOB content
  TByteDynArray = array of byte;
  PByteDynArray = ^TByteDynArray;

  {$ifndef UNICODE}
  {$ifdef FPC}
  NativeInt = PtrInt;
  NativeUInt = PtrUInt;
  {$else}
  NativeInt = integer;
  NativeUInt = cardinal;
  {$endif}
  RawByteString = AnsiString;
  {$endif}

  // this type will store UTF-8 encoded buffer (also on NextGen platform)
  {$ifdef NEXTGEN}
  TUTF8Buffer = TBytes;
  // TObjecTList is not defined in Mobile platforms
  TObjectList = TObjectList<TObject>;
  {$else}
  TUTF8Buffer = UTF8String;
  {$endif}

  /// exception used during standand-alone cross-platform JSON process
  EJSONException = class(Exception);

  /// which kind of document the TJSONVariantData contains
  TJSONVariantKind = (jvUndefined, jvObject, jvArray);

  PJSONVariantData = ^TJSONVariantData;

  {$A-}
  /// stores any JSON object or array as variant
  // - this structure is not very optimized for speed or memory use, but is
  // simple and strong enough for our client-side purpose
  // - it is in fact already faster (and using less memory) than DBXJSON and
  // SuperObject / XSuperObject libraries - of course, mORMot's TDocVariant
  // is faster, as dwsJSON is in some cases, but those are not cross-platform
  {$ifdef UNICODE}
  TJSONVariantData = record
  private
  {$else}
  TJSONVariantData = object
  protected
  {$endif}
    VType: TVarType;
    _Align: byte;
    VKind: TJSONVariantKind;
    VCount: integer;
    function GetKind: TJSONVariantKind;
    function GetCount: integer;
    function GetVarData(const aName: string; var Dest: TVarData): boolean;
    function GetValue(const aName: string): variant;
    function GetValueCopy(const aName: string): variant;
    procedure SetValue(const aName: string; const aValue: variant);
    function GetItem(aIndex: integer): variant;
    procedure SetItem(aIndex: integer; const aItem: variant);
  public
    /// names of this jvObject
    Names: TStringDynArray;
    /// values of this jvObject or jvArray
    Values: TVariantDynArray;
    /// initialize the low-level memory structure
    procedure Init; overload;
    /// initialize the low-level memory structure with a given JSON content
    procedure Init(const JSON: string); overload;
    /// initialize the low-level memory structure with a given array of variant
    procedure InitFrom(const aValues: TVariantDynArray); overload;
    /// access to a nested TJSONVariantData item
    // - returns nil if aName was not found, or not a true TJSONVariantData item
    function Data(const aName: string): PJSONVariantData;
      {$ifdef HASINLINE}inline;{$endif}
    /// access to a nested TJSONVariantData item, creating it if necessary
    // - aPath can be specified with any depth, e.g. 'level1.level2.level3' 
    // - if the item does not exist or is not a true TJSONVariantData, a new
    // one will be created, and returned as pointer
    function EnsureData(const aPath: string): PJSONVariantData;
    /// add a void TJSONVariantData to the jvArray and return a pointer to it
    function AddItem: PJSONVariantData;
    /// add a value to the jvArray
    // - raise a ESJONException if the instance is a jvObject
    procedure AddValue(const aValue: variant);
    /// add a name/value pair to the jvObject
    // - raise a ESJONException if the instance is a jvArray
    procedure AddNameValue(const aName: string; const aValue: variant);
    /// search for a name in this jvObject
    function NameIndex(const aName: string): integer;
    /// set a value of this jvObject to a given path
    // - aPath can be specified with any depth, e.g. 'level1.level2.level3' 
    procedure SetPath(const aPath: string; const aValue: variant); 
    /// fill this document from a JSON array or object
    function FromJSON(const JSON: string): boolean;
    /// convert this document into JSON array or object
    function ToJSON: string;
    /// fill the published properties of supplied class from this JSON object
    function ToObject(Instance: TObject): boolean;
    /// create an instance, and fill its published properties from this JSON object
    // - it should contain some "ClassName" properties, i.e. JSON should have
    // been created by ObjectToJSON(Instance,true) and the class should have
    // been registered with RegisterClassForJSON()
    function ToNewObject: TObject;
    /// kind of document this TJSONVariantData contains
    // - returns jvUndefined if this instance is not a TJSONVariant custom variant
    property Kind: TJSONVariantKind read GetKind;
    /// number of items in this jvObject or jvArray
    // - returns 0 if this instance is not a TJSONVariant custom variant
    property Count: integer read GetCount;
    /// access by name to a value of this jvObject
    // - value is returned as (varVariant or varByRef) for best speed
    // - will return UnAssigned if aName is not correct or this is not a jvObject
    property Value[const aName: string]: variant read GetValue write SetValue; default;
    /// access by name to a value of this jvObject
    // - value is returned as a true copy (not varByRef) so this property is
    // slower but safer than Value[], if the owning TJsonVariantData disappears
    // - will return UnAssigned if aName is not correct or this is not a jvObject
    property ValueCopy[const aName: string]: variant read GetValueCopy;
    /// access by index to a value of this jvArray
    // - will return UnAssigned if aIndex is not correct or this is not a jvArray
    property Item[aIndex: integer]: variant read GetItem write SetItem;
  end;
  {$A+}

  /// low-level class used to register TJSONVariantData as custom type
  // - allows late binding to values, e.g.
  // ! jsonvar.avalue := jsonvar.avalue+1;
  // - due to an issue with FPC implementation, you can only read properties,
  // not set them, so you should write:
  // ! TJSONVariantData(jsonvar)['avalue'] := jsonvar.avalue+1;
  TJSONVariant = class(TInvokeableVariantType)
  protected
    {$ifndef FPC}
    {$ifndef ISDELPHI6}
    function FixupIdent(const AText: string): string; override;
    {$endif}
    {$endif}
  public
    procedure Copy(var Dest: TVarData; const Source: TVarData;
      const Indirect: Boolean); override;
    procedure Clear(var V: TVarData); override;
    function GetProperty(var Dest: TVarData; const V: TVarData;
      const Name: string): Boolean; override;
    {$ifdef FPC_VARIANTSETVAR} // see http://mantis.freepascal.org/view.php?id=26773
    function SetProperty(var V: TVarData; const Name: string;
      const Value: TVarData): Boolean; override;
    {$else}
    function SetProperty(const V: TVarData; const Name: string;
      const Value: TVarData): Boolean; override;
    {$endif}
    procedure Cast(var Dest: TVarData; const Source: TVarData); override;
    procedure CastTo(var Dest: TVarData; const Source: TVarData;
      const AVarType: TVarType); override;
  end;

  /// handle a JSON result table, as returned by mORMot's server
  // - handle both expanded and non expanded layout
  // - will be used e.g. on client side for variant-based ORM data parsing
  TJSONTable = class
  protected
    fJSON: string;
    fFieldNames: TStringDynArray;
    fJSONExpanded: boolean;
    fJSONIndexFirstValue: integer;
    fJSONCurrentIndex: integer;
    fRowValues: TVariantDynArray;
    function Get(const FieldName: string): variant;
  public
    /// parse the supplied JSON content
    constructor Create(const aJSON: string);
    /// case-insensitive search for a field name
    function FieldIndex(const FieldName: string): integer;
    /// to be called in a loop to iterate through all data rows
    // - if returned true, Value[] contains the fields of this row
    function Step(SeekFirst: boolean=false): boolean; 
    /// to be called in a loop to iterate through all data rows
    // - if returned true, RowValues contains this row as TJSONVariant
    function StepValue(var RowValues: variant; SeekFirst: boolean=false): boolean;
    /// after Step() returned true, can be used to retrieve a field value by name
    property Value[const FieldName: string]: variant read Get; default;
    /// after Step() returned true, can be used to retrieve a field value by index
    property RowValues: TVariantDynArray read fRowValues;
    /// the recognized field names
    property FieldNames: TStringDynArray read fFieldNames;
    /// the associated JSON content
    property JSON: string read fJSON;
  end;

  /// an abstract type used for RTTI type information  
  TRTTITypeInfo = PPropInfo;

  /// an abstract type used for RTTI property information
  TRTTIPropInfo = PPropInfo;

  TRTTIPropInfoDynArray = array of TRTTIPropInfo;

  /// handle a JSON result table, as returned by mORMot's server
  // - handle both expanded and non expanded layout
  // - this class is able to use RTTI to fill all published properties of
  // a TObject
  TJSONTableObject = class(TJSONTable)
  protected
    fTypeInfo: pointer;
    fPropInfo: array of TRTTIPropInfo;
    procedure FillPropInfo(aTypeInfo: TRTTITypeInfo); virtual;
    procedure FillInstance(Instance: TObject); virtual;
    function GetPropInfo(aTypeInfo: TRTTITypeInfo; const PropName: string): TRTTIPropInfo; virtual;
  public
    /// to be called in a loop to iterate through all data rows
    // - if returned true, Object published properties will contain this row
    function StepObject(Instance: TObject; SeekFirst: boolean=false): boolean; virtual;
  end;

  /// used e.g. by TSynTest for each test case
  TPublishedMethod = record
    Name: string;
    Method: TMethod;
  end;
  /// as filled by GetPublishedMethods()
  TPublishedMethodDynArray = array of TPublishedMethod;


/// create a TJSONVariant instance from a given JSON content
// - typical usage may be:
//! var doc: variant;
//!     json: string;
//! begin
//!   doc := JSONVariant('{"test":1234,"name":"Joh\"n\r"}');
//!   assert(doc.test=1234); // access via late binding
//!   assert(doc.name='Joh"n'#13);
//!   assert(doc.name2=null); // unknown properties returns null
//!   json := doc; // to convert a TJSONVariant to JSON, just assign to a string
//!   assert(json='{"test":1234,"name":"Joh\"n\r"}');
//! end;
// - note that FPC does not allow to set values by late-binding
function JSONVariant(const JSON: string): variant; overload;

/// create a TJSONVariant TJSONVariant array from a supplied array of values
function JSONVariant(const values: TVariantDynArray): variant; overload;

/// create a TJSONVariant TJSONVariant array from a supplied array of values
function JSONVariantFromConst(const constValues: array of variant): variant; 

/// access to a TJSONVariant instance members
// - e.g. Kind, Count, Names[] or Values[]
// - will raise an exception if the supplied variant is not a TJSONVariant
// - this function is safer than TJSONVariant(JSONVariant)
function JSONVariantData(const JSONVariant: variant): PJSONVariantData;

/// access to a TJSONVariant instance members
// - e.g. Kind, Count, Names[] or Values[]
// - will return a read-only fake TJSONVariant with Kind=jvUndefined if the
// supplied variant is not a TJSONVariant
// - if ExpectedKind is jvArray of jvObject, it would return a fake TJSONVariant
// with Kind=jvUndefined if the JSONVariant kind does not match - so you can write:
// !var _a: integer;
// !    _arr: PJSONVariantData;
// !...
// !   _arr := JSONVariantDataSafe(_variant,jvArray);
// !   SetLength(result,_arr.Count);
// !   for _a := 0 to _arr.Count-1 do
// !     result[_a] := _arr.Values[_a];
// in the above code, _arr.Count will be 0 if _variant.Kind<>jvArray
// - this function is safer than TJSONVariant(JSONVariant)
function JSONVariantDataSafe(const JSONVariant: variant;
  ExpectedKind: TJSONVariantKind=jvUndefined): PJSONVariantData;

var
  /// the custom variant type definition registered for TJSONVariant
  JSONVariantType: TInvokeableVariantType;


/// compute the quoted JSON string corresponding to the supplied text
function StringToJSON(const Text: string): string;

/// compute the JSON representation of a floating-point value
procedure DoubleToJSON(Value: double; var result: string);

/// compute the ISO-8601 JSON text representation of a date/time value
// - e.g. "YYYY-MM-DD" "Thh:mm:ss" or "YYYY-MM-DDThh:mm:ss"
// - if Date is 0, will return ""
function DateTimeToJSON(Value: TDateTime): string;

/// compute the JSON representation of a variant value
// - will work for simple types, or TJSONVariant object or array
function ValueToJSON(const Value: variant): string;

/// compute a variant from its JSON representation
// - will work for simple types, or TJSONVariant object or array
function JSONToValue(const JSON: string): variant;

/// compute the ISO-8601 JSON text representation of the current date/time value
// - e.g. "2015-06-27T20:59:29"
function NowToIso8601: string;

/// compute the unquoted ISO-8601 text representation of a date/time value
// - e.g. 'YYYY-MM-DD' 'Thh:mm:ss' or 'YYYY-MM-DDThh:mm:ss'
// - if Date is 0, will return ''
function DateTimeToIso8601(Value: TDateTime): string;

/// convert unquoted ISO-8601 text representation into a date/time value
// - e.g. 'YYYY-MM-DD' 'Thh:mm:ss' or 'YYYY-MM-DDThh:mm:ss'
function Iso8601ToDateTime(const Value: string): TDateTime;

/// compute the JSON representation of an object published properties
// - handle only simple types of properties, not nested class instances
// - any TList/TObjectList/TCollection will be serialized as JSON array
function ObjectToJSON(Instance: TObject; StoreClassName: boolean=false): string;

/// fill an object published properties from the supplied JSON object
// - handle only simple types of properties, not nested class instances
function JSONToObject(Instance: TObject; const JSON: string): boolean;

/// create a new object and fil its published properties from the supplied
// JSON object, which should include "ClassName":"..." properties
// - JSON should have been created with ObjectToJSON(Instance,true) and
// the class should have been registered with RegisterClassForJSON()
function JSONToNewObject(const JSON: string): pointer;

/// register the class types to be created from its name
// - used e.g. by JSONToNewObject() or TJSONVariantData.ToNewObject
procedure RegisterClassForJSON(const Classes: array of TClass);

/// create a class instance from its name
// - the class should have been registered previously via RegisterClassForJSON()
// - if the supplied class name is not found, will return nil
function CreateClassForJSON(const ClassName: string): TObject;

/// create a list of object published properties from the supplied JSON object
// - handle only simple types of properties, not nested class instances
function JSONToObjectList(ItemClass: TClass; const JSON: string): TObjectList;

/// return a string corresponding to the type name, as stored in the RTTI
// - e.g. 'TDateTime', 'TByteDynArray', 'TModTime', 'TCreateTime'
function RTTIPropInfoTypeName(PropInfo: TRTTIPropInfo): string;

/// retrieve the published properties type information about a given class
procedure GetPropsInfo(TypeInfo: TRTTITypeInfo; var PropNames: TStringDynArray;
  var PropRTTI: TRTTIPropInfoDynArray);

/// retrieve the value of a published property as variant
function GetInstanceProp(Instance: TObject; PropInfo: TRTTIPropInfo): variant;

/// set the value of a published property from a variant
procedure SetInstanceProp(Instance: TObject; PropInfo: TRTTIPropInfo;
  const Value: variant);

/// retrieve all the published methods of a given class, using RTTI
procedure GetPublishedMethods(Instance: TObject;
  out Methods: TPublishedMethodDynArray);

/// convert an "array of const" parameter value into its string representation
function VarRecToValue(const V: TVarRec; out wasString: boolean): string;

/// convert the supplied text as "text", as expected by SQL standard
procedure DoubleQuoteStr(var text: string);

/// decode a Base64-encoded string
// - default withBase64Magic=TRUE will expect the string to start with our
// JSON_BASE64_MAGIC marker
function Base64JSONStringToBytes(const JSONString: string;
  var Bytes: TByteDynArray; withBase64Magic: boolean=true): boolean;

/// Base-64 encode a BLOB into string
// - default withBase64Magic=TRUE will include our JSON_BASE64_MAGIC marker
function BytesToBase64JSONString(const Bytes: TByteDynArray;
  withBase64Magic: boolean=true): string;

const
  /// special code to mark Base64 binary content in JSON string
  // - Unicode special char U+FFF0 is UTF-8 encoded as EF BF B0 bytes
  // - prior to Delphi 2009, it won't work as expected since U+FFF0 won't be
  // able to be converted into U+FFF0
  {$ifdef UNICODE}
  JSON_BASE64_MAGIC: word = $fff0;
  {$else}
  JSON_BASE64_MAGIC: array[0..2] of byte = ($ef,$bf,$b0);
  {$endif}

  /// size, in platform chars, of our special code to mark Base64 binary
  // content in JSON string
  // - equals 1 since Delphi 2009 (UTF-16 encoded), or 3 for older versions
  // (UTF-8encoded) of the compiler compiler
  JSON_BASE64_MAGIC_LEN = sizeof(JSON_BASE64_MAGIC) div sizeof(char);

{$ifndef ISSMS}
/// read an UTF-8 (JSON) file into a native string
// - file should be existing, otherwise an exception is raised
function UTF8FileToString(const aFileName: TFileName): string;
{$endif}

/// this function is faster than str := str+chr !
procedure AppendChar(var str: string; chr: Char);
  {$ifdef HASINLINE}inline;{$endif}

/// check that two ASCII-7 latin text do match
function IdemPropName(const PropName1,PropName2: string): boolean; overload;
  {$ifdef HASINLINE}inline;{$endif}

/// check that two ASCII-7 latin text do match
// - first parameter is expected to be a shortstring low-level buffer - as such,
// this overloaded function would work with NEXTGEN encoded RTTI
function IdemPropName(PropName1: PByteArray; const PropName2: string): boolean; overload;
  {$ifdef HASINLINE}inline;{$endif}

/// convert ASCII-7 latin text, encoded as a shortstring buffer, into a string
// - as such, this function would work with NEXTGEN encoded RTTI
function ShortStringToString(Buffer: PByteArray): string;

/// check that two ASCII-7 latin text do match
function StartWithPropName(const PropName1,PropName2: string): boolean;


implementation

function IdemPropName(const PropName1,PropName2: string): boolean;
var L,i: integer;
begin
  result := false;
  L := length(PropName2);
  if length(PropName1)<>L then
    exit;
  for i := 1 to L do
    if (ord(PropName1[i]) xor ord(PropName2[i])) and
      {$ifdef UNICODE}$ffdf{$else}$df{$endif}<>0 then
      exit;
  result := true;
end;

function ShortStringToString(Buffer: PByteArray): string;
{$ifdef UNICODE}
var i: integer;
begin
  SetLength(result,Buffer^[0]);
  for i := 1 to Buffer^[0] do
    result[i] := chr(Buffer^[i]);
end;
{$else}
begin
  SetString(result,PAnsiChar(@Buffer^[1]),Buffer^[0]);
end;
{$endif}

function IdemPropName(PropName1: PByteArray; const PropName2: string): boolean;
var L,i: integer;
begin
  result := false;
  L := length(PropName2);
  if PropName1^[0]<>L then
    exit;
  for i := 1 to L do
    if (PropName1^[i] xor ord(PropName2[i])) and
      {$ifdef UNICODE}$ffdf{$else}$df{$endif}<>0 then
      exit;
  result := true;
end;

function StartWithPropName(const PropName1,PropName2: string): boolean;
var L,i: integer;
begin
  result := false;
  L := length(PropName2);
  if length(PropName1)<L then
    exit;
  for i := 1 to L do
    if (ord(PropName1[i]) xor ord(PropName2[i])) and
      {$ifdef UNICODE}$ffdf{$else}$df{$endif}<>0 then
      exit;
  result := true;
end;

{$ifndef ISSMS} // there is no file within HTML5 DOM

{$ifdef FPC}
// assume string is UTF-8 encoded (as with Lazarus/LCL)
// note that when working with variants, FPC 2.7.1 sometimes clear the code page
type UTF8ToString = RawByteString;
{$else}
{$ifndef UNICODE}
function UTF8ToString(const utf8: TUTF8Buffer): string;
begin
  result := UTF8ToAnsi(utf8);
end;
{$endif}
{$endif}

function UTF8FileToString(const aFileName: TFileName): string;
var F: TFileStream;
    len: integer;
    utf8: TUTF8Buffer;
begin
  F := TFileStream.Create(aFileName,fmOpenRead);
  try
    len := F.Size;
    SetLength(utf8,len);
    {$ifdef NEXTGEN}
    F.Read(utf8[0],len);
    result := TEncoding.UTF8.GetString(utf8);
    {$else}
    F.Read(utf8[1],len);
    result := UTF8ToString(utf8);
    {$endif}
  finally
    F.Free;
  end;
end;
{$endif}

function JSONVariant(const JSON: string): variant;
begin
  VarClear(result);
  TJSONVariantData(result).FromJSON(JSON);
end;

function JSONVariant(const values: TVariantDynArray): variant;
begin
  VarClear(result);
  TJSONVariantData(result).Init;
  TJSONVariantData(result).VKind := jvArray;
  TJSONVariantData(result).VCount := length(values);
  TJSONVariantData(result).Values := values;
end;

function JSONVariantFromConst(const constValues: array of variant): variant; 
var i: integer;
begin
  VarClear(result);
  with TJSONVariantData(result) do begin
    Init;
    VKind := jvArray;
    VCount := length(values);
    SetLength(Values,VCount);
    for i := 0 to VCount-1 do
      Values[i] := constValues[i];
  end;
end;

function JSONVariantData(const JSONVariant: variant): PJSONVariantData;
begin
  with TVarData(JSONVariant) do
    if VType=JSONVariantType.VarType then
      result := @JSONVariant else
    if VType=varByRef or varVariant then
      result := JSONVariantData(PVariant(VPointer)^) else
    raise EJSONException.CreateFmt('JSONVariantData.Data(%d<>JSONVariant)',[VType]);
end;

const // will be in code section of the exe, so will be read-only by design
  JSONVariantDataFake: TJSONVariantData = ();

function JSONVariantDataSafe(const JSONVariant: variant;
  ExpectedKind: TJSONVariantKind=jvUndefined): PJSONVariantData;
begin
  with TVarData(JSONVariant) do
    if VType=JSONVariantType.VarType then
      if (ExpectedKind=jvUndefined) or
         (TJSONVariantData(JSONVariant).VKind=ExpectedKind) then
        result := @JSONVariant else
        result := @JSONVariantDataFake else
    if VType=varByRef or varVariant then
      result := JSONVariantDataSafe(PVariant(VPointer)^) else
      result := @JSONVariantDataFake;
end;

procedure AppendChar(var str: string; chr: Char);
{$ifdef ISSMS} // JavaScript immutable strings
begin
  str := str+chr
end;
{$else}
var len: Integer;
begin
  len := length(str);
  SetLength(str,len+1);
  PChar(pointer(str))[len] := chr; // SetLength() made str unique
end; 
{$endif}

function StringToJSON(const Text: string): string;
var len,j: integer;
procedure DoEscape;
var i: Integer;
begin
  result := '"'+copy(Text,1,j-1); // here FPC 2.7.1 erases UTF-8 encoding
  for i := j to len do begin
    case Text[i] of
    #8:  result := result+'\b';
    #9:  result := result+'\t';
    #10: result := result+'\n';
    #12: result := result+'\f';
    #13: result := result+'\r';
    '\': result := result+'\\';
    '"': result := result+'\"';
    else
    if Text[i]<' ' then
      result := result+'\u00'+IntToHex(ord(Text[i]),2) else
      AppendChar(result,Text[i]); // will be UTF-8 encoded later
    end;
  end;
  AppendChar(result,'"');
end;
begin
  len := length(Text);
  for j := 1 to len do
    case Text[j] of
    #0..#31,'\','"': begin
      DoEscape;
      exit;
    end;
    end;
  // if we reached here, no character needs to be escaped in this string
  result := '"'+Text+'"'; // here FPC 2.7.1 erases UTF-8 encoding :(
end;

{$ifdef KYLIX}
  {$define NOFORMATSETTINGS}
{$endif}
{$ifdef ISDELPHI6}
  {$define NOFORMATSETTINGS}
{$endif}

{$ifdef NOFORMATSETTINGS}
procedure DoubleToJSON(Value: double; var result: string);
var decsep: Char;
begin // warning: this is NOT thread-safe if you mix settings
  decsep := DecimalSeparator;
  result := FloatToStr(Value);
  DecimalSeparator := decsep;
end;
{$else}
var
  SettingsUS: TFormatSettings
  {$ifdef FPC} = (
      CurrencyFormat: 1;
      NegCurrFormat: 5;
      ThousandSeparator: ',';
      DecimalSeparator: '.';
      CurrencyDecimals: 2;
      DateSeparator: '-';
      TimeSeparator: ':';
      ListSeparator: ',';
      CurrencyString: '$';
      ShortDateFormat: 'd/m/y';
      LongDateFormat: 'dd" "mmmm" "yyyy';
      TimeAMString: 'AM';
      TimePMString: 'PM';
      ShortTimeFormat: 'hh:nn';
      LongTimeFormat: 'hh:nn:ss';
      ShortMonthNames: ('Jan','Feb','Mar','Apr','May','Jun',
                        'Jul','Aug','Sep','Oct','Nov','Dec');
      LongMonthNames: ('January','February','March','April','May','June',
                       'July','August','September','October','November','December');
      ShortDayNames: ('Sun','Mon','Tue','Wed','Thu','Fri','Sat');
      LongDayNames:  ('Sunday','Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
      TwoDigitYearCenturyWindow: 50;)
  {$endif};
procedure DoubleToJSON(Value: double; var result: string);
begin
  result := FloatToStr(Value,SettingsUS);
end;
{$endif}

function DateTimeToJSON(Value: TDateTime): string;
begin // e.g. "YYYY-MM-DD" "Thh:mm:ss" or "YYYY-MM-DDThh:mm:ss"
  result := '"'+DateTimeToIso8601(Value)+'"';
end;

function NowToIso8601: string;
begin
  result := DateTimeToIso8601(Now);
end;

function DateTimeToIso8601(Value: TDateTime): string;
begin // e.g. YYYY-MM-DD Thh:mm:ss or YYYY-MM-DDThh:mm:ss
  if Value=0 then
    result := '' else
  if frac(Value)=0 then
    result := FormatDateTime('yyyy"-"mm"-"dd',Value) else
  if trunc(Value)=0 then
    result := FormatDateTime('"T"hh":"nn":"ss',Value) else
    result := FormatDateTime('yyyy"-"mm"-"dd"T"hh":"nn":"ss',Value);
end;

function Iso8601ToDateTime(const Value: string): TDateTime;
var Y,M,D, HH,MI,SS: cardinal;
begin //  YYYY-MM-DD   Thh:mm:ss  or  YYYY-MM-DDThh:mm:ss
      //  1234567890   123456789      1234567890123456789
  result := 0;
  case Length(Value) of
  9: if (Value[1]='T') and (Value[4]=':') and (Value[7]=':') then begin
    HH := ord(Value[2])*10+ord(Value[3])-(48+480);
    MI := ord(Value[5])*10+ord(Value[6])-(48+480);
    SS := ord(Value[8])*10+ord(Value[9])-(48+480);
    if (HH<24) and (MI<60) and (SS<60) then
      result := EncodeTime(HH,MI,SS,0);
  end;
  10: if (Value[5]=Value[8]) and (ord(Value[8]) in [ord('-'),ord('/')]) then begin
    Y := ord(Value[1])*1000+ord(Value[2])*100+
         ord(Value[3])*10+ord(Value[4])-(48+480+4800+48000);
    M := ord(Value[6])*10+ord(Value[7])-(48+480);
    D := ord(Value[9])*10+ord(Value[10])-(48+480);
    if (Y<=9999) and ((M-1)<12) and ((D-1)<31) then
      result := EncodeDate(Y,M,D);
  end;
  19: if (Value[5]=Value[8]) and (ord(Value[8]) in [ord('-'),ord('/')]) and
         (ord(Value[11]) in [ord(' '),ord('T')]) and (Value[14]=':') and (Value[17]=':') then begin
    Y := ord(Value[1])*1000+ord(Value[2])*100+
         ord(Value[3])*10+ord(Value[4])-(48+480+4800+48000);
    M := ord(Value[6])*10+ord(Value[7])-(48+480);
    D := ord(Value[9])*10+ord(Value[10])-(48+480);
    HH := ord(Value[12])*10+ord(Value[13])-(48+480);
    MI := ord(Value[15])*10+ord(Value[16])-(48+480);
    SS := ord(Value[18])*10+ord(Value[19])-(48+480);
    if (Y<=9999) and ((M-1)<12) and ((D-1)<31) and
       (HH<24) and (MI<60) and (SS<60) then
      result := EncodeDate(Y,M,D)+EncodeTime(HH,MI,SS,0);
  end;
  end;
end;

function ValueToJSON(const Value: variant): string;
var I64: Int64;
begin
  if TVarData(Value).VType=JSONVariantType.VarType then
    result := TJSONVariantData(Value).ToJSON else
  if (TVarData(Value).VType=varByRef or varVariant) then
    result := ValueToJSON(PVariant(TVarData(Value).VPointer)^) else
  if TVarData(Value).VType<=varNull then
    result := 'null' else
  if VarIsOrdinal(Value) then begin
    I64 := Value;
    result := IntToStr(I64);
  end else
  if TVarData(Value).VType=varDate then
    result := DateTimeToJSON(TVarData(Value).VDouble) else
  if VarIsFloat(Value) then
    DoubleToJSON(Value,result) else
  if VarIsStr(Value) then
    result := StringToJSON(Value) else
    result := Value;
end;

function VarRecToValue(const V: TVarRec; out wasString: boolean): string;
// http://smartmobilestudio.com/forums/topic/is-array-of-const-supported-in-sms
begin
  wasString := not (V.VType in
    [vtBoolean,vtInteger,vtInt64,vtCurrency,vtExtended,vtVariant]);
  with V do
  case VType of
  {$ifndef NEXTGEN}
  vtString:     result := string(VString^);
  vtAnsiString: result := string(AnsiString(VAnsiString));
  vtChar:       result := string(VChar);
  vtPChar:      result := string(VPChar);
  vtWideString: result := string(WideString(VWideString));
  {$endif}
  {$ifdef UNICODE}
  vtUnicodeString: result := string(VUnicodeString);
  {$endif}
  vtPWideChar:  result := string(VPWideChar);
  vtWideChar:   result := string(VWideChar);
  vtBoolean:    if VBoolean then result := '1' else result := '0';
  vtInteger:    result := IntToStr(VInteger);
  vtInt64:      result := IntToStr(VInt64^);
  vtCurrency:   DoubleToJSON(VCurrency^,result);
  vtExtended:   DoubleToJSON(VExtended^,result);
  vtObject:     result := ObjectToJSON(VObject);
  vtVariant: if TVarData(VVariant^).VType<=varNull then
    result := 'null' else begin
    wasString := VarIsStr(VVariant^);
    result := VVariant^;
  end;
  else result := '';
  end;
end;

procedure DoubleQuoteStr(var text: string);
var i,j: integer;
    tmp: string;
begin
  i := pos('"',text);
  if i=0 then begin
    text := '"'+text+'"';
    exit;
  end;
  tmp := '"'+copy(text,1,i)+'"';
  for j := i+1 to length(text) do
    if text[j]='"' then
      tmp := tmp+'""' else
      AppendChar(tmp,text[j]);
  text := tmp+'"';
end;


{ TJSONParser }

type
  /// the JSON node types, as recognized by TJSONParser
  TJSONParserKind = (
    kNone, kNull, kFalse, kTrue, kString, kInteger, kFloat, kObject, kArray);

  /// used to parse any JSON content
  TJSONParser = {$ifdef UNICODE}record{$else}object{$endif}
    JSON: string;
    Index: integer;
    JSONLength: integer;
    procedure Init(const aJSON: string; aIndex: integer);
    function GetNextChar: char;                {$ifdef HASINLINE}inline;{$endif}
    function GetNextNonWhiteChar: char;        {$ifdef HASINLINE}inline;{$endif}
    function CheckNextNonWhiteChar(aChar: char): boolean; {$ifdef HASINLINE}inline;{$endif}
    function GetNextString(out str: string): boolean; overload;
    function GetNextString: string; overload;  {$ifdef HASINLINE}inline;{$endif}
    function GetNextJSON(out Value: variant): TJSONParserKind;
    function CheckNextIdent(const ExpectedIdent: string): Boolean;
    function GetNextAlphaPropName(out fieldName: string): boolean;
    function ParseJSONObject(var Data: TJSONVariantData): boolean;
    function ParseJSONArray(var Data: TJSONVariantData): boolean;
    procedure GetNextStringUnEscape(var str: string);
  end;

procedure TJSONParser.Init(const aJSON: string; aIndex: integer);
begin
  JSON := aJSON;
  JSONLength := length(JSON);
  Index := aIndex;
end;

function TJSONParser.GetNextChar: char;
begin
  if Index<=JSONLength then begin
    result := JSON[Index];
    inc(Index);
  end else
    result := #0;
end;

function TJSONParser.GetNextNonWhiteChar: char;
begin
  if Index<=JSONLength then
    repeat
      if JSON[Index]>' ' then begin
        result := JSON[Index];
        inc(Index);
        exit;
      end;
      inc(Index);
    until Index>JSONLength;
  result := #0;
end;

function TJSONParser.CheckNextNonWhiteChar(aChar: char): boolean;
begin
  if Index<=JSONLength then
    repeat
      if JSON[Index]>' ' then begin
        result := JSON[Index]=aChar;
        if result then
          inc(Index);
        exit;
      end;
      inc(Index);
    until Index>JSONLength;
  result := false;
end;

procedure TJSONParser.GetNextStringUnEscape(var str: string);
var c: char;
    u: string;
    unicode,err: integer;
begin
  repeat
    c := GetNextChar;
    case c of
    #0: exit;
    '"': break;
    '\': begin
      c := GetNextChar;
      case c of
      #0: exit;
      'b': AppendChar(str,#08);
      't': AppendChar(str,#09);
      'n': AppendChar(str,#$0a);
      'f': AppendChar(str,#$0c);
      'r': AppendChar(str,#$0d);
      'u': begin
        u := Copy(JSON,Index,4);
        if length(u)<>4 then
          exit;
        inc(Index,4);
        val('$'+u,unicode,err);
        if err<>0 then
          exit;
        AppendChar(str,char(unicode));
      end;
      else AppendChar(str,c);
      end;
    end;
    else AppendChar(str,c);
    end;
  until false;
end;

function TJSONParser.GetNextString(out str: string): boolean;
var i: integer;
begin
  for i := Index to JSONLength do
    case JSON[i] of
    '"': begin // end of string without escape -> direct copy
      str := copy(JSON,Index,i-Index);
      Index := i+1;
      result := true;
      exit;
    end;
    '\': begin // need unescaping
      str := copy(JSON,Index,i-Index);
      Index := i;
      GetNextStringUnEscape(str);
      result := true;
      exit;
    end;
    end;
  result := false;
end;

function TJSONParser.GetNextString: string;
begin
  if not GetNextString(result) then
    result := '';
end;

function TJSONParser.GetNextAlphaPropName(out fieldName: string): boolean;
var i: integer;
begin
  result := False;
  if (Index>=JSONLength) or
     not (Ord(JSON[Index]) in [Ord('A')..Ord('Z'),Ord('a')..Ord('z'),Ord('_'),Ord('$')]) then
    exit; // first char must be alphabetical
  for i := Index+1 to JSONLength do
    case Ord(JSON[i]) of
    Ord('0')..Ord('9'),Ord('A')..Ord('Z'),Ord('a')..Ord('z'),Ord('_'):
      ; // allow MongoDB extended syntax, e.g. {age:{$gt:18}}
    Ord(':'),Ord('='): begin // allow both age:18 and age=18 pairs
      fieldName := Copy(JSON,Index,i-Index);
      Index := i+1;
      result := true;
      exit;
    end;
    else exit;
    end;
end;

function TJSONParser.GetNextJSON(out Value: variant): TJSONParserKind;
var str: string;
    i64: Int64;
    d: double;
    start,err: integer;
begin
  result := kNone;
  case GetNextNonWhiteChar of
  'n': if copy(JSON,Index,3)='ull' then begin
         inc(Index,3);
         result := kNull;
         Value := null;
       end;
  'f': if copy(JSON,Index,4)='alse' then begin
         inc(Index,4);
         result := kFalse;
         Value := false;
       end;
  't': if copy(JSON,Index,3)='rue' then begin
         inc(Index,3);
         result := kTrue;
         Value := true;
       end;
  '"': if GetNextString(str) then begin
         result := kString;
         Value := str;
       end;
  '{': if ParseJSONObject(TJSONVariantData(Value)) then
         result := kObject;
  '[': if ParseJSONArray(TJSONVariantData(Value)) then
         result := kArray;
  '-','0'..'9': begin
    start := Index-1;
    while true do
      case JSON[Index] of
      '-','+','0'..'9','.','E','e': inc(Index);
      else break;
      end;
    str := copy(JSON,start,Index-start);
    val(str,i64,err);
    if err=0 then begin
      Value := i64;
      result := kInteger;
    end else begin
      val(str,d,err);
      if err<>0 then
        exit;
      Value := d;
      result := kFloat;
    end;
  end;
  end;
end;

function TJSONParser.CheckNextIdent(const ExpectedIdent: string): Boolean;
begin
  result := (GetNextNonWhiteChar='"') and
            (CompareText(GetNextString,ExpectedIdent)=0) and
            (GetNextNonWhiteChar=':');
end;

function TJSONParser.ParseJSONArray(var Data: TJSONVariantData): boolean;
var item: variant;
begin
  result := false;
  Data.Init;
  if not CheckNextNonWhiteChar(']') then // '[]' -> void array
    repeat
      if GetNextJSON(item)=kNone then
        exit;
      Data.AddValue(item);
      case GetNextNonWhiteChar of
      ',': continue;
      ']': break;
      else exit;
      end;
    until false;
  SetLength(Data.Values,Data.VCount);
  Data.VKind := jvArray;
  result := true;
end;

function TJSONParser.ParseJSONObject(var Data: TJSONVariantData): boolean;
var key: string;
    val: variant;
begin
  result := false;
  Data.Init;
  if not CheckNextNonWhiteChar('}') then // '{}' -> void object
    repeat
      if CheckNextNonWhiteChar('"') then begin
        if (not GetNextString(key)) or (GetNextNonWhiteChar<>':') then
          exit;
      end else
        if not GetNextAlphaPropName(key) then
          exit;                             
      if GetNextJSON(val)=kNone then
        exit; // writeln(Copy(JSON,Index-10,30));
      Data.AddNameValue(key,val);
      case GetNextNonWhiteChar of
      ',': continue;
      '}': break;
      else exit;
      end;
    until false;
  SetLength(Data.Names,Data.VCount);
  SetLength(Data.Values,Data.VCount);
  Data.VKind := jvObject;
  result := true;
end;


function JSONToValue(const JSON: string): variant;
var Parser: TJSONParser;
begin
  Parser.Init(JSON,1);
  Parser.GetNextJSON(result);
end;


{ RTTI-oriented functions }

const
  BASE64: array[0..63] of char =
    'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/';
var
  BASE64DECODE: array of ShortInt;

function BytesToBase64JSONString(const Bytes: TByteDynArray;
  withBase64Magic: boolean): string;
var i,len,x,c,j: cardinal;
    P: PChar;
begin
  len := length(Bytes);
  if len=0 then begin
    result := '';
    exit;
  end;
  if withBase64Magic then
    x := JSON_BASE64_MAGIC_LEN else
    x := 0;
  SetLength(result,((len+2)div 3)*4+x);
  P := pointer(result);
  if withBase64Magic then
    move(JSON_BASE64_MAGIC,P^,sizeof(JSON_BASE64_MAGIC));
  j := 0;
  for i := 1 to len div 3 do begin
    c := Bytes[j] shl 16 or Bytes[j+1] shl 8 or Bytes[j+2];
    inc(j,3);
    P[x]   := BASE64[(c shr 18) and $3f];
    P[x+1] := BASE64[(c shr 12) and $3f];
    P[x+2] := BASE64[(c shr 6) and $3f];
    P[x+3] := BASE64[c and $3f];
    inc(x,4);
  end;
  case len mod 3 of
    1: begin
      c := Bytes[j] shl 4;
      P[x]   := BASE64[(c shr 6) and $3f];
      P[x+1] := BASE64[c and $3f];
      P[x+2] := '=';
      P[x+3] := '=';
      inc(x,4);
    end;
    2: begin
      c := Bytes[j] shl 10 or Bytes[j+1] shl 2;
      P[x]   := BASE64[(c shr 12) and $3f];
      P[x+1] := BASE64[(c shr 6) and $3f];
      P[x+2] := BASE64[c and $3f];
      P[x+3] := '=';
      inc(x,4);
    end;
  end;
  assert(integer(x)=Length(Result));
end;

function Base64One(c: Char): integer;
  {$ifdef HASINLINE}inline;{$endif}
begin
  result := ord(c);
  if result>127 then
    result := -1 else
    result := BASE64DECODE[result];
end;

function Base64JSONStringToBytes(const JSONString: string;
  var Bytes: TByteDynArray; withBase64Magic: boolean): boolean;
var i,bits,value,x,magiclen,len: cardinal;
begin
  result := JSONString='';
  if result then
    exit;
  if withBase64Magic then
    if comparemem(pointer(JSONString),@JSON_BASE64_MAGIC,sizeof(JSON_BASE64_MAGIC)) then
      magiclen := JSON_BASE64_MAGIC_LEN else
      {$ifndef UNICODE}
      if JSONString[1]='?' then // handle UTF-8 decoding error on ANSI Delphi
        magiclen := 1 else
      {$endif}
      exit else
    magiclen := 0; // withBase64Magic=false
  x := length(JSONString);
  len := x-magiclen;
  if len and 3<>0 then
    exit;
  if len=0 then
    Bytes := nil else begin
    if BASE64DECODE=nil then begin
      SetLength(BASE64DECODE,128);
      for i := 0 to 127 do
        BASE64DECODE[i] := -1;
      for i := 0 to high(BASE64) do
        BASE64DECODE[ord(BASE64[i])] := i;
    end;
    len := (len shr 2)*3;
    if Base64One(JSONString[x])<0 then begin
      dec(len);
      if Base64One(JSONString[x-1])<0 then
        dec(len);
    end;
    SetLength(Bytes,len);
    bits := 0;
    value := 0;
    len := 0;
    for i := magiclen+1 to Length(JSONString) do begin
      x := ord(JSONString[i]); // inlined Base64One(JSONString[i])
      if x>127 then
        break;
      x := cardinal(BASE64DECODE[x]);
      if integer(x)<0 then
        break;
      value := value*64+x;
      bits := bits+6;
      if bits>=8 then begin
        bits := bits-8;
        x := value shr bits;
        value := value and ((1 shl bits)-1);
        Bytes[len] := x;
        inc(len);
      end;
    end;
  end;
  result := len=cardinal(length(Bytes));
end;

function RTTIPropInfoTypeName(PropInfo: TRTTIPropInfo): string;
begin
  result := ShortStringToString(@PropInfo^.PropType^.Name);
end;

procedure GetPropsInfo(TypeInfo: TRTTITypeInfo; var PropNames: TStringDynArray;
  var PropRTTI: TRTTIPropInfoDynArray);
var i,n: integer;
    List: PPropList;
begin
  n := GetPropList(PTypeInfo(TypeInfo),List);
  SetLength(PropNames,n);
  SetLength(PropRTTI,n);
  for i := 0 to n-1 do begin
    PropRTTI[i] := List^[i];
    PropNames[i] := ShortStringToString(@PropRTTI[i]^.Name);
  end;
  freemem(List);
end;

function IsDateTime(PropInfo: TRTTIPropInfo): boolean;
  {$ifdef HASINLINE}inline;{$endif}
begin
  result := PropInfo^.PropType{$ifndef FPC}^{$endif}=TypeInfo(TDateTime);
end;

type
  // used to map a TPropInfo.GetProc/SetProc and retrieve its kind
  PropWrap = packed record
    FillBytes: array [0..SizeOf(Pointer)-2] of byte;
    /// = $ff for a field address, or =$fe for a virtual method
    Kind: byte;
  end;

function IsBlob(PropInfo: TRTTIPropInfo): boolean;
  {$ifdef HASINLINE}inline;{$endif}
begin // we only handle plain TByteDynArray properties without getter/setter
{$ifdef FPC}
  result := (PropInfo^.PropType=TypeInfo(TByteDynArray)) and
            (PropInfo^.PropProcs and 3=ptField);
{$else}
  result := (PropInfo^.PropType^=TypeInfo(TByteDynArray)) and
            (PropWrap(PropInfo^.GetProc).Kind=$FF);
{$endif}
end;

function GetTByteDynArrayProp(Instance: TObject; PropInfo: TRTTIPropInfo): PByteDynArray;
  {$ifdef HASINLINE}inline;{$endif}
begin
  result := Pointer(NativeUInt(Instance)+
    (NativeUInt(PropInfo^.GetProc){$ifndef FPC} and $00FFFFFF{$endif}));
end;

function GetInstanceProp(Instance: TObject; PropInfo: TRTTIPropInfo): variant;
var obj: TObject;
begin
  VarClear(result);
  if (PropInfo=nil) or (Instance=nil) then
    exit;
  case PropInfo^.PropType^.Kind of
  tkInt64{$ifdef FPC}, tkQWord{$endif}:
    result := GetInt64Prop(Instance,PropInfo);
  tkEnumeration, tkInteger, tkSet:
    result := GetOrdProp(Instance,PropInfo);
  {$ifdef NEXTGEN}
  tkUString:
    result := GetStrProp(Instance,PropInfo);
  {$else}
  {$ifdef FPC}tkAString,{$endif}tkLString:
    result := GetStrProp(Instance,PropInfo);
  tkWString:
    result := GetWideStrProp(Instance,PropInfo);
  {$ifdef UNICODE}
  tkUString:
    result := GetUnicodeStrProp(Instance,PropInfo);
  {$endif UNICODE}
  {$endif NEXTGEN}
  tkFloat:
    if IsDateTime(PropInfo) then
      result := DateTimeToIso8601(GetFloatProp(Instance,PropInfo)) else
      result := GetFloatProp(Instance,PropInfo);
  tkVariant:
    result := GetVariantProp(Instance,PropInfo);
  tkClass: begin
    obj := TObject(NativeInt(GetOrdProp(Instance,PropInfo)));
    if obj=nil then
      result := null else
      TJSONVariantData(result).Init(ObjectToJSON(obj));
  end;
  tkDynArray:
    if IsBlob(PropInfo) then
      result := BytesToBase64JSONString(GetTByteDynArrayProp(Instance,PropInfo)^);
  end;
end;

procedure SetInstanceProp(Instance: TObject; PropInfo: TRTTIPropInfo;
  const Value: variant);
var blob: PByteDynArray;
    obj: TObject;
begin
  if (PropInfo<>nil) and (Instance<>nil) then
  case PropInfo^.PropType^.Kind of
  tkInt64{$ifdef FPC}, tkQWord{$endif}:
    if TVarData(Value).VType=varInt64 then
      SetInt64Prop(Instance,PropInfo,TVarData(Value).VInt64) else
      SetOrdProp(Instance,PropInfo,Value);
  tkEnumeration, tkInteger, tkSet:
    SetOrdProp(Instance,PropInfo,Value);
  {$ifdef NEXTGEN}
  tkUString:
    if TVarData(Value).VType<=varNull then
      SetStrProp(Instance,PropInfo,'') else
      SetStrProp(Instance,PropInfo,Value);
  {$else}
  {$ifdef FPC}tkAString,{$endif} tkLString:
    if TVarData(Value).VType<=varNull then
      SetStrProp(Instance,PropInfo,'') else
      SetStrProp(Instance,PropInfo,Value);
  tkWString:
    if TVarData(Value).VType<=varNull then
      SetWideStrProp(Instance,PropInfo,'') else
      SetWideStrProp(Instance,PropInfo,Value);
  {$ifdef UNICODE}
  tkUString:
    if TVarData(Value).VType<=varNull then
      SetUnicodeStrProp(Instance,PropInfo,'') else
      SetUnicodeStrProp(Instance,PropInfo,Value);
  {$endif UNICODE}
  {$endif NEXTGEN}
  tkFloat:
    if IsDateTime(PropInfo) and VarIsStr(Value) then
      SetFloatProp(Instance,PropInfo,Iso8601ToDateTime(Value)) else
      SetFloatProp(Instance,PropInfo,Value);
  tkVariant:
    SetVariantProp(Instance,PropInfo,Value);
  tkDynArray:
    if IsBlob(PropInfo) then begin
      blob := GetTByteDynArrayProp(Instance,PropInfo);
      if (TVarData(Value).VType<=varNull) or
        not Base64JSONStringToBytes(Value,blob^) then
        Finalize(blob^);
    end;
  tkClass: begin
    obj := TObject(NativeInt(GetOrdProp(Instance,PropInfo)));
    if TVarData(Value).VType>varNull then
      if obj=nil then begin
        obj := JSONVariantData(Value)^.ToNewObject;
        if obj<>nil then
          SetOrdProp(Instance,PropInfo,NativeInt(obj));
      end else
        JSONVariantData(Value)^.ToObject(obj);
  end;
  end;
end;

function JSONToObjectList(ItemClass: TClass; const JSON: string): TObjectList;
var doc: TJSONVariantData;
    item: TObject;
    i: integer;
begin
  doc.Init(JSON);
  if (doc.VKind<>jvArray) or (ItemClass=nil) then
    result := nil else begin
    result := TObjectList.Create;
    for i := 0 to doc.Count-1 do begin
      item := ItemClass.Create;
      if not JSONVariantData(doc.Values[i])^.ToObject(item) then begin
        FreeAndNil(result);
        exit;
      end;
      result.Add(item);
    end;
  end;
end;

function JSONToObject(Instance: TObject; const JSON: string): boolean;
var doc: TJSONVariantData;
begin
  if Instance=nil then
    result := false else begin
    doc.Init(JSON);
    result := doc.ToObject(Instance);
  end;
end;

function JSONToNewObject(const JSON: string): pointer;
var doc: TJSONVariantData;
begin
  doc.Init(JSON);
  result := doc.ToNewObject;
end;

var
  RegisteredClass: array of record
    ClassName: string;
    ClassType: TClass;
  end;

function FindClassForJSON(const ClassName: string): integer;
begin
  for result := 0 to high(RegisteredClass) do
    if IdemPropName(RegisteredClass[result].ClassName,ClassName) then
      exit;
  result := -1;
end;

function CreateClassForJSON(const ClassName: string): TObject;
var i: integer;
begin
  i := FindClassForJSON(ClassName);
  if i<0 then
    result := nil else
    result := RegisteredClass[i].ClassType.Create;
end;

procedure RegisterClassForJSON(const Classes: array of TClass);
var c,i: integer;
    name: string;
begin
  for c := 0 to high(Classes) do begin
    name := string(Classes[c].ClassName);
    i := FindClassForJSON(name);
    if i>=0 then
      continue;
    i := length(RegisteredClass);
    SetLength(RegisteredClass,i+1);
    RegisteredClass[i].ClassName := Name;
    RegisteredClass[i].ClassType := Classes[c];
  end;
end;

function ObjectToJSON(Instance: TObject; StoreClassName: boolean): string;
var TypeInfo: PTypeInfo;
    PropCount, i: integer;
    PropList: PPropList;
    PropInfo: PPropInfo;
begin
  if Instance=nil then begin
    result := 'null';
    exit;
  end;
  {$ifndef NEXTGEN}
  if Instance.InheritsFrom(TList) then begin
    if TList(Instance).Count=0 then
      result := '[]' else begin
      result := '[';
      for i := 0 to TList(Instance).Count-1 do
        result := result+ObjectToJSON(TObject(
          TList(Instance).List{$ifdef FPC}^{$endif}[i]),StoreClassName)+',';
      result[length(result)] := ']';
    end;
    exit;
  end;
  {$endif}
  if Instance.InheritsFrom(TStrings) then begin
    if TStrings(Instance).Count=0 then
      result := '[]' else begin
      result := '[';
      for i := 0 to TStrings(Instance).Count-1 do
        result := result+StringToJSON(TStrings(Instance).Strings[i])+',';
      result[length(result)] := ']';
    end;
    exit;
  end;
  if Instance.InheritsFrom(TCollection) then begin
    if TCollection(Instance).Count=0 then
      result := '[]' else begin
      result := '[';
      for i := 0 to TCollection(Instance).Count-1 do
        result := result+ObjectToJSON(TCollection(Instance).Items[i],StoreClassName)+',';
      result[length(result)] := ']';
    end;
    exit;
  end;
  TypeInfo := Instance.ClassInfo;
  if TypeInfo=nil then begin
    result := 'null';
    exit;
  end;
  PropCount := GetPropList(TypeInfo,PropList);
  if PropCount>0 then
    try
      if StoreClassName then
        result := '{"ClassName":"'+string(Instance.ClassName)+'",' else
        result := '{';
      for i := 0 to PropCount-1 do begin
        PropInfo := PropList^[i];
        result := result+StringToJSON(ShortStringToString(@PropInfo^.Name))+':'+
          ValueToJSON(GetInstanceProp(Instance,PropInfo))+',';
      end;
      result[length(result)] := '}';
    finally
      FreeMem(PropList);
    end else
    result := 'null';
end;

procedure GetPublishedMethods(Instance: TObject;
  out Methods: TPublishedMethodDynArray);
var n: integer;
  procedure AddParentsFirst(C: TClass);
  type
    TMethodInfo = packed record
    {$ifdef FPC}
      Name: PShortString;
      Addr: Pointer;
    {$else}
      Len: Word;
      Addr: Pointer;
      Name: Byte;
    {$endif}
    end;
  var M: ^TMethodInfo;
      Method: TMethod;
      i,MCount: integer;
  begin
    if C=nil then
      exit;
    AddParentsFirst(C.ClassParent); // put children methods afterward
    M := PPointer(NativeInt(C)+vmtMethodTable)^;
    if M=nil then
      exit;
    Method.Data := Instance;
    MCount := {$ifdef FPC}PCardinal{$else}PWord{$endif}(M)^;
    inc({$ifdef FPC}PCardinal{$else}PWord{$endif}(M));
    for i := 1 to MCount do begin
      Method.Code := M^.Addr;
      if n>=length(Methods) then
        SetLength(Methods,n+32);
      Methods[n].Name := {$ifdef FPC}M^.Name^{$else}ShortStringToString(@M^.Name){$endif};
      Methods[n].Method := Method;
      inc(n);
      {$ifdef FPC}
      inc(M);
      {$else}
      inc(PByte(M),M^.Len);
      {$endif}
    end;
  end;
begin
  if Instance=nil then
    exit;
  n := 0;
  AddParentsFirst(Instance.ClassType);
  SetLength(Methods,n);
end;


{ TJSONVariantData }

procedure TJSONVariantData.Init;
begin
  VType := JSONVariantType.VarType;
  {$ifdef UNICODE} // makes compiler happy
  _Align := 0;
  {$endif}
  VKind := jvUndefined;
  VCount := 0;
  SetLength(Names, 0);
  SetLength(Values, 0);
  pointer(Names) := nil;
  pointer(Values) := nil;
end;

procedure TJSONVariantData.Init(const JSON: string);
begin
  Init;
  FromJSON(JSON);
  if VType=varNull then
    VKind := jvObject else
  if VType<>JSONVariantType.VarType then
    Init; // we expect a true JSON array or object here
end;

procedure TJSONVariantData.InitFrom(const aValues: TVariantDynArray); 
begin
  Init;
  VKind := jvArray;
  Values := aValues;
end;

procedure TJSONVariantData.AddNameValue(const aName: string;
  const aValue: variant);
begin
  if VKind=jvUndefined then
    VKind := jvObject else
    if VKind<>jvObject then
      raise EJSONException.CreateFmt('AddNameValue(%s) over array',[aName]);
  if VCount<=length(Values) then begin
    SetLength(Values,VCount+VCount shr 3+32);
    SetLength(Names,VCount+VCount shr 3+32);
  end;
  Values[VCount] := aValue;
  Names[VCount] := aName;
  inc(VCount);
end;

procedure TJSONVariantData.AddValue(const aValue: variant);
begin
  if VKind=jvUndefined then
    VKind := jvArray else
    if VKind<>jvArray then
      raise EJSONException.Create('AddValue() over object');
  if VCount<=length(Values) then
    SetLength(Values,VCount+VCount shr 3+32);
  Values[VCount] := aValue;
  inc(VCount);
end;

function TJSONVariantData.FromJSON(const JSON: string): boolean;
var Parser: TJSONParser;
begin
  Parser.Init(JSON,1);
  result := Parser.GetNextJSON(variant(self)) in [kObject,kArray];
end;

function TJSONVariantData.Data(const aName: string): PJSONVariantData;
var i: integer;
begin
  i := NameIndex(aName);
  if (i<0) or (TVarData(Values[i]).VType<>JSONVariantType.VarType) then
    result := nil else
    result := @Values[i];
end;

function TJSONVariantData.GetKind: TJSONVariantKind;
begin
  if (@self=nil) or (VType<>JSONVariantType.VarType) then
    result := jvUndefined else
    result := VKind;
end;

function TJSONVariantData.GetCount: integer;
begin
  if (@self=nil) or (VType<>JSONVariantType.VarType) then
    result := 0 else
    result := VCount;
end;

function TJSONVariantData.GetValue(const aName: string): variant;
begin
  VarClear(result);
  if (@self<>nil) and (VType=JSONVariantType.VarType) and (VKind=jvObject) then
    GetVarData(aName,TVarData(result));
end;

function TJSONVariantData.GetValueCopy(const aName: string): variant;
var i: cardinal;
begin
  VarClear(result);
  if (@self<>nil) and (VType=JSONVariantType.VarType) and (VKind=jvObject) then begin
    i := cardinal(NameIndex(aName));
    if i<cardinal(length(Values)) then
      result := Values[i];
  end;
end;

function TJSONVariantData.GetItem(aIndex: integer): variant;
begin
  VarClear(result);
  if (@self<>nil) and (VType=JSONVariantType.VarType) and (VKind=jvArray) then
    if cardinal(aIndex)<cardinal(VCount) then
      result := Values[aIndex];
end;

procedure TJSONVariantData.SetItem(aIndex: integer; const aItem: variant);
begin
  if (@self<>nil) and (VType=JSONVariantType.VarType) and (VKind=jvArray) then
    if cardinal(aIndex)<cardinal(VCount) then
      Values[aIndex] := aItem;
end;

function TJSONVariantData.GetVarData(const aName: string;
  var Dest: TVarData): boolean;
var i: cardinal;
begin
  i := cardinal(NameIndex(aName));
  if i<cardinal(length(Values)) then begin
    Dest.VType := varVariant or varByRef;
    Dest.VPointer := @Values[i];
    result := true;
  end else
    result := false;
end;

function TJSONVariantData.NameIndex(const aName: string): integer;
begin
  if (@self<>nil) and (VType=JSONVariantType.VarType) and (Names<>nil) then
    for result := 0 to VCount-1 do
      if Names[result]=aName then
        exit;
  result := -1;
end;

procedure TJSONVariantData.SetPath(const aPath: string; const aValue: variant);
var i: integer;
begin
  for i := length(aPath) downto 1 do 
    if aPath[i]='.' then begin
      EnsureData(copy(aPath,1,i-1))^.SetValue(copy(aPath,i+1,maxInt),aValue);
      exit;
    end;
  SetValue(aPath,aValue);
end;

function TJSONVariantData.EnsureData(const aPath: string): PJSONVariantData;
var i: integer;
    new: TJSONVariantData;
begin // recursive value set
  i := Pos('.',aPath);
  if i=0 then begin
    i := NameIndex(aPath);
    if i<0 then begin // not existing: create new
      new.Init;
      AddNameValue(aPath,variant(new));
      result := @Values[VCount-1];
    end else begin
      if TVarData(Values[i]).VType<>JSONVariantType.VarType then begin
        VarClear(Values[i]);
        TJSONVariantData(Values[i]).Init; // create as TJSONVariantData
      end;
      result := @Values[i];
    end;
  end else
    result := EnsureData(copy(aPath,1,i-1))^.EnsureData(copy(aPath,i+1,maxInt));
end;

function TJSONVariantData.AddItem: PJSONVariantData;
var new: TJSONVariantData;
begin
  new.Init;
  AddValue(variant(new));
  result := @Values[VCount-1];
end;

procedure TJSONVariantData.SetValue(const aName: string;
  const aValue: variant);
var i: integer;
begin
  if @self=nil then
    raise EJSONException.Create('Unexpected Value[] access');
  if aName='' then
    raise EJSONException.Create('Unexpected Value['''']');
  i := NameIndex(aName);
  if i<0 then
    AddNameValue(aName,aValue) else
    Values[i] := aValue;
end;

function TJSONVariantData.ToJSON: string;
var i: integer;
begin
  case VKind of
  jvObject:
    if VCount=0 then
      result := '{}' else begin
      result := '{';
      for i := 0 to VCount-1 do
        result := result+StringToJSON(Names[i])+':'+ValueToJSON(Values[i])+',';
      result[length(result)] := '}';
  end;
  jvArray:
    if VCount=0 then
      result := '[]' else begin
      result := '[';
      for i := 0 to VCount-1 do
        result := result+ValueToJSON(Values[i])+',';
      result[length(result)] := ']';
    end;
  else result := 'null';
  end;
end;

function TJSONVariantData.ToNewObject: TObject;
var ndx,i: Integer;
begin
  result := nil;
  if (Kind<>jvObject) or (Count=0) then
    exit;
  ndx := NameIndex('ClassName');
  if ndx<0 then
    exit;
  result := CreateClassForJSON(Values[ndx]);
  if result=nil then
    exit; // class name has not been registered
  for i := 0 to Count-1 do
    if i<>ndx then
      SetInstanceProp(result,GetPropInfo(result,Names[i]),Values[i]);
end;

function TJSONVariantData.ToObject(Instance: TObject): boolean;
var i: integer;
    aItem: TCollectionItem;
begin
  result := false;
  if Instance=nil then
    exit;
  case Kind of
  jvObject:
    for i := 0 to Count-1 do
      SetInstanceProp(Instance,
        GetPropInfo(Instance,Names[i]),Values[i]);
  jvArray:
    if Instance.InheritsFrom(TCollection) then begin
      TCollection(Instance).Clear;
      for i := 0 to Count-1 do begin
        aItem := TCollection(Instance).Add;
        if not JSONVariantData(Values[i])^.ToObject(aItem) then
          exit;
      end;
    end else
    if Instance.InheritsFrom(TStrings) then
    try
      TStrings(Instance).BeginUpdate;
      TStrings(Instance).Clear;
      for i := 0 to Count-1 do
        TStrings(Instance).Add(Values[i]);
    finally
      TStrings(Instance).EndUpdate;
    end else
      exit;
  else
    exit;
  end;
  result := true;
end;


{ TJSONVariant }

procedure TJSONVariant.Cast(var Dest: TVarData; const Source: TVarData);
begin
  CastTo(Dest,Source,VarType);
end;

procedure TJSONVariant.CastTo(var Dest: TVarData; const Source: TVarData;
  const AVarType: TVarType);
begin
  if Source.VType<>VarType then
    RaiseCastError;
  variant(Dest) := TJSONVariantData(Source).ToJSON;
end;

procedure TJSONVariant.Clear(var V: TVarData);
begin
  V.VType := varEmpty;
  Finalize(TJSONVariantData(V).Names);
  Finalize(TJSONVariantData(V).Values);
end;

procedure TJSONVariant.Copy(var Dest: TVarData; const Source: TVarData;
  const Indirect: Boolean);
begin
  if Indirect then
    SimplisticCopy(Dest,Source,true) else begin
    VarClear(variant(Dest));
    TJSONVariantData(Dest).Init;
    TJSONVariantData(Dest) := TJSONVariantData(Source);
  end;
end;

{$ifndef FPC}
{$ifndef ISDELPHI6}
function TJSONVariant.FixupIdent(const AText: string): string;
begin // we expect the names to be case-sensitive
  result := AText;
end;
{$endif}
{$endif}

function TJSONVariant.GetProperty(var Dest: TVarData; const V: TVarData;
  const Name: string): Boolean;
begin
  if not TJSONVariantData(V).GetVarData(Name,Dest) then
    Dest.VType := varNull;
  result := true;
end;

{$ifdef FPC_VARIANTSETVAR}
function TJSONVariant.SetProperty(var V: TVarData; const Name: string;
  const Value: TVarData): Boolean;
{$else}
function TJSONVariant.SetProperty(const V: TVarData; const Name: string;
  const Value: TVarData): Boolean;
{$endif}
begin
  {$ifdef FPC}
  {$ifndef FPC_VARIANTSETVAR} 
  raise EJSONException.Create('Setting TJSONVariant via late-binding does not'+
    ' work with FPC - see http://mantis.freepascal.org/view.php?id=26773 -'+
    ' use latest SVN or JSONVariantDataSafe(jsonvar)^[''prop''] := ... instead');
  {$endif}
  {$endif}
  TJSONVariantData(V).SetValue(Name,variant(Value));
  result := true;
end;


{ TJSONTable }

constructor TJSONTable.Create(const aJSON: string);
var f,firstValue: integer;
    EndOfField: char;
    fieldCount, fieldName, dummy: variant;
    Parser: TJSONParser;
begin
  Parser.Init(aJSON,1);
  fJSON := aJSON;
  EndOfField := #0;
  if (Parser.GetNextNonWhiteChar='{') and
      Parser.CheckNextIdent('fieldCount') and
     (Parser.GetNextJSON(fieldCount)=kInteger) and
     (Parser.GetNextNonWhiteChar=',') and
      Parser.CheckNextIdent('values') and
     (Parser.GetNextNonWhiteChar='[') then begin
    // non expanded format: {"fieldCount":2,"values":["ID","Int",1,0,2,0,3,...]
    SetLength(fFieldNames,integer(fieldCount));
    for f := 0 to high(fFieldNames) do begin
      if Parser.GetNextJSON(fieldName)<>kString then
        exit;
      fFieldNames[f] := fieldName;
      EndOfField := Parser.GetNextNonWhiteChar;
      if EndOfField<>',' then
        if (EndOfField<>']') or (f<>High(FieldNames)) then
          exit
    end;
    if EndOfField=',' then
      fJSONIndexFirstValue := Parser.Index;
  end else begin
    // expanded format: [{"ID":1,"Int":0},{"ID":2,"Int":0},{"ID":3,...]
    Parser.Index := 1;
    if (Parser.GetNextNonWhiteChar='[') and
       (Parser.GetNextNonWhiteChar='{') then begin
      firstValue := Parser.Index;
      f := 0;
      repeat
        if (Parser.GetNextJSON(fieldName)<>kString) or
           (Parser.GetNextNonWhiteChar<>':') then
          exit;
        if Parser.GetNextJSON(dummy)=kNone then
          exit;
        SetLength(fFieldNames,f+1);
        fFieldNames[f] := fieldName;
        inc(f);
        EndOfField := Parser.GetNextNonWhiteChar;
        if EndOfField<>',' then
          if EndOfField='}' then
            break else
            exit;
      until false;
      fJSONIndexFirstValue := firstValue;
      fJSONExpanded := true;
    end;    
  end;
  SetLength(fRowValues,length(fFieldNames));
end;

function TJSONTable.FieldIndex(const FieldName: string): integer;
begin
  for result := 0 to high(fFieldNames) do
    if CompareText(fFieldNames[result],FieldName)=0 then
      exit;
  result := -1;
end;

function TJSONTable.Get(const FieldName: string): variant;
var ndx: integer;
begin
  ndx := FieldIndex(FieldName);
  if ndx<0 then
    result := null else
    result := fRowValues[ndx];
end;

function TJSONTable.Step(SeekFirst: boolean): boolean;
var f: integer;
    EndOfField: char;
    Parser: TJSONParser;
begin
  result := false;
  if SeekFirst or (fJSONCurrentIndex=0) then
    fJSONCurrentIndex := fJSONIndexFirstValue;
  if fJSONCurrentIndex<=0 then
    exit;
  Parser.Init(fJSON,fJSONCurrentIndex);
  fJSONCurrentIndex := -1; // indicates end of content in case of exit below
  EndOfField := #0;
  for f := 0 to high(fRowValues) do begin
    if fJSONExpanded and not Parser.CheckNextIdent(fFieldNames[f]) then
      exit;
    if Parser.GetNextJSON(fRowValues[f])=kNone then
      exit;
    EndOfField := Parser.GetNextNonWhiteChar;
    if EndOfField<>',' then
      if f<>High(fRowValues) then
        exit else
      if ((EndOfField=']') and (not fJSONExpanded)) or
         ((EndOfField='}') and fJSONExpanded) then
        break else
        exit;
  end;
  if fJSONExpanded then begin
    if EndOfField<>'}' then
      exit;
    EndOfField := Parser.GetNextNonWhiteChar;
    if (EndOfField=',') and
       (Parser.GetNextNonWhiteChar<>'{') then
      exit;
  end;
  if EndOfField=',' then
    fJSONCurrentIndex := Parser.Index; // indicates next Step() has data
  result := true;
end;

function TJSONTable.StepValue(var RowValues: variant; SeekFirst: boolean): boolean;
begin
  result := Step(SeekFirst);
  if not result then
    exit;
  if TVarData(RowValues).VType<>JSONVariantType.VarType then begin
    VarClear(RowValues);
    TJSONVariantData(RowValues).Init;
  end;
  TJSONVariantData(RowValues).VKind := jvObject;
  TJSONVariantData(RowValues).VCount := Length(fFieldNames);
  TJSONVariantData(RowValues).Names := fFieldNames;
  TJSONVariantData(RowValues).Values := fRowValues;
end;


{ TJSONTableObject }

function TJSONTableObject.StepObject(Instance: TObject; SeekFirst: boolean=false): boolean;
begin
  if (Instance=nil) then
    result := false else
    result := Step(SeekFirst);
  if result then
    FillInstance(Instance);
end;

procedure TJSONTableObject.FillInstance(Instance: TObject);
var i: integer;
begin
  if fTypeInfo<>Instance.ClassInfo then
    FillPropInfo(Instance.ClassInfo);
  for i := 0 to Length(fPropInfo)-1 do
    SetInstanceProp(Instance,fPropInfo[i],fRowValues[i]);
end;

function TJSONTableObject.GetPropInfo(aTypeInfo: TRTTITypeInfo;
  const PropName: string): TRTTIPropInfo;
begin
  result := TypInfo.GetPropInfo(PTypeInfo(aTypeInfo),PropName);
end;

procedure TJSONTableObject.FillPropInfo(aTypeInfo: TRTTITypeInfo);
var i: integer;
begin
  fTypeInfo := aTypeInfo;
  SetLength(fPropInfo,Length(fFieldNames));
  for i := 0 to length(FieldNames)-1 do
    fPropInfo[i] := GetPropInfo(aTypeInfo,fFieldNames[i]);
end;


initialization
  JSONVariantType := TJSONVariant.Create;
  {$ifndef FPC}
  {$ifndef NOFORMATSETTINGS}
  {$ifdef ISDELPHIXE}
  SettingsUS := TFormatSettings.Create('en_US');
  {$else}
  GetLocaleFormatSettings($0409,SettingsUS);
  {$endif}
  {$endif}
  {$endif}
end.
