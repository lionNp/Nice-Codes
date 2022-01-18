#include <windows.h>
#include <iostream>

//good to know: wenn inputs in den input stream injected werden, dann werden auslesbare flags gesetzt

//was auch immer das ist
HINSTANCE hInstanceKeyboard = ::GetModuleHandle(NULL);
HINSTANCE hInstanceMouse = ::GetModuleHandle(NULL);

//hookfunktion definieren
LRESULT WINAPI KeyboardCallback(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI MouseCallback(int nCode, WPARAM wParam, LPARAM lParam);

//hook an low level keyboard binden, ruft callbackfunktio auf
HHOOK keyboard_hook;
HHOOK mouse_hook;

//struct das info über lowlevel keybaordinput enthält
KBDLLHOOKSTRUCT kbdStruct;

//struct das info über lowlevel mouseinput enthält
MSLLHOOKSTRUCT msllStruct;

bool suicide = false;


int main()
{
    //priorität des threads erhöhen, sonst buggt der maushandler aus
    HANDLE current_thread = GetCurrentThread();
    bool stat = SetThreadPriority(current_thread, THREAD_PRIORITY_ABOVE_NORMAL);
    switch(stat)
    {
        case true:
            std::cout << "raising of priority succeeded\n";
            break;
        case false:
            std::cout << "raising of priority failed\n";
            break;
    }

    keyboard_hook = SetWindowsHookExA(WH_KEYBOARD_LL, KeyboardCallback, hInstanceKeyboard, 0);
    mouse_hook = SetWindowsHookExA(WH_MOUSE_LL, MouseCallback, hInstanceMouse, 0);

    //windows message
    MSG msg;
    while(GetMessage(&msg, 0, 0, 0))
    {
        if(suicide == true)
        {
            return 0;
        }
        printf("msg recvd\n");
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


        switch(wParam)
        {
            case WM_KEYDOWN:
                if(kbdStruct.vkCode == VK_F1)
                {
                    std::cout << "F1 was pressed, unhooking and terminating process!\n";
                    suicide = true;
                    return UnhookWindowsHookEx(keyboard_hook);
                }
                std::cout << wVirtualKey;
                std::cout << "\n";
                break;

            case WM_IME_KEYUP:
                std::cout << "some key up\n";
                break;
        }
    }

    //std::cout << "Hi!\n";

    //return CallNextHookEx(NULL, nCode, wParam, lParam );
    return (long long int) NULL;
}

LRESULT WINAPI MouseCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    if(nCode == 0)
    {
        auto msllStruct = *((MSLLHOOKSTRUCT*) lParam);
        POINT coords = msllStruct.pt;
        LONG x = coords.x;
        LONG y = coords.y;

        switch(wParam)
        {
            case WM_LBUTTONDOWN:
                std::cout << "mouse1 down\n";
                break;

            case WM_LBUTTONUP:
                std::cout << "mouse1 up\n";
                break;

            default:
                std::cout << "x: " << x << " y: " << y << "\n";
                break;
        }
    }

    //return CallNextHookEx(NULL, nCode, wParam, lParam );
    return (long long int) NULL;
}