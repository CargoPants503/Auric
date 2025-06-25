
#include <Core/DebugRenderer.h>
#include <Base/Log.h>


namespace Kyber
{
bool debugEnabled = false;
bool exampleText = false;

void DebugRenderer::RenderDebug()
{
    DebugRenderer2 debugRenderer;

    if (exampleText)
    {
        // Draw text
        debugRenderer.drawText(1260, 20, "          This is Debug Text! It's normally unused by the game but it's pretty cool.      ");
        debugRenderer.drawText(1260, 40, "  This is only a proof of concept for now. Will actually be used for debugging eventually.");

        // Draw a 3D line
        Vec3 start = { 0.0f, 0.0f, 0.0f };
        Vec3 end = { 1.0f, 1.0f, 0.0f };
        Color32 red = { 255, 0, 0, 255 };
        debugRenderer.drawLine(start, end, red);

        // Draw a 100×100 box
        Vec3 minPos = { 0.0f, 100.0f, 0.0f };
        Vec3 maxPos = { 100.0f, 0.00, 0.0f };
        debugRenderer.drawBox3d(minPos, maxPos, red);
    }

    if (debugEnabled)
    {
        std::string t_serverPlayerManager = "ServerPlayerManager: 0x" + to_hex(reinterpret_cast<uintptr_t>(ServerGameContext::Get()->GetPlayerManager()));
        std::string t_clientPlayerManager = "ClientPlayerManager: 0x" + to_hex(reinterpret_cast<uintptr_t>(ClientGameContext::Get()->GetPlayerManager()));
        std::string t_serverGameContext = "ServerGameContext: 0x" + to_hex(reinterpret_cast<uintptr_t>(ServerGameContext::Get()));
        std::string t_clientGameContext = "ClientGameContext: 0x" + to_hex(reinterpret_cast<uintptr_t>(ClientGameContext::Get()));

        debugRenderer.drawText(1260, 20, t_serverPlayerManager);
        debugRenderer.drawText(1260, 40, t_clientPlayerManager);
        debugRenderer.drawText(1260, 60, t_serverGameContext);
        debugRenderer.drawText(1260, 80, t_clientGameContext);

    }
}
} // namespace Kyber
