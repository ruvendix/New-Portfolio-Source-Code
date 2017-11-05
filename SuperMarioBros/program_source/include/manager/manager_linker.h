/*
 * <제작 날짜>
 * 2017-10-30
 *
 * <파일 설명>
 * 매니저들을 관리합니다.
 * 필요한 매니저를 등록하고 가져다가 쓸 수 있습니다.
 * 매니저마다 형식이 다르므로 등록은 수작업으로 해야 합니다.
 */

#ifndef EASIEST__MANAGER_LINKER_H_
#define EASIEST__MANAGER_LINKER_H_

// 매니저들을 포함합니다.
#include "obj_mgr.h"
#include "file_mgr.hpp"
#include "game_mgr.h"
#include "random_mgr.hpp"
#include "sound_mgr.hpp"
#include "stage_mgr.h"
#include "system_mgr.hpp"
#include "time_mgr.hpp"
#include "user_input_mgr.hpp"

extern    mgr::FileMgr*          g_pFileMgr;
extern    mgr::GameMgr*          g_pGameMgr;
extern    mgr::ObjMgr*           g_pObjectMgr;
extern    mgr::RandomMgr*        g_pRandomMgr;
extern    mgr::SoundMgr*         g_pSoundMgr;
extern    mgr::StageMgr*         g_pStageMgr;
extern    mgr::SystemMgr*        g_pSystemMgr;
extern    mgr::TimeMgr*          g_pTimeMgr;
extern    mgr::UserInputMgr*     g_pUserInputMgr;

#endif