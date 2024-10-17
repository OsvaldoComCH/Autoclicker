/*
g++ main.cpp -o Autoclicker.exe -O2 -lgdi32
*/

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <cstdio>
#include "controls.cpp"


wctrls::Button CloseBtn, MinimizeBtn, CustomBtn;
wctrls::NumberInput SpeedEdit, IntervalEdit;
wctrls::Label SpeedLabel, IntervalLabel, CPSLabel, UsLabel, Title;
wctrls::RadioButton LeftRadio, RightRadio, CustomRadio;

wctrls::GroupBox Group;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    using namespace wctrls;
    switch (Msg)
    {
        case WM_CREATE:
        {
            Title = Label(hwnd, L"Welcome To Autoclicker", 5, 10, 120, 15, 0);

            SpeedEdit = NumberInput(hwnd, 10, 50, 50, 20, 0);
            IntervalEdit = NumberInput(hwnd, 95, 50, 50, 20, 0);
            CloseBtn = Button(hwnd, L"X", 155, 5, 20, 20, 0);
            MinimizeBtn = Button(hwnd, L"-", 130, 5, 20, 20, 0);
            SpeedLabel = Label(hwnd, L"Speed", 10, 35, 70, 15, 0);
            CPSLabel = Label(hwnd, L"CPS", 65, 53, 25, 15, 0);
            IntervalLabel = Label(hwnd, L"Interval", 95, 35, 70, 15, 0);
            UsLabel = Label(hwnd, L"us", 150, 53, 25, 15, 0);

            Group = GroupBox(hwnd, 10, 80, 160, 160);

            LeftRadio = RadioButton(Group.GetHandle(), L"Mouse Left", 10, 10, 140, 30, 0);
            RightRadio = RadioButton(Group.GetHandle(), L"Mouse Right", 10, 40, 140, 30, 0);
            CustomRadio = RadioButton(Group.GetHandle(), L"Custom", 10, 70, 140, 30, 0);
            CustomBtn = Button(Group.GetHandle(), L"Key: NUMPAD0", 10, 100, 140, 40, 0);
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
        case WM_CTLCOLORSTATIC:
        {
            return (LRESULT)GetStockObject(WHITE_BRUSH);
        }
        break;
        case WM_CTLCOLORBTN:
        {
            switch(lParam)
            {
                case LeftRadio.GetHandle():
                case RightRadio.GetHandle():
                case CustomRadio.GetHandle():
                {
                    return (LRESULT)GetStockObject(WHITE_BRUSH);
                }
                break;
            }
        }
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            /*
            HBRUSH Brush = CreateSolidBrush(RGB(240,240,240));
            FillRect(hdc, &ps.rcPaint, Brush);
            DeleteObject(Brush);
            */
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