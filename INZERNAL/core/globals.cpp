﻿#pragma once
#include <core/globals.h>
#include <sdk/player/NetAvatar.h>
#include <PathFinder/PathFinder.h>

// clang-format off


//logging options
namespace logging {
		bool	enabled		= true; //master switch for all logging
	
		//logging in console
		int		console		= callfunction;

		//logging in menu (not yet implemented)
		int		max_count	= 5000;  //max events in menu, for performance concerns.
		int		menu		= sendpacket | sendpacketraw | processtank | callfunction;

		bool packetview = true;
}

//options
namespace opt {

	//enhanchements 
	float		fps_limit	= 0.0f;	//fps limit gets forced to this
	std::string	gt_version	= "3.67";	//gt version gets spoofed to this
	std::string	gt_supported    = "3.67";	//the gt version for which INZERNAL was built for. Probably wont work for other versions.

	bool		spoof_login	= true;		//whether or not to spoof mac, hash2, wk, rid, etc on login. GT version spoofed even when off.
	bool		spoof_name	= true;		//Also set the requestedName field to random. Might be unwanted for non grow-id accounts.
	WinSpoof	spoof_win	= ::wsMimic;	//Mode of zf/fz spoofing mode. See the WinSpoof enum for more details.
	FlagMode	flag_mode	= ::fmCustom; //See FlagMode enum for details.
	std::string	flag		= "al";		//set if flag_mode is set to fmCustom

	bool		custom_server_on	= false;	//when on it uses 
	std::string	custom_server_val	= "127.0.0.1"; //localhost works with proxy. custom servers and growtopia2/1 work too.

	//cheats
	namespace cheat {	
		bool	mod_zoom			= true;		//unlimited zoom. Cant ban you. cant punch further, only view.
		bool	dev_zoom			= false;	//	mod zoom with build/punch too. can ban when using punch/build far.
		bool	block_sendpacketraw	= false;	//	blocks any and all sendpacketraw requests. Acts as full ghost.
		bool	antighost			= false;		//	ignores ghost effect.
		bool	tp_click			= true;		//when on, holding CTRL allows you to tp to mouse location.
		bool	see_ghosts			= true;		//allows you to see ghosts so you can avoid constant slime
		bool	dash				= false;	//allows you to perform dashing when double clicking A/D
		bool	jump_charge			= false;	//switches jumping mode to charging
		bool	jump_cancel			= false;	//tapping W in air instantly stops the ascent and instantly starts bringing you down
		bool	antipunch			= true;		//basically (personal) punch jammer even when there is none
		bool	see_fruits			= false;	//See how many fruits a tree will have, before it has grown. Visually sets them to be fully grown though.
		bool	dialog_cheat		= false;	//Allows you to move when dialogs are opened, also punch and do other things.

		bool	punch_cooldown_on	= false;		//	custom punch cooldown
		float	punch_cooldown_val	= 0.15f;
		
		bool	gravity_on			= false;	//	custom gravity
		float	gravity_val			= 400.0f;	

		bool	speed_on			= true;	//	custom movement speed
		float	speed_val			= 450.f;
		
		bool	accel_on			= false;	//	custom acceleration
		float	accel_val			= 3200.0f;

		bool	waterspeed_on		= true;	//	custom water speed
		float	waterspeed_val		= 325.f;



		bool		playeresp = false;
		bool		itemesp = false;
		bool		autocollect = false;
		bool		filterautocollect = false;
		int			itemfilter = 242;
		int			range_val = 1;

		bool		noname = false;
		bool		autopunchplayer = false;

		bool		autoleavepacket = false;
		bool		bruteforcepassdoor = false;
		bool		itemtp = false;
		bool		autofarm = false;
		bool		blinkcolor = false;
		bool		spamwater = false;
		int			watervalue = 822;
		int			itemid_val = 5640;

		bool crystalmode = false;
		bool randommodepacketstate = false;

		bool superpunchbreak = false;
		bool nazismoke = false;


		bool testmftiles = false;
		bool PathFindinglol = false;
		bool pfdone = false;
		bool onkilled = false;
		int gtmap[60][100];
		//std::vector<Pathfinder::Point> pathLine;

		bool ghost = false;
		bool dancemove = false;

