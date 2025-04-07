// Copyright BattleDash. All Rights Reserved.

#define _WINSOCKAPI_
#include <Core/Server.h>

#include <Core/Program.h>
#include <Hook/HookManager.h>
#include <Base/Log.h>
#include <Utilities/ErrorUtils.h>
#include <Utilities/MemoryUtils.h>
#include <Utilities/PlatformUtils.h>

#include <SDK/TypeInfo.h>
#include <SDK/SDK.h>

#include <ws2tcpip.h>
#include <iomanip>
#include <iostream>
#include <minhook/MinHook.h>
#include <sstream>
#include <stdio.h>
#include <thread>

#define OFFSET_SERVER_CONSTRUCTOR HOOK_OFFSET(0x143C3D3C0)
#define OFFSET_SERVER_START HOOK_OFFSET(0x143C466F0)

#define OFFSET_SERVERPLAYER_SETTEAMID HOOK_OFFSET(0x143CBE6F0)
#define OFFSET_SERVERPLAYER_LEAVEINGAME HOOK_OFFSET(0x143CB6770)
#define OFFSET_SERVERPLAYER_DISCONNECT HOOK_OFFSET(0x143CB2040)
#define OFFSET_SERVERPEER_DELETECONNECTION HOOK_OFFSET(0x143D94660)
#define OFFSET_SERVERPEER_CONNECTIONFORPLAYER HOOK_OFFSET(0x143CD4180)

#define OFFSET_SERVERCONNECTION_DISCONNECT HOOK_OFFSET(0x143C772F0)
#define OFFSET_SERVERCONNECTION_KICKPLAYER HOOK_OFFSET(0x143C7F140)
#define OFFSET_SERVERCONNECTION_CREATEPLAYER HOOK_OFFSET(0x143C7FBA0)
#define OFFSET_SERVERPLAYERMANAGER_DELETEPLAYER HOOK_OFFSET(0x143CB1CB0)

#define OFFSET_APPLY_SETTINGS HOOK_OFFSET(0x14334AE20)
#define OFFSET_CLIENT_INIT_NETWORK HOOK_OFFSET(0x143A97630)
#define OFFSET_CLIENT_CONNECTTOADDRESS HOOK_OFFSET(0x143B136F0)

#define OFFSET_SERVER_PATCH 0x143A9C8BE
#define OFFSET_SERVER_PATCH2 HOOK_OFFSET(0x14450A9E0)

#define OFFSET_SERVERPLAYERMANAGER HOOK_OFFSET(0x143CACA00)
#define OFFSET_SERVERSENDMESSAGE HOOK_OFFSET(0x144483EF0)

#define OFFSET_LOADLEVEL HOOK_OFFSET(0x1445049A0)


