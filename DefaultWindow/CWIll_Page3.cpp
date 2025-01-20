#include "stdafx.h"
#include "CWIll_Page3.h"

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

#include "CPoison.h"

#include "CBall.h"
#include "CBody.h"
#include "CWeb.h"

#include "CSound.h"

#include "CQuest.h"


CWIll_Page3::CWIll_Page3()
    : m_pPoison(nullptr)
{

    CreateAnimator();
}

CWIll_Page3::~CWIll_Page3()
{
}

void CWIll_Page3::Initialize(Vec2 _vPos)
{
    m_tInfo = { _vPos.x ,_vPos.y ,180.f,240.f };
    m_tInfo.fY = 581 - m_tInfo.fCY / 2;

    m_eObjType = OBJID::OBJ_BOSS;
    m_ePage = WILL_PAGE::PAGE3;
    m_eDir = MONSTER_DIR::LEFT;
    m_fMaxHp = 22000;
    m_fAttackInfo = 10.f;
    m_fSpeed = 100.f;

    m_fAllAttackDelay = 2.f;

    m_fAttackDelay = 1.f;           // 기본 거미공격
    m_fSkillDelay = 5.f;            // 독 뿌리기
    m_fSkill_2_Delay = 10.f;        // 하얀눈
    m_fSkill_3_Delay = 10.f;        // 주황눈
    m_fCreateWebDelay = 10.f;       // 거미줄 생성 시간

    m_fHp = m_fMaxHp;

    m_vAttack1RangeSize = Vec2(500.f, 200.f);     // 기본 거미공격
                                                  // 독이랑 거미줄은 보스 스킬에서 따로 충돌처리

    m_vAttack2RangeSize = Vec2(0.f);     // 하얀눈    // 타겟라인에 없으면 즉사
    m_vAttack3RangeSize = Vec2(0.f);     // 노란눈    // 타겟라인에 있으면 즉사



    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"boss3_walk_left", L"../API/Boss/page3/walk_left.png");
    GetAnimator()->CreateAnimation(L"boss3_walk_left", pTex, Vec2(0.f, 0.f), Vec2(243.f, 314.f), Vec2(0.f, 314.f), 0.1, 16);

   

    CTexture* pTex2 = CResMgr::CreateSingleTonInst()->LoadTexture(L"boss3_attack_left", L"../API/Boss/page3/attack_left.png");
    GetAnimator()->CreateAnimation(L"boss3_attack_left", pTex2, Vec2(0.f, 0.f), Vec2(667.f, 385.f), Vec2(0.f, 385.f), 0.1f, 25);




    CTexture* pTex4 = CResMgr::CreateSingleTonInst()->LoadTexture(L"boss3_skill_1_left", L"../API/Boss/page3/skill1_left.png");
    GetAnimator()->CreateAnimation(L"boss3_skill_1_left", pTex4, Vec2(0.f, 0.f), Vec2(350.f, 322.f), Vec2(0.f, 322.f), 0.08f, 24);


    CTexture* pTex5 = CResMgr::CreateSingleTonInst()->LoadTexture(L"boss3_skill_2_left", L"../API/Boss/page3/skill2_left.png");
    GetAnimator()->CreateAnimation(L"boss3_skill_2_left", pTex5, Vec2(0.f, 0.f), Vec2(1137.f, 798.f), Vec2(0.f, 798.f), 0.08f, 31);


    CTexture* pTex6 = CResMgr::CreateSingleTonInst()->LoadTexture(L"boss3_skill_3_left", L"../API/Boss/page3/skill3_left.png");
    GetAnimator()->CreateAnimation(L"boss3_skill_3_left", pTex6, Vec2(0.f, 0.f), Vec2(1144.f, 848.f), Vec2(0.f, 848.f), 0.08f, 31);



    CTexture* pTex7 = CResMgr::CreateSingleTonInst()->LoadTexture(L"boss3_dead", L"../API/Boss/page3/die.png");
    GetAnimator()->CreateAnimation(L"boss3_dead", pTex7, Vec2(0.f, 0.f), Vec2(788.f, 688.f), Vec2(788.f, 0.f), 0.13f, 42);


    GetAnimator()->Play(L"boss3_walk_left", false);

}

