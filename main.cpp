/*
g++ main.cpp -o Autoclicker.exe -O2 -lgdi32
*/

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <cstdio>
#include "ctrlfunctions.cpp"

wctrls::Button CloseBtn, MinimizeBtn;
wctrls::ToggleButton CustomBtn, ActivateBtn, StartBtn;
wctrls::NumberInput SpeedEdit, IntervalEdit;
wctrls::Label SpeedLabel, IntervalLabel, CPSLabel, UsLabel, Title;
wctrls::RadioButton LeftRadio, RightRadio, CustomRadio;

wctrls::CheckBox ToggleCheck;

wctrls::GroupBox Group;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    using namespace wctrls;
    switch (Msg)
    {
        case WM_CREATE:
        {
            Title = Label(hwnd, L"Vroom-Vroom Autoclicker", 30, 5, 80, 30, ES_MULTILINE | ES_CENTER);

            SpeedEdit = NumberInput(hwnd, 10, 55, 50, 20, 0);
            IntervalEdit = NumberInput(hwnd, 95, 55, 50, 20, 0);
            CloseBtn = Button(hwnd, L"X", 150, 5, 20, 20, 0);
            MinimizeBtn = Button(hwnd, L"-", 125, 5, 20, 20, 0);
            SpeedLabel = Label(hwnd, L"Speed", 10, 40, 70, 15, 0);
            CPSLabel = Label(hwnd, L"CPS", 65, 58, 25, 15, 0);
            IntervalLabel = Label(hwnd, L"Interval", 95, 40, 70, 15, 0);
            UsLabel = Label(hwnd, L"us", 150, 58, 25, 15, 0);

            ToggleCheck = CheckBox(hwnd, L"Toggle Mode", 45, 85, 90, 20, 0);

            Group = GroupBox(hwnd, 10, 110, 160, 120);

            LeftRadio = RadioButton(Group.GetHandle(), L"Mouse Left", 10, 10, 140, 20, 0);
            RightRadio = RadioButton(Group.GetHandle(), L"Mouse Right", 10, 30, 140, 20, 0);
            CustomRadio = RadioButton(Group.GetHandle(), L"Custom", 10, 50, 140, 20, 0);
            CustomBtn = Button(Group.GetHandle(), L"Key: NUMPAD0", 10, 70, 140, 40, BS_PUSHBUTTON);

            CustomBtn.Toggle(0);
            SendMessage(LeftRadio.GetHandle(), BM_SETCHECK, BST_CHECKED, 0);

            ActivateBtn = Button(hwnd, L"Activate: NUMPAD0", 20, 240, 140, 40, BS_PUSHBUTTON);
            StartBtn = Button(hwnd, L"Start", 30, 290, 120, 30, BS_PUSHBUTTON);
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
                    }else
                    if((HWND)lParam == CustomRadio.GetHandle())
                    {
                        CustomBtn.Toggle(1);
                    }else
                    if((HWND)lParam == LeftRadio.GetHandle())
                    {
                        CustomBtn.Toggle(0);
                    }else
                    if((HWND)lParam == RightRadio.GetHandle())
                    {
                        CustomBtn.Toggle(0);
                    }else
                    if((HWND)lParam == StartBtn.GetHandle())
                    {
                        if(StartBtn.GetState() == BST_CHECKED)
                        {
                            StartBtn.SetText(L"Stop");
                            Title.SetText(L"Autoclicker is running...");
                            
                            SpeedEdit.Toggle(0);
                            IntervalEdit.Toggle(0);
                            CloseBtn.Toggle(0);
                            MinimizeBtn.Toggle(0);
                            ToggleCheck.Toggle(0);
                            LeftRadio.Toggle(0);
                            RightRadio.Toggle(0);
                            CustomRadio.Toggle(0);
                            CustomBtn.Toggle(0);
                            ActivateBtn.Toggle(0);
                        }else
                        {
                            StartBtn.SetText(L"Start");
                            Title.SetText(L"Autoclicker has stopped.");
                            
                            SpeedEdit.Toggle(1);
                            IntervalEdit.Toggle(1);
                            CloseBtn.Toggle(1);
                            MinimizeBtn.Toggle(1);
                            ToggleCheck.Toggle(1);
                            LeftRadio.Toggle(1);
                            RightRadio.Toggle(1);
                            CustomRadio.Toggle(1);
                            ActivateBtn.Toggle(1);

                            if(CustomRadio.GetState() == BST_CHECKED)
                            {
                                CustomBtn.Toggle(1);
                            }
                        }
                    }
                }
                break;
            }
        }
        break;
        /*
        case WM_CTLCOLORBTN:
        case WM_CTLCOLORSTATIC:
        {
            if((HWND)lParam == LeftRadio.GetHandle() ||
            (HWND)lParam == RightRadio.GetHandle() ||
            (HWND)lParam == CustomRadio.GetHandle())
            {
                SetBkMode((HDC)wParam, OPAQUE);
                return (LRESULT)GetStockObject(NULL_BRUSH);
            }
            return (LRESULT) GetClassLongPtr(hwnd, GCLP_HBRBACKGROUND);
        }
        break;
        */
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
    wc.hbrBackground = CreateSolidBrush(RGB(240,240,240));

    if(!RegisterClass(&wc))
    {
        return 1;
    }

    HWND hwnd = CreateWindowEx
    (
        0, L"MainWindow", L"Vroom-Vroom Autoclicker",
        WS_OVERLAPPED | WS_DLGFRAME,
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