/*
 * <제작 날짜>
 * 2017-10-30
 *
 * <파일 설명>
 * 매니저들을 관리합니다.
 * 필요한 매니저를 등록하고 가져다가 쓸 수 있습니다.
 * 매니저마다 형식이 다르므로 등록은 수작업으로 해야 합니다.
 */

#include "manager_linker.h"

mgr::FileMgr*          g_pFileMgr      = &mgr::FileMgr::ObtainInstance();
mgr::GameMgr*          g_pGameMgr      = &mgr::GameMgr::ObtainInstance();
mgr::ObjMgr*           g_pObjectMgr    = &mgr::ObjMgr::ObtainInstance();
mgr::RandomMgr*        g_pRandomMgr    = &mgr::RandomMgr::ObtainInstance();
mgr::SoundMgr*         g_pSoundMgr     = &mgr::SoundMgr::ObtainInstance();
mgr::StageMgr*         g_pStageMgr     = &mgr::StageMgr::ObtainInstance();
mgr::SystemMgr*        g_pSystemMgr    = &mgr::SystemMgr::ObtainInstance();
mgr::TimeMgr*          g_pTimeMgr      = &mgr::TimeMgr::ObtainInstance();
mgr::UserInputMgr*     g_pUserInputMgr = &mgr::UserInputMgr::ObtainInstance();