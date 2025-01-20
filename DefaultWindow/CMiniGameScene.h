#pragma once
#include "CScene.h"
class CMiniGameScene :
    public CScene
{
public:
    CMiniGameScene();
    ~CMiniGameScene();

public:

    // CScene을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual void Late_Update() override;
    virtual void Update();

    virtual void Render(HDC hDC) override;
    virtual void Enter() override;

    virtual void Exit();


public:
    void    SetGameStart(bool _b) { m_bGameStart = _b; }


private:
    float       m_fCreateBoom;
    bool        m_bGameStart;
};

