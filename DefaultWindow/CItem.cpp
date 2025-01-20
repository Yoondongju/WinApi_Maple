#include "stdafx.h"
#include "CItem.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "ObjMgr.h"



CItem::CItem()
    : m_pTex(nullptr)
{
}

CItem::~CItem()
{
}

void CItem::Initialize(ITEM_TYPE _e, int _iPrice, CTexture* pTex)
{
    m_tInfo = { 0.f,0.f,34.f,34.f };

    m_eObjType = OBJID::OBJ_ITEM;
    m_eItemType = _e;
    m_iPrice = _iPrice;

    m_pTex = pTex;
}

int CItem::Update()
{
	if (m_bDead)
		return OBJ_DEAD;



	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CItem::Late_Update()
{
}

void CItem::Render(HDC hDC)
{
	//AlphaBlend(hDC
	//	, m_tRect.left		// ( ������ġ )						// �̹����� ����� x
	//	, m_tRect.top		// ( ������ġ )						// �̹����� ����� y
	//	, m_tInfo.fCX							// ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
	//	, m_tInfo.fCY
	//	, m_pTex->GetDC()
	//	, 0								// ������ �̹����� ������ġ
	//	, 0
	//	, m_pTex->Width() 			// �߶� ũ��ϱ� �׻� 800 �̿�����
	//	, m_pTex->Height()
	//	, this->GetBf());

}

void CItem::Release()
{
}
