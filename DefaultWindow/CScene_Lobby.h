#pragma once
#include "CScene.h"
class CScene_Lobby :
    public CScene
{
public:
    CScene_Lobby();
    ~CScene_Lobby();

public:

    // CScene을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual void Late_Update() override;
    virtual void Update();

    virtual void Render(HDC hDC) override;
    virtual void Enter() override;

    virtual void Exit();

private:
   
   

};

