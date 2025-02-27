#pragma once
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "shlwapi.lib")
#include <d3d9.h>
#include <enet/include/enet.h>
#include <proton/NetHTTP.h>
#include <proton/Variant.h>
#include <proton/clanlib/vec2.h>
#include <stdio.h>
#include <atomic>
#include <core/json.hpp>
#include <map>
#include <string>
#include <chrono>


// clang-format off

//TODO: move this
struct TextureD3D9 {
    union {
        IDirect3DBaseTexture9* m_ptr;
        IDirect3DTexture9* m_texture2d;
        IDirect3DVolumeTexture9* m_texture3d;
        IDirect3DCubeTexture9* m_textureCube;
    };

    IDirect3DSurface9* m_surface;

    union {
        IDirect3DBaseTexture9* m_staging;
        IDirect3DTexture9* m_staging2d;
        IDirect3DVolumeTexture9* m_staging3d;
        IDirect3DCubeTexture9* m_stagingCube;
    };

    uint64_t m_flags;
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_depth;
    uint8_t m_numMips;
    uint8_t m_type;
    uint8_t m_requestedFormat;
    uint8_t m_textureFormat;
};


class BaseApp {public:};
class App : BaseApp {public:};
class variantlist_t;
struct GameUpdatePacket;
struct AvatarRenderData;
struct WorldObjectMap;
struct NetAvatar;
struct LevelTouchComponent;
struct WorldCamera;
struct GameLogic;
struct SurfaceAnim;
struct ResourceManager;

namespace types {
	//hooked
	using	SendPacketRaw				= void(__cdecl*)(int, GameUpdatePacket*, int, void*, ENetPeer*, int);
	using	SendPacket					= void(__cdecl*)(int, std::string&, ENetPeer*);
	using	ProcessTankUpdatePacket		= void(__cdecl*)(GameLogic*, GameUpdatePacket*);

	//other functions, not hooked
	using	WorldToScreen				= void(__cdecl*)(WorldCamera*, CL_Vec2f&, CL_Vec2f);
	using	SetCharacterExtraMods		= void(__cdecl*)(NetAvatar*, uint8_t*);
	using	GetSurfaceAnim				= SurfaceAnim*(__cdecl*)(ResourceManager*, const std::string&, bool);

	typedef	std::chrono::duration<double> elapsed;
	typedef std::chrono::system_clock::time_point time;
}

enum WinSpoof {
	wsOff = 0,		//will not try to spoof anything
	wsRandom = 1,	//will set random values to zf and fz as usual
	wsMimic = 2		//will set unmodified newest growtopia.exe values to avoid fake win-ver tracking. needs manual updating
};
enum FlagMode {
	fmKeep = 0,		//keep your flag
	fmRandom = 1,	//pick random flag from gt folder
	fmCustom = 2,	//use custom flag
};

namespace logging {

		enum { 
			 sendpacket = (1 << 0), //the text of the packet
			 sendpacketraw = (1 << 1), //just the type, not the full info
			 processtank = (1 << 2), //just the type, not the full info
			 callfunction = (1 << 3), //processtankupdatepacket CALL_FUNCTION serializes as variantlist
			 logmsg	= (1 << 4), //LogMsg function
			 callfuncspr = (1 << 5) //sendpacketraw CALL_FUNCTION serializes as variantlist
		 };

		extern bool	enabled;
		extern int console;
		extern int max_count;
		extern int menu;	
		extern bool packetview;
}

namespace opt {
	
	extern std::string	gt_version;
	extern std::string	gt_supported;
	extern float		fps_limit;

	extern bool			spoof_login;
	extern bool			spoof_name;
	extern WinSpoof		spoof_win;
	extern FlagMode		flag_mode;
	extern std::string	flag;

	extern bool			custom_server_on;
	extern std::string	custom_server_val;

	namespace cheat {
		extern bool		dev_zoom;
		extern bool		block_sendpacketraw;
		extern bool		antighost;
		extern bool		tp_click;
		extern bool		mod_zoom;
		extern bool		see_ghosts;
		extern bool		dash;
		extern bool		jump_charge;
		extern bool		jump_cancel;
		extern bool		antipunch;
		extern bool		see_fruits;
		extern bool		dialog_cheat;

