@echo off
:: --------{ EB Automotive Batch File }--------
::
:: script to update MCAL module with EB content
:: or reset it to vendor content

if [%1]==[EB_update] goto usage
if [%1]==[origin] goto usage
echo Usage: %0 [OPTION]
echo(
echo   EB_update
echo		Update files of the plug-in with content of Elektrobit Automotive GmbH.
echo   origin
echo		Reset the files of the plug-in with vendor content.
echo(
goto copy_end

:usage
cd %~d0 >NUL
cd %~p0
:: if exist an *.origin_version delete the current file:
:: if exist an *.EB_update file delete the current file:

:: perform origin
if [%1]==[EB_update] goto copy_EB
:: if exist an *.origin_version file make it to the current file:
goto copy_end

:: perform EB update
:copy_EB
:: if exist an *.EB_update file make it to the current file:
:copy_end
