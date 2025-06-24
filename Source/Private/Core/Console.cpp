#include <Core/Program.h>
#include <Hook/Func.h>
#include <iostream>
#include <Hook/HookManager.h>
#include <Core/Console.h>
#include <Base/Log.h>

namespace Kyber
{
TL_DECLARE_FUNC(0x14334B160, void, ConsoleRegistry_registerConsoleMethods, const char* groupName, ConsoleMethod* methods, int count);

void SetTeamCommand(ConsoleContext& cc)
{
    auto stream = cc.stream();
    std::string playerName;
    int team;
    stream >> playerName >> team;

    ServerPlayer* player = g_program->m_server->m_ServerPlayerManager->GetPlayer(playerName.c_str());

    if (player == nullptr)
    {
        cc << "Couldn't find player " << playerName;
        return;
    }

    g_program->m_server->SetPlayerTeam(player, team);
    cc << "Set " << playerName << " to team " << team;
    KYBER_LOG(LogLevel::Console, "Set " + playerName + " To Team " << team);
}

void LoadLevelCommand(ConsoleContext& cc)
{
    auto stream = cc.stream();
    std::string levelPath, gameMode;
    stream >> levelPath >> gameMode;
    if (levelPath.empty() || gameMode.empty())
        return;

    GameSettings* gameSettings = Settings<GameSettings>("Game");
    constexpr const char* kFrontendLevel = "Levels/FrontEnd/FrontEnd";

    if (std::strcmp(gameSettings->Level, kFrontendLevel) == 0)
    {
        cc << "Start a server first!\n";
        KYBER_LOG(LogLevel::Console, "LoadLevelCommand failed: server not running");
        return;
    }

    ServerLoadLevelStruct levelInfo;
    levelInfo.level = levelPath.c_str();
    levelInfo.gameMode = gameMode.c_str();

    g_program->m_server->LoadLevel(levelInfo);

    gameSettings->Level = strdup(levelInfo.level);
    gameSettings->DefaultLayerInclusion = strdup(
        (std::string("GameMode=") + levelInfo.gameMode).c_str()
    );
       
    cc << "Loading level: " << levelPath
        << " with mode: " << gameMode << "\n";
    KYBER_LOG(LogLevel::Console,
        "LoadLevelCommand: level=" << levelPath 
        << " mode=" << gameMode
    );
}

void RegisterConsoleCommand(StaticConsoleMethodPtr_t func, const char* name, const char* description)
{
    ConsoleMethod* method = new ConsoleMethod{ func, name, 0, description };
    ConsoleRegistry_registerConsoleMethods("Auric", method, 1);
}

Console::Console()
{
    KYBER_LOG(LogLevel::Debug, "[Console] Initializing Console Commands");

    RegisterConsoleCommand(&SetTeamCommand, "SetTeam", "<player> <team>");
    RegisterConsoleCommand(&LoadLevelCommand, "LoadLevel", "<LevelPath> <GameMode>");
}
} // namespace Kyber
