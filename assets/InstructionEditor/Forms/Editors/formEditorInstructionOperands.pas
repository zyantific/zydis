unit formEditorInstructionOperands;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.ComCtrls, System.ImageList, Vcl.ImgList, cxGraphics,
  Vcl.StdCtrls, untInstructionEditor;

type
  TfrmEditorInstructionOperands = class(TForm)
    GroupBox: TGroupBox;
    btnCancel: TButton;
    btnApply: TButton;
    imgIcons16: TcxImageList;
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    GroupBox1: TGroupBox;
    procedure FormCreate(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure btnApplyClick(Sender: TObject);
  strict private
    FApplyChanges: Boolean;
    FEditor: TInstructionEditor;
    FDefinition: TInstructionDefinition;
  strict private
    function GetOperands: TInstructionOperands; inline;
    procedure SetOperands(const Value: TInstructionOperands); inline;
  public
    property ApplyChanges: Boolean read FApplyChanges;
    property Operands: TInstructionOperands read GetOperands write SetOperands;
  end;

var
  frmEditorInstructionOperands: TfrmEditorInstructionOperands;

implementation

{$R *.dfm}

{ TfrmEditorInstructionOperands }

procedure TfrmEditorInstructionOperands.btnApplyClick(Sender: TObject);
begin
  FApplyChanges := true;
  Close;
end;

procedure TfrmEditorInstructionOperands.btnCancelClick(Sender: TObject);
begin
  Close;
end;

procedure TfrmEditorInstructionOperands.FormCreate(Sender: TObject);
begin
  FEditor := TInstructionEditor.Create;
  FEditor.Reset;
  FDefinition := FEditor.CreateDefinition('dummy');
end;

procedure TfrmEditorInstructionOperands.FormDestroy(Sender: TObject);
begin
  if (Assigned(FEditor)) then
  begin
    FEditor.Free;
  end;
end;

function TfrmEditorInstructionOperands.GetOperands: TInstructionOperands;
begin
  Result := FDefinition.Operands;
end;

procedure TfrmEditorInstructionOperands.SetOperands(const Value: TInstructionOperands);
begin
  FDefinition.Operands.Assign(Value);
end;

end.
