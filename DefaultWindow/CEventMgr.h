#pragma once
#include "Define.h"

enum EVENT_TYPE
{
	SCENE_CHANGE,
	EVENT_END
};

struct tEvent
{
	EVENT_TYPE		eEven;
	DWORD_PTR		lParam;
	DWORD_PTR		wParam;

};

class CEventMgr
{
	SINGLE(CEventMgr)

public:
	void Update();
	void Excute(const tEvent& _eve);

	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); }

private:
	vector<tEvent>	m_vecEvent;

};

