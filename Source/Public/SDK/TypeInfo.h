// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <stddef.h>

namespace Kyber
{
enum ClientState
{
    ClientState_WaitingForStaticBundleLoad, // 0

    ClientState_LoadProfileOptions, // 1
    ClientState_LostConnection,     // 2
    ClientState_WaitingForUnload,   // 3
    ClientState_Startup,            // 4
    ClientState_StartServer,        // 5

    ClientState_WaitingForLevel,       // 6
    ClientState_StartLoadingLevel,     // 7
    ClientState_WaitingForLevelLoaded, // 8
    ClientState_WaitingForLevelLink,   // 9
    ClientState_LevelLinked,           // 10
    ClientState_WaitingForGhosts,      // 11

    ClientState_Ingame,      // 12
    ClientState_LeaveIngame, // 13

    ClientState_ConnectToServer, // 14

    ClientState_ShuttingDown, // 15
    ClientState_Shutdown,     // 16

    ClientState_None, // 17
};

enum ChatChannel
{
    ChatChannel_All,
    ChatChannel_Team,
    ChatChannel_Partner,
    ChatChannel_Admin,
    ChatChannel_Game,
    ChatChannel_Spectator,
    ChatChannel_Private,
    ChatChannel_Count,
};


enum SecureReason // needs updating
{
    SecureReason_Ok,
    SecureReason_WrongProtocolVersion,
    SecureReason_WrongTitleVersion,
    SecureReason_ServerFull,
    SecureReason_KickedOut,
    SecureReason_Banned,
    SecureReason_GenericError,
    SecureReason_WrongPassword,
    SecureReason_KickedOutDemoOver,
    SecureReason_RankRestricted,
    SecureReason_ConfigurationNotAllowed,
    SecureReason_ServerReclaimed,
    SecureReason_MissingContent,
    SecureReason_NotVerified,
    SecureReason_TimedOut,
    SecureReason_ConnectFailed,
    SecureReason_NoReply,
    SecureReason_AcceptFailed,
    SecureReason_MismatchingContent,
    SecureReason_InteractivityTimeout,
    SecureReason_KickedFromQueue,
    SecureReason_TeamKills,
    SecureReason_KickedByAdmin,
    SecureReason_KickedViaPunkBuster,
    SecureReason_KickedOutServerFull,
    SecureReason_ESportsMatchStarting,
    SecureReason_NotInESportsRosters,
    SecureReason_ESportsMatchEnding,
    SecureReason_VirtualServerExpired,
    SecureReason_VirtualServerRecreate,
    SecureReason_ESportsTeamFull,
    SecureReason_ESportsMatchAborted,
    SecureReason_ESportsMatchWalkover,
    SecureReason_ESportsMatchWarmupTimedOut,
    SecureReason_NotAllowedToSpectate,
    SecureReason_NoSpectateSlotAvailable,
    SecureReason_InvalidSpectateJoin,
    SecureReason_KickedViaFairFight,
    SecureReason_KickedCommanderOnLeave,
    SecureReason_KickedCommanderAfterMutiny,
    SecureReason_ServerMaintenance,
    SecureReason_KickedViaShield,
};
class DataContainer
{
public:
    char _0x000[24]; // 0x0000
};
enum GamePlatform
{
    GamePlatform_Ps3,
    GamePlatform_Win32,
    GamePlatform_Xenon,
    GamePlatform_Gen4a,
    GamePlatform_Gen4b,
    GamePlatform_Android,
    GamePlatform_iOS,
    GamePlatform_OSX,
    GamePlatform_Linux,
    GamePlatform_Any,
    GamePlatform_Invalid,
    GamePlatformCount
};
class SystemSettings : public DataContainer
{
public:
    GamePlatform Platform; // 0x0018
    char _0x001C[4];       // 0x001C
};
enum LogFileCollisionMode
{
    LFCM_Overwrite, // 0x0000
    LFCM_Rotate,    // 0x0001
    LFCM_TimeStamp  // 0x0002
};
enum TeamId
{
    TeamNeutral, // 0x0000
    Team1,       // 0x0001
    Team2,       // 0x0002
    Team3,       // 0x0003
    Team4,       // 0x0004
    Team5,       // 0x0005
    Team6,       // 0x0006
    Team7,       // 0x0007
    Team8,       // 0x0008
    Team9,       // 0x0009
    Team10,      // 0x000A
    Team11,      // 0x000B
    Team12,      // 0x000C
    Team13,      // 0x000D
    Team14,      // 0x000E
    Team15,      // 0x000F
    Team16,      // 0x0010
    TeamIdCount  // 0x0011
};
class Asset : public DataContainer
{
public:
    char* Name; // 0x0018
};
enum LocalPlayerViewId
{
    LocalPlayerViewId_RootView,  // 0x0000
    LocalPlayerViewId_Secondary, // 0x0001
    LocalPlayerViewId_Custom1,   // 0x0002
    LocalPlayerViewId_Custom2,   // 0x0003
    LocalPlayerViewId_Custom3,   // 0x0004
    LocalPlayerViewId_Custom4,   // 0x0005
    LocalPlayerViewId_Count      // 0x0006
};
enum ViewDefinitionType
{
    ViewType_FullScreen,                  // 0x0000
    ViewType_AutoVerticalSplit,           // 0x0001
    ViewType_AutoFullHorizontalSplit,     // 0x0002
    ViewType_AutoOffsetedHorizontalSplit, // 0x0003
    ViewType_AutoQuadrant,                // 0x0004
    ViewType_Custom                       // 0x0005
};
enum InputActionMapSlot
{
    InputActionMapSlot_Undefined,
    InputActionMapSlot_Root1,
    InputActionMapSlot_Root2,
    InputActionMapSlot_Root3,
    InputActionMapSlot_Root4,
    InputActionMapSlot_Root5,
    InputActionMapSlot_Root6,
    InputActionMapSlot_Root7,
    InputActionMapSlot_Root8,
    InputActionMapSlot_Root9,
    InputActionMapSlot_Root10,
    InputActionMapSlot_Root11,
    InputActionMapSlot_Root12,
    InputActionMapSlot_Root13,
    InputActionMapSlot_Root14,
    InputActionMapSlot_Root15,
    InputActionMapSlot_Root16,
    InputActionMapSlot_Sticks1,
    InputActionMapSlot_Sticks2,
    InputActionMapSlot_Sticks3,
    InputActionMapSlot_Sticks4,
    InputActionMapSlot_Buttons1,
    InputActionMapSlot_Buttons2,
    InputActionMapSlot_Buttons3,
    InputActionMapSlot_Buttons4,
    InputActionMapSlot_Sticks1Buttons1,
    InputActionMapSlot_Sticks1Buttons2,
    InputActionMapSlot_Sticks1Buttons3,
    InputActionMapSlot_Sticks1Buttons4,
    InputActionMapSlot_Sticks2Buttons1,
    InputActionMapSlot_Sticks2Buttons2,
    InputActionMapSlot_Sticks2Buttons3,
    InputActionMapSlot_Sticks2Buttons4,
    InputActionMapSlot_Sticks3Buttons1,
    InputActionMapSlot_Sticks3Buttons2,
    InputActionMapSlot_Sticks3Buttons3,
    InputActionMapSlot_Sticks3Buttons4,
    InputActionMapSlot_Sticks4Buttons1,
    InputActionMapSlot_Sticks4Buttons2,
    InputActionMapSlot_Sticks4Buttons3,
    InputActionMapSlot_Sticks4Buttons4,
    InputActionMapSlot_Count
};
struct ViewDefinition
{
    LocalPlayerViewId ViewId;    // 0x0000
    ViewDefinitionType ViewType; // 0x0004
    uint32_t ScreenIndex;        // 0x0008
    float OffsetX;               // 0x000C
    float OffsetY;               // 0x0010
    float Width;                 // 0x0014
    float Height;                // 0x0018
    float FovScale;              // 0x001C
    bool NormalizedSize;         // 0x0020
    char _0x0021[3];             // 0x0021
};
enum LocalPlayerId
{
    LocalPlayerId_0, // 0x0000
    LocalPlayerId_1, // 0x0001
    LocalPlayerId_2, // 0x0002
    LocalPlayerId_3, // 0x0003
    LocalPlayerId_4, // 0x0004
    LocalPlayerId_5, // 0x0005
    LocalPlayerId_6, // 0x0006
    LocalPlayerId_7,
    LocalPlayerId_Invalid
};
enum SKU
{
    WW,
    EU,
    US,
    JPN,
    ROA,
    RU,
    EN
};
struct PlayerViewDefinition
{
    ViewDefinition* Views;       // 0x0000
    LocalPlayerId LocalPlayerId; // 0x0008
    char _0x000C[4];             // 0x000C
};
class GameModeViewDefinition : public Asset
{
public:
    char* GameModeName;                    // 0x0020
    PlayerViewDefinition* ViewDefinitions; // 0x0028
    float MaxVariableFps;
};
class EntryInputActionMapsData
{
public:
    int32_t ActionMapSettingsScheme;
    InputActionMapSlot DefaultInputActionMap;
    char pad[8];
    uint32_t Identifier;
};
class GameSettingsComponent : public Asset
{};
class VersionData : public Asset
{
public:
    char* disclaimer; // 0x0020
    int32_t Version;  // 0x0028
    //char _0x002C[4];  // 0x002C
    char* DateTime;   // 0x0030
    char* BranchId;   // 0x0038
    char* GameName;   // 0x0048
};
class SubWorldInclusionCriterion : public DataContainer
{
public:
    char* Name;     // 0x0020
    char** Options; // 0x0018
    
};
class SubWorldInclusion : public Asset
{
public:
    SubWorldInclusionCriterion** Criteria; // 0x0020
};
class SubViewData : public DataContainer
{};
class PlayerViewData : public DataContainer
{
public:
    SubViewData** SubViews; // 0x0018
};
class InputActionMappingsData
{
public:
    char pad[8];
};
class PlayerData : public Asset
{
public:
    PlayerViewData* PlayerView; // 0x0020
    EntryInputActionMapsData* InputConceptDefinition;
    InputActionMappingsData* InputMapping;
};
class GameTime : public SystemSettings
{
public:
    float JoinJobsTimeLimit;
    float YieldTimeLimit;
    int32_t YieldTime;
    float MaxSimFps;
    uint32_t ForceSimRate;
    float MaxVariableFps;
    float MaxInactiveVariableFps;
    float ForceDeltaTime;
    int32_t ForceDeltaTickCount;
    int32_t ClampTicks;
    float TimeScale;
    float DebugFrameDelay;
    int32_t FixedSleepTime;
    bool UseWaitableTimers;
    bool DoubleNoTickWait;
    bool VariableSimTickTimeEnable;
    bool ForceUseSleepTimer;
    bool ForceSinglePlayerFixedTick;
    bool ForceMultiplayerOneTickMin;
    bool EnableSinglePlayerFixedTick;
    bool AlternatingFramesSleepModeEnable;
    bool EnableServerJobInterpolation;
    bool EnableServerJobRunWhileGamePaused;
};
class GameSettings : public SystemSettings
{
public:
    uint32_t MaxPlayerCount;
    uint32_t MaxSpectatorCount;
    uint32_t MinPlayerCountElimination;
    LogFileCollisionMode LogFileCollisionMode;
    uint32_t LogFileRotationHistoryLength;
    char* Level;
    char* StartPoint;
    char* InstallationLevel;
    char* InstallationStartPoint;
    char* InstallationDefaultLayerInclusion;
    char _0x000[8];                          // InputConfiguration InputConfiguration;
    char* ActiveGameModeViewDefinition;
    GameModeViewDefinition** GameModeViewDefinitions;
    TeamId DefaultTeamId;
    uint32_t PS3ContentRatingAge;
    uint32_t LogHistory;
    VersionData* Version;
    SubWorldInclusion* LayerInclusionTable;
    char* DefaultLayerInclusion;
    float TimeBeforeSpawnIsAllowed;
    float LevelWarmUpTime;
    float TimeToWaitForQuitTaskCompletion;
    PlayerData* Player;
    char pad_test[8]; // DifficultyDatas DifficultySettings;
    uint32_t DifficultyIndex;
    SKU CurrentSKU;
    GameSettingsComponent GameSettingsComponents;
    bool LogFileEnable;
    bool ResourceRefreshAlwaysAllowed;
    bool SpawnMaxLocalPlayersOnStartup;
    bool UseSpeedBasedDetailedCollision;
    bool UseSingleWeaponSelector;
    bool AutoAimEnabled;
    bool HasUnlimitedAmmo;
    bool HasUnlimitedMags;
    bool RotateLogs;
    bool AdjustVehicleCenterOfMass;
    bool AimAssistEnabled;
    bool AimAssistUsePolynomials;
    bool ForceFreeStreaming;
    bool ForceDisableFreeStreaming;
    bool IsGodMode;
    bool IsJesusMode;
    bool IsJesusModeAi;
    bool GameAdministrationEnabled;
    bool AllowDestructionOutsideCombatArea;
    bool DefaultCameraInheritsFov;
    /*
    uint32_t MaxPlayerCount;                          // 0x0020
    char _0x0024[4];                                  // 0x0024
    uint32_t MaxSpectatorCount;
    char _0x005C[4];                                  // 0x
    uint32_t MinPlayerCountElimination;
    LogFileCollisionMode LogFileCollisionMode;        // 0x
    uint32_t LogFileRotationHistoryLength;            // 0x
    char* Level;                                      // 0x
    char* StartPoint;                                 // 0x
    char* InstallationLevel;                          // 0x
    char* InstallationStartPoint;                     // 0x
    char* InstallationDefaultLayerInclusion;          // 0x
    char* ActiveGameModeViewDefinition;               // 0x
    GameModeViewDefinition** GameModeViewDefinitions; // 0x
    TeamId DefaultTeamId;  
    VersionData* Version;                             // 0x0030
    char* DefaultLayerInclusion;                      // 0x
    float TimeToWaitForQuitTaskCompletion; 
    PlayerData* Player;                               // 0x
    int32_t DifficultyIndex;                          // 0x
    GameSettingsComponent** GameSettingsComponents;   // 0x
    bool LogFileEnable;                               // 0x00A8
    bool ResourceRefreshAlwaysAllowed;                // 0x00A9
    bool SpawnMaxLocalPlayersOnStartup;               // 0x00AA


    //SubWorldInclusion* SubWorldInclusion;             // 0x0038
                                      
    
    
    //char _0x0094[4];                                  // 0x0094
    //char _0x00AB[5];                                  // 0x00AB
    */
};
class NetworkSettings : public SystemSettings
{
public:
    uint32_t ProtocolVersion;
    char* TitleId;
    uint32_t ClientPort;
    uint32_t ServerPort;
    uint32_t MaxGhostCount;
    uint32_t GhostReserveAfterDeleteCount;
    uint32_t MaxClientToServerGhostCount;
    uint32_t ClientToServerGhostReserveAfterDeleteCount;
    uint32_t MaxClientCount;
    uint32_t MaxClientFrameSize;
    uint32_t MaxServerFrameSize;
    char* XlspAddress;
    char* ServerAddress;
    char* ClientConnectionDebugFilePrefix;
    char* ServerConnectionDebugFilePrefix;
    float SinglePlayerTimeNudgeGhostFrequencyFactor;
    float SinglePlayerTimeNudgeBias;
    float SinglePlayerTimeNudge;
    float SinglePlayerTimeNudgeSmoothingTime;
    float MemorySocketTimeNudgeGhostFrequencyFactor;
    float MemorySocketTimeNudgeBias;
    float MemorySocketTimeNudge;
    float MemorySocketTimeNudgeSmoothingTime;
    float LocalHostTimeNudgeGhostFrequencyFactor;
    float LocalHostTimeNudgeBias;
    float LocalHostTimeNudge;
    float LocalHostTimeNudgeSmoothingTime;
    float DefaultTimeNudgeGhostFrequencyFactor;
    float DefaultTimeNudgeBias;
    float DefaultTimeNudge;
    float DefaultTimeNudgeSmoothingTime;
    float ConnectTimeout;
    float PacketLossLogInterval;
    uint32_t MaxLocalPlayerCount;
    bool SinglePlayerAutomaticTimeNudge;
    bool MemorySocketAutomaticTimeNudge;
    bool LocalHostAutomaticTimeNudge;
    bool DefaultAutomaticTimeNudge;
    bool IncrementServerPortOnFail;
    bool UseFrameManager;
    bool TimeSyncEnabled;




