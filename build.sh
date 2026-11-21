#!/usr/bin/env bash
# Builds AntiDialog.exe for Windows x64 from Linux/macOS using clang + lld (no Windows SDK needed).
# Requirements: clang, lld (lld-link), llvm-dlltool, llvm-rc  (e.g. `apt install clang lld llvm`)
set -euo pipefail
cd "$(dirname "$0")"
OUT=build
mkdir -p "$OUT"

# Import libraries generated from the exact list of Win32 functions the program uses.
mklib() {
  local lib=$1; shift
  { echo "LIBRARY $lib.dll"; echo "EXPORTS"; for f in "$@"; do echo "  $f"; done; } > "$OUT/$lib.def"
  llvm-dlltool -m i386:x86-64 -d "$OUT/$lib.def" -l "$OUT/$lib.lib"
}
mklib kernel32 GetModuleHandleW ExitProcess CreateThread Sleep GetTickCount GetModuleFileNameW \
  GetPrivateProfileIntW WritePrivateProfileStringW GetEnvironmentVariableW CreateDirectoryW GetFileAttributesW CopyFileW
mklib winmm timeBeginPeriod timeEndPeriod
mklib user32 RegisterClassExW CreateWindowExW DefWindowProcW GetMessageW TranslateMessage DispatchMessageW \
  IsDialogMessageW PostQuitMessage SendInput SendMessageW PostMessageW SetWindowTextW GetWindowTextW MessageBoxW \
  LoadCursorW LoadIconW SetTimer KillTimer GetAsyncKeyState MapVirtualKeyW GetKeyNameTextW wsprintfW EnableWindow \
  ShowWindow UpdateWindow GetSystemMetrics AdjustWindowRectEx GetDC ReleaseDC GetSysColorBrush GetSysColor \
  UpdateLayeredWindow SetWindowPos DrawTextW GetWindowRect InvalidateRect
mklib gdi32 GetDeviceCaps CreateFontW SetTextColor SetBkMode CreateCompatibleDC CreateDIBSection SelectObject \
  DeleteObject DeleteDC BitBlt GdiFlush
mklib comctl32 InitCommonControlsEx
mklib shell32 ShellExecuteW

(cd res && llvm-rc -fo "../$OUT/app.res" app.rc)
clang --target=x86_64-pc-windows-msvc -O2 -ffreestanding -fno-builtin -fno-math-errno \
  -fno-stack-protector -mno-stack-arg-probe -Wall -Wextra -Wno-unused-parameter \
  -c src/antidialog.c -o "$OUT/antidialog.obj"
lld-link /out:"$OUT/AntiDialog.exe" /subsystem:windows /entry:entry /nodefaultlib /Brepro \
  "$OUT/antidialog.obj" "$OUT/app.res" \
  "$OUT/kernel32.lib" "$OUT/user32.lib" "$OUT/gdi32.lib" "$OUT/comctl32.lib" "$OUT/winmm.lib" "$OUT/shell32.lib"
echo "Built $OUT/AntiDialog.exe"
