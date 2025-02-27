#pragma once
#include <core/gt.h>
#include <core/utils.h>
#include <hooks/ProcessTankUpdatePacket.h>
#include <hooks/SendPacket.h>
#include <hooks/SendPacketRaw.h>
#include <hooks/Update.h>
#include <hooks/hooks.h>
#include <intrin.h>
#include <menu\menu.h>
#include <sdk/sdk.h>
#include <stdio.h>
#include <iomanip>
#include <thread>
#include <set>
#include "PathFinder/PathFinder.h"
#include <PathFinder/Astar.hpp>
#include <Keyauth/Xor.h>
//#include "PathFinder/AStar.h"

WNDPROC hooks::wndproc; //special cases which dont follow normal pattern
LPVOID hooks::endscene;

hookmanager* hookmgr = new hookmanager();
bool canrender = false;

static int map5[60][100];

static void updatemap() {
    
}

static void pathFinder()
{
    std::vector<int> iData = { 2250, 2248 };
    auto logic = sdk::GetGameLogic();
    auto w = logic->GetWorld();
    auto l = sdk::GetGameLogic()->GetLocalPlayer();
    auto t = logic->GetTileMap();
    int posX = l->GetPos().x / 32, posY = l->GetPos().y / 32;
    int X = opt::cheat::TouchPos.x, Y = opt::cheat::TouchPos.y;

    opt::cheat::pfdone = true;

    static std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now() - std::chrono::milliseconds(100);

    if (w)
    {
        AStar::Generator pFind;
        pFind.setWorldSize({ w->tilemap.size.x, w->tilemap.size.y });
        pFind.setHeuristic(AStar::Heuristic::manhattan);

        for (auto& tile : t->tiles)
        {
            if (tile.foreground && tile.foreground != 482 && tile.foreground != 6)
            {
                pFind.addCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 11186 && tile.flags == 25) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 1240 && tile.flags == 57) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 2586 && tile.flags == 33) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 2586 && tile.flags == 1) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 2246 && tile.flags == 33) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 6214 && tile.flags == 33) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 998 && tile.flags == 32) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 762 && tile.flags == -15871) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 1420 && tile.flags == 1) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 2414 && tile.flags == 33) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 2244 && tile.flags == 33) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 1436 && tile.flags == 33) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 1684 && tile.flags == 33) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 608 && tile.flags == 1) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 598 && tile.flags == 192) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 4722 && tile.flags == 1) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 4482 && tile.flags == 1) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 410 && tile.flags == 64) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
            if (tile.foreground == 3818 && tile.flags == 1) {
                pFind.removeCollision({ tile.position_x, tile.position_y });
            }
        }
        consts::set_float(0, 0);

        vector<AStar::CL_Vec2f> way = pFind.findPath({ posX, posY }, { X, Y });
        std::reverse(way.begin(), way.end());

        if (!way.empty())
        {
            if (way.size() > 1)
            {
                for (int i = 0; i < way.size(); i++)
                {


                    GameUpdatePacket packet{ 0 };
                    packet.type = PACKET_STATE;
                    packet.int_x = way[i].x;
                    packet.int_y = way[i].y;
                    packet.pos_x = way[i].x * 32;
                    packet.pos_y = way[i].y * 32;
                    packet.vec_x = way[i].x * 32;
                    packet.vec_y = way[i].y * 32;
                    packet.flags = 32 | (1 << 10) | (1 << 11);

                    if (i % 5 == 0 || i == 0)
                    {
                        if (std::chrono::high_resolution_clock::now() - start_time >= std::chrono::milliseconds(100))
                        {
                            start_time = std::chrono::high_resolution_clock::now();

                            gt::send(&packet);
                        }
                    }

                    l->SetPosAtTile(way[i].x, way[i].y);
                    std::this_thread::sleep_for(20ms);
                }
            }
            else
            {
                if (std::chrono::high_resolution_clock::now() - start_time >= std::chrono::milliseconds(1000))
                {
                    start_time = std::chrono::high_resolution_clock::now();

                    gt::sendlog(XorStr("You landed on the same position you were!").c_str());
                }
            }
        }
        else
        {
            if (std::chrono::high_resolution_clock::now() - start_time >= std::chrono::milliseconds(1000))
            {
                start_time = std::chrono::high_resolution_clock::now();

                gt::sendlog(XorStr("`#Blocked!").c_str());
            }
        }
        consts::set_float(0, 400);
        opt::cheat::pfdone = false;
        opt::cheat::PathFindinglol = false;
    }
}

