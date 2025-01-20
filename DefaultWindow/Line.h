#pragma once

#include "Define.h"

class CLine
{
public:
	CLine();
	CLine(LINEPOINT& tLPoint, LINEPOINT& tRPoint);
	CLine(LINEPOINT& tLPoint, LINEPOINT& tRPoint , LINETYPE _e);

	CLine(LINE& tLine);
	CLine(LINE& tLine , LINETYPE _e);

	~CLine();

public:
	const LINE&		Get_Info() const { return m_tInfo; }

	LINETYPE		Get_LineType() { return m_eLineType; }

	void			Set_LineType(LINETYPE _e) { m_eLineType = _e; }

public:
	void		Render(HDC hDC);

private:
	LINE		m_tInfo;
	LINETYPE	m_eLineType;
};

