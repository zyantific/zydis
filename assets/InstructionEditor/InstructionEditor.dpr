program InstructionEditor;

uses
  Vcl.Forms,
  formMain in 'Forms\formMain.pas' {frmMain},
  untInstructionEditor in 'untInstructionEditor.pas',
  untInstructionFilters in 'untInstructionFilters.pas',
  untHelperClasses in 'untHelperClasses.pas',
  formEditorCPUIDFeatureFlags in 'Forms\Editors\formEditorCPUIDFeatureFlags.pas' {frmEditorCPUIDFeatureFlags},
  Vcl.Themes,
  Vcl.Styles,
  untPropertyHints in 'untPropertyHints.pas',
  formCreateDefinition in 'Forms\formCreateDefinition.pas' {frmCreateDefinition},
  untPropertyEditors in 'untPropertyEditors.pas',
  formEditorX86Registers in 'Forms\Editors\formEditorX86Registers.pas' {frmEditorX86Registers},
  formGenerator in 'Forms\formGenerator.pas' {frmGenerator},
  formEditorInstructionOperands in 'Forms\Editors\formEditorInstructionOperands.pas' {frmEditorInstructionOperands};

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
