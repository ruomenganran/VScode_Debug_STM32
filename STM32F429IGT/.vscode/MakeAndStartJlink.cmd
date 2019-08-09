echo off
cd %ProgramFiles(x86)%/SEGGER/JLink_V512f
tasklist /fi "Imagename eq JLinkGDBServer.exe"|find "JLinkGDBServer.exe"&&taskkill /f /im "JLinkGDBServer.exe"
tasklist /fi "Imagename eq JLinkGDBServer.exe"|find "JLinkGDBServer.exe"&&taskkill /f /im "JLinkGDBServer.exe"
start JLinkGDBServer.exe -select USB -device %1 -if JTAG -speed 1000 -noir
mingw32-make
