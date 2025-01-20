#include "stdafx.h"
#include "CBoss_Page2.h"

#include "LineMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "ObjMgr.h"
#include "SelectGDI.h"

#include "Player.h"
#include "CBossUI.h"

#include "CWill_Page2.h"

#include "CSound.h"

#include "CTimer.h"

CBoss_Page2::CBoss_Page2()
{
	m_SceneType = SCENE_TYPE::BOSS_PAGE2;
}

CBoss_Page2::~CBoss_Page2()
{
}

void CBoss_Page2::Enter()
{
	CLineMgr::Get_Instance()->Load_BossPage2_Line();
	CLineMgr::Get_Instance()->Initialize(SCENE_TYPE::BOSS_PAGE2);


	CWill_Page2* pWill = new CWill_Page2;
	pWill->Initialize(Vec2(800.f, 500.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS, pWill);


	CBossUI* pWillHp = new CBossUI;
	pWillHp->Initialize(2);
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pWillHp);







	CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
	pPlayer->Set_Pos(700.f, 500.f);



	CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"Boss_Page2_BGM");
	pNewSound->PlayToBGM(true);
	pNewSound->SetPosition(1.f); // 백분률 , 소리위치
	pNewSound->SetVolume(60.f); // 소리 볼륨 크기


	CCamera::CreateSingleTonInst()->FadeOut(5.f);



	CTimer* pTimerUI = new CTimer;
	pTimerUI->Initialize(Vec2(WINCX / 2.f, 130.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pTimerUI);

}

void CBoss_Page2::Initialize()
{
	m_pBossIntroTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Boss_Intro2", L"../API/Boss/intro2.png");
	m_pMapTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Boss_Page2", L"../API/Map/Boss_Page2.png");
}

void CBoss_Page2::Update()
{
	if (CCamera::CreateSingleTonInst()->IsEffectEnd())
	{
		CObjMgr::Get_Instance()->Update();
	}
}

void CBoss_Page2::Late_Update()
{
	if (CCamera::CreateSingleTonInst()->IsEffectEnd())
	{
		CObjMgr::Get_Instance()->Late_Update();
	}
}

void CBoss_Page2::Render(HDC hDC)
{
	if (CCamera::CreateSingleTonInst()->IsEffectEnd())
	{
		CScene::Render(hDC);
		CObjMgr::Get_Instance()->Render(hDC);
	}
	else
	{
		AlphaBlend(hDC
			, 0					// 이미지를 출력할 x
			, 0					// 이미지를 출력할 y
			, WINCX				// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
			, WINCY
			, m_pBossIntroTex->GetDC()
			, 0							// 가져올 이미지의 시작위치
			, 0
			, m_pBossIntroTex->Width() 					// 잘라낼 크기니까 항상 800 이여야함
			, m_pBossIntroTex->Height()
			, m_pBossIntroTex->GetBf());
	}
	
}



void CBoss_Page2::Exit()
{
	list<CLine*>& lineList = CLineMgr::Get_Instance()->GetLineList();
	for (auto& iter : lineList)
		Safe_Delete<CLine*>(iter);


	list<CObj*>& BossList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_BOSS);
	for (auto& iter : BossList)
		Safe_Delete<CObj*>(iter);


	list<CObj*>& BossSkillList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_BOSS_SKILL);
	for (auto& iter : BossSkillList)
		Safe_Delete<CObj*>(iter);


	list<CObj*>& UI = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_UI);

	for (auto iter = UI.begin(); iter != UI.end();)
	{
		

		CTimer* pTimer = dynamic_cast<CTimer*>(*iter);

		if (pTimer)
		{
			Safe_Delete<CObj*>(*iter);
			iter = UI.erase(iter);
		}
		else
			++iter;

	}



	lineList.clear();
	BossList.clear();
	BossSkillList.clear();
}
