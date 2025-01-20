#pragma once

#include "Define.h"

class CObj;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,  // ���� ������°�
	FADE_OUT, // ���� ��ο����°�
	NONE,
};

struct tCamEffect
{
	CAM_EFFECT  eEfeect;		// ī�޶� ����Ʈȿ��
	float		m_fDuration;	// ī�޶� ȿ�� �ִ� ���� �ð�
	float		m_fCurTime;		// ī�޷� ȿ�� ���� ����� �ð�

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
	Vec2	m_vLookAt;		// ī�޶� ���� ��ġ
	CObj*	m_pTargetObj;	// ī�޶� Ÿ�� ������Ʈ

	Vec2	m_vDiff;		// �ػ� �߽���ġ�� ī�޶� LookAt ���̰� 

	CObj*	m_pPlayer;



	CTexture*			 m_pVeilTex;						 // ī�޶� ������ (�帷 �ؽ���)


	list<tCamEffect>	m_listCamEffect;		 // ī�޶� ����Ʈ
	bool				m_CamEffect_End;		 // ����Ʈ �� ǥ���ߴ���?

	bool				m_Ending;

};

