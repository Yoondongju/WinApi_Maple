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
	void		Update();		// 실시간으로(매 프레임마다) 변경되는 값을 만드는 함수
	void		Late_Update();
	void		Render();		// 실시간으로(매 프레임마다) 출력하는 함수
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

	// 자주 사용하는 펜 GDI Object
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_TYPE_END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::PEN_TYPE_END];


	//HDC			m_hBackDC;			// 더블버퍼링용   텍스쳐에서 dc랑 비트맵잇음
	CTexture*	m_pMemTex;			// 백버퍼 텍스쳐
};





// 디자인 패턴 : 코드의 구조들을 일정한 형태로 만들어 재사용하기 편리하게 만든 패턴
// https://refactoring.guru/ko/design-patterns

// 추상 팩토리 패턴 : 관련 객체들의 구상 클래스들을 지정하지 않고도 관련 객체들의 모음을 생성할 수 있도록 하는 생성패턴입니다.
// 객체 생성 시 동반되는 공통적인 작업을 추상화 시킨 것

// 반복자 패턴 : 내부 표현 방식은 공개하지 않고 순차적인 접근 방법을 제공하는 패턴

// 메디에이터(중재자) 패턴 : 상호작용하는 객체들이 서로 복잡한 관계를 맺고 있을 경우 별도의 형식으로 정의하여 중재하는 객체를 두는 패턴

// 싱글톤 패턴 : 단 하나의 인스턴스만 생성하여 사용하는 패턴