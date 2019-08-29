#define ID_BUTTON	1
#include <Windows.h>
#include <commctrl.h>

const char g_szClassName[] = "MyClassName";

LRESULT CALLBACK ButtonProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch(Msg)
	{
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			HDC hdc_x = CreateCompatibleDC(NULL);
			HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, "texture.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); //Load the bitmap
			SelectObject(hdc_x, hBitmap); //Put the bitmap into the hdc_x
			
			BitBlt(hdc, 0, 0, 180, 50, hdc_x, 0, 0, SRCCOPY); //Draw it.
			
			EndPaint(hWnd, &ps);
			break;
		}
		
		default:
			return DefSubclassProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch(Msg)
	{
		case WM_CREATE: {
			RECT rect;
			GetWindowRect(hWnd, &rect);
			
			HWND hButton = CreateWindow(TEXT("BUTTON"), TEXT("START EDITING!"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, ((rect.right - rect.left) / 2) - 90, 500, 180, 50,
					hWnd, (HMENU)ID_BUTTON, NULL, NULL);
					
			SetWindowSubclass(hButton, ButtonProc, 0, 0);
			break;
		}
		
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			HDC hdc_x = CreateCompatibleDC(NULL);
			HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, "wallpaper.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); //Load the bitmap
			SelectObject(hdc_x, hBitmap); //Put the bitmap into the hdc_x
			
			RECT rect;
			GetWindowRect(hWnd, &rect);
			
			BitBlt(hdc, 0, 0, rect.right - rect.left, 400, hdc_x, 0, 0, SRCCOPY); //Draw it.
			
			HFONT hFont = CreateFont(48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Roboto Th"); //Create the font. (I'm using Roboto Thin.)
			DeleteDC(hdc_x); //Delete the HDC containing the bitmap.
			SelectObject(hdc, hFont);
			
			SetTextColor(hdc, RGB(255, 255, 255)); //White text.
			SetBkMode(hdc, TRANSPARENT); //Transparent background.
			
			int a = (rect.right - rect.left) / 2;
			int b = 200;
			
			int x = a - (360 / 2);
			int y = b - (207 / 2);
			
			TextOut(hdc, x, y, "We love nice pictures.", strlen("We love nice pictures."));
			
			ReleaseDC(hWnd, hdc);
			EndPaint(hWnd, &ps);
			break;
		}
		
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
			
		case WM_DESTROY:
			PostQuitMessage(0x00);
			break;
			
		default:
			return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLein, int nShowCmd)
{
	WNDCLASSEXA wc;
	HWND hWnd;
	MSG Msg;
	
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = g_szClassName;
	wc.lpszMenuName = "MENU";
	wc.style = CS_HREDRAW | CS_VREDRAW;
	
	if(!RegisterClassExA(&wc))
	{
		MessageBox(NULL, "Cannot register window class.", "Uh oh...", MB_ICONERROR | MB_OK);
		return -1;
	}
	
	hWnd = CreateWindowExA(WS_EX_LAYERED, g_szClassName, "Scenes", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
			hInstance, NULL);
			
	if(hWnd == NULL)
	{
		MessageBox(NULL, "Cannot create the window.", "Uh oh...", MB_ICONERROR | MB_OK);
		return -1;
	}
	
	SetLayeredWindowAttributes(hWnd, 0, 249, LWA_ALPHA);
	
	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);
	
	while(GetMessage(&Msg, hWnd, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	
	return Msg.wParam;
	
}
