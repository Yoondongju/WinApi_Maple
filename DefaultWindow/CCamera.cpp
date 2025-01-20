#include "stdafx.h"
#include "CCamera.h"

#include "Obj.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "ObjMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CTexture.h"

#include "CResMgr.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_pVeilTex(nullptr)
	, m_CamEffect_End(false)
	, m_Ending(false)
{
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_vLookAt = (WINCX / 2.f, WINCY/2.f);

	m_pVeilTex = CResMgr::CreateSingleTonInst()->CreateTexture(L"CameraVeil", WINCX, WINCY);
}

CCamera::~CCamera()
{
}




void CCamera::Update()
{
	if (m_Ending)
	{
		ZoomIn();
		return;
	}



	if (m_pTargetObj)
	{
		CTexture* pCurSceneTex =  CSceneMgr::CreateSingleTonInst()->GetCurScene()->GetMapTex();

		// 200 1300
		if (m_pPlayer->GetPos().x - WINCX / 2.f > 0
			&& m_pPlayer->GetPos().x + WINCX / 2.f < pCurSceneTex->Width())
		{
			m_vLookAt.x = m_pTargetObj->Get_Info().fX;     
		}	

		if (m_pPlayer->GetPos().y - WINCY / 2.f > 0
			&& m_pPlayer->GetPos().y + WINCY / 2.f < pCurSceneTex->Height())
		{
			m_vLookAt.y = m_pTargetObj->Get_Info().fY;
		}	
	}

	
	

	//if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::UP) == KEY_STATE::HOLD)
	//{
	//	m_vLookAt.y -= 500.f * fDT;
	//}
	//if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
	//{
	//	m_vLookAt.y += 500.f * fDT;
	//}
	//if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
	//{
	//	m_vLookAt.x -= 500.f * fDT;
	//}
	//if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
	//{
	//	m_vLookAt.x += 500.f * fDT;
	//}

	



	// 화면 중앙좌표와 카메라 LookAt 차이계산
	CalDiff();

}

void CCamera::Render(HDC _dc)
{
	if (m_listCamEffect.empty())
	{
		return;
	}


	tCamEffect& effect = m_listCamEffect.front();
	effect.m_fCurTime += fDT;


	float fRatio = 0.f; // 이펙트 진행 비율
	fRatio = effect.m_fCurTime / effect.m_fDuration;

	int iAlpha = 0;

	if (fRatio < 0.f)	 // 비율 값은 항상 0~1 사이에 나와야함
		fRatio = 0.f;	 // 비율 값은 항상 0~1 사이에 나와야함
	if (fRatio > 1.f)	 // 비율 값은 항상 0~1 사이에 나와야함
		fRatio = 1.f;	 // 비율 값은 항상 0~1 사이에 나와야함

	// 255 불투명  0 투명
	if (CAM_EFFECT::FADE_OUT == effect.eEfeect)
	{
		iAlpha = (int)(255.f * fRatio);
	}
	else if (CAM_EFFECT::FADE_IN == effect.eEfeect)
	{
		iAlpha = (int)(255.f * (1.f - fRatio));
	}


	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;



	AlphaBlend(_dc
		, 0
		, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, m_pVeilTex->GetDC()
		, 0, 0, (int)m_pVeilTex->Width(), (int)m_pVeilTex->Height()
		, bf);


	// 진행 시간이 이펙트 최대 지정 시간을 넘어선 경우
	if (effect.m_fDuration <= effect.m_fCurTime)
	{
		// 효과종료
		m_listCamEffect.pop_front();
		m_CamEffect_End = true;
	}
}

void CCamera::ZoomIn()
{
	m_vLookAt.x += 0.5f;
	m_vLookAt.y = WINCY;
}

void CCamera::CalDiff()
{	
	m_vDiff = m_vLookAt - Vec2(WINCX / 2.f,	WINCY/2.f);
}
