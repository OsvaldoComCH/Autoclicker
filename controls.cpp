#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <string>

class Button
{
    private:
    HWND hwnd;

    public:
    Button(){}

    Button(HWND Parent, const wchar_t * Text, int XPos, int YPos, int Width, int Height, int Style)
    {
        HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(Parent, GWLP_HINSTANCE);
        hwnd = CreateWindowEx
        (
            0, L"BUTTON", Text,
            WS_CHILD | WS_VISIBLE | Style,
            XPos, YPos, Width, Height,
            Parent, NULL, hInstance, NULL
        );
    }

    Button(HWND Parent, const wchar_t * Text, int XPos, int YPos, int Width, int Height)
    {
        Button(Parent, Text, XPos, YPos, Width, Height, BS_DEFPUSHBUTTON);
    }

    int GetState()
    {
        return (int)SendMessage(hwnd, BM_GETSTATE, 0, 0);
    }

    HWND GetHandle()
    {
        return hwnd;
    }
};

class GroupBox : public Button
{
    public:
    GroupBox(){}

    GroupBox(HWND Parent, int XPos, int YPos, int Width, int Height)
    : Button(Parent, NULL, XPos, YPos, Width, Height, BS_GROUPBOX){}
};

class RadioButton : public Button
{
    public:
    RadioButton(){}

    RadioButton(HWND Parent, const wchar_t * Text, int XPos, int YPos, int Width, int Height)
    : Button(Parent, Text, XPos, YPos, Width, Height, BS_AUTORADIOBUTTON){}
};

class Edit
{
    private:
    HWND hwnd;

    public:
    Edit(){}

    Edit(HWND Parent, const wchar_t * Text, int XPos, int YPos, int Width, int Height)
    {
        HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(Parent, GWLP_HINSTANCE);
        hwnd = CreateWindowEx
        (
            0, L"EDIT", NULL,
            WS_CHILD | WS_VISIBLE | WS_DLGFRAME | ES_NUMBER | ES_RIGHT,
            XPos, YPos, Width, Height,
            Parent, NULL, hInstance, NULL
        );
    }

    unsigned long GetNumber()
    {
        wchar_t Text[11];
        GetWindowText(hwnd, Text, 11);
        return std::stoul(Text, nullptr);
    }

    HWND GetHandle()
    {
        return hwnd;
    }
};

class Label
{
    private:
    int XPos, YPos, Length;
    wchar_t * Text;

    public:
    Label(){}

    Label(int x, int y, wchar_t * Text, int Length)
    {
        this->XPos = x;
        this->YPos = y;
        this->Length = Length;
        this->Text = Text;
    }

    void Print(HDC hdc)
    {
        TextOut(hdc, XPos, YPos, Text, Length);
    }
};