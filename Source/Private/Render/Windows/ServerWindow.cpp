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
    if (index < 0 || index >= static_cast<int>(playerList.size()))
    {
        return false;
    }

    ServerPlayer* player = playerList[index];
    if (!player || !player->m_name)
    {
        return false;
    }

    std::string playerName(player->m_name);
    std::string playerInfo = playerName + "  " + std::to_string(player->m_id);
    ImGui::Text("%s", playerInfo.c_str());

    if (!isHoster)
        return true;

    ImGui::SameLine();
    std::string swapLabel = "SWAP TEAM##" + playerName;
    if (ImGui::SmallButton(swapLabel.c_str()))
    {
        // In SWBF, player extents form an intrusive linked list of a player’s settings. While less stable, reading 0x2BAC is much easier
        uint32_t team = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(player) + 0x2BAC);
        g_program->m_server->SetPlayerTeam(player, team == 1 ? 2 : 1);
    }

    ImGui::SameLine();
    std::string kickLabel = "KICK##" + playerName;
    if (ImGui::SmallButton(kickLabel.c_str()))
    {
        g_program->m_server->KickPlayer(player, "You have been kicked.", true);
    }

    return true;
}

bool DrawMapRotation() 
{
    ImGui::Text("----- Map Rotation ----- ");

    auto& mapList = g_program->m_server->m_mapList;

    if (mapList.empty())
    {
        ImGui::Text("No Maps in Map Rotation. Start a server first");
    }

    else
    {
        for (int i = 0; i < mapList.size(); ++i)
        {
            MapRotation* map = mapList[i];

            ImGui::Text("Map: %s | Mode: %s", map->Name, map->GameMode);
            ImGui::SameLine(450);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));

            // Move the map up in the rotation
            if (ImGui::Button(("UP##" + std::to_string(i)).c_str()) && i > 0)
            {
                std::swap(mapList[i], mapList[i - 1]);
            }

            ImGui::SameLine();
            
            // Move the map down in the rotation
            if (ImGui::Button(("DOWN##" + std::to_string(i)).c_str()) && i < mapList.size() - 1)
            {
                std::swap(mapList[i], mapList[i + 1]);
            }

            ImGui::SameLine();

            // Remove the map from the rotation
            if (ImGui::Button(("X##" + std::to_string(i)).c_str()))
            {
                delete mapList[i];
                mapList.erase(mapList.begin() + i);
                --i;
            }

            ImGui::PopStyleVar();
        }
    }
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

    DrawMapRotation();

    ServerPlayerManager* serverPlayerManager = ServerGameContext::Get()->GetPlayerManager();
    ClientPlayerManager* clientPlayerManager = ClientGameContext::Get()->GetPlayerManager();

    // A ServerPlayerManager doesn't Always exist, unlike the ClientPlayerManager.
    // Have it display a serverPlayerManager when possible you need to see if a player exists
    // because you can have a pointer to where the serverPlayerManager is supposed to be without
    // a ServerPlayerManager actually existing
    
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
            ImGui::SameLine();
            if (ImGui::Button("Add to Map Rotation"))
            {
                g_program->m_server->m_mapList.push_back(new MapRotation{ currentLevel.level, currentMode.mode, currentLevel.name });
            }
            ImGui::SameLine();
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
    
    if (serverPlayerManager->m_players[0] != nullptr)
    {
        std::map<int32_t, std::vector<ServerPlayer*>> players;

        players[1] = std::vector<ServerPlayer*>();
        players[2] = std::vector<ServerPlayer*>();

        for (ServerPlayer* player : serverPlayerManager->m_players)
        {
            if (player)
            {
                uint32_t teamId = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(player) + 0x2BAC);
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
        std::map<int32_t, std::vector<ServerPlayer*>> players;

        players[1] = std::vector<ServerPlayer*>();
        players[2] = std::vector<ServerPlayer*>();

        for (ServerPlayer* player : clientPlayerManager->m_players)
        {
            if (player)
            {
                uint32_t teamId = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(player) + 0x2BAC);
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
    ImGui::End();

}
} // namespace Kyber