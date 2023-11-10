#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>

int introTextScrollAmount = 20;
void renderText(HDC hdc, int textsize, LPCWSTR text, int x, int y) {
	HFONT hFont = CreateFontW(textsize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                         CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	SelectObject(hdc, hFont);
	TextOutW(hdc, x, y, text, lstrlenW(text));
	DeleteObject(hFont);
	ReleaseDC(NULL, hdc);
}

// Function to handle window messages
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);

				// Set the text color
				SetTextColor(hdc, RGB(200, 200, 200)); // White text

				// Set the background color
				SetBkColor(hdc, RGB(0, 0, 0)); // Black background
				
				// Render the text
				const wchar_t* text = L"A young scientist is working on a very important project\nthat involves very dangerous chemicals worse than acid. It includes\nCarbon dioxide, Oxygen, Acid and a lot of other stuff.\nThe young scientist drops the bottle of chemicals and releases\ndifferent beings on earth Werewolves, monsters, dragons, and\nmore the scientist goes to fix the world by getting,\ngadgets, gear, weapons, and most powerful magic. His son,\na normal boy, gets infected and hunted down. His mission\nis to kill the ultimate monster hunting him down.";
				renderText(hdc, 24, text, 50, 50+introTextScrollAmount);
				EndPaint(hwnd, &ps);
			}
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

HWND createWindow(HINSTANCE hInstance, int nCmdShow) {
	WNDCLASSEXW wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"Quest of the Sword";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassExW(&wc))
	{
		MessageBoxW(NULL, L"Window Registration Failed!", L"QOTS Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Create the window
	HWND hwnd = CreateWindowExW(0, L"Quest of the Sword", L"Quest of the Sword", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		MessageBoxW(NULL, L"Window Creation Failed!", L"QOTS Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	return hwnd;
}

bool YesNoMessageWindow(char* text, char* title, int icon) {
	int sdfgh = MessageBoxW(NULL, (LPCWSTR)text, (LPCWSTR)title, MB_ICONQUESTION | MB_YESNO);
	if (sdfgh == 7) {
		return false;
	}
	else if (sdfgh == 6) {
		return true;
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwnd = createWindow(hInstance, nCmdShow);

	//int gpuExelerate = YesNoMessageWindow(("Would you like to use GPU exeleration", "GPU exeleration?", MB_ICONQUESTION | MB_YESNO);

	// Game loop and message handling
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		introTextScrollAmount++;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	} 

	return msg.wParam;
}