// Copyright BattleDash. All Rights Reserved.

#include <Render/Windows/ServerWindow.h>

#include <Base/Log.h>
#include <Core/Program.h>
#include <Render/Windows/MainWindow.h>
#include <SDK/Modes.h>
#include <EASTL/fixed_vector.h>

#include <vector>
#include <algorithm>
#include <map>

namespace Kyber
{
ServerWindow::ServerWindow() {

}

bool ServerWindow::IsEnabled()
{
    return g_mainWindow->IsEnabled() && m_isEnabled;
}

bool DrawScoreboardPlayer(std::vector<ServerPlayer*> playerList, int index, bool isHoster)
{
    if (playerList.size() <= index)
    {
        return false;
    }
    ServerPlayer* player = playerList[index];
    std::string playerInfo = std::string(player->m_name) + "  " + std::to_string(player->m_id);
    ImGui::Text("%s", playerInfo.c_str());

    ImGui::SameLine();
    if (isHoster) {
        if (ImGui::SmallButton(("SWAP TEAM##" + std::string(player->m_name)).c_str()))
        {
            g_program->m_server->SetPlayerTeam(player, *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(player) + 0x2BAC) == 1 ? 2 : 1);
        }
        ImGui::SameLine();
        if (ImGui::SmallButton(("KICK##" + std::string(player->m_name)).c_str()))
        {
            g_program->m_server->KickPlayer(player, "You have been kicked.");
            g_program->m_server->SendKickedMessage(player, player->m_name);
        }
    }

    
   
    return true;
}

