#pragma once
#include "CScene.h"
class CBoss_Page3 :
    public CScene
{
public:
    CBoss_Page3();
    ~CBoss_Page3();

public:
    // CScene을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Enter() override;
    virtual void Exit() override;
};

