// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <stddef.h>
#include <xmmintrin.h>

namespace Kyber
{
struct Color32
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    Color32(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {}
};
struct Vec2
{
    constexpr Vec2()
        : x(0.0f)
        , y(0.0f)
    {}

    constexpr Vec2(float _x, float _y)
        : x(_x)
        , y(_y)
    {}

    float x, y;
};
struct Vec3
{
    Vec3()
        : x(0)
        , y(0)
        , z(0)
    {}

    Vec3(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
    {}

    Vec3 operator+(const Vec3& other) const
    {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3 operator-(const Vec3& other) const
    {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    Vec3 operator*(const Vec3& other) const
    {
        return Vec3(x * other.x, y * other.y, z * other.z);
    }

    Vec3 operator*(float scalar) const
    {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    union
    {
        struct
        {
            float x, y, z;
            char _0x000C[4]; // 0x000C
        };

        __m128 simd;
    };

    std::string ToString() const
    {
        return "{" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "}";
    }
};
struct Tuple3f
{
    float x, y, z;
};
struct Tuple2f
{
    float x, y;
};
struct DebugRenderVertex
{
    Tuple3f pos;
    Color32 color;
    Tuple3f normal;
    uint32_t pad;
};
enum DebugGeometryType
{
    DebugGeometryType_Triangle3d,
    DebugGeometryType_Line3d,
    DebugGeometryType_Triangle2d,
    DebugGeometryType_Line2d,
    DebugGeometryType_Font2d,
    DebugGeometryType_TriangleStrip
};
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
enum BackendType
{
    Backend_Lan,
    Backend_Blaze,
    Backend_Peer,
    Backend_Local,
    Backend_Playground,
    Backend_Count_
};
enum OnlineEnvironment
{
    OnlineEnvironment_Development,
    OnlineEnvironment_Test,
    OnlineEnvironment_Certification,
    OnlineEnvironment_Production,
    OnlineEnvironment_Count,
};
enum LogLevelType
{
    LogLevel_Default,
    LogLevel_Fatal,
    LogLevel_Error,
    LogLevel_Warn,
    LogLevel_Info,
    LogLevel_Debug,
    LogLevel_Trace,
};
class OnlineSettings : public SystemSettings
{
public:
    BackendType Backend;
    BackendType PeerBackend;
    OnlineEnvironment Environment;
    char pad_0001[16]; // PointerRef<OnlineProviderAsset> Provider;
    // List<OnlinePlatformConfiguration> Platforms;
    char* ServiceNameOverride;
    LogLevelType LogLevel;
    int32_t BlazeLogLevel;
    int32_t DirtySockLogLevel;
    char pad_0002[16];
    // PointerRef<OnlineRichPresenceData> RichPresenceData;
    // PointerRef<> LicenseConfig;
    char* MatchmakingScenario;
    char* MatchmakingScenarioWithLevel;
    char* Region;
    char* Country;
    char* PingSite;
    char* MatchmakingToken;
    uint32_t NegativeUserCacheRefreshPeriod;
    char* ServerLoginEmail;
    char* ServerLoginPassword;
    char* ServerLoginPersonaName;
    int32_t BlazeServerConnectionTimeout;
    int32_t BlazeServerTimeout;
    int32_t BlazeClientConnectionTimeout;
    int32_t BlazeClientTimeout;
    int32_t PeerPort;
    uint32_t BlazeCachedUserRefreshInterval;
    int32_t DirtySockServerPacketQueueCapacity;
    uint32_t MinPlayerCapacity;
    uint32_t MaxPlayerCapacity;
    uint32_t GameQueueCapacity;
    bool AssertOnPresenceRequestFailures;
    bool ClientIsPresenceEnabled;
    bool ServerIsPresenceEnabled;
    bool IsSecure;
    bool EnableQoS;
    bool WaitForQoS;
    bool ServerIsReconfigurable;
    bool SupportHostMigration;
    bool ServerAllowAnyReputation;
    bool DirtySockVoipEnabled;
    bool MatchmakingRoleEnabled;
    bool EnableNucleusLtOverride;
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
enum QualityLevel
{
    QualityLevel_Low,
    QualityLevel_Medium,
    QualityLevel_High,
    QualityLevel_Ultra,
    QualityLevel_All,
    QualityLevel_Invalid,
};
enum LightTileDebugLightCountMode
{
    LightTileDebugLightCountMode_Total,
    LightTileDebugLightCountMode_Punctual,
    LightTileDebugLightCountMode_PunctualShadow,
    LightTileDebugLightCountMode_Area,
    LightTileDebugLightCountMode_AreaShadow,
    LightTileDebugLightCountMode_LocalIBL,
    LightTileDebugLightCountMode_LocalPR,
};
enum PostProcessAAMode
{
    PostProcessAAMode_None,
    PostProcessAAMode_FxaaLow,
    PostProcessAAMode_FxaaMedium,
    PostProcessAAMode_FxaaHigh,
    PostProcessAAMode_FxaaCompute,
    PostProcessAAMode_FxaaComputeExtreme,
    PostProcessAAMode_Smaa1x,
    PostProcessAAMode_SmaaT2x,
    PostProcessAAMode_TemporalAA,
};
enum ScaleResampleMode
{
    ScaleResampleMode_Point,
    ScaleResampleMode_Linear,
    ScaleResampleMode_Bicubic,
    ScaleResampleMode_Lanczos,
    ScaleResampleMode_LanczosSeparable,
    ScaleResampleMode_BicubicSharp,
    ScaleResampleMode_BicubicSharpSeparable,
};
enum SkyRenderMode
{
    SkyRenderMode_SkyBox,
    SkyRenderMode_PhysicallyBased,
};
enum SpotLightShadowmapTextureMode
{
    SpotLightShadowmapTextureMode_Normal,
    SpotLightShadowmapTextureMode_Array,
    SpotLightShadowmapTextureMode_Atlas,
};
struct QualityScalableInt
{
    int32_t Low;
    int32_t Medium;
    int32_t High;
    int32_t Ultra;
};
struct WorldRenderSettingsBase : DataContainer
{
    float CullScreenAreaScale;
    float MinShadowViewCoverage;
    Vec3 MotionBlurClearColor;
    Vec3 DynamicEnvmapDefaultPosition;
    float ShadowmapMinFov;
    float ShadowmapSizeZScale;
    uint32_t ShadowmapResolution;
    uint32_t ShadowmapResolutionMax;
    uint32_t ShadowmapQuality;
    float ShadowmapPoissonFilterScale;
    uint32_t ShadowmapSliceCount;
    float ShadowmapSliceSchemeWeight;
    float ShadowmapFirstSliceScale;
    float ShadowmapViewDistance;
    float ShadowmapExtrusionLength;
    float ForceShadowmapFirstSliceViewDistance;
    float CockpitShadowsExtrusionLength;
    float ShadowmapTransitionBlendAmount;
    float ShadowmapForegroundExtrusionLength;
    float ShadowmapForegroundSplitDistance;
    float ShadowmapForegroundSizeZScale;
    float ViewportMaskScale;
    float ViewportMaskInnerScale;
    int32_t SunPcssMaxSampleCount;
    int32_t SunPcssAdaptiveSampleIncrement;
    float MotionBlurScale;
    float MotionBlurFixedShutterTime;
    float MotionBlurMax;
    float MotionBlurRadialBlurMax;
    float MotionBlurNoiseScale;
    uint32_t MotionBlurQuality;
    uint32_t MotionBlurDebugMode;
    uint32_t MotionBlurMaxSampleCount;
    float ForceMotionBlurDepthCutoff;
    float ForceMotionBlurCutoffGradientScale;
    float MotionBlurDepthCheckThreshold;
    float MotionBlurDepthCheckMaxDistance;
    uint32_t MultisampleCount;
    uint32_t MultisampleQuality;
    int32_t OnlyShadowmapSlice;
    char padding[4]; // WorldViewMode ViewMode;
    uint32_t AdditionalHdrTargetInESRAM;
    int32_t DrawDebugBlurPyramidMipLevel;
    uint32_t DrawDebugBuffers;
    float HalfResDepthMinMaxDitherThreshold;
    uint32_t PhysicalSkyPrecisionHeight;
    uint32_t PhysicalSkyPrecisionView;
    uint32_t PhysicalSkyPrecisionSun;
    uint32_t PhysicalSkyScatteringOrders;
    uint32_t PhysicalSkyAerialPerspectiveTextureWidth;
    uint32_t PhysicalSkyAerialPerspectiveTextureHeight;
    uint32_t PhysicalSkyAerialPerspectiveTextureDepth;
    uint32_t PhysicalSkyScatteringEvalFrameCount;
    float PhysicalSkyAerialPerspectiveMaxDistance;
    float SkyEnvmapFilterWidth;
    uint32_t SkyEnvmapResolution;
    int32_t DrawDebugSkyEnvmapMipLevel;
    char padding2[4]; // MipmapFilterMode SkyEnvmapFilterMode;
    uint32_t SkyEnvmapSidesPerFrameCount;
    float SkyEnvmapUpdateCountThreshold;
    float SkyEnvmapUpdateValueThreshold;
    float DynamicEnvmapFilterWidth;
    int32_t DrawDebugDynamicEnvmapMipLevel;
    char padding3[4]; // MipmapFilterMode DynamicEnvmapFilterMode;
    uint32_t DynamicEnvmapSpecularConvolutionSampleCount;
    uint32_t DynamicEnvmapShadowmapResolution;
    int32_t DynamicEnvmapShadowmapFarPlane;
    int32_t DynamicEnvmapShadowmapShadowExtrusion;
    bool DeferredShadingEnable;
    bool ForwardOpaqueEnable;
    bool FullZPassEnable;
    bool TileMaterialClassificationEnable;
    bool ShadowmapsEnable;
    bool ShadowmapArrayEnable;
    bool TransparencyShadowmapsEnable;
    bool TransparencyShadowmapsHalfRes;
    bool ShadowmapFixedMovementEnable;
    bool ShadowmapFixedDepthEnable;
    bool ShadowmapViewDistanceScaleEnable;
    bool ShadowmapCullVolumeEnable;
    bool ShadowmapAdjustFarPlane;
    bool CockpitShadowsEnable;
    bool ShadowmapAccumEnable;
    bool ShadowmapAccumReuseEnable;
    bool ShadowmapAccumBilinearEnable;
    bool ShadowmapAccumStencilEnable;
    bool ShadowmapAccumStencil2Enable;
    bool ShadowmapTransitionBlendEnable;
    bool ShadowmapForegroundEnable;
    bool ShadowmapForegroundUseFirstPersonViewTransform;
    bool ShadowmapStereoSharedEnable;
    bool DrawListStereoSharedEnable;
    bool DxShadowmap16BitEnable;
    bool DxSpotLightShadowmap16BitEnable;
    bool DxDynamicEnvmapShadowmap16BitEnable;
    bool ApplyShadowmapsEnable;
    bool GenerateShadowmapsEnable;
    bool SimpleShadowmapsEnable;
    bool EmitterShadowingBlendToggle;
    bool EmitterShadowingManySamplesToggle;
    bool DxLinearDepth32BitFormatEnable;
    bool MotionBlurEnable;
    bool MotionBlurForceOn;
    bool MotionBlurOptimalStableVelocityFormula;
    bool MotionBlurPreciseStableVelocityFormula;
    bool MotionBlurStencilPassEnable;
    bool MotionBlurGeometryPassEnable;
    bool MotionBlurBackgroundPassEnable;
    bool MotionBlurCenteredEnable;
    bool MotionBlurHairPassEnable;
    bool DrawTransparent;
    bool DrawTransparentDecal;
    bool TransparentAfterMotionBlur;
    bool Enable;
    bool HdrEnable;
    bool LdrEnable;
    bool ReadOnlyDepthEnable;
    bool ConsoleRenderTargetPoolSharingEnable;
    bool FastHdrEnable;
    bool LinearDepthInESRAM;
    bool HalfResDepthResolveEnable;
    bool FinalPostEnable;
    bool OutputGammaCorrectionEnable;
    bool ScreenEffectEnable;
    bool DrawSolidBoundingBoxes;
    bool DrawLineBoundingBoxes;
    bool DrawBoundingSpheres;
    bool DrawFrustums;
    bool DrawLocalIBLFrustums;
    bool DrawDebugShadowmaps;
    bool DrawDebugSpotLightShadowmaps;
    bool DrawDebugSkyEnvmap;
    bool DrawDebugVelocityBuffer;
    bool DrawDebugZBufferEnable;
    bool DrawDebugHalfResEnvironment;
    bool DrawDebugDistortion;
    bool DrawDebugVisibleEntityTypes;
    bool DrawDebugSkyTextures;
    bool DrawDebugMarschnerTextures;
    bool DrawDebugDof;
    bool DrawDebugDofFullscreen;
    bool DrawDebugHalfResHdrTargets;
    bool DrawDebugHiZMinMaxBufferEnable;
    bool DrawDebugScreenSpaceRaytraceBucketsEnable;
    bool DrawDebugEmitterSunTransmittanceMaps;
    bool DrawDebugBlurPyramid;
    bool DrawDebugOcclusionZBuffer;
    bool DrawDebugLocalIBLOcclusionZBuffer;
    bool WireframeEnable;
    bool ZPassEnable;
    bool OccluderMeshZPrepassEnable;
    bool OccluderMeshZPrepassDrawEnable;
    bool OccluderMeshZPrepassDebugEnable;
    bool HalfResEnable;
    bool ForceFullResEnable;
    bool HalfResLensFlaresEnable;
    bool ForegroundEnable;
    bool ForegroundDepthClearEnable;
    bool ForegroundZPassEnable;
    bool ForegroundTransparentEnable;
    bool ThirdPersonFriendlySSREnable;
    bool MidgroundEnable;
    bool ExtraHalfResDepthForSSAO;
    bool BilateralHalfResCompositeEnable;
    bool HalfResDepthMinMaxDitherEnable;
    bool SkyLightingEnable;
    bool SkyRenderEnable;
    bool SkyDepthFogEnable;
    bool SkyHeightFogEnable;
    bool SkyForwardScatteringEnable;
    bool PhysicalSkyEnabled;
    bool PhysicalSkyForcePrecompute;
    bool TransparentFoggingEnable;
    bool DistortionEnable;
    bool DistortionHalfResEnable;
    bool Distortion8BitEnable;
    bool DistortionTilingEnable;
    bool StaticEnvmapEnable;
    bool CustomEnvmapEnable;
    bool CustomEnvmapMipmapClampEnable;
    bool SkyEnvmapEnable;
    bool SkyEnvmapMipmapGenEnable;
    bool SkyEnvmapUpdateEnable;
    bool SkyEnvmapForceUpdateEnable;
    bool SkyEnvmapUseFastHDR;
    bool SkyEnvmapUse32bitLatLongTexture;
    bool SkyEnvmapDebugColorEnable;
    bool DynamicEnvmapEnable;
    bool DynamicEnvmapMipmapGenEnable;
    bool DrawDebugDynamicEnvmap;
    bool DynamicEnvmapShadowmapEnable;
    bool DynamicEnvmapShadowmapFarPlaneOverride;
    bool DynamicEnvmapShadowmapShadowExtrusionOverride;
    bool DrawDebugDynamicEnvmapShadowmap;
    bool DrawDynamicEnvmapFrustums;
    bool HairCoverageEnable;
    bool SetupJobEnable;
    bool FinishSyncJobsFirstEnable;
    bool PrepareDispatchListJobEnable;
};
struct WorldRenderSettings : WorldRenderSettingsBase
{
    uint32_t GenericEntityMaxVisibleEntityCount;
    uint32_t DrawDebugGroundHeight;
    float DecalVolumeScale;
    uint32_t MaxLensFlaresPerFrame;
    QualityLevel LensFlaresQualityLevel;
    uint32_t GBufferLayout;
    uint32_t GBufferTestCount;
    float GBufferAlphaTestSimpleSmoothness;
    float GBufferForceSmoothness;
    float GBufferForceSpecularAlbedo;
    int32_t HierarchicalZJitterForceIndex;
    uint32_t OutdoorLightTileBatchCount;
    int32_t OnlyLightTileIndex;
    uint32_t EmitterSunTransmittanceMapResolution;
    uint32_t MaxDestructionVolumeCount;
    uint32_t MaxDecalVolumeCount;
    uint32_t LightTileCsAvgLightCountPerTile;
    float LightCullFrustumExpandDistance;
    LightTileDebugLightCountMode LightTileDebugLightMode;
    int32_t LightTileDebugColorMode;
    uint32_t DebugLightStatsLightCountHighwatermark;
    float LightLodFadeArea;
    float LightLodMinArea;
    float LightLodRadiusFactor;
    uint32_t OcclusionCullingWidth;
    uint32_t OcclusionCullingHeight;
    uint32_t OcclusionTriangleCount;
    uint32_t ShadowOcclusionCullingWidth;
    uint32_t ShadowOcclusionCullingHeight;
    uint32_t ShadowOcclusionTriangleCount;
    float FrustumSilhouetteCullingPadding;
    int32_t SubSurfaceScatteringSampleCount;
    float SubsurfaceBlurPixelRadiusCullThreshold;
    int32_t OnlyTileIndex;
    float PlanarReflectionViewScale;
    float PlanarReflectionConvolutionSampleClampThreshold;
    uint32_t PlanarReflectionConvolutionSampleCount;
    float PlanarReflectionCullFOV;
    float PlanarReflectionFarPlane;
    uint32_t DrawDebugPlanarReflectionMipLevel;
    uint32_t DrawDebugPlanarReflectionMode;
    float ReflectionLodScale;
    PostProcessAAMode PostProcessAntialiasingMode;
    uint32_t TemporalAAJitterCount;
    float TemporalAASharpness;
    float TemporalAAMinHistoryBlendFactor;
    float TemporalAAMaxHistoryBlendFactor;
    float TemporalAADisocclusionRejectionFactor;
    float TemporalAALumaContrastFactor;
    float TemporalAAMotionSharpeningFactor;
    float TemporalAAAntiflickerMultiplier;
    float TemporalAAAntiflickerInDistance;
    float TemporalAAAntiflickerOutDistance;
    uint32_t DrawDebugTemporalAAAccumulationCount;
    uint32_t DrawDebugTemporalAADebugMode;
    float DrawDebugTemporalAAMaxDistance;
    float TemporalAAResponsiveness;
    float TemporalAAAntiflickerStrength;
    uint32_t TemporalAAQuality;
    ScaleResampleMode RenderScaleResampleMode;
    QualityLevel SkyCelestialQuality;
    QualityScalableInt SkyCelestialMaxQuadCount;
    SkyRenderMode SkyRenderMode;
    float InterpupillaryDistance;
    uint32_t SpotLightShadowmapResolution;
    uint32_t SpotLightShadowmapQuality;
    float SpotLightShadowmapPoissonFilterScale;
    SpotLightShadowmapTextureMode SpotLightShadowmapTextureMode;
    float SpotLightShadowMaxAngle;
    float SpotLightShadowFadeOutRange;
    uint32_t MaxShadowCount;
    uint32_t MaxPunctualLightCount;
    uint32_t MaxPunctualShadowLightCount;
    uint32_t MaxAreaLightCount;
    uint32_t MaxAreaShadowLightCount;
    uint32_t MaxLocalReflectionVolumeCount;
    uint32_t MaxLocalPlanarReflectionCount;
    uint32_t MaxPunctualRectangularLightCount;
    QualityLevel PunctualLightShadowLevel;
    QualityLevel AreaLightShadowLevel;
    uint32_t LocalIBLMaxFaceCapture;
    uint32_t LocalIBLLightingUpdateCount;
    uint32_t LocalIBLRefreshDelayCount;
    float LocalIBLSunUpdateThreshold;
    uint32_t LocalIBLShadowmapSliceCount;
    uint32_t LocalIBLShadowmapResolution;
    uint32_t PBRLocalIBLAcquisitionWaitFrameCount;
    uint32_t PBRDiffuseConvolutionMipLevelOffset;
    uint32_t PBRSpecularConvolutionSampleCount;
    uint32_t PBRDebugSpecularConvolutionSampleCount;
    uint32_t LocalIBLResolution;
    float DrawDebugLocalIBLPreviewScale;
    uint32_t DrawDebugLocalIBLIndex;
    uint32_t DrawDebugLocalIBLMipLevel;
    uint32_t ContinuousLocalIBLIndex;
    uint32_t MaxLocalPlanarReflectionTargetCount;
    float PBRMaxIlluminanceValue;
    float DiffuseRangeSRGBMinLimitValue;
    float DiffuseRangeSRGBMinValue;
    float DiffuseRangeSRGBMaxValue;
    float DiffuseRangeSRGBMaxLimitValue;
    float VolumetricLightCascadeBaseVoxelSize;
    float VolumetricLightCascadeVoxelSizeCascadeFactor;
    uint32_t VolumetricLightCascadeResolution;
    float VolumetricDensityCascadeBaseVoxelSize;
    float VolumetricDensityCascadeVoxelSizeCascadeFactor;
    uint32_t VolumetricDensityCascadeResolution;
    float VolumetricLightingIncreaseTemporalSmoothingFactor;
    float VolumetricLightingDecreaseTemporalSmoothingFactor;
    uint32_t VolumetricShadowQuality;
    uint32_t VolumetricShadowmapResolution;
    uint32_t VolumetricShadowmapMaxCount;
    QualityLevel PunctualLightCastVolumetricShadowmapEnableLevel;
    QualityLevel AreaLightCastVolumetricShadowmapEnableLevel;
    uint32_t VolumetricParticlesInjectionMode;
    uint32_t DrawDebugVolumetricDensity;
    uint32_t DrawDebugVolumetricLight;
    float DrawGpuHistogramHDRMinEV;
    float DrawGpuHistogramHDRMaxEV;
    uint32_t DrawGpuHistogramBinCount;
    uint32_t NumberOfEntitiesPerPartition;
    int32_t ForceTemporalAAQuality;
    bool TestRenderingEnable;
    bool GenericEntityRendererEnable;
    bool ZBufferShadowTestEnable;
    bool DecalVolumeEnable;
    bool DrawDebugDecalVolumes;
    bool DrawDebugDestructionVolumes;
    bool LensFlaresEnable;
    bool DrawDebugLensFlareOccluders;
    bool DrawDebugLensFlares;
    bool LensFlareOcclusionEnable;
    bool CloudShadowEnable;
    bool OverrideDynamicAO;
    bool DrawDebugDynamicAO;
    bool FilmicEffectsEnable;
    bool EmissiveEnable;
    bool GBufferClearEnable;
    bool DxGBufferLight16BitEnable;
    bool DxGBufferNormal16BitEnable;
    bool DxGBufferRoughness16BitEnable;
    bool GBufferAlphaTestSimpleEnable;
    bool Gen4aEsramEnable;
    bool Gen4aHierarchicalZEsramEnable;
    bool Gen4aScreenSpaceRaytraceEsramEnable;
    bool HierarchicalZJitterEnable;
    bool SpecularLightingEnable;
    bool SkinLightingEnable;
    bool TranslucencyLightingEnable;
    bool TranslucencyAutoThicknessEnable;
    bool DynamicEnvmapLightingEnable;
    bool OutdoorLightEnable;
    bool LightStencilMethodEnable;
    bool LightVolumeMethodEnable;
    bool LightVolumeDepthTestEnable;
    bool OutdoorKeyLightEnable;
    bool OutdoorSkyLightEnable;
    bool OutdoorLightTilingEnable;
    bool OutdoorLightTileRenderEnable;
    bool OutdoorLightTileBlendEnable;
    bool OutdoorLightTileSimpleShaderEnable;
    bool EmitterSunTransmittanceMapEnable;
    bool RadiositySpotLightShadowCullingEnable;
    bool LightTileCombineOutdoorLightEnable;
    bool LightTileCsPathEnable;
    bool LightTileAsyncComputeCulling;
    bool LightTileMinMaxUseHTile;
    bool LightTileUseCullingHierarchy;
    bool LightTileUseDetailedGpuTimers;
    bool LightTileUseCsIndirectClears;
    bool DrawDebugLightStats;
    bool DrawDebugLightStatsForward;
    bool DrawDebugLightSources;
    bool DrawDebugLightShadowSources;
    bool DrawDebugLightShadowStats;
    bool DrawDebugGBuffer;
    bool DrawDebugMaterialInput;
    bool DrawDebugMaterialOutput;
    bool DrawDebugLightEmissiveSurface;
    bool UseNewLightCullEnable;
    bool LightCullEnable;
    bool LightOcclusionCullEnable;
    bool LightConeCullEnable;
    bool LocalIBLOcclusionCullingEnable;
    bool ShadowOcclusionCullingEnable;
    bool FrustumSilhouetteCullingEnable;
    bool SubSurfaceScatteringEnable;
    bool TranslucencyEnable;
    bool SplitLightingEnable;
    bool SubsurfaceBlurComputeEnable;
    bool SubsurfaceBlurQuadtreeTileGenEnable;
    bool OpaqueSortBySolutionEnable;
    bool MainOpaqueZPassEnable;
    bool PlanarReflectionEnable;
    bool PlanarReflectionFastHdrEnable;
    bool PlanarReflectionBlurEnable;
    bool PlanarReflectionConvolutionEnable;
    bool PlanarReflectionConvolutionRandomSamplesEnable;
    bool PlanarReflectionConvolutionPostFilterEnable;
    bool PlanarReflectionClippingEnable;
    bool DrawDebugPlanarReflection;
    bool DrawDebugPlanarReflectionCullFrustum;
    bool LocalPlanarReflectionConvolutionEnable;
    bool OverlayEnable;
    bool OverlayZTestEnable;
    bool OutlineEnable;
    bool SmaaVelocityReprojectionEnable;
    bool SmaaUseStencil;
    bool SmaaPredicatedThresholdingEnable;
    bool TemporalAAJitterUseCmj;
    bool TemporalAASmoothHistoryFiltering;
    bool TemporalAAAsyncCompute;
    bool DrawDebugTemporalAAEnable;
    bool TemporalAADofCocFilterEnable;
    bool TemporalAAHistorySharpeningEnable;
    bool RenderScaleResampleEnable;
    bool SkyCelestialEnable;
    bool FullscreenLensReflectionEnable;
    bool SpriteDOFBeforeMotionBlur;
    bool VrHmdLensDistortionEnable;
    bool VrHmdLateReprojectionEnable;
    bool SpotLightShadowmapEnable;
    bool PBRSupportOriginalLight;
    bool RadiosityShadowCullingEnable;
    bool PunctualLightsEnable;
    bool AreaLightsEnable;
    bool LocalReflectionEnable;
    bool TilePassPunctualLightsEnable;
    bool TilePassPunctualLightShadowEnable;
    bool TilePassAreaLightsEnable;
    bool TilePassAreaLightShadowEnable;
    bool TilePassLocalReflectionVolumeEnable;
    bool TilePassLocalPlanarReflectionEnable;
    bool SphereLightsEnable;
    bool PunctualSphereLightsEnable;
    bool SpotLightsEnable;
    bool PunctualSpotLightsEnable;
    bool TubeLightsEnable;
    bool PunctualTubeLightsEnable;
    bool RectangularLightsEnable;
    bool PunctualRectangularLightsEnable;
    bool LocalReflectionVolumeSphereEnable;
    bool LocalReflectionVolumeBoxEnable;
    bool LocalPlanarReflectionEnable;
    bool LocalIBLUpdateWithSkyEnable;
    bool LocalIBLUpdateWithEnlightenSkyBoxChange;
    bool LocalIBLSunSpecularOcclusionEnable;
    bool LocalIBLBoxCullingEnable;
    bool LocalIBLShadowmapFaceMerging;
    bool PBRLocalIBLFogEnable;
    bool PBRDrawDiffuseReference;
    bool PBRDrawSpecularReference;
    bool PBRDrawLocalIBLReference;
    bool PBRDrawDistantIBLReference;
    bool PBRDrawAreaLightReference;
    bool PBRConvolutionMISEnable;
    bool PBRConvolutionHighestMIPEnable;
    bool PBRConvolutionCubeArrayEnable;
    bool PBRConvolutionChainEnable;
    bool DrawDebugLocalIBLEnable;
    bool DrawDebugLocalIBLStatsEnable;
    bool DrawDebugLocalIBLShadowmaps;
    bool DrawDebugPreIntegratedFGTexture;
    bool DrawDebugReflectionState;
    bool DrawDebugProbeMirrorEnable;
    bool DrawDebugProbeDiffuseEnable;
    bool DrawDebugProbeScreenEnable;
    bool DrawDebugProbeScreenOnRight;
    bool ContinuousLocalIBLEnable;
    bool PBRConvolutionPrecomputedSampleEnable;
    bool PBRConvolutionComputeEnable;
    bool PBRConvolutionRandomRotationEnable;
    bool DrawDebugLocalPlanarReflections;
    bool EmitterQuadRenderingEnable;
    bool EmitterMeshRenderingEnable;
    bool EmitterPointLightsEnable;
    bool EmitterSpotLightsEnable;
    bool UseSSSProfileforOATS;
    bool DeterministicRenderingEnable;
    bool HdrNanInfRemovalEnable;
    bool HdrNanInfRemovalForceEnable;
    bool VolumetricRenderingEnable;
    bool VolumetricCascadePositionUpdateEnable;
    bool VolumetricLightingTemporalAAEnable;
    bool VolumetricLightingUpsamplePreviousCascade;
    bool VolumetricShadowSkipLowerMipSamples;
    bool VolumetricShadowCascadeBasedQuality;
    bool VolumetricShadowmapEnable;
    bool VolumetricParticlesDensityInjectionEnable;
    bool EmitterVolumetricLightingEnable;
    bool DrawDebugVolumetricCascadedVolumesEnable;
    bool DrawDebugVolumetricShadowMaps;
    bool DrawDebugVolumetricEmitterInjectingDensityEnable;
    bool LightShaftFastHdrEnable;
    bool DrawGpuHistogramEnable;
    bool DrawGpuHistogramRed;
    bool DrawGpuHistogramBlue;
    bool DrawGpuHistogramGreen;
    bool DrawGpuHistogramLuminance;
    bool DrawGpuHistogramHDRMode;
    bool EntityRendererPartitioningEnable;
    bool DrawDebugEntityRendererPartitions;
    bool VehicleEntityForegroundZPassEnable;
    bool SoldierRenderFirstPersonTransformEnable;
    bool SelectiveStaticModelEntityZPassEnable;
    bool AfterTAATransparentEnable;
    bool AfterTAAForegroundNoDepthEnable;
    bool VehicleEntityEnableMeshComponentCulling;
    bool ForceTemporalAAOff;
};
class NetworkSettings : public DataContainer
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

    static NetworkSettings* GetInstance()
    {
        return *reinterpret_cast<NetworkSettings**>(0x14281C858);
    }


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
struct GameRenderSettings : DataContainer
{
    //void* vtbl;
    uint32_t InactiveSkipFrameCount;
    float ResolutionScale;
    float ResolutionScaleMax;
    int32_t MantleEnable;
    float CameraCutMaxFrameTranslation;
    float NearPlane;
    float ViewDistance;
    float ForceFov;
    float FovMultiplier;
    float ForceOrthoViewSize;
    float EdgeModelScreenAreaScale;
    float EdgeModelViewDistance;
    int32_t EdgeModelForceLod;
    float EdgeModelLodScale;
    float StaticModelPartOcclusionMaxScreenArea;
    uint32_t StaticModelCullJobCount;
    uint32_t SplitScreenTestViewCount;
    uint32_t SplitScreenTestCase;
    float ForceBlurAmount;
    float ForceWorldFadeAmount;
    float StereoCrosshairMaxHitDepth;
    float StereoCrosshairRadius;
    float StereoCrosshairDampingFactor;
    uint32_t UIBlurTextureDivisor;
    uint32_t UIBlurFilter;
    float UIBlurDeviation;
    bool Enable;
    bool NullRendererEnable;
    bool JobEnable;
    bool BuildJobSyncEnable;
    bool DrawDebugDynamicTextureArrays;
    bool DrawDebugInfo;
    bool DrawScreenInfo;
    bool ResolutionScaleDynamicEnabled;
    bool Fullscreen;
    bool ForceVSyncEnable;
    bool MovieVSyncEnable;
    bool VSyncFlashTestEnable;
    bool OutputBrightnessTestEnable;
    bool GlEnable;
    bool Dx11Enable;
    bool Dx12Enable;
    bool BalsaEnable;
    bool Gen4bColorRemap;
    bool GpuTextureCompressorEnable;
    bool MeshWorldEnable;
    bool EmittersEnable;
    bool EntityRenderEnable;
    bool DebugRendererEnable;
    bool DebugRenderServiceEnable;
    bool InitialClearEnable;
    bool GpuProfilerEnable;
    bool ForceOrthoViewEnable;
    bool ForceSquareOrthoView;
    bool DestructionVolumeDrawEnable;
    bool EdgeModelsEnable;
    bool EdgeModelCastShadowsEnable;
    bool EdgeModelDepthBiasEnable;
    bool EdgeModelShadowDepthBiasEnable;
    bool EdgeModelUseMainLodEnable;
    bool EdgeModelUseLodBox;
    bool EdgeModelCullEnable;
    bool EdgeModelFrustumCullEnable;
    bool EdgeModelDrawBoxes;
    bool EdgeModelDrawStats;
    bool StaticModelEnable;
    bool StaticModelMeshesEnable;
    bool StaticModelZPassEnable;
    bool StaticModelPartCullEnable;
    bool StaticModelPartFrustumCullEnable;
    bool StaticModelPartOcclusionCullEnable;
    bool StaticModelPartShadowCullEnable;
    bool StaticModelDrawBoxes;
    bool StaticModelDrawStats;
    bool StaticModelCullSpuJobEnable;
    bool StaticModelSurfaceShaderTerrainAccessEnable;
    bool LockView;
    bool ResetLockedView;
    bool InfiniteProjectionMatrixEnable;
    bool SecondaryStreamingViewEnable;
    bool FadeEnable;
    bool FadeWaitingEnable;
    bool BlurEnable;
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