/*
 * <���� ��¥>
 * 2017-10-30
 *
 * <���� ����>
 * �Ŵ������� �����մϴ�.
 * �ʿ��� �Ŵ����� ����ϰ� �����ٰ� �� �� �ֽ��ϴ�.
 * �Ŵ������� ������ �ٸ��Ƿ� ����� ���۾����� �ؾ� �մϴ�.
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