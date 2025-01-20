#pragma once
#include "CPlayerUI.h"
class CMonster;
class CTexture;


class CKariainUI :
    public CPlayerUI
{
public:
	CKariainUI();
	~CKariainUI();


	virtual void Initialize() {}
	virtual void Initialize(CMonster* _pOwner);

	virtual int  Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;


private:
	CMonster* m_pBoss;
	CTexture* m_pBossHp;
};

