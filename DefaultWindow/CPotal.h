#pragma once
#include "Obj.h"
class CPotal :
    public CObj
{
public:
    CPotal();
    ~CPotal();

public:
    virtual void Initialize(){}
    virtual void Initialize(Vec2 _vPos , SCENE_TYPE _e);


    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;


public:
    SCENE_TYPE      GetMoveSceneType() { return m_eMoveSceneType; }


private:
    SCENE_TYPE      m_eMoveSceneType;



};

