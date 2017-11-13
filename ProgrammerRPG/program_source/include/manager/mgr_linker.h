/*
 * <���� ��¥>
 * 2017-11-11
 *
 * <���� ����>
 * ���� �ȿ��� ����ϴ� �Ŵ������� ���� �����մϴ�.
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