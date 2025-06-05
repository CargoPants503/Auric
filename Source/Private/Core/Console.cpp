#include <Core/Program.h>
#include <Hook/Func.h>
#include <iostream>
#include <Hook/HookManager.h>
#include <Core/Console.h>
#include <Base/Log.h>



namespace Kyber
{
TL_DECLARE_FUNC(0x14334B160, void, ConsoleRegistry_registerConsoleMethods, const char* groupName, ConsoleMethod* methods, int count);

// Credit BattleDash
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
    std::string levelPath;
    std::string gameMode;
    stream >> levelPath >> gameMode;
    if (levelPath.empty() || gameMode.empty()){return;}


    GameSettings* gameSettings = Settings<GameSettings>("Game");
    if (std::strcmp(gameSettings->Level, "Levels/FrontEnd/FrontEnd") != 0)
    {   
        
        ServerLoadLevelStruct loadLevel;
        loadLevel.level = levelPath.c_str();
        loadLevel.gameMode = gameMode.c_str(); //_strdup(("GameMode=" + gameMode).c_str());
        g_program->m_server->LoadLevel(loadLevel);
        gameSettings->Level = strdup(loadLevel.level);
        gameSettings->DefaultLayerInclusion = strdup((std::string("GameMode=") + loadLevel.gameMode).c_str());
       
        cc << "Set " << loadLevel.level << " to team " << loadLevel.gameMode;
        KYBER_LOG(LogLevel::Console, "Loading Level " << loadLevel.level << " " << loadLevel.gameMode);
    }
    else
    {
        cc << "Start A Server First!";
        KYBER_LOG(LogLevel::Console, "Start a server to use this command!");
    }
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
