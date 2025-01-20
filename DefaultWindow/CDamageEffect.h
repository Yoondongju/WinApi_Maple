#pragma once
#include "Obj.h"

class CTexture;


enum class DAMEGE_NUM
{
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,

	MISS,
};

class CDamageEffect : public CObj
{
public:
	CDamageEffect();
	~CDamageEffect();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;


public:
	void SetCreatePos(Vec2 _v) { m_vCreatePos = _v; }


public:
	DamageEffectType GetCurDamageEffect() { return m_eEffectType; }



	


protected:
	vector<pair<DAMEGE_NUM, CTexture*>>		m_vecDamageTex;

	int							m_iDamage;

	Vec2						m_vCreatePos;
	Vec2						m_vOffset;

	float						m_fDeleteDelay;

	BYTE						m_byte;

	DamageEffectType			m_eEffectType;

	float						m_fParticleDelay;


	unsigned int				m_iCount;
};

