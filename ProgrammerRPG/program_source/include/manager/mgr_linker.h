/*
 * <제작 날짜>
 * 2017-11-11
 *
 * <파일 설명>
 * 게임 안에서 사용하는 매니저들을 통합 관리합니다.
 */

#ifndef PROGRAMMER_RPG__MANAGER_LINKER_H_
#define PROGRAMMER_RPG__MANAGER_LINKER_H_

#include "file_mgr.hpp"
#include "random_mgr.hpp"
#include "user_input_mgr.hpp"
#include "system_mgr.hpp"
#include "manager/obj_mgr.h"
#include "manager/scene_mgr.h"

// = &mgr::FileMgr::ObtainInstance()
extern mgr::FileMgr*      g_pFileMgr;
extern mgr::RandomMgr*    g_pRandMgr;
extern mgr::UserInputMgr* g_pUserInputMgr;
extern mgr::SceneMgr*     g_pSceneMgr;
extern mgr::ObjMgr*       g_pObjMgr;
extern mgr::SystemMgr*    g_pSystemMgr;

#endif