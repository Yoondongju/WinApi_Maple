#pragma once
#include "CPlayerUI.h"

class CMonster;
class CTexture;

class CBossUI :
    public CPlayerUI
{
public:
	CBossUI();
	~CBossUI();


	virtual void Initialize(){}
	virtual void Initialize(int _pageCount);

	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;


private:
	CMonster*	m_pBoss;
	CTexture*	m_pBossHp;

};

