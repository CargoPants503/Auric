// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Render/Windows/Window.h>

namespace Kyber
{
class ServerSettingsWindow : public Window
{
public:
    ServerSettingsWindow();
    ~ServerSettingsWindow();
    void Draw() override;
    bool IsEnabled() override;
};
} // namespace Kyber