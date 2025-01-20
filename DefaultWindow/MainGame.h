#pragma once

#include "Define.h"

#include "Player.h"
#include "Mouse.h"


class CMainGame
{
	SINGLE(CMainGame)

public:
	HDC	GetMainGameDC() {return m_hDC;}
	CTexture* GetBackTexture() { return m_pMemTex; }

public:
	void		Initialize();
	void		Update();		// �ǽð�����(�� �����Ӹ���) ����Ǵ� ���� ����� �Լ�
	void		Late_Update();
	void		Render();		// �ǽð�����(�� �����Ӹ���) ����ϴ� �Լ�
	void		Release();


public:
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }


	HFONT GetUsingFont() { return m_hFont; }
	HFONT GetOldFont() { return m_hOldFont; }

	void SetUsingFont(HFONT _h) { m_hFont = _h; }
	void SetOldFont(HFONT _h) { m_hOldFont = _h; }

private:	
	HDC			m_hDC;

	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[256];


	HFONT			m_hOldFont;
	HFONT			m_hFont;

	// ���� ����ϴ� �� GDI Object
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_TYPE_END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::PEN_TYPE_END];


	//HDC			m_hBackDC;			// ������۸���   �ؽ��Ŀ��� dc�� ��Ʈ������
	CTexture*	m_pMemTex;			// ����� �ؽ���
};





// ������ ���� : �ڵ��� �������� ������ ���·� ����� �����ϱ� ���ϰ� ���� ����
// https://refactoring.guru/ko/design-patterns

// �߻� ���丮 ���� : ���� ��ü���� ���� Ŭ�������� �������� �ʰ� ���� ��ü���� ������ ������ �� �ֵ��� �ϴ� ���������Դϴ�.
// ��ü ���� �� ���ݵǴ� �������� �۾��� �߻�ȭ ��Ų ��

// �ݺ��� ���� : ���� ǥ�� ����� �������� �ʰ� �������� ���� ����� �����ϴ� ����

// �޵�����(������) ���� : ��ȣ�ۿ��ϴ� ��ü���� ���� ������ ���踦 �ΰ� ���� ��� ������ �������� �����Ͽ� �����ϴ� ��ü�� �δ� ����

// �̱��� ���� : �� �ϳ��� �ν��Ͻ��� �����Ͽ� ����ϴ� ����