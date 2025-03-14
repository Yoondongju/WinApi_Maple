#include "stdafx.h"
#include "CWill_Page1.h"

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

#include "CBall.h"
#include "CBody.h"
#include <ctime>

#include "CSound.h"

CWill_Page1::CWill_Page1()
    : m_bSkillUsing(false)
    , m_pBall(nullptr)
    , m_fCreateBodyDelay(4.f)
    , m_pBody(nullptr)
{
    srand(time(NULL));
    CreateAnimator();
}

CWill_Page1::~CWill_Page1()
{
}

void CWill_Page1::Initialize(Vec2 _vPos)
{
    m_tInfo = { _vPos.x ,_vPos.y ,180.f,240.f };
    m_eObjType = OBJID::OBJ_BOSS;
    m_ePage = WILL_PAGE::PAGE1;
    m_fMaxHp = 10000;
    m_fAttackInfo = 10.f;
    m_fSpeed = 100.f;
    m_fAttackDelay = 1.f;
    m_fSkillDelay = 5.f;
    m_fHp = m_fMaxHp;

    m_vAttack1RangeSize = Vec2(250.f, 150.f);


    

    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"boss_walk_left", L"../API/Boss/page1/walk_left.png");
    GetAnimator()->CreateAnimation(L"boss_walk_left", pTex, Vec2(0.f, 0.f), Vec2(174.f, 194.f), Vec2(174.f, 0.f), 0.3, 8);

    CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"boss_walk_right", L"../API/Boss/page1/walk_right.png");
    GetAnimator()->CreateAnimation(L"boss_walk_right", pTex1, Vec2(0.f, 0.f), Vec2(174.f, 194.f), Vec2(174.f, 0.f), 0.3, 8);


    CTexture* pTex2 = CResMgr::CreateSingleTonInst()->LoadTexture(L"boss_attack_left", L"../API/Boss/page1/attack1_left.png");
    GetAnimator()->CreateAnimation(L"boss_attack_left", pTex2, Vec2(0.f, 0.f), Vec2(593.f, 321.f), Vec2(593.f, 0.f), 0.1f, 20);

    CTexture* pTex3 = CResMgr::CreateSingleTonInst()->LoadTexture(L"boss_attack_right", L"../API/Boss/page1/attack1_right.png");
    GetAnimator()->CreateAnimation(L"boss_attack_right", pTex3, Vec2(0.f, 0.f), Vec2(593.f, 321.f), Vec2(593.f, 0.f), 0.1f, 20);



    CTexture* pTex4 = CResMgr::CreateSingleTonInst()->LoadTexture(L"boss_attack3_left", L"../API/Boss/page1/attack3_left.png");
    GetAnimator()->CreateAnimation(L"boss_attack3_left", pTex4, Vec2(0.f, 0.f), Vec2(345.f, 522.f), Vec2(345.f, 0.f), 0.08f, 16);

    CTexture* pTex5 = CResMgr::CreateSingleTonInst()->LoadTexture(L"boss_attack3_right", L"../API/Boss/page1/attack3_right.png");
    GetAnimator()->CreateAnimation(L"boss_attack3_right", pTex5, Vec2(0.f, 0.f), Vec2(345.f, 522.f), Vec2(345.f, 0.f), 0.08f, 16);


    CTexture* pTex6 = CResMgr::CreateSingleTonInst()->LoadTexture(L"boss_dead", L"../API/Boss/page1/die_left.png");
    GetAnimator()->CreateAnimation(L"boss_dead", pTex6, Vec2(0.f, 0.f), Vec2(250.f, 455.f), Vec2(250.f, 0.f), 0.12f, 64);

    GetAnimator()->Play(L"boss_walk_left", true);
}

