#pragma once
#include "Obj.h"


enum class QUEST_STATE
{
    WAIT,
    PROCEED,
    COMPLETE,

    END,
};


enum class QUEST_TYPE
{
    PORTIONBUY_DRAG,
    PETBUY_ACTIVE,
    TICKSTAT,
    TICKSKILL,
    HUNTING1,

    MINIGAME,

    TICKSIX,
    

    HUNTING2,
    WEARINGPARTS,

    
    KILL_WILL,

    EMD,
};



class CTexture;

class CQuest :
    public CObj
{
public:
    CQuest();
    ~CQuest();

public:
    virtual void Initialize(){}
    virtual void Initialize(Vec2 _vPos);

    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

    void StartQuest();

public:
    void SetState(QUEST_STATE _e) { m_eQuestState = _e; }
    QUEST_STATE GetState() { return m_eQuestState; }


public:
    void       SetCurQuest(QUEST_TYPE _e) { m_eCurQuest = _e;  m_bSuccess = false; }    // 퀘스트 재할당시 미션성공여부 false로 초기화d
    QUEST_TYPE GetCurQuest() { return m_eCurQuest; }


    bool       IsSuccess() { return m_bSuccess; }
    void       SetSuccess(bool _b) { m_bSuccess = _b; }

private:
    QUEST_STATE         m_eQuestState;
    QUEST_TYPE          m_eCurQuest;
    bool                m_bSuccess;
};



