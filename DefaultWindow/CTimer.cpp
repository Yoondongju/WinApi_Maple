#include "stdafx.h"
#include "CTimer.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CMonster.h"
#include "ObjMgr.h"


#include "CTimeMgr.h"


CTimer::CTimer()
	: m_iMinute(30)
	, m_iSecond(0)
{

	m_bAffectedCamera = false;
}

CTimer::~CTimer()
{
}

void CTimer::Initialize()
{
	m_tInfo = { WINCX / 2.f, 160.f, 220, 100 };
	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::UITYPE_NONE;


	// 544  224  6

	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Timer", L"../API/Damage/testTimer.png");


	
	m_vecNumTex.push_back(make_pair(NUM::ZERO, CResMgr::CreateSingleTonInst()->LoadTexture(L"ZERO", L"../API/Damage/Prision.Number.0.png")));
	m_vecNumTex.push_back(make_pair(NUM::ONE, CResMgr::CreateSingleTonInst()->LoadTexture(L"ONE", L"../API/Damage/Prision.Number.1.png")));
	m_vecNumTex.push_back(make_pair(NUM::TWO, CResMgr::CreateSingleTonInst()->LoadTexture(L"TWO", L"../API/Damage/Prision.Number.2.png")));
	m_vecNumTex.push_back(make_pair(NUM::THREE, CResMgr::CreateSingleTonInst()->LoadTexture(L"THREE", L"../API/Damage/Prision.Number.3.png")));
	m_vecNumTex.push_back(make_pair(NUM::FOUR, CResMgr::CreateSingleTonInst()->LoadTexture(L"FOUR", L"../API/Damage/Prision.Number.4.png")));
	m_vecNumTex.push_back(make_pair(NUM::FIVE, CResMgr::CreateSingleTonInst()->LoadTexture(L"FIVE", L"../API/Damage/Prision.Number.5.png")));
	m_vecNumTex.push_back(make_pair(NUM::SIX, CResMgr::CreateSingleTonInst()->LoadTexture(L"SIX", L"../API/Damage/Prision.Number.6.png")));
	m_vecNumTex.push_back(make_pair(NUM::SEVEN, CResMgr::CreateSingleTonInst()->LoadTexture(L"SEVEN", L"../API/Damage/Prision.Number.7.png")));
	m_vecNumTex.push_back(make_pair(NUM::EIGHT, CResMgr::CreateSingleTonInst()->LoadTexture(L"EIGHT", L"../API/Damage/Prision.Number.8.png")));
	m_vecNumTex.push_back(make_pair(NUM::NINE, CResMgr::CreateSingleTonInst()->LoadTexture(L"NINE", L"../API/Damage/Prision.Number.9.png")));
}


void CTimer::Initialize(Vec2 _v)
{
	m_tInfo = { _v.x, _v.y, 220, 100 };
	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::UITYPE_NONE;


	// 544  224  6

	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Timer", L"../API/Damage/testTimer.png");



	m_vecNumTex.push_back(make_pair(NUM::ZERO, CResMgr::CreateSingleTonInst()->LoadTexture(L"ZERO", L"../API/Damage/Prision.Number.0.png")));
	m_vecNumTex.push_back(make_pair(NUM::ONE, CResMgr::CreateSingleTonInst()->LoadTexture(L"ONE", L"../API/Damage/Prision.Number.1.png")));
	m_vecNumTex.push_back(make_pair(NUM::TWO, CResMgr::CreateSingleTonInst()->LoadTexture(L"TWO", L"../API/Damage/Prision.Number.2.png")));
	m_vecNumTex.push_back(make_pair(NUM::THREE, CResMgr::CreateSingleTonInst()->LoadTexture(L"THREE", L"../API/Damage/Prision.Number.3.png")));
	m_vecNumTex.push_back(make_pair(NUM::FOUR, CResMgr::CreateSingleTonInst()->LoadTexture(L"FOUR", L"../API/Damage/Prision.Number.4.png")));
	m_vecNumTex.push_back(make_pair(NUM::FIVE, CResMgr::CreateSingleTonInst()->LoadTexture(L"FIVE", L"../API/Damage/Prision.Number.5.png")));
	m_vecNumTex.push_back(make_pair(NUM::SIX, CResMgr::CreateSingleTonInst()->LoadTexture(L"SIX", L"../API/Damage/Prision.Number.6.png")));
	m_vecNumTex.push_back(make_pair(NUM::SEVEN, CResMgr::CreateSingleTonInst()->LoadTexture(L"SEVEN", L"../API/Damage/Prision.Number.7.png")));
	m_vecNumTex.push_back(make_pair(NUM::EIGHT, CResMgr::CreateSingleTonInst()->LoadTexture(L"EIGHT", L"../API/Damage/Prision.Number.8.png")));
	m_vecNumTex.push_back(make_pair(NUM::NINE, CResMgr::CreateSingleTonInst()->LoadTexture(L"NINE", L"../API/Damage/Prision.Number.9.png")));
}


