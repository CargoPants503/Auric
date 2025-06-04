// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Core/Server.h>
#include <SDK/TypeInfo.h>
#include <API/APIService.h>

#include <Windows.h>

#define OFFSET_GLOBAL_CLIENT 0x142B817E0
#define OFFSET_GLOBAL_SETTINGS_MANAGER 0x142A4EA00
#define OFFSET_GET_CLIENT_INSTANCE 0x143B9F260

namespace Kyber
{
__int64 ClientStateChangeHk(__int64 a1, ClientState currentClientState, ClientState lastClientState);
__int64 GetSettingsObjectHk(__int64 inst, const char* identifier);
__int64 LookupSettingsObjectHk(__int64 inst, __int64 typeInfo);

class Program
{
public:
    Program(HMODULE module);
    ~Program();

    DWORD WINAPI InitializationThread();
    void InitializePatches();
    void InitializeGameHooks();

    template<typename T>
    T* GetSettingsObject(const char* identifier)
    {
        return reinterpret_cast<T*>(GetSettingsObjectHk(*reinterpret_cast<__int64*>(OFFSET_GLOBAL_SETTINGS_MANAGER), identifier));
    }

    template<typename T>
    T* LookupSettingsObject(__int64 typeInfo)
    {
        return reinterpret_cast<T*>(LookupSettingsObjectHk(*reinterpret_cast<__int64*>(OFFSET_GLOBAL_SETTINGS_MANAGER), typeInfo));
    }


    __int64 ChangeClientState(ClientState currentClientState)
    {
        return ClientStateChangeHk(
            *reinterpret_cast<__int64*>(*reinterpret_cast<__int64*>(((__int64 (*)(void))OFFSET_GET_CLIENT_INSTANCE)() + 0x38) + 0x20),
            currentClientState, m_clientState);
    }

    HMODULE m_module;
    //APIService* m_api;
    Server* m_server;
    ClientState m_clientState;
    bool m_joining;
    bool m_threadStarted;
};

template<class T>
class Settings
{
public:
    Settings(const char* identifier)
    {
        m_settings = g_program->GetSettingsObject<T>(identifier);
    }

    inline T* operator->()
    {
        return m_settings;
    }
    inline const T* operator->() const
    {
        return m_settings;
    }
    inline operator T*()
    {
        return m_settings;
    }
    inline operator const T*() const
    {
        return m_settings;
    }

private:
    T* m_settings;
};
template<class T>
class SettingsLookup
{
public:
    SettingsLookup(__int64 typeInfo)
    {
        m_settings = g_program->LookupSettingsObject<T>(typeInfo);
    }

    inline T* operator->()
    {
        return m_settings;
    }
    inline const T* operator->() const
    {
        return m_settings;
    }
    inline operator T*()
    {
        return m_settings;
    }
    inline operator const T*() const
    {
        return m_settings;
    }

private:
    T* m_settings;
};
} // namespace Kyber

extern Kyber::Program* g_program;