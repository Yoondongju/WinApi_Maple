#include "stdafx.h"
#include "CExecutor.h"

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
#include <ctime>

CExecutor::CExecutor()
{
    srand(time(NULL));

    CreateAnimator();
}

CExecutor::~CExecutor()
{
}

void CExecutor::Initialize(Vec2 _vPos)
{
    m_tInfo = { _vPos.x ,_vPos.y ,170.f,181.f };
    m_eObjType = OBJID::OBJ_MONSTER;
    m_fSpeed = 100.f;

    m_iDropMoney = 1000;

    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"monster2_stand_left", L"../API/Monster2/stand/stand_left.png");
    GetAnimator()->CreateAnimation(L"monster2_stand_left", pTex, Vec2(0.f, 0.f), Vec2(161.f, 181.f), Vec2(161.f, 0.f), 0.3, 8);

    CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"monster2_stand_right", L"../API/Monster2/stand/stand_right.png");
    GetAnimator()->CreateAnimation(L"monster2_stand_right", pTex1, Vec2(0.f, 0.f), Vec2(161.f, 181.f), Vec2(161.f, 0.f), 0.3, 8);

   


    CTexture* pTex2 = CResMgr::CreateSingleTonInst()->LoadTexture(L"monster2_walk_left", L"../API/Monster2/move/walk_left.png");
    GetAnimator()->CreateAnimation(L"monster2_walk_left", pTex2, Vec2(0.f, 0.f), Vec2(169.f, 171.f), Vec2(169.f, 0.f), 0.1, 8);

    CTexture* pTex3 = CResMgr::CreateSingleTonInst()->LoadTexture(L"monster2_walk_right", L"../API/Monster2/move/walk_right.png");
    GetAnimator()->CreateAnimation(L"monster2_walk_right", pTex3, Vec2(0.f, 0.f), Vec2(169.f, 171.f), Vec2(169.f, 0.f), 0.1, 8);




    CTexture* pTex6 = CResMgr::CreateSingleTonInst()->LoadTexture(L"monster2_die", L"../API/Monster2/die/die.png");
    GetAnimator()->CreateAnimation(L"monster2_die", pTex6, Vec2(0.f, 0.f), Vec2(192.4f, 215.f), Vec2(192.4f, 0.f), 0.15f, 17);

    GetAnimator()->Play(L"monster2_stand_left", true);

}

int CExecutor::Update()
{
    if (m_bDeadAniPlay)
    {
        GetAnimator()->Play(L"monster2_die", false);

        if (GetAnimator()->GetCurAnimation()->GetFinish())
        {
            CExecutor* pClone = new CExecutor();
            pClone->Initialize(this->GetPos());
            CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MONSTER, pClone);


            CMoney* pMoney = new CMoney;
            pMoney->Initialize(GetPos(), 100);
            CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MESO, pMoney);

            m_pCollisonObj = nullptr;
            this->Set_Dead();
            return OBJ_DEAD;
        }
    }




    if (m_bDeadAniPlay)
    {
        if (m_iDamageCount != -999)
        {
            CPlayerSkill* pSkill = static_cast<CPlayerSkill*>(m_pCollisonObj);

            int iAttackCount = static_cast<CPlayerSkill*>(m_pCollisonObj)->GetAttackCount();

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
                m_iDamageCount = -999;
                m_fDamageCreateDelay = 0.08f;
               
            }
        }

    }


   



    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CExecutor::Late_Update()
{
    if (m_bDeadAniPlay)
    {
        GetAnimator()->Update();
        return;
    }


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


        if (5 > abs(m_fTargetX - m_tInfo.fX))
        {
            m_bArrival = true;
            m_fMoveDelay -= fDT;

            switch (m_eDir)
            {
            case MONSTER_DIR::LEFT:
                GetAnimator()->Play(L"monster2_stand_left", true);
                break;
            case MONSTER_DIR::RIGHT:
                GetAnimator()->Play(L"monster2_stand_right", true);
                break;
            default:
                break;
            }

        }
        else
        {
            m_bArrival = false;

            if (m_fTargetX > m_tInfo.fX)
            {
                m_tInfo.fX += m_fSpeed * fDT;

                m_eDir = MONSTER_DIR::RIGHT;
                GetAnimator()->Play(L"monster2_walk_right", true);
            }
            else if (m_fTargetX < m_tInfo.fX)
            {
                m_tInfo.fX -= m_fSpeed * fDT;

                m_eDir = MONSTER_DIR::LEFT;
                GetAnimator()->Play(L"monster2_walk_left", true);
            }
        }

    }



    GetAnimator()->Update();
}

void CExecutor::Render(HDC hDC)
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

void CExecutor::Release()
{
}