int CWill_Page1::Update()
{
    if (m_bDeadAniPlay)
    {
        GetAnimator()->Play(L"boss_dead", false);

        if (GetAnimator()->GetCurAnimation()->GetFinish())
        {
            this->Set_Dead();
            ChangeScene(SCENE_TYPE::BOSS_PAGE2);
            return OBJ_DEAD;
        }
    }


    if (m_fCreateBodyDelay <= 0.f)
    {
        if (m_pBody)                // 바디에서 스스로 삭제하면 이 문장 필요없는데 착각한듯? 일단냅둠 
        {
            m_pBody->Set_Dead();
            m_pBody = nullptr;
        }
            

        if (!m_pBody)
        {
            CBody* pBody = new CBody;
            pBody->Initialize(Vec2( float(rand() % WINCX), 350.f));
            CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS, pBody);
            m_pBody = pBody;
        }

        m_fCreateBodyDelay = 4.f;
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
    m_fCreateBodyDelay -= fDT;


    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CWill_Page1::Late_Update()
{
	if (m_bDeadAniPlay)
	{
		GetAnimator()->Update();
		return;
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
        default:
            break;
        }
    }







    float pY = 0.f;
    m_bLineCol = CLineMgr::Get_Instance()->Collision_LineMonster(this, m_tInfo.fX, m_tInfo.fY, &pY, &m_fTargetX);

    if (m_fAttackDelay <= 0.f)
    {         
        if (m_fSkillDelay <= 0.f)
            StartSkill();
        else
            StartAttack();          
    }


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
                GetAnimator()->Play(L"boss_walk_left", true);
                break;
            case MONSTER_DIR::RIGHT:             
                GetAnimator()->Play(L"boss_walk_right", true);
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
                GetAnimator()->Play(L"boss_walk_right", true);
            }
            else if (!m_bAttacking && m_fTargetX < m_tInfo.fX)
            {
                m_tInfo.fX -= m_fSpeed * fDT;

                m_eDir = MONSTER_DIR::LEFT;
                GetAnimator()->Play(L"boss_walk_left", true);
            }
        }

    }


    
    
    

	GetAnimator()->Update();
}

void CWill_Page1::Render(HDC hDC)
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
    //
    //
    //
    //SelectGDI p1(hDC, PEN_TYPE::RED);
    //SelectGDI b1(hDC, BRUSH_TYPE::HOLLOW);
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //if(m_bAttacking)
    //{
    //    Vec2 vPos1 = CCamera::CreateSingleTonInst()->GetRenderPos(Vec2(m_vAttack1RangePos));
    //
    //    Rectangle(hDC
    //        , (int)(vPos1.x - m_vAttack1RangeSize.x / 2.f)
    //        , (int)(vPos1.y - m_vAttack1RangeSize.y / 2.f)
    //        , (int)(vPos1.x + m_vAttack1RangeSize.x / 2.f)
    //        , (int)(vPos1.y + m_vAttack1RangeSize.y / 2.f));
    //}

}

void CWill_Page1::Release()
{
}

void CWill_Page1::StartAttack()
{  
    if (!m_bAttacking)
    {
        m_eAttackType = WILL_ATTACK_TYPE::ATTACK1;
        m_bAttacking = true;

        switch (m_eDir)
        {
        case MONSTER_DIR::LEFT:     
            m_vAttack1RangePos = Vec2(m_tInfo.fX - m_vAttack1RangeSize.x / 2.f, m_tInfo.fY);
            GetAnimator()->Play(L"boss_attack_left", false);
            break;
        case MONSTER_DIR::RIGHT:
            m_vAttack1RangePos = Vec2(m_tInfo.fX + m_vAttack1RangeSize.x / 2.f, m_tInfo.fY);
            GetAnimator()->Play(L"boss_attack_right", false);
            break;
        default:
            break;
        }
    }
  
}


void CWill_Page1::StartSkill()
{
    if (!m_bAttacking)
    {
        m_eAttackType = WILL_ATTACK_TYPE::SKILL;

        m_bSkillUsing = true;
        m_bAttacking = true;

        switch (m_eDir)
        {
        case MONSTER_DIR::LEFT:
        {
            m_vAttack3RangePos = Vec2(m_tInfo.fX, m_tInfo.fY);
            GetAnimator()->Play(L"boss_attack3_left", false);

            if (!m_pBall)
            {
                CBall* pBall = new CBall;
                pBall->Initialize(this->GetPos(), m_eDir, m_ePage);
                CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS_SKILL, pBall);
            }         
        }
           
            break;
        case MONSTER_DIR::RIGHT:
        {
            m_vAttack3RangePos = Vec2(m_tInfo.fX, m_tInfo.fY);
            GetAnimator()->Play(L"boss_attack3_right", false);

            if (!m_pBall)
            {
                CBall* pBall = new CBall;
                pBall->Initialize(this->GetPos(), m_eDir, m_ePage);
                CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS_SKILL, pBall);
            }
        }
            
            break;
        default:
            break;
        }
    }

}
