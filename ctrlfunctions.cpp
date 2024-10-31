#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <cstring>
#include "controls.cpp"

void KeybdRead(wctrls::ToggleButton * Button, int KeyCode)
{
    Button->SetState(BST_UNCHECKED);
    /*
    if(KeyCode == VK_ESCAPE)
    {
        return;
    }else
    */
    if(KeyCode == VK_RETURN)
    {
        Button->SetText(L"ENTER");
    }else
    if(KeyCode == VK_TAB)
    {
        Button->SetText(L"TAB");
    }else
    if(KeyCode == VK_BACK)
    {
        Button->SetText(L"BACKSPACE");
    }else
    if(KeyCode == VK_SHIFT)
    {
        Button->SetText(L"SHIFT");
    }else
    if(KeyCode == VK_LEFT)
    {
        Button->SetText(L"LEFT");
    }else
    if(KeyCode == VK_UP)
    {
        Button->SetText(L"UP");
    }else
    if(KeyCode == VK_RIGHT)
    {
        Button->SetText(L"RIGHT");
    }else
    if(KeyCode == VK_DOWN)
    {
        Button->SetText(L"DOWN");
    }else
    if(KeyCode >= VK_NUMPAD0 && KeyCode <= VK_NUMPAD9)
    {
        wchar_t Text[8];
        swprintf(Text, L"NUMPAD%i", KeyCode - VK_NUMPAD0);
        Button->SetText(Text);
    }else
    {
        int Key = MapVirtualKeyEx(KeyCode, MAPVK_VK_TO_CHAR, GetKeyboardLayout(0));
        if(Key)
        {
            Button->SetText((wchar_t *) &Key);
        }else
        {
            return;
        }
    }
    Button->KeyCode = KeyCode;
}