/*
 * <���� ��¥>
 * 2017-10-30
 *
 * <���� ����>
 * �Ŵ������� �����մϴ�.
 * �ʿ��� �Ŵ����� ����ϰ� �����ٰ� �� �� �ֽ��ϴ�.
 * �Ŵ������� ������ �ٸ��Ƿ� ����� ���۾����� �ؾ� �մϴ�.
 */

#ifndef EASIEST__MANAGER_LINKER_H_
#define EASIEST__MANAGER_LINKER_H_

// �Ŵ������� �����մϴ�.
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