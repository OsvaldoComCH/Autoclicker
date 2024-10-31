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
wctrls::Label SpeedLabel, IntervalLabel, CPSLabel, UsLabel, Title, ActivateLabel;
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
            Title = Label(hwnd, L"Vroom-Vroom Autoclicker", 10, 5, 110, 30, ES_MULTILINE | ES_CENTER);

            SpeedEdit = NumberInput(hwnd, 10, 55, 50, 20, 0);
            IntervalEdit = NumberInput(hwnd, 95, 55, 50, 20, 0);
            CloseBtn = Button(hwnd, L"X", 150, 5, 20, 20, 0);
            MinimizeBtn = Button(hwnd, L"-", 125, 5, 20, 20, 0);
            SpeedLabel = Label(hwnd, L"Speed", 10, 40, 70, 15, 0);
            CPSLabel = Label(hwnd, L"CPS", 65, 58, 25, 15, 0);
            IntervalLabel = Label(hwnd, L"Interval", 95, 40, 70, 15, 0);
            UsLabel = Label(hwnd, L"us", 150, 58, 25, 15, 0);

            ToggleCheck = CheckBox(hwnd, L"Toggle Mode", 45, 85, 90, 20, 0);

            Group = GroupBox(hwnd, L"Rapid-fire key", 10, 110, 160, 120);

            LeftRadio = RadioButton(hwnd, L"Mouse Left", 20, 130, 140, 20, 0);
            RightRadio = RadioButton(hwnd, L"Mouse Right", 20, 150, 140, 20, 0);
            CustomRadio = RadioButton(hwnd, L"Custom Key:", 20, 170, 140, 20, 0);
            CustomBtn = ToggleButton(hwnd, L"Enter", 20, 190, 140, 30, BS_PUSHBUTTON);

            CustomBtn.Toggle(0);
            KeybdRead(&CustomBtn, VK_RETURN);
            SendMessage(LeftRadio.GetHandle(), BM_SETCHECK, BST_CHECKED, 0);

            ActivateLabel = Label(hwnd, L"Activation Key:", 20, 235, 140, 15, 0);
            ActivateBtn = ToggleButton(hwnd, L"NUMPAD0", 20, 255, 140, 30, BS_PUSHBUTTON);

            KeybdRead(&ActivateBtn, VK_NUMPAD0);

            StartBtn = ToggleButton(hwnd, L"Start", 30, 290, 120, 30, BS_PUSHBUTTON);
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
                    }else
                    if((HWND)lParam == CustomBtn.GetHandle())
                    {
                        if(CustomBtn.GetState() == BST_CHECKED)
                        {
                            Title.SetText(L"Select a key to rapid-fire");

                            SpeedEdit.Toggle(0);
                            IntervalEdit.Toggle(0);
                            LeftRadio.Toggle(0);
                            RightRadio.Toggle(0);
                            CustomRadio.Toggle(0);
                            ActivateBtn.Toggle(0);
                            StartBtn.Toggle(0);
                            ToggleCheck.Toggle(0);
                            SetFocus(hwnd);
                        }else
                        {
                            Title.SetText(L"Vroom-Vroom Autoclicker");

                            SpeedEdit.Toggle(1);
                            IntervalEdit.Toggle(1);
                            LeftRadio.Toggle(1);
                            RightRadio.Toggle(1);
                            CustomRadio.Toggle(1);
                            ActivateBtn.Toggle(1);
                            StartBtn.Toggle(1);
                            ToggleCheck.Toggle(1);
                        }
                    }else
                    if((HWND)lParam == ActivateBtn.GetHandle())
                    {
                        if(ActivateBtn.GetState() == BST_CHECKED)
                        {
                            Title.SetText(L"Select a hotkey to activate the rapid-fire");

                            SpeedEdit.Toggle(0);
                            IntervalEdit.Toggle(0);
                            LeftRadio.Toggle(0);
                            RightRadio.Toggle(0);
                            CustomRadio.Toggle(0);
                            CustomBtn.Toggle(0);
                            StartBtn.Toggle(0);
                            ToggleCheck.Toggle(0);
                            SetFocus(hwnd);
                        }else
                        {
                            Title.SetText(L"Vroom-Vroom Autoclicker");

                            SpeedEdit.Toggle(1);
                            IntervalEdit.Toggle(1);
                            LeftRadio.Toggle(1);
                            RightRadio.Toggle(1);
                            CustomRadio.Toggle(1);
                            StartBtn.Toggle(1);
                            ToggleCheck.Toggle(1);
                            if(CustomRadio.GetState() == BST_CHECKED)
                            {
                                CustomBtn.Toggle(1);
                            }
                        }
                    }
                }
                break;
                case EN_CHANGE:
                {
                    if((HWND)lParam == SpeedEdit.GetHandle())
                    {

                    }else
                    if((HWND)lParam == IntervalEdit.GetHandle())
                    {

                    }
                }
                break;
            }
        }
        break;
        case WM_KEYDOWN:
        {
            if(CustomBtn.GetState() == BST_CHECKED)
            {
                KeybdRead(&CustomBtn, (int)wParam);

                Title.SetText(L"Vroom-Vroom Autoclicker");

                SpeedEdit.Toggle(1);
                IntervalEdit.Toggle(1);
                LeftRadio.Toggle(1);
                RightRadio.Toggle(1);
                CustomRadio.Toggle(1);
                ActivateBtn.Toggle(1);
                StartBtn.Toggle(1);
                ToggleCheck.Toggle(1);
            }else
            if(ActivateBtn.GetState() == BST_CHECKED)
            {
                KeybdRead(&ActivateBtn, (int)wParam);

                Title.SetText(L"Vroom-Vroom Autoclicker");
                
                SpeedEdit.Toggle(1);
                IntervalEdit.Toggle(1);
                LeftRadio.Toggle(1);
                RightRadio.Toggle(1);
                CustomRadio.Toggle(1);
                StartBtn.Toggle(1);
                ToggleCheck.Toggle(1);
                if(CustomRadio.GetState() == BST_CHECKED)
                {
                    CustomBtn.Toggle(1);
                }
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
    //FreeConsole();

    MSG Msg;

    while(GetMessage(&Msg, hwnd, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return 0;
}