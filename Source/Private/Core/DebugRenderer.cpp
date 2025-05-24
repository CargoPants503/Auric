#pragma once
#include <Core/DebugRenderer.h>
#include <Base/Log.h>


namespace Kyber
{
bool debugEnabled = false;

// ---- THIS DEFINES the static member you declared! ----
void DebugRenderer::RenderDebug()
{

    if (debugEnabled)
    {
        DebugRenderer2 debugRenderer;

        // Draw text
        debugRenderer.drawText(1260, 20, "          This is Debug Text! It's normally unused by the game but it's pretty cool.      ");
        debugRenderer.drawText(1260, 40, "  This is only a proof of concept for now. Will actually be used for debugging eventually.");

        // Draw a 3D line
        Vec3 start = { 0.0f, 0.0f, 0.0f };
        Vec3 end = { 1.0f, 1.0f, 0.0f };
        Color32 red = { 255, 0, 0, 255 };
        debugRenderer.drawLine(start, end, red);

        // Draw a 100×100×100 box
        Vec3 minPos = { 0.0f, 100.0f, 0.0f };
        Vec3 maxPos = { 100.0f, 0.00, 0.0f };
        debugRenderer.drawBox3d(minPos, maxPos, red);
    }
    
}
} // namespace Kyber
