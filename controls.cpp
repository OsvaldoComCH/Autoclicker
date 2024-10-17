#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <string>

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

    constexpr HWND GetHandle()
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

    int GetState()
    {
        return (int)SendMessage(hwnd, BM_GETSTATE, 0, 0);
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
    : Button(Parent, Text, XPos, YPos, Width, Height, BS_AUTORADIOBUTTON | Style){}
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
    NumberInput(HWND Parent, int XPos, int YPos, int Width, int Height, int Style)
    : Edit(Parent, NULL, XPos, YPos, Width, Height, Style | WS_DLGFRAME | ES_RIGHT | ES_NUMBER){}

    unsigned long GetNumber()
    {
        wchar_t Text[11];
        GetWindowText(hwnd, Text, 11);
        return std::stoul(Text, nullptr);
    }
};

class Label : public Edit
{
    public:
    Label(){}

    Label(HWND Parent, const wchar_t * Text, int XPos, int YPos, int Width, int Height, int Style)
    : Edit(Parent, Text, XPos, YPos, Width, Height, Style | ES_READONLY)
    {
        HideCaret(hwnd);
    }
};

};