		bool GetNetid = false;
		int GetNetids = -1;
		bool killaura = false;
		bool punchaura = false;
		bool spamtrade = false;
		bool checkw = false;
		bool clickallroulette = false;

	
		bool pathfinder = false;

		bool emptybox = false;
		bool addstock = false;
		bool pullstock = false;

		bool titlepos = false;

		int setflagtoitemid = 0;

		bool random_flag = false;
		 bool solve_captcha = false;

		 bool fastvend = false;

		 bool owner_detect = false;
		 vector<int> owner_netid;
		 char owner_name[76];

		 bool auto_msg = false;

		  bool auto_pull = false;

		  bool auto_ban = false;

		 char msg_text[76];

		 bool spammer = false;
		 char spam_text[76];
		 int spaminterval = 4000;

		 bool auto_stop_farm = false;

		 bool autocollect_gems = false;

		 char friend_uid[89] = "";
		 char msgtext[89];

		 vector<int> people_uid;
		 vector<string> people_name;
		 int select_max = 100;
		 bool start_msgall = false;
		 std::string name = "";
		 std::string password = "";
		 std::string mac = "";

		 std::string TileForeground;
		 std::string owner_id;

		 bool spin_checker = false;



		 bool isLogged = false;
		 bool isReallyLogged = false;

		 bool growscan;

		 char KeyauthUsername[20] = "";
		 char KeyauthPassword[20] = "";


		 float vitemidX1 = 0.f; // hat 
		 float vitemidX2 = 0.f; // shoes
		 float vitemidX3 = 0.f; // wing

		 float vitemidY1 = 0.f; // shirt
		 float vitemidY2 = 0.f; // idk 
		 float vitemidY3 = 0.f; // hair

		 float vitemidZ1 = 0.f; // pant
		 float vitemidZ2 = 0.f; //hand
		 float vitemidZ3 = 0.f; // neck 
		 float vitemidX5 = 0.f;

		 bool fastdrop = false;
		  bool fasttrash = false;


		  vector<string> blacklist_name;
		  //C:\UsersÖmer Şemsettin Edeme\AppData\Local\Growtopia

		  std::string itemdata_file = "items.dat";


		  bool antibounce = false;

		  bool modfly = false;
		  bool modfly2 = false;

		  bool followplayer = false;
		CL_Vec2f TouchPos;
	}
	
}

//other variables
namespace global {
		HWND		hwnd	= NULL;		//	pointer to hwnd of Growtopia window
		App*		app		= nullptr;	//	pointer to App instance
		bool		unload	= false;	//	proces terminates when set to true
		bool		d9init	= false;	//	has s_renderD3D9 yet been init? if not, then check in App::Update for news
		uintptr_t	gt		= 0;		//	growtopia base address
		bool		load	= false;	//	menu/imgui initialization status
		bool		draw	= false;	//	menu draw status. set to true for menu to show up when you inject
		std::string	version	= "V0.6 Beta";	//	INZERNAL version
		float		fade	= 0.f;		//	does not matter, will get automatically updated
		charstate_t state{};			//	state info of player that may be modified so that we can restore it later.
}

// clang-format on

void charstate_t::copy_from_packet(GameUpdatePacket* packet) {
    //int8s
    buildrange = packet->build_range - 128;
    punchrange = packet->punch_range - 128;

    //floats
    gravity = packet->gravity_out;
    speed = packet->speed_out;
    accel = packet->accel;
    punch_strength = packet->punch_strength;
    water_speed = packet->water_speed;

    //ints
    punchid = packet->punchid;
    pupil_color = packet->pupil_color;
    eye_color = packet->eyecolor;
    eye_shade_color = packet->eye_shade_color;
    eff_flags1 = packet->effect_flags;
    eff_flags2 = packet->flags;
    if (opt::cheat::antighost) {//remove mindcontrol mod
        packet->flags &= ~(1 << 11);
        eff_flags2 &= ~(1 << 11); 
    }
}

void charstate_t::copy_inject(NetAvatar* player, bool is_local) {
    gravity = player->gravity.get(is_local);
    speed = player->speed.get(is_local);
    accel = player->accel.get(is_local);
    punch_strength = player->punch_strength.get(is_local);
    water_speed = player->water_speed;

    //cant copy more than this because we dont know all the values in NetAvatar ATM
}
