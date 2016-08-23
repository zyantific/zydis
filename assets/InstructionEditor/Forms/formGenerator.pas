unit formGenerator;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, VirtualTrees, System.ImageList, Vcl.ImgList, cxGraphics,
  Vcl.StdCtrls, untInstructionEditor;

type
  TfrmGenerator = class(TForm)
    GroupBox: TGroupBox;
    btnClose: TButton;
    btnGenerate: TButton;
    imgIcons16: TcxImageList;
    TreeView: TVirtualStringTree;
    imgTreeView: TcxImageList;
    procedure FormCreate(Sender: TObject);
    procedure TreeViewCollapsing(Sender: TBaseVirtualTree; Node: PVirtualNode;
      var Allowed: Boolean);
    procedure TreeViewFreeNode(Sender: TBaseVirtualTree; Node: PVirtualNode);
    procedure TreeViewGetImageIndex(Sender: TBaseVirtualTree; Node: PVirtualNode;
      Kind: TVTImageKind; Column: TColumnIndex; var Ghosted: Boolean; var ImageIndex: Integer);
    procedure TreeViewGetText(Sender: TBaseVirtualTree; Node: PVirtualNode; Column: TColumnIndex;
      TextType: TVSTTextType; var CellText: string);
    procedure btnCloseClick(Sender: TObject);
    procedure btnGenerateClick(Sender: TObject);
    procedure TreeViewBeforeCellPaint(Sender: TBaseVirtualTree; TargetCanvas: TCanvas;
      Node: PVirtualNode; Column: TColumnIndex; CellPaintMode: TVTCellPaintMode; CellRect: TRect;
      var ContentRect: TRect);
  strict private
    FEditor: TInstructionEditor;
    FProgressNodeTotal: PVirtualNode;
    FProgressNode: array[TGeneratorWorkOperation] of PVirtualNode;
    FInfoNode: array[0..6] of PVirtualNode;
    FCurrentOperation: TGeneratorWorkOperation;
  strict private
    procedure GeneratorWorkStart(Sender: TObject; Operation: TGeneratorWorkOperation; MinWorkCount,
      MaxWorkCount: Integer);
    procedure GeneratorWork(Sender: TObject; WorkCount: Integer);
    procedure GeneratorWorkEnd(Sender: TObject);
  public
    property Editor: TInstructionEditor read FEditor write FEditor;
  end;

var
  frmGenerator: TfrmGenerator;

implementation

uses
  untHelperClasses;

{$R *.dfm}

type
  TGeneratorNodeType = (ntCategory, ntSpacer, ntOperation, ntValue);

  PGeneratorNodeData = ^TGeneratorNodeData;
  TGeneratorNodeData = record
  public
    NodeType: TGeneratorNodeType;
    Text: String;
    ProgressActive: Boolean;
    ProgressMax: Integer;
    ProgressUpdateStep: Integer;
    Progress: Double;
    Value: String;
  public
    procedure ProgressInit(MaxWorkCount: Integer; MinWorkCount: Integer); inline;
    procedure ProgressUpdate(NewProgress: Double); inline;
    procedure WorkCountUpdate(WorkCount: Integer); inline;
    function IsProgressUpdateStep(WorkCount: Integer): Boolean; inline;
  end;

{ TGeneratorNodeData }

function TGeneratorNodeData.IsProgressUpdateStep(WorkCount: Integer): Boolean;
begin
  Assert(NodeType = ntOperation);
  Result := ((WorkCount mod ProgressUpdateStep) = 0);
end;

procedure TGeneratorNodeData.ProgressInit(MaxWorkCount, MinWorkCount: Integer);
begin
  Assert(NodeType = ntOperation);
  ProgressMax := (MaxWorkCount - MinWorkCount);
  ProgressUpdateStep := Round(ProgressMax / 100) + 1;
end;

procedure TGeneratorNodeData.ProgressUpdate(NewProgress: Double);
var
  Format: TFormatSettings;
