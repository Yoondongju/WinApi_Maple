#include "stdafx.h"
#include "CTimeMgr.h"

CTimeMgr::CTimeMgr()
	: m_llPrevCount{}
	, m_llCurCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount()
	, m_iFPS()
{

}


CTimeMgr::~CTimeMgr()
{


}

void CTimeMgr::init()
{
	// �ʱ�ȭ �Ҷ� ���� ī��Ʈ (update ���������� ���� ī��Ʈ��)
	QueryPerformanceCounter(&m_llPrevCount);

	// �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_llFrequency);


}

void CTimeMgr::update()
{
	// 1 FPS ? ( update ���������� ���� ī��Ʈ )
	QueryPerformanceCounter(&m_llCurCount);

	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;


	// ���� ī��Ʈ�� ����ī��Ʈ�� ���� (������ ������ ����)
	m_llPrevCount = m_llCurCount;




	if (m_dDT > (1. / 60.))
	{
		m_dDT = (1. / 60.);
	}



}

void CTimeMgr::render()
{

	// ++m_iCallCount;
	// m_dAcc += m_dDT;
	// 
	// 
	// if (m_dAcc >= 1.)
	// {
	// 	m_iFPS = m_iCallCount;
	// 	m_dAcc = 0.;
	// 	m_iCallCount = 0;
	// 
	// 	wchar_t szBufffer[255] = {};
	// 
	// 	swprintf_s(szBufffer, L"FPS: %d , DT: %f", m_iFPS, m_dDT);
	// 	SetWindowText(g_hWnd, szBufffer);
	// }

}