int CTimer::Update()
{	
	static float fCount(0);
	if (fCount >= 1.f)			// 1초가 지났다면 
	{
		fCount = 0.f;
		m_iSecond -= 1;
	}
	if (m_iSecond < 0)
	{
		m_iMinute -= 1;
		m_iSecond = 59;
	}

	fCount += fDT;
	
	__super::Update_Rect();
    return 0;
}

void CTimer::Late_Update()
{
	
}

void CTimer::Render(HDC hDC)
{
	AlphaBlend(hDC
		, m_tRect.left	                        // ( 고정위치 )	// 이미지를 출력할 x
		, m_tRect.top					            // ( 고정위치 )  // 이미지를 출력할 y
		, m_tInfo.fCX					            // 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
		, m_tInfo.fCY
		, m_pUITex->GetDC()
		, 0								            // 가져올 이미지의 시작위치
		, 0
		, m_pUITex->Width() 			                // 잘라낼 크기니까 항상 800 이여야함
		, m_pUITex->Height()
		, this->GetBf());


	NUM iFirstMinute = NUM(m_iMinute / 10);      // 몫				(ex: 32 , 18 이럴때 10으로 나눠보면댐)
	NUM iSecondMinute = NUM(m_iMinute % 10);		// 나머지			(ex: 32 , 18 이럴때 10으로 나눠보면댐)

	NUM iFirstSecond = NUM(m_iSecond / 10);
	NUM iSecondSecond = NUM(m_iSecond % 10);


	for (int i = 0; i < 4; ++i)
	{
		CTexture* pRenderTex = nullptr;

		switch (i)
		{
		case 0:
		{
			switch (iFirstMinute)
			{
			case NUM::ZERO:
				pRenderTex = m_vecNumTex[(UINT)NUM::ZERO].second;
				break;
			case NUM::ONE:
				pRenderTex = m_vecNumTex[(UINT)NUM::ONE].second;
				break;
			case NUM::TWO:
				pRenderTex = m_vecNumTex[(UINT)NUM::TWO].second;
				break;
			case NUM::THREE:
				pRenderTex = m_vecNumTex[(UINT)NUM::THREE].second;
				break;
			case NUM::FOUR:
				pRenderTex = m_vecNumTex[(UINT)NUM::FOUR].second;
				break;
			case NUM::FIVE:
				pRenderTex = m_vecNumTex[(UINT)NUM::FIVE].second;
				break;
			case NUM::SIX:
				pRenderTex = m_vecNumTex[(UINT)NUM::SIX].second;
				break;
			case NUM::SEVEN:
				pRenderTex = m_vecNumTex[(UINT)NUM::SEVEN].second;
				break;
			case NUM::EIGHT:
				pRenderTex = m_vecNumTex[(UINT)NUM::EIGHT].second;
				break;
			case NUM::NINE:
				pRenderTex = m_vecNumTex[(UINT)NUM::NINE].second;
				break;
			case NUM::NUM_END:
				break;
			default:
				break;
			}
		}
			break;

		case 1:
		{
			switch (iSecondMinute)
			{
			case NUM::ZERO:
				pRenderTex = m_vecNumTex[(UINT)NUM::ZERO].second;
				break;
			case NUM::ONE:
				pRenderTex = m_vecNumTex[(UINT)NUM::ONE].second;
				break;
			case NUM::TWO:
				pRenderTex = m_vecNumTex[(UINT)NUM::TWO].second;
				break;
			case NUM::THREE:
				pRenderTex = m_vecNumTex[(UINT)NUM::THREE].second;
				break;
			case NUM::FOUR:
				pRenderTex = m_vecNumTex[(UINT)NUM::FOUR].second;
				break;
			case NUM::FIVE:
				pRenderTex = m_vecNumTex[(UINT)NUM::FIVE].second;
				break;
			case NUM::SIX:
				pRenderTex = m_vecNumTex[(UINT)NUM::SIX].second;
				break;
			case NUM::SEVEN:
				pRenderTex = m_vecNumTex[(UINT)NUM::SEVEN].second;
				break;
			case NUM::EIGHT:
				pRenderTex = m_vecNumTex[(UINT)NUM::EIGHT].second;
				break;
			case NUM::NINE:
				pRenderTex = m_vecNumTex[(UINT)NUM::NINE].second;
				break;
			case NUM::NUM_END:
				break;
			default:
				break;
			}
		}
			break;

		case 2:
		{
			switch (iFirstSecond)
			{
			case NUM::ZERO:
				pRenderTex = m_vecNumTex[(UINT)NUM::ZERO].second;
				break;
			case NUM::ONE:
				pRenderTex = m_vecNumTex[(UINT)NUM::ONE].second;
				break;
			case NUM::TWO:
				pRenderTex = m_vecNumTex[(UINT)NUM::TWO].second;
				break;
			case NUM::THREE:
				pRenderTex = m_vecNumTex[(UINT)NUM::THREE].second;
				break;
			case NUM::FOUR:
				pRenderTex = m_vecNumTex[(UINT)NUM::FOUR].second;
				break;
			case NUM::FIVE:
				pRenderTex = m_vecNumTex[(UINT)NUM::FIVE].second;
				break;
			case NUM::SIX:
				pRenderTex = m_vecNumTex[(UINT)NUM::SIX].second;
				break;
			case NUM::SEVEN:
				pRenderTex = m_vecNumTex[(UINT)NUM::SEVEN].second;
				break;
			case NUM::EIGHT:
				pRenderTex = m_vecNumTex[(UINT)NUM::EIGHT].second;
				break;
			case NUM::NINE:
				pRenderTex = m_vecNumTex[(UINT)NUM::NINE].second;
				break;
			case NUM::NUM_END:
				break;
			default:
				break;
			}
		}
			break;

		case 3:
		{
			switch (iSecondSecond)
			{
			case NUM::ZERO:
				pRenderTex = m_vecNumTex[(UINT)NUM::ZERO].second;
				break;
			case NUM::ONE:
				pRenderTex = m_vecNumTex[(UINT)NUM::ONE].second;
				break;
			case NUM::TWO:
				pRenderTex = m_vecNumTex[(UINT)NUM::TWO].second;
				break;
			case NUM::THREE:
				pRenderTex = m_vecNumTex[(UINT)NUM::THREE].second;
				break;
			case NUM::FOUR:
				pRenderTex = m_vecNumTex[(UINT)NUM::FOUR].second;
				break;
			case NUM::FIVE:
				pRenderTex = m_vecNumTex[(UINT)NUM::FIVE].second;
				break;
			case NUM::SIX:
				pRenderTex = m_vecNumTex[(UINT)NUM::SIX].second;
				break;
			case NUM::SEVEN:
				pRenderTex = m_vecNumTex[(UINT)NUM::SEVEN].second;
				break;
			case NUM::EIGHT:
				pRenderTex = m_vecNumTex[(UINT)NUM::EIGHT].second;
				break;
			case NUM::NINE:
				pRenderTex = m_vecNumTex[(UINT)NUM::NINE].second;
				break;
			case NUM::NUM_END:
				break;
			default:
				break;
			}
		}
			break;

		default:
			break;
		}
		

		

		//i가  2일땐  5정도 밀어줘야하고

		int k = 0;
		if (i >= 2)
			k = 17;


		AlphaBlend(hDC
			, (m_tInfo.fX - 30) + (NUM_WIDTH * i) + k	                        // ( 고정위치 )	// 이미지를 출력할 x
			, (m_tInfo.fY - 5)					            // ( 고정위치 )  // 이미지를 출력할 y
			, NUM_WIDTH					            // 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
			, NUM_HEIGHT
			, pRenderTex->GetDC()
			, 0								            // 가져올 이미지의 시작위치
			, 0
			, pRenderTex->Width() 			                // 잘라낼 크기니까 항상 800 이여야함
			, pRenderTex->Height()
			, this->GetBf());

	}
	

}

void CTimer::Release()
{
}


