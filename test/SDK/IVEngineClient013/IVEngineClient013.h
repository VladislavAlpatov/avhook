#pragma once
#include "../IBaseInterface.h"

namespace SSDK
{
	typedef struct player_info_s
	{
		unsigned __int64		uiUnk;
		unsigned __int64		uiXuid;
		char                    szName[128];
		int                     iUserID;
		char                    szGuid[32 + 1];
		unsigned int            uiFriendsID;
		char                    szFriendsName[128];
		bool                    bFakePlayer;
		bool                    bIsHltv;
		unsigned long           ulCustomFiles[4];
		unsigned char           uszFilesDownloader;
	} player_info_t;

	class IVEngineClient013 : public IBaseInterface
	{
	public:
		// Get player information: name etc...
		player_info_s GetPlayerInfo(int ent_num);

		// Is game console visible?
		bool	      Con_IsVisible();
		// Get local player index
		int			  GetLocalPlayer();
		bool          IsInGame();
		bool          IsConnected();
	};

}

