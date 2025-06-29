#pragma once

#include <SDK/TypeInfo.h>
#include <SDK/SDK.h>

#include <Hook/Func.h>

namespace Kyber
{
//Server
TL_DECLARE_FUNC(0x1445049A0, void, LoadLevel_Setup, ServerLoadLevelStruct a1);
TL_DECLARE_FUNC(0x144483EF0, void, SendServerMessage_Send, __int64 qword_142CE2948, ChatChannel channel, const char* message, ServerPlayer* player);

//Players
TL_DECLARE_FUNC(0x143C7F140, void, ServerConnection_KickPlayer, __int64 inst, __int64 reason, const std::string& reasonText);
TL_DECLARE_FUNC(0x143CBE6F0, void, ServerConnection_SetPlayerTeam, ServerPlayer* player, int teamId);
TL_DECLARE_FUNC(0x143CD4180, __int64, ServerPeer_ConnectionForPlayer, __int64 inst, ServerPlayer* player);
}