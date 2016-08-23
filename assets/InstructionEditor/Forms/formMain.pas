unit formMain;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, System.UITypes,
  System.ImageList, System.Generics.Collections, Vcl.Graphics, Vcl.Controls, Vcl.Forms, Vcl.Dialogs,
  Vcl.ImgList, Vcl.StdCtrls, Vcl.ExtCtrls, dxSkinsCore, dxSkinBlue, dxSkinSeven, dxDockPanel, cxOI,
  dxSkinsdxBarPainter, cxGraphics, cxControls, cxLookAndFeels, cxLookAndFeelPainters,cxVGrid,
  dxRibbonCustomizationForm, dxRibbonSkins, cxStyles, cxEdit, cxInplaceContainer, dxSkinsForm,
  dxStatusBar, dxRibbonStatusBar, cxClasses, dxRibbon, dxBar, dxRibbonForm, cxSplitter, cxPC,
  dxBarExtItems, dxSkinsdxDockControlPainter, dxDockControl, dxSkinsdxRibbonPainter,
  dxGDIPlusClasses, VirtualTrees, untInstructionEditor;

// TODO: Add support for multi node selection and allow copy / paste / cut / delete of mutiple
//       definitions
//       http://www.delphipraxis.net/136601-virtual-treeview-multiselect-onchange-event-problem.html

// TODO: Update inspector after inspected object changed

