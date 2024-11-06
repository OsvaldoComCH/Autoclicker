#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <string>
#include "AlarmClock.hpp"

namespace wctrls
{

class Window
{
    protected:
    HWND hwnd;

    public:
    Window(){}

    Window(HWND Parent, const wchar_t * Class, const wchar_t * Text, int XPos, int YPos, int Width, int Height, int Style)
    {
        hwnd = CreateWindowEx
        (
            0, Class, Text,
            WS_CHILD | WS_VISIBLE | Style,
            XPos, YPos, Width, Height,
            Parent, NULL, (HINSTANCE)GetWindowLongPtr(Parent, GWLP_HINSTANCE), NULL
        );
        SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
    }

    void Toggle(bool State)
    {
        EnableWindow(hwnd, State);
    }

    void SetText(const wchar_t * Text)
    {
        SetWindowText(hwnd, Text);
    }

    void GetText(wchar_t * Buffer, int Size)
    {
        GetWindowText(hwnd, Buffer, Size);
    }

    HWND GetHandle()
    {
        return hwnd;
    }
};

class Button : public Window
{
    public:
    Button(){}

    Button(HWND Parent, const wchar_t * Text, int XPos, int YPos, int Width, int Height, int Style)
    : Window(Parent, L"BUTTON", Text, XPos, YPos, Width, Height, Style){}

    short GetState()
    {
        return (int)SendMessage(hwnd, BM_GETSTATE, 0, 0);
    }
    void SetState(short State)
    {
        SendMessage(hwnd, BM_SETSTATE, (WPARAM)State, 0);
    }
};

class GroupBox : public Button
{
    public:
    GroupBox(){}

    GroupBox(HWND Parent, int XPos, int YPos, int Width, int Height)
    : Button(Parent, NULL, XPos, YPos, Width, Height, BS_GROUPBOX){}

    GroupBox(HWND Parent, const wchar_t * Text, int XPos, int YPos, int Width, int Height)
    : Button(Parent, Text, XPos, YPos, Width, Height, BS_GROUPBOX){}
};

class RadioButton : public Button
{
    public:
    RadioButton(){}

    RadioButton(HWND Parent, const wchar_t * Text, int XPos, int YPos, int Width, int Height, int Style)
    : Button(Parent, Text, XPos, YPos, Width, Height, Style | BS_AUTORADIOBUTTON){}

    short GetState()
    {
        return (int)SendMessage(hwnd, BM_GETCHECK, 0, 0);
    }
    void SetState(short State)
    {
        SendMessage(hwnd, BM_SETCHECK, (WPARAM)State, 0);
    }
};

class CheckBox : public Button
{
    public:
    CheckBox(){}

    CheckBox(HWND Parent, const wchar_t * Text, int XPos, int YPos, int Width, int Height, int Style)
    : Button(Parent, Text, XPos, YPos, Width, Height, Style | BS_AUTOCHECKBOX){}

    short GetState()
    {
        return (int)SendMessage(hwnd, BM_GETCHECK, 0, 0);
    }
    void SetState(short State)
    {
        SendMessage(hwnd, BM_SETCHECK, (WPARAM)State, 0);
    }
};

class ToggleButton : public CheckBox
{
    public:
    ToggleButton(){}

    ToggleButton(HWND Parent, const wchar_t * Text, int XPos, int YPos, int Width, int Height, int Style)
    : CheckBox(Parent, Text, XPos, YPos, Width, Height, Style | BS_PUSHLIKE){}
};

class Edit : public Window
{
    public:
    Edit(){}

    Edit(HWND Parent, const wchar_t * Text, int XPos, int YPos, int Width, int Height, int Style)
    : Window(Parent, L"EDIT", Text, XPos, YPos, Width, Height, Style){}
};

class NumberInput : public Edit
{
    public:
    NumberInput(){}
    NumberInput(HWND Parent, const wchar_t * Text, int XPos, int YPos, int Width, int Height, int Style)
    : Edit(Parent, Text, XPos, YPos, Width, Height, Style | WS_DLGFRAME | ES_RIGHT | ES_NUMBER){}

    unsigned GetNumber()
    {
        wchar_t Text[11];
        GetWindowText(hwnd, Text, 11);
        unsigned Number;
        swscanf(Text, L"%u", &Number);
        return Number;
    }

    void SetNumber(unsigned Number)
    {
        wchar_t Text[11];
        swprintf(Text, L"%u", Number);
        SetWindowText(hwnd, Text);
    }
};

class Label : public Edit
{
    public:
    Label(){}

    Label(HWND Parent, const wchar_t * Text, int XPos, int YPos, int Width, int Height, int Style)
    : Edit(Parent, Text, XPos, YPos, Width, Height, Style | ES_READONLY){}
};

};