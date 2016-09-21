unit formCodeGenerator;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, System.ImageList, Vcl.ImgList, cxGraphics, Vcl.StdCtrls,
  Vcl.ComCtrls, Zydis.InstructionEditor;

type
  TfrmCodeGenerator = class(TForm)
    GroupBox: TGroupBox;
    btnClose: TButton;
    btnGenerate: TButton;
    imgIcons16: TcxImageList;
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    GroupBox1: TGroupBox;
    pbTotalProgress: TProgressBar;
    Label1: TLabel;
    pbCurrentOperation: TProgressBar;
    Label2: TLabel;
    lblOperationName: TLabel;
    procedure btnCloseClick(Sender: TObject);
    procedure btnGenerateClick(Sender: TObject);
  strict private
    FEditor: TInstructionEditor;
  strict private
    procedure GeneratorWorkStart(Sender: TObject; const OperationName: String;
      OperationCount, OperationNumber: Integer; MinWorkCount, MaxWorkCount: Integer);
    procedure GeneratorWork(Sender: TObject; WorkCount: Integer);
    procedure GeneratorWorkEnd(Sender: TObject);
  public
    property Editor: TInstructionEditor read FEditor write FEditor;
  end;

var
  frmCodeGenerator: TfrmCodeGenerator;

implementation

uses
  Zydis.CodeGenerator, untHelperClasses;

{$R *.dfm}

{ TfrmGenerator }

procedure TfrmCodeGenerator.btnCloseClick(Sender: TObject);
begin
  Close;
end;

procedure TfrmCodeGenerator.btnGenerateClick(Sender: TObject);
var
  Generator: TCodeGenerator;
  Statistics: TCodeGeneratorStatistics;
begin
  pbTotalProgress.Min := 0;
  pbTotalProgress.Max := 0;
  pbTotalProgress.Position := 0;
  Generator := TCodeGenerator.Create;
  try
    Generator.OnWorkStart := GeneratorWorkStart;
    Generator.OnWork := GeneratorWork;
    Generator.OnWorkEnd := GeneratorWorkEnd;
    Generator.GenerateCode(
      FEditor, 'D:\Verteron Development\GitHub\zyan-disassembler-engine\', Statistics);
    // TODO: Display statistics
  finally
    Generator.Free;
  end;
end;

procedure TfrmCodeGenerator.GeneratorWork(Sender: TObject; WorkCount: Integer);
begin
  pbTotalProgress.Position := pbTotalProgress.Max - pbCurrentOperation.Max + WorkCount;
  pbCurrentOperation.Position := WorkCount;
  if ((WorkCount mod pbCurrentOperation.Tag) = 0) then
  begin
    Application.ProcessMessages;
  end;
end;

procedure TfrmCodeGenerator.GeneratorWorkEnd(Sender: TObject);
begin
  lblOperationName.Caption := '';
  pbTotalProgress.Position := pbTotalProgress.Max;
  pbCurrentOperation.Position := pbCurrentOperation.Max;
  Application.ProcessMessages;
end;

procedure TfrmCodeGenerator.GeneratorWorkStart(Sender: TObject; const OperationName: String;
  OperationCount, OperationNumber: Integer; MinWorkCount, MaxWorkCount: Integer);
begin
  lblOperationName.Caption := OperationName;
  pbTotalProgress.Position := pbTotalProgress.Max;
  pbTotalProgress.Min := pbTotalProgress.Min + MinWorkCount;
  pbTotalProgress.Max := pbTotalProgress.Max + MaxWorkCount;
  pbCurrentOperation.Position := MinWorkCount;
  pbCurrentOperation.Min := MinWorkCount;
  pbCurrentOperation.Max := MaxWorkCount;
  if ((MaxWorkCount - MinWorkCount) > 1000) then
  begin
    pbCurrentOperation.Tag := 100;
  end else if ((MaxWorkCount - MinWorkCount) > 100) then
  begin
    pbCurrentOperation.Tag := 10;
  end else
  begin
    pbCurrentOperation.Tag := 1;
  end;
  Application.ProcessMessages;
end;

end.
