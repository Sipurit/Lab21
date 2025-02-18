#include <windows.h>
#include<cstdlib>
#include<stdio.h>

HWND textfield, textbox1, textbox2;
char number[2];

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {

		case WM_CREATE:
		
		textfield = CreateWindowA("STATIC", "Please input two numbers", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 20, 180, 25, hwnd, NULL, NULL, NULL);

		textbox1 = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 50, 50, 120, 25, hwnd, NULL, NULL, NULL);
		textbox2 = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 50, 80, 120, 25, hwnd, NULL, NULL, NULL);
		CreateWindow("BUTTON", "+", WS_BORDER | WS_CHILD | WS_VISIBLE, 60, 110, 25, 25, hwnd, (HMENU) 1, NULL, NULL);
		CreateWindow("BUTTON", "-", WS_BORDER | WS_CHILD | WS_VISIBLE, 85, 110, 25, 25, hwnd, (HMENU) 2, NULL, NULL);
		CreateWindow("BUTTON", "*", WS_BORDER | WS_CHILD | WS_VISIBLE, 110, 110, 25, 25, hwnd, (HMENU) 3, NULL, NULL);
		CreateWindow("BUTTON", "/", WS_BORDER | WS_CHILD | WS_VISIBLE, 135, 110, 25, 25, hwnd, (HMENU) 4, NULL, NULL);

		break;

		case WM_COMMAND:
		switch (LOWORD(wParam)) {
			case 1:
			case 2: 
			case 3: 
			case 4: 
				{
					char number[2][10];
					double a, b, result;
					GetWindowText(textbox1, number[0], sizeof(number[0]));
					GetWindowText(textbox2, number[1], sizeof(number[1]));
					a = atof(number[0]);
					b = atof(number[1]);
	
					if (LOWORD(wParam) == 1) result = a + b;
					else if (LOWORD(wParam) == 2) result = a - b;
					else if (LOWORD(wParam) == 3) result = a * b;
					else if (LOWORD(wParam) == 4) {
						if (b == 0) {
							MessageBox(hwnd, "Error: Division by zero!", "Error", MB_OK | MB_ICONERROR);
							break;
						}
						result = a / b;
					}
	
					char resultStr[100];
					sprintf(resultStr, "%f", result);
					MessageBox(hwnd, resultStr, "Result", MB_OK);
				}
				break;
		}
		break;

		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(255,105,180));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "My Calculator", 
		WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
