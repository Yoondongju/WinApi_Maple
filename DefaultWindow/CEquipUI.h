#pragma once
#include "CPlayerUI.h"
class CEquipUI :
    public CPlayerUI
{
public:
	CEquipUI();
	~CEquipUI();

	virtual void Initialize() override;
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
	Vec2	GetItemOffset(ITEM_TYPE _e) { return m_vItemOffset[(UINT)_e]; }
	Vec2	GetItemTargetPos(ITEM_TYPE _e) { return m_vItemTargetPos[(UINT)_e]; }

private:
	Vec2			m_vDragStart;

	Vec2			m_vItemOffset[(UINT)ITEM_TYPE::ITEM_END];  // ������ ���� ��ġ�� �ڸ��� �ٸ���
	Vec2			m_vItemTargetPos[(UINT)ITEM_TYPE::ITEM_END];  // ������ ���� ��ġ�� �ڸ��� �ٸ���
};

