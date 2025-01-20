#pragma once

#include "Define.h"
#include "CCamera.h"

class CAnimator;
class CTexture;

struct  NameUI
{
	wstring		strName;
	INFO		tInfo;
	CTexture*	pTex;
	HFONT		hFont;
	HFONT		hOldFont;

	


	NameUI()
	{

	}

	NameUI(wstring _str, INFO _Info, CTexture* _p)
	{
		strName = _str;
		tInfo = _Info;
		pTex = _p;
	}

};


class CObj
{
public:
	CObj();
	virtual ~CObj();

public:

public:
	virtual		void		Initialize()	PURE;
	virtual		int			Update()		PURE;
	virtual		void		Late_Update()	PURE;
	virtual		void		Render(HDC hDC)	PURE;
	virtual		void		Release()		PURE;


public:
	void CreateAnimator();
	CAnimator* GetAnimator() { return m_pAnimator; }


public:
	void SetObjType(OBJID _e) { m_eObjType = _e; }
	OBJID GetObjType() { return m_eObjType; }

public:

	void SetBf(BLENDFUNCTION _bf) { m_bf = _bf; }
	BLENDFUNCTION GetBf() { return m_bf; }


public:
	void Set_CXY(float _fCX, float _fCY)
	{
		m_tInfo.fCX = _fCX;
		m_tInfo.fCY = _fCY;
	}
	void			Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	
	Vec2	GetPos()
	{
		return Vec2(m_tInfo.fX, m_tInfo.fY);
	}

	Vec2	GetSize()
	{
		return Vec2(m_tInfo.fCX, m_tInfo.fCY);
	}


	RECT			Get_Rect() { return m_tRect; }
	INFO			Get_Info() { return m_tInfo; }
	bool			Get_Dead() { return m_bDead; }
	void			Set_Dead() { m_bDead = true; }


public:
	float	GetAngle() { return m_fAngle; }
	
	bool	IsAffectedCamera() { return m_bAffectedCamera; }


protected:
	void		Update_Rect();

protected:
	INFO		m_tInfo;

	RECT		m_tRect;

	float		m_fSpeed;
	bool		m_bDead;

	float		m_fAngle;

	bool		m_bAffectedCamera;


	CAnimator*	m_pAnimator;

	OBJID		m_eObjType;

	BLENDFUNCTION	m_bf;


	NameUI		m_tNameUI;


public:
	bool		m_bNoRender;
};

