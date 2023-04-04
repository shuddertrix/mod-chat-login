/**
    This plugin can be used for common player customizations
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "ChannelMgr.h"
#include "Chat.h"

class LoginChat : public PlayerScript{
public:

    LoginChat() : PlayerScript("LoginChat") { }

    void OnLogin(Player* player) override {

    if (sConfigMgr->GetOption<bool>("LoginChat.enabled", false))
    {
        std::string channelName = sConfigMgr->GetOption<std::string>("LoginChat.name", "world");
        int32 channelId = sConfigMgr->GetOption<int32>("LoginChat.id", 1);
        QueryResult result = CharacterDatabase.Query("SELECT channelId FROM channels WHERE name = '{}'", channelName);

        if (!result) return;
    
        if (ChannelMgr* cMgr = ChannelMgr::forTeam(player->GetTeamId()))
        {
            if (Channel* channel = cMgr->GetJoinChannel(channelName, channelId))
                    channel->JoinChannel(player, "");
            cMgr->LoadChannels();
        }

    }
    }
};

void AddLoginChatScripts() {
    new LoginChat();
}

