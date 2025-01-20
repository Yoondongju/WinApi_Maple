#include "stdafx.h"
#include "CKariain.h"

#include "ObjMgr.h"
#include "CResMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "SelectGDI.h"

#include "Player.h"

#include "CTimeMgr.h"

#include "CPlayerSkill.h"
#include "CDamageEffect.h"

#include "CMoney.h"
#include "CSound.h"
#include <random>

#include "CKariainSkill.h"

#include "CQuest.h"
#include "CTimer.h"


CKariain::CKariain()
    : m_pCreateAni(nullptr)
{
    CreateAnimator();
}

CKariain::~CKariain()
{
    list<CObj*>& BossSkill_List= CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_BOSS_SKILL);
    //짜피 한개바께없음

    Safe_Delete(BossSkill_List.back());
    BossSkill_List.clear();


    if (m_pMySkill)
        m_pMySkill = nullptr;

    m_pCreateAni = nullptr;
}

void CKariain::Initialize(Vec2 _vPos)
{
    m_tInfo = { _vPos.x ,_vPos.y ,250.f,380.f };
    m_eObjType = OBJID::OBJ_BOSS;
    m_fSpeed = 400.f;
    m_iDropExp = 10;
    m_iDropMoney = 1000;
    m_fAttackDelay = 10.f;
    m_fTelepoteDelay = 6.f;

    m_fMaxHp = 20000;
    m_fHp = m_fMaxHp;

    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"kariain_stand_left", L"../API/kariain/stand_left.png");
    GetAnimator()->CreateAnimation(L"kariain_stand_left", pTex, Vec2(0.f, 0.f), Vec2(256.f, 259.f), Vec2(256.f, 0.f), 0.4f, 8);
   
    CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"kariain_stand_right", L"../API/kariain/stand_right.png");
    GetAnimator()->CreateAnimation(L"kariain_stand_right", pTex1, Vec2(0.f, 0.f), Vec2(256.f, 259.f), Vec2(256.f, 0.f), 0.4f, 8);



    CTexture* pTex2 = CResMgr::CreateSingleTonInst()->LoadTexture(L"kariain_walk_left", L"../API/kariain/walk_left.png");
    GetAnimator()->CreateAnimation(L"kariain_walk_left", pTex2, Vec2(0.f, 0.f), Vec2(264.f, 260.f), Vec2(264.f, 0.f), 0.07f, 6);

    CTexture* pTex3 = CResMgr::CreateSingleTonInst()->LoadTexture(L"kariain_walk_right", L"../API/kariain/walk_right.png");
    GetAnimator()->CreateAnimation(L"kariain_walk_right", pTex3, Vec2(0.f, 0.f), Vec2(264.f, 260.f), Vec2(264.f, 0.f), 0.07f, 6);



    CTexture* pTex4 = CResMgr::CreateSingleTonInst()->LoadTexture(L"kariain_attack1", L"../API/kariain/attack1.png");
    GetAnimator()->CreateAnimation(L"kariain_attack1", pTex4, Vec2(0.f, 0.f), Vec2(323.f, 357.f), Vec2(323.f, 0.f), 0.06f, 34);

    CTexture* pTex5 = CResMgr::CreateSingleTonInst()->LoadTexture(L"kariain_attack2", L"../API/kariain/attack2.png");
    GetAnimator()->CreateAnimation(L"kariain_attack2", pTex5, Vec2(0.f, 0.f), Vec2(308.f, 359.f), Vec2(308.f, 0.f), 0.06f, 35);
    


    CTexture* pTex8 = CResMgr::CreateSingleTonInst()->LoadTexture(L"kariain_telepote", L"../API/kariain/telepote.png");
    GetAnimator()->CreateAnimation(L"kariain_telepote", pTex8, Vec2(0.f, 0.f), Vec2(310.f, 320.f), Vec2(310.f, 0.f), 0.1f, 21);


    CTexture* pTex9 = CResMgr::CreateSingleTonInst()->LoadTexture(L"kariain_die", L"../API/kariain/die.png");
    GetAnimator()->CreateAnimation(L"kariain_die", pTex9, Vec2(0.f, 0.f), Vec2(301.f, 248.f), Vec2(301.f, 0.f), 0.15f, 16);



    CTexture* pTex10 = CResMgr::CreateSingleTonInst()->LoadTexture(L"kariain_create", L"../API/kariain/create.png");
    GetAnimator()->CreateAnimation(L"kariain_create", pTex10, Vec2(0.f, 0.f), Vec2(861.f, 639.f), Vec2(861.f, 0.f), 0.1f, 33);


    GetAnimator()->Play(L"kariain_create", false);
    m_pCreateAni = GetAnimator()->GetCurAnimation();        // 한번 부여


    CKariainSkill* pSkill = new CKariainSkill;
    pSkill->Initialize(m_eDir);
    CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS_SKILL, pSkill);
    pSkill->SetActive(false);
    m_pMySkill = pSkill;
    




    CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"LM_gen");
    pNewSound->Play(false);
    pNewSound->SetPosition(1.f); // 백분률 , 소리위치
    pNewSound->SetVolume(50.f); // 소리 볼륨 크기
}

