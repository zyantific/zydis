unit formCreateDefinition;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, cxGraphics, cxControls, cxLookAndFeels,
  cxLookAndFeelPainters, cxStyles, cxEdit, dxSkinsCore, cxInplaceContainer, cxVGrid, cxOI,
  System.ImageList, Vcl.ImgList, Vcl.StdCtrls, dxSkinSeven;

type
  TfrmCreateDefinition = class(TForm)
    GroupBox: TGroupBox;
    btnCancel: TButton;
    btnApply: TButton;
    imgIcons16: TcxImageList;
    Inspector: TcxRTTIInspector;
    procedure btnCancelClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure btnApplyClick(Sender: TObject);
  private
    FCanceled: Boolean;
  public
    property Canceled: Boolean read FCanceled;
  end;

var
  frmCreateDefinition: TfrmCreateDefinition;

implementation

{$R *.dfm}

procedure TfrmCreateDefinition.btnApplyClick(Sender: TObject);
begin
  Close;
end;

procedure TfrmCreateDefinition.btnCancelClick(Sender: TObject);
begin
  FCanceled := true;
  Close;
end;

procedure TfrmCreateDefinition.FormCreate(Sender: TObject);
begin
  FCanceled := false;
end;

end.
