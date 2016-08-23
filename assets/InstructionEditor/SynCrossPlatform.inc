
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

}

{$ifdef FPC}

  {.$MODE DELPHI} // we need e.g. auto-dereferenced pointers, as in Delphi
  {$INLINE ON}
  {$MINENUMSIZE 1}
  {$PACKSET 1}
  {$PACKENUM 1}

  {$define HASINLINE}
  {$define USEOBJECTINSTEADOFRECORD}
  {$Q-} // disable overflow checking
  {$R-} // disable range checking

  {$ifdef VER2_7_1}
    {$define ISFPC271}
    // defined if the http://mantis.freepascal.org/view.php?id=26773 bug is fixed
    // you should use 2.7.1/trunk branch in revision 28995 from 2014-11-05T22:17:54
    // => this will change the TInvokeableVariantType.SetProperty() signature
    {$define FPC_VARIANTSETVAR}
  {$endif}

{$else}

{$ifdef DWSSCRIPT} // always defined since SMS 1.1.2
  {$define ISDWS}           // e.g. for SmartMobileStudio or Delphi Web Script
  {$define ISSMS}           // for SmartMobileStudio
{$else}
  {$ifdef NEXTGEN}
    {$define HASINLINE}
    {$ZEROBASEDSTRINGS OFF}      // we expect to share code among platforms
    {$define ISDELPHI2010}
    {$define ISDELPHIXE}
    {$define USETMONITOR}
    {$if CompilerVersion >= 29.0}
      {$define ISDELPHIXE8} // e.g. for System.Net.HttpClient
    {$ifend}
  {$else}
  {$ifdef CONDITIONALEXPRESSIONS}  // Delphi 6 or newer
    {$ifdef UNICODE}
      {$ifdef CPUX64}
        {$define CPU64}
      {$endif}
    {$else}
      {$define USEOBJECTINSTEADOFRECORD}
    {$endif}
    {$ifdef VER140}
      {$define ISDELPHI6}
    {$endif}
    {$if CompilerVersion >= 18}    // Delphi 2006 or newer
      {$define HASINLINE}
    {$ifend}
    {$if CompilerVersion >= 21.0}
      {$define ISDELPHI2010}
    {$ifend}
    {$if CompilerVersion >= 22.0}
      {$define ISDELPHIXE}
    {$ifend}
    {$if CompilerVersion >= 23.0}
      {$define ISDELPHIXE2} // e.g. for Vcl.Graphics
      {$ifndef MSWINDOWS}
      {$define USETMONITOR}
      {$endif}
    {$ifend}
    {$if CompilerVersion >= 25.0}
      {$define ISDELPHIXE4}
      {$ZEROBASEDSTRINGS OFF}      // we expect to share code among platforms
      {$warn DUPLICATE_CTOR_DTOR OFF} // avoid W1029 unneeded hints
    {$ifend}
    {$if CompilerVersion >= 29.0}
      {$define ISDELPHIXE8} // e.g. for System.Net.HttpClient
    {$ifend}
  {$else}
    {$define ISDELPHI5OROLDER}
    {$define USEOBJECTINSTEADOFRECORD}
  {$endif CONDITIONALEXPRESSIONS}
  {$endif NEXTGEN}
  {$Q-} // disable overflow checking
  {$R-} // disable range checking
{$endif DELPHIWEBSCRIPT}

{$endif FPC}