namespace Kyber
{

Server::Server()
    : m_socketSpawnInfo(SocketSpawnInfo(false, "", ""))
    , m_socketManager(new SocketManager(ProtocolDirection::Clientbound, SocketSpawnInfo(false, "", "")))
    , m_natClient(nullptr)
    , m_ServerPlayerManager(nullptr)
    , m_ClientPlayerManager(nullptr)
    , m_running(false)
    , m_hooksRemoved(false)
    , m_serverInstance(0)
    , m_isFirstLaunch(true)
{
    //ConsoleInit();
    InitializeGameHooks();
    DisableGameHooks();
    InitializeGamePatches();
    // new std::thread(&Server::PortForwardingThread, this);
}

Server::~Server()
{
    KYBER_LOG(LogLevel::Debug, "Destroying Server");
}

// NAT Punch-Through using https://github.com/BattleDash/Kyber/blob/main/NATServer
DWORD WINAPI Server::PortForwardingThread()
{
    int port = 10001;
    while (!m_natClient)
    {
        m_natClient = m_socketManager->Listen((":" + std::to_string(port)).c_str(), false);
    }

    // My own hosted instance of Kyber/NATServer
    m_natClient->SetPeerAddress(SocketAddr("65.108.70.186", 10000));

    while (1)
    {
        if (this == nullptr || m_natClient == nullptr)
        {
            break;
        }
        uint8_t* buffer = new uint8_t[1600];
        int length = m_natClient->ReceiveFrom(buffer, 1600);
        if (length > 0)
        {
            KYBER_LOG(LogLevel::Debug, "Received packet: " << reinterpret_cast<char*>(buffer));
            if (m_running)
            {
                // Send an empty packet to the client that wants to connect, to make the router accept the connection
                ISocket* client = m_socketManager->m_sockets.back();
                client->SetPeerAddress(SocketAddr(reinterpret_cast<char*>(buffer), 25100));
                client->Send(buffer, 1);
                KYBER_LOG(LogLevel::Debug, "Sent NAT packet");
            }
        }
        // Keep alive
        m_natClient->Send(reinterpret_cast<uint8_t*>(" "), 1);
        delete[] buffer;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}



void Server::Start(const char* level, const char* mode, int maxPlayers)
{
    EnableGameHooks();
    
    KYBER_LOG(LogLevel::Debug, "set networkSettings")
    ClientSettings* clientSettings = Settings<ClientSettings>("Client");
    clientSettings->ServerIp = "";

    GameSettings* gameSettings = Settings<GameSettings>("Game");
    gameSettings->Level = const_cast<char*>(level);

    gameSettings->StartPoint = "Offline_WalkerAssault"; //For SinglePlayer Maps

    char* gameMode = new char[strlen(mode) + 11];
    strcpy_s(gameMode, strlen(mode) + 11, "GameMode=");
    strcat_s(gameMode, strlen(mode) + 11, mode);
    gameSettings->DefaultLayerInclusion = gameMode;
    
    g_program->ChangeClientState(ClientState_Startup);

    m_running = true;
    m_hooksRemoved = false;

    
}

void Kyber::Server::ClientPlayerManagerCtr()
{
    KYBER_LOG(LogLevel::Debug, "ClientGameContext: 0x" << std::hex << reinterpret_cast<uintptr_t>(ClientGameContext::Get()));

    ClientPlayerManager* playerManager = ClientGameContext::Get()->GetPlayerManager();

    g_program->m_server->m_ClientPlayerManager = reinterpret_cast<ClientPlayerManager*>(playerManager);
}

__int64 ServerCtorHk(__int64 inst, ServerSpawnInfo& info, SocketManager* socketManager)
{
    static const auto trampoline = HookManager::Call(ServerCtorHk);

    g_program->m_server->m_serverInstance = inst;
    info.isCoop = false;
    info.isLocalHost = false;

    return trampoline(inst, info, socketManager);
    ;
}

__int64 ServerStartHk(__int64 inst, ServerSpawnInfo* info, ServerSpawnOverrides* spawnOverrides)
{

    static const auto trampoline = HookManager::Call(ServerStartHk);
    Server* server = g_program->m_server;
    spawnOverrides->socketManager = (__int64)server->m_socketManager;
    return trampoline(inst, info, spawnOverrides);
}


__int64 __fastcall ServerPlayerManagerHk(__int64 inst, __int64 playerData, unsigned int maxPlayerCount, int maxSpectatorCount) {

    
    static const auto trampoline = HookManager::Call(ServerPlayerManagerHk);
    __int64 result = trampoline(inst, playerData, maxPlayerCount, maxSpectatorCount);

    g_program->m_server->m_ServerPlayerManager = reinterpret_cast<ServerPlayerManager*>(result);
    if (reinterpret_cast<ServerPlayerManager*>(result))
    {
        KYBER_LOG(LogLevel::Debug, "PlayerManager: 0x" << std::hex << reinterpret_cast<ServerPlayerManager*>(result));
    }
    return result;
}

__int64 __fastcall ClientPlayerManagerHk(__int64 inst, __int64 playerData, unsigned int maxPlayerCount)
{
    
    static const auto trampoline = HookManager::Call(ClientPlayerManagerHk);
    __int64 result = trampoline(inst, playerData, maxPlayerCount);
    return result;
}

bool ServerConnectionCreatePlayer(__int64 inst, NetworkCreateJoiningPlayerMessage* message) 
{
    static const auto trampoline = HookManager::Call(ServerConnectionCreatePlayer);

    std::string playerName = message->playerName;
    bool TEMP_isJoiningPlayerNotASpectator = true;
    if (playerName == "Nuuby4") 
    {
        TEMP_isJoiningPlayerNotASpectator = true;
    }
    if (TEMP_isJoiningPlayerNotASpectator)
    {
        KYBER_LOG(LogLevel::Info, message->playerName << " has joined.");
        return trampoline(inst, message);

    }
    else{
        message->isSpectator = true;
        KYBER_LOG(LogLevel::Info, message->playerName << " has joined as Spectator.");
        return trampoline(inst, message);
    }
        
}


__int64 SettingsManagerApplyHk(__int64 inst, __int64* a2, char* script, BYTE* a4)
{
    static const auto trampoline = HookManager::Call(SettingsManagerApplyHk);
    Server* server = g_program->m_server;
    if (server->m_running && !server->m_hooksRemoved)
    {
        server->m_hooksRemoved = true;
        server->DisableGameHooks();
    }
    KYBER_LOG(LogLevel::DebugPlusPlus, "SettingsManagerApplyHk(" << script << ")");
    if (strstr(script, "InstallationLevel"))
    {
        return 0;
    }
    return trampoline(inst, a2, script, a4);
}

bool ClientInitNetworkHk(__int64 inst, bool singleplayer, bool localhost, bool coop, bool hosted)
{
    static const auto trampoline = HookManager::Call(ClientInitNetworkHk);
    if (g_program->m_server->m_running || strlen(Settings<ClientSettings>("Client")->ServerIp) > 0)
    {
        printf("%p\n", inst);
        *reinterpret_cast<__int64*>(inst + 0xB8) =
            reinterpret_cast<__int64>(new SocketManagerCreator(g_program->m_server->m_socketSpawnInfo));
    }
    return trampoline(inst, singleplayer, localhost, coop, hosted);
}

void ClientConnectToAddressHk(__int64 inst, const char* ipAddress, const char* serverPassword)
{
    static const auto trampoline = HookManager::Call(ClientConnectToAddressHk);
    SocketSpawnInfo info = g_program->m_server->m_socketSpawnInfo;
    if (info.isProxied)
    {
        trampoline(inst, (std::string(info.proxyAddress) + ":25200").c_str(), serverPassword);
    }
    else
    {
        trampoline(inst, ipAddress, serverPassword);
    }
}



void ServerPlayerLeaveIngameHk(ServerPlayer* inst)
{
    static const auto trampoline = HookManager::Call(ServerPlayerLeaveIngameHk);
    KYBER_LOG(LogLevel::Debug, "ServerPlayerLeaveIngame called");
    trampoline(inst);
}

void ServerPlayerDisconnectHk(ServerPlayer* inst, __int64 reason, const std::string& reasonText)
{
    static const auto trampoline = HookManager::Call(ServerPlayerDisconnectHk);
    KYBER_LOG(LogLevel::Debug, "ServerPlayerDisconnect called 0x" << reason << " 0x" << reasonText.c_str());
    trampoline(inst, reason, reasonText);
}

void ServerPeerDeleteConnectionHk(__int64 inst, __int64 serverConnection, __int64 reason, char* reasonText)
{
    static const auto trampoline = HookManager::Call(ServerPeerDeleteConnectionHk);
    KYBER_LOG(LogLevel::Debug, "ServerPeerDeleteConnection called 0x" << reason << " " << reasonText);
    trampoline(inst, serverConnection, reason, reasonText);
}

__int64 ServerPeerConnectionForPlayerHk(__int64 inst, ServerPlayer* player)
{
    static const auto trampoline = HookManager::Call(ServerPeerConnectionForPlayerHk);
    return trampoline(inst, player);
}

void ServerConnectionDisconnectHk(__int64 inst, __int64 reason, char* reasonText)
{
    static const auto trampoline = HookManager::Call(ServerConnectionDisconnectHk);
    KYBER_LOG(LogLevel::Debug, "ServerConnectionDisconnect called 0x" << reason << " " << reasonText);
    trampoline(inst, reason, reasonText);
}

__int64 ServerPatch2Hk(__int64 inst) {
    return 3;
}

void ServerPlayerManagerDeletePlayerHk(ServerPlayerManager* inst, ServerPlayer* player)
{
    static const auto trampoline = HookManager::Call(ServerPlayerManagerDeletePlayerHk);
    KYBER_LOG(LogLevel::DebugPlusPlus, "ServerPlayerManagerDeletePlayer called");
    trampoline(inst, player);
}

void LoadLevelHk(ServerLoadLevelStruct a1)
{
    static const auto trampoline = HookManager::Call(LoadLevelHk);
    trampoline(a1);
}

void ServerPlayerSetTeamIdHk(ServerPlayer* inst, int teamId)
{
    static const auto trampoline = HookManager::Call(ServerPlayerSetTeamIdHk);
    // g_program->m_server->InitializeGamePatches2();
    KYBER_LOG(LogLevel::Debug, "Set " << std::string(inst->m_name) << "To Team " << teamId);
    trampoline(inst, teamId);
}
void ServerConnectionKickPlayerHk(__int64 inst, __int64 reason, const std::string& reasonText)
{
    static const auto trampoline = HookManager::Call(ServerConnectionKickPlayerHk);
    KYBER_LOG(LogLevel::Debug, "ServerConnectionKickPlayer called 0x" << reason << " " << reasonText.c_str());
    
    trampoline(inst, reason, reasonText.c_str());
}
void SendServerMessageHk(ServerPlayer* inst, ChatChannel channel, const char* message)
{
    static const auto trampoline = HookManager::Call(SendServerMessageHk);

    if (!(message && inst))
    {
        return;
    }

    KYBER_LOG(LogLevel::Debug, " a1: " << inst << " channel: " << channel << " message: " << message);

    return trampoline(inst, channel, message);
}
HookTemplate server_hook_offsets[] = {
    { OFFSET_SERVER_CONSTRUCTOR, ServerCtorHk },
    { OFFSET_SERVER_START, ServerStartHk },
    { OFFSET_SERVERPLAYER_SETTEAMID, ServerPlayerSetTeamIdHk },
    { OFFSET_SERVERPLAYER_LEAVEINGAME, ServerPlayerLeaveIngameHk },
    { OFFSET_SERVERPEER_DELETECONNECTION, ServerPeerDeleteConnectionHk },
    { OFFSET_SERVERPEER_CONNECTIONFORPLAYER, ServerPeerConnectionForPlayerHk },
    { OFFSET_SERVERPLAYER_DISCONNECT, ServerPlayerDisconnectHk },
    { OFFSET_SERVERCONNECTION_DISCONNECT, ServerConnectionDisconnectHk },
    { OFFSET_SERVERCONNECTION_KICKPLAYER, ServerConnectionKickPlayerHk },
    { OFFSET_SERVERSENDMESSAGE, SendServerMessageHk },
    { OFFSET_SERVERPLAYERMANAGER_DELETEPLAYER, ServerPlayerManagerDeletePlayerHk },
    { OFFSET_APPLY_SETTINGS, SettingsManagerApplyHk },
    { OFFSET_CLIENT_INIT_NETWORK, ClientInitNetworkHk },
    { OFFSET_CLIENT_CONNECTTOADDRESS, ClientConnectToAddressHk },
    { OFFSET_SERVER_PATCH2, ServerPatch2Hk},
    { OFFSET_SERVERPLAYERMANAGER, ServerPlayerManagerHk},
    { OFFSET_SERVERCONNECTION_CREATEPLAYER, ServerConnectionCreatePlayer },
    { OFFSET_LOADLEVEL, LoadLevelHk}
    
    
    /*,
    { OFFSET_CLIENTPLAYERMANAGER, ClientPlayerManagerHk}*/
    
};






void Server::InitializeGameHooks()
{
    for (HookTemplate& hook : server_hook_offsets)
    {
        HookManager::CreateHook(hook.offset, hook.hook);
    }
    HookManager::EnableHook(OFFSET_SERVERPLAYERMANAGER);
    Hook::ApplyQueuedActions();
    KYBER_LOG(LogLevel::Debug, "Initialized Server Hooks");
}

void Server::EnableGameHooks()
{
    HookManager::EnableHook(OFFSET_SERVER_CONSTRUCTOR);
    HookManager::EnableHook(OFFSET_SERVER_START);
    HookManager::EnableHook(OFFSET_SERVER_PATCH2);
    HookManager::EnableHook(HOOK_OFFSET(0x143B136F0)); // 0x143B136F0
    Hook::ApplyQueuedActions();
    KYBER_LOG(LogLevel::Debug, "Enabled Server Hooks");
}

void Server::DisableGameHooks()
{
    HookManager::DisableHook(OFFSET_SERVER_CONSTRUCTOR);
    HookManager::DisableHook(OFFSET_SERVER_START);
    HookManager::DisableHook(reinterpret_cast<void*>(0x143B136F0)); // 0x143B136F0
    Hook::ApplyQueuedActions();
    KYBER_LOG(LogLevel::Debug, "Disabled Server Hooks");
}

void Server::InitializeGamePatches()
{
    BYTE ptch[] = { 0xB9, 0x01, 0x00, 0x00, 0x00 };
    MemoryUtils::Patch((void*)OFFSET_SERVER_PATCH, (void*)ptch, sizeof(ptch));
    BYTE ptch2[] = { 0x90, 0x90 };
    MemoryUtils::Patch((void*)(OFFSET_SERVER_PATCH + 0x5), (void*)ptch2, sizeof(ptch2));

   

    HookManager::EnableHook(OFFSET_SERVERPLAYERMANAGER);
}

void Server::InitializeGamePatches2()
{
    BYTE ptch3[] = { 0x90, 0x90, 0x90, 0x90, 0x90 }; // NOP out the instruction
    //MemoryUtils::Patch((void*)OFFSET_INVINCIBILITY_TEST, (void*)ptch3, sizeof(ptch3));
}

void Server::InitializeGameSettings()
{
    WSGameSettings* wsSettings = Settings<WSGameSettings>("Whiteshark");
    GameTime* gameTimeSettings = Settings<GameTime>("GameTime");
    GameSettings* gameSettings = Settings<GameSettings>("Game");
    OnlineSettings* onlineSettings = Settings<OnlineSettings>("Online");
    gameTimeSettings->TimeScale = 1;
    wsSettings->ForcePrivateMatchLobby = true;
    wsSettings->NoInteractivityTimeoutTime = 600;
    wsSettings->SkipLobby = true;
    wsSettings->SkipPreRound = true;
    wsSettings->UnlockAllHeroes = true;
    wsSettings->PCSplitScreen = true;
    wsSettings->SupportsDebugging = true;
    wsSettings->LobbyMaxTeamDiff = 20;
    wsSettings->LobbyThreshold = 1;
    onlineSettings->MatchmakingScenario = "DevUltraQuick";
    onlineSettings->MatchmakingScenarioWithLevel = "DevUltraQuick";




    //KYBER_LOG(LogLevel::Debug, gameSettings->CurrentSKU)
    //wsSettings->AutoBalanceTeamsOnNeutral = true;

    //AutoPlayerSettings* aiSettings = Settings<AutoPlayerSettings>("AutoPlayers");
    //aiSettings->AllowSuicide = false;
}

void Server::Stop() 
{
    m_running = false;
    m_ServerPlayerManager = nullptr;
    m_ClientPlayerManager = nullptr;
    UDPSocket* socket = m_socketManager->m_sockets.back();
    if (socket != m_natClient)
    {
        m_socketManager->Close(socket);
        socket->Close();
    }
}
} // namespace Kyber
