#include "stdafx.h"
#include "CQuest.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "ObjMgr.h"
#include "CTimeMgr.h"

#include "Player.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CQuickSlotUI.h"
#include "CEquipUI.h"

#include "CSound.h"

CQuest::CQuest()
    : m_bSuccess(false)
{
    m_eCurQuest = QUEST_TYPE::PORTIONBUY_DRAG;
    m_eObjType = OBJID::OBJ_BACKGROUD;
    CreateAnimator();
}

CQuest::~CQuest()
{
}

void CQuest::Initialize(Vec2 _vPos)
{
    m_tInfo = { _vPos.x , _vPos.y , 50.f , 56.f };
    m_eQuestState = QUEST_STATE::WAIT;

   
    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"wait", L"../API/UI/quest/left.png");
    GetAnimator()->CreateAnimation(L"wait", pTex, Vec2(0.f, 0.f), Vec2(44.f, 46.f), Vec2(44.f, 0.f), 0.5f, 8);


    CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"proceed", L"../API/UI/quest/middle.png");
    GetAnimator()->CreateAnimation(L"proceed", pTex1, Vec2(0.f, 0.f), Vec2(42.f, 44.f), Vec2(42.f, 0.f), 0.5f, 4);


    CTexture* pTex2 = CResMgr::CreateSingleTonInst()->LoadTexture(L"complete", L"../API/UI/quest/right.png");
    GetAnimator()->CreateAnimation(L"complete", pTex2, Vec2(0.f, 0.f), Vec2(44.f, 44.f), Vec2(44.f, 0.f), 0.5f, 8);



    GetAnimator()->Play(L"wait", true);
}

int CQuest::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

  
    StartQuest();


 

    if (m_bSuccess)
    {
        m_eQuestState = QUEST_STATE::COMPLETE;
    }
       
   


    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CQuest::Late_Update()
{

    switch (m_eQuestState)
    {
    case QUEST_STATE::WAIT:
        GetAnimator()->Play(L"wait", true);
        break;
    case QUEST_STATE::PROCEED:
        GetAnimator()->Play(L"proceed", true);
        break;
    case QUEST_STATE::COMPLETE:
    {
        GetAnimator()->Play(L"complete", true);
    }
      
        break;
    case QUEST_STATE::END:
        break;
    default:
        break;
    }

    GetAnimator()->Update();
}

void CQuest::Render(HDC hDC)
{
    GetAnimator()->GetCurAnimation()->Render(hDC);
}

void CQuest::Release()
{
}

void CQuest::StartQuest()
{
    CPlayer* pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();

    switch (m_eCurQuest)
    {
    case QUEST_TYPE::PORTIONBUY_DRAG:
    {
        if (pPlayer->GetPlayerQuickSlotUI()->GetChildUI().size() > 0)
            m_bSuccess = true;
    }
        break;
    case QUEST_TYPE::PETBUY_ACTIVE:
    {
        if (pPlayer->GetMyPet())
            m_bSuccess = true;
    }
        break;
    case QUEST_TYPE::TICKSTAT:
    {
        if (pPlayer->GetSTR() > 4)
            m_bSuccess = true;
    }
        break;
    case QUEST_TYPE::TICKSKILL:
    {
        CPlayerSkill** pSkill = pPlayer->GetAllSkill();
        bool bCheck = true;

        for (auto i = 0; i < SKILL_TYPE::SKILL_END; ++i)
        {
            if (nullptr == pSkill[i])
                bCheck = false;
        }   
        if(bCheck)
            m_bSuccess = true;
    }
        break;
    case QUEST_TYPE::HUNTING1:
    {
        if (pPlayer->GetLevel() == 9)
            m_bSuccess = true;
    }
        break;

    case QUEST_TYPE::MINIGAME:
    {
        // 미니 게임 나갓을때 처리햇음
    }
        break;

    case QUEST_TYPE::TICKSIX:
    {
       
    }
    break;

    case QUEST_TYPE::HUNTING2:
    {
        // 카이아린 뒤질때 처리햇음 문제시 카이아린의 업데이트를 보라
    }
        break;
    case QUEST_TYPE::WEARINGPARTS:
    {
        if (pPlayer->GetPlayerEquipUI()->GetChildUI().size() >= 1)
            m_bSuccess = true;
    }
        break;
    case QUEST_TYPE::KILL_WILL:
    {
        // 윌 죽엇을ㄸ ㅐ 처리햇음
    }
        break;

    default:
        break;
    }
   
}
