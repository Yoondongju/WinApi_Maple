#include "stdafx.h"
#include "CHitDamageEffect.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CTimeMgr.h"
#include "CCamera.h"
#include "ObjMgr.h"

#include "Player.h"

CHitDamageEffect::CHitDamageEffect()
{
    m_iDamage = 1004;

    m_vCreatePos = Vec2(0.f, 0.f);
    m_vOffset = Vec2(0.f, -120.f);
    m_fDeleteDelay = 1.f;
    m_byte = 255;

   
    m_iCount = 1000;
}

CHitDamageEffect::~CHitDamageEffect()
{
}

void CHitDamageEffect::Initialize()
{
    m_eEffectType = DamageEffectType::NONE;

    m_tInfo = { 0.f,0.f,50.f,50.f };        // ��ġ�� ������ �밡�� ������ ������ ������Ʈ���� ���� �Ǿ���

    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::ZERO, CResMgr::CreateSingleTonInst()->LoadTexture(L"hit0", L"../API/Damage/NoViolet0.0.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::ONE, CResMgr::CreateSingleTonInst()->LoadTexture(L"hit1", L"../API/Damage/NoViolet0.1.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::TWO, CResMgr::CreateSingleTonInst()->LoadTexture(L"hit2", L"../API/Damage/NoViolet0.2.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::THREE, CResMgr::CreateSingleTonInst()->LoadTexture(L"hit3", L"../API/Damage/NoViolet0.3.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::FOUR, CResMgr::CreateSingleTonInst()->LoadTexture(L"hit4", L"../API/Damage/NoViolet0.4.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::FIVE, CResMgr::CreateSingleTonInst()->LoadTexture(L"hit5", L"../API/Damage/NoViolet0.5.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::SIX, CResMgr::CreateSingleTonInst()->LoadTexture(L"hit6", L"../API/Damage/NoViolet0.6.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::SEVEN, CResMgr::CreateSingleTonInst()->LoadTexture(L"hit7", L"../API/Damage/NoViolet0.7.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::EIGHT, CResMgr::CreateSingleTonInst()->LoadTexture(L"hit8", L"../API/Damage/NoViolet0.8.png")));
    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::NINE, CResMgr::CreateSingleTonInst()->LoadTexture(L"hit9", L"../API/Damage/NoViolet0.9.png")));

    m_vecDamageTex.push_back(make_pair(DAMEGE_NUM::MISS, CResMgr::CreateSingleTonInst()->LoadTexture(L"MISS", L"../API/Damage/NoViolet0.Miss.png")));


    m_tInfo.fX = m_vCreatePos.x;
    m_tInfo.fY = m_vCreatePos.y;
}

int CHitDamageEffect::Update()
{
    if (m_bDead)
        return OBJ_DEAD;


    m_byte -= 3.f * fDT;

    BLENDFUNCTION bf = GetBf();
    bf.SourceConstantAlpha = m_byte;

    SetBf(bf);


    if (DamageEffectType::NONE == m_eEffectType)
    {
        m_tInfo.fY -= (3.f * fDT);
    }

    //else if (DamageEffectType::VOLCANO == m_eEffectType)
    //{
    //    Set_Pos(m_vCreatePos.x + m_vOffset.x, m_vCreatePos.y + m_vOffset.y);
    //
    //    m_tInfo.fCX = 100 * m_fDeleteDelay;
    //    m_tInfo.fCY = 100 * m_fDeleteDelay;
    //}
    //else if (DamageEffectType::PATICLE == m_eEffectType)
    //{
    //    // ��ġ �����Ǵ� ��ġ �ٲ�����
    //    // ������Ʈ ���鼭 ���ŵǴ� ��ġ�� �ٲ�����
    //    Set_Pos(m_vCreatePos.x + m_vOffset.x, m_vCreatePos.y + m_vOffset.y);
    //
    //    m_tInfo.fY -= (15 * m_fParticleDelay - ((9.8f * m_fParticleDelay * m_fParticleDelay) * 0.5));
    //    m_fParticleDelay += 0.1f;
    //
    //
    //    m_tInfo.fCY = 100 * m_fDeleteDelay;
    //    m_tInfo.fCX = 100 * m_fDeleteDelay;
    //}



    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CHitDamageEffect::Late_Update()
{
    if (m_fDeleteDelay <= 0.f)
    {
        ((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->m_pHitEffect = nullptr;   
        this->Set_Dead();
        return;
    }

    m_fDeleteDelay -= fDT;
}

void CHitDamageEffect::Render(HDC hDC)
{
    if (m_iDamage == -1)
    {
        CTexture* pTex = nullptr;
        pTex = m_vecDamageTex[(UINT)DAMEGE_NUM::MISS].second;

        Vec2 vPos = CCamera::CreateSingleTonInst()->GetRenderPos(this->GetPos());


        AlphaBlend(hDC
            , vPos.x 	                        // ( ������ġ )	// �̹����� ����� x
            , vPos.y					            // ( ������ġ )  // �̹����� ����� y
            , m_tInfo.fCX					            // ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
            , m_tInfo.fCY
            , pTex->GetDC()
            , 0								            // ������ �̹����� ������ġ
            , 0
            , pTex->Width() 			                // �߶� ũ��ϱ� �׻� 800 �̿�����
            , pTex->Height()
            , this->GetBf());

        return;
    }

    for (size_t i = 1; i < 5; ++i)
    {
        if (m_iDamage == 0)
        {
            m_iDamage = 1004;
            m_iCount = 1000;
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
            , vPos.x + (m_tInfo.fCX * i)	                        // ( ������ġ )	// �̹����� ����� x
            , vPos.y					            // ( ������ġ )  // �̹����� ����� y
            , m_tInfo.fCX					            // ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
            , m_tInfo.fCY
            , pTex->GetDC()
            , 0								            // ������ �̹����� ������ġ
            , 0
            , pTex->Width() 			                // �߶� ũ��ϱ� �׻� 800 �̿�����
            , pTex->Height()
            , this->GetBf());


    }

}

void CHitDamageEffect::Release()
{
}
