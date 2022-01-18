#include <windows.h>
#include <iostream>

//was auch immer das ist
HINSTANCE hInstance = ::GetModuleHandle(NULL);

//hookfunktion definieren
LRESULT WINAPI KeyboardCallback(int nCode, WPARAM wParam, LPARAM lParam);

//hook an low level keyboard binden, ruft callbackfunktio auf
HHOOK keyboard_hook;

//strct das info über lowlevel keybaordinput enthält
KBDLLHOOKSTRUCT kbdStruct;

bool suicide = false;


int main()
{
    keyboard_hook = SetWindowsHookExA(WH_KEYBOARD_LL, KeyboardCallback, hInstance, 0);

    //windows message
    MSG msg;
    while(GetMessage(&msg, 0, 0, 0))
    {
        if(suicide == true)
        {
            return 0;
        }
    }
    return 0;
}

LRESULT WINAPI KeyboardCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    //zeichen empfangen
    if(nCode >= 0)
    {
        //ka warum hier auto
        auto kbdStruct = *((KBDLLHOOKSTRUCT*) lParam);
        DWORD wVirtualKey = kbdStruct.vkCode;

        if(kbdStruct.vkCode == VK_F1)
        {
            std::cout << "F1 was pressed, unhooking and terminating process!\n";
            suicide = true;
            return UnhookWindowsHookEx(keyboard_hook);
        }
        std::cout << wVirtualKey;
        std::cout << "\n";
    }

    //std::cout << "Hi!\n";

    return CallNextHookEx( NULL, nCode, wParam, lParam );
}