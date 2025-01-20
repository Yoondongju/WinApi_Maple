#pragma once
#include "CPlayerUI.h"


class CPlayer;


class CStatUI :
    public CPlayerUI
{
public:
	CStatUI();
	~CStatUI();


	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void MouseLBtnDown();
	virtual void MouseLBtnUp();
	virtual void MouseClick();

	virtual void MouseOn();
	virtual void MouseOut();



private:
	Vec2			m_vDragStart;
	
	


	RECT			m_ptText;		// Stat text 나올 rect 영역
	
	wstring			m_strStat[8];		// Stat 정보 문자열


	wstring			m_strAbility;
	wstring			m_strSDIL[4];

	

};

