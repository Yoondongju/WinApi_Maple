#pragma once

#include "Define.h"

class CObj;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,  // 점점 밝아지는거
	FADE_OUT, // 점점 어두워지는거
	NONE,
};

struct tCamEffect
{
	CAM_EFFECT  eEfeect;		// 카메라 이펙트효과
	float		m_fDuration;	// 카메라 효과 최대 진행 시간
	float		m_fCurTime;		// 카메로 효과 현재 진행된 시간

};


class CCamera
{
	SINGLE(CCamera)

public:
	Vec2 GetLookAt() { return m_vLookAt; }

	void SetLookAt(Vec2 _v) { m_vLookAt = _v; }
	

	void SetTarget(CObj* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 GetRenderPos(Vec2 _vObjPos){ return Vec2(_vObjPos - m_vDiff); }
	
	bool IsEffectEnd() { return m_CamEffect_End; }


	void Update();
	void Render(HDC _dc);




	void ZoomIn();




	void SetEnd(bool _b) { m_Ending = _b; }


private:
	void CalDiff();



public:
	CTexture* GetVeilTex() { return m_pVeilTex; }


	void FadeIn(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEfeect = CAM_EFFECT::FADE_IN;
		ef.m_fDuration = _fDuration;
		ef.m_fCurTime = 0.f;

		m_listCamEffect.push_back(ef);
		m_CamEffect_End = false;

		if (0.f == _fDuration)
			assert(nullptr);
	}


	void FadeOut(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEfeect = CAM_EFFECT::FADE_OUT;
		ef.m_fDuration = _fDuration;
		ef.m_fCurTime = 0.f;

		m_listCamEffect.push_back(ef);
		m_CamEffect_End = false;

		if (0.f == _fDuration)
			assert(nullptr);
	}



	


private:
	Vec2	m_vLookAt;		// 카메라가 보는 위치
	CObj*	m_pTargetObj;	// 카메라 타겟 오브젝트

	Vec2	m_vDiff;		// 해상도 중심위치와 카메라 LookAt 차이값 

	CObj*	m_pPlayer;



	CTexture*			 m_pVeilTex;						 // 카메라 가림막 (장막 텍스쳐)


	list<tCamEffect>	m_listCamEffect;		 // 카메라 이펙트
	bool				m_CamEffect_End;		 // 이펙트 다 표현했는지?

	bool				m_Ending;

};

