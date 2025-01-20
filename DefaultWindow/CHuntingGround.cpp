#include "stdafx.h"
#include "CHuntingGround.h"

#include "ObjMgr.h"
#include "CResMgr.h"

#include "CTexture.h"
#include "LineMgr.h"

#include "CNpc.h"
#include "CStoreNpc.h"
#include "CPotal.h"
#include "Player.h"
#include "CPet.h"

#include "CBerarion.h"
#include "CSceneMgr.h"

#include "CSound.h"



CHuntingGround::CHuntingGround()
{
	m_SceneType = SCENE_TYPE::HUNTING_GROUND;
	
}

CHuntingGround::~CHuntingGround()
{

}

void CHuntingGround::Initialize()
{
	m_pMapTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Hunting_Scene_Map", L"../API/Map/HuntingMap_final.png");
}


void CHuntingGround::Enter()
{
	if (m_vecPotal.size() == 0)
	{
		CPotal* pPotal = new CPotal;
		pPotal->Initialize(Vec2(200.f, 1250.f), SCENE_TYPE::LOBBY);
		CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_POTAL, pPotal);
		m_vecPotal.push_back(pPotal);

	}


	// 몬스터 소환 //
	CBerarion* pBerarion = new CBerarion;
	pBerarion->Initialize(Vec2(220.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, pBerarion);
	
	CBerarion* pBerarion4 = new CBerarion;
	pBerarion4->Initialize(Vec2(750.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, pBerarion4);
	
	
	
	CBerarion* pBerarion2 = new CBerarion;
	pBerarion2->Initialize(Vec2(1500.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, pBerarion2);
	
	
	CBerarion* pBerarion3 = new CBerarion;
	pBerarion3->Initialize(Vec2(2200.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, pBerarion3);
	
	
	
	CBerarion* pBerarion5 = new CBerarion;
	pBerarion5->Initialize(Vec2(1900.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, pBerarion5);
	
	
	CBerarion* pBerarion6 = new CBerarion;
	pBerarion6->Initialize(Vec2(2500.f, 1000.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, pBerarion6);
	
	
	CBerarion* pBerarion7 = new CBerarion;
	pBerarion7->Initialize(Vec2(1300.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, pBerarion7);






	CLineMgr::Get_Instance()->Load_Hunting1_Line();
	CLineMgr::Get_Instance()->Initialize(SCENE_TYPE::HUNTING_GROUND);

	

	if (SCENE_TYPE::LOBBY == CSceneMgr::CreateSingleTonInst()->GetPreScene()->GetSceneType())
	{
		CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
		pPlayer->Set_Pos(200.f, 1250.f);
		((CPlayer*)pPlayer)->GetMyPet()->Set_Pos(180.f, 1250.f);



		Vec2 vPos = Vec2(640.f, 1093.8f);					// 씬 전환시 카메라 이동 필요함 
		CCamera::CreateSingleTonInst()->SetLookAt(vPos);
	}
	else
	{

	}

	CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"Hunting1_BGM");
	pNewSound->PlayToBGM(true);
	pNewSound->SetPosition(1.f); // 백분률 , 소리위치
	pNewSound->SetVolume(60.f); // 소리 볼륨 크기


	CCamera::CreateSingleTonInst()->FadeIn(2.f);

}



void CHuntingGround::Update()
{
	CObjMgr::Get_Instance()->Update();


	

}

void CHuntingGround::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CHuntingGround::Render(HDC hDC)
{
	CScene::Render(hDC);

	CObjMgr::Get_Instance()->Render(hDC);
}


void CHuntingGround::Exit()
{
	list<CLine*>& lineList = CLineMgr::Get_Instance()->GetLineList();

	for (auto& iter : lineList)
		Safe_Delete<CLine*>(iter);



	list<CObj*>& potalList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_POTAL);
	for (auto& iter : potalList)
		Safe_Delete<CObj*>(iter);


	list<CObj*>& MonList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_MONSTER);
	for (auto& iter : MonList)
		Safe_Delete<CObj*>(iter);


	list<CObj*>& MesoList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_MESO);
	for (auto& iter : MesoList)
		Safe_Delete<CObj*>(iter);
	

	m_vecPotal.clear();
	lineList.clear();
	MonList.clear();
	MesoList.clear();
	potalList.clear();
}