    /*
    uint32_t ProtocolVersion;                        // 0x0020
    char _0x0024[4];                                 // 0x0024
    char* TitleId;                                   // 0x0028
    uint32_t ClientPort;                             // 0x0030
    uint32_t ServerPort;                             // 0x0034
    uint32_t MaxGhostCount;                          // 0x0038
    uint32_t GhostReserveAfterDeleteCount;
    uint32_t MaxClientToServerGhostCount;   
    uint32_t ClientToServerGhostReserveAfterDeleteCount;

    uint32_t MaxClientCount;                         // 0x0040
    uint32_t MaxClientFrameSize;                     // 0x0044
    uint32_t MaxServerFrameSize;                     // 0x0048
    char* XlspAddress;
    char* ServerAddress;                             // 0x0050
    char* ClientConnectionDebugFilePrefix;           // 0x0058
    char* ServerConnectionDebugFilePrefix;           // 0x0060
    float SinglePlayerTimeNudgeGhostFrequencyFactor;
    float SinglePlayerTimeNudgeBias;                 // 0x0068
    float SinglePlayerTimeNudge;                     // 0x006C
    float MemorySocketTimeNudgeGhostFrequencyFactor;
    float MemorySocketTimeNudgeBias;                 // 0x0070
    float MemorySocketTimeNudge;                     // 0x0074
    float LocalHostTimeNudgeGhostFrequencyFactor;
    float LocalHostTimeNudgeBias;                    // 0x0078
    float LocalHostTimeNudge;                        // 0x007C
    float LocalHostTimeNudgeSmoothingTime;
    float DefaultTimeNudgeGhostFrequencyFactor;
    float DefaultTimeNudgeBias;                      // 0x0080
    float DefaultTimeNudge;                          // 0x0084
    float DefaultTimeNudgeSmoothingTime;
    float ConnectTimeout;                            // 0x0088
    float PacketLossLogInterval;                     // 0x008C
    uint32_t MaxLocalPlayerCount;
    //uint32_t ValidLocalPlayersMask;                  // 0x0090
   // uint32_t DesiredLocalPlayersMask;                // 0x0094
    //uint32_t PersistentLocalPlayersMask;             // 0x0098
   // uint32_t SinglePlayerMaxMessagesPerNetworkFrame; // 0x009C
   // uint32_t MaxMessagesPerNetworkFrame;             // 0x00A0
    bool SinglePlayerAutomaticTimeNudge;             // 0x00A4
    bool MemorySocketAutomaticTimeNudge;             // 0x00A5
    bool LocalHostAutomaticTimeNudge;                // 0x00A6
    bool DefaultAutomaticTimeNudge;                  // 0x00A7
    bool IncrementServerPortOnFail;                  // 0x00A8
    bool UseFrameManager;                            // 0x00A9
    bool TimeSyncEnabled;                            // 0x00AA
    //bool MLUREnabled;                                // 0x00AB
    //char _0x00AC[4];                                 // 0x00AC*/
};
struct Guid
{
    uint32_t data1;
    uint16_t data2;
    uint16_t data3;
    uint8_t data4[8];
};
class ClientSettings : public SystemSettings
{
public:
    char _0x001[8];
    char _0x002[8];
    float JuiceDistanceThreshold;
    float JuiceTimeThreshold;
    float JuiceVehicleDistanceThreshold;
    float JuiceVehicleTimeThreshold;
    char* JuiceReportPerformanceCategory;
    char* ScreenshotFilename;
    char* ScreenshotSuffix;
    uint32_t Team;
    int32_t SpawnPointIndex;
    char* ServerIp;
    char* SecondaryServerIp;
    float AimScale;
    float MouseSensitivityMin;
    float MouseSensitivitySliderRange;
    float MouseSensitivityFactor;
    float MouseSensitivityPower;
    float XenonGamepadDeadZoneCenter;
    float XenonGamepadDeadZoneAxis;
    float XenonGamepadDeadZoneOffsetAxis;
    float PS3GamepadDeadZoneCenter;
    float PS3GamepadDeadZoneAxis;
    float PS3GamepadDeadZoneOffsetAxis;
    float PCGamepadDeadZoneCenter;
    float PCGamepadDeadZoneAxis;
    float PCGamepadDeadZoneOffsetAxis;
    float Gen4aGamepadDeadZoneCenter;
    float Gen4aGamepadDeadZoneAxis;
    float Gen4aGamepadDeadZoneOffsetAxis;
    float Gen4bGamepadDeadZoneCenter;
    float Gen4bGamepadDeadZoneAxis;
    float Gen4bGamepadDeadZoneOffsetAxis;
    float GamepadGuid;
    float ClientBulletsPerQuery;
    float IncomingFrequency;
    uint32_t IncomingRate;
    uint32_t OutgoingRate;
    float LoadingTimeout;
    float LoadedTimeout;
    float IngameTimeout;
    char* InstancePath;
    float FrameHistoryTimeWarnScale;
    bool IsSpectator;
    bool VsyncEnable;
    bool VsyncDuringLoadingScreenEnable;
    bool VisualFrameInterpolation;
    bool AllowVideoRecording;
    bool DebrisClusterEnabled;
    bool VegetationEnabled;
    bool ForceEnabled;
    bool WorldRenderEnabled;
    bool TerrainEnabled;
    bool WaterPhysicsEnabled;
    bool OvergrowthEnabled;
    bool EffectsEnabled;
    bool EmittersEnabled;
    bool AutoIncrementPadIndex;
    bool JuicePlayerReportPositionEnabled;
    bool JuiceReportPerformanceEnabled;
    bool JuiceReportMemoryEnabled;
    bool JuiceReportPerformanceOnlyOnSimFrames;
    bool LipSyncEnabled;
    bool OnDamageSpottingEnabled;
    bool IgnoreClientFireRateMultiplier;
    bool PauseGameOnStartUp;
    bool SkipFastLevelLoad;
    bool InputEnable;
    bool ScreenshotToFile;
    bool LoadMenu;
    bool DebugMenuOnLThumb;
    bool InvertFreeCamera;
    bool ScreenshotComparisonsEnable;
    bool RenderTags;
    bool InvertPitch;
    bool InvertPadPcRightStick;
    bool Scheme0FlipY;
    bool Scheme1FlipY;
    bool Scheme2FlipY;
    bool InvertYaw;
    bool ConsoleInputEmulation;
    bool InputLayoutChangeOnlyForPad;
    bool SampleInputEveryVisualFrame;
    bool SampleVisualFrameInputPostFrame;
    bool HavokVisualDebugger;
    bool HavokCaptureToFile;
    bool UseMouseAndKeyboardSystem;
    bool UseGlobalGamePadInput;
    bool ShowBuildId;
    bool ExtractPersistenceInformation;
    bool EnableRestTool;
    bool LocalVehicleSimulationEnabled;
    bool AsyncClientBulletEntity;
    bool AutoUnspawnDynamicObjects;
    bool QuitGameOnServerDisconnect;
    bool DebugTrackAllPlayersInSpawnScreen;
    bool UseOldKillerCamera;
    bool LuaOptionSetEnable;
    bool FrameInterpolationAudioUpdate;