void hooks::init_endscene() {   
    if (global::d9init)
        return;

    auto s_renderD3D9 = *(uintptr_t*)sigs::get(sig::s_renderd3d9);

    if (!s_renderD3D9)
        return;

    //source for s_RenderD3D9: https://github.com/bkaradzic/bgfx/blob/master/src/renderer_d3d9.cpp
    //the dx9 rendering device that GT (bgfx) uses as well

    auto m_d3d9ex = *(IDirect3D9Ex**)(s_renderD3D9 + 312);
    void** vtable = nullptr;
    if (m_d3d9ex) { //bgfx proefers m_deviceEx if m_d3d9ex exists
        auto m_deviceEx = *(IDirect3DDevice9Ex**)(s_renderD3D9 + 320);
        if (!m_deviceEx) {
            auto m_device = *(IDirect3DDevice9**)(s_renderD3D9 + 336);
            if (!m_device)
                return;
            vtable = *reinterpret_cast<void***>(m_device);
        }
        vtable = *reinterpret_cast<void***>(m_deviceEx);
    }
    else {
        auto m_device = *(IDirect3DDevice9**)(s_renderD3D9 + 336);
        if (!m_device)
            return;
        vtable = *reinterpret_cast<void***>(m_device);
    }
    if (!vtable)
        return;
    global::d9init = true;
    MH_CreateHook(LPVOID(vtable[42]), EndScene, (void**)(&hooks::endscene));
    MH_EnableHook(LPVOID(vtable[42]));
    utils::printc("93", "Hooked endscene");
}

void hooks::init() {
    global::hwnd = FindWindowA(nullptr, "Growtopia");

    init_endscene();

    //hooks can now be found in sigs.cpp, they are directly set up there
    for (auto hk : hookmgr->hooks)
        MH_CreateHook(hk->address, hk->hooked, &hk->orig);

    if (!global::hwnd)
        printf("TESTING: HWND not found\n");

    wndproc = WNDPROC(SetWindowLongPtrW(global::hwnd, -4, LONG_PTR(WndProc)));

    MH_EnableHook(MH_ALL_HOOKS);
    utils::printc("93", "Hooks have been setup!");
    //DrawString("The quick brown fox jumped over the lazy dog", 16, 20, 0, 0, 0, 1);
}

void hooks::destroy() {
    UpdateManager::OnDestroy();

    //I mean, I can't be bothered to deal with this, so let's just restore this sig in case we re-inject
    //it does not matter anyways cuz this is in App::Init and won't be called again.
    auto mutex2 = sigs::get(sig::mutexbypass2);
    utils::patch_bytes<6>(mutex2, "\xB9\x01\x00\x1F\x00\xFF");
    SetWindowLongPtr(global::hwnd, -4, LONG_PTR(wndproc));
RETRY:
    if (MH_OK != MH_DisableHook(MH_ALL_HOOKS)) {
        auto res = MessageBox(GetForegroundWindow(), L"Hooks could not be reverted", L"Internal", MB_ABORTRETRYIGNORE | MB_ICONERROR | MB_TOPMOST);
        switch (res) {
            case IDABORT:
                while (!TerminateProcess(GetCurrentProcess(), EXIT_SUCCESS))
                    ;
            case IDRETRY: goto RETRY;
            case IDIGNORE: // just ignore
                break;
        }
    }
}

void __cdecl hooks::BaseApp_SetFPSLimit(BaseApp* ba, float fps) {
    static auto orig = decltype(&hooks::BaseApp_SetFPSLimit)(hookmgr->orig(sig::baseapp_setfpslimit));
    orig(ba, opt::fps_limit);
}

