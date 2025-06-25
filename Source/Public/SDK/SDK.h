// Copyright BattleDash. All Rights Reserved.

#pragma once
#include <EASTL/string.h>
#include <EASTL/fixed_vector.h>

#include <stddef.h>
#include <sstream>
#include <string>
#include <vector>

//Type Info Offsets
#define OFFSET_TYPEINFO_GAMESETTINGS 0x142FC5EC0
#define OFFSET_TYPEINFO_NETWORKSETTINGS 0x142FBF790
#define OFFSET_TYPEINFO_SYNCEDGAME 0x142FC5E60
#define OFFSET_TYPEINFO_WHITESHARK 0x1430574A0
#define OFFSET_TYPEINFO_WHITESHARKUI 0x14303E200
#define OFFSET_TYPEINFO_SERVERSETTINGS 0x142FBE7D0
#define OFFSET_TYPEINFO_CLIENTSETTINGS 0x142FCCC10
#define OFFSET_TYPEINFO_UISETTINGS 0x142FD47D0
#define OFFSET_TYPEINFO_GAMERENDERSETTINGS 0x142FE8D30
#define OFFSET_TYPEINFO_ONLINESETTINGS 0x142FFE600
#define OFFSET_TYPEINFO_ORIGINSETTINGS 0x142FFF7D0

namespace Kyber
{
class LevelSetup
{
public:
    void* vtable;
    char pad_0010[8];
    char* Name;
    char pad_0018[200];
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

    char pad_02F0[1276];

    ServerPlayer* GetPlayer(const char* name)
    {
        for (const auto& player : m_players)
        {
            if (player == nullptr)
                continue;

            if (std::strcmp(player->m_name, name) == 0)
                return player;
        }
        return nullptr;
    }
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
    // Technically the players, spectators, have their own struct but they're similar enough to where I can use the ServerPlayer
    ServerPlayer* m_players[64]; // 0x0100 
    ServerPlayer* m_spectators[64];
    ServerPlayer* m_localPlayers[64];
};

class NetworkCreateJoiningPlayerMessage
{
public:
    char pad_0000[72];
    char* playerName;
    bool isSpectator;
};

//All credit for TypeInfo goes to BattleDash
enum TypeCodeEnum : uint16_t
{
    kTypeCode_Void = 0,
    kTypeCode_DbObject = 1,
    kTypeCode_ValueType = 2,
    kTypeCode_Class = 3,
    kTypeCode_Array = 4,
    kTypeCode_CString = 7,
    kTypeCode_Enum = 8,
    kTypeCode_Boolean = 10,
    kTypeCode_Int8 = 11,
    kTypeCode_Uint8 = 12,
    kTypeCode_Int16 = 13,
    kTypeCode_Uint16 = 14,
    kTypeCode_Int32 = 15,
    kTypeCode_Uint32 = 16,
    kTypeCode_Int64 = 17,
    kTypeCode_Uint64 = 18,
    kTypeCode_Float32 = 19,
    kTypeCode_Float64 = 20,
};

struct TypeObject
{
    virtual class TypeInfo* getType() const = 0;

protected:
    virtual ~TypeObject() = default;
};

class MemberInfoData
{
public:
    char* name;     // 0x0000
    uint16_t flags; // 0x0008

    static const uint32_t kFlagIsBlittable = 1 << 15;

    bool IsBlittable() const
    {
        return (flags & kFlagIsBlittable) == kFlagIsBlittable;
    }
}; // Size: 0x000A

class TestList
{
public:
    char pad_0000[136]; // 0x0000
};

class ModuleInfo
{
public:
    char* moduleName;             // 0x0000
    class ModuleInfo* nextModule; // 0x0008
    class TestList* testList;     // 0x0010
};

class TypeInfoData : public MemberInfoData
{
public:
    uint16_t totalSize;            // 0x000A
    uint32_t guid;                 // 0x000C
    class ModuleInfo* module;      // 0x0010
    class TypeInfo* arrayTypeInfo; // 0x0018
    uint16_t alignment;            // 0x0020
    uint16_t fieldCount;           // 0x0022
    uint32_t signature;            // 0x0024
};

class TypeInfo
{
public:
    class TypeInfoData* typeInfoData; // 0x0000
    TypeInfo* next;

    char pad[0x28];
    // ClassInfo ONLY
    const TypeInfo* m_super;
    const TypeObject* m_defaultInstance;
    uint16_t m_classId;
    uint16_t m_lastClassId;
    // End - ClassInfo ONLY

    TypeCodeEnum getBasicType() const;
    const char* getName() const;

}; // Size: 0x0008

class Message : public TypeObject
{
public:
    const int category;
    const int type;
};

class OnlineId
{
public:
    uint64_t m_nativeData; // 0x0000
    char m_id[16];         // 0x0008
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

class ServerGameContext
{
public:
    char pad_0000[104];
    ServerPlayerManager* playerManager;
    __int64 serverPeer;

    static ServerGameContext* Get()
    {
        return *(ServerGameContext**)0x142C20A00;
    }
    
    ServerPlayerManager* GetPlayerManager()
    {
        if (this != nullptr && this->playerManager != nullptr)
        {
            return this->playerManager;
        }

        return nullptr;
    }
};

class MemoryArena
{
public:
    char pad_0000[136]; // 0x0000
};                      // Size: 0x0088

struct ServerSpawnInfo
{
    ServerSpawnInfo(LevelSetup* setup)
        : levelSetup(setup)
    {}

    void* fileSystem = nullptr;
    void* damageArbitrator = nullptr;
    ServerPlayerManager* playerManager = nullptr;
    LevelSetup* levelSetup;
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

class ServerLoadLevelStruct
{
public:
    char pad_0000[16];
    const char* level;
    const char* gameMode;
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

struct MapRotation
{
public:
    const char* Level;
    const char* GameMode;
    const char* Name;
};

} // namespace Kyber