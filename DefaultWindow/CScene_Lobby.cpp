#include "stdafx.h"
#include "CScene_Lobby.h"

#include "ObjMgr.h"
#include "CResMgr.h"

#include "CTexture.h"
#include "LineMgr.h"

#include "CNpc.h"
#include "CStoreNpc.h"
#include "CPotal.h"
#include "Player.h"

#include "CPet.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CSound.h"


CScene_Lobby::CScene_Lobby()
{
	m_SceneType = SCENE_TYPE::LOBBY;

}

CScene_Lobby::~CScene_Lobby()
{
}

void CScene_Lobby::Enter()
{
	if (!m_pNpc)
	{
		CNpc* pNpc = new CNpc;
		pNpc->Initialize();
		CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_NPC, pNpc);
		m_pNpc = pNpc;
	}

	if (!m_pStoreNpc)
	{
		CNpc* pNpc = new CStoreNpc;
		pNpc->Initialize();
		CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_NPC, pNpc);
		m_pStoreNpc = pNpc;
	}

	if (m_vecPotal.size() == 0)
	{
		CPotal* pPotal = new CPotal;
		pPotal->Initialize(Vec2(3900.f, 950.f),SCENE_TYPE::HUNTING_GROUND);
		CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_POTAL, pPotal);
		m_vecPotal.push_back(pPotal);


		CPotal* pPotal1 = new CPotal;
		pPotal1->Initialize(Vec2(120.f, 950.f), SCENE_TYPE::HUNTING_GROUND2);
		CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_POTAL, pPotal1);
		m_vecPotal.push_back(pPotal1);
	}
	

	CLineMgr::Get_Instance()->Load_Lobby_Line();
	CLineMgr::Get_Instance()->Initialize(SCENE_TYPE::LOBBY);


	if (SCENE_TYPE::HUNTING_GROUND == CSceneMgr::CreateSingleTonInst()->GetPreScene()->GetSceneType())
	{
		CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
		pPlayer->Set_Pos(3900.f, 1000.f);
		((CPlayer*)pPlayer)->GetMyPet()->Set_Pos(4000.f, 1000.f);

		Vec2 vPos = Vec2(3643.5f, 829.2f);					// 씬 전환시 카메라 이동 필요함 
		CCamera::CreateSingleTonInst()->SetLookAt(vPos);
	}
	else if (SCENE_TYPE::HUNTING_GROUND2 == CSceneMgr::CreateSingleTonInst()->GetPreScene()->GetSceneType())
	{
		CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
		pPlayer->Set_Pos(131.f, 1000.f);
		((CPlayer*)pPlayer)->GetMyPet()->Set_Pos(4000.f, 1000.f);

		Vec2 vPos = Vec2(640.f, 820.f);					// 씬 전환시 카메라 이동 필요함 
		CCamera::CreateSingleTonInst()->SetLookAt(vPos);
	}

	CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"Lobby_BGM");
	pNewSound->PlayToBGM(true);
	pNewSound->SetPosition(1.f); // 백분률 , 소리위치
	pNewSound->SetVolume(60.f); // 소리 볼륨 크기
	

	CCamera::CreateSingleTonInst()->FadeIn(2.f);
}

void CScene_Lobby::Initialize()
{
	m_pMapTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Lobby_Scene_Map", L"../API/Map/LobbyMap_final.png");

}

void CScene_Lobby::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CScene_Lobby::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CScene_Lobby::Render(HDC hDC)
{
	CScene::Render(hDC);

	CObjMgr::Get_Instance()->Render(hDC);
}



void CScene_Lobby::Exit()
{
	list<CLine*>& lineList = CLineMgr::Get_Instance()->GetLineList();
	for (auto& iter : lineList)
		Safe_Delete<CLine*>(iter);



	list<CObj*>& potalList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_POTAL);
	for (auto& iter : potalList)
		Safe_Delete<CObj*>(iter);



	m_vecPotal.clear();

	lineList.clear();
	potalList.clear();
}
