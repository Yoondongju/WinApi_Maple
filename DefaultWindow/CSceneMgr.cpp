#include "stdafx.h"
#include "CSceneMgr.h"

#include "CScene.h"
#include "CScene_Lobby.h"
#include "CHuntingGround.h"
#include "CHuntingGround2.h"

#include "CCamera.h"

#include "ObjMgr.h"

#include "CBoss_Lobby.h"
#include "CBoss_Page1.h"
#include "CBoss_Page2.h"
#include "CBoss_Page3.h"

#include "CMiniGameScene.h"

CSceneMgr::CSceneMgr()
	: m_pCurScene(nullptr)
	, m_pPreScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{
	for (auto& iter : m_vecGameScene)
	{
		Safe_Delete<CScene*>(iter);
	}
	
}

void CSceneMgr::init()
{
	m_vecGameScene.push_back(new CScene_Lobby());
	m_vecGameScene.back()->Initialize();

	m_vecGameScene.push_back(new CHuntingGround());
	m_vecGameScene.back()->Initialize();

	m_vecGameScene.push_back(new CHuntingGround2());
	m_vecGameScene.back()->Initialize();

	m_vecGameScene.push_back(new CBoss_Lobby());
	m_vecGameScene.back()->Initialize();

	m_vecGameScene.push_back(new CBoss_Page1());
	m_vecGameScene.back()->Initialize();

	m_vecGameScene.push_back(new CBoss_Page2());
	m_vecGameScene.back()->Initialize();

	m_vecGameScene.push_back(new CBoss_Page3());
	m_vecGameScene.back()->Initialize();

	m_vecGameScene.push_back(new CMiniGameScene());
	m_vecGameScene.back()->Initialize();
	
	m_pCurScene = m_vecGameScene[SCENE_TYPE::LOBBY];
	m_pPreScene = m_pCurScene;
	m_pCurScene->Enter();
}

void CSceneMgr::Update()
{
	m_pCurScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pCurScene->Late_Update();

}

void CSceneMgr::Render(HDC hDC)
{
	m_pCurScene->Render(hDC);
}


void CSceneMgr::SceneChange(SCENE_TYPE _e)
{
	m_pCurScene->Exit();

	m_pPreScene = m_pCurScene;

	m_pCurScene = m_vecGameScene[_e];

	m_pCurScene->Enter();
}
