/*
 * <���� ��¥>
 * 2017-11-11
 *
 * <���� ����>
 * ���� �ȿ��� ����ϴ� �Ŵ������� ���� �����մϴ�.
 */

#include "manager/mgr_linker.h"

mgr::FileMgr*      g_pFileMgr      = &mgr::FileMgr::ObtainInstance();
mgr::RandomMgr*    g_pRandMgr      = &mgr::RandomMgr::ObtainInstance();
mgr::UserInputMgr* g_pUserInputMgr = &mgr::UserInputMgr::ObtainInstance();
mgr::ObjMgr*       g_pObjMgr       = &mgr::ObjMgr::ObtainInstance();
mgr::SceneMgr*     g_pSceneMgr     = &mgr::SceneMgr::ObtainInstance();
mgr::SystemMgr*    g_pSystemMgr    = &mgr::SystemMgr::ObtainInstance();