int CKariain::Update()
{

    if (m_bDeadAniPlay)
    {
        CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"LM_die");
        pNewSound->Play(false);
        pNewSound->SetPosition(1.f); // 백분률 , 소리위치
        pNewSound->SetVolume(50.f); // 소리 볼륨 크기

        GetAnimator()->Play(L"kariain_die", false);

        if (GetAnimator()->GetCurAnimation()->GetFinish())
        {
            CQuest* playerQuest = ((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->GetQuest();
            if (QUEST_TYPE::HUNTING2 == playerQuest->GetCurQuest())
            {
                playerQuest->SetSuccess(true);
            }


            list<CObj*>& UI = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_UI);
            for (auto iter = UI.begin(); iter != UI.end();)
            {
                CTimer* pTimer = dynamic_cast<CTimer*>(*iter);

                if (pTimer)
                {
                    Safe_Delete<CObj*>(*iter);
                    iter = UI.erase(iter);
                }
                else
                    ++iter;
            }



            this->Set_Dead();           
            return OBJ_DEAD;
        }
    }


    if (m_bDeadAniPlay)
        return OBJ_NOEVENT;

    if (m_fAttackDelay <= 0.f)
    {
        if (m_fTelepoteDelay <= 0.f)
            StartTelepote();
        else
        {
            StartAttack();
            m_pMySkill->SetActive(true);
        }
            
    }



    if (m_bHit)
    {
        CPlayerSkill* pSkill = dynamic_cast<CPlayerSkill*>(m_pCollisonObj);
        if (pSkill)
        {
            if (m_iDamageCount > 20)        // 버그 터지면 (이유모름 일단 막아둠)
                m_iDamageCount = 0;

            int iAttackCount = pSkill->GetAttackCount();

            if (m_iDamageCount < iAttackCount && m_iDamageCount == 0 || m_fDamageCreateDelay <= 0.f)
            {
                if (SKILL_TYPE::DEATHFAULT == m_eColliSkillType)
                {
                    CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"black_jack_hit");
                    pNewSound->Play(false);
                    pNewSound->SetPosition(1.f); // 백분률 , 소리위치
                    pNewSound->SetVolume(50.f); // 소리 볼륨 크기


                    CDamageEffect* pEffect = new CDamageEffect;
                    pEffect->Initialize();

                    if (DamageEffectType::PATICLE != pEffect->GetCurDamageEffect())
                    {
                        INFO tInfo = this->Get_Info();
                        pEffect->SetCreatePos(Vec2(tInfo.fX - tInfo.fCX / 2.f, tInfo.fY - (m_iDamageCount * 35)));
                        CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_DAMAGE_EFFECT, pEffect);
                    }
                    else    // 파티클 타입이라는 소리고 
                    {
                        INFO tInfo = this->Get_Info();
                        int iDir = 1;
                        if (m_iDamageCount % 2 == 0)
                            iDir = -1;
                        pEffect->SetCreatePos(Vec2(tInfo.fX + (m_iDamageCount * 20) * iDir, tInfo.fY - (rand() % 300)));
                        CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_DAMAGE_EFFECT, pEffect);
                    }



                    ++m_iDamageCount;
                    m_fDamageCreateDelay = 0.08f;
                }
                else if (SKILL_TYPE::RAGINGBLOW == m_eColliSkillType)
                {
                    CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"black_jack");
                    pNewSound->Play(false);
                    pNewSound->SetPosition(1.f); // 백분률 , 소리위치
                    pNewSound->SetVolume(50.f); // 소리 볼륨 크기

                    CDamageEffect* pEffect = new CDamageEffect;
                    pEffect->Initialize();

                    if (DamageEffectType::PATICLE != pEffect->GetCurDamageEffect())
                    {
                        INFO tInfo = this->Get_Info();
                        pEffect->SetCreatePos(Vec2(tInfo.fX - tInfo.fCX / 2.f, tInfo.fY - (m_iDamageCount * 35)));
                        CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_DAMAGE_EFFECT, pEffect);
                    }
                    else    // 파티클 타입이라는 소리고 
                    {
                        INFO tInfo = this->Get_Info();
                        int iDir = 1;
                        if (m_iDamageCount % 2 == 0)
                            iDir = -1;
                        pEffect->SetCreatePos(Vec2(tInfo.fX + (m_iDamageCount * 20) * iDir, tInfo.fY - (rand() % 300)));
                        CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_DAMAGE_EFFECT, pEffect);
                    }



                    ++m_iDamageCount;
                    m_fDamageCreateDelay = 0.08f;
                }
                else if (SKILL_TYPE::SIX == m_eColliSkillType)
                {
                    wstring strKey = pSkill->GetAnimator()->GetCurAnimation()->GetKey();

                    if (strKey == L"six_1"
                        || strKey == L"six_2"
                        || strKey == L"six_9"
                        || strKey == L"six_10"
                        || strKey == L"six_11")
                    {
                        CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"player_six_sound");
                        pNewSound->Play(true);
                        pNewSound->SetPosition(1.f); // 백분률 , 소리위치
                        pNewSound->SetVolume(70.f); // 소리 볼륨 크기



                        pSkill->SetFirstAttack(true);

                        CDamageEffect* pEffect = new CDamageEffect;
                        pEffect->Initialize();


                        if (DamageEffectType::PATICLE != pEffect->GetCurDamageEffect())
                        {
                            INFO tInfo = this->Get_Info();
                            pEffect->SetCreatePos(Vec2(tInfo.fX - tInfo.fCX / 2.f, tInfo.fY - (m_iDamageCount * 35)));
                            CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_DAMAGE_EFFECT, pEffect);
                        }
                        else    // 파티클 타입이라는 소리고 
                        {
                            INFO tInfo = this->Get_Info();
                            int iDir = 1;
                            if (m_iDamageCount % 2 == 0)
                                iDir = -1;
                            pEffect->SetCreatePos(Vec2(tInfo.fX + (m_iDamageCount * 20) * iDir, tInfo.fY - (rand() % 300)));
                            CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_DAMAGE_EFFECT, pEffect);
                        }



                        ++m_iDamageCount;
                        m_fDamageCreateDelay = 0.08f;
                    }
                }
                else
                {
                    CDamageEffect* pEffect = new CDamageEffect;
                    pEffect->Initialize();

                    if (DamageEffectType::PATICLE != pEffect->GetCurDamageEffect())
                    {
                        INFO tInfo = this->Get_Info();
                        pEffect->SetCreatePos(Vec2(tInfo.fX - 200.f, tInfo.fY - (m_iDamageCount * 35)));
                        CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_DAMAGE_EFFECT, pEffect);
                    }
                    else    // 파티클 타입이라는 소리고 
                    {
                        INFO tInfo = this->Get_Info();
                        int iDir = 1;
                        if (m_iDamageCount % 2 == 0)
                            iDir = -1;
                        pEffect->SetCreatePos(Vec2(tInfo.fX + (m_iDamageCount * 50) * iDir, tInfo.fY - (rand() % 300)));
                        CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_DAMAGE_EFFECT, pEffect);
                    }


                    ++m_iDamageCount;
                    m_fDamageCreateDelay = 0.08f;
                }

            }



            m_fDamageCreateDelay -= fDT;

            if (m_iDamageCount == iAttackCount)
            {
                m_iDamageCount = 0;                 // 999 아님?
                m_fDamageCreateDelay = 0.08f;
                m_pCollisonObj = nullptr;
            }
        }

    }



    m_fAttackDelay -= fDT;
    m_fTelepoteDelay -= fDT;

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CKariain::Late_Update()
{
    if (m_bDeadAniPlay)
    {
        GetAnimator()->Update();
        return;
    }

 

    if (m_pCreateAni->GetFinish())
    {

        float pY = 0.f;
        m_bLineCol = CLineMgr::Get_Instance()->Collision_LineMonster(this, m_tInfo.fX, m_tInfo.fY, &pY, &m_fTargetX);

        if (m_bLineCol)
        {
            if (m_tInfo.fY + (m_tInfo.fCY / 2.f) + 5 < pY)
            {
                m_tInfo.fY += 1000.f * fDT;
            }
            else if (m_tInfo.fY + (m_tInfo.fCY / 2.f) + 5 >= pY)
            {
                m_tInfo.fY = pY - m_tInfo.fCY / 2;
            }


            if (!m_bAttacking && 5 > abs(m_fTargetX - m_tInfo.fX))
            {
                m_bArrival = true;
                m_fMoveDelay -= fDT;

                switch (m_eDir)
                {
                case MONSTER_DIR::LEFT:
                    GetAnimator()->Play(L"kariain_stand_left", true);
                    break;
                case MONSTER_DIR::RIGHT:
                    GetAnimator()->Play(L"kariain_stand_right", true);
                    break;
                default:
                    break;
                }

            }

            else
            {
                m_bArrival = false;

                if (!m_bAttacking && m_fTargetX > m_tInfo.fX)
                {
                    m_tInfo.fX += m_fSpeed * fDT;

                    m_eDir = MONSTER_DIR::RIGHT;
                    GetAnimator()->Play(L"kariain_walk_right", true);
                }
                else if (!m_bAttacking && m_fTargetX < m_tInfo.fX)
                {
                    m_tInfo.fX -= m_fSpeed * fDT;

                    m_eDir = MONSTER_DIR::LEFT;
                    GetAnimator()->Play(L"kariain_walk_left", true);
                }
            }
        }
    }


    if (GetAnimator()->GetCurAnimation()->GetFinish())
    {    
        GetAnimator()->GetCurAnimation()->SetFrame(0);
        m_bAttacking = false;
        

        switch (m_eState)
        {
        case KARIAIN_STATE::ATTACK1:
        {            
            m_pMySkill->SetActive(false);
        }
           
            break;
        case KARIAIN_STATE::ATTACK2:
        { 
            m_pMySkill->SetActive(false);
        }
            break;
        case KARIAIN_STATE::TELEPOTE:
        {
            std::random_device rd;
            std::mt19937 mt(rd());

            std::uniform_int_distribution<int> distX(0, WINCX);
            float randNumX = distX(mt);
            std::uniform_int_distribution<int> distY(0, WINCY);
            float randNumY = distY(mt);


            m_tInfo.fX = randNumX;
            m_tInfo.fY = randNumY;
            m_fTelepoteDelay = 10.f;
        }        
            break;
        default:
            break;
        }
    }



    GetAnimator()->Update();
}

