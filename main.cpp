/*
g++ main.cpp -o Autoclicker.exe -O2 -lgdi32
*/

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <cstdio>
#include "controls.cpp"

Button CloseBtn, MinimizeBtn;
Edit SpeedEdit, IntervalEdit;
Label SpeedLabel, IntervalLabel, CPSLabel, UsLabel;

GroupBox Group;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_CREATE:
        {
            SpeedEdit = Edit(hwnd, NULL, 10, 30, 130, 25);
            IntervalEdit = Edit(hwnd, NULL, 10, 80, 130, 25);
            CloseBtn = Button(hwnd, L"X", 150, 5, 20, 20, 0);
            MinimizeBtn = Button(hwnd, L"-", 125, 5, 20, 20, 0);
            SpeedLabel = Label(10, 10, (wchar_t*)L"Speed", 5);
            CPSLabel = Label(145, 35, (wchar_t*)L"CPS", 3);
            IntervalLabel = Label(10, 60, (wchar_t*)L"Interval", 8);
            UsLabel = Label(145, 85, (wchar_t*)L"us", 2);

            SendMessage(SpeedEdit.GetHandle(), WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
            SendMessage(IntervalEdit.GetHandle(), WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
        }
        break;
        case WM_COMMAND:
        {
            switch(HIWORD(wParam))
            {
                case BN_CLICKED:
                {
                    if((HWND)lParam == CloseBtn.GetHandle())
                    {
                        SendMessage(hwnd, WM_CLOSE, 0, 0);
                    }else
                    if((HWND)lParam == MinimizeBtn.GetHandle())
                    {
                        ShowWindow(hwnd, SW_MINIMIZE);
                    }
                }
                break;
            }
        }
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            HBRUSH Brush = CreateSolidBrush(RGB(192,192,192));
            FillRect(hdc, &ps.rcPaint, Brush);

            SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));

            SetBkColor(hdc, RGB(192,192,192));
            SpeedLabel.Print(hdc);
            CPSLabel.Print(hdc);
            IntervalLabel.Print(hdc);
            UsLabel.Print(hdc);
            
            DeleteObject(Brush);
            EndPaint(hwnd, &ps);
        }
        break;
        default:
            return DefWindowProc(hwnd,Msg,wParam,lParam);
        break;
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = {};
    wc.lpfnWndProc = (WNDPROC) WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MainWindow";

    if(!RegisterClass(&wc))
    {
        return 1;
    }

    HWND hwnd = CreateWindowEx
    (
        0, L"MainWindow", L"Vroom-Vroom Autoclicker",
        WS_OVERLAPPED,
        CW_USEDEFAULT, CW_USEDEFAULT, 185, 360,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, nCmdShow);
    FreeConsole();

    MSG Msg;

    while(GetMessage(&Msg, hwnd, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return 0;
}