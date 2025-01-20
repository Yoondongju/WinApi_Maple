#include "stdafx.h"
#include "CScene.h"

#include "ObjMgr.h"
#include "CMonster.h"
#include "AbstractFactory.h"


#include "LineMgr.h"

#include "CTexture.h"

#include "CCamera.h"


CScene::CScene()
	: m_pMapTex(nullptr)
	, m_iMapMinX(0)
	, m_iMapMinY(0)
	, m_pNpc(nullptr)
	, m_pStoreNpc(nullptr)
	, m_pBossIntroTex(nullptr)
{
	m_vecPotal.reserve(3);
}

CScene::~CScene()
{
}

void CScene::Update()
{
	
}

void CScene::Late_Update()
{

}

void CScene::Render(HDC hDC)
{
	Vec2 vLookAt = CCamera::CreateSingleTonInst()->GetLookAt();
	
	m_iMapMinX = vLookAt.x - WINCX / 2.f;
	m_iMapMinY = vLookAt.y - WINCY / 2.f;    


	if (m_iMapMinX <= 0)
		m_iMapMinX = 0;
	if (m_iMapMinX + WINCX > m_pMapTex->Width() )
		m_iMapMinX = m_pMapTex->Width() - WINCX;
	
		

	if (m_iMapMinY < 0)
		m_iMapMinY = 0;
	if (m_iMapMinY + WINCY > m_pMapTex->Height())
	{
		m_iMapMinY = m_pMapTex->Height() - WINCY;		
	}
		

	AlphaBlend(hDC
		, 0					// �̹����� ����� x
		, 0					// �̹����� ����� y
		, WINCX				// ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
		, WINCY
		, m_pMapTex->GetDC()
		, m_iMapMinX					// ������ �̹����� ������ġ
		, m_iMapMinY
		, WINCX 					// �߶� ũ��ϱ� �׻� 800 �̿�����
		, WINCY 
		, m_pMapTex->GetBf());

}

void CScene::Exit()
{
	

}
