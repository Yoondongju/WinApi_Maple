#include "stdafx.h"
#include "CPet.h"

#include "ObjMgr.h"
#include "CResMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "SelectGDI.h"

#include "Player.h"

#include "CTimeMgr.h"
#include "CMoney.h"

#include "CSound.h"

CPet::CPet()
    : m_pOwner(nullptr)
    , m_vOffset(60.f,0.f)
{
    CreateAnimator();
}

CPet::~CPet()
{
}

void CPet::Initialize()
{
    m_pOwner = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();

    m_tInfo = { 0.f,0.f,50.f,50.f };
    m_eObjType = OBJID::OBJ_PET;

	m_vRecognizeSize = Vec2(500.f, 500.f);

    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"pet_stand_left", L"../API/UI/Item/Pet_Stand_left.png");
    GetAnimator()->CreateAnimation(L"pet_stand_left", pTex, Vec2(0.f, 0.f), Vec2(37.f, 47.f), Vec2(37.f, 0.f), 0.5, 6);

    CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"pet_stand_right", L"../API/UI/Item/Pet_Stand_right.png");
    GetAnimator()->CreateAnimation(L"pet_stand_right", pTex1, Vec2(0.f, 0.f), Vec2(37.f, 47.f), Vec2(37.f, 0.f), 0.5, 6);

    CTexture* pTex2 = CResMgr::CreateSingleTonInst()->LoadTexture(L"pet_jump_left", L"../API/UI/Item/Pet_Jump_left.png");
    GetAnimator()->CreateAnimation(L"pet_jump_left", pTex2, Vec2(0.f, 0.f), Vec2(36.f, 44.f), Vec2(0.f, 0.f), 0.1, 1);

    CTexture* pTex3 = CResMgr::CreateSingleTonInst()->LoadTexture(L"pet_jump_right", L"../API/UI/Item/Pet_Jump_right.png");
    GetAnimator()->CreateAnimation(L"pet_jump_right", pTex3, Vec2(0.f, 0.f), Vec2(36.f, 44.f), Vec2(0.f, 0.f), 0.1, 1);

    CTexture* pTex4 = CResMgr::CreateSingleTonInst()->LoadTexture(L"pet_rope", L"../API/UI/Item/Pet_Rope.png");
    GetAnimator()->CreateAnimation(L"pet_rope", pTex4, Vec2(0.f, 0.f), Vec2(35.f, 44.f), Vec2(0.f, 0.f), 0.1, 1);



    GetAnimator()->Play(L"pet_stand_left", true);


	CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"pet");
	pNewSound->Play(false);
	pNewSound->SetPosition(1.f); // 백분률 , 소리위치
	pNewSound->SetVolume(50.f); // 소리 볼륨 크기
}

