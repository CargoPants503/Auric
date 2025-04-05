// Copyright BattleDash. All Rights Reserved.

#pragma once
#include <Network/SocketManager.h>

//#include <EASTL/string.h>
#include <EASTL/fixed_vector.h>

#include <stddef.h>
#include <string>
#include <vector>

namespace Kyber
{
struct LevelSetup
{
    std::string name;
};
struct ServerSpawnOverrides
{
    LevelSetup* levelSetup;
    __int64 socketManager;
    __int64 connectionCreator;
    __int64 peerCreator;
};
class ServerPlayer
{
public:
    void* vtable;                     // 0x0000
    class PlayerData* m_data;         // 0x0008
    class MemoryArena* m_memoryArena; // 0x0010
    char* m_name;                     // 0x0018
    char pad_0020[20];                // 0x0020
    uint64_t m_id;
    bool m_isAIPlayer;  // 0x0038
    char pad_0039[31];  // 0x0039
    int32_t m_teamId;   // 0x0058
    char pad_005C[496]; // 0x005C

}; // Size: 0x024C



class EastlServerPlayerManager
{
public:
    char pad_0000[8];               // 0x0000
    class PlayerData* m_playerData; // 0x0008
    uint32_t m_maxPlayerCount;      // 0x0010
    uint32_t m_playerCountBitCount; // 0x0014
    uint32_t m_playerIdBitCount;    // 0x0018
    char pad_001C[628];             // 0x001C
    //ServerPlayer* m_players[64];
    eastl::fixed_vector<ServerPlayer*, 64> m_players; // 0x00C8

    // class ServerPlayer* m_players[64]; // 0x00F0 //0x290
    char pad_02F0[1276]; // 0x02F0 // Size: 0x07EC
};


class ServerPlayerManager
{
public:
    char pad_0000[8];                  // 0x0000
    class PlayerData* m_playerData;    // 0x0008
    uint32_t m_maxPlayerCount;         // 0x0010
    uint32_t m_playerCountBitCount;    // 0x0014
    uint32_t m_playerIdBitCount;       // 0x0018
    char pad_001C[628];                // 0x001C
    ServerPlayer* m_players[64];
    //eastl::fixed_vector<ServerPlayer*, 64> m_players; // 0x00C8

    //class ServerPlayer* m_players[64]; // 0x00F0 //0x290
    char pad_02F0[1276];               // 0x02F0 // Size: 0x07EC
};                                     // Size: 0x07EC
class ClientPlayerManager
{
public:
    char pad_0000[8];
    class PlayerData* m_playerData;
    uint32_t m_maxPlayerCount;      // 0x0010
    uint32_t m_playerCountBitCount; // 0x0014
    uint32_t m_playerIdBitCount;    // 0x0018
    char pad_001C[224];
    // Technically the players, spectators, have their own structure but they're similar enough that I can use the ServerPlayer
    ServerPlayer* m_players[64]; // 0x0100 
    ServerPlayer* m_spectators[64];
    ServerPlayer* m_localPlayers[64];
};
class ClientGameContext
{
public: 
    char pad_0000[56]; // 0x0000
    void* clientLevel; // 0x0038
    char pad_0040[40]; // 0x0040
    ClientPlayerManager* playerManager; //0x058

    ClientPlayerManager* GetPlayerManager()
    {
        if (this != nullptr && this->playerManager != nullptr)
        {
            return this->playerManager;
        }

        return nullptr;
    }

    static ClientGameContext* Get()
    {
        return *(ClientGameContext**)0x142AE8080;
    }
};
class OnlineId
{
public:
    uint64_t m_nativeData; // 0x0000
    char m_id[16];         // 0x0008
};
/*
class ClientPlayer
{
public:
    virtual void unk1(){};
    class PlayerData* m_data;         // 0x0008
    class MemoryArena* m_memoryArena; // 0x0010
    const char* m_name;               // 0x0018
    char pad_0020[24];                // 0x0020
    LocalPlayerId m_localPlayerId;
    uint32_t m_analogInputEnableMask;
    uint64_t m_digitalInputEnableMask;
    char pad_0048[16]; // 0x0048
    int32_t m_teamId;  // 0x0058
    char pad[4];
    OnlineId m_onlineId;
    char pad_005C[392];                               // 0x005C
    class AttachedControllable* attachedControllable; // 0x0200
    char pad_0208[8];                                 // 0x0208

    // Beware that this may not actually be a soldier entity.
    // Always check if the type equals "WSClientSoldierEntity"
    // before using fields specific to that type.
    class ClientSoldierEntity* controlledControllable; // 0x0210

    char pad_0218[16];                                // 0x0218
    class ClientCameraViewManager* cameraViewManager; // 0x0228
};
*/
class ServerGameContext
{
public:
    char pad_0000[104];
    EastlServerPlayerManager* m_eastlServerPlayerManager;
};


class MemoryArena
{
public:
    char pad_0000[136]; // 0x0000
};                      // Size: 0x0088

struct ServerSpawnInfo
{
    ServerSpawnInfo(LevelSetup& setup)
        : levelSetup(setup)
    {}

    void* fileSystem = nullptr;
    void* damageArbitrator = nullptr;
    ServerPlayerManager* playerManager = nullptr;
    LevelSetup& levelSetup;
    unsigned int tickFrequency = 0;
    bool isSinglePlayer = false;
    bool isLocalHost = false;
    bool isDedicated = false;
    bool isEncrypted = false;
    bool isCoop = false;
    bool isMenu = false;
    bool keepResources = false;
    void* saveData;
    void* serverCallbacks = nullptr;
    void* runtimeModules = nullptr;
};
struct PlayerData2
{
    void* returnAddress;                  // Offset 0x0000: Unknown pointer (return address)
    const uint32_t networkableGroupCount; // Offset 0x0004: Constant unsigned int
    uint32_t maxPlayerCount;              // Offset 0x0008: Maximum number of players
    uint32_t maxSpectatorCount;           // Offset 0x000C: Maximum number of spectators
};

struct SocketSpawnInfo
{
    SocketSpawnInfo(bool isProxied, const char* proxyAddress, const char* serverName)
        : isProxied(isProxied)
        , proxyAddress(proxyAddress)
        , serverName(serverName)
    {}

    bool isProxied;
    const char* proxyAddress;
    const char* serverName;
    const char* serverMode;
    const char* serverLevel;
};


} // namespace Kyber