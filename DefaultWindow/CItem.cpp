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
	//	, m_tRect.left		// ( 고정위치 )						// 이미지를 출력할 x
	//	, m_tRect.top		// ( 고정위치 )						// 이미지를 출력할 y
	//	, m_tInfo.fCX							// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
	//	, m_tInfo.fCY
	//	, m_pTex->GetDC()
	//	, 0								// 가져올 이미지의 시작위치
	//	, 0
	//	, m_pTex->Width() 			// 잘라낼 크기니까 항상 800 이여야함
	//	, m_pTex->Height()
	//	, this->GetBf());

}

void CItem::Release()
{
}
