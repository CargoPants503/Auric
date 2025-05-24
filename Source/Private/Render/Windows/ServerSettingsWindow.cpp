// Copyright BattleDash. All Rights Reserved.

#include <Render/Windows/ServerSettingsWindow.h>

#include <Base/Log.h>
#include <Core/Program.h>
#include <Render/Windows/MainWindow.h>
#include <Utilities/ErrorUtils.h>
#include <SDK/Modes.h>
#include <Core/DebugRenderer.h>

#include <Windows.h>
#include <chrono>

namespace Kyber
{
ServerSettingsWindow::ServerSettingsWindow() {}

bool ServerSettingsWindow::IsEnabled()
{
    return g_mainWindow->IsEnabled() && m_isEnabled;
}

void ServerSettingsWindow::Draw()
{
    ImGui::Begin("Server Settings", &m_isEnabled);
    if (g_program->m_server->m_running)
    {
        if (g_program == nullptr || g_program->m_server == nullptr)
        {
            KYBER_LOG(LogLevel::Error, "g_program or g_program->m_server is null!");
        }
        WSGameSettings* wsSettings = Settings<WSGameSettings>("Whiteshark");
        GameTime* gameTimeSettings = Settings<GameTime>("GameTime");
        GameSettings* gameSettings = Settings<GameSettings>("Game");
        ClientSettings* clientSettings = Settings<ClientSettings>("Client");
        ServerSettings* serverSettings = Settings<ServerSettings>("Server");
        SyncedGameSettings* syncedGameSettings = Settings<SyncedGameSettings>("SyncedGame");

        ImGui::Text("Most Settings Only Apply Upon Respawning");
        ImGui::Text("Modifying certain settings can cause server issues, be Careful!");
        ImGui::Separator();

        static float humanHealthMultiplier = serverSettings->HumanHealthMultiplier;
        static float timeScale = gameTimeSettings->TimeScale;
        static int RespawnTimeModifier = serverSettings->RespawnTimeModifier;
        static float sprintSpeedMultiplier = 1.0f; // Default sprint speed multiplier

        ImGui::SliderFloat("Health Multiplier [unstable]", &humanHealthMultiplier, 0.1f, 32.0f);
        {
            serverSettings->HumanHealthMultiplier = humanHealthMultiplier;
        }
        ImGui::SliderFloat("Time Scale", &timeScale, 0.5f, 10.0f);
        {
            gameTimeSettings->TimeScale = timeScale;
        }
        ImGui::SliderInt("Respawn Time Modifier ", &RespawnTimeModifier, 0, 8);
        {
            serverSettings->RespawnTimeModifier = RespawnTimeModifier;
        }

        //This does not work yet, offsets are hard to find for ebx
        /*
        ImGui::SliderFloat("Sprint Speed Multiplier", &sprintSpeedMultiplier, 0.5f, 10.0f);
        {
            // Modify the memory value for sprint speed multiplier directly
            uint8_t targetAoB[] = { 0xA2, 0x66, 0xA8, 0x69, 0x7C, 0xDF, 0xAD, 0x4B, 0xB5, 0x5F, 0x99, 0x53, 0x6F, 0x25, 0x51, 0xF6 };
            SIZE_T aoBSize = sizeof(targetAoB);

            uintptr_t baseAddress = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
            SIZE_T regionSize = 0x2000000;

            uintptr_t foundAddress = 0;

            for (uintptr_t i = baseAddress; i < baseAddress + regionSize; ++i)
            {
                if (memcmp(reinterpret_cast<void*>(i), targetAoB, aoBSize) == 0)
                {
                    foundAddress = i;
                    break;
                }
            }

            if (foundAddress != 0)
            {
                uintptr_t floatAddress = foundAddress + 0x44; // Offset to the sprint speed float.
                float* floatPointer = reinterpret_cast<float*>(floatAddress);
                DWORD oldProtect;
                VirtualProtect(floatPointer, sizeof(float), PAGE_EXECUTE_READWRITE, &oldProtect);
                *floatPointer = sprintSpeedMultiplier;
                VirtualProtect(floatPointer, sizeof(float), oldProtect, &oldProtect);
            }
            else
            {
                KYBER_LOG(LogLevel::Error, "Sprint speed AoB not found!");
            }
        }
        */
        ImGui::Separator();
        
        static bool DisableRegenerateHealth = syncedGameSettings->DisableRegenerateHealth;
        static bool EnableFriendlyFire = syncedGameSettings->EnableFriendlyFire;
        static bool HavokVisualDebugger = serverSettings->HavokVisualDebugger;

        if (ImGui::Button(DisableRegenerateHealth ? "Disable Regenerate Health ON" : "Disable Regenerate Health OFF")) // Only Applies on Player Respawned
         {
                DisableRegenerateHealth = !DisableRegenerateHealth; // Toggle the state
                syncedGameSettings->DisableRegenerateHealth = DisableRegenerateHealth;

        }
        
        ImGui::SameLine(350);
        ImGui::Text("Applies On Spawned");
        
        if (ImGui::Button(EnableFriendlyFire ? "Friendly Fire ON" : "Friendly Fire OFF")) // Only Applies on Player Respawned
        {
            EnableFriendlyFire = !EnableFriendlyFire; // Toggle the state
            syncedGameSettings->EnableFriendlyFire = EnableFriendlyFire;
        }
        ImGui::SameLine(350);
        ImGui::Text("Applies On Spawned");
        if (ImGui::Button(Kyber::IsDebugEnabled() ? "Visual Debug ON" : "Visual Debug OFF"))
        {
            if (Kyber::IsDebugEnabled())
            {
                Kyber::SetDebugEnabled(false);

            }
            else
            {
                Kyber::SetDebugEnabled(true);

            }
        }

        /*
        if (ImGui::Button(HavokVisualDebugger ? "Havok: TRUE" : "Havok: FALSE")) // Only Applies on Player Respawned
        {
            HavokVisualDebugger = !HavokVisualDebugger; // Toggle the state
            serverSettings->HavokVisualDebugger = HavokVisualDebugger;
        }
        ImGui::SameLine(350);
        ImGui::Text("Applies On Spawned");
        */


        //ImGui::PopStyleColor(); // crashes if colors aren't being updated/changed
        
        ImGui::Separator();
    }
    else
    {
        ImGui::Text("Please Join A Server Before Changing Settings");
        ImGui::Text("If you are inside a server please join the Auric Discord");
    }
    ImGui::End();
}
} // namespace Kyber