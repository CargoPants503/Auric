// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Network/SocketManager.h>
#include <SDK/SDK.h>
#include <SDK/TypeInfo.h>

#include <Windows.h>
#include <string>

#define OFFSET_SERVERGAMECONTEXT_INSTANCE 0x142C20A00

#define OFFSET_NETWORK_THING 0x142FBF790

namespace Kyber
{

void ServerPlayerSetTeamIdHk(ServerPlayer* inst, int teamId);
void ServerPlayerLeaveIngameHk(ServerPlayer* inst);
void ServerPlayerDisconnectHk(ServerPlayer* inst, __int64 reason, const std::string& reasonText);
void ServerPeerDeleteConnectionHk(__int64 inst, __int64 serverConnection, __int64 reason, char* reasonText);
__int64 ServerPeerConnectionForPlayerHk(__int64 inst, ServerPlayer* player);
void ServerConnectionDisconnectHk(__int64 inst, __int64 reason, char* reasonText);
void ServerConnectionKickPlayerHk(__int64 inst, __int64 reason, const std::string& reasonText);
void SendServerMessageHk(ServerPlayer* inst, ChatChannel channel, const char* message);
void ServerPlayerManagerDeletePlayerHk(ServerPlayerManager* inst, ServerPlayer* player);
void CreatePlayerManager();
void LoadLevelHk(ServerLoadLevelStruct a1);





class Server
{
public:
    Server();
    ~Server();

    DWORD WINAPI PortForwardingThread();
    void InitializeGameHooks();
    void EnableGameHooks();
    void DisableGameHooks();
    //void ConsoleInit();
    void InitializeGamePatches();
    void InitializeGamePatches2();
    void InitializeGameSettings();
    void ClientPlayerManagerCtr();
    void Start(const char* level, const char* mode, int maxPlayers);
    void Stop();

    void SetPlayerTeam(ServerPlayer* player, int teamId)
    {
        return ServerPlayerSetTeamIdHk(player, teamId);
    }

    ServerGameContext* GetServerGameContext2()
    {
        return *reinterpret_cast<ServerGameContext**>(OFFSET_SERVERGAMECONTEXT_INSTANCE);
    }

    __int64 GetServerGameContext()
    {
        return *reinterpret_cast<__int64*>(OFFSET_SERVERGAMECONTEXT_INSTANCE);
    }

    void KickPlayer(ServerPlayer* player, char* reason)
    {
        __int64 serverPeer = *reinterpret_cast<__int64*>(GetServerGameContext() + 0x70);
        __int64 serverConnection = ServerPeerConnectionForPlayerHk(serverPeer, player);
        ServerConnectionKickPlayerHk(serverConnection, SecureReason_KickedByAdmin, std::string(reason));
    }

    void SendKickedMessage(ServerPlayer* inst, const char* name)
    {
        std::string message = std::string(name) + " WAS KICKED BY ADMIN";
        SendServerMessageHk(inst, ChatChannel_Game, message.c_str());

    }

    void BanPlayer(ServerPlayer* player, char* reason)
    {
        __int64 serverPeer = *reinterpret_cast<__int64*>(GetServerGameContext() + 0x70);
        __int64 serverConnection = ServerPeerConnectionForPlayerHk(serverPeer, player);
        ServerConnectionKickPlayerHk(serverConnection, SecureReason_KickedViaShield, std::string(reason));
    }
    void LoadLevel(ServerLoadLevelStruct a1)
    {
        LoadLevelHk(a1);
    }

    


    SocketManager* m_socketManager;
    ISocket* m_natClient; // ServerPlayerManager* m_playerManager;
    EastlServerPlayerManager* m_eastlServerPlayerManager;
    ServerPlayerManager* m_ServerPlayerManager;
    ClientPlayerManager* m_ClientPlayerManager;
    ServerSpawnOverrides m_serverSpawnOverrides;
    SocketSpawnInfo m_socketSpawnInfo;
    std::vector<MapRotation*> m_mapList;
    __int64 m_serverInstance;
    bool m_running;
    bool m_hooksRemoved;
        // the m_isFirstLaunch basically forces the ClientPlayerManager 
        // to be visible as soon as the game launches because the client 
        // state isn't set when is apart of controlling the visiblity
    bool m_isFirstLaunch;

};
} // namespace Kyber