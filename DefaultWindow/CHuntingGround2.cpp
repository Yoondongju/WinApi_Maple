#include "stdafx.h"
#include "CHuntingGround2.h"

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

#include "CKariainUI.h"
#include "CKariain.h"

#include "CTimeMgr.h"
#include "CExecutor.h"

#include "CWarringUI.h"

#include "CTimer.h"


CHuntingGround2::CHuntingGround2()
	: m_fCreateLMDelay(25.f)   // 수정해야함 늦게
	, m_pKariain(nullptr )
{
	m_SceneType = SCENE_TYPE::HUNTING_GROUND2;

}

CHuntingGround2::~CHuntingGround2()
{
	m_pKariain = nullptr;
}

void CHuntingGround2::Initialize()
{
	m_pMapTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Hunting_Scene_Map2", L"../API/Map/HuntingMap2.png");
}


void CHuntingGround2::Enter()
{


	CExecutor* pBerarion = new CExecutor;
	pBerarion->Initialize(Vec2(1640.f, 100.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, pBerarion);


	CExecutor* pBerarion4 = new CExecutor;
	pBerarion4->Initialize(Vec2(1620.f, 100.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, pBerarion4);
	
	
	
	CExecutor* pBerarion2 = new CExecutor;
	pBerarion2->Initialize(Vec2(996.f, 890.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, pBerarion2);
	

	
	CExecutor* pBerarion3 = new CExecutor;
	pBerarion3->Initialize(Vec2(345.f, 643.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, pBerarion3);
	
	
	
	CExecutor* pBerarion5 = new CExecutor;
	pBerarion5->Initialize(Vec2(2700.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, pBerarion5);
	
	

	CExecutor* pBerarion6 = new CExecutor;
	pBerarion6->Initialize(Vec2(1002.f, 362.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, pBerarion6);
	
	
	CExecutor* pBerarion7 = new CExecutor;
	pBerarion7->Initialize(Vec2(3200.f, 400.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, pBerarion7);



	CExecutor* pBerarion8 = new CExecutor;
	pBerarion8->Initialize(Vec2(2258.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, pBerarion8);



	CExecutor* pBerarion9 = new CExecutor;
	pBerarion9->Initialize(Vec2(3200.f, 400.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, pBerarion9);


	




	if (m_vecPotal.size() == 0)
	{
		CPotal* pPotal = new CPotal;
		pPotal->Initialize(Vec2(200.f, 1100.f), SCENE_TYPE::LOBBY);
		CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_POTAL, pPotal);
		m_vecPotal.push_back(pPotal);

	}


	CLineMgr::Get_Instance()->Load_Hunting2_Line();
	CLineMgr::Get_Instance()->Initialize(SCENE_TYPE::HUNTING_GROUND2);



	if (SCENE_TYPE::LOBBY == CSceneMgr::CreateSingleTonInst()->GetPreScene()->GetSceneType())
	{
		CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
		pPlayer->Set_Pos(200.f, 1150.f);
		((CPlayer*)pPlayer)->GetMyPet()->Set_Pos(100.f, 1150.f);



		Vec2 vPos = Vec2(640.f, 972.f);					// 씬 전환시 카메라 이동 필요함 
		CCamera::CreateSingleTonInst()->SetLookAt(vPos);
	}


	CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"Hunting2_First_BGM");
	pNewSound->PlayToBGM(true);
	pNewSound->SetPosition(1.f); // 백분률 , 소리위치
	pNewSound->SetVolume(70.f); // 소리 볼륨 크기


	CCamera::CreateSingleTonInst()->FadeIn(2.f);
}



void CHuntingGround2::Update()
{
	if (CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_BOSS).size() > 0)
	{
		CObjMgr::Get_Instance()->Update();
		return;
	}


	if (m_fCreateLMDelay <= 5.f)
	{
		static bool bCheck = false;
		if (!bCheck)
		{
			CWarringUI* pWarringUI = new CWarringUI;
			pWarringUI->Initialize();
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pWarringUI);

			bCheck = true;
		}
	}

	
	if (m_fCreateLMDelay <= 0.f)
	{ 
		static bool bCheck = false;
		if (!bCheck)
		{
			CCamera::CreateSingleTonInst()->FadeOut(3.f);
			bCheck = true;
		}	
	}

	if (!m_pKariain && m_fCreateLMDelay <= 0.f && CCamera::CreateSingleTonInst()->IsEffectEnd())
	{
		list<CObj*>& MonList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_MONSTER);
		for (auto& iter : MonList)
			Safe_Delete<CObj*>(iter);

		list<CObj*>& MesoList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_MESO);
		for (auto& iter : MesoList)
			Safe_Delete<CObj*>(iter);

		MonList.clear();
		MesoList.clear();

		CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"Hunting2_Second_BGM");
		pNewSound->PlayToBGM(true);
		pNewSound->SetPosition(1.f); // 백분률 , 소리위치
		pNewSound->SetVolume(70.f); // 소리 볼륨 크기


		Vec2 vPos = CObjMgr::Get_Instance()->Get_Player()->GetPos();

		CKariain* p = new CKariain;
		p->Initialize(vPos);			// 플레이어 앞에 나타남
		CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS, p);
		m_pKariain = p;


		CKariainUI* pKariUI = new CKariainUI;
		pKariUI->Initialize(p);
		CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pKariUI);


		CTimer* pTimerUI = new CTimer;
		pTimerUI->Initialize();
		CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pTimerUI);
	}



	m_fCreateLMDelay -= fDT;
	CObjMgr::Get_Instance()->Update();
}

void CHuntingGround2::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CHuntingGround2::Render(HDC hDC)
{
	CScene::Render(hDC);

	CObjMgr::Get_Instance()->Render(hDC);
}


void CHuntingGround2::Exit()
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
