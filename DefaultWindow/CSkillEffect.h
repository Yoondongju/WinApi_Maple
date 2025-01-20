#pragma once
#include "Obj.h"

class CPlayerSkill;
class CPlayer;

class CSkillEffect : public CObj
{
public:
	CSkillEffect();
	~CSkillEffect();

public:
	virtual void Initialize(){}
	virtual void Initialize(CPlayerSkill* _pOwner);

	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	CPlayerSkill*	m_pOwnerSkill;
	CPlayer*		m_pPlayer;

	Vec2			m_vOffset;
};

