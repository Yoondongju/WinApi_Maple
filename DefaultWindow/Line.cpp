#include "stdafx.h"
#include "Line.h"

#include "CCamera.h"


CLine::CLine()
{
	ZeroMemory(&m_tInfo, sizeof(LINE));
}

CLine::CLine(LINEPOINT& tLPoint, LINEPOINT& tRPoint)
	: m_tInfo(tLPoint, tRPoint)
	, m_eLineType(LINETYPE::NONE)
{
}

CLine::CLine(LINEPOINT & tLPoint, LINEPOINT & tRPoint, LINETYPE _e) 
	: m_tInfo(tLPoint, tRPoint)
	, m_eLineType(_e)
{

}

CLine::CLine(LINE & tLine) : m_tInfo(tLine)
{
}

CLine::CLine(LINE& tLine, LINETYPE _e)
	: m_tInfo(tLine)
	, m_eLineType(_e)
{
}

CLine::~CLine()
{
}


void CLine::Render(HDC hDC)
{
	
	Vec2 vLPointPos = Vec2(m_tInfo.tLPoint.fX, m_tInfo.tLPoint.fY);
	Vec2 vLPointRenderPos = CCamera::CreateSingleTonInst()->GetRenderPos(vLPointPos);

	Vec2 vRPointPos = Vec2(m_tInfo.tRPoint.fX, m_tInfo.tRPoint.fY);
	Vec2 vRPointRenderPos = CCamera::CreateSingleTonInst()->GetRenderPos(vRPointPos);


	MoveToEx(hDC, (int)vLPointRenderPos.x, (int)vLPointRenderPos.y, nullptr);
	LineTo(hDC, (int)(vRPointRenderPos.x), (int)(vRPointRenderPos.y));
}