		extern bool		punch_cooldown_on;
		extern float	punch_cooldown_val;

		extern bool		gravity_on;
		extern float	gravity_val;

		extern bool		speed_on;
		extern float	speed_val;

		extern bool		accel_on;
		extern float	accel_val;

		extern bool		waterspeed_on;
		extern float	waterspeed_val;


		extern bool		playeresp;
		extern bool		itemesp;
		extern bool		autocollect;
		extern bool		filterautocollect;
		extern int	itemfilter;
		extern int	range_val;
		extern bool bruteforcepassdoor;
		extern bool autofarm;
		extern bool itemtp;
		extern bool noname;
		extern int	itemid_val;
		extern bool	spamwater;
		extern int	watervalue;
		extern bool autopunchplayer;
		extern bool blinkcolor;

		extern bool crystalmode;
		extern bool randommodepacketstate;

		extern bool testmftiles;
		extern bool PathFindinglol;
		extern bool pfdone;
		extern bool onkilled;
		extern int gtmap[60][100];

		extern bool ghost;
		extern bool dancemove;
		extern bool nazismoke;

		extern bool superpunchbreak;


		extern bool GetNetid;
		extern int GetNetids;
		extern bool killaura;
		extern bool punchaura;
		extern bool spamtrade;
		extern bool checkw;

		extern bool clickallroulette;

		extern bool pathfinder;

		extern bool emptybox;
		extern bool addstock;
		extern bool pullstock;

		extern bool titlepos;

		extern int setflagtoitemid;

		extern bool random_flag;
		extern bool solve_captcha;

		extern bool fastvend;

		extern bool owner_detect;
		extern vector<int> owner_netid;
		extern char owner_name[76];

		extern bool auto_msg;

		extern bool auto_pull;

		extern bool auto_ban;
		extern char msg_text[76];

		extern bool spammer;
		extern char spam_text[76];
		extern int spaminterval;


		extern bool auto_stop_farm;

		extern bool autocollect_gems;


		extern char friend_uid[89];
		extern  char  msgtext[89];
		extern vector<int> people_uid;
		extern vector<string> people_name;
		extern int select_max;
		extern bool start_msgall;

		extern std::string name;
		extern std::string password;
		extern std::string mac;

		extern std::string TileForeground;
		extern std::string owner_id;

		extern bool spin_checker;


		extern bool isLogged;
		extern bool isReallyLogged;

		extern bool growscan;

		extern char KeyauthUsername[20];
		extern char KeyauthPassword[20];


		extern float vitemidX1;
		extern float vitemidX2;
		extern float vitemidX3;

		extern float vitemidY1;
		extern float vitemidY2;
		extern float vitemidY3;

		extern float vitemidZ1;
		extern float vitemidZ2;
		extern float  vitemidZ3;
		extern float vitemidX5;

		extern bool fastdrop;
		extern bool fasttrash;

		extern vector<string> blacklist_name;


		extern std::string itemdata_file;

		extern bool antibounce;
		extern bool modfly;
		extern bool modfly2;

		extern bool followplayer;
		extern CL_Vec2f TouchPos;
	}
	
}

struct charstate_t {
    int punchid = 0;
    int8_t buildrange = 0;
    int8_t punchrange = 0;
    int pupil_color;
    int eye_color;
    int eye_shade_color;
    int eff_flags1 = 0;
    int eff_flags2 = 0;
    float gravity = 1000.0f; //just in case we inject mid world, change gravity, but never receive 
    float speed = 250.f;
    float accel = 1200.f;
    float punch_strength = 300.f;
    float water_speed  = 125.f;

    void copy_from_packet(GameUpdatePacket* packet);

	//yeah in the 0.1% chance that we inject mid world and quickly change gravity etc
	//without ever receiving set state packet, then uninjecting, getting ping reply, and that would ban without copying info on inject.
	void copy_inject(NetAvatar* player, bool is_local); 
};
namespace global {
	extern App*			app;
	extern bool			unload;
	extern bool			d9init;
	extern HWND			hwnd;
	extern uintptr_t	gt;
	extern bool			load;
	extern bool			draw;
	extern std::string	version;
	extern float		fade;
	extern charstate_t	state;
	//	extern nlohmann::json m_cfg;
}

// clang-format on

