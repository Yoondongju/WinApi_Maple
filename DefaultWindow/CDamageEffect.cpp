#include "stdafx.h"
#include "CDamageEffect.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CTimeMgr.h"
#include "CCamera.h"
#include "ObjMgr.h"

#include "Player.h"

CDamageEffect::CDamageEffect()
    : m_fParticleDelay(0.f)
{
    m_iDamage = 19991109;

    m_vCreatePos = Vec2(0.f, 0.f);
    m_vOffset = Vec2(0.f, -120.f);
    m_fDeleteDelay = 1.f;
    m_byte = 255;


    m_iCount = 10000000;
}

CDamageEffect::~CDamageEffect()
{
}

void CDamageEffect::Initialize()
{
    m_eEffectType = ((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->GetDamageEffect();

    m_tInfo = { 0.f,0.f,50.f,50.f };        // 위치는 몬스터의 대가리 위에서 나오고 업데이트에서 갱신 되야함

    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::ZERO, CResMgr::CreateSingleTonInst()->LoadTexture(L"0", L"../API/Damage/NoCri0.0.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::ONE, CResMgr::CreateSingleTonInst()->LoadTexture(L"1", L"../API/Damage/NoCri0.1.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::TWO, CResMgr::CreateSingleTonInst()->LoadTexture(L"2", L"../API/Damage/NoCri0.2.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::THREE, CResMgr::CreateSingleTonInst()->LoadTexture(L"3", L"../API/Damage/NoCri0.3.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::FOUR, CResMgr::CreateSingleTonInst()->LoadTexture(L"4", L"../API/Damage/NoCri0.4.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::FIVE, CResMgr::CreateSingleTonInst()->LoadTexture(L"5", L"../API/Damage/NoCri0.5.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::SIX, CResMgr::CreateSingleTonInst()->LoadTexture(L"6", L"../API/Damage/NoCri0.6.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::SEVEN, CResMgr::CreateSingleTonInst()->LoadTexture(L"7", L"../API/Damage/NoCri0.7.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::EIGHT, CResMgr::CreateSingleTonInst()->LoadTexture(L"8", L"../API/Damage/NoCri0.8.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::NINE, CResMgr::CreateSingleTonInst()->LoadTexture(L"9", L"../API/Damage/NoCri0.9.png")));

}

int CDamageEffect::Update()
{
    if (m_bDead)
        return OBJ_DEAD;


    m_byte -= 2.2f * fDT;

    BLENDFUNCTION bf = GetBf();
    bf.SourceConstantAlpha = m_byte;

    SetBf(bf);
    

    if (DamageEffectType::NONE == m_eEffectType)
    {
        Set_Pos(m_vCreatePos.x + m_vOffset.x, m_vCreatePos.y + m_vOffset.y);
    }
    else if (DamageEffectType::VOLCANO == m_eEffectType)
    {
        Set_Pos(m_vCreatePos.x + m_vOffset.x, m_vCreatePos.y + m_vOffset.y);

        m_tInfo.fCX = 100 * m_fDeleteDelay;
        m_tInfo.fCY = 100 * m_fDeleteDelay;
    }
    else if (DamageEffectType::PATICLE == m_eEffectType)
    {
        // 위치 생성되는 위치 바뀌어야함
        // 업데이트 돌면서 갱신되는 위치도 바뀌어야함
        Set_Pos(m_vCreatePos.x + m_vOffset.x, m_vCreatePos.y + m_vOffset.y);

        m_tInfo.fY -= (15 * m_fParticleDelay - ((9.8f * m_fParticleDelay * m_fParticleDelay) * 0.5));
        m_fParticleDelay += 0.1f;

      
        m_tInfo.fCY = 100 * m_fDeleteDelay;
        m_tInfo.fCX = 100 * m_fDeleteDelay;
    }
    


    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CDamageEffect::Late_Update()
{
    if (m_fDeleteDelay <= 0.f)
    {
        this->Set_Dead();
        return;
    }

    m_fDeleteDelay -= fDT;
}

void CDamageEffect::Render(HDC hDC)
{

    for (size_t i = 1; i < 9; ++i)
    {
        if (m_iDamage == 0)
        {
            m_iDamage = 19991109;
            m_iCount = 10000000;
        }


        int iNum = m_iDamage / m_iCount;

        m_iDamage %= m_iCount;
        m_iCount /= 10;

        CTexture* pTex = nullptr;

        switch ((DAMEGE_NUM)iNum)
        {
        case DAMEGE_NUM::ZERO:
            pTex = m_vecDamageTex[(UINT)DAMEGE_NUM::ZERO].second;
            break;
        case DAMEGE_NUM::ONE:
            pTex = m_vecDamageTex[(UINT)DAMEGE_NUM::ONE].second;
            break;
        case DAMEGE_NUM::TWO:
            pTex = m_vecDamageTex[(UINT)DAMEGE_NUM::TWO].second;
            break;
        case DAMEGE_NUM::THREE:
            pTex = m_vecDamageTex[(UINT)DAMEGE_NUM::THREE].second;
            break;
        case DAMEGE_NUM::FOUR:
            pTex = m_vecDamageTex[(UINT)DAMEGE_NUM::FOUR].second;
            break;
        case DAMEGE_NUM::FIVE:
            pTex = m_vecDamageTex[(UINT)DAMEGE_NUM::FIVE].second;
            break;
        case DAMEGE_NUM::SIX:
            pTex = m_vecDamageTex[(UINT)DAMEGE_NUM::SIX].second;
            break;
        case DAMEGE_NUM::SEVEN:
            pTex = m_vecDamageTex[(UINT)DAMEGE_NUM::SEVEN].second;
            break;
        case DAMEGE_NUM::EIGHT:
            pTex = m_vecDamageTex[(UINT)DAMEGE_NUM::EIGHT].second;
            break;
        case DAMEGE_NUM::NINE:
            pTex = m_vecDamageTex[(UINT)DAMEGE_NUM::NINE].second;
            break;

        default:
            break;
        }
       

        Vec2 vPos = CCamera::CreateSingleTonInst()->GetRenderPos(this->GetPos());


        AlphaBlend(hDC
            , vPos.x + (m_tInfo.fCX * i)	                        // ( 고정위치 )	// 이미지를 출력할 x
            , vPos.y					            // ( 고정위치 )  // 이미지를 출력할 y
            , m_tInfo.fCX					            // 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
            , m_tInfo.fCY
            , pTex->GetDC()
            , 0								            // 가져올 이미지의 시작위치
            , 0
            , pTex->Width() 			                // 잘라낼 크기니까 항상 800 이여야함
            , pTex->Height()
            , this->GetBf());


    }

}

void CDamageEffect::Release()
{
}
