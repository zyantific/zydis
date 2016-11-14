unit formEditorX86Registers;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes,
  System.UITypes, Vcl.Graphics, Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Zydis.InstructionEditor,
  System.ImageList, Vcl.ImgList, cxGraphics, Vcl.StdCtrls, VirtualTrees;

type
  TfrmEditorX86Registers = class(TForm)
    GroupBox: TGroupBox;
    btnCancel: TButton;
    btnApply: TButton;
    imgIcons16: TcxImageList;
    VirtualTreeView: TVirtualStringTree;
    imgTreeView: TcxImageList;
    procedure btnApplyClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure VirtualTreeViewFreeNode(Sender: TBaseVirtualTree; Node: PVirtualNode);
    procedure VirtualTreeViewGetImageIndex(Sender: TBaseVirtualTree; Node: PVirtualNode;
      Kind: TVTImageKind; Column: TColumnIndex; var Ghosted: Boolean;
      var ImageIndex: System.UITypes.TImageIndex);
    procedure VirtualTreeViewGetText(Sender: TBaseVirtualTree; Node: PVirtualNode;
      Column: TColumnIndex; TextType: TVSTTextType; var CellText: string);
    procedure VirtualTreeViewCollapsing(Sender: TBaseVirtualTree; Node: PVirtualNode;
      var Allowed: Boolean);
    procedure VirtualTreeViewChecked(Sender: TBaseVirtualTree; Node: PVirtualNode);
  strict private
    FApplyChanges: Boolean;
    FRegisters: TX86RegisterSet;
  strict private
    procedure SetRegisters(const Value: TX86RegisterSet);
  public
    property ApplyChanges: Boolean read FApplyChanges;
    property Registers: TX86RegisterSet read FRegisters write SetRegisters;
  end;

var
  frmEditorX86Registers: TfrmEditorX86Registers;

implementation

uses
  System.TypInfo;

{$R *.dfm}

type
  PNodeData = ^TNodeData;
  TNodeData = record
  public
    IsCategory: Boolean;
    Text: String;
    Value: TX86Register;
  end;

{ TfrmEditorX86Registers }

procedure TfrmEditorX86Registers.btnApplyClick(Sender: TObject);
begin
  FApplyChanges := true;
  Close;
end;

procedure TfrmEditorX86Registers.btnCancelClick(Sender: TObject);
begin
  Close;
end;

procedure TfrmEditorX86Registers.FormCreate(Sender: TObject);

function AddCategory(Root: PVirtualNode; const Text: String): PVirtualNode;
var
  NodeData: PNodeData;
begin
  Result := VirtualTreeView.AddChild(Root);
  if (Assigned(Root)) then
  begin
    VirtualTreeView.CheckType[Result] := ctTriStateCheckBox;
  end;
  NodeData := VirtualTreeView.GetNodeData(Result);
  NodeData^.IsCategory := true;
  NodeData^.Text := Text;
end;

procedure AddRegisterRange(Root: PVirtualNode; RegisterLow, RegisterHigh: TX86Register);
var
  Node: PVirtualNode;
  NodeData: PNodeData;
  R: TX86Register;
  S: String;
begin
  for R := RegisterLow to RegisterHigh do
  begin
    Node := VirtualTreeView.AddChild(Root);
    VirtualTreeView.CheckType[Node] := ctTriStateCheckBox;
    NodeData := VirtualTreeView.GetNodeData(Node);
    NodeData^.IsCategory := false;
    S := GetEnumName(TypeInfo(TX86Register), Ord(R));
    Delete(S, 1, 3);
    NodeData^.Text := S;
    NodeData^.Value := R;
  end;
end;

var
  Root, N1, N2: PVirtualNode;
