#pragma once
#include "CDamageEffect.h"

class CHitDamageEffect : public CDamageEffect
{
public:
	CHitDamageEffect();
	~CHitDamageEffect();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	void	SetDamage(int _i) { m_iDamage = _i; }


};

