#include "stdafx.h"
#include "CMiniGameScene.h"

#include "ObjMgr.h"
#include "CResMgr.h"

#include "CTexture.h"
#include "LineMgr.h"

#include "CNpc.h"

#include "Player.h"

#include "CPet.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CSound.h"
#include "CWall.h"
#include "CRail.h"

#include "CPlayerCart.h"

#include "CBoom.h"

#include "CTimeMgr.h"

#include "CMiniGameButton.h"

#include "CQuest.h"


CMiniGameScene::CMiniGameScene()
	: m_fCreateBoom(1.f)
	, m_bGameStart(false)
{
	m_SceneType = SCENE_TYPE::MINIGAME;
}

CMiniGameScene::~CMiniGameScene()
{
}

void CMiniGameScene::Enter()
{
	CWall* pWall = new CWall;
	pWall->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_WALL, pWall);			// 맵,레일,폭탄,카트 모두 OBJ_WALL으로 관리할거니까 생성시점이란 렌더시점 맞춰야함


	CRail* pRail = new CRail;
	pRail->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_WALL, pRail);


	CPlayerCart* pCart = new CPlayerCart;
	pCart->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MINIGAMEOBJ, pCart);


	CMiniGameButton* pBtn = new CMiniGameButton;
	pBtn->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pBtn);

	


	CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"MiniGame_BGM");
	pNewSound->PlayToBGM(true);
	pNewSound->SetPosition(1.f); // 백분률 , 소리위치
	pNewSound->SetVolume(60.f); // 소리 볼륨 크기



	// 반드시 미니게임 나갈때 원상복구 시켜야함 !!!!!!!!!!!!11
	//list<CObj*>& UIList= CObjMgr::Get_Instance()->Get_TypeObj(OBJ_UI);
	//for (auto& iter : UIList)
	//	iter->m_bNoRender = true;


	list<CObj*>& playerList = CObjMgr::Get_Instance()->Get_TypeObj(OBJ_PLAYER);
	for (auto& iter : playerList)
		iter->m_bNoRender = true;
	list<CObj*>& petList = CObjMgr::Get_Instance()->Get_TypeObj(OBJ_PET);
	for (auto& iter : petList)
		iter->m_bNoRender = true;



	CCamera::CreateSingleTonInst()->FadeIn(3.f);
}

void CMiniGameScene::Initialize()
{
	m_pMapTex = CResMgr::CreateSingleTonInst()->CreateTexture(L"back", WINCX, WINCY);

}

void CMiniGameScene::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMiniGameScene::Update()
{
	if (m_bGameStart)
	{
		if (m_fCreateBoom <= 0.f)
		{
			CBoom* pBoom = new CBoom;
			pBoom->Initialize();
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MINIGAMEOBJ, pBoom);

			m_fCreateBoom = 1.f;
		}
		m_fCreateBoom -= fDT;
	}
	
	CObjMgr::Get_Instance()->Update();
}

void CMiniGameScene::Render(HDC hDC)
{
	

	CObjMgr::Get_Instance()->Render(hDC);
}



void CMiniGameScene::Exit()
{
	list<CObj*>& UIList = CObjMgr::Get_Instance()->Get_TypeObj(OBJ_UI);
	for (auto& iter : UIList)
		iter->m_bNoRender = false;
	list<CObj*>& playerList = CObjMgr::Get_Instance()->Get_TypeObj(OBJ_PLAYER);
	for (auto& iter : playerList)
		iter->m_bNoRender = false;
	list<CObj*>& petList = CObjMgr::Get_Instance()->Get_TypeObj(OBJ_PET);
	for (auto& iter : petList)
		iter->m_bNoRender = false;





	list<CObj*>& wallList = CObjMgr::Get_Instance()->Get_TypeObj(OBJ_WALL);
	for (auto& iter : wallList)
		Safe_Delete(iter);


	list<CObj*>& minigameList = CObjMgr::Get_Instance()->Get_TypeObj(OBJ_MINIGAMEOBJ);
	for (auto& iter : minigameList)
		Safe_Delete(iter);




	CQuest* playerQuest = ((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->GetQuest();
	if (QUEST_TYPE::MINIGAME == playerQuest->GetCurQuest())
	{
		playerQuest->SetSuccess(true);
	}


	wallList.clear();
	minigameList.clear();	
}