program InstructionEditor;

uses
  Vcl.Forms,
  formMain in 'Forms\formMain.pas' {frmMain},
  Zydis.InstructionEditor in 'Zydis.InstructionEditor.pas',
  Zydis.InstructionFilters in 'Zydis.InstructionFilters.pas',
  untHelperClasses in 'untHelperClasses.pas',
  formEditorCPUIDFeatureFlags in 'Forms\Editors\formEditorCPUIDFeatureFlags.pas' {frmEditorCPUIDFeatureFlags},
  Vcl.Themes,
  Vcl.Styles,
  untPropertyHints in 'untPropertyHints.pas',
  formCreateDefinition in 'Forms\formCreateDefinition.pas' {frmCreateDefinition},
  formEditorX86Registers in 'Forms\Editors\formEditorX86Registers.pas' {frmEditorX86Registers},
  formCodeGenerator in 'Forms\formCodeGenerator.pas' {frmCodeGenerator},
  Zydis.CodeGenerator in 'Zydis.CodeGenerator.pas',
  untPropertyEditors in 'untPropertyEditors.pas';

{$R *.res}

begin
  {$IFDEF DEBUG}
  ReportMemoryLeaksOnShutdown := true;
  {$ENDIF}
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TfrmMain, frmMain);
  Application.Run;
end.
