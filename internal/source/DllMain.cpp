#include <Windows.h>

#include "java/java.hpp"

DWORD WINAPI Main(LPVOID lpvReserved) {
    auto hinstDLL = static_cast<HINSTANCE>(lpvReserved);

    java->init();

    FreeLibraryAndExitThread(hinstDLL, 0);
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    DisableThreadLibraryCalls(hinstDLL);

    if (fdwReason == DLL_PROCESS_ATTACH) {
        HANDLE mainThread = CreateThread(0, 0, Main, hinstDLL, 0, 0);

        if (!mainThread) {
            return FALSE;
        }
        else {
            CloseHandle(mainThread);
            return TRUE;
        }
    }
}