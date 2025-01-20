#pragma once
#include "Obj.h"

class CTexture;



class CMouse : public CObj
{
public:
	CMouse();
	virtual ~CMouse();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	CTexture*	m_pTexNon;
	CTexture*	m_pTexClick;
};

