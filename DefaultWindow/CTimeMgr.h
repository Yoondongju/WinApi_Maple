#pragma once

#include "Define.h"

class CTimeMgr
{
	SINGLE(CTimeMgr)

private:
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llFrequency;

	double			m_dDT; // 1������ ���� �ð���
	double			m_dAcc; // 1�� üũ�� ���� ���� �ð���
	UINT			m_iCallCount; // �Լ� ȣ�� Ƚ��
	UINT			m_iFPS;		// �ʴ� ȣ�� Ƚ��


public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }

};