int CPet::Update()
{
    if (m_bDead)
        return OBJ_DEAD;




	if (PLAYER_DIR::RIGHT == m_pOwner->GetPlayerDir())
	{
		m_vOffset.x = -60;
		GetAnimator()->Play(L"pet_stand_right", true);
	}
	else if (PLAYER_DIR::LEFT == m_pOwner->GetPlayerDir())
	{ 
		m_vOffset.x = 60;
		GetAnimator()->Play(L"pet_stand_left", true);
	}



	Vec2 vPos = m_pOwner->GetPos();


	if (m_tInfo.fX < vPos.x + m_vOffset.x)
	{
		m_tInfo.fX += 200 * fDT;
		GetAnimator()->Play(L"pet_stand_right", true);
	}
	else if (m_tInfo.fX > vPos.x + m_vOffset.x)
	{
		m_tInfo.fX -= 200 * fDT;
		GetAnimator()->Play(L"pet_stand_left", true);
	}
	if (abs(m_tInfo.fX - (vPos.x + m_vOffset.x)) < 10)
		m_tInfo.fX = vPos.x + m_vOffset.x;
	
	m_tInfo.fY = vPos.y + m_vOffset.y;






    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CPet::Late_Update()
{
	PLAYER_DIR ePlayerDir = m_pOwner->GetPlayerDir();
	PLAYER_STATE ePlayerState = m_pOwner->GetPlayerState();

	if (PLAYER_STATE::ROPE_MOVE == ePlayerState
		|| PLAYER_STATE::ROPE_NOMOVE == ePlayerState)
	{
		m_tInfo.fX = m_pOwner->GetPos().x;
		m_tInfo.fY = m_pOwner->GetPos().y;
	}

	if (ePlayerDir == PLAYER_DIR::RIGHT)	// 오른쪽방향
	{
		switch (ePlayerState)
		{
		//case PLAYER_STATE::IDLE:
		//	GetAnimator()->Play(L"pet_stand_right", true);
		//	break;
		//case PLAYER_STATE::WALK:
		//	GetAnimator()->Play(L"pet_stand_right", true);
		//	break;
		case PLAYER_STATE::JUMP:
			GetAnimator()->Play(L"pet_jump_right", true);
			break;
		case PLAYER_STATE::ROPE_NOMOVE:
			GetAnimator()->Play(L"pet_rope", true);
			break;
		case PLAYER_STATE::ROPE_MOVE:
			GetAnimator()->Play(L"pet_rope", true);
			break;
		case PLAYER_STATE::STATE_END:
			break;
		default:
			break;
		}
	}
	else if (ePlayerDir == PLAYER_DIR::LEFT)  // 왼쪽
	{
		switch (ePlayerState)
		{
		//case PLAYER_STATE::IDLE:
		//	GetAnimator()->Play(L"pet_stand_left", true);
		//	break;
		//case PLAYER_STATE::WALK:
		//	GetAnimator()->Play(L"pet_stand_left", true);
		//	break;
		case PLAYER_STATE::JUMP:
			GetAnimator()->Play(L"pet_jump_left", true);
			break;
		case PLAYER_STATE::ROPE_NOMOVE:
			GetAnimator()->Play(L"pet_rope", true);
			break;
		case PLAYER_STATE::ROPE_MOVE:
			GetAnimator()->Play(L"pet_rope", true);
			break;
		case PLAYER_STATE::STATE_END:
			break;
		default:
			break;
		}
	}


	
	
	
	FindMeso();


    GetAnimator()->Update();
}

void CPet::Render(HDC hDC)
{
    GetAnimator()->GetCurAnimation()->Render(hDC);


    //SelectGDI p(hDC, PEN_TYPE::GREEN);
    //SelectGDI b(hDC, BRUSH_TYPE::HOLLOW);


    //Vec2 vPos = CCamera::CreateSingleTonInst()->GetRenderPos(Vec2(m_tInfo.fX, m_tInfo.fY));
	//
    //Rectangle(hDC
    //    , (int)(vPos.x - m_tInfo.fCX / 2.f)
    //    , (int)(vPos.y - m_tInfo.fCY / 2.f)
    //    , (int)(vPos.x + m_tInfo.fCX / 2.f)
    //    , (int)(vPos.y + m_tInfo.fCY / 2.f));
	//
	//
	//
	//
	//
	//SelectGDI p1(hDC, PEN_TYPE::RED);
	//SelectGDI b1(hDC, BRUSH_TYPE::HOLLOW);
	//
	//
	//Vec2 vPos1 = CCamera::CreateSingleTonInst()->GetRenderPos(Vec2(m_tInfo.fX, m_tInfo.fY));
	//
	//Rectangle(hDC
	//	, (int)(vPos1.x - m_vRecognizeSize.x / 2.f)
	//	, (int)(vPos1.y - m_vRecognizeSize.y / 2.f)
	//	, (int)(vPos1.x + m_vRecognizeSize.x / 2.f)
	//	, (int)(vPos1.y + m_vRecognizeSize.y / 2.f));


}


void CPet::FindMeso()
{
	for (auto& iter : CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_MESO))
	{
		INFO tInfo = iter->Get_Info();

		float	fWidth = abs(m_tInfo.fX - tInfo.fX);
		float	fHeight = abs(m_tInfo.fY - tInfo.fY);

		float	fRadiusX = (m_vRecognizeSize.x + tInfo.fCX) * 0.5f;
		float	fRadiusY = (m_vRecognizeSize.y + tInfo.fCY) * 0.5f;

		if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))	// 충돌
		{
			((CMoney*)iter)->SetMagnet(true, this);
		}
	}

}




void CPet::Release()
{
}

