#pragma once
#include "CPlayerUI.h"


class CQuest;

class CConversationUI :public CPlayerUI
{
public:
	CConversationUI();
	~CConversationUI();

	virtual void Initialize() {}

	virtual void Initialize(NPC_TYPE _e);

	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void MouseLBtnDown();
	virtual void MouseLBtnUp();
	virtual void MouseClick();

	virtual void MouseOn();
	virtual void MouseOut();


public:
	void	StartAction();
	void    SetReText();

public:

	void	SetInteractionObj(CObj* _p) { m_pInteractionObj = _p; }
	CObj*	GetInteractionObj() { return m_pInteractionObj; }


	BYTE GetCount() { return m_iCount; }
	void SetCount(BYTE _ch) { m_iCount = _ch; }

	BYTE GetMaxCount() { return m_iMaxCount; }
	void SetMaxCount(BYTE _ch) { m_iMaxCount = _ch; }


private:
	CObj*					m_pInteractionObj;


	CTexture*					m_pPlayerTex;
	CTexture*					m_pNpcTex;
	CTexture*					m_pRenderTex;

	vector <pair<wstring,BYTE>>			m_vecText;		// 두번째 값이 0이면 플레이어 1이면 npc
	

	NPC_TYPE					m_eActionType;
	BYTE						m_iMaxCount;
	BYTE						m_iCount;

};

