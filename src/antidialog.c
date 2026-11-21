/* AntiDialog for Genshin Impact (or any game)
   Plain Win32, no C runtime. Single portable .exe.
   - F7 (global) starts/stops. Action: keyboard key, left click or right click.
   - "REC"-style overlay (breathing green capsule) drawn on top of the game.
   - Settings are saved automatically to %APPDATA%\AntiDialog\config.ini */

typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;
typedef int BOOL;
typedef unsigned int UINT;
typedef unsigned char BYTE;
typedef unsigned long long ULONG_PTR, WPARAM, SIZE_T;
typedef long long LONG_PTR, LPARAM, LRESULT;
typedef void *HANDLE, *HWND, *HINSTANCE, *HMENU, *HICON, *HCURSOR, *HBRUSH, *HFONT, *HDC, *HGDIOBJ;
typedef unsigned short WCHAR;
typedef LRESULT (*WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef DWORD (*THREADPROC)(void *);
#define NULL ((void *)0)
#define API __declspec(dllimport)

typedef struct { UINT cbSize, style; WNDPROC lpfnWndProc; int cbClsExtra, cbWndExtra; HINSTANCE hInstance;
  HICON hIcon; HCURSOR hCursor; HBRUSH hbrBackground; const WCHAR *lpszMenuName, *lpszClassName; HICON hIconSm; } WNDCLASSEXW;
typedef struct { LONG x, y; } POINT;
typedef struct { LONG cx, cy; } SIZE;
typedef struct { HWND hwnd; UINT message; WPARAM wParam; LPARAM lParam; DWORD time; POINT pt; DWORD lPrivate; } MSG;
typedef struct { LONG left, top, right, bottom; } RECT;
typedef struct { LONG dx, dy; DWORD mouseData, dwFlags, time; ULONG_PTR dwExtraInfo; } MOUSEINPUT;
typedef struct { WORD wVk, wScan; DWORD dwFlags, time; ULONG_PTR dwExtraInfo; } KEYBDINPUT;
typedef struct { DWORD type; union { MOUSEINPUT mi; KEYBDINPUT ki; } u; } INPUT;
typedef struct { DWORD dwSize, dwICC; } INITCOMMONCONTROLSEX;
typedef struct { BYTE BlendOp, BlendFlags, SourceConstantAlpha, AlphaFormat; } BLENDFUNCTION;
typedef struct { DWORD biSize; LONG biWidth, biHeight; WORD biPlanes, biBitCount; DWORD biCompression, biSizeImage;
  LONG biXPelsPerMeter, biYPelsPerMeter; DWORD biClrUsed, biClrImportant; } BITMAPINFOHEADER;
typedef struct { BITMAPINFOHEADER bmiHeader; DWORD bmiColors[1]; } BITMAPINFO;
typedef struct { UINT CtlType, CtlID, itemID, itemAction, itemState; HWND hwndItem; HDC hDC; RECT rcItem; ULONG_PTR itemData; } DRAWITEMSTRUCT;

/* kernel32 */
API HINSTANCE GetModuleHandleW(const WCHAR *);
API void ExitProcess(UINT);
API HANDLE CreateThread(void *, SIZE_T, THREADPROC, void *, DWORD, DWORD *);
API void Sleep(DWORD);
API DWORD GetTickCount(void);
API DWORD GetModuleFileNameW(HINSTANCE, WCHAR *, DWORD);
API UINT GetPrivateProfileIntW(const WCHAR *, const WCHAR *, int, const WCHAR *);
API BOOL WritePrivateProfileStringW(const WCHAR *, const WCHAR *, const WCHAR *, const WCHAR *);
API DWORD GetEnvironmentVariableW(const WCHAR *, WCHAR *, DWORD);
API BOOL CreateDirectoryW(const WCHAR *, void *);
API DWORD GetFileAttributesW(const WCHAR *);
API BOOL CopyFileW(const WCHAR *, const WCHAR *, BOOL);
/* winmm */
API UINT timeBeginPeriod(UINT);
API UINT timeEndPeriod(UINT);
/* user32 */
API WORD RegisterClassExW(const WNDCLASSEXW *);
API HWND CreateWindowExW(DWORD, const WCHAR *, const WCHAR *, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, void *);
API LRESULT DefWindowProcW(HWND, UINT, WPARAM, LPARAM);
API BOOL GetMessageW(MSG *, HWND, UINT, UINT);
API BOOL TranslateMessage(const MSG *);
API LRESULT DispatchMessageW(const MSG *);
API BOOL IsDialogMessageW(HWND, MSG *);
API void PostQuitMessage(int);
API UINT SendInput(UINT, INPUT *, int);
API LRESULT SendMessageW(HWND, UINT, WPARAM, LPARAM);
API BOOL PostMessageW(HWND, UINT, WPARAM, LPARAM);
API BOOL SetWindowTextW(HWND, const WCHAR *);
API int GetWindowTextW(HWND, WCHAR *, int);
API int MessageBoxW(HWND, const WCHAR *, const WCHAR *, UINT);
API HCURSOR LoadCursorW(HINSTANCE, const WCHAR *);
API HICON LoadIconW(HINSTANCE, const WCHAR *);
API ULONG_PTR SetTimer(HWND, ULONG_PTR, UINT, void *);
API BOOL KillTimer(HWND, ULONG_PTR);
API short GetAsyncKeyState(int);
API UINT MapVirtualKeyW(UINT, UINT);
API int GetKeyNameTextW(LONG, WCHAR *, int);
API int wsprintfW(WCHAR *, const WCHAR *, ...);
API BOOL EnableWindow(HWND, BOOL);
API BOOL ShowWindow(HWND, int);
API BOOL UpdateWindow(HWND);
API int GetSystemMetrics(int);
API BOOL AdjustWindowRectEx(RECT *, DWORD, BOOL, DWORD);
API HDC GetDC(HWND);
API int ReleaseDC(HWND, HDC);
API HBRUSH GetSysColorBrush(int);
API DWORD GetSysColor(int);
API BOOL UpdateLayeredWindow(HWND, HDC, POINT *, SIZE *, HDC, POINT *, DWORD, BLENDFUNCTION *, DWORD);
API BOOL SetWindowPos(HWND, HWND, int, int, int, int, UINT);
API int DrawTextW(HDC, const WCHAR *, int, RECT *, UINT);
API BOOL GetWindowRect(HWND, RECT *);
API BOOL InvalidateRect(HWND, const RECT *, BOOL);
/* gdi32 */
API int GetDeviceCaps(HDC, int);
API HFONT CreateFontW(int, int, int, int, int, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, const WCHAR *);
API DWORD SetTextColor(HDC, DWORD);
API int SetBkMode(HDC, int);
API HDC CreateCompatibleDC(HDC);
API HGDIOBJ CreateDIBSection(HDC, const BITMAPINFO *, UINT, void **, HANDLE, DWORD);
API HGDIOBJ SelectObject(HDC, HGDIOBJ);
API BOOL DeleteObject(HGDIOBJ);
API BOOL DeleteDC(HDC);
API BOOL BitBlt(HDC, int, int, int, int, HDC, int, int, DWORD);
API BOOL GdiFlush(void);
/* shell32 */
API HINSTANCE ShellExecuteW(HWND, const WCHAR *, const WCHAR *, const WCHAR *, const WCHAR *, int);
/* comctl32 */
API BOOL InitCommonControlsEx(const INITCOMMONCONTROLSEX *);

/* No CRT: the compiler may still emit references to these symbols */
int _fltused = 0x9875;
void *memset(void *d, int c, SIZE_T n) { volatile BYTE *p = d; while (n--) *p++ = (BYTE)c; return d; }
void *memcpy(void *d, const void *s, SIZE_T n) { volatile BYTE *p = d; const BYTE *q = s; while (n--) *p++ = *q++; return d; }

#define WM_DESTROY 0x0002
#define WM_CLOSE 0x0010
#define WM_SETFONT 0x0030
#define WM_DRAWITEM 0x002B
#define WM_COMMAND 0x0111
#define WM_TIMER 0x0113
#define WM_HSCROLL 0x0114
#define WM_CTLCOLORSTATIC 0x0138
#define WM_EXITSIZEMOVE 0x0232
#define WM_USER 0x0400
#define WM_APP_TOGGLE 0x8001
#define WS_OVERLAPPED 0x00000000L
#define WS_POPUP 0x80000000L
#define WS_CAPTION 0x00C00000L
#define WS_SYSMENU 0x00080000L
#define WS_MINIMIZEBOX 0x00020000L
#define WS_CHILD 0x40000000L
#define WS_VISIBLE 0x10000000L
#define WS_TABSTOP 0x00010000L
#define WS_VSCROLL 0x00200000L
#define WS_EX_TOPMOST 0x00000008L
#define WS_EX_TRANSPARENT 0x00000020L
#define WS_EX_TOOLWINDOW 0x00000080L
#define WS_EX_CLIENTEDGE 0x00000200L
#define WS_EX_LAYERED 0x00080000L
#define WS_EX_NOACTIVATE 0x08000000L
#define ES_NUMBER 0x2000
#define ES_CENTER 0x1
#define SS_RIGHT 0x2
#define SS_CENTER 0x1
#define SS_ETCHEDHORZ 0x10
#define BS_PUSHBUTTON 0
#define BS_DEFPUSHBUTTON 1
#define BS_OWNERDRAW 0xB
#define CBS_DROPDOWNLIST 3
#define CB_ADDSTRING 0x0143
#define CB_GETCURSEL 0x0147
#define CB_SETCURSEL 0x014E
#define CBN_SELCHANGE 1
#define EN_CHANGE 0x0300
#define BN_CLICKED 0
#define EM_SETLIMITTEXT 0x00C5
#define TBS_NOTICKS 0x0010
#define TBM_GETPOS (WM_USER)
#define TBM_SETPOS (WM_USER + 5)
#define TBM_SETRANGE (WM_USER + 6)
#define TBM_SETPAGESIZE (WM_USER + 21)
#define SM_CXSCREEN 0
#define SM_CYSCREEN 1
#define SM_XVIRTUALSCREEN 76
#define SM_YVIRTUALSCREEN 77
#define SM_CXVIRTUALSCREEN 78
#define SM_CYVIRTUALSCREEN 79
#define LOGPIXELSY 90
#define COLOR_BTNFACE 15
#define TRANSPARENT 1
#define MB_ICONWARNING 0x30
#define INPUT_MOUSE 0
#define INPUT_KEYBOARD 1
#define MOUSEEVENTF_LEFTDOWN 0x02
#define MOUSEEVENTF_LEFTUP 0x04
#define MOUSEEVENTF_RIGHTDOWN 0x08
#define MOUSEEVENTF_RIGHTUP 0x10
#define KEYEVENTF_EXTENDEDKEY 0x1
#define KEYEVENTF_KEYUP 0x2
#define KEYEVENTF_SCANCODE 0x8
#define VK_F7 0x76
#define HWND_TOPMOST ((HWND)(LONG_PTR)-1)
#define SWP_NOSIZE 0x1
#define SWP_NOMOVE 0x2
#define SWP_NOACTIVATE 0x10
#define ULW_ALPHA 0x2
#define DT_SINGLELINE 0x20
#define DT_CALCRECT 0x400
#define DT_NOPREFIX 0x800
#define SRCCOPY 0x00CC0020
#define MAKEINTRESOURCEW(i) ((const WCHAR *)(ULONG_PTR)(WORD)(i))
#define PAYPAL_URL L"https://www.paypal.me/JanSan280406"
#define POS_OFFSET 100000 /* GetPrivateProfileInt cannot return negative values */

enum { ID_ACTION = 100, ID_ASSIGN, ID_KEYNAME, ID_INTERVAL, ID_TOGGLE, ID_STATUS,
       ID_OVSWITCH, ID_TRANSP, ID_TRANSPVAL, ID_BLUR, ID_BLURVAL, ID_DONATE };
enum { TIMER_CAPTURE = 2, TIMER_ANIM = 3 };
enum { ACT_KEY = 0, ACT_LCLICK = 1, ACT_RCLICK = 2 };

static volatile LONG g_running = 0;
static volatile LONG g_action = ACT_KEY;
static volatile LONG g_vk = 0;
static volatile LONG g_interval = 100;
static int g_ovEnabled = 1, g_transp = 15, g_blur = 50;
static int g_capturing = 0, g_loading = 1;
static BYTE g_downAtStart[256];
static HWND g_hwnd, g_status, g_toggle, g_assign, g_keyname, g_interval_edit, g_action_cb;
static HWND g_donate, g_switch, g_transpTb, g_transpVal, g_blurTb, g_blurVal;
static HFONT g_font, g_fontBig, g_fontBold;
static int g_dpi = 96;
static WCHAR g_ini[600];

/* overlay */
static HWND g_ov;
static HDC g_ovDC;
static HGDIOBJ g_ovBmp, g_ovOldBmp;
static int g_ovW, g_ovH, g_ovX, g_ovY, g_ovVisible = 0, g_ovTick = 0;
static DWORD g_ovStart, g_previewUntil;

static int S(int v) { return v * g_dpi / 96; }
static float clampf(float v, float a, float b) { return v < a ? a : (v > b ? b : v); }
static float absf(float v) { return v < 0 ? -v : v; }
static float sqrtf_(float v) { return __builtin_sqrtf(v < 0 ? 0 : v); }

/* ---------------- settings (.ini) ---------------- */
static int file_exists(const WCHAR *path) { return GetFileAttributesW(path) != 0xFFFFFFFF; }

/* Settings live in %APPDATA%\AntiDialog\config.ini (the folder is created automatically).
   Settings from older builds (%APPDATA%\AutoClicker\config.ini or an .ini next to the .exe) are migrated.
   The .ini section is still called [AutoClicker] so the migration is a plain copy. */
static void exe_ini_path(WCHAR *out) {
  DWORD n = GetModuleFileNameW(NULL, out, 520);
  int dot = -1;
  for (DWORD i = 0; i < n; i++) { if (out[i] == L'.') dot = (int)i; if (out[i] == L'\\') dot = -1; }
  if (n > 0 && n < 520 && dot > 0) { out[dot] = 0; wsprintfW(out + dot, L".ini"); }
  else wsprintfW(out, L"AntiDialog.ini");
}

static void ini_init(void) {
  WCHAR app[520], dir[560], old[600];
  DWORD m = GetEnvironmentVariableW(L"APPDATA", app, 520);
  if (m > 0 && m < 520) {
    wsprintfW(dir, L"%s\\AntiDialog", app);
    CreateDirectoryW(dir, NULL); /* no-op if it already exists */
    wsprintfW(g_ini, L"%s\\config.ini", dir);
    if (!file_exists(g_ini)) {
      wsprintfW(old, L"%s\\AutoClicker\\config.ini", app);
      if (file_exists(old)) CopyFileW(old, g_ini, 1);
      else { exe_ini_path(old); if (file_exists(old)) CopyFileW(old, g_ini, 1); }
    }
    if (WritePrivateProfileStringW(L"AutoClicker", L"Version", L"4", g_ini)) return;
  }
  /* no APPDATA or no write access: fall back to next to the .exe */
  exe_ini_path(g_ini);
  WritePrivateProfileStringW(L"AutoClicker", L"Version", L"4", g_ini);
}

static void save_int(const WCHAR *k, int v) {
  if (g_loading) return;
  WCHAR b[24]; wsprintfW(b, L"%d", v);
  WritePrivateProfileStringW(L"AutoClicker", k, b, g_ini);
}
static int load_int(const WCHAR *k, int def) { return (int)GetPrivateProfileIntW(L"AutoClicker", k, def, g_ini); }
static void save_winpos(void) {
  RECT r;
  if (GetWindowRect(g_hwnd, &r)) { save_int(L"WinX", r.left + POS_OFFSET); save_int(L"WinY", r.top + POS_OFFSET); }
}

/* ---------------- input ---------------- */
static int is_extended(int vk) {
  switch (vk) {
    case 0x21: case 0x22: case 0x23: case 0x24: case 0x25: case 0x26: case 0x27: case 0x28:
    case 0x2D: case 0x2E: case 0x6F: case 0x90: case 0xA3: case 0xA5: case 0x5B: case 0x5C: case 0x5D: case 0x2C:
      return 1;
  }
  return 0;
}

static const WCHAR *vk_english(int vk) {
  switch (vk) {
    case 0x08: return L"Backspace"; case 0x09: return L"Tab"; case 0x0D: return L"Enter";
    case 0x13: return L"Pause"; case 0x14: return L"Caps Lock"; case 0x1B: return L"Esc";
    case 0x20: return L"Space"; case 0x21: return L"Page Up"; case 0x22: return L"Page Down";
    case 0x23: return L"End"; case 0x24: return L"Home"; case 0x25: return L"Left Arrow";
    case 0x26: return L"Up Arrow"; case 0x27: return L"Right Arrow"; case 0x28: return L"Down Arrow";
    case 0x2C: return L"Print Screen"; case 0x2D: return L"Insert"; case 0x2E: return L"Delete";
    case 0x5B: return L"Left Win"; case 0x5C: return L"Right Win"; case 0x5D: return L"Menu";
    case 0x6A: return L"Num *"; case 0x6B: return L"Num +"; case 0x6D: return L"Num -";
    case 0x6E: return L"Num ."; case 0x6F: return L"Num /"; case 0x90: return L"Num Lock";
    case 0x91: return L"Scroll Lock"; case 0xA0: return L"Left Shift"; case 0xA1: return L"Right Shift";
    case 0xA2: return L"Left Ctrl"; case 0xA3: return L"Right Ctrl"; case 0xA4: return L"Left Alt";
    case 0xA5: return L"Right Alt";
  }
  return NULL;
}

static void key_name(int vk, WCHAR *out, int n) {
  const WCHAR *en = vk_english(vk);
  if (en) { wsprintfW(out, L"%s", en); return; }
  if ((vk >= 0x30 && vk <= 0x39) || (vk >= 0x41 && vk <= 0x5A)) { out[0] = (WCHAR)vk; out[1] = 0; return; }
  if (vk >= 0x60 && vk <= 0x69) { wsprintfW(out, L"Num %d", vk - 0x60); return; }
  if (vk >= 0x70 && vk <= 0x87) { wsprintfW(out, L"F%d", vk - 0x6F); return; }
  UINT sc = MapVirtualKeyW(vk, 0);
  LONG lp = (LONG)(sc << 16);
  if (is_extended(vk)) lp |= 1 << 24;
  if (!sc || !GetKeyNameTextW(lp, out, n)) wsprintfW(out, L"Key 0x%02X", vk);
}

static void send_key(int vk, int up) {
  INPUT in; memset(&in, 0, sizeof in);
  in.type = INPUT_KEYBOARD;
  WORD sc = (WORD)MapVirtualKeyW(vk, 0);
  if (sc) { in.u.ki.wScan = sc; in.u.ki.dwFlags = KEYEVENTF_SCANCODE; }
  else in.u.ki.wVk = (WORD)vk;
  in.u.ki.dwFlags |= (up ? KEYEVENTF_KEYUP : 0) | (is_extended(vk) ? KEYEVENTF_EXTENDEDKEY : 0);
  SendInput(1, &in, sizeof in);
}

static void send_click(int right) {
  INPUT in[2]; memset(in, 0, sizeof in);
  in[0].type = in[1].type = INPUT_MOUSE;
  in[0].u.mi.dwFlags = right ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_LEFTDOWN;
  in[1].u.mi.dwFlags = right ? MOUSEEVENTF_RIGHTUP : MOUSEEVENTF_LEFTUP;
  SendInput(2, in, sizeof in[0]);
}

static DWORD worker(void *p) {
  (void)p;
  for (;;) {
    if (!g_running) { Sleep(5); continue; }
    DWORD iv = (DWORD)g_interval; if (iv < 1) iv = 1;
    if (g_action == ACT_KEY) {
      int vk = g_vk;
      if (vk) {
        DWORD hold = iv / 2; if (hold > 30) hold = 30; if (hold < 1) hold = 1;
        send_key(vk, 0); Sleep(hold); send_key(vk, 1);
        if (iv > hold) Sleep(iv - hold);
      } else Sleep(iv);
    } else {
      send_click(g_action == ACT_RCLICK);
      Sleep(iv);
    }
  }
  return 0;
}

/* Global F7: polls the physical key state, works even while a game has focus */
static DWORD hotkey_thread(void *p) {
  (void)p; int prev = 1;
  for (;;) {
    int d = (GetAsyncKeyState(VK_F7) & 0x8000) != 0;
    if (d && !prev) PostMessageW(g_hwnd, WM_APP_TOGGLE, 0, 0);
    prev = d;
    Sleep(10);
  }
  return 0;
}

/* ---------------- antialiased drawing ---------------- */
/* signed distance to a horizontal capsule (negative inside) */
static float sdf_capsule(float px, float py, float cx, float cy, float hw, float r) {
  float ax = cx - hw + r, bx = cx + hw - r;
  float qx = px < ax ? px - ax : (px > bx ? px - bx : 0.f);
  float qy = py - cy;
  return sqrtf_(qx * qx + qy * qy) - r;
}

typedef struct { float r, g, b, a; } PX; /* premultiplied, 0..255 / 0..1 */
static void over(PX *d, float r, float g, float b, float a) {
  if (a <= 0) return;
  if (a > 1) a = 1;
  d->r = r * a + d->r * (1 - a);
  d->g = g * a + d->g * (1 - a);
  d->b = b * a + d->b * (1 - a);
  d->a = a + d->a * (1 - a);
}
static DWORD pack_premul(PX *p) {
  int a = (int)(p->a * 255.f + 0.5f), r = (int)(p->r + 0.5f), g = (int)(p->g + 0.5f), b = (int)(p->b + 0.5f);
  if (a > 255) a = 255; if (r > a) r = a; if (g > a) g = a; if (b > a) b = a;
  return ((DWORD)a << 24) | ((DWORD)r << 16) | ((DWORD)g << 8) | (DWORD)b;
}

static HGDIOBJ make_dib(HDC ref, int w, int h, void **bits) {
  BITMAPINFO bi; memset(&bi, 0, sizeof bi);
  bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bi.bmiHeader.biWidth = w;
  bi.bmiHeader.biHeight = -h; /* top-down */
  bi.bmiHeader.biPlanes = 1;
  bi.bmiHeader.biBitCount = 32;
  *bits = NULL;
  return CreateDIBSection(ref, &bi, 0, bits, NULL, 0);
}

/* ---------------- overlay ---------------- */
static void render_overlay(void) {
  /* size scales with screen resolution (168x36 px at 2560x1440), like the game UI */
  float s = GetSystemMetrics(SM_CYSCREEN) / 1440.f;
  if (s < 0.75f) s = 0.75f;
  if (s > 2.5f) s = 2.5f;
  float capW = 168.f * s, capH = 36.f * s, r = capH * 0.5f;
  float b = (float)g_blur;
  float feather = 1.f + b * 0.09f * s;        /* edge softness */
  float glowR = (3.f + b * 0.20f) * s;        /* blurred glow */
  int pad = (int)(glowR + feather + 3.f);
  int W = (int)capW + 2 * pad, H = (int)capH + 2 * pad;

  HDC scr = GetDC(NULL);
  void *bits = NULL, *mbits = NULL;
  HGDIOBJ bmp = make_dib(scr, W, H, &bits);
  HGDIOBJ mbmp = make_dib(scr, W, H, &mbits);
  HDC mdc = CreateCompatibleDC(scr);
  if (!g_ovDC) g_ovDC = CreateCompatibleDC(scr);
  ReleaseDC(NULL, scr);
  if (!bmp || !mbmp || !bits || !mbits || !mdc || !g_ovDC) {
    if (bmp) DeleteObject(bmp);
    if (mbmp) DeleteObject(mbmp);
    if (mdc) DeleteDC(mdc);
    return;
  }

  /* text mask rendered with GDI */
  HGDIOBJ mold = SelectObject(mdc, mbmp);
  memset(mbits, 0, (SIZE_T)W * H * 4);
  HFONT f = CreateFontW(-(int)(13.5f * s + 0.5f), 0, 0, 0, 700, 0, 0, 0, 1, 0, 0, 4 /*ANTIALIASED*/, 0, L"Segoe UI");
  HGDIOBJ fold = SelectObject(mdc, f);
  SetTextColor(mdc, 0x00FFFFFF);
  SetBkMode(mdc, TRANSPARENT);
  RECT tr = { 0, 0, 2000, 400 };
  DrawTextW(mdc, L"ACTIVE", -1, &tr, DT_CALCRECT | DT_SINGLELINE | DT_NOPREFIX);
  int tw = tr.right - tr.left, th = tr.bottom - tr.top;
  float dotR = 4.5f * s, gap = 8.f * s;
  float groupW = dotR * 2 + gap + tw;
  float cx = pad + capW / 2, cy = pad + capH / 2;
  float gx = pad + (capW - groupW) / 2;
  float dotCx = gx + dotR;
  RECT tr2;
  tr2.left = (LONG)(gx + dotR * 2 + gap);
  tr2.top = (LONG)(cy - th / 2.f + 0.5f);
  tr2.right = tr2.left + tw + 2;
  tr2.bottom = tr2.top + th;
  DrawTextW(mdc, L"ACTIVE", -1, &tr2, DT_SINGLELINE | DT_NOPREFIX);
  GdiFlush();

  DWORD *px = (DWORD *)bits;
  const DWORD *mk = (const DWORD *)mbits;
  int sh = (int)(s + 0.5f); if (sh < 1) sh = 1;
  for (int y = 0; y < H; y++) {
    float fy = y + 0.5f;
    float ty = clampf((fy - (cy - r)) / (2 * r), 0, 1);
    float fr = 40 + (18 - 40) * ty, fg = 185 + (120 - 185) * ty, fb = 95 + (60 - 95) * ty;
    for (int x = 0; x < W; x++) {
      float fx = x + 0.5f;
      PX p = { 0, 0, 0, 0 };
      float d = sdf_capsule(fx, fy, cx, cy, capW / 2, r);
      /* soft green glow */
      float dd = d > 0 ? d : 0;
      float gl = clampf(1.f - dd / glowR, 0, 1);
      over(&p, 74, 222, 128, gl * gl * 0.42f);
      /* capsule body (green glass) */
      float cov = clampf(0.5f - d / feather, 0, 1);
      over(&p, fr, fg, fb, 0.74f * cov);
      /* inner rim highlight */
      float rim = clampf(1.f - absf(d + 1.2f * s) / (1.0f * s + feather * 0.25f), 0, 1);
      over(&p, 160, 245, 190, rim * 0.40f);
      /* REC-style dot */
      float dx = fx - dotCx, dy = fy - cy;
      float dd2 = sqrtf_(dx * dx + dy * dy) - dotR;
      float dg = clampf(1.f - (dd2 > 0 ? dd2 : 0) / (7.f * s), 0, 1);
      over(&p, 200, 255, 215, dg * dg * 0.55f);
      over(&p, 240, 255, 245, clampf(0.5f - dd2, 0, 1));
      /* text shadow and text */
      if (y - sh >= 0) over(&p, 0, 45, 20, ((mk[(y - sh) * W + x] >> 8) & 255) / 255.f * 0.35f);
      over(&p, 255, 255, 255, ((mk[y * W + x] >> 8) & 255) / 255.f);
      px[y * W + x] = pack_premul(&p);
    }
  }

  SelectObject(mdc, fold);
  DeleteObject(f);
  SelectObject(mdc, mold);
  DeleteObject(mbmp);
  DeleteDC(mdc);

  /* swap in the new overlay bitmap */
  HGDIOBJ prev = SelectObject(g_ovDC, bmp);
  if (!g_ovOldBmp) g_ovOldBmp = prev;
  if (g_ovBmp) DeleteObject(g_ovBmp);
  g_ovBmp = bmp;
  g_ovW = W; g_ovH = H;
  int sw = GetSystemMetrics(SM_CXSCREEN);
  g_ovX = sw - (int)(40.f * s) - (int)capW - pad;
  g_ovY = (int)(34.f * s) - pad;
}

static void overlay_tick(void) {
  if (!g_ov || !g_ovBmp) return;
  DWORD now = GetTickCount();
  int want = g_ovEnabled && (g_running || (LONG)(g_previewUntil - now) > 0);
  if (!want) {
    if (g_ovVisible) { ShowWindow(g_ov, 0); g_ovVisible = 0; }
    return;
  }
  if (!g_ovVisible) g_ovStart = now;
  /* breathing: smoothstepped triangle wave, 2.2 s period */
  float t = (float)((now - g_ovStart) % 2200) / 2200.f;
  float tri = t < 0.5f ? t * 2.f : (1.f - t) * 2.f;
  float sm = tri * tri * (3.f - 2.f * tri);
  float k = 1.f - 0.45f * sm;
  float a = 255.f * (100 - g_transp) / 100.f * k;
  BLENDFUNCTION bf = { 0, 0, (BYTE)clampf(a, 0, 255), 1 /*AC_SRC_ALPHA*/ };
  POINT dst = { g_ovX, g_ovY }, src = { 0, 0 };
  SIZE sz = { g_ovW, g_ovH };
  UpdateLayeredWindow(g_ov, NULL, &dst, &sz, g_ovDC, &src, 0, &bf, ULW_ALPHA);
  if (!g_ovVisible) {
    ShowWindow(g_ov, 4 /*SW_SHOWNOACTIVATE*/);
    SetWindowPos(g_ov, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    g_ovVisible = 1;
  } else if (++g_ovTick % 30 == 0) {
    /* re-assert topmost so it stays above the game */
    SetWindowPos(g_ov, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
  }
}

static void preview_overlay(void) {
  if (g_loading) return;
  g_previewUntil = GetTickCount() + 2000;
  overlay_tick();
}

/* ---------------- custom-drawn toggle switch ---------------- */
static void draw_switch(DRAWITEMSTRUCT *di) {
  int W = di->rcItem.right - di->rcItem.left, H = di->rcItem.bottom - di->rcItem.top;
  if (W <= 0 || H <= 0) return;
  void *bits = NULL;
  HGDIOBJ bmp = make_dib(di->hDC, W, H, &bits);
  HDC mdc = CreateCompatibleDC(di->hDC);
  if (!bmp || !bits || !mdc) { if (bmp) DeleteObject(bmp); if (mdc) DeleteDC(mdc); return; }
  HGDIOBJ old = SelectObject(mdc, bmp);
  float s = g_dpi / 96.f;
  DWORD bg = GetSysColor(COLOR_BTNFACE);
  float bgR = (float)(bg & 255), bgG = (float)((bg >> 8) & 255), bgB = (float)((bg >> 16) & 255);
  float r = H / 2.f - 1.f, cx = W / 2.f, cy = H / 2.f;
  float tr_ = g_ovEnabled ? 34 : 150, tg = g_ovEnabled ? 197 : 150, tb = g_ovEnabled ? 94 : 156;
  float kr = r - 3.f * s; if (kr < 2) kr = 2;
  float kx = g_ovEnabled ? (W - 1.f - r) : (1.f + r);
  int focus = (di->itemState & 0x10) != 0;
  DWORD *px = (DWORD *)bits;
  for (int y = 0; y < H; y++) for (int x = 0; x < W; x++) {
    float fx = x + 0.5f, fy = y + 0.5f;
    float R = bgR, G = bgG, B = bgB, a;
    float d = sdf_capsule(fx, fy, cx, cy, W / 2.f - 1.f, r);
    if (focus) { a = clampf(1.f - absf(d - 1.f * s), 0, 1) * 0.6f; R += (0 - R) * a; G += (120 - G) * a; B += (215 - B) * a; }
    a = clampf(0.5f - d, 0, 1);
    R += (tr_ - R) * a; G += (tg - G) * a; B += (tb - B) * a;
    float dx = fx - kx, dy = fy - (cy + 1.f * s);
    float ds = sqrtf_(dx * dx + dy * dy) - kr;
    a = clampf(0.5f - ds / (2.f * s), 0, 1) * 0.25f;
    R *= 1 - a; G *= 1 - a; B *= 1 - a;
    dy = fy - cy;
    float dk = sqrtf_(dx * dx + dy * dy) - kr;
    a = clampf(0.5f - dk, 0, 1);
    R += (255 - R) * a; G += (255 - G) * a; B += (255 - B) * a;
    px[y * W + x] = ((DWORD)(R + 0.5f) << 16) | ((DWORD)(G + 0.5f) << 8) | (DWORD)(B + 0.5f);
  }
  BitBlt(di->hDC, di->rcItem.left, di->rcItem.top, W, H, mdc, 0, 0, SRCCOPY);
  SelectObject(mdc, old);
  DeleteObject(bmp);
  DeleteDC(mdc);
}

/* ---------------- Donate (PayPal) button ---------------- */
static void draw_donate(DRAWITEMSTRUCT *di) {
  int W = di->rcItem.right - di->rcItem.left, H = di->rcItem.bottom - di->rcItem.top;
  if (W <= 0 || H <= 0) return;
  void *bits = NULL;
  HGDIOBJ bmp = make_dib(di->hDC, W, H, &bits);
  HDC mdc = CreateCompatibleDC(di->hDC);
  if (!bmp || !bits || !mdc) { if (bmp) DeleteObject(bmp); if (mdc) DeleteDC(mdc); return; }
  HGDIOBJ old = SelectObject(mdc, bmp);
  float s = g_dpi / 96.f;
  int pressed = (di->itemState & 0x1) != 0, focus = (di->itemState & 0x10) != 0;
  DWORD bg = GetSysColor(COLOR_BTNFACE);
  float bgR = (float)(bg & 255), bgG = (float)((bg >> 8) & 255), bgB = (float)((bg >> 16) & 255);
  float cR = pressed ? 0 : 0, cG = pressed ? 87 : 112, cB = pressed ? 150 : 186; /* PayPal blue #0070BA */
  float r = H / 2.f - 1.f, cx = W / 2.f, cy = H / 2.f;
  DWORD *px = (DWORD *)bits;
  for (int y = 0; y < H; y++) for (int x = 0; x < W; x++) {
    float fx = x + 0.5f, fy = y + 0.5f, R = bgR, G = bgG, B = bgB, a;
    float d = sdf_capsule(fx, fy, cx, cy, W / 2.f - 1.f, r);
    a = clampf(0.5f - d, 0, 1);
    float t = clampf(fy / H, 0, 1);
    float fR = cR, fG = cG + 18 * (1 - t), fB = cB + 22 * (1 - t); /* subtle gradient */
    R += (fR - R) * a; G += (fG - G) * a; B += (fB - B) * a;
    if (focus) { a = clampf(1.f - absf(d + 2.f * s), 0, 1) * 0.7f; R += (255 - R) * a; G += (255 - G) * a; B += (255 - B) * a; }
    px[y * W + x] = ((DWORD)(R + 0.5f) << 16) | ((DWORD)(G + 0.5f) << 8) | (DWORD)(B + 0.5f);
  }
  GdiFlush();
  HGDIOBJ fold = SelectObject(mdc, g_fontBold);
  SetTextColor(mdc, 0x00FFFFFF);
  SetBkMode(mdc, TRANSPARENT);
  RECT tr = { 0, 0, W, H };
  DrawTextW(mdc, L"\u2665  Donate with PayPal", -1, &tr, DT_SINGLELINE | DT_NOPREFIX | 0x1 /*CENTER*/ | 0x4 /*VCENTER*/);
  SelectObject(mdc, fold);
  BitBlt(di->hDC, di->rcItem.left, di->rcItem.top, W, H, mdc, 0, 0, SRCCOPY);
  SelectObject(mdc, old);
  DeleteObject(bmp);
  DeleteDC(mdc);
}

/* ---------------- UI ---------------- */
static void read_interval(void) {
  WCHAR buf[16]; int n = GetWindowTextW(g_interval_edit, buf, 16), v = 0;
  for (int i = 0; i < n; i++) if (buf[i] >= L'0' && buf[i] <= L'9') v = v * 10 + (buf[i] - L'0');
  if (v < 1) v = 1;
  g_interval = v;
  save_int(L"Interval", v);
}

static void update_labels(void) {
  WCHAR b[32];
  wsprintfW(b, L"%d%%", g_transp); SetWindowTextW(g_transpVal, b);
  wsprintfW(b, L"%d%%", g_blur); SetWindowTextW(g_blurVal, b);
}

static void set_key_label(void) {
  WCHAR name[64], txt[96];
  if (g_vk) { key_name(g_vk, name, 64); wsprintfW(txt, L"Key: %s", name); }
  else wsprintfW(txt, L"Key: (none)");
  SetWindowTextW(g_keyname, txt);
}

static void update_ui(void) {
  if (g_running) {
    SetWindowTextW(g_status, L"● ACTIVE  —  F7 to stop");
    SetWindowTextW(g_toggle, L"Stop (F7)");
  } else {
    SetWindowTextW(g_status, L"■ STOPPED  —  F7 to start");
    SetWindowTextW(g_toggle, L"Start (F7)");
  }
  EnableWindow(g_action_cb, !g_running);
  EnableWindow(g_assign, !g_running && g_action == ACT_KEY);
}

static void stop_capture(void) {
  if (!g_capturing) return;
  g_capturing = 0;
  KillTimer(g_hwnd, TIMER_CAPTURE);
  SetWindowTextW(g_assign, L"Set key");
}

static void toggle(void) {
  stop_capture();
  if (!g_running) {
    read_interval();
    if (g_action == ACT_KEY && !g_vk) {
      MessageBoxW(g_hwnd, L"Set a key first using the \"Set key\" button.", L"AntiDialog", MB_ICONWARNING);
      return;
    }
  }
  g_running = !g_running;
  if (!g_running && g_action == ACT_KEY && g_vk) send_key(g_vk, 1); /* make sure the key is not left held down */
  if (!g_running) g_previewUntil = GetTickCount();
  update_ui();
  overlay_tick();
}

static HWND mk(DWORD ex, const WCHAR *cls, const WCHAR *txt, DWORD style, int x, int y, int w, int h, int id, HFONT font) {
  HWND c = CreateWindowExW(ex, cls, txt, WS_CHILD | WS_VISIBLE | style, S(x), S(y), S(w), S(h), g_hwnd,
                           (HMENU)(LONG_PTR)id, GetModuleHandleW(NULL), NULL);
  if (c) SendMessageW(c, WM_SETFONT, (WPARAM)font, 1);
  return c;
}

static LRESULT wndproc(HWND h, UINT m, WPARAM w, LPARAM l) {
  switch (m) {
    case WM_APP_TOGGLE:
      toggle();
      return 0;
    case WM_COMMAND: {
      int id = (int)(w & 0xFFFF), code = (int)((w >> 16) & 0xFFFF);
      if (id == ID_TOGGLE && code == BN_CLICKED) toggle();
      else if (id == ID_DONATE && code == BN_CLICKED) ShellExecuteW(h, L"open", PAYPAL_URL, NULL, NULL, 1);
      else if (id == ID_OVSWITCH && code == BN_CLICKED) {
        g_ovEnabled = !g_ovEnabled;
        save_int(L"Overlay", g_ovEnabled);
        InvalidateRect(g_switch, NULL, 0);
        if (g_ovEnabled) preview_overlay(); else overlay_tick();
      } else if (id == ID_ASSIGN && code == BN_CLICKED) {
        if (g_capturing) { stop_capture(); return 0; }
        for (int vk = 0; vk < 256; vk++) g_downAtStart[vk] = (GetAsyncKeyState(vk) & 0x8000) ? 1 : 0;
        g_capturing = 1;
        SetWindowTextW(g_assign, L"Press a key...");
        SetTimer(h, TIMER_CAPTURE, 15, NULL);
      } else if (id == ID_ACTION && code == CBN_SELCHANGE) {
        LONG a = (LONG)SendMessageW(g_action_cb, CB_GETCURSEL, 0, 0);
        if (a < 0 || a > 2) a = 0;
        g_action = a;
        save_int(L"Action", a);
        stop_capture();
        update_ui();
      } else if (id == ID_INTERVAL && code == EN_CHANGE) read_interval();
      return 0;
    }
    case WM_HSCROLL:
      if ((HWND)l == g_transpTb) {
        int v = (int)SendMessageW(g_transpTb, TBM_GETPOS, 0, 0);
        if (v != g_transp) { g_transp = v; save_int(L"Transparency", v); update_labels(); }
        preview_overlay();
      } else if ((HWND)l == g_blurTb) {
        int v = (int)SendMessageW(g_blurTb, TBM_GETPOS, 0, 0);
        if (v != g_blur) { g_blur = v; save_int(L"Blur", v); update_labels(); render_overlay(); }
        preview_overlay();
      }
      return 0;
    case WM_DRAWITEM: {
      DRAWITEMSTRUCT *di = (DRAWITEMSTRUCT *)l;
      if (di && di->CtlID == ID_OVSWITCH) { draw_switch(di); return 1; }
      if (di && di->CtlID == ID_DONATE) { draw_donate(di); return 1; }
      break;
    }
    case WM_TIMER:
      if (w == TIMER_ANIM) { overlay_tick(); return 0; }
      if (w == TIMER_CAPTURE && g_capturing) {
        for (int vk = 8; vk < 255; vk++) {
          if (vk == 0x10 || vk == 0x11 || vk == 0x12 || vk == VK_F7) continue; /* skip generic Shift/Ctrl/Alt and F7 */
          int down = (GetAsyncKeyState(vk) & 0x8000) != 0;
          if (!down) { g_downAtStart[vk] = 0; continue; }
          if (g_downAtStart[vk]) continue;
          g_vk = vk;
          save_int(L"Key", vk);
          set_key_label();
          stop_capture();
          break;
        }
      }
      return 0;
    case WM_CTLCOLORSTATIC:
      if ((HWND)l == g_status) {
        SetTextColor((HDC)w, g_running ? 0x00009A00 : 0x000000C0); /* BGR */
        SetBkMode((HDC)w, TRANSPARENT);
        return (LRESULT)GetSysColorBrush(COLOR_BTNFACE);
      }
      break;
    case WM_EXITSIZEMOVE:
      save_winpos();
      break;
    case WM_CLOSE:
      g_running = 0;
      if (g_vk) send_key(g_vk, 1);
      save_winpos();
      if (g_ov) ShowWindow(g_ov, 0);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }
  return DefWindowProcW(h, m, w, l);
}

void entry(void) {
  HINSTANCE hi = GetModuleHandleW(NULL);
  INITCOMMONCONTROLSEX icc = { sizeof icc, 0x4000 | 0xFF };
  InitCommonControlsEx(&icc);
  timeBeginPeriod(1);

  HDC dc = GetDC(NULL); g_dpi = GetDeviceCaps(dc, LOGPIXELSY); ReleaseDC(NULL, dc);
  if (g_dpi < 96) g_dpi = 96;
  g_font = CreateFontW(-S(12), 0, 0, 0, 400, 0, 0, 0, 1, 0, 0, 5, 0, L"Segoe UI");
  g_fontBold = CreateFontW(-S(12), 0, 0, 0, 700, 0, 0, 0, 1, 0, 0, 5, 0, L"Segoe UI");
  g_fontBig = CreateFontW(-S(15), 0, 0, 0, 700, 0, 0, 0, 1, 0, 0, 5, 0, L"Segoe UI");

  /* load settings */
  ini_init();
  int a = load_int(L"Action", ACT_KEY); if (a < 0 || a > 2) a = ACT_KEY; g_action = a;
  int vk = load_int(L"Key", 0x46 /* F */); if (vk < 8 || vk > 254 || vk == VK_F7) vk = 0x46; g_vk = vk;
  int iv = load_int(L"Interval", 100); if (iv < 1 || iv > 9999999) iv = 100; g_interval = iv;
  g_ovEnabled = load_int(L"Overlay", 1) ? 1 : 0;
  g_transp = load_int(L"Transparency", 15); if (g_transp < 0 || g_transp > 90) g_transp = 15;
  g_blur = load_int(L"Blur", 50); if (g_blur < 0 || g_blur > 100) g_blur = 50;

  WNDCLASSEXW wc; memset(&wc, 0, sizeof wc);
  wc.cbSize = sizeof wc;
  wc.lpfnWndProc = wndproc;
  wc.hInstance = hi;
  wc.hIcon = LoadIconW(hi, MAKEINTRESOURCEW(1));
  wc.hIconSm = wc.hIcon;
  wc.hCursor = LoadCursorW(NULL, MAKEINTRESOURCEW(32512));
  wc.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
  wc.lpszClassName = L"AntiDialogMain";
  RegisterClassExW(&wc);

  WNDCLASSEXW oc; memset(&oc, 0, sizeof oc);
  oc.cbSize = sizeof oc;
  oc.lpfnWndProc = DefWindowProcW;
  oc.hInstance = hi;
  oc.lpszClassName = L"AntiDialogOverlay";
  RegisterClassExW(&oc);

  DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
  RECT r = { 0, 0, S(320), S(444) };
  AdjustWindowRectEx(&r, style, 0, 0);
  int ww = r.right - r.left, wh = r.bottom - r.top;
  int x = (GetSystemMetrics(SM_CXSCREEN) - ww) / 2, y = (GetSystemMetrics(SM_CYSCREEN) - wh) / 2;
  int sx = load_int(L"WinX", 0), sy = load_int(L"WinY", 0);
  if (sx && sy) {
    sx -= POS_OFFSET; sy -= POS_OFFSET;
    int vx = GetSystemMetrics(SM_XVIRTUALSCREEN), vy = GetSystemMetrics(SM_YVIRTUALSCREEN);
    int vw = GetSystemMetrics(SM_CXVIRTUALSCREEN), vh = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    if (sx >= vx - ww / 2 && sx <= vx + vw - ww / 2 && sy >= vy && sy <= vy + vh - S(40)) { x = sx; y = sy; }
  }
  g_hwnd = CreateWindowExW(0, wc.lpszClassName, L"AntiDialog (Administrator)", style, x, y, ww, wh, NULL, NULL, hi, NULL);

  mk(0, L"STATIC", L"Action:", 0, 16, 18, 90, 18, -1, g_font);
  g_action_cb = mk(0, L"COMBOBOX", L"", CBS_DROPDOWNLIST | WS_TABSTOP | WS_VSCROLL, 110, 14, 194, 120, ID_ACTION, g_font);
  SendMessageW(g_action_cb, CB_ADDSTRING, 0, (LPARAM)L"Keyboard key");
  SendMessageW(g_action_cb, CB_ADDSTRING, 0, (LPARAM)L"Left click");
  SendMessageW(g_action_cb, CB_ADDSTRING, 0, (LPARAM)L"Right click");
  SendMessageW(g_action_cb, CB_SETCURSEL, (WPARAM)g_action, 0);

  g_assign = mk(0, L"BUTTON", L"Set key", BS_PUSHBUTTON | WS_TABSTOP, 16, 50, 124, 28, ID_ASSIGN, g_font);
  g_keyname = mk(0, L"STATIC", L"", 0, 150, 56, 154, 18, ID_KEYNAME, g_font);
  set_key_label();

  mk(0, L"STATIC", L"Interval (ms):", 0, 16, 96, 92, 18, -1, g_font);
  WCHAR ivs[16]; wsprintfW(ivs, L"%d", iv);
  g_interval_edit = mk(WS_EX_CLIENTEDGE, L"EDIT", ivs, ES_NUMBER | ES_CENTER | WS_TABSTOP, 110, 92, 90, 24, ID_INTERVAL, g_font);
  SendMessageW(g_interval_edit, EM_SETLIMITTEXT, 7, 0);

  mk(0, L"STATIC", L"", SS_ETCHEDHORZ, 16, 130, 288, 2, -1, g_font);
  mk(0, L"STATIC", L"Overlay", 0, 16, 140, 200, 18, -1, g_fontBold);

  mk(0, L"STATIC", L"Show on-screen overlay", 0, 16, 170, 220, 18, -1, g_font);
  g_switch = mk(0, L"BUTTON", L"", BS_OWNERDRAW | WS_TABSTOP, 258, 166, 46, 24, ID_OVSWITCH, g_font);

  mk(0, L"STATIC", L"Transparency", 0, 16, 204, 150, 18, -1, g_font);
  g_transpVal = mk(0, L"STATIC", L"", SS_RIGHT, 234, 204, 70, 18, ID_TRANSPVAL, g_font);
  g_transpTb = mk(0, L"msctls_trackbar32", L"", WS_TABSTOP | TBS_NOTICKS, 8, 222, 304, 30, ID_TRANSP, g_font);
  SendMessageW(g_transpTb, TBM_SETRANGE, 1, (LPARAM)((90 << 16) | 0));
  SendMessageW(g_transpTb, TBM_SETPAGESIZE, 0, 10);
  SendMessageW(g_transpTb, TBM_SETPOS, 1, g_transp);

  mk(0, L"STATIC", L"Blur", 0, 16, 258, 150, 18, -1, g_font);
  g_blurVal = mk(0, L"STATIC", L"", SS_RIGHT, 234, 258, 70, 18, ID_BLURVAL, g_font);
  g_blurTb = mk(0, L"msctls_trackbar32", L"", WS_TABSTOP | TBS_NOTICKS, 8, 276, 304, 30, ID_BLUR, g_font);
  SendMessageW(g_blurTb, TBM_SETRANGE, 1, (LPARAM)((100 << 16) | 0));
  SendMessageW(g_blurTb, TBM_SETPAGESIZE, 0, 10);
  SendMessageW(g_blurTb, TBM_SETPOS, 1, g_blur);
  update_labels();

  g_toggle = mk(0, L"BUTTON", L"Start (F7)", BS_DEFPUSHBUTTON | WS_TABSTOP, 16, 318, 288, 34, ID_TOGGLE, g_font);
  g_status = mk(0, L"STATIC", L"", SS_CENTER, 16, 362, 288, 26, ID_STATUS, g_fontBig);
  g_donate = mk(0, L"BUTTON", L"Donate with PayPal", BS_OWNERDRAW | WS_TABSTOP, 60, 400, 200, 32, ID_DONATE, g_fontBold);

  /* overlay window: topmost, click-through, never takes focus, hidden from the taskbar */
  g_ov = CreateWindowExW(WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
                         oc.lpszClassName, L"AntiDialog Overlay", WS_POPUP, 0, 0, 1, 1, NULL, NULL, hi, NULL);
  render_overlay();

  g_loading = 0;
  update_ui();
  ShowWindow(g_hwnd, 1);
  UpdateWindow(g_hwnd);
  SetTimer(g_hwnd, TIMER_ANIM, 33, NULL);
  CreateThread(NULL, 0, worker, NULL, 0, NULL);
  CreateThread(NULL, 0, hotkey_thread, NULL, 0, NULL);

  MSG msg;
  while (GetMessageW(&msg, NULL, 0, 0) > 0) {
    if (IsDialogMessageW(g_hwnd, &msg)) continue;
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }
  timeEndPeriod(1);
  ExitProcess(0);
}
