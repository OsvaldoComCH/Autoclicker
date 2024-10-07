#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

class Button
{
    public:
    HWND hwnd;
    bool State;

    Button(){}

    Button(HWND Parent, const wchar_t * Text, int XPos, int YPos, int Width, int Height)
    {
        HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(Parent, GWLP_HINSTANCE);
        hwnd = CreateWindowEx
        (
            0, L"BUTTON", Text,
            WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            XPos, YPos, Width, Height,
            Parent, NULL, hInstance, NULL
        );
    }

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
}