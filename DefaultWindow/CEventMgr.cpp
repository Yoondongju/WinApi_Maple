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
	for (size_t i = 0; i < m_vecEvent.size(); ++i)   // �Ҹ��� �Ժη� �ǵ帮�� ����.. �������� ���ɽ����� �ٷ����
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

		// ��Ŀ�� UI ���� (���� Scene�� UI�� ����Ű�� �ֱ� ����)
		CUIMgr::CreateSingleTonInst()->SetFocusUI(nullptr);
	}
	break;

	default:
		break;
	}

}