    /*
    Guid AudioSystemGuid;               // 0x0020
    char* ScreenshotFilename;           // 0x0030
    char* ScreenshotSuffix;             // 0x0038
    uint32_t Team;                      // 0x0040
    int32_t SpawnPointIndex;            // 0x0044
    char* ServerIp;                     // 0x0048
    char* SecondaryServerIp;            // 0x0050
    float AimScale;                     // 0x0058
    float IncomingFrequency;            // 0x005C
    float OutgoingFrequency;            // 0x0060
    uint32_t IncomingRate;              // 0x0064
    uint32_t OutgoingRate;              // 0x0068
    float LoadingTimeout;               // 0x006C
    float LoadedTimeout;                // 0x0070
    float IngameTimeout;                // 0x0074
    float CpuQuality;                   // 0x0078
    char _0x007C[4];                    // 0x007C
    char* InstancePath;                 // 0x0080
    float FrameHistoryTimeWarnScale;    // 0x0088
    bool IsSpectator;                   // 0x008C
    bool AllowVideoRecording;           // 0x008D
    bool DebrisClusterEnabled;          // 0x008E
    bool VegetationEnabled;             // 0x008F
    bool ForceEnabled;                  // 0x0090
    bool WorldRenderEnabled;            // 0x0091
    bool TerrainEnabled;                // 0x0092
    bool WaterPhysicsEnabled;           // 0x0093
    bool OvergrowthEnabled;             // 0x0094
    bool EffectsEnabled;                // 0x0095
    bool AutoIncrementPadIndex;         // 0x0096
    bool LipSyncEnabled;                // 0x0097
    bool PauseGameOnStartUp;            // 0x0098
    bool SkipFastLevelLoad;             // 0x0099
    bool ScreenshotToFile;              // 0x009A
    bool LoadMenu;                      // 0x009B
    bool DebugMenuOnLThumb;             // 0x009C
    bool ScreenshotComparisonsEnable;   // 0x009D
    bool RenderTags;                    // 0x009E
    bool Scheme0FlipY;                  // 0x009F
    bool Scheme1FlipY;                  // 0x00A0
    bool Scheme2FlipY;                  // 0x00A1
    bool HavokVisualDebugger;           // 0x00A2
    bool HavokCaptureToFile;            // 0x00A3
    bool ShowBuildId;                   // 0x00A4
    bool ExtractPersistenceInformation; // 0x00A5
    bool EnableRestTool;                // 0x00A6
    bool LocalVehicleSimulationEnabled; // 0x00A7
    bool AutoUnspawnDynamicObjects;     // 0x00A8
    bool QuitGameOnServerDisconnect;    // 0x00A9
    bool LuaOptionSetEnable;            // 0x00AA
    bool FastExit;                      // 0x00AB
    char _0x00AC[4];                    // 0x00AC*/
};
class WSGameSettings : public SystemSettings
{
public:
    char* ReleaseVersionName;
    float RestartCooldown;
    float PostSpawnRestartCooldown;
    float NoInteractivityTimeoutTime;
    float NoInteractivityThresholdLimit;
    float PrivateMatchNoInteractivityTimeoutTime;
    float NoInteractivityTimeoutTimeFirstSpawn;
    float NoInteractivityPreKickWarning;
    uint32_t LobbyThreshold;
    uint32_t LobbyMaxTeamDiff;
    bool SupportsDebugging;
    bool Is2PlayersCoop;
    bool ForceThirdPerson;
    bool SkipLobby;
    bool SkipPreRound;
    bool ForcePrivateMatchLobby;
    bool UseDamageNumbers;
    bool StopEOR;
    bool UnlockAllHeroes;
    bool AlwaysAllowJoinAsSpectator;
    bool PCSplitScreen;


