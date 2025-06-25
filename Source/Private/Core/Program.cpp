// Copyright BattleDash. All Rights Reserved.

#include <Core/Program.h>

#include <Base/Version.h>
#include <Base/Log.h>
#include <Render/Renderer.h>
#include <Utilities/ErrorUtils.h>
#include <Utilities/PlatformUtils.h>
#include <Utilities/MemoryUtils.h>
#include <Hook/HookManager.h>
#include <SDK/SDK.h>
#include <Network/SocketManager.h>
#include <MinHook/MinHook.h>

#include <Windows.h>
#include <cstdio>
#include <chrono>
#include <thread>

#define OFFSET_CLIENT_STATE_CHANGE HOOK_OFFSET(0x143A95BB0)
#define OFFSET_GET_SETTINGS_OBJECT HOOK_OFFSET(0x143363D80)
#define OFFSET_SETTINGS_CTR HOOK_OFFSET(0x143363EE0)

Kyber::Program* g_program;

namespace Kyber
{
Program::Program(HMODULE module)
    : m_module(module)
    , m_console(nullptr)
    , m_server(nullptr)
    , m_clientState(ClientState_None)
    , m_joining(false)
{
    InitializePatches();
    KYBER_LOG(LogLevel::Info, "Initialized Game Patches");

    if (g_program || MH_Initialize() != MH_OK)
    {
        ErrorUtils::ThrowException("Initialization failed. Please restart Battlefront and try again!");
    }

    // Open a console
    AllocConsole();
    FILE* pFile;
    freopen_s(&pFile, "CONOUT$", "w", stdout);

    // ANSI Colors
    HANDLE stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode;
    GetConsoleMode(stdoutHandle, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(stdoutHandle, dwMode);
    SetConsoleTitleA(("Auric v" + KYBER_VERSION).c_str());
    
    // This is for "safe" starting. If I hook functions too early, the game will crash or will force a sign in that always fails 
    // Game patches are different, they don't do that. I'm required to make patches to startup functions for console commands
    new std::thread([this]() {
        for (int i = 5; i > 0; --i)
        {
            std::cout << "\rInitialization starting in " << i << "... " << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        std::cout << "\r[Kyber-Release] [Info]                                                        \n";
        this->InitializationThread();
    });

    KYBER_LOG(LogLevel::Info, " ____           ___       ___            _    ");
    KYBER_LOG(LogLevel::Info, "|  __| ___  __ |_. | ___ | . | ____ -__ | |_   __");
    KYBER_LOG(LogLevel::Info, "| |__ | .'|| _| _| || . ||  _|| . ||   ||  _||_ -| ");
    KYBER_LOG(LogLevel::Info, "|____||__,||_| |__//|___||_|  |__,||_|_||_|  |___|");
}

Program::~Program()
{
    KYBER_LOG(LogLevel::Info, "Destroying Kyber");
    HookManager::RemoveHooks();
    delete m_server;
    delete m_console;
    delete g_renderer;
}

DWORD WINAPI Program::InitializationThread()
{
    KYBER_LOG(LogLevel::Info, "Starting");
    InitializeGameHooks();
    KYBER_LOG(LogLevel::Warning, "Special Thanks to BattleDash")

    g_renderer = new Renderer();
    m_server = new Server();
    m_console = new Console();

    KYBER_LOG(LogLevel::Info, "Initialized Auric v" << KYBER_VERSION);
    KYBER_LOG(LogLevel::Warning, "Press [INSERT] on your Keyboard to use Auric!");

    while (1)
    {
        if (GetAsyncKeyState(VK_END) & 1)
        {
            KYBER_LOG(LogLevel::Info, "Ejecting Auric");
            FreeLibrary(m_module);
            delete this;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    return 0;
}

HookTemplate program_hook_offsets[] = {
    { OFFSET_CLIENT_STATE_CHANGE, ClientStateChangeHk },
    { OFFSET_GET_SETTINGS_OBJECT, GetSettingsObjectHk },
    { OFFSET_SETTINGS_CTR, LookupSettingsObjectHk}
};

void Program::InitializePatches()
{
    BYTE alwaysTruePatch[6] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
    MemoryUtils::Patch((void*)0x143338021, alwaysTruePatch, sizeof(alwaysTruePatch));
    MemoryUtils::Patch((void*)0x143362261, alwaysTruePatch, sizeof(alwaysTruePatch));

    BYTE alwaysFalsePatch[2] = { 0xEB, 0x0F };
    MemoryUtils::Patch((void*)0x1432F28C6, alwaysFalsePatch, sizeof(alwaysFalsePatch));
}

void Program::InitializeGameHooks()
{
    for (HookTemplate& hook : program_hook_offsets)
    {
        HookManager::CreateHook(hook.offset, hook.hook);
    }
    Hook::ApplyQueuedActions();
}

__int64 ClientStateChangeHk(__int64 inst, ClientState currentClientState, ClientState lastClientState)
{
    static const auto trampoline = HookManager::Call(ClientStateChangeHk);

    g_program->m_clientState = currentClientState;
    g_program->m_server->m_isFirstLaunch = false; //Fixes UI that's setup in ServerWindow.cpp

    KYBER_LOG(LogLevel::Debug, "Client state changed to " << currentClientState);
    Server* server = g_program->m_server;

    if (currentClientState == ClientState_Startup)
    {
        if (server->m_running)
        {
            server->Stop();

            GameSettings* gameSettings = Settings<GameSettings>("Game");
            gameSettings->Level = "Levels/FrontEnd/FrontEnd";
            gameSettings->DefaultLayerInclusion = "";
        }
        else
        {
            if (!g_program->m_joining)
            {
                Settings<ClientSettings>("Client")->ServerIp = "";
            }
            else
            {
                g_program->m_joining = false;
            }
        }
    }
    else if (currentClientState == ClientState_Ingame && server->m_running)
    {
        server->InitializeGameSettings();
    }
    return trampoline(inst, currentClientState, lastClientState);
}

__int64 LookupSettingsObjectHk(__int64 inst, __int64 typeInfo)
{
    static const auto trampoline = HookManager::Call(LookupSettingsObjectHk);
    return trampoline(inst, typeInfo);
}

__int64 GetSettingsObjectHk(__int64 inst, const char* identifier)
{
    static const auto trampoline = HookManager::Call(GetSettingsObjectHk);
    return trampoline(inst, identifier);
}
} // namespace Kyber