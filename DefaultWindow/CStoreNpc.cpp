#include "stdafx.h"
#include "CStoreNpc.h"


#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "ObjMgr.h"
#include "SelectGDI.h"
#include "CTexture.h"


CStoreNpc::CStoreNpc()
{
}

CStoreNpc::~CStoreNpc()
{
}

void CStoreNpc::Initialize()
{
	m_tInfo = { 2100.f, 970.f , 90.f , 90.f };


	m_eObjType = OBJID::OBJ_NPC;
	m_eNpcType = NPC_TYPE::STORE;


	wstring	str = L"  ���� ����";
	INFO tInfo = { m_tInfo.fX, m_tInfo.fY + 55.f, 90.f,20.f };
	CTexture* pNameTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"NameTex", L"../API/UI/NameBackground.png");

	m_tNameUI = NameUI(str, tInfo, pNameTex);


	CreateAnimator();					// �׻� �ִϸ����� ��������� ObjType ���������!!!!!!!!!!1

	CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"store_npc_stand", L"../API/UI/storeNpc.png");
	GetAnimator()->CreateAnimation(L"store_npc_stand", pTex, Vec2(0.f, 0.f), Vec2(84.f, 113.f), Vec2(84.f, 0.f), 0.3f, 4);

	GetAnimator()->Play(L"store_npc_stand", true);
}

int CStoreNpc::Update()
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

void CStoreNpc::Late_Update()
{
	CheckRecognize();

	GetAnimator()->Update();
}

void CStoreNpc::Render(HDC hDC)
{
	GetAnimator()->GetCurAnimation()->Render(hDC);


	//SelectGDI p(hDC, PEN_TYPE::GREEN);
	//SelectGDI b(hDC, BRUSH_TYPE::HOLLOW);



	
	Vec2 vNamePos = CCamera::CreateSingleTonInst()->GetRenderPos(Vec2(m_tNameUI.tInfo.fX, m_tNameUI.tInfo.fY));



	AlphaBlend(hDC
		, (int)vNamePos.x - m_tNameUI.tInfo.fCX / 2.f					// �̹����� ����� x
		, (int)vNamePos.y - m_tNameUI.tInfo.fCY / 2.f				// �̹����� ����� y
		, (int)m_tNameUI.tInfo.fCX			// ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
		, (int)m_tNameUI.tInfo.fCY
		, m_tNameUI.pTex->GetDC()
		, 0											// ������ �̹����� ������ġ
		, 0
		, m_tNameUI.pTex->Width()					// �߶� ũ��ϱ� �׻� 800 �̿�����
		, m_tNameUI.pTex->Height()
		, m_tNameUI.pTex->GetBf());


	RECT rt = { vNamePos.x - m_tNameUI.tInfo.fCX / 2.f + 15
		, vNamePos.y - m_tNameUI.tInfo.fCY / 2.f + 3
		, vNamePos.x + m_tNameUI.tInfo.fCX / 2.f
		, vNamePos.y + m_tNameUI.tInfo.fCY / 2.f
	};

	DrawTextW(hDC
		, m_tNameUI.strName.c_str()		// ������ ������
		, -1
		, &rt
		, DT_LEFT | DT_WORDBREAK);




	//float renderX = m_rtRecognize.left + (m_rtRecognize.right - m_rtRecognize.left) / 2.f;
	//float renderY = m_rtRecognize.top + (m_rtRecognize.bottom - m_rtRecognize.top) / 2.f;
	//
	//
	//Vec2 vPos = CCamera::CreateSingleTonInst()->GetRenderPos(Vec2(renderX, renderY));
	//
	//
	//
	//Rectangle(hDC
	//	, (int)vPos.x - (m_rtRecognize.right - m_rtRecognize.left) / 2.f
	//	, (int)vPos.y - (m_rtRecognize.bottom - m_rtRecognize.top) / 2.f
	//	, (int)vPos.x + (m_rtRecognize.right - m_rtRecognize.left) / 2.f
	//	, (int)vPos.y + (m_rtRecognize.bottom - m_rtRecognize.top) / 2.f);

}

void CStoreNpc::Release()
{
}