type
  TfrmMain = class(TdxRibbonForm)
    BarManager: TdxBarManager;
    RibbonTab1: TdxRibbonTab;
    Ribbon: TdxRibbon;
    StatusBar: TdxRibbonStatusBar;
    SkinController: TdxSkinController;
    barMainManu: TdxBar;
    barEditor: TdxBar;
    lbLoadDatabase: TdxBarLargeButton;
    lbSaveDatabase: TdxBarLargeButton;
    imgIcons16: TcxImageList;
    imgIcons32: TcxImageList;
    lbCreateDefinition: TdxBarLargeButton;
    barStatusBarProgress: TdxBar;
    piStatusBarProgress: TdxBarProgressItem;
    barView: TdxBar;
    Splitter: TcxSplitter;
    bbDuplicateDefinition: TdxBarButton;
    bbDeleteDefinition: TdxBarButton;
    barGenerator: TdxBar;
    lbGenerate: TdxBarLargeButton;
    pnlInspector: TPanel;
    DockingManager: TdxDockingManager;
    imgMisc: TcxImageList;
    DockSite: TdxDockSite;
    LayoutDockSite: TdxLayoutDockSite;
    pnlPropertyInspector: TdxDockPanel;
    Inspector: TcxRTTIInspector;
    pnlPropertyInformation: TdxDockPanel;
    VertContainerDockSite: TdxVertContainerDockSite;
    lblPropertyInfo: TLabel;
    popupEditor: TdxRibbonPopupMenu;
    dxBarSeparator1: TdxBarSeparator;
    dxBarSeparator2: TdxBarSeparator;
    dxBarSeparator3: TdxBarSeparator;
    bbClipboardCopy: TdxBarButton;
    barClipboard: TdxBar;
    lbClipboardPaste: TdxBarLargeButton;
    bbClipboardCut: TdxBarButton;
    lbMnemonicFilter: TdxBarLargeButton;
    bbExpandNodes: TdxBarButton;
    bbCollapseNodes: TdxBarButton;
    barMnemonicFilter: TdxBar;
    edtMnemonicFilter: TdxBarEdit;
    bbExactMatch: TdxBarButton;
    EditorTree: TVirtualStringTree;
    imgTreeView: TcxImageList;
    dxBarSeparator4: TdxBarSeparator;
    bbExpandLeaf: TdxBarButton;
    bbCollapseLeaf: TdxBarButton;
    Button1: TButton;
    Button2: TButton;
    procedure FormCreate(Sender: TObject);
    procedure FormResize(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure lbLoadDatabaseClick(Sender: TObject);
    procedure lbSaveDatabaseClick(Sender: TObject);
    procedure EditorTreeGetText(Sender: TBaseVirtualTree; Node: PVirtualNode; Column: TColumnIndex;
      TextType: TVSTTextType; var CellText: string);
    procedure EditorTreeChange(Sender: TBaseVirtualTree; Node: PVirtualNode);
    procedure EditorTreeCompareNodes(Sender: TBaseVirtualTree; Node1, Node2: PVirtualNode;
      Column: TColumnIndex; var Result: Integer);
    procedure EditorTreeCollapsing(Sender: TBaseVirtualTree; Node: PVirtualNode;
      var Allowed: Boolean);
    procedure EditorTreePaintText(Sender: TBaseVirtualTree; const TargetCanvas: TCanvas;
      Node: PVirtualNode; Column: TColumnIndex; TextType: TVSTTextType);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure lbCreateDefinitionClick(Sender: TObject);
    procedure lbGenerateClick(Sender: TObject);
    procedure bbDeleteDefinitionClick(Sender: TObject);
    procedure InspectorItemChanged(Sender: TObject; AOldRow: TcxCustomRow; AOldCellIndex: Integer);
    procedure bbDuplicateDefinitionClick(Sender: TObject);
    procedure EditorTreeKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
    procedure bbClipboardCopyClick(Sender: TObject);
    procedure lbClipboardPasteClick(Sender: TObject);
    procedure bbExpandNodesClick(Sender: TObject);
    procedure bbCollapseNodesClick(Sender: TObject);
    procedure bbClipboardCutClick(Sender: TObject);
    procedure lbMnemonicFilterClick(Sender: TObject);
    procedure edtMnemonicFilterCurChange(Sender: TObject);
    procedure bbExactMatchClick(Sender: TObject);
    procedure EditorTreeMouseUp(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X,
      Y: Integer);
    procedure bbExpandLeafClick(Sender: TObject);
    procedure bbCollapseLeafClick(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure EditorTreeGetImageIndex(Sender: TBaseVirtualTree;
      Node: PVirtualNode; Kind: TVTImageKind; Column: TColumnIndex;
      var Ghosted: Boolean; var ImageIndex: TImageIndex);
  strict private
    FEditor: TInstructionEditor;
    FUpdating: Boolean;
    FHasUnsavedChanges: Boolean;
    FExpandedFilterProperties: TList<String>;
    FExpandedDefinitionProperties: TList<String>;
    FInspectorActiveFilterRow: String;
    FInspectorActiveDefinitionRow: String;
    FEditing: Boolean;
    FEditedNode: PVirtualNode;
  strict private
    procedure EditorWorkStart(Sender: TObject; MinWorkCount, MaxWorkCount: Integer);
    procedure EditorWork(Sender: TObject; WorkCount: Integer);
    procedure EditorWorkEnd(Sender: TObject);
    procedure EditorBeginUpdate(Sender: TObject);
    procedure EditorEndUpdate(Sender: TObject);
    procedure EditorFilterCreated(Sender: TObject; Filter: TInstructionFilter);
    procedure EditorFilterInserted(Sender: TObject; Filter: TInstructionFilter);
    procedure EditorFilterChanged(Sender: TObject; Filter: TInstructionFilter);
    procedure EditorFilterRemoved(Sender: TObject; Filter: TInstructionFilter);
    procedure EditorFilterDestroyed(Sender: TObject; Filter: TInstructionFilter);
    procedure EditorDefinitionCreated(Sender: TObject; Definition: TInstructionDefinition);
    procedure EditorDefinitionInserted(Sender: TObject; Definition: TInstructionDefinition);
    procedure EditorDefinitionChanged(Sender: TObject; Definition: TInstructionDefinition);
    procedure EditorDefinitionRemoved(Sender: TObject; Definition: TInstructionDefinition);
    procedure EditorDefinitionDestroyed(Sender: TObject; Definition: TInstructionDefinition);
  strict private
    function GetTreeNode(const Definition: TInstructionDefinition): PVirtualNode; overload;
    function GetTreeNode(const Filter: TInstructionFilter): PVirtualNode; overload;
  strict private
    procedure SetDefaultWindowPosition; inline;
    procedure LoadGUIConfiguration;
    procedure SaveGUIConfiguration;
    procedure UpdateExpandedProperties;
  strict private
    procedure UpdateControls;
    procedure UpdateStatistic;
  strict private
    procedure ClipboardPaste(Node: PVirtualNode);
    procedure ClipboardCopy(Node: PVirtualNode);
    procedure ClipboardCut(Node: PVirtualNode);
    procedure DefinitionCreate;
    procedure DefinitionDuplicate(Node: PVirtualNode);
    procedure DefinitionDelete(Node: PVirtualNode);
    procedure ExpandAllNodes(Expanded: Boolean);
    procedure ExpandLeaf(Node: PVirtualNode; Expanded: Boolean);
    procedure SetMnemonicFilter(const Filter: String; ExactMatch: Boolean);
  public
    { Public-Deklarationen }
  end;

var
  frmMain: TfrmMain;

implementation

uses
  System.IniFiles, Vcl.Clipbrd, SynCrossPlatformJSON, formCreateDefinition, formGenerator,
  untHelperClasses, untPropertyHints,

  System.Math;

{$R *.dfm}

type
  TEditorNodeType = (ntFilterTable, ntInstructionDefinition);

  PEditorNodeData = ^TEditorNodeData;
  TEditorNodeData = record
  public
    NodeType: TEditorNodeType;
    case Integer of
      0: (DataClass: TPersistent);
      1: (Filter: TInstructionFilter);
      2: (Definition: TInstructionDefinition);
  end;

{$REGION 'Code: TreeView related methods'}
function TfrmMain.GetTreeNode(const Definition: TInstructionDefinition): PVirtualNode;
begin
  // We are using the "data" property to store the corresponding node pointer
  Assert(Assigned(Definition.Data));
  Result := Definition.Data;
end;

function TfrmMain.GetTreeNode(const Filter: TInstructionFilter): PVirtualNode;
begin
  // We are using the "data" property to store the corresponding node pointer
  Assert(Assigned(Filter.Data));
  Result := Filter.Data;
end;
{$ENDREGION}

{$REGION 'Code: TreeView related operations'}
procedure TfrmMain.ClipboardCopy(Node: PVirtualNode);

procedure SaveToJSON(Filter: TInstructionFilter; JSONArray: PJSONVariantData);
var
  I: Integer;
  JSONObject: TJSONVariantData;
begin
  if (Filter.IsDefinitionContainer) then
  begin
    for I := 0 to (Filter as TDefinitionContainer).DefinitionCount - 1 do
    begin
      JSONObject.Init;
      (Filter as TDefinitionContainer).Definitions[I].SaveToJSON(@JSONObject);
      JSONArray^.AddValue(Variant(JSONObject));
    end;
  end else
  begin
    for I := 0 to Filter.Capacity - 1 do
    begin
      if (Assigned(Filter.Items[I])) then
      begin
        SaveToJSON(Filter.Items[I], JSONArray);
      end;
    end;
  end;
end;

var
  NodeData: PEditorNodeData;
  JSON,
  JSONArray,
  JSONObject: TJSONVariantData;
begin
  NodeData := EditorTree.GetNodeData(Node);
  if (Assigned(NodeData)) then
  begin
    JSONArray.Init;
    if (NodeData^.NodeType = ntInstructionDefinition) then
    begin
      JSONObject.Init;
      NodeData^.Definition.SaveToJSON(@JSONObject);
      JSONArray.AddValue(Variant(JSONObject));
    end else
    begin
      if (Application.MessageBox(
        'You are trying to copy multiple definitions to clipboard. Do you want to continue?',
        'Question', MB_ICONQUESTION or MB_YESNO) <> IdYes) then
      begin
        Exit;
      end;
      SaveToJSON(NodeData^.Filter, @JSONArray);
    end;
    JSON.Init;
    JSON.AddNameValue('definitions', Variant(JSONArray));
    Clipboard.AsText := TJSONHelper.JSONToString(@JSON);
  end;
end;

procedure TfrmMain.ClipboardCut(Node: PVirtualNode);
begin
  ClipboardCopy(Node);
  DefinitionDelete(Node);
end;

procedure TfrmMain.ClipboardPaste(Node: PVirtualNode);
var
  JSON: TJSONVariantData;
  JSONArray: PJSONVariantData;
  I: Integer;
  D: TInstructionDefinition;
begin
  JSON.Init;
  if (JSON.FromJSON(Clipboard.AsText) and (JSON.Kind = jvObject)) then
  begin
    JSONArray := JSON.Data('definitions');
    if (Assigned(JSONArray) and (JSONArray^.Kind = jvArray)) then
    begin
      if (JSONArray^.Count > 1) then
      begin
        if (Application.MessageBox(
          'You are trying to paste multiple definitions from clipboard. Do you want to continue?',
          'Question', MB_ICONQUESTION or MB_YESNO) <> IdYes) then
        begin
          Exit;
        end;
      end;
      FEditor.BeginUpdate;
      try
        for I := 0 to JSONArray^.Count - 1 do
        begin
          D := FEditor.CreateDefinition('unnamed');
          try
            D.BeginUpdate;
            try
              D.Update;
              D.LoadFromJSON(JSONVariantDataSafe(JSONArray^.Item[I], jvObject));
            finally
              D.EndUpdate;
            end;
          except
            on E: Exception do
            begin
              D.Free;
              Application.MessageBox(PChar(E.Message), 'Error', MB_ICONERROR);
            end;
          end;
        end;
      finally
        FEditor.EndUpdate;
      end;
    end;
  end;
end;

procedure TfrmMain.DefinitionCreate;
var
  frmCreateDefinition: TfrmCreateDefinition;
  D: TInstructionDefinition;
begin
  frmCreateDefinition := TfrmCreateDefinition.Create(Application);
  try
    D := FEditor.CreateDefinition('unnamed');
    D.BeginUpdate;
    try
      // Force initial position update to cause OnDefinitionInserted for new definitions with
      // unchanged (position-relevant) properties.
      D.Update;
      frmCreateDefinition.Inspector.InspectedObject := D;
      frmCreateDefinition.ShowModal;
    finally
      if (not frmCreateDefinition.Canceled) then D.EndUpdate;
    end;
    if (frmCreateDefinition.Canceled) then
    begin
      D.Free;
    end;
  finally
    frmCreateDefinition.Free;
  end;
end;

procedure TfrmMain.DefinitionDelete(Node: PVirtualNode);
var
  NextNode: PVirtualNode;
  NodeData: PEditorNodeData;
begin
  NodeData := EditorTree.GetNodeData(Node);
  if Assigned(NodeData) and (NodeData^.NodeType = ntInstructionDefinition) then
  begin
    NextNode := EditorTree.GetNextSibling(Node);
    if (not Assigned(NextNode)) then
    begin
      NextNode := EditorTree.GetPreviousSibling(Node);
    end;
    NodeData^.Definition.Free;
    if (Assigned(NextNode)) then
    begin
      EditorTree.FocusedNode := NextNode;
      EditorTree.Selected[NextNode] := true;
    end;
  end;
end;

procedure TfrmMain.DefinitionDuplicate(Node: PVirtualNode);
var
  frmCreateDefinition: TfrmCreateDefinition;
  D: TInstructionDefinition;
  NodeData: PEditorNodeData;
begin
  NodeData := EditorTree.GetNodeData(Node);
  if (Assigned(NodeData) and (NodeData^.NodeType = ntInstructionDefinition)) then
  begin
    frmCreateDefinition := TfrmCreateDefinition.Create(Application);
    try
      D := FEditor.CreateDefinition('unnamed');
      D.BeginUpdate;
      try
        // Force initial position update to cause OnDefinitionInserted for new definitions with
        // unchanged (position-relevant) properties.
        D.Update;
        D.Assign(NodeData^.Definition);
        frmCreateDefinition.Inspector.InspectedObject := D;
        frmCreateDefinition.ShowModal;
      finally
        if (not frmCreateDefinition.Canceled) then D.EndUpdate;
      end;
      if (frmCreateDefinition.Canceled) then
      begin
        D.Free;
      end;
    finally
      frmCreateDefinition.Free;
    end;
  end;
end;

procedure TfrmMain.ExpandAllNodes(Expanded: Boolean);
var
  Node: PVirtualNode;
  NodeData: PEditorNodeData;
begin
  EditorTree.BeginUpdate;
  try
    Node := EditorTree.GetFirst;
    while (Assigned(Node)) do
    begin
      NodeData := EditorTree.GetNodeData(Node);
      if (Assigned(NodeData) and (NodeData^.NodeType = ntFilterTable) and
        (Assigned(NodeData^.Filter)) and
        (not (iffIsRootTable in NodeData^.Filter.FilterFlags))) then
      begin
        EditorTree.Expanded[Node] := Expanded;
      end;
      Node := EditorTree.GetNext(Node);
    end;
  finally
    EditorTree.EndUpdate;
  end;
end;

procedure TfrmMain.ExpandLeaf(Node: PVirtualNode; Expanded: Boolean);
begin
  // TODO:
end;
{$ENDREGION}

{$REGION 'Events: Form'}
procedure TfrmMain.FormCloseQuery(Sender: TObject; var CanClose: Boolean);
var
  ID: Integer;
begin
  CanClose := true;
  if (FHasUnsavedChanges) then
  begin
    ID := Application.MessageBox('The current database have unsaved changes. Do you'
      + ' really want to exit?', 'Question', MB_ICONWARNING or MB_YESNO or MB_DEFBUTTON2);
    CanClose := (ID = IdYes);
  end;
end;

procedure TfrmMain.FormCreate(Sender: TObject);
begin
  EditorTree.NodeDataSize := SizeOf(TEditorNodeData);

  FExpandedFilterProperties := TList<String>.Create;
  FExpandedDefinitionProperties := TList<String>.Create;

  SetDefaultWindowPosition;
  LoadGUIConfiguration;

  StatusBar.Panels[1].Visible := false;

  FEditor := TInstructionEditor.Create;
  FEditor.OnWorkStart := EditorWorkStart;
  FEditor.OnWork := EditorWork;
  FEditor.OnWorkEnd := EditorWorkEnd;
  FEditor.OnBeginUpdate := EditorBeginUpdate;
  FEditor.OnEndUpdate := EditorEndUpdate;
  FEditor.OnFilterCreated := EditorFilterCreated;
  FEditor.OnFilterInserted := EditorFilterInserted;
  FEditor.OnFilterChanged := EditorFilterChanged;
  FEditor.OnFilterRemoved := EditorFilterRemoved;
  FEditor.OnFilterDestroyed := EditorFilterDestroyed;
  FEditor.OnDefinitionCreated := EditorDefinitionCreated;
  FEditor.OnDefinitionInserted := EditorDefinitionInserted;
  FEditor.OnDefinitionChanged := EditorDefinitionChanged;
  FEditor.OnDefinitionRemoved := EditorDefinitionRemoved;
  FEditor.OnDefinitionDestroyed := EditorDefinitionDestroyed;

  FEditing := false;
  FEditor.Reset;
  FEditing := true;
  ExpandAllNodes(true);
end;

procedure TfrmMain.FormDestroy(Sender: TObject);
begin
  FEditing := false;
  SaveGUIConfiguration;
  ExpandAllNodes(false);
  if (Assigned(FEditor)) then
  begin
    FEditor.Free;
  end;
  if (Assigned(FExpandedFilterProperties)) then
  begin
    FExpandedFilterProperties.Free;
  end;
  if (Assigned(FExpandedDefinitionProperties)) then
  begin
    FExpandedDefinitionProperties.Free;
  end;
end;

procedure TfrmMain.FormResize(Sender: TObject);
begin
  piStatusBarProgress.Width := barStatusBarProgress.Control.ClientWidth;
end;
{$ENDREGION}

{$REGION 'Events: InstructionEditor'}
procedure TfrmMain.EditorBeginUpdate(Sender: TObject);
begin
  EditorTree.BeginUpdate;
  FUpdating := true;
end;

procedure TfrmMain.EditorDefinitionChanged(Sender: TObject; Definition: TInstructionDefinition);
begin
  EditorTree.RepaintNode(GetTreeNode(Definition));
  UpdateStatistic;
  if (FEditing) then
  begin
    if (not (csDestroying in ComponentState)) and (lbMnemonicFilter.Down) then
    begin
      SetMnemonicFilter(edtMnemonicFilter.Text, bbExactMatch.Down);
    end;
    FHasUnsavedChanges := true;
    UpdateControls;
  end;
end;

procedure TfrmMain.EditorDefinitionCreated(Sender: TObject; Definition: TInstructionDefinition);
var
  Node: PVirtualNode;
  NodeData: PEditorNodeData;
begin
  Node := EditorTree.AddChild(nil);
  Definition.Data := Node;
  EditorTree.IsVisible[Node] := false;
  NodeData := EditorTree.GetNodeData(Node);
  NodeData^.NodeType := ntInstructionDefinition;
  NodeData^.Definition := Definition;
  UpdateStatistic;
end;

procedure TfrmMain.EditorDefinitionDestroyed(Sender: TObject; Definition: TInstructionDefinition);
begin
  EditorTree.DeleteNode(GetTreeNode(Definition));
  if (Inspector.InspectedObject = Definition) then
  begin
    Inspector.InspectedObject := nil;
  end;
  UpdateStatistic;
end;

procedure TfrmMain.EditorDefinitionInserted(Sender: TObject; Definition: TInstructionDefinition);
var
  Node: PVirtualNode;
begin
  Assert(Assigned(Definition.Parent));
  Node := GetTreeNode(Definition);
  EditorTree.IsVisible[Node] := true;
  EditorTree.MoveTo(Node, GetTreeNode(Definition.Parent), amAddChildLast, false);
  if (FEditing) then
  begin
    FEditedNode := Node;
    FHasUnsavedChanges := true;
    UpdateControls;
  end;
end;

procedure TfrmMain.EditorDefinitionRemoved(Sender: TObject; Definition: TInstructionDefinition);
var
  Node: PVirtualNode;
begin
  Node := GetTreeNode(Definition);
  EditorTree.IsVisible[Node] := false;
  EditorTree.MoveTo(Node, nil, amInsertAfter, false);
  if (FEditing) then
  begin
    if (EditorTree.FocusedNode = Node) then
    begin
      EditorTree.FocusedNode := nil;
      EditorTree.Selected[Node] := false;
    end;
    FHasUnsavedChanges := true;
    UpdateControls;
  end;
end;

procedure TfrmMain.EditorEndUpdate(Sender: TObject);
begin
  EditorTree.EndUpdate;
  FUpdating := false;
  if (FEditing) and Assigned(FEditedNode) then
  begin
    EditorTree.FocusedNode := FEditedNode;
    EditorTree.Selected[FEditedNode] := true;
    EditorTree.ScrollIntoView(FEditedNode, true);
    FEditedNode := nil;
  end;
  UpdateStatistic;
end;

procedure TfrmMain.EditorFilterChanged(Sender: TObject; Filter: TInstructionFilter);
begin
  EditorTree.RepaintNode(GetTreeNode(Filter));
end;

procedure TfrmMain.EditorFilterCreated(Sender: TObject; Filter: TInstructionFilter);
var
  Node: PVirtualNode;
  NodeData: PEditorNodeData;
begin
  Node := EditorTree.AddChild(nil);
  Filter.Data := Node;
  if (not (iffIsRootTable in Filter.FilterFlags)) then
  begin
    EditorTree.IsVisible[Node] := false;
  end;
  NodeData := EditorTree.GetNodeData(Node);
  NodeData^.NodeType := ntFilterTable;
  NodeData^.Filter := Filter;
  UpdateStatistic;
end;

procedure TfrmMain.EditorFilterDestroyed(Sender: TObject; Filter: TInstructionFilter);
begin
  EditorTree.DeleteNode(GetTreeNode(Filter));
  if (Inspector.InspectedObject = Filter) then
  begin
    Inspector.InspectedObject := nil;
  end;
  UpdateStatistic;
end;

procedure TfrmMain.EditorFilterInserted(Sender: TObject; Filter: TInstructionFilter);
var
  Node, ParentNode: PVirtualNode;
begin
  Assert(Assigned(Filter.Parent));
  Node := GetTreeNode(Filter);
  ParentNode := GetTreeNode(Filter.Parent);
  EditorTree.MoveTo(Node, ParentNode, amAddChildLast, false);
  EditorTree.IsVisible[Node] := true;
  // Expand root table after first filter insertion
  if (iffIsRootTable in Filter.Parent.FilterFlags) and (Filter.Parent.ItemCount = 1) then
  begin
    EditorTree.Expanded[ParentNode] := true;
  end;
end;

procedure TfrmMain.EditorFilterRemoved(Sender: TObject; Filter: TInstructionFilter);
var
  Node: PVirtualNode;
begin
  Node := GetTreeNode(Filter);
  EditorTree.IsVisible[Node] := false;
  EditorTree.MoveTo(Node, nil, amInsertAfter, false);
  if (FEditing) then
  begin
    if (EditorTree.FocusedNode = Node) then
    begin
      EditorTree.FocusedNode := nil;
      EditorTree.Selected[Node] := false;
    end;
    UpdateControls;
  end;
end;

procedure TfrmMain.EditorWork(Sender: TObject; WorkCount: Integer);
begin
  piStatusBarProgress.Position := WorkCount;
  if ((WorkCount mod piStatusBarProgress.Tag) = 0) then
  begin
    Application.ProcessMessages;
  end;
end;

procedure TfrmMain.EditorWorkEnd(Sender: TObject);
begin
  piStatusBarProgress.Visible := ivNever;
end;

procedure TfrmMain.EditorWorkStart(Sender: TObject; MinWorkCount, MaxWorkCount: Integer);
begin
  piStatusBarProgress.Min := MinWorkCount;
  piStatusBarProgress.Max := MaxWorkCount;
  piStatusBarProgress.Tag := Round((MaxWorkCount - MinWorkCount) / 100) + 1;
  piStatusBarProgress.Position := 0;
  piStatusBarProgress.Visible := ivAlways;
end;
{$ENDREGION}

{$REGION 'Events: TreeView'}
procedure TfrmMain.EditorTreeChange(Sender: TBaseVirtualTree; Node: PVirtualNode);
var
  NodeData: PEditorNodeData;
  I: Integer;
begin
  UpdateExpandedProperties;
  Inspector.BeginUpdate;
  try
    if (Assigned(Inspector.FocusedRow)) then
    begin
      if (Inspector.InspectedObject is TInstructionFilter) then
      begin
        FInspectorActiveFilterRow :=
          (Inspector.FocusedRow as TcxPropertyRow).PropertyEditor.GetName;
      end else if (Inspector.InspectedObject is TInstructionDefinition) then
      begin
        FInspectorActiveDefinitionRow :=
          (Inspector.FocusedRow as TcxPropertyRow).PropertyEditor.GetName;
      end;
    end;
    Inspector.InspectedObject := nil;
    NodeData := Sender.GetNodeData(Node);
    if Assigned(NodeData) then
    begin
      Inspector.InspectedObject := NodeData^.DataClass;
      for I := 0 to Inspector.Rows.Count - 1 do
      begin
        if ((NodeData^.NodeType = ntFilterTable) and FExpandedFilterProperties.Contains(
          (Inspector.Rows[I] as TcxPropertyRow).PropertyEditor.GetName)) or
          ((NodeData^.NodeType = ntInstructionDefinition) and
          FExpandedDefinitionProperties.Contains(
          (Inspector.Rows[I] as TcxPropertyRow).PropertyEditor.GetName)) then
        begin
          Inspector.Rows[I].Expanded := true;
        end;
        if ((NodeData^.NodeType = ntFilterTable) and (FInspectorActiveFilterRow =
          (Inspector.Rows[I] as TcxPropertyRow).PropertyEditor.GetName)) or
          ((NodeData^.NodeType = ntInstructionDefinition) and
          (FInspectorActiveDefinitionRow =
          (Inspector.Rows[I] as TcxPropertyRow).PropertyEditor.GetName)) then
        begin
          Inspector.FocusedRow := Inspector.Rows[I];
        end;
      end;
    end;
  finally
    Inspector.EndUpdate;
  end;
  UpdateControls;
end;

procedure TfrmMain.EditorTreeCollapsing(Sender: TBaseVirtualTree; Node: PVirtualNode;
  var Allowed: Boolean);
var
  NodeData: PEditorNodeData;
begin
  NodeData := Sender.GetNodeData(Node);
  if (Assigned(NodeData) and (NodeData^.NodeType = ntFilterTable) and
    Assigned(NodeData^.Filter) and (iffIsRootTable in NodeData^.Filter.FilterFlags)) then
  begin
    Allowed := false;
  end;
end;

procedure TfrmMain.EditorTreeCompareNodes(Sender: TBaseVirtualTree; Node1, Node2: PVirtualNode;
  Column: TColumnIndex; var Result: Integer);
var
  NodeDataA,
  NodeDataB: PEditorNodeData;
begin
  NodeDataA := Sender.GetNodeData(Node1);
  NodeDataB := Sender.GetNodeData(Node2);
  if (NodeDataA^.NodeType <> NodeDataB^.NodeType) then Exit;
  if (Assigned(NodeDataA) and Assigned(NodeDataB) and
    Assigned(NodeDataA^.DataClass) and Assigned(NodeDataB^.DataClass)) then
  begin
    case NodeDataA^.NodeType of
      ntFilterTable:
        begin
          Assert(NodeDataB^.NodeType = ntFilterTable);
          if (Assigned(NodeDataA^.Filter.Parent)) then
          begin
            Assert(Assigned(NodeDataB^.Filter.Parent));
            Assert(NodeDataA^.Filter.Parent = NodeDataB^.Filter.Parent);
            Result := NodeDataA^.Filter.Parent.IndexOf(NodeDataA^.Filter) -
              NodeDataB^.Filter.Parent.IndexOf(NodeDataB^.Filter);
          end;
        end;
      ntInstructionDefinition:
        begin
          Assert(NodeDataB^.NodeType = ntInstructionDefinition);
          Result := CompareStr(NodeDataA^.Definition.Mnemonic, NodeDataB^.Definition.Mnemonic);
        end;
    end;
  end;
end;

procedure TfrmMain.EditorTreeGetImageIndex(Sender: TBaseVirtualTree;
  Node: PVirtualNode; Kind: TVTImageKind; Column: TColumnIndex;
  var Ghosted: Boolean; var ImageIndex: TImageIndex);
var
  NodeData: PEditorNodeData;
begin
  if (Column <> 0) or (Kind = ikOverlay) then
  begin
    Exit;
  end;
  NodeData := Sender.GetNodeData(Node);
  if Assigned(NodeData) then
  begin
    case NodeData^.NodeType of
      ntFilterTable:
        begin
          ImageIndex := 0;
          if (NodeData^.Filter is TDefinitionContainer) then
          begin
            ImageIndex := 1;
          end;
        end;
      ntInstructionDefinition:
        begin
          ImageIndex := 2;
        end;
    end;
  end;
end;

procedure TfrmMain.EditorTreeGetText(Sender: TBaseVirtualTree; Node: PVirtualNode;
  Column: TColumnIndex; TextType: TVSTTextType; var CellText: string);
var
  NodeData: PEditorNodeData;
  S: String;
begin
  CellText := '';
  NodeData := Sender.GetNodeData(Node);
  if (Assigned(NodeData) and Assigned(NodeData^.DataClass)) then
  begin
    case (NodeData^.NodeType) of
      ntFilterTable:
        begin
          if (TextType <> ttNormal) and (not (Column in [0])) then Exit;
          case Column of
            0:
              begin
                case TextType of
                  ttNormal:
                    begin
                      if (not Assigned(NodeData^.Filter.Parent)) then
                      begin
                        CellText := 'Root';
                      end else
                      begin
                        CellText := IntToHex(NodeData^.Filter.Parent.IndexOf(NodeData^.Filter), 2);
                      end;
                    end;
                  ttStatic:
                    begin
                      if (Assigned(NodeData^.Filter.Parent)) then
                      begin
                        S := NodeData^.Filter.Parent.GetItemDescription(
                          NodeData^.Filter.Parent.IndexOf(NodeData^.Filter));
                        if (S <> '') then
                        begin
                          CellText := '(' + S + ')';
                        end;
                      end;
                    end;
                end;
              end;
          end;
        end;
      ntInstructionDefinition:
        begin
          if (TextType <> ttNormal) and (not (Column in [0, 1])) then Exit;
          case Column of
            0:
              begin
                case TextType of
                  ttNormal: CellText := IntToHex(Node.Index, 2);
                  ttStatic: CellText := 'Definition';
                end;
              end;
            1:
              begin
                case TextType of
                  ttNormal:
                    begin
                      CellText := IntToHex(NodeData^.Definition.Opcode, 2);
                    end;
                  ttStatic:
                    begin
                      CellText := ''; // TODO:
                    end
                end;
              end;
            2: CellText := NodeData^.Definition.Mnemonic;
            3: CellText := NodeData^.Definition.Operands.OperandA.GetDescription(true);
            4: CellText := NodeData^.Definition.Operands.OperandB.GetDescription(true);
            5: CellText := NodeData^.Definition.Operands.OperandC.GetDescription(true);
            6: CellText := NodeData^.Definition.Operands.OperandD.GetDescription(true);
            7: CellText := NodeData^.Definition.Comment;
          end;
        end;
    end;
  end;
end;

procedure TfrmMain.EditorTreeKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);

procedure CopyOperands;
var
  NodeData: PEditorNodeData;
  I: Integer;
  S: String;
  O: TInstructionOperand;
begin
  NodeData := EditorTree.GetNodeData(EditorTree.FocusedNode);
  if (Assigned(NodeData) and (NodeData^.NodeType = ntInstructionDefinition)) then
  begin
    S := '';
    for I := 0 to 3 do
    begin
      O := nil;
      case I of
        0: O := NodeData^.Definition.Operands.OperandA;
        1: O := NodeData^.Definition.Operands.OperandB;
        2: O := NodeData^.Definition.Operands.OperandC;
        3: O := NodeData^.Definition.Operands.OperandD;
      end;
      S := S + IntToStr(Integer(O.OperandType)) + ',' + IntToStr(Integer(O.Encoding)) + ',' +
        IntToStr(Integer(O.AccessMode)) + ',';
    end;
    Clipboard.AsText := S;
  end;
end;

procedure PasteOperands;
var
  NodeData: PEditorNodeData;
  A: TArray<String>;
  I, J: Integer;
  O: TInstructionOperand;
begin
  NodeData := EditorTree.GetNodeData(EditorTree.FocusedNode);
  if (Assigned(NodeData) and (NodeData^.NodeType = ntInstructionDefinition)) then
  begin
    A := Clipboard.AsText.Split([',']);
    if (Length(A) >= 12) then
    begin
      I := 0;
      J := 0;
      while (J < 4) do
      begin
        O := nil;
        case J of
          0: O := NodeData^.Definition.Operands.OperandA;
          1: O := NodeData^.Definition.Operands.OperandB;
          2: O := NodeData^.Definition.Operands.OperandC;
          3: O := NodeData^.Definition.Operands.OperandD;
        end;
        O.OperandType := TOperandType(StrToInt(A[I]));
        O.Encoding := TOperandEncoding(StrToInt(A[I + 1]));
        O.AccessMode := TOperandAccessMode(StrToInt(A[I + 2]));
        Inc(I, 3);
        Inc(J);
      end;
    end;
  end;
end;

begin
  if (ssCtrl in Shift) then
  begin
    case Key of
      Ord('V'):
        lbClipboardPaste.Click;
      Ord('C'):
        bbClipboardCopy.Click;
      Ord('X'):
        bbClipboardCut.Click;
      Ord('F'):
        lbMnemonicFilter.Click;
      Ord('E'):
        CopyOperands;
      Ord('R'):
        PasteOperands;
    end;
  end else if (Shift = []) then
  begin
    case Key of
      VK_DELETE:
        bbDeleteDefinition.Click;
    end;
  end;
end;

procedure TfrmMain.EditorTreeMouseUp(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X,
  Y: Integer);
begin
  if (Button = mbRight) then
  begin
    popupEditor.PopupFromCursorPos;
  end;
end;

procedure TfrmMain.EditorTreePaintText(Sender: TBaseVirtualTree; const TargetCanvas: TCanvas;
  Node: PVirtualNode; Column: TColumnIndex; TextType: TVSTTextType);
var
  NodeData: PEditorNodeData;
begin
  NodeData := Sender.GetNodeData(Node);
  if (Assigned(NodeData) and Assigned(NodeData^.DataClass)) then
  begin
    case NodeData^.NodeType of
      ntFilterTable:
        begin
          if (NodeData^.Filter.HasConflicts) then
          begin
            TargetCanvas.Font.Color := clRed;
            Exit;
          end;
        end;
      ntInstructionDefinition:
        begin
          if (NodeData^.Definition.HasConflicts) then
          begin
            TargetCanvas.Font.Color := clRed;
            Exit;
          end;
        end;
    end;
  end;
  case Column of
    0:
      begin
        case TextType of
          ttNormal: ;
          ttStatic: TargetCanvas.Font.Color := clGray;
        end;
      end;
    1:
      begin
        case TextType of
          ttNormal: ;
          ttStatic: TargetCanvas.Font.Color := clGray;
        end;
      end;
  end;
end;
{$ENDREGION}

procedure TfrmMain.bbClipboardCopyClick(Sender: TObject);
begin
  ClipboardCopy(EditorTree.FocusedNode);
end;

procedure TfrmMain.bbClipboardCutClick(Sender: TObject);
begin
  ClipboardCut(EditorTree.FocusedNode);
end;

procedure TfrmMain.bbDuplicateDefinitionClick(Sender: TObject);
begin
  DefinitionDuplicate(EditorTree.FocusedNode);
end;

procedure TfrmMain.bbExactMatchClick(Sender: TObject);
begin
  SetMnemonicFilter(edtMnemonicFilter.Text, bbExactMatch.Down);
end;

procedure TfrmMain.bbExpandLeafClick(Sender: TObject);
begin
  ExpandLeaf(EditorTree.FocusedNode, true);
end;

procedure TfrmMain.bbExpandNodesClick(Sender: TObject);
begin
  ExpandAllNodes(true);
end;

procedure TfrmMain.Button1Click(Sender: TObject);

procedure DeleteDuplicates(T: TInstructionFilter);
var
  L: TList<TInstructionDefinition>;
  D: TInstructionDefinition;
  I, J: Integer;
  B: Boolean;
begin
  if (T is TDefinitionContainer) then
  begin
    L := TList<TInstructionDefinition>.Create;
    try
      for I := (T as TDefinitionContainer).DefinitionCount - 1 downto 0 do
      begin
        D := (T as TDefinitionContainer).Definitions[I];
        B := true;
        for J := 0 to L.Count - 1 do
        begin
          if ((D.Mnemonic = L[J].Mnemonic) and D.Operands.Equals(L[J].Operands) and
            D.CPUID.Equals(L[J].CPUID) and (D.EVEXCD8Scale = L[J].EVEXCD8Scale)) then
          begin
            L[J].Flags := L[J].Flags + D.Flags;
            D.Free;
            B := false;
            Break;
          end;
        end;
        if (B) then L.Add(D);
      end;
    finally
      L.Free;
    end;
  end else
  begin
    for I := 0 to T.Capacity - 1 do
    begin
      if Assigned(T.Items[I]) then
      begin
        DeleteDuplicates(T.Items[I]);
      end;
    end;
  end;
end;

var
  I, J, K, RegCount, MemIndex: Integer;
  S: String;
  A: TArray<String>;
  D: TInstructionDefinition;
  O: TInstructionOperand;
begin
  FEditor.BeginUpdate;

  for I := 0 to FEditor.DefinitionCount - 1 do
  begin
    D := FEditor.Definitions[I];
    if (D.Encoding <> ieEVEX) then Continue;
    S := D.Comment;
    J := 1;
    while (J < Length(S)) and (S[J] <> ' ') do Inc(J);
    Delete(S, 1, J);
    A := S.Split([',']);
    for J := Low(A) to High(A) do
    begin
      A[J] := Trim(A[J]);
    end;
    S := A[High(A)];
    J := 1;
    while (J < Length(S)) and (S[J] <> ' ') do Inc(J);
    Delete(S, J, Length(S));
    A[High(A)] := S;
    if (A[High(A)][1] = '(') then SetLength(A, Length(A) - 1);

    RegCount := 0;
    MemIndex := -1;
    D.BeginUpdate;
    for J := Low(A) to High(A) do
    begin
      O := nil;
      case J of
        0: O := D.Operands.OperandA;
        1: O := D.Operands.OperandB;
        2: O := D.Operands.OperandC;
        3: O := D.Operands.OperandD;
      end;

      if (Pos('{1to', A[J]) > 0) then D.Flags := D.Flags + [ifHasEVEXBC];
      if (Pos('{sae}', A[J]) > 0) then D.Flags := D.Flags + [ifHasEVEXSAE];

      if (Pos('VK1', A[J]) > 0) then O.OperandType := optMSKR;
      if (Pos('VK2', A[J]) > 0) then O.OperandType := optMSKR;
      if (Pos('VK4', A[J]) > 0) then O.OperandType := optMSKR;
      if (Pos('VK8', A[J]) > 0) then O.OperandType := optMSKR;
      if (Pos('VK16', A[J]) > 0) then O.OperandType := optMSKR;
      if (Pos('VK32', A[J]) > 0) then O.OperandType := optMSKR;
      if (Pos('VK64', A[J]) > 0) then O.OperandType := optMSKR;

      if (Pos('GR8', A[J]) > 0) then O.OperandType := optGPR8;
      if (Pos('GR16', A[J]) > 0) then O.OperandType := optGPR16;
      if (Pos('GR32', A[J]) > 0) then O.OperandType := optGPR32;
      if (Pos('GR64', A[J]) > 0) then O.OperandType := optGPR64;
      if (Pos('8mem', A[J]) > 0) then O.OperandType := optMem8;
      if (Pos('16mem', A[J]) > 0) then O.OperandType := optMem16;
      if (Pos('32mem', A[J]) > 0) then
      begin
        if (Pos('{1to2}', A[J]) > 0) then O.OperandType := optMem32Bcst2 else
        if (Pos('{1to4}', A[J]) > 0) then O.OperandType := optMem32Bcst4 else
        if (Pos('{1to8}', A[J]) > 0) then O.OperandType := optMem32Bcst8 else
        if (Pos('{1to16}', A[J]) > 0) then O.OperandType := optMem32Bcst16 else
        O.OperandType := optMem32;
      end;
      if (Pos('64mem', A[J]) > 0) then
      begin
        if (Pos('{1to2}', A[J]) > 0) then O.OperandType := optMem64Bcst2 else
        if (Pos('{1to4}', A[J]) > 0) then O.OperandType := optMem64Bcst4 else
        if (Pos('{1to8}', A[J]) > 0) then O.OperandType := optMem64Bcst8 else
        if (Pos('{1to16}', A[J]) > 0) then O.OperandType := optMem64Bcst16 else
        O.OperandType := optMem64;
      end;

      if (Pos('VR128', A[J]) > 0) then O.OperandType := optVR128;
      if (Pos('VR256', A[J]) > 0) then O.OperandType := optVR256;
      if (Pos('VR512', A[J]) > 0) then O.OperandType := optVR512;
      if (Pos('128mem', A[J]) > 0) then O.OperandType := optMem128;
      if (Pos('256mem', A[J]) > 0) then O.OperandType := optMem256;
      if (Pos('512mem', A[J]) > 0) then O.OperandType := optMem512;

      if (Pos('vx32', A[J]) > 0) then O.Encoding := opeNone;
      if (Pos('vx64', A[J]) > 0) then O.Encoding := opeNone;
      if (Pos('vx128', A[J]) > 0) then O.Encoding := opeNone;
      if (Pos('vx256', A[J]) > 0) then O.Encoding := opeNone;
      if (Pos('vx512', A[J]) > 0) then O.Encoding := opeNone;
      if (Pos('vy32', A[J]) > 0) then O.Encoding := opeNone;
      if (Pos('vy64', A[J]) > 0) then O.Encoding := opeNone;
      if (Pos('vy128', A[J]) > 0) then O.Encoding := opeNone;
      if (Pos('vy256', A[J]) > 0) then O.Encoding := opeNone;
      if (Pos('vy512', A[J]) > 0) then O.Encoding := opeNone;
      if (Pos('vz32', A[J]) > 0) then O.Encoding := opeNone;
      if (Pos('vz64', A[J]) > 0) then O.Encoding := opeNone;
      if (Pos('vz128', A[J]) > 0) then O.Encoding := opeNone;
      if (Pos('vz256', A[J]) > 0) then O.Encoding := opeNone;
      if (Pos('vz512', A[J]) > 0) then O.Encoding := opeNone;

      if (Pos('imm8', A[J]) > 0) then O.OperandType := optImm8;
      if (Pos('imm8u', A[J]) > 0) then O.OperandType := optImm8U;
      if (Pos('u8imm', A[J]) > 0) then O.OperandType := optImm8U;

      if (O.Encoding = opeModrmRm) then
      begin
        MemIndex := J;
        if (D.EVEXCD8Scale <> 0) then
        begin
          case D.EvexCD8Scale of
            1:  O.Encoding := opeModrmRmCD1;
            2:  O.Encoding := opeModrmRmCD2;
            4:  O.Encoding := opeModrmRmCD4;
            8:  O.Encoding := opeModrmRmCD8;
            16: O.Encoding := opeModrmRmCD16;
            32: O.Encoding := opeModrmRmCD32;
            64: O.Encoding := opeModrmRmCD64;
          end;
        end;
      end;

      if (O.Encoding = opeModrmReg) then Inc(RegCount);
    end;
    D.Operands.OperandA.AccessMode := opaWrite;
    if (RegCount = 3) or ((RegCount = 2) and (MemIndex > -1) and (MemIndex <> 1)) then
    begin
      D.Operands.OperandB.Encoding := opeVexVVVV;
    end;
    D.EndUpdate;

  end;
  DeleteDuplicates(FEditor.RootTable.Items[$62]);
  FEditor.EndUpdate;
end;

procedure TfrmMain.Button2Click(Sender: TObject);

function BitsNeeded(N: Integer): Integer;
begin
  Result := Floor(log2(n) + 1);
end;

var
  Mnemonics: TDictionary<String, Boolean>;
  Node: PVirtualNode;
  NodeData: PEditorNodeData;
  LOPS: TList<TPair<TInstructionOperands, Integer>>;
  LCPUID: TList<TPair<TCPUIDFeatureFlagSet, Integer>>;
  LEFLAGS: TList<TPair<TX86Flags, Integer>>;
  LREGS: TList<TPair<TX86RegisterSet, Integer>>;
  I, J, Bits: Integer;
  B: Boolean;
  POPS: TPair<TInstructionOperands, Integer>;
  PCPUID: TPair<TCPUIDFeatureFlagSet, Integer>;
  PEFLAGS: TPair<TX86Flags, Integer>;
  PREGS: TPair<TX86RegisterSet, Integer>;
begin
  Bits := 4; // EVEX Info

  Mnemonics := TDictionary<String, Boolean>.Create;
  try
    Node := EditorTree.GetFirst;
    while Assigned(Node) do
    begin
      NodeData := EditorTree.GetNodeData(Node);
      if (NodeData^.NodeType = ntInstructionDefinition) then
      begin
        if (not Mnemonics.ContainsKey(NodeData^.Definition.Mnemonic)) then
        begin
          Mnemonics.Add(NodeData^.Definition.Mnemonic, true);
        end;
      end;
      Node := EditorTree.GetNext(Node);
    end;
    ShowMessage('Mnemonics: ' + IntToStr(Mnemonics.Count) + ' (' + IntToStr(BitsNeeded(Mnemonics.Count)) + ' bit)');
    Inc(Bits, BitsNeeded(Mnemonics.Count));
  finally
    Mnemonics.Free;
  end;

  LOPS := TList<TPair<TInstructionOperands, Integer>>.Create;
  for I := 0 to FEditor.DefinitionCount - 1 do
  begin
    B := false;
    for J := 0 to LOPS.Count - 1 do
    begin
      if (LOPS[J].Key.Equals(FEditor.Definitions[I].Operands)) then
      begin
        POPS := LOPS[J];
        Inc(POPS.Value);
        LOPS[J] := POPS;
        B := true;
        Break;
      end;
    end;
    if (not B) then
    begin
      POPS.Key := FEditor.Definitions[I].Operands;
      POPS.Value := 1;
      LOPS.Add(POPS);
    end;
  end;
  ShowMessage('OPS: ' + IntToStr(LOPS.Count) + ' (' + IntToStr(BitsNeeded(LOPS.Count)) + ' bit)');
  Inc(Bits, BitsNeeded(LOPS.Count));
  LOPS.Free;

  LCPUID := TList<TPair<TCPUIDFeatureFlagSet, Integer>>.Create;
  for I := 0 to FEditor.DefinitionCount - 1 do
  begin
    B := false;
    for J := 0 to LOPS.Count - 1 do
    begin
      if (LCPUID[J].Key = FEditor.Definitions[I].CPUID.FeatureFlags) then
      begin
        PCPUID := LCPUID[J];
        Inc(PCPUID.Value);
        LCPUID[J] := PCPUID;
        B := true;
        Break;
      end;
    end;
    if (not B) then
    begin
      PCPUID.Key := FEditor.Definitions[I].CPUID.FeatureFlags;
      PCPUID.Value := 1;
      LCPUID.Add(PCPUID);
    end;
  end;
  ShowMessage('CPUID: ' + IntToStr(LCPUID.Count) + ' (' + IntToStr(BitsNeeded(LCPUID.Count)) + ' bit)');
  Inc(Bits, BitsNeeded(LCPUID.Count));
  LCPUID.Free;

  LEFLAGS := TList<TPair<TX86Flags, Integer>>.Create;
  for I := 0 to FEditor.DefinitionCount - 1 do
  begin
    B := false;
    for J := 0 to LOPS.Count - 1 do
    begin
      if (LEFLAGS[J].Key.Equals(FEditor.Definitions[I].X86Flags)) then
      begin
        PEFLAGS := LEFLAGS[J];
        Inc(PEFLAGS.Value);
        LEFLAGS[J] := PEFLAGS;
        B := true;
        Break;
      end;
    end;
    if (not B) then
    begin
      PEFLAGS.Key := FEditor.Definitions[I].X86Flags;
      PEFLAGS.Value := 1;
      LEFLAGS.Add(PEFLAGS);
    end;
  end;
  ShowMessage('EFLAGS: ' + IntToStr(LEFLAGS.Count) + ' (' + IntToStr(BitsNeeded(LEFLAGS.Count)) + ' bit)');
  Inc(Bits, BitsNeeded(LEFLAGS.Count));
  LEFLAGS.Free;

  LREGS := TList<TPair<TX86RegisterSet, Integer>>.Create;
  for I := 0 to FEditor.DefinitionCount - 1 do
  begin
    B := false;
    for J := 0 to LOPS.Count - 1 do
    begin
      if (LREGS[J].Key = FEditor.Definitions[I].ImplicitRead.Registers) then
      begin
        PREGS := LREGS[J];
        Inc(PREGS.Value);
        LREGS[J] := PREGS;
        B := true;
        Break;
      end;
    end;
    if (not B) then
    begin
      PREGS.Key := FEditor.Definitions[I].ImplicitRead.Registers;
      PREGS.Value := 1;
      LREGS.Add(PREGS);
    end;
    B := false;
    for J := 0 to LOPS.Count - 1 do
    begin
      if (LREGS[J].Key = FEditor.Definitions[I].ImplicitWrite.Registers) then
      begin
        PREGS := LREGS[J];
        Inc(PREGS.Value);
        LREGS[J] := PREGS;
        B := true;
        Break;
      end;
    end;
    if (not B) then
    begin
      PREGS.Key := FEditor.Definitions[I].ImplicitWrite.Registers;
      PREGS.Value := 1;
      LREGS.Add(PREGS);
    end;
  end;
  ShowMessage('REGS: ' + IntToStr(LREGS.Count) + ' (' + IntToStr(BitsNeeded(LREGS.Count)) + ' bit)');
  Inc(Bits, BitsNeeded(LREGS.Count));
  LEFLAGS.Free;

  ShowMessage('BytesNeeded: ' + IntToStr(Ceil(Bits / 8)) + ' (' + IntToStr(Bits) + ' bits)');
end;

procedure TfrmMain.bbCollapseLeafClick(Sender: TObject);
begin
  ExpandLeaf(EditorTree.FocusedNode, false);
end;

procedure TfrmMain.bbCollapseNodesClick(Sender: TObject);
begin
  ExpandAllNodes(false);
end;

procedure TfrmMain.bbDeleteDefinitionClick(Sender: TObject);
begin
  DefinitionDelete(EditorTree.FocusedNode);
end;

procedure TfrmMain.edtMnemonicFilterCurChange(Sender: TObject);
begin
  // TODO: Filter is offsync, if the user leaves the edit by pressing ESC or focusing an other
  //       control
  SetMnemonicFilter(edtMnemonicFilter.CurText, bbExactMatch.Down);
end;

procedure TfrmMain.lbClipboardPasteClick(Sender: TObject);
begin
  ClipboardPaste(EditorTree.FocusedNode);
end;

procedure TfrmMain.lbCreateDefinitionClick(Sender: TObject);
begin
  DefinitionCreate;
end;

procedure TfrmMain.lbGenerateClick(Sender: TObject);

procedure DeleteDuplicates(T: TInstructionFilter);
var
  L: TList<TInstructionDefinition>;
  D: TInstructionDefinition;
  I, J: Integer;
  B: Boolean;
begin
  if (T is TDefinitionContainer) then
  begin
    L := TList<TInstructionDefinition>.Create;
    try
      for I := (T as TDefinitionContainer).DefinitionCount - 1 downto 0 do
      begin
        D := (T as TDefinitionContainer).Definitions[I];
        B := true;
        for J := 0 to L.Count - 1 do
        begin
          if (D.Equals(L[J])) then
          begin
            D.Free;
            B := false;
            Break;
          end;
        end;
        if (B) then L.Add(D);
      end;
    finally
      L.Free;
    end;
  end else
  begin
    for I := 0 to T.Capacity - 1 do
    begin
      if Assigned(T.Items[I]) then
      begin
        DeleteDuplicates(T.Items[I]);
      end;
    end;
  end;
end;

var
  frmGenerator: TfrmGenerator;
begin
  frmGenerator := TfrmGenerator.Create(Application);
  try
    frmGenerator.Editor := FEditor;
    frmGenerator.ShowModal;
  finally
    frmGenerator.Free;
  end;

  Exit;
  FEditor.BeginUpdate;
  DeleteDuplicates(FEditor.RootTable);
  FEditor.EndUpdate;
end;

procedure TfrmMain.lbLoadDatabaseClick(Sender: TObject);
var
  ID: Integer;
begin
  if (FHasUnsavedChanges) then
  begin
    ID := Application.MessageBox('Reloading the database will revert all unsaved changes. Do you'
      + ' really want to continue?', 'Question', MB_ICONWARNING or MB_YESNO or MB_DEFBUTTON2);
    if (ID <> IdYes) then
    begin
      Exit;
    end;
  end;
  FEditing := false;
  try
    ExpandAllNodes(false);
    FEditor.LoadFromFile(ExtractFilePath(ParamStr(0)) + 'instructions.json');
    if (lbMnemonicFilter.Down) then
    begin
      SetMnemonicFilter(edtMnemonicFilter.Text, bbExactMatch.Down);
    end;
  except
    on E: Exception do
    begin
      Application.MessageBox(PChar(E.Message), 'Error', MB_ICONERROR);
    end;
  end;
  FEditing := true;
  FHasUnsavedChanges := false;
  UpdateControls;
end;

procedure TfrmMain.lbMnemonicFilterClick(Sender: TObject);
begin
  StatusBar.Panels[1].Visible := lbMnemonicFilter.Down;
  piStatusBarProgress.Width := barStatusBarProgress.Control.ClientWidth;
  if (lbMnemonicFilter.Down) then
  begin
    SetMnemonicFilter(edtMnemonicFilter.Text, bbExactMatch.Down);
    edtMnemonicFilter.SetFocus;
  end else
  begin
    SetMnemonicFilter('', false);
  end;
end;

procedure TfrmMain.lbSaveDatabaseClick(Sender: TObject);
begin
  FEditor.SaveToFile(ExtractFilePath(ParamStr(0)) + 'instructions.json');
  FHasUnsavedChanges := false;
  UpdateControls;
end;

procedure TfrmMain.LoadGUIConfiguration;
var
  Ini: TIniFile;
  I: Integer;
  A: TArray<String>;
begin
  DockingManager.LoadLayoutFromIniFile(ChangeFileExt(ParamStr(0), 'Layout.ini'));
  Ini := TIniFile.Create(ChangeFileExt(ParamStr(0), '.ini'));
  try
    for I := 0 to EditorTree.Header.Columns.Count - 1 do
    begin
      EditorTree.Header.Columns[I].Width := Ini.ReadInteger('Editor',
        Format('Col_%.2d_Width', [I]), EditorTree.Header.Columns[I].Width);
    end;
    A := Ini.ReadString('Inspector', 'ExpandedFilterProperties', '').Split([',']);
    for I := Low(A) to High(A) do
    begin
      FExpandedFilterProperties.Add(A[I]);
    end;
    A := Ini.ReadString('Inspector', 'ExpandedDefinitionProperties', '').Split([',']);
    for I := Low(A) to High(A) do
    begin
      FExpandedDefinitionProperties.Add(A[I]);
    end;
    pnlInspector.Width := Ini.ReadInteger('Inspector', 'Width', 364);
    Inspector.OptionsView.RowHeaderWidth := Ini.ReadInteger('Inspector', 'RowHeaderWidth', 170);
  finally
    Ini.Free;
  end;
end;

procedure TfrmMain.SaveGUIConfiguration;
var
  Ini: TIniFile;
  I: Integer;
  S: String;
begin
  DockingManager.SaveLayoutToIniFile(ChangeFileExt(ParamStr(0), 'Layout.ini'));
  Ini := TIniFile.Create(ChangeFileExt(ParamStr(0), '.ini'));
  try
    for I := 0 to EditorTree.Header.Columns.Count - 1 do
    begin
      Ini.WriteInteger('Editor', Format('Col_%.2d_Width', [I]), EditorTree.Header.Columns[I].Width);
    end;
    UpdateExpandedProperties;
    S := '';
    for I := 0 to FExpandedFilterProperties.Count - 1 do
    begin
      S := S + FExpandedFilterProperties[I];
      if (I < FExpandedFilterProperties.Count - 1) then
      begin
        S := S + ',';
      end;
    end;
    Ini.WriteString('Inspector', 'ExpandedFilterProperties', S);
    S := '';
    for I := 0 to FExpandedDefinitionProperties.Count - 1 do
    begin
      S := S + FExpandedDefinitionProperties[I];
      if (I < FExpandedDefinitionProperties.Count - 1) then
      begin
        S := S + ',';
      end;
    end;
    Ini.WriteString('Inspector', 'ExpandedDefinitionProperties', S);
    Ini.WriteInteger('Inspector', 'Width', pnlInspector.Width);
    Ini.WriteInteger('Inspector', 'RowHeaderWidth', Inspector.OptionsView.RowHeaderWidth);
  finally
    Ini.Free;
  end;
end;

procedure TfrmMain.SetDefaultWindowPosition;
var
  R: TRect;
begin
  R := Screen.MonitorFromPoint(Mouse.CursorPos).WorkareaRect;
  SetBounds(R.Left + 50, R.Top + 50, R.Width - 100, R.Height - 100);
end;

procedure TfrmMain.SetMnemonicFilter(const Filter: String; ExactMatch: Boolean);

procedure ApplyMnemonicFilter(Filter: TInstructionFilter; out IsVisible: Boolean;
  const FilterText: String; FilterLength: Integer);
var
  D: TInstructionDefinition;
  C: TDefinitionContainer;
  I: Integer;
  B: Boolean;
begin
  IsVisible := (FilterLength = 0);
  if (iffIsDefinitionContainer in Filter.FilterFlags) then
  begin
    C := (Filter as TDefinitionContainer);
    for I := 0 to C.DefinitionCount - 1 do
    begin
      B := IsVisible;
      D := C.Definitions[I];
      if (not IsVisible) then
      begin
        if (Length(D.Mnemonic) >= FilterLength) then
        begin
          if (ExactMatch) then
          begin
            B := (CompareStr(FilterText, LowerCase(D.Mnemonic)) = 0);
          end else
          begin
            B := (CompareStr(FilterText, AnsiLowerCase(Copy(D.Mnemonic, 1, FilterLength))) = 0);
          end;
        end;
      end;
      EditorTree.IsVisible[GetTreeNode(D)] := B;
      IsVisible := IsVisible or B;
    end;
  end else
  begin
    for I := 0 to Filter.Capacity - 1 do
    begin
      if (not Assigned(Filter.Items[I])) then Continue;
      ApplyMnemonicFilter(Filter.Items[I], B, FilterText, FilterLength);
      EditorTree.IsVisible[GetTreeNode(Filter.Items[I])] := B;
      IsVisible := IsVisible or B;
    end;
    EditorTree.IsVisible[GetTreeNode(Filter)] := IsVisible;
  end;
end;

var
  FilterText: String;
  FilterLength: Integer;
  IsVisible: Boolean;
begin
  EditorTree.BeginUpdate;
  try
    FilterText := AnsiLowerCase(Filter);
    FilterLength := Length(Filter);
    ApplyMnemonicFilter(FEditor.RootTable, IsVisible, FilterText, FilterLength);
  finally
    EditorTree.EndUpdate;
  end;
end;

procedure TfrmMain.UpdateControls;
var
  NodeData: PEditorNodeData;
begin
  lbSaveDatabase.Enabled := FHasUnsavedChanges;

  NodeData := EditorTree.GetNodeData(EditorTree.FocusedNode);
  bbDuplicateDefinition.Enabled :=
    Assigned(NodeData) and (NodeData^.NodeType = ntInstructionDefinition);
  bbDeleteDefinition.Enabled :=
    Assigned(NodeData) and (NodeData^.NodeType = ntInstructionDefinition);
  bbClipboardCopy.Enabled :=
    Assigned(NodeData) {and (NodeData^.NodeType = ntInstructionDefinition)};
  bbClipboardCut.Enabled :=
    Assigned(NodeData) and (NodeData^.NodeType = ntInstructionDefinition);
  bbExpandLeaf.Enabled :=
    Assigned(NodeData) and (NodeData^.NodeType <> ntInstructionDefinition);
  bbCollapseLeaf.Enabled :=
    Assigned(NodeData) and (NodeData^.NodeType <> ntInstructionDefinition);
end;

procedure TfrmMain.UpdateExpandedProperties;
var
  I: Integer;
begin
  if (Assigned(Inspector.InspectedObject)) then
  begin
    if (Inspector.InspectedObject is TInstructionFilter) then
    begin
      FExpandedFilterProperties.Clear;
    end;
    if (Inspector.InspectedObject is TInstructionDefinition) then
    begin
      FExpandedDefinitionProperties.Clear;
    end;
    for I := 0 to Inspector.Rows.Count - 1 do
    begin
      if (Inspector.Rows[I].Expanded) then
      begin
        if (Inspector.InspectedObject is TInstructionFilter) then
        begin
          FExpandedFilterProperties.Add(
            (Inspector.Rows[I] as TcxPropertyRow).PropertyEditor.GetName);
        end;
        if (Inspector.InspectedObject is TInstructionDefinition) then
        begin
          FExpandedDefinitionProperties.Add(
            (Inspector.Rows[I] as TcxPropertyRow).PropertyEditor.GetName);
        end;
      end;
    end;
  end;
end;

procedure TfrmMain.UpdateStatistic;
var
  Mnemonics: TDictionary<String, Boolean>;
  Node: PVirtualNode;
  NodeData: PEditorNodeData;
begin
  if (not FUpdating) then
  begin
    Mnemonics := TDictionary<String, Boolean>.Create;
    try
      Node := EditorTree.GetFirst;
      while Assigned(Node) do
      begin
        NodeData := EditorTree.GetNodeData(Node);
        if (NodeData^.NodeType = ntInstructionDefinition) then
        begin
          if (not Mnemonics.ContainsKey(NodeData^.Definition.Mnemonic)) then
          begin
            Mnemonics.Add(NodeData^.Definition.Mnemonic, true);
          end;
        end;
        Node := EditorTree.GetNext(Node);
      end;
      StatusBar.Panels[2].Text := 'Mnemonics: ' + IntToStr(Mnemonics.Count);
    finally
      Mnemonics.Free;
    end;
    StatusBar.Panels[3].Text := 'Definitions: ' + IntToStr(FEditor.DefinitionCount);
    StatusBar.Panels[4].Text := 'Filters: ' + IntToStr(FEditor.FilterCount);
  end;
end;

procedure TfrmMain.InspectorItemChanged(Sender: TObject; AOldRow: TcxCustomRow;
  AOldCellIndex: Integer);
var
  Row: TcxPropertyRow;
  S: String;
begin
  lblPropertyInfo.Caption := 'No info text available';
  Row := (Inspector.FocusedRow as TcxPropertyRow);
  if Assigned(Row) and Assigned(Row.PropertyEditor) then
  begin
    S := Row.PropertyEditor.GetName;
    while (Assigned(Row.Parent)) do
    begin
      Row := (Row.Parent as TcxPropertyRow);
      S := Row.PropertyEditor.GetName + '.' + S;
    end;
    if (Inspector.InspectedObject is TInstructionFilter) then
    begin
      S := 'Filter.' + S;
    end else if (Inspector.InspectedObject is TInstructionDefinition) then
    begin
      S := 'Definition.' + S;
    end;
    lblPropertyInfo.Caption := GetPropertyHint(S);
  end;
end;

end.