begin
  Assert(NodeType = ntOperation);
  Progress := NewProgress;
  Format.DecimalSeparator := '.';
  Value := FormatFloat('0.00', Progress * 100, Format) + '%';
end;

procedure TGeneratorNodeData.WorkCountUpdate(WorkCount: Integer);
begin
  Assert(NodeType = ntOperation);
  if (ProgressMax = 0) then
  begin
    ProgressUpdate(1.0);
  end else
  begin
    ProgressUpdate(WorkCount / ProgressMax);
  end;
end;

{ TfrmGenerator }

procedure TfrmGenerator.btnCloseClick(Sender: TObject);
begin
  Close;
end;

procedure TfrmGenerator.btnGenerateClick(Sender: TObject);

procedure SetInfoNodeValue(Node: PVirtualNode; const Value: String);
var
  NodeData: PGeneratorNodeData;
begin
  NodeData := TreeView.GetNodeData(Node);
  NodeData^.Value := Value;
end;

var
  Generator: TTableGenerator;
  Node: PVirtualNode;
  NodeData: PGeneratorNodeData;
  I: Integer;
begin
  TreeView.BeginUpdate;
  try
    for Node in FProgressNode do
    begin
      NodeData := TreeView.GetNodeData(Node);
      NodeData^.ProgressActive := false;
      NodeData^.ProgressUpdate(0);
    end;
    NodeData := TreeView.GetNodeData(FProgressNodeTotal);
    NodeData^.ProgressActive := false;
    NodeData^.ProgressUpdate(0);
  finally
    TreeView.EndUpdate;
  end;
  Generator := TTableGenerator.Create;
  try
    Generator.OnWorkStart := GeneratorWorkStart;
    Generator.OnWork := GeneratorWork;
    Generator.OnWorkEnd := GeneratorWorkEnd;
    Generator.GenerateFiles(FEditor,
      'D:\Verteron Development\GitHub\zyan-disassembler-engine old\include\Zydis\Internal\');
    TreeView.BeginUpdate;
    try
      for I := Low(FInfoNode) to High(FInfoNode) do
      begin
        case I of
          0: SetInfoNodeValue(FInfoNode[I], IntToStr(Generator.Statistics.FilterCount));
          1: SetInfoNodeValue(FInfoNode[I], IntToStr(Generator.Statistics.DefinitionCount));
          2: SetInfoNodeValue(FInfoNode[I], IntToStr(Generator.Statistics.MnemonicCount));
          3: SetInfoNodeValue(FInfoNode[I], TSizeFormatter.Format(Generator.Statistics.FilterSize));
          4: SetInfoNodeValue(FInfoNode[I],
            TSizeFormatter.Format(Generator.Statistics.DefinitionSize));
          5: SetInfoNodeValue(FInfoNode[I],
            TSizeFormatter.Format(Generator.Statistics.MnemonicSize));
          6: SetInfoNodeValue(FInfoNode[I], TSizeFormatter.Format(Generator.Statistics.FilterSize
            + Generator.Statistics.DefinitionSize + Generator.Statistics.MnemonicSize));
        end;
      end;
    finally
      TreeView.EndUpdate;
    end;
    Application.ProcessMessages;
  finally
    Generator.Free;
  end;
end;

procedure TfrmGenerator.FormCreate(Sender: TObject);

function AddNodeData(Parent: PVirtualNode; NodeType: TGeneratorNodeType; const Text: String;
  const Value: String = ''): PVirtualNode;
var
  NodeData: PGeneratorNodeData;
begin
  Result := TreeView.AddChild(Parent);
  NodeData := TreeView.GetNodeData(Result);
  if (Assigned(NodeData)) then
  begin
    NodeData^.NodeType := NodeType;
    NodeData^.Text := Text;
    case NodeType of
      ntOperation:
        begin
          NodeData^.ProgressActive := false;
          NodeData^.ProgressUpdate(0);
        end;
      ntValue:
          NodeData^.Value := Value;
    end;
  end;
end;

var
  Category: PVirtualNode;
begin
  TreeView.NodeDataSize := SizeOf(TGeneratorNodeData);
  TreeView.BeginUpdate;
  try
    Category := AddNodeData(nil, ntCategory, 'Progress');
    FProgressNode[woIndexingDefinitions] :=
      AddNodeData(Category, ntOperation, 'Indexing definitions');
    FProgressNode[woIndexingFilters] :=
      AddNodeData(Category, ntOperation, 'Indexing filters');
    FProgressNode[woGeneratingFilterFiles] :=
      AddNodeData(Category, ntOperation, 'Generating filter files');
    FProgressNode[woGeneratingDefinitionFiles] :=
      AddNodeData(Category, ntOperation, 'Generating definition files');
    FProgressNode[woGeneratingMnemonicFiles] :=
      AddNodeData(Category, ntOperation, 'Generating mnemonic files');
    FProgressNodeTotal :=
      AddNodeData(Category, ntOperation, 'Total progress');
    TreeView.Expanded[Category] := true;
    AddNodeData(nil, ntSpacer, '');
    Category := AddNodeData(nil, ntCategory, 'Statistics');
    FInfoNode[0] := AddNodeData(Category, ntValue, 'Filter Count', '-');
    FInfoNode[1] := AddNodeData(Category, ntValue, 'Definition Count', '-');
    FInfoNode[2] := AddNodeData(Category, ntValue, 'Mnemonic Count', '-');
    FInfoNode[3] := AddNodeData(Category, ntValue, 'Filter Size', '-');
    FInfoNode[4] := AddNodeData(Category, ntValue, 'Definition Size', '-');
    FInfoNode[5] := AddNodeData(Category, ntValue, 'MnemonicSize', '-');
    FInfoNode[6] := AddNodeData(Category, ntValue, 'TotalSize', '-');
    TreeView.Expanded[Category] := true;
  finally
    TreeView.EndUpdate;
  end;
end;

procedure TfrmGenerator.GeneratorWork(Sender: TObject; WorkCount: Integer);
var
  Node: PVirtualNode;
  NodeData: PGeneratorNodeData;
  ProgressTotal: Double;
begin
  NodeData := TreeView.GetNodeData(FProgressNode[FCurrentOperation]);
  NodeData^.WorkCountUpdate(WorkCount);
  if (NodeData^.IsProgressUpdateStep(WorkCount)) then
  begin
    TreeView.RepaintNode(FProgressNode[FCurrentOperation]);
    ProgressTotal := 0;
    for Node in FProgressNode do
    begin
      NodeData := TreeView.GetNodeData(Node);
      ProgressTotal := ProgressTotal + NodeData^.Progress;
    end;
    NodeData := TreeView.GetNodeData(FProgressNodeTotal);
    NodeData^.ProgressUpdate(ProgressTotal / Length(FProgressNode));
    TreeView.RepaintNode(FProgressNodeTotal);
    Application.ProcessMessages;
  end;
end;

procedure TfrmGenerator.GeneratorWorkEnd(Sender: TObject);
var
  NodeData: PGeneratorNodeData;
begin
  NodeData := TreeView.GetNodeData(FProgressNode[FCurrentOperation]);
  NodeData^.ProgressActive := false;
  NodeData^.ProgressUpdate(1);
  TreeView.RepaintNode(FProgressNode[FCurrentOperation]);
  NodeData := TreeView.GetNodeData(FProgressNodeTotal);
  if (FCurrentOperation = High(TGeneratorWorkOperation)) then
  begin
    NodeData^.ProgressActive := false;
  end;
  NodeData^.ProgressUpdate((Integer(FCurrentOperation) + 1) / Length(FProgressNode));
  TreeView.RepaintNode(FProgressNodeTotal);
end;

procedure TfrmGenerator.GeneratorWorkStart(Sender: TObject; Operation: TGeneratorWorkOperation;
  MinWorkCount, MaxWorkCount: Integer);
var
  NodeData: PGeneratorNodeData;
begin
  FCurrentOperation := Operation;
  NodeData := TreeView.GetNodeData(FProgressNode[Operation]);
  NodeData^.ProgressInit(MaxWorkCount, MinWorkCount);
  NodeData^.ProgressActive := true;
  TreeView.RepaintNode(FProgressNode[FCurrentOperation]);
  NodeData := TreeView.GetNodeData(FProgressNodeTotal);
  if (FCurrentOperation = Low(TGeneratorWorkOperation)) then
  begin
    NodeData^.ProgressActive := true;
    TreeView.RepaintNode(FProgressNodeTotal);
  end;
end;

 procedure TfrmGenerator.TreeViewBeforeCellPaint(Sender: TBaseVirtualTree; TargetCanvas: TCanvas;
  Node: PVirtualNode; Column: TColumnIndex; CellPaintMode: TVTCellPaintMode; CellRect: TRect;
  var ContentRect: TRect);
var
  NodeData: PGeneratorNodeData;
  ProgressWidth: Integer;
begin
  if (Column = 1) then
  begin
    NodeData := Sender.GetNodeData(Node);
    if (Assigned(NodeData) and (NodeData^.NodeType = ntOperation) and
      (NodeData^.Progress <> 1) and (NodeData^.Progress <> 0)) then
    begin
      TargetCanvas.Pen.Color := $0000A162;
      TargetCanvas.Brush.Color := $0055F2B5;
      TargetCanvas.Rectangle(CellRect.Left, CellRect.Top, CellRect.Right,
        CellRect.Bottom - CellRect.Top);
      TargetCanvas.Pen.Color := $0000A162;
      TargetCanvas.Brush.Color := $000FE18E;
      ProgressWidth := Round(NodeData^.Progress * (CellRect.Right - CellRect.Left));
      TargetCanvas.Rectangle(CellRect.Left, CellRect.Top, CellRect.Left + ProgressWidth,
        CellRect.Bottom - CellRect.Top);
    end;
  end;
end;

procedure TfrmGenerator.TreeViewCollapsing(Sender: TBaseVirtualTree; Node: PVirtualNode;
  var Allowed: Boolean);
begin
  Allowed := false;
end;

procedure TfrmGenerator.TreeViewFreeNode(Sender: TBaseVirtualTree; Node: PVirtualNode);
var
  NodeData: PGeneratorNodeData;
begin
  NodeData := Sender.GetNodeData(Node);
  if (Assigned(NodeData)) then
  begin
    Finalize(NodeData^);
  end;
end;

procedure TfrmGenerator.TreeViewGetImageIndex(Sender: TBaseVirtualTree; Node: PVirtualNode;
  Kind: TVTImageKind; Column: TColumnIndex; var Ghosted: Boolean; var ImageIndex: Integer);
var
  NodeData: PGeneratorNodeData;
begin
  ImageIndex := -1;
  if (Column = 0) and (Kind in [ikNormal, ikSelected]) then
  begin
    NodeData := Sender.GetNodeData(Node);
    if (Assigned(NodeData)) then
    begin
      case NodeData^.NodeType of
        ntCategory:
          ImageIndex := 0;
        ntOperation:
          begin
            if (NodeData^.ProgressActive) then
            begin
              ImageIndex := 2;
            end else
            begin
              ImageIndex := 1;
            end;
          end;
        ntValue:
          ImageIndex := 3;
      end;
    end;
  end;
end;

procedure TfrmGenerator.TreeViewGetText(Sender: TBaseVirtualTree; Node: PVirtualNode;
  Column: TColumnIndex; TextType: TVSTTextType; var CellText: string);
var
  NodeData: PGeneratorNodeData;
begin
  CellText := '';
  NodeData := Sender.GetNodeData(Node);
  if (Assigned(NodeData)) then
  begin
    if (NodeData^.NodeType in [ntCategory, ntOperation, ntValue]) then
    begin
      case Column of
        0: CellText := NodeData^.Text;
        1: CellText := NodeData^.Value;
      end;
    end;
  end;
end;

end.
