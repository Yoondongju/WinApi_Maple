#pragma once
#include "CScene.h"
class CBoss_Page1 :
    public CScene
{
public:
    CBoss_Page1();
    ~CBoss_Page1();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Enter() override;
    virtual void Exit() override;

};

