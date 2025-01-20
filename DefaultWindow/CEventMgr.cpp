#include "stdafx.h"
#include "CEventMgr.h"

#include "CSceneMgr.h"
#include "CUIMgr.h"


CEventMgr::CEventMgr()
{
	m_vecEvent.reserve(5);
}

CEventMgr::~CEventMgr()
{




}

void CEventMgr::Update()
{
	for (size_t i = 0; i < m_vecEvent.size(); ++i)   // 소멸자 함부로 건드리지 말자.. 문제생김 조심스럽게 다뤄야함
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();

}

void CEventMgr::Excute(const tEvent& _eve )
{
	switch (_eve.eEven)
	{
	case (UINT)EVENT_TYPE::SCENE_CHANGE:
	{
		// lParam: Next Scene Type
		CSceneMgr::CreateSingleTonInst()->SceneChange((SCENE_TYPE)_eve.lParam);

		// 포커스 UI 해제 (이전 Scene의 UI를 가르키고 있기 때문)
		CUIMgr::CreateSingleTonInst()->SetFocusUI(nullptr);
	}
	break;

	default:
		break;
	}

}
