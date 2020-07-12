
FORFILES /m *.vox /c "cmd /c IsoVoxel.exe @file 64 64 64 1 full" 


@echo off
setlocal
setlocal enabledelayedexpansion
@echo off
for /d /r "%CD%" %%i in (*Above) do (
  @if exist "%%i" (
    @set _variable=%%i
    @echo !_variable!
    @start /d D:\"Program Files (x86)"\"SpriteSheet Packer\" SpriteSheetPacker.exe !_variable! !_variable!\.. -f json 
   
    )
  )
endlocal



