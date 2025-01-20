#pragma once
#include "CScene.h"

class CKariain;

class CHuntingGround2 :
    public CScene
{
public:
    CHuntingGround2();
    ~CHuntingGround2();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Enter() override;
    virtual void Exit() override;


private:
    float           m_fCreateLMDelay;
    CKariain*       m_pKariain;
};

