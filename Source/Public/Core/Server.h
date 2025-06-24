// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Network/SocketManager.h>
#include <Base/Log.h>
#include <SDK/SDK.h>
#include <SDK/TypeInfo.h>
#include <SDK/Funcs.h>

#include <Windows.h>
#include <string> 

namespace Kyber
{

class Server
{
public:
    Server();
    ~Server();

    DWORD WINAPI PortForwardingThread();
    void InitializeGameHooks();
    void EnableGameHooks();
    void DisableGameHooks();
    void InitializeGamePatches();
    void InitializeGameSettings();
    void ClientPlayerManagerCtr();
    void Start(const char* level, const char* mode, int maxPlayers);
    void Stop();

    void SetPlayerTeam(ServerPlayer* player, int teamId)
    {
        return ServerConnection_SetPlayerTeam(player, teamId);
    }

    ServerGameContext* GetServerGameContext2()
    {
        return *reinterpret_cast<ServerGameContext**>(0x142C20A00);
    }

    __int64 GetServerGameContext()
    {
        return *reinterpret_cast<__int64*>(0x142C20A00);
    }

    void KickPlayer(ServerPlayer* player, char* reason, bool sendKickedMessage)
    {
        __int64 serverPeer = *reinterpret_cast<__int64*>(GetServerGameContext() + 0x70);
        __int64 serverConnection = ServerPeer_ConnectionForPlayer(serverPeer, player);
        ServerConnection_KickPlayer(serverConnection, SecureReason_KickedByAdmin, std::string(reason));

        if (sendKickedMessage)
        {
            std::string message = std::string(player->m_name) + " WAS KICKED BY ADMIN";
            SendServerMessage_Send(*reinterpret_cast<__int64*>(0x142CE2948), ChatChannel_Game, message.c_str(), player);
        }

        KYBER_LOG(LogLevel::Info, player->m_name << " was kicked [" << reason << "]");
    }

    void LoadLevel(ServerLoadLevelStruct a1)
    {
        LoadLevel_Setup(a1);
    }

    //Networking
    SocketManager* m_socketManager;
    ISocket* m_natClient;

    //Players
    ServerPlayerManager* m_ServerPlayerManager;
    ClientPlayerManager* m_ClientPlayerManager;
    
    //Server
    ServerSpawnOverrides m_serverSpawnOverrides;
    SocketSpawnInfo m_socketSpawnInfo;
    std::vector<MapRotation*> m_mapList;

    //Program
    __int64 m_serverInstance;
    bool m_running;
    bool m_hooksRemoved;
    bool m_isFirstLaunch;
};
} // namespace Kyber