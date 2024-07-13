// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include "Java.h"
#include "Cheat.h"
#include "iostream"
#include <thread>
#include <chrono>
#include "GUI.h"
#include "Hook.h"


void __stdcall MainThread(HINSTANCE instance)
{
    if (Hook::init())
        goto _shutdown;

    while (!GetAsyncKeyState(VK_END))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }

_shutdown:
    Hook::shutdown();
    FreeLibrary(instance);
}

void initialise()
{
    jsize count;

    if (JNI_GetCreatedJavaVMs(&ct.vm, 1, &count) != JNI_OK || count == 0)
        return;

    jint rest = ct.vm->GetEnv((void**)&ct.env, JNI_VERSION_1_6);

    if (rest == JNI_EDETACHED)
        rest = ct.vm->AttachCurrentThread((void**)&ct.env, nullptr);

    if (ct.env != nullptr)
        runModules();

}

bool __stdcall DllMain(HINSTANCE instance, DWORD reason, LPVOID p_reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
        freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);

        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)initialise, 0, 0, 0);

        DisableThreadLibraryCalls(instance);

        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

        if (static std::thread main_thread([instance] { MainThread(instance); }); main_thread.joinable())
            main_thread.detach();
    }
    else if (reason == DLL_PROCESS_DETACH)
    {

        FreeConsole();
        fclose(stdout);
    }

    return true;
}