int CWIll_Page3::Update()
{
    if (m_bDeadAniPlay)
    {
        GetAnimator()->Play(L"boss3_dead", false);

        if (GetAnimator()->GetCurAnimation()->GetFinish())
        {
            CQuest* playerQuest = ((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->GetQuest();
            if (QUEST_TYPE::KILL_WILL == playerQuest->GetCurQuest())
            {
                playerQuest->SetSuccess(true);
            }

            this->Set_Dead();
            ChangeScene(SCENE_TYPE::LOBBY);
            return OBJ_DEAD;
        }
    }


    if (!m_bAttacking && !m_bDeadAniPlay)
        GetAnimator()->Play(L"boss3_walk_left", true);

   

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
                        pEffect->SetCreatePos(Vec2(tInfo.fX - 200.f, tInfo.fY - (m_iDamageCount * 35)));
                        CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_DAMAGE_EFFECT, pEffect);
                    }
                    else    // 파티클 타입이라는 소리고 
                    {
                        INFO tInfo = this->Get_Info();
                        int iDir = 1;
                        if (m_iDamageCount % 2 == 0)
                            iDir = -1;
                        pEffect->SetCreatePos(Vec2(tInfo.fX + (m_iDamageCount * 40) * iDir, tInfo.fY - (rand() % 300)));
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
    m_fSkillDelay -= fDT;
    m_fSkill_2_Delay -= fDT;
    m_fSkill_3_Delay -= fDT;
    m_fCreateWebDelay -= fDT;

    m_fAllAttackDelay -= fDT;

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CWIll_Page3::Late_Update()
{
    if (m_bDeadAniPlay)
    {
        GetAnimator()->Update();
        return;
    }

    if (m_fCreateWebDelay <= 0.f)
    {
        CWeb* pWeb = new CWeb;
        pWeb->Initialize();
        CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS_SKILL, pWeb);

        m_fCreateWebDelay = 10.f;
    }




    if (m_fAllAttackDelay <= 0.f)
    {
        if (m_fSkill_3_Delay <= 0.f)
            StartSkill3();                   // 노란눈
        else if (m_fSkill_2_Delay <= 0.f)
            StartSkill2();                   // 흰눈
        else if (m_fSkillDelay <= 0.f)
            StartSkill();                    // 독
        else if (m_fAllAttackDelay <= 0.f)
            StartAttack();                   // 기본공격



        m_fAllAttackDelay = 2.f;
    }



    if (GetAnimator()->GetCurAnimation()->GetFinish())
    {
        GetAnimator()->GetCurAnimation()->SetFrame(0);
        m_bAttacking = false;

        switch (m_eAttackType)
        {
        case WILL_ATTACK_TYPE::ATTACK1:
            m_fAttackDelay = 1.f;
            break;
        case WILL_ATTACK_TYPE::SKILL:
            m_fSkillDelay = 5.f;
            break;
        case WILL_ATTACK_TYPE::SKILL2:
            m_fSkill_2_Delay = 10.f;
            break;
        case WILL_ATTACK_TYPE::SKILL3:
            m_fSkill_3_Delay = 10.f;
            break;
        default:
            break;
        }
    }


    GetAnimator()->Update();
}

void CWIll_Page3::Render(HDC hDC)
{
    GetAnimator()->GetCurAnimation()->Render(hDC);


   // SelectGDI p(hDC, PEN_TYPE::GREEN);
   // SelectGDI b(hDC, BRUSH_TYPE::HOLLOW);
   //
   //
   // Vec2 vPos = CCamera::CreateSingleTonInst()->GetRenderPos(Vec2(m_tInfo.fX, m_tInfo.fY));
   //
   // Rectangle(hDC
   //     , (int)(vPos.x - m_tInfo.fCX / 2.f)
   //     , (int)(vPos.y - m_tInfo.fCY / 2.f)
   //     , (int)(vPos.x + m_tInfo.fCX / 2.f)
   //     , (int)(vPos.y + m_tInfo.fCY / 2.f));
   //
   //
   //
   // SelectGDI p1(hDC, PEN_TYPE::RED);
   // SelectGDI b1(hDC, BRUSH_TYPE::HOLLOW);
   //
   //
   // if (m_bAttacking)
   // {
   //    // Vec2 vPos1 = CCamera::CreateSingleTonInst()->GetRenderPos(Vec2(m_vAttack1RangePos));
   //    //
   //    // Rectangle(hDC
   //    //     , (int)(vPos1.x - m_vAttack1RangeSize.x / 2.f)
   //    //     , (int)(vPos1.y - m_vAttack1RangeSize.y / 2.f)
   //    //     , (int)(vPos1.x + m_vAttack1RangeSize.x / 2.f)
   //    //     , (int)(vPos1.y + m_vAttack1RangeSize.y / 2.f));
   //
   // }
}

void CWIll_Page3::Release()
{
}

void CWIll_Page3::StartAttack()
{
    if (!m_bAttacking)
    {
        m_eAttackType = WILL_ATTACK_TYPE::ATTACK1;
        m_bAttacking = true;

        m_vAttack1RangePos = Vec2(m_tInfo.fX, m_tInfo.fY);
        GetAnimator()->Play(L"boss3_attack_left", false);
    }
}


void CWIll_Page3::StartSkill()
{
    if (!m_bAttacking)
    {
        m_eAttackType = WILL_ATTACK_TYPE::SKILL;
        m_bSkillUsing = true;
        m_bAttacking = true;

        if (!m_pPoison)
        {
            CPoison* pPoison = new CPoison;
            pPoison->Initialize(GetPos());
            CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS_SKILL, pPoison);
        }
       
        GetAnimator()->Play(L"boss3_skill_1_left", false); 
    }
}

void CWIll_Page3::StartSkill2()
{
    if (!m_bAttacking)
    {
        m_eAttackType = WILL_ATTACK_TYPE::SKILL2;
        m_bSkillUsing = true;
        m_bAttacking = true;


        GetAnimator()->Play(L"boss3_skill_2_left", false);
    }
}

void CWIll_Page3::StartSkill3()
{
    if (!m_bAttacking)
    {
        m_eAttackType = WILL_ATTACK_TYPE::SKILL3;
        m_bSkillUsing = true;
        m_bAttacking = true;



        GetAnimator()->Play(L"boss3_skill_3_left", false);
    }
}
