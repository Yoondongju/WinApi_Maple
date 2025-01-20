#pragma once
#include "Obj.h"

class CTexture;


class CItem : public CObj
{
public:
    CItem();
    ~CItem();

public:
    virtual void Initialize() { }
    virtual void Initialize(ITEM_TYPE _e, int _iPrice , CTexture* pTex);


    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;




protected:
    ITEM_TYPE   m_eItemType;
    int         m_iPrice;
   
    CTexture*   m_pTex;



};

