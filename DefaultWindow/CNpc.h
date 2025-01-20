#pragma once
#include "Obj.h"



class CNpc : public CObj
{
public:
    CNpc();
    ~CNpc();

public:
    // CObj을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;




public:
    bool        IsRecognize() { return m_bRecognize; }

    NPC_TYPE    GetNpcType() { return m_eNpcType; }
    
protected:
    void CheckRecognize();

protected:
    RECT        m_rtRecognize;
    bool        m_bRecognize;
    
    NPC_TYPE    m_eNpcType;



};