void CKariain::Render(HDC hDC)
{
    GetAnimator()->GetCurAnimation()->Render(hDC);


    //SelectGDI p(hDC, PEN_TYPE::GREEN);
    //SelectGDI b(hDC, BRUSH_TYPE::HOLLOW);
    //
    //
    //Vec2 vPos = CCamera::CreateSingleTonInst()->GetRenderPos(Vec2(m_tInfo.fX, m_tInfo.fY));
    //
    //Rectangle(hDC
    //    , (int)(vPos.x - m_tInfo.fCX / 2.f)
    //    , (int)(vPos.y - m_tInfo.fCY / 2.f)
    //    , (int)(vPos.x + m_tInfo.fCX / 2.f)
    //    , (int)(vPos.y + m_tInfo.fCY / 2.f));
}

void CKariain::Release()
{
}


void CKariain::StartAttack()
{
    m_fAttackDelay = 10.f;
    m_bAttacking = true;


    static bool bCheck = false;

    if (!bCheck)
    {
        CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"LM_attack1");
        pNewSound->Play(false);
        pNewSound->SetPosition(1.f); // 백분률 , 소리위치
        pNewSound->SetVolume(50.f); // 소리 볼륨 크기

        m_eState = KARIAIN_STATE::ATTACK1;
        GetAnimator()->Play(L"kariain_attack1", false);
        
        bCheck = true;
    }
    else
    {
        CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"LM_attack3");
        pNewSound->Play(false);
        pNewSound->SetPosition(1.f); // 백분률 , 소리위치
        pNewSound->SetVolume(50.f); // 소리 볼륨 크기

        m_eState = KARIAIN_STATE::ATTACK2;
        GetAnimator()->Play(L"kariain_attack2", false);

        bCheck = false;
    }
    
}

void CKariain::StartTelepote()
{
    m_bAttacking = true;
    GetAnimator()->Play(L"kariain_telepote", false);
    
    m_eState = KARIAIN_STATE::TELEPOTE;
}
