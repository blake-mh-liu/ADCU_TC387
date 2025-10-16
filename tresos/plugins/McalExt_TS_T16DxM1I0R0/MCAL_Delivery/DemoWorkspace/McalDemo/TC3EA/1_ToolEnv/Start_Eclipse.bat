ECHO OFF
CALL c:\sofit\aurix2g_sw_mcal\setpath.cmd
CALL c:\sofit\aurix2g_sw_mcal\sofit_tools.cmd
set LM_LICENSE_FILE=7594@blrla042.blr.infineon.com
set RLM_LICENSE=7594@sinlal01.sin.infineon.com
set WRSD_LICENSE_FILE=4230@blrla042.blr.infineon.com
set TSK_LICENSE_KEY_SW160800=6dfa-5f5c-946c-4277
set TSK_LICENSE_SERVER=sinlal01.sin.infineon.com:9090;vihlal21.vih.infineon.com:9090
set GHS_LMHOST=blrlal11.blr.infineon.com
set GHS_LMPORT=2009
SET HIGHTEC_LM=%HIGHTEC_HOME%\licensemanager
set TSK_NO_ANONYMOUS=1
set BINUTILS_PATH=%BIFACES_HOME%\bin
set PATH=%BINUTILS_PATH%;%PATH%
set PATH=%PATH%;%HIGHTEC_HOME%\licensemanager
SET PERL_LIB_PATH=%PERL_HOME%\c\bin
SET MAKECMD_WITH_APP=%ECLIPSE_HOME%\eclipse.exe
SET BUILDENV=DEV
SET SOFIT_PROJECT=

REM -----------------------------------------------------
SET PATH=%BINUTILS_PATH%;%PERL_LIB_PATH%;%HIGHTEC_LM%;%PATH%

START %MAKECMD_WITH_APP%
EXIT
