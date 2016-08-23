unit formEditorCPUIDFeatureFlags;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, untInstructionEditor, cxOI, Vcl.StdCtrls, System.ImageList,
  Vcl.ImgList, cxGraphics, VirtualTrees;

type
  TfrmEditorCPUIDFeatureFlags = class(TForm)
    GroupBox: TGroupBox;
    btnCancel: TButton;
    imgIcons16: TcxImageList;
    btnApply: TButton;
    VirtualTreeView: TVirtualStringTree;
    imgTreeView: TcxImageList;
    procedure btnApplyClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure VirtualTreeViewChecked(Sender: TBaseVirtualTree; Node: PVirtualNode);
    procedure VirtualTreeViewCollapsing(Sender: TBaseVirtualTree; Node: PVirtualNode;
      var Allowed: Boolean);
    procedure VirtualTreeViewFreeNode(Sender: TBaseVirtualTree; Node: PVirtualNode);
    procedure VirtualTreeViewGetImageIndex(Sender: TBaseVirtualTree; Node: PVirtualNode;
      Kind: TVTImageKind; Column: TColumnIndex; var Ghosted: Boolean; var ImageIndex: Integer);
    procedure VirtualTreeViewGetText(Sender: TBaseVirtualTree; Node: PVirtualNode;
      Column: TColumnIndex; TextType: TVSTTextType; var CellText: string);
  strict private
    FApplyChanges: Boolean;
    FFeatureFlags: TCPUIDFeatureFlagSet;
  strict private
    procedure SetFeatureFlags(const Value: TCPUIDFeatureFlagSet);
  public
    property ApplyChanges: Boolean read FApplyChanges;
    property FeatureFlags: TCPUIDFeatureFlagSet read FFeatureFlags write SetFeatureFlags;
  end;

var
  frmEditorCPUIDFeatureFlags: TfrmEditorCPUIDFeatureFlags;

implementation

uses
  System.TypInfo;

{$R *.dfm}

type
  PNodeData = ^TNodeData;
  TNodeData = record
  public
    Text: String;
    Value: TCPUIDFeatureFlag;
  end;

procedure TfrmEditorCPUIDFeatureFlags.btnApplyClick(Sender: TObject);
begin
  FApplyChanges := true;
  Close;
end;

procedure TfrmEditorCPUIDFeatureFlags.btnCancelClick(Sender: TObject);
begin
  Close;
end;

procedure TfrmEditorCPUIDFeatureFlags.FormCreate(Sender: TObject);
var
  Root,
  Node: PVirtualNode;
  NodeData: PNodeData;
  C: TCPUIDFeatureFlag;
  S: String;
begin
  FFeatureFlags := [];
  VirtualTreeView.NodeDataSize := SizeOf(TNodeData);
  VirtualTreeView.BeginUpdate;
  try
    Root := VirtualTreeView.AddChild(nil);
    NodeData := VirtualTreeView.GetNodeData(Root);
    NodeData^.Text := 'CPUID Feature Flags';
    for C := Low(TCPUIDFeatureFlag) to High(TCPUIDFeatureFlag) do
    begin
      Node := VirtualTreeView.AddChild(Root);
      VirtualTreeView.CheckType[Node] := ctCheckBox;
      NodeData := VirtualTreeView.GetNodeData(Node);
      S := GetEnumName(TypeInfo(TCPUIDFeatureFlag), Ord(C));
      Delete(S, 1, 2);
      NodeData^.Text := S;
      NodeData^.Value := C;
    end;
    VirtualTreeView.Expanded[Root] := true;
  finally
    VirtualTreeView.EndUpdate;
  end;
end;

procedure TfrmEditorCPUIDFeatureFlags.SetFeatureFlags(const Value: TCPUIDFeatureFlagSet);
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
      if (Assigned(NodeData) and (Node.Parent <> VirtualTreeView.RootNode)) then
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

procedure TfrmEditorCPUIDFeatureFlags.VirtualTreeViewChecked(Sender: TBaseVirtualTree;
  Node: PVirtualNode);
var
  NodeData: PNodeData;
begin
  NodeData := Sender.GetNodeData(Node);
  if (Assigned(NodeData)) then
  begin
    case Sender.CheckState[Node] of
      csCheckedNormal:
        FFeatureFlags := FFeatureFlags + [NodeData^.Value];
      csUncheckedNormal:
        FFeatureFlags := FFeatureFlags - [NodeData^.Value];
    end;
  end;
end;

procedure TfrmEditorCPUIDFeatureFlags.VirtualTreeViewCollapsing(Sender: TBaseVirtualTree;
  Node: PVirtualNode; var Allowed: Boolean);
begin
  Allowed := false;
end;

procedure TfrmEditorCPUIDFeatureFlags.VirtualTreeViewFreeNode(Sender: TBaseVirtualTree;
  Node: PVirtualNode);
var
  NodeData: PNodeData;
begin
  NodeData := Sender.GetNodeData(Node);
  if (Assigned(NodeData)) then
  begin
    Finalize(NodeData^);
  end;
end;

procedure TfrmEditorCPUIDFeatureFlags.VirtualTreeViewGetImageIndex(Sender: TBaseVirtualTree;
  Node: PVirtualNode; Kind: TVTImageKind; Column: TColumnIndex; var Ghosted: Boolean;
  var ImageIndex: Integer);
begin
  ImageIndex := -1;
  if (Kind in [ikNormal, ikSelected]) then
  begin
    if (Node.Parent = Sender.RootNode) then
    begin
      ImageIndex := 0;
    end else
    begin
      ImageIndex := 1;
    end;
  end;
end;

procedure TfrmEditorCPUIDFeatureFlags.VirtualTreeViewGetText(Sender: TBaseVirtualTree;
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

end.
