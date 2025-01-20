#pragma once
#include "CScene.h"

#include "CMonster.h"

class CHuntingGround :
    public CScene
{
public:
    CHuntingGround();
    ~CHuntingGround();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Enter() override;
    virtual void Exit() override;



private:
   

};

