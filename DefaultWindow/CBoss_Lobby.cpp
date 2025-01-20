#include "stdafx.h"
#include "CBoss_Lobby.h"

#include "LineMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "ObjMgr.h"
#include "SelectGDI.h"

#include "Player.h"

#include "CConversationUI.h"

#include "CSound.h"

CBoss_Lobby::CBoss_Lobby()
	: m_pConversationUI(nullptr)
{
	m_SceneType = SCENE_TYPE::BOSS_LOBBY;
}

CBoss_Lobby::~CBoss_Lobby()
{
}

void CBoss_Lobby::Enter()
{
	CLineMgr::Get_Instance()->Load_BossLobby_Line();
	CLineMgr::Get_Instance()->Initialize(SCENE_TYPE::BOSS_LOBBY);


	CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
	pPlayer->Set_Pos(700.f, 500.f);


	CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"Boss_Lobby_BGM");
	pNewSound->PlayToBGM(true);
	pNewSound->SetPosition(1.f); // 백분률 , 소리위치
	pNewSound->SetVolume(60.f); // 소리 볼륨 크기


	CCamera::CreateSingleTonInst()->FadeIn(2.f);
}

void CBoss_Lobby::Initialize()
{
	m_vRecogPos = Vec2(1267.f, 900.f);
	m_vRecogSize = Vec2(300.f,300.f);

	m_pMapTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Boss_Lobby", L"../API/Map/Boss_Lobby.png");
}

void CBoss_Lobby::Update()
{
	CObjMgr::Get_Instance()->Update();


	CPlayer* pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();
	Vec2 vPos = pPlayer->GetPos();
	Vec2 vSize = pPlayer->GetSize();

	float	fWidth = abs(vPos.x - m_vRecogPos.x);
	float	fHeight = abs(vPos.y - m_vRecogPos.y);

	float	fRadiusX = (vSize.x + m_vRecogSize.x) * 0.5f;
	float	fRadiusY = (vSize.y + m_vRecogSize.y) * 0.5f;

	if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))	// 충돌
	{
		if (!m_pConversationUI)
		{
			CConversationUI* pUI = new CConversationUI;
			pUI->Initialize(NPC_TYPE::BOSS_SIGN);
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pUI);
			m_pConversationUI = pUI;
		}	
	}
	else
	{
		list<CObj*>& UIList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_UI);
		list <CObj*>::iterator iter = UIList.begin();

		for (iter; iter != UIList.end();)
		{
			if (m_pConversationUI == (*iter))
			{
				Safe_Delete<CPlayerUI*>(m_pConversationUI);		// ObjMgr에서 지워주는건 씬 나갈때 할거임 
				iter = UIList.erase(iter);
			}
			else
				++iter;
		}

	}


}

void CBoss_Lobby::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CBoss_Lobby::Render(HDC hDC)
{
	CScene::Render(hDC);

	CObjMgr::Get_Instance()->Render(hDC);



	//SelectGDI p(hDC, PEN_TYPE::RED);
	//SelectGDI b(hDC, BRUSH_TYPE::HOLLOW);
	//
	//
	//
	//Vec2 vPos = CCamera::CreateSingleTonInst()->GetRenderPos(m_vRecogPos);
	//
	//Rectangle(hDC
	//	, (int)(vPos.x - m_vRecogSize.x / 2.f)
	//	, (int)(vPos.y - m_vRecogSize.y / 2.f)
	//	, (int)(vPos.x + m_vRecogSize.x / 2.f)
	//	, (int)(vPos.y + m_vRecogSize.y / 2.f));

}



void CBoss_Lobby::Exit()
{
	list<CLine*>& lineList = CLineMgr::Get_Instance()->GetLineList();
	for (auto& iter : lineList)
		Safe_Delete<CLine*>(iter);
	lineList.clear();

}
