#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <SDK/SDK.h>
#include <SDK/TypeInfo.h>
#include <Hook/Func.h>

namespace Kyber
{
extern bool debugEnabled;
extern bool exampleText;

inline void SetDebugEnabled(bool enable)
{
    debugEnabled = enable;
}

inline bool IsDebugEnabled()
{
    return debugEnabled;
}

TL_DECLARE_FUNC(0x1433151D0, void*, DebugRenderer_current);
TL_DECLARE_FUNC(0x143317710, void, DebugRenderer_InternalDrawText, void* inst, int x, int y, const char* text, __int64 a4, __int64 a5);
TL_DECLARE_FUNC(0x14331C1A0, DebugRenderVertex*, DebugRenderer_writeCachedVertices, void* inst, int a2, int a3);

class DebugRenderer
{
public:
    virtual ~DebugRenderer() = default;
    static void RenderDebug();
};

class DebugRenderer2
{
public:
    void drawLine(Vec3 pos1, Vec3 pos2, Color32 color);
    void drawText(int x, int y, const std::string& text);
    void drawBox3d(Vec3 minPos, Vec3 maxPos, Color32 color);
};

// This is for making my code cleaner in the .cpp file
auto to_hex = [](uintptr_t v) {
    std::ostringstream ss;
    ss << std::hex << v;
    return ss.str();
};

__forceinline void writeLine(DebugRenderVertex*& v, Vec3 pos1, Vec3 pos2, Color32 color1, Color32 color2)
{
    v->pos = *reinterpret_cast<const Tuple3f*>(&pos1);
    v->color = color1;
    v++;

    v->pos = *reinterpret_cast<const Tuple3f*>(&pos2);
    v->color = color2;
    v++;
}

__forceinline void writeLine(DebugRenderVertex*& v, Vec3 pos1, Vec3 pos2, Color32 color)
{
    writeLine(v, pos1, pos2, color, color);
}

__forceinline void writeLine2d(DebugRenderVertex*& v, Vec2 startPos, Vec2 endPos, Color32 color)
{
    v->pos.x = startPos.x;
    v->pos.y = startPos.y;
    v->pos.z = 1.0f;
    v->color = color;
    v++;

    v->pos.x = endPos.x;
    v->pos.y = endPos.y;
    v->pos.z = 1.0f;
    v->color = color;
    v++;
}

inline void DebugRenderer2::drawText(int x, int y, const std::string& text)
{//                                           a1            a2 a3    a4          a5             a5
    DebugRenderer_InternalDrawText(DebugRenderer_current(), x, y, text.c_str(), 4278190080, 1065353216);
}

inline void DebugRenderer2::drawLine(Vec3 pos1, Vec3 pos2, Color32 color)
{
    DebugRenderVertex* v = DebugRenderer_writeCachedVertices(DebugRenderer_current(), DebugGeometryType_Line3d, 2);
    writeLine(v, pos1, pos2, color);
}

inline void DebugRenderer2::drawBox3d(Vec3 minPos, Vec3 maxPos, Color32 color)
{
    Vec3 a = { minPos.x, minPos.y, 1.0f };
    Vec3 b = { maxPos.x, minPos.y, 1.0f };
    Vec3 c = { maxPos.x, maxPos.y, 1.0f };
    Vec3 d = { minPos.x, maxPos.y, 1.0f };

    drawLine(a, b, color); // bottom
    drawLine(b, c, color); // right
    drawLine(c, d, color); // top
    drawLine(d, a, color); // left
}

} // namespace Kyber