    /*
    char* ReleaseVersionName;                     // 0x0020
    float RestartCooldown;                        // 0x0028
    float PostSpawnRestartCooldown;               // 0x002C
    float NoInteractivityTimeoutTime;             // 0x0030
    float NoInteractivityThresholdLimit;          // 0x0034
    float PrivateMatchNoInteractivityTimeoutTime; // 0x0038
    int32_t PreferredTeam;                        // 0x003C
    char* PlayerName;                             // 0x0040
    int32_t LevelLightingOverride;                // 0x0048
    float ObjectiveDamageScale;                   // 0x004C
    int32_t TicketLossScale;                      // 0x0050
    int32_t LobbyThreshold;                       // 0x0054
    int32_t MaxTeamSizeDifference;                // 0x0058
    int32_t EventWelcomeTimer;                    // 0x005C
    int32_t MaximumBattlepoints;                  // 0x0060
    bool SupportsDebugging;                       // 0x0064
    bool Is2PlayersCoop;                          // 0x0065
    bool ForceThirdPerson;                        // 0x0066
    bool EnableMaxRegenerationLimit;              // 0x0067
    bool SkipLobby;                               // 0x0068
    bool DisableHeroDebugMenu;                    // 0x0069
    bool ForcePrivateMatchLobby;                  // 0x006A
    bool StopEOR;                                 // 0x006B
    bool DisableStartupFlow;                      // 0x006C
    bool AutoBalanceTeamsOnNeutral;               // 0x006D
    char _0x006E[2];                              // 0x006E*/
};
class CongestionControlSettings
{
    uint32_t LatencySampleCount;
    float LatencyMsMin;
    float LatencyMsMax;
    float PacketLossMin;
    float PacketLossMax;
    float LatencyIncrMsMin;
    float LatencyIncrMsMax;
    float ConnectionGradeBad;
    float ConnectionGradeGood;
    float ConnectionGradeBest;
    float FreqChangeStepScale;
    float FreqDistScaleMin;
    float FreqDistBiasMax;
    bool Enabled;
};
class ServerSettings : public SystemSettings
{
public:
    char* InstancePath;
    uint32_t RemoteControlPort;
    uint32_t MaxQueriesPerSecond;
    char* SavePoint;
    float TimeoutTime;
    uint32_t PlayerCountNeededForMultiplayer;
    char* DebugMenuClick;
    CongestionControlSettings CongestionCtrl;
    float LoadingTimeout;
    float IngameTimeout;
    float OutgoingFrequency;
    uint32_t IncomingRate;
    uint32_t OutgoingRate;
    char* Playlist;
    int32_t DedicatedServerCpu;
    uint32_t SaveGameVersion;
    char* ServerName;
    char* ServerPassword;
    float VehicleSpawnDelayModifier;
    float HumanHealthMultiplier;
    float RespawnTimeModifier;
    char* AdministrationPassword;
    char* RemoteAdministrationPort;
    bool QueryProviderEnabled;
    bool DebrisClusterEnabled;
    bool VegetationEnabled;
    bool WaterPhysicsEnabled;
    bool IsDesertingAllowed;
    bool IsRenderDamageEvents;
    bool RespawnOnDeathPosition;
    bool IsStatsEnabled;
    bool IsNetworkStatsEnabled;
    bool IsAiEnabled;
    bool IsDestructionEnabled;
    bool IsSoldierAnimationEnabled;
    bool IsSoldierDetailedCollisionEnabled;
    bool LoadSavePoint;
    bool DisableCutscenes;
    bool HavokVisualDebugger;
    bool HavokCaptureToFile;
    bool ShowTriggerDebugText;
    bool TimeoutGame;
    bool AILooksIntoCamera;
    bool DeathmatchDebugInfo;
    bool VehicleInteractionIgnoresSeeThrough;
    bool JobEnable;
    bool ThreadingEnable;
    bool DrawActivePhysicsObjects;
    bool IsRanked;
    bool UnlockResolver;
    bool ScoringLogEnabled;
    bool InstantUpdateEnabled;
    bool ForcePlaylist;
    bool AutoUnspawnBangers;
    bool RegulatedAIThrottle;
    bool EnableAnimationCulling;
    bool FallBackToSquadSpawn;
    bool SaveGameUseProfileSaves;
    bool VehicleSpawnAllowed;
    bool AdministrationEnabled;
    bool AdministrationLogEnabled;
    bool AdministrationTimeStampLogNames;
    bool AdministrationEventsEnabled;
    bool AdministrationServerNameRestricted;
};
class SyncedGameSettings : public SystemSettings
{
public:
    uint32_t DifficultyIndex;
    float BulletDamageModifier;
    float MaxAllowedLatency;
    float FrameHistoryTimeMax;
    float FrameHistoryTime;
    uint32_t MoveManagerOutgoingFrequency;
    uint32_t MaxCorrectionUpdateCount;
    bool DisableToggleEntryCamera;
    bool DisableRegenerateHealth;
    bool EnableFriendlyFire;
    bool AllowClientSideDamageArbitration;
};
} // namespace Kyber