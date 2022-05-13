// main file. intiliazes and handles the win32 window.
// compile command: g++ src\window.cpp -o bin\app.exe -static-libgcc -static-libstdc++

#include "calc.cpp"
#include <windows.h>
#include <wingdi.h>
#include <string>

#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") 

#define HCMD_CALCULATE 1

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void InitLoadingState(HWND);
void LoadControls(HWND);
void CmdCalculate();

HWND hInput, hOutput;
HMENU hMenu;

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprevinst, LPSTR lpcmdline, int nshowcmd) {
	WNDCLASSW wc = {0};
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hinst;
	wc.lpszClassName = L"WindowMain";
	wc.lpfnWndProc = WindowProcedure;
	
	if (!RegisterClassW(&wc))
		return -1;
	CreateWindowW(L"WindowMain", L"test", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 325, 90+30, NULL, NULL, NULL,NULL);
	
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
			}
			break;
		case WM_CREATE:
			InitLoadingState(hwnd);
			break;
		default:
			return DefWindowProcW(hwnd, msg, wp, lp);
	}
}

void InitLoadingState(HWND hwnd) {
	LoadControls(hwnd);
}

void LoadControls(HWND hwnd) {
	hOutput = CreateWindowExW(0, L"static", L"0", WS_VISIBLE | WS_CHILD, 5, 5, 300, 20, hwnd, NULL, NULL, NULL);
	hInput = CreateWindowExW(0, L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 5, 30, 300, 20, hwnd, NULL, NULL, NULL);
	CreateWindowExW(0, L"Button", L"Calculate", WS_VISIBLE | WS_CHILD, 5, 55, 70+30, 20, hwnd, (HMENU)HCMD_CALCULATE, NULL, NULL);
}

void CmdCalculate() {
	wchar_t winput[8];
	GetWindowTextW(hInput, (LPWSTR)winput, 8);
	
	std::wstring ws(winput);
	std::string input(ws.begin(), ws.end());
	std::string output = std::to_string(Calculate(input));
	
	SetWindowTextA(hOutput, (LPCSTR)output.c_str());
}
