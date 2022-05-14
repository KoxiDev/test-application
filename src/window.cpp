// window.cpp
// main file. initializes and handles the main win32 window.

#include "calc.cpp"
#include <windows.h>
#include <wingdi.h>
#include <string>
#include <map>

#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") 

#define TITLEBAR_OFFSET 30
#define HCMD_CALCULATE 1
#define HCMD_OPEN_SETTINGS 2
#define HCMD_CLOSE_SETTINGS 3
#define HCMD_HANDLE_S_CHECKBOX_1 4

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void LoadControls(HWND);
void LoadControlsBack(HWND);
void CmdCalculate();
void OpenAppSettings(HWND);

std::map<int, bool> appsettings;
HWND hInput, hOutput, a, b, c;

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprevinst, LPSTR lpcmdline, int nshowcmd) {
	WNDCLASSW wc = {0};
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hinst;
	wc.lpszClassName = L"WindowMain";
	wc.lpfnWndProc = WindowProcedure;
	
	if (!RegisterClassW(&wc))
		return -1;
	CreateWindowW(L"WindowMain", L"Basic Calculator", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_VISIBLE, 100, 100, 325, 170+30, NULL, NULL, NULL, NULL);
	
	MSG msg = {0};
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
		case WM_COMMAND:
			switch (wp) {
				case HCMD_CALCULATE:
					CmdCalculate();
					break;
				case HCMD_OPEN_SETTINGS:
					OpenAppSettings(hwnd);
					break;
				case HCMD_CLOSE_SETTINGS:
					LoadControlsBack(hwnd);
					break;
				case HCMD_HANDLE_S_CHECKBOX_1:
					// checkbox state check: SendDlgItemMessageW(hwnd, HCMD_HANDLE_S_CHECKBOX_1, BM_GETCHECK, 0, 0)
					break;
			}
			break;
		case WM_CREATE:
			LoadControls(hwnd);
			break;
		default:
			return DefWindowProcW(hwnd, msg, wp, lp);
	}
}

void LoadControls(HWND hwnd) {
	a = CreateWindowExW(0, L"button", L"Settings", WS_VISIBLE | WS_CHILD, 5, 5, 70, 20, hwnd, (HMENU)HCMD_OPEN_SETTINGS, NULL, NULL);
	hOutput = CreateWindowExW(0, L"static", L"0", WS_VISIBLE | WS_CHILD, 5, TITLEBAR_OFFSET+5, 300, 20, hwnd, NULL, NULL, NULL);
	hInput = CreateWindowExW(0, L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 5, TITLEBAR_OFFSET+30, 300, 20, hwnd, NULL, NULL, NULL);
	b = CreateWindowExW(0, L"button", L"Calculate", WS_VISIBLE | WS_CHILD, 5, TITLEBAR_OFFSET+55, 100, 20, hwnd, (HMENU)HCMD_CALCULATE, NULL, NULL);
	c = CreateWindowExW(0, L"static", L"by KoxiDev", WS_VISIBLE | WS_CHILD, 5, TITLEBAR_OFFSET+110, 200, 20, hwnd, NULL, NULL, NULL);
}

void LoadControlsBack(HWND hwnd) {
	DestroyWindow(a);
	DestroyWindow(b);
	DestroyWindow(c);
	LoadControls(hwnd);
}

void CmdCalculate() {
	wchar_t winput[16];
	GetWindowTextW(hInput, (LPWSTR)winput, 16);
	
	std::wstring ws(winput);
	std::string input(ws.begin(), ws.end());
	std::string output = Calculate(input);
	
	SetWindowTextA(hOutput, (LPCSTR)output.c_str());
}

void OpenAppSettings(HWND hwnd) {
	DestroyWindow(hInput);
	DestroyWindow(hOutput);
	DestroyWindow(a);
	DestroyWindow(b);
	DestroyWindow(c);
	
	a = CreateWindowExW(0, L"button", L"Close", WS_VISIBLE | WS_CHILD, 5, 5, 45, 20, hwnd, (HMENU)HCMD_CLOSE_SETTINGS, NULL, NULL);
	b = CreateWindowExW(0, L"button", L"null", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 5, 30, 100, 20, hwnd, (HMENU)HCMD_HANDLE_S_CHECKBOX_1, NULL, NULL);
}
