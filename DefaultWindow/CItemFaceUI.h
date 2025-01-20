#pragma once
#include "CStoreUI.h"

class CTexture;

class CItemFaceUI :
    public CPlayerUI
{
public:
	CItemFaceUI();
	~CItemFaceUI();


	virtual void Initialize(){}
	virtual void Initialize(CTexture* _pTex, UI_TYPE _e , ITEM_TYPE _eItemType);


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

	ITEM_TYPE GetItemType() { return m_eItemType; }


public:
	int GetEquipNum() { return m_iEquipNum; }
	void SetEquipNum(int _i) { m_iEquipNum = _i; }


private:
	static int				m_iCountStoreNum;
	int						m_iStoreNum;

	static int				m_iCountEquipNum;
	int						m_iEquipNum;

	static int				m_iCountSobiNum;
	int						m_iSobiNum;
	
	ITEM_TYPE				m_eItemType;


	Vec2					m_vDragStart;

	bool					m_bEquip;

	bool					m_bClick;
};