int __cdecl hooks::LogMsg(const char* msg, ...) {
    static auto orig = decltype(&hooks::LogMsg)(hookmgr->orig(sig::logmsg));
    char buf[0x1000u];
    int len = -1;
    va_list va;
    va_start(va, msg);
    if (0 > (len = _vsnprintf_s(buf, sizeof(buf), msg, va))) {
        va_end(va);
        return 0;
    }
    va_end(va);

    if (len < 90 && len > 2) {
        if (logging::enabled && logging::console & logging::logmsg)
            utils::printc("88", "LogMsg\t%s", buf);
    }
    return orig(buf);
}

bool __cdecl hooks::NetAvatar_CanMessageT4(NetAvatar* player) {
    utils::printc("1;40;31", "CanMessageT4 called, there is a chance of ban, so automatically left the world.");
    if(!opt::custom_server_on)
    gt::send(3, "action|quit_to_exit");
    return false;
}

bool active = false;
LRESULT __stdcall hooks::WndProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    active = GetActiveWindow() == global::hwnd;

    //TODO: with imgui
    if (menu::WndProc(wnd, msg, wparam, lparam))
        return true;

    if (msg == WM_KEYDOWN && (wparam == VK_CONTROL || wparam == VK_LCONTROL || wparam == VK_RCONTROL))
        return true;

    /*if (msg == WM_KEYUP && wparam == VK_F3) //TODO: customization to these keybinds
        global::unload = true;*/

    if (msg == WM_KEYUP && wparam == VK_F7) { //Convenient way for me when checking accs, to go to their worlds from cli
        auto cboard = utils::get_clipboard();
        if (cboard.find("error") != -1)
            printf("Couldn't get clipboard data.\n");
        else {
            std::string packet = "action|join_request\nname|" + cboard + "\ninvitedWorld|0";
            gt::send(NET_MESSAGE_GAME_MESSAGE, packet, false);
        }
    }
    if (msg == WM_KEYUP && wparam == VK_F8) {
        std::string packet = "action|input|\ntext|/go";
        gt::send(2, packet, true);
    }

    return CallWindowProcW(hooks::wndproc, wnd, msg, wparam, lparam);
}

void __cdecl hooks::SendPacketRaw(int type, GameUpdatePacket* packet, int size, void* packetsender, ENetPeer* peer, int flag) {
    SendPacketRawHook::Execute(type, packet, size, packetsender, peer, flag);
}

void __cdecl hooks::HandleTouch(LevelTouchComponent* touch, CL_Vec2f pos, bool started) {
    static auto orig = decltype(&hooks::HandleTouch)(hookmgr->orig(sig::handletouch));

    //TODO: WorldCamera::WorldToScreen to check if pos is within imgui menu when global::draw

    auto rend = sdk::GetGameLogic()->renderer;
    if (rend && global::draw && active) {
        //   auto screen = rend->GetCamera()->WorldToScreen(pos);
        //   auto screen = rend->GetCamera()->WorldToScreen(pos);

        auto screen = rend->GetCamera()->WorldToScreen(pos);

        //     auto pos = ImGui::GetWindowPos();
        //   auto size = ImGui::GetWindowSize();
        //     auto pos = ImGui::GetWindowPos();
        //   auto size = ImGui::GetWindowSize();
        //imgui cant call these during this time so just save them somewhere when not lazy

        /* if (screen.x >= pos.x && screen.x <= (pos.x + size.x) && screen.y >= pos.y && screen.y <= (pos.y + size.y)) {
        /* if (screen.x >= pos.x && screen.x <= (pos.x + size.x) && screen.y >= pos.y && screen.y <= (pos.y + size.y)) {
            printf("good for us?\n");
        }*/
        //  return;
        //  return;
    }
    auto logic = sdk::GetGameLogic();
    auto tilemap = logic->GetTileMap();
    opt::cheat::TouchPos.x = pos.x / 32;
    opt::cheat::TouchPos.y = pos.y / 32;
    if (GetAsyncKeyState(VK_SHIFT) && logic->GetLocalPlayer()) {
        if (!opt::cheat::TouchPos.x == 0 && !opt::cheat::TouchPos.y == 0) {
            std::thread t(&pathFinder);
            t.detach();
        }
    }
    auto draw = ImGui::GetBackgroundDrawList();
    if (opt::cheat::tp_click && GetAsyncKeyState(VK_CONTROL)) {
        //localplayer is guaranteed to be a valid pointer here according to xrefs
        auto local = sdk::GetGameLogic()->GetLocalPlayer();
        auto new_pos = pos - (local->GetSize() / 2.f);
        local->SetPos(new_pos);
        pos = new_pos;
    }
    if (GetAsyncKeyState(VK_CONTROL)) {
        return;
    }
    if (!(GetAsyncKeyState(VK_CONTROL) && opt::cheat::autopunchplayer)) {
        orig(touch, pos, started);
    }
        //orig(touch, pos, started);
}

