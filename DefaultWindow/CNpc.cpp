#include "stdafx.h"
#include "CNpc.h"


#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "ObjMgr.h"
#include "SelectGDI.h"
#include "CTexture.h"

#include "CConversationUI.h"
#include "CQuest.h"

#include "Player.h"


CNpc::CNpc()
	:m_bRecognize(false)
{
	ZeroMemory(&m_rtRecognize, sizeof(RECT));
}

CNpc::~CNpc()
{
}

void CNpc::Initialize()
{
	m_tInfo = { 800.f, WINCY - 300.f , 60.f , 60.f };
	
	m_eObjType = OBJID::OBJ_NPC;
	m_eNpcType = NPC_TYPE::TALK;

	wstring	str = L"  레인";
	INFO tInfo = { m_tInfo.fX, m_tInfo.fY + 40.f, 90.f,20.f };
	CTexture* pNameTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"NameTex", L"../API/UI/NameBackground.png");

	m_tNameUI = NameUI(str, tInfo, pNameTex);


	CreateAnimator();					// 항상 애니메이터 만들기전에 ObjType 정해줘야함!!!!!!!!!!1

	CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"npc_stand", L"../API/UI/NPC_RAIN_STAND.png");
	GetAnimator()->CreateAnimation(L"npc_stand", pTex, Vec2(0.f, 0.f), Vec2(56.f, 55.f), Vec2(56.f, 0.f), 0.3f, 3);

	GetAnimator()->Play(L"npc_stand", true);




	CQuest* pQuest = new CQuest;								// npc 만들자마자 그에따른 퀘스트도 동시존재
	pQuest->Initialize(Vec2(m_tInfo.fX, m_tInfo.fY - 50));
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BACKGROUD, pQuest);
	((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->SetQuest(pQuest);
}

int CNpc::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	m_rtRecognize.left = m_tRect.left - 40;
	m_rtRecognize.top = m_tRect.top - 40;
	m_rtRecognize.right = m_tRect.right + 40;
	m_rtRecognize.bottom = m_tRect.bottom + 40;
	
	return OBJ_NOEVENT;
}

void CNpc::Late_Update()
{
	CheckRecognize();

	GetAnimator()->Update();
}

void CNpc::Render(HDC hDC)
{
	GetAnimator()->GetCurAnimation()->Render(hDC);


	//SelectGDI p(hDC, PEN_TYPE::GREEN);
	//SelectGDI b(hDC, BRUSH_TYPE::HOLLOW);




	Vec2 vNamePos = CCamera::CreateSingleTonInst()->GetRenderPos(Vec2(m_tNameUI.tInfo.fX, m_tNameUI.tInfo.fY));

	AlphaBlend(hDC
		, (int)vNamePos.x - m_tNameUI.tInfo.fCX / 2.f					// 이미지를 출력할 x
		, (int)vNamePos.y - m_tNameUI.tInfo.fCY / 2.f					// 이미지를 출력할 y
		, (int)m_tNameUI.tInfo.fCX										// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
		, (int)m_tNameUI.tInfo.fCY
		, m_tNameUI.pTex->GetDC()
		, 0																// 가져올 이미지의 시작위치
		, 0
		, m_tNameUI.pTex->Width()										// 잘라낼 크기니까 항상 800 이여야함
		, m_tNameUI.pTex->Height()
		, m_tNameUI.pTex->GetBf());


	RECT rt = { vNamePos.x - m_tNameUI.tInfo.fCX / 2.f + 15
		, vNamePos.y - m_tNameUI.tInfo.fCY / 2.f + 3
		, vNamePos.x + m_tNameUI.tInfo.fCX / 2.f
		, vNamePos.y + m_tNameUI.tInfo.fCY / 2.f
	};

	DrawTextW(hDC
		, m_tNameUI.strName.c_str()		// 변수가 들어가야함
		, -1
		, &rt
		, DT_LEFT | DT_WORDBREAK);



	//float renderX = m_rtRecognize.left + (m_rtRecognize.right - m_rtRecognize.left) / 2.f;
	//float renderY = m_rtRecognize.top + (m_rtRecognize.bottom - m_rtRecognize.top) / 2.f;
	//
	//
	//Vec2 vPos = CCamera::CreateSingleTonInst()->GetRenderPos(Vec2(renderX, renderY));
	//
	//Rectangle(hDC
	//	, (int)vPos.x - (m_rtRecognize.right - m_rtRecognize.left) / 2.f
	//	, (int)vPos.y - (m_rtRecognize.bottom - m_rtRecognize.top) / 2.f
	//	, (int)vPos.x + (m_rtRecognize.right - m_rtRecognize.left) / 2.f
	//	, (int)vPos.y + (m_rtRecognize.bottom - m_rtRecognize.top) / 2.f);

}

void CNpc::Release()
{
}

void CNpc::CheckRecognize()
{
	CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();

	INFO	playerInfo = pPlayer->Get_Info();

	float xPos = m_rtRecognize.left + (m_rtRecognize.right - m_rtRecognize.left) / 2.f;
	float yPos = m_rtRecognize.top + (m_rtRecognize.bottom - m_rtRecognize.top) / 2.f;

	if (abs(xPos - playerInfo.fX) < (m_rtRecognize.right - m_rtRecognize.left) / 2.f + playerInfo.fCX / 2.f
		&& abs(yPos - playerInfo.fY) < (m_rtRecognize.bottom - m_rtRecognize.top) / 2.f + playerInfo.fCY / 2.f)
	{
		// 인식범위 rect에 들어왔으면
		m_bRecognize = true;
	}
	else
		m_bRecognize = false;

		
}
