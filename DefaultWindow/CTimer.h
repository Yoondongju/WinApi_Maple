#pragma once
#include "CPlayerUI.h"


enum class NUM
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
	
	NUM_END
};

class CTexture;

#define	NUM_WIDTH 25
#define NUM_HEIGHT 38

class CTimer :
    public CPlayerUI
{
public:
	CTimer();
	~CTimer();


	virtual void Initialize();
	virtual void Initialize(Vec2 _v);

	virtual int  Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;


private:
	vector<pair<NUM, CTexture* >>	m_vecNumTex;

	int							m_iMinute;
	int							m_iSecond;
};