void ServerWindow::Draw()
{
    ImGui::Begin("SERVER SETTINGS", &m_isEnabled, ImGuiWindowFlags_AlwaysAutoResize);
    GameSettings* gameSettings = Settings<GameSettings>("Game");
    ImGui::Text("GAME MODE:");
    ImGui::SameLine();
    ImGui::Text(gameSettings->DefaultLayerInclusion);
    ImGui::Text("LEVEL:");
    ImGui::SameLine();
    ImGui::Text(gameSettings->Level);
    ImGui::Separator();

    if (g_program->m_clientState == 12 || g_program->m_server->m_isFirstLaunch)
    {
        static GameMode currentMode = { "", "Mode", {}, {} };
        static GameLevel currentLevel = { "", "Level" };
        if (ImGui::BeginCombo("##modeCombo", currentMode.name))
        {
            for (int n = 0; n < IM_ARRAYSIZE(s_game_modes); n++)
            {
                bool selected = (strcmp(currentMode.mode, s_game_modes[n].mode) == 0);
                if (ImGui::Selectable(s_game_modes[n].name, selected))
                {
                    currentMode = s_game_modes[n];
                    currentLevel = { "", "Level" };
                }
                if (selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        if (ImGui::BeginCombo("##levelCombo", currentLevel.name))
        {
            for (int i = 0; i < currentMode.levels.size(); i++)
            {
                GameLevel level = GetGameLevel(currentMode, currentMode.levels[i]);
                bool selected = (strcmp(currentLevel.level, level.level) == 0);
                if (ImGui::Selectable(level.name, selected))
                {
                    currentLevel = level;
                }
                if (selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        if (!g_program->m_server->m_running ||  gameSettings->Level == "Levels/FrontEnd/Frontend")
        {
            static int maxPlayers = 40;
            ImGui::SliderInt("Max Players", &maxPlayers, 2, 64);
            if (ImGui::IsItemHovered())
            {
                ImGui::BeginTooltip();
                ImGui::Text("When you use a Kyber Proxy, your server");
                ImGui::Text("will be displayed on the server browser,");
                ImGui::Text("and client/host IPs will be hidden.\n\n");
                ImGui::Text("When you don't use a Kyber Proxy, you will");
                ImGui::Text("need to Port Forward port 25200 in your router");
                ImGui::Text("and have players connect to your IP directly.");
                ImGui::Text("Mod verification is not supported when not using a proxy.");
                ImGui::EndTooltip();
            }
            static int errorTime = 0;
            if (ImGui::Button("Start Server"))
            {
                if (strcmp(currentMode.name, "Mode") != 0 && strcmp(currentLevel.name, "Level") != 0)
                {
                    g_program->m_server->Start(currentLevel.level, currentMode.mode, maxPlayers);
                }
                else
                {
                    errorTime = 1000;
                }
            }
            if (errorTime > 0)
            {
                if (ImGui::IsItemHovered())
                {
                    ImGui::BeginTooltip();
                    ImGui::Text("Please select a game mode and level.");
                    ImGui::EndTooltip();
                }
                errorTime--;
            }
        }
        else
        {
            if (ImGui::Button("Load New Level"))
            {
                if (strcmp(currentMode.name, "Mode") != 0 && strcmp(currentLevel.name, "Level") != 0)
                {
                    ServerLoadLevelStruct levelStruct;
                    const char* level= currentLevel.level;
                    const char* gameMode = currentMode.mode;
                    levelStruct.level = level;
                    levelStruct.gameMode = gameMode;

                    g_program->m_server->LoadLevel(levelStruct);
                    KYBER_LOG(LogLevel::Debug, "Loading Level with Level: " << level << " and GameMode: " << gameMode);
                    gameSettings->Level = strdup(currentLevel.level);
                    std::string modeString = std::string("GameMode=") + currentMode.mode;
                    gameSettings->DefaultLayerInclusion = strdup(modeString.c_str());


                }
            }
            if (ImGui::Button("Restart Level"))
            {
                ServerLoadLevelStruct levelStruct;
                const char* level = gameSettings->Level;

                const char* fullString = gameSettings->DefaultLayerInclusion;
                const char* prefix = "GameMode=";
                const char* gameMode = nullptr;

                if (strncmp(fullString, prefix, strlen(prefix)) == 0)
                {
                    gameMode = fullString + strlen(prefix);
                }

                levelStruct.level = level;
                levelStruct.gameMode = gameMode;

                g_program->m_server->LoadLevel(levelStruct);
                KYBER_LOG(LogLevel::Debug, "Restarting Level with Level: " << level << " and GameMode: " << gameMode);

            }
        }       
    }
    if (g_program->m_clientState) // default: else if
    {
        ImGui::Separator();
        ImGui::Text("PLAYER LIST");

        ServerPlayerManager* serverPlayerManager = g_program->m_server->m_ServerPlayerManager;
        ClientPlayerManager* clientPlayerManager = g_program->m_server->m_ClientPlayerManager;
        
        if (serverPlayerManager != nullptr && g_program->m_clientState == ClientState_Ingame) // Is ServerPlayerManager
        {
           
            std::map<int32_t, std::vector<ServerPlayer*>> players;
            // Bleh
            players[1] = std::vector<ServerPlayer*>();
            players[2] = std::vector<ServerPlayer*>();
            for (ServerPlayer* player : serverPlayerManager->m_players)
            {
                if (player)
                {
                    uint32_t teamId = *reinterpret_cast<uint32_t*>(
                        reinterpret_cast<uint8_t*>(player) + 0x2BAC); // I have my reasons for doing this instead of using the struct
                    if (teamId)
                    {
                        players[teamId].push_back(player);
                    }
                    else
                    {
                        players[1].push_back(player);
                    }
                }
            }

            if (ImGui::BeginTable("PLAYER LIST", 2, ImGuiTableFlags_SizingFixedFit))
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("LIGHT SIDE");
                ImGui::TableNextColumn();
                ImGui::Text("DARK SIDE");
                for (int i = 0; i < 64; i++)
                {
                    ImGui::TableNextRow();
                    int drew = 0;
                    for (int j = 1; j <= players.size(); j++)
                    {
                        ImGui::TableNextColumn();
                        if (DrawScoreboardPlayer(players[j], i, true))
                        {
                            drew++;
                        }
                    }
                    if (!drew)
                    {
                        break;
                    }
                }
                ImGui::EndTable();
            }
        }
        else
        {
            if (serverPlayerManager == nullptr && clientPlayerManager && (g_program->m_clientState == ClientState_Ingame  || g_program->m_server->m_isFirstLaunch)) // Is Client Manager
            {
                
                std::map<int32_t, std::vector<ServerPlayer*>> players;
                // Bleh
                players[1] = std::vector<ServerPlayer*>();
                players[2] = std::vector<ServerPlayer*>();
                for (ServerPlayer* player : clientPlayerManager->m_players)
                {
                    if (player)
                    {
                        uint32_t teamId = *reinterpret_cast<uint32_t*>(
                            reinterpret_cast<uint8_t*>(player) + 0x2BAC); // I have my reasons for doing this instead of using the struct
                        if (teamId)
                        {
                            players[teamId].push_back(player);
                        }
                        else
                        {
                            players[1].push_back(player);
                        }
                    }
                }

                if (ImGui::BeginTable("PLAYER LIST", 2, ImGuiTableFlags_SizingFixedFit))
                {
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::Text("LIGHT SIDE");
                    ImGui::TableNextColumn();
                    ImGui::Text("DARK SIDE");
                    for (int i = 0; i < 64; i++)
                    {
                        ImGui::TableNextRow();
                        int drew = 0;
                        for (int j = 1; j <= players.size(); j++)
                        {
                            ImGui::TableNextColumn();
                            if (DrawScoreboardPlayer(players[j], i, false))
                            {
                                drew++;
                            }
                        }
                        if (!drew)
                        {
                            break;
                        }
                    }
                    ImGui::EndTable();
                }
            }
        }
    }
    else
    {
        ImGui::Text("Settings will be available once");
        ImGui::Text("the game is fully loaded.");
    }
    ImGui::End();

}
} // namespace Kyber