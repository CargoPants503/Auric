// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Render/Windows/Window.h>

#include <Base/Version.h>

namespace Kyber
{
class CreditsWindow : public Window
{
public:
    // clang-format off
    const char* credits[17] = {
        ("AURIC V" + KYBER_VERSION).c_str(),
        ""
        "ORIGINAL CREATOR & DEVELOPER",
        "BattleDash - Kyber",
        "",
        "UPDATER/PORTER FOR 2015",
        "CargoPants",
        "",
        "KYBER COMMUNITY MANAGER",
        "Dangercat - Kyber",
        "",
        "CONTRIBUTORS",
        "Kape",
        "Lucapook",
        "Andersson799",
        "Cade - Kyber",
        "Mophead - Kyber",
        "Dyvinia - Kyber"
    };
    // clang-format on

    CreditsWindow();
    ~CreditsWindow();
    void Draw() override;
    bool IsEnabled() override;
};
} // namespace Kyber