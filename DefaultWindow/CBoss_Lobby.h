#pragma once
#include "CScene.h"

class CPlayerUI;

class CBoss_Lobby :
    public CScene
{
public:
    CBoss_Lobby();
    ~CBoss_Lobby();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Enter() override;
    virtual void Exit() override;


private:
    Vec2            m_vRecogPos;
    Vec2            m_vRecogSize;

    CPlayerUI* m_pConversationUI;

};

