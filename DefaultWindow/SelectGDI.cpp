#include "stdafx.h"
#include "SelectGDI.h"

#include "MainGame.h"

SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _ePenType)
	:m_hDC(_dc)
	,m_hDefaultBrush(nullptr)
	,m_hDefaultPen(nullptr)
{
	HPEN hGreenPen = CMainGame::CreateSingleTonInst()->GetPen(_ePenType);
	m_hDefaultPen = (HPEN)SelectObject(_dc, hGreenPen);

	 
}


SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _eBrushType)
	: m_hDC(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
{
	
	HBRUSH BrushType = CMainGame::CreateSingleTonInst()->GetBrush(_eBrushType);
	m_hDefaultBrush = (HBRUSH)SelectObject(_dc, BrushType);
	
}


SelectGDI::~SelectGDI()
{
	SelectObject(m_hDC, m_hDefaultPen);
	SelectObject(m_hDC, m_hDefaultBrush);
	
}