begin
  FRegisters := [];
  VirtualTreeView.NodeDataSize := SizeOf(TNodeData);
  VirtualTreeView.BeginUpdate;
  try
    Root := AddCategory(nil, 'Root');

    N1 := AddCategory(Root, 'General Purpose Registers');
    N2 := AddCategory(N1, '64-bit');
    AddRegisterRange(N2, regRAX, regR15);
    N2 := AddCategory(N1, '32-bit');
    AddRegisterRange(N2, regEAX, regR15D);
    N2 := AddCategory(N1, '16-bit');
    AddRegisterRange(N2, regAX, regR15W);
    N2 := AddCategory(N1, '8-bit');
    AddRegisterRange(N2, regAL, regR15B);
    VirtualTreeView.Expanded[N1] := true;

    N1 := AddCategory(Root, 'Floating Point Registers');
    N2 := AddCategory(N1, 'Legacy');
    AddRegisterRange(N2, regST0, regST7);
    N2 := AddCategory(N1, 'Multimedia');
    AddRegisterRange(N2, regMM0, regMM7);
    VirtualTreeView.Expanded[N1] := true;

    N1 := AddCategory(Root, 'Vector Registers');
    N2 := AddCategory(N1, '512-bit');
    AddRegisterRange(N2, regZMM0, regZMM31);
    N2 := AddCategory(N1, '256-bit');
    AddRegisterRange(N2, regYMM0, regYMM31);
    N2 := AddCategory(N1, '128-bit');
    AddRegisterRange(N2, regXMM0, regXMM31);
    VirtualTreeView.Expanded[N1] := true;

    N1 := AddCategory(Root, 'Special Registers');
    AddRegisterRange(N1, regRFLAGS, regMXCSR);

    N1 := AddCategory(Root, 'Segment Registers');
    AddRegisterRange(N1, regES, regFS);

    N1 := AddCategory(Root, 'Table Registers');
    AddRegisterRange(N1, regGDTR, regTR);

    N1 := AddCategory(Root, 'Test Registers');
    AddRegisterRange(N1, regTR0, regTR7);

    N1 := AddCategory(Root, 'Control Registers');
    AddRegisterRange(N1, regCR0, regCR15);

    N1 := AddCategory(Root, 'Debug Registers');
    AddRegisterRange(N1, regDR0, regDR15);

    N1 := AddCategory(Root, 'Mask Registers');
    AddRegisterRange(N1, regK0, regK7);

    N1 := AddCategory(Root, 'Bound Registers');
    AddRegisterRange(N1, regBND0, regBNDSTATUS);

    VirtualTreeView.Expanded[Root] := true;
  finally
    VirtualTreeView.EndUpdate;
  end;
end;

procedure TfrmEditorX86Registers.VirtualTreeViewChecked(Sender: TBaseVirtualTree; Node: PVirtualNode);
var
  NodeData: PNodeData;
begin
  NodeData := Sender.GetNodeData(Node);
  if (Assigned(NodeData) and (not NodeData^.IsCategory)) then
  begin
    case Sender.CheckState[Node] of
      csCheckedNormal:
        FRegisters := FRegisters + [NodeData^.Value];
      csUncheckedNormal:
        FRegisters := FRegisters - [NodeData^.Value];
    end;
  end;
end;

procedure TfrmEditorX86Registers.VirtualTreeViewCollapsing(Sender: TBaseVirtualTree;
  Node: PVirtualNode; var Allowed: Boolean);
begin
  Allowed := (Node.Parent <> Sender.RootNode);
end;

procedure TfrmEditorX86Registers.VirtualTreeViewFreeNode(Sender: TBaseVirtualTree; Node: PVirtualNode);
var
  NodeData: PNodeData;
begin
  NodeData := Sender.GetNodeData(Node);
  if (Assigned(NodeData)) then
  begin
    Finalize(NodeData^);
  end;
end;

procedure TfrmEditorX86Registers.VirtualTreeViewGetImageIndex(Sender: TBaseVirtualTree;
  Node: PVirtualNode; Kind: TVTImageKind; Column: TColumnIndex; var Ghosted: Boolean;
  var ImageIndex: System.UITypes.TImageIndex);
var
  NodeData: PNodeData;
begin
  ImageIndex := -1;
  if (Kind in [ikNormal, ikSelected]) then
  begin
    NodeData := Sender.GetNodeData(Node);
    if (Assigned(NodeData)) then
    begin
      if (NodeData^.IsCategory) then
      begin
        ImageIndex := 0;
      end else
      begin
        ImageIndex := 1;
      end;
    end;
  end;
end;

procedure TfrmEditorX86Registers.VirtualTreeViewGetText(Sender: TBaseVirtualTree;
  Node: PVirtualNode; Column: TColumnIndex; TextType: TVSTTextType; var CellText: string);
var
  NodeData: PNodeData;
begin
  NodeData := Sender.GetNodeData(Node);
  if (Assigned(NodeData)) then
  begin
    CellText := NodeData^.Text;
  end;
end;

procedure TfrmEditorX86Registers.SetRegisters(const Value: TX86RegisterSet);
var
  Node: PVirtualNode;
  NodeData: PNodeData;
begin
  VirtualTreeView.BeginUpdate;
  try
    Node := VirtualTreeView.GetFirst;
    while (Assigned(Node)) do
    begin
      NodeData := VirtualTreeView.GetNodeData(Node);
      if (Assigned(NodeData) and (not NodeData^.IsCategory)) then
      begin
        if (NodeData^.Value in Value) then
        begin
          VirtualTreeView.CheckState[Node] := csCheckedNormal;
        end else
        begin
          VirtualTreeView.CheckState[Node] := csUncheckedNormal;
        end;
      end;
      Node := VirtualTreeView.GetNext(Node);
    end;
  finally
    VirtualTreeView.EndUpdate;
  end;
end;

end.