void __cdecl hooks::WorldCamera_OnUpdate(WorldCamera* camera, CL_Vec2f unk, CL_Vec2f unk2) {
    static auto orig = decltype(&hooks::WorldCamera_OnUpdate)(hookmgr->orig(sig::worldcamera_onupdate));
    if (opt::cheat::tp_click && GetAsyncKeyState(VK_CONTROL)) //if we dont do this then there is major sliding when teleporting.
        return;
    if (opt::cheat::pathfinder && GetAsyncKeyState(VK_SHIFT)) //if we dont do this then there is major sliding when teleporting.
        return;

    orig(camera, unk, unk2);
}

void __cdecl hooks::SendPacket(int type, std::string& packet, ENetPeer* peer) {
    SendPacketHook::Execute(type, packet, peer);
}



void __cdecl hooks::ProcessTankUpdatePacket(GameLogic* logic, GameUpdatePacket* packet) {
    ProcessTankUpdatePacketHook::Execute(logic, packet);
}

bool __cdecl hooks::CanSeeGhosts(int id) {
    static auto orig = decltype(&hooks::CanSeeGhosts)(hookmgr->orig(sig::canseeghosts));
    if (opt::cheat::see_ghosts)
        return true;
    return orig(id);
}


long __stdcall hooks::EndScene(IDirect3DDevice9* device) {
    static auto orig = decltype(&hooks::EndScene)(endscene);
    menu::EndScene(device, active); //Imgui happens here
    return orig(device);
}

//ideal hook for all kinds of continuous loops and also conveniently gets us app
void __cdecl hooks::App_Update(App* app) {
    UpdateManager::Execute(app);
}

void __cdecl hooks::TileExtra_Serialize(TileExtra* te, uint8_t* mem, uint32_t* pos, bool save1, World* world, bool save2, Tile* target, int version) { // fixed 3.64 crash
    static auto orig = decltype(&hooks::TileExtra_Serialize)(hookmgr->orig(sig::tileextra_serialize));
    orig(te, mem, pos, save1, world, save2, target, version);
    if (te->type == 3 && target->tile_extra) {
        printf("\n\n[Tile access list]\nID: %d\n", target->foreground);
        utils::printc("96", "Owner: %d", target->tile_extra->owner);
        for (auto id : target->tile_extra->access_list)
            utils::printc("92", "\t%d", id);

        printf("\n");
    }
}

void __cdecl hooks::OnPunched(NetAvatar* local, CL_Vec2f pos, NetAvatar* puncher) {
    static auto orig = decltype(&hooks::OnPunched)(hookmgr->orig(sig::onpunched));

    if (!opt::cheat::antipunch)
        orig(local, pos, puncher);
}

float __cdecl hooks::GetFruitBloomProgressPercent(Tile* tile) {
    static auto orig = decltype(&hooks::GetFruitBloomProgressPercent)(hookmgr->orig(sig::getfruitbloompercent));

    if (opt::cheat::see_fruits)
        return 1.0f; //more than 1.0 is possible and makes trees bigger than normal, ig you can add it if you are interested
    else
        return orig(tile);
}

bool __cdecl hooks::DialogIsOpened(GameLogic* logic) {
    static auto orig = decltype(&hooks::DialogIsOpened)(hookmgr->orig(sig::dialogisopened));

    if (opt::cheat::dialog_cheat)
        return false;
    else
        return orig(logic);
}
