:: ____________________________
:: ██▀▀█▀▀██▀▀▀▀▀▀▀█▀▀█        │   ▄▄▄                ▄▄      
:: ██  ▀  █▄  ▀██▄ ▀ ▄█ ▄▀▀ █  │  ▀█▄  ▄▀██ ▄█▄█ ██▀▄ ██  ▄███
:: █  █ █  ▀▀  ▄█  █  █ ▀▄█ █▄ │  ▄▄█▀ ▀▄██ ██ █ ██▀  ▀█▄ ▀█▄▄
:: ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀────────┘                 ▀▀
::  by Guillaume 'Aoineko' Blanchard under CC BY-SA license
::────────────────────────────────────────────────────────────────────

cls
@echo off
taskkill /IM java.exe
taskkill /IM openMsx.exe
cls

..\..\tools\build\Node\node.exe ..\..\engine\script\js\build.js target=%1


rem start openmsx.exe -machine Philips_NMS_8250 -carta E:\Dropbox\FAUSTO\SVILUPPI\MSX\CODE\C\MSXgl\projects\samprexp\out\samprexp.rom