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

    //Cannot change the level while in a level unfortuntately. Looking for fixes

    if (!g_program->m_server->m_running)
    {
        static GameMode currentMode = { "", "Mode", {}, {} };
        static GameLevel currentLevel = { "", "Level" };
        //static KyberProxy currentProxy = m_proxies->at(0);
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
    if (g_program->m_clientState) // default: else if
    {
        // ImGui::Text("The server host will need a mod to start the game");
        // ImGui::Text("Find it on github.com/CargoPants503/Auric/releases/tag/auricv1.0");
        // ImGui::Text("If the game hasn't started, a mod might be overriding the file!");
        ImGui::Text("Leave this game to start a new one.");
        ImGui::Separator();
        // AutoPlayerSettings* aiSettings = Settings<AutoPlayerSettings>("AutoPlayers");

        // if (ImGui::Button("START GAME"))
        //{
        //  These bots don't actually exist, it just tricks the server into thinking they do.
        // aiSettings->ForceFillGameplayBotsTeam1 = 20;
        // aiSettings->ForceFillGameplayBotsTeam2 = 19;
        //}
        ImGui::Separator();
        // ImGui::Text("AI SETTINGS");
        // ImGui::SliderInt("AI COUNT", &aiSettings->ForcedServerAutoPlayerCount, -1, 64);
        // ImGui::Checkbox("UPDATE AI", &aiSettings->UpdateAI);
        ImGui::SameLine();
        // ImGui::Checkbox("AI IGNORE PLAYERS", &aiSettings->ServerPlayersIgnoreClientPlayers);
        // ImGui::Checkbox("AUTO BALANCE TEAMS", &Settings<WSGameSettings>("Whiteshark")->AutoBalanceTeamsOnNeutral);
        ImGui::Separator();
        ImGui::Text("PLAYER LIST");

        
        //auto* playerList = g_program->m_server->GetServerGameContext2()->m_eastlServerPlayerManager->m_players;

        ServerPlayerManager* serverPlayerManager = g_program->m_server->m_ServerPlayerManager;
        ClientPlayerManager* clientPlayerManager = g_program->m_server->m_ClientPlayerManager;
        
        if (serverPlayerManager != nullptr && g_program->m_clientState == ClientState_Ingame) // Is ServerPlayerManager
        {
            //KYBER_LOG(LogLevel::Debug, "EASTLPlayerList: " << std::hex << reinterpret_cast<uintptr_t>(&playerList));
            bool printOne = true;
            if (printOne)
            {
                auto& playerList = g_program->m_server->GetServerGameContext2()->m_eastlServerPlayerManager->m_players;
                KYBER_LOG(LogLevel::Debug, std::hex << reinterpret_cast<uintptr_t>(&playerList));
                printOne = false;
            }






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