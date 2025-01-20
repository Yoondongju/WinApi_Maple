#include "stdafx.h"
#include "Player.h"

#include "AbstractFactory.h"

#include "ObjMgr.h"

#include "LineMgr.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"


#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CUIMgr.h"

#include "CResMgr.h"

#include "CCamera.h"

#include "CPlayerUI.h"
#include "CQuickSlotUI.h"
#include "CStatUI.h"
#include "CSkillUI.h"
#include "CInventoryUI.h"


#include "CWarriorLeap.h"
#include "CUpperCharge.h"
#include "CRush.h"
#include "CDeathfault.h"
#include "COrablade.h"
#include "CRagingblow.h"


#include "SelectGDI.h"

#include "CNpc.h"
#include "CConversationUI.h"
#include "CStoreUI.h"

#include "CEquipUI.h"
#include "CPet.h"

#include "CPotal.h"

#include "CEffect.h"
#include "CDieUI.h"
#include "CStone.h"

#include "CSixSkill.h"

#include "CSound.h"
#include "CQuest.h"

#include "CDamageEffectUI.h"


CPlayer::CPlayer()
	: m_fDistance(0.f), m_bJump(false), m_bDownJump(false), m_fTime(0.f), m_fPower(0.f), m_bRope(false)
	, m_bLineride(false)
	, m_PreState(PLAYER_STATE::STATE_END)
	, m_CurState(PLAYER_STATE::IDLE)
	, m_bCameraCheck(true)
	, m_pStatUI(nullptr)
	, m_fMaxHp(100)
	, m_fHp(50)
	, m_fMaxMp(100)
	, m_fMp(50)
	, m_fAttackInfo(1000.f)
	, m_iAbilityPoint(5)
	, m_iSTR(4)
	, m_iDEX(4)
	, m_iINT(4)
	, m_iLUK(4)
	, m_iSkillPoint(6)
	, m_vJumpTargetPos(0.f, 0.f)
	, m_iJumpCount(2)
	, m_bLand(false)
	, m_eDir(PLAYER_DIR::RIGHT)
	, m_bCastingskill(false)
	, m_fTargetLinefY(0.f)
	, m_pInventory(nullptr)
	, m_pEquipUI(nullptr)
	, m_iMeso(100)
	, m_pStoreUI(nullptr)
	, m_pConversationUI(nullptr)
	, m_pPet(nullptr)
	, m_iMaxExp(60)
	, m_iExp(0)
	, m_fHitDelay(1.5)
	, m_bFakeDead(false)
	, m_bCollision(false)
	, m_bFirstCollision(false)
	, m_Alphabyte(255)
	, m_pDieUI(nullptr)
	, m_pQuest(nullptr)
	, m_eDamgeEffectType(DamageEffectType::NONE)
	, m_pDamageEffectUI(nullptr)
	, m_iLevel(1)
	, m_pHitEffect(nullptr)
{
	for (int i = 0; i < SKILL_TYPE::SKILL_END; ++i) 
		m_tSkill[i] = nullptr;

	for (int i = 0; i < (UINT)ITEM_TYPE::ITEM_END; ++i)
		m_pItem[i] = nullptr;
	
	

	m_eObjType = OBJID::OBJ_PLAYER;
	CreateAnimator();					// 항상 애니메이터 만들기전에 ObjType 정해줘야함!!!!!!!!!!1
	

	CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_stand_left", L"../API/Player/stand/player_stand_left.png");
	GetAnimator()->CreateAnimation(L"player_stand_left", pTex, Vec2(0.f, 0.f), Vec2(92.f, 96.f), Vec2(92.f, 0.f), 0.5f, 3);

	CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_stand_right", L"../API/Player/stand/player_stand_right.png");
	GetAnimator()->CreateAnimation(L"player_stand_right", pTex1, Vec2(0.f, 0.f), Vec2(92.f, 96.f), Vec2(92.f, 0.f), 0.5f, 3);

	CTexture* pTex2 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_walk_left", L"../API/Player/walk/player_walk_left.png");
	GetAnimator()->CreateAnimation(L"player_walk_left", pTex2, Vec2(0.f, 0.f), Vec2(92.f, 96.f), Vec2(92.f, 0.f), 0.1f, 4);

	CTexture* pTex3 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_walk_right", L"../API/Player/walk/player_walk_right.png");
	GetAnimator()->CreateAnimation(L"player_walk_right", pTex3, Vec2(0.f, 0.f), Vec2(92.f, 96.f), Vec2(92.f, 0.f), 0.1f, 4);


	CTexture* pTex4 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_jump_left", L"../API/Player/jump/player_jump_left.png");
	GetAnimator()->CreateAnimation(L"player_jump_left", pTex4, Vec2(0.f, 0.f), Vec2(92.f, 96.f), Vec2(92.f, 0.f), 0.1f, 1);

	CTexture* pTex5 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_jump_right", L"../API/Player/jump/player_jump_right.png");
	GetAnimator()->CreateAnimation(L"player_jump_right", pTex5, Vec2(0.f, 0.f), Vec2(92.f, 96.f), Vec2(92.f, 0.f), 0.1f, 1);

	CTexture* pTex6 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_rope_nomove", L"../API/Player/rope/rope_nomove.png");
	GetAnimator()->CreateAnimation(L"player_rope_nomove", pTex6, Vec2(0.f, 0.f), Vec2(92.f, 96.f), Vec2(0.f, 0.f), 0.1f, 1);

	CTexture* pTex7 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_rope_move", L"../API/Player/rope/rope_move.png");
	GetAnimator()->CreateAnimation(L"player_rope_move", pTex7, Vec2(0.f, 0.f), Vec2(92.f, 96.f), Vec2(92.f, 0.f), 0.2f, 2);



	CTexture* pTex8 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_dead_left", L"../API/Player/dead/player_dead_left.png");
	GetAnimator()->CreateAnimation(L"player_dead_left", pTex8, Vec2(0.f, 0.f), Vec2(52.f, 76.f), Vec2(0.f, 0.f), 0.2f, 1);


	CTexture* pTex9 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_dead_right", L"../API/Player/dead/player_dead_right.png");
	GetAnimator()->CreateAnimation(L"player_dead_right", pTex9, Vec2(0.f, 0.f), Vec2(52.f, 76.f), Vec2(0.f, 0.f), 0.2f, 1);



	CTexture* pTex10 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_deathfault_left", L"../API/Player/deathfault/test_left.png");
	GetAnimator()->CreateAnimation(L"player_deathfault_left", pTex10, Vec2(0.f, 0.f), Vec2(256.f, 134.f), Vec2(0.f, 134.f), 0.76f, 2);

	CTexture* pTex11 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_deathfault_right", L"../API/Player/deathfault/test_right.png");
	GetAnimator()->CreateAnimation(L"player_deathfault_right", pTex11, Vec2(0.f, 0.f), Vec2(256.f, 134.f), Vec2(0.f, 134.f), 0.76f, 2);




	CTexture* pTex12 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_orablade_left", L"../API/Player/orablade/left.png");
	GetAnimator()->CreateAnimation(L"player_orablade_left", pTex12, Vec2(0.f, 0.f), Vec2(92.f, 96.f), Vec2(0.f, 96.f), 0.05f, 10);

	CTexture* pTex13 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_orablade_right", L"../API/Player/orablade/right.png");
	GetAnimator()->CreateAnimation(L"player_orablade_right", pTex13, Vec2(0.f, 0.f), Vec2(92.f, 96.f), Vec2(0.f, 96.f), 0.05f, 10);



	CTexture* pTex18 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_rush_left", L"../API/Player/rush/left.png");
	GetAnimator()->CreateAnimation(L"player_rush_left", pTex18, Vec2(0.f, 0.f), Vec2(165.f, 74.f), Vec2(165.f, 0.f), 0.05f, 7);

	CTexture* pTex19 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_rush_right", L"../API/Player/rush/right.png");
	GetAnimator()->CreateAnimation(L"player_rush_right", pTex19, Vec2(0.f, 0.f), Vec2(165.f, 74.f), Vec2(165.f, 0.f), 0.05f, 7);




	CTexture* pTex17 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_upperchage_left", L"../API/Player/upperchage/left.png");
	GetAnimator()->CreateAnimation(L"player_upperchage_left", pTex17, Vec2(0.f, 0.f), Vec2(52.f, 86.2f), Vec2(0.f, 86.2f), 0.09f, 9);

	CTexture* pTex14 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_upperchage_right", L"../API/Player/upperchage/right.png");
	GetAnimator()->CreateAnimation(L"player_upperchage_right", pTex14, Vec2(0.f, 0.f), Vec2(52.f, 86.2f), Vec2(0.f, 86.2f), 0.09f, 9);



	CTexture* pTex15 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_ragingblow_left", L"../API/Player/ragingblow/test_left.png");
	GetAnimator()->CreateAnimation(L"player_ragingblow_left", pTex15, Vec2(0.f, 0.f), Vec2(256.f, 141.f), Vec2(0.f, 141.f), 0.0545f, 11);

	CTexture* pTex16 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_ragingblow_right", L"../API/Player/ragingblow/test_right.png");
	GetAnimator()->CreateAnimation(L"player_ragingblow_right", pTex16, Vec2(0.f, 0.f), Vec2(256.f, 141.f), Vec2(0.f, 141.f), 0.0545f, 11);



	GetAnimator()->Play(L"player_stand_right",true);
}


CPlayer::~CPlayer()
{
	Release();
	m_pPet = nullptr;
}

void CPlayer::Initialize()
{
	m_tInfo		= { 2000.f, WINCY - 200.f , 90.f , 90.f};
	m_fSpeed	= 0.9f;
	m_fDistance = 100.f;
	m_fPower = 7.f;
	m_vPrePos = Vec2(m_tInfo.fX,m_tInfo.fY);
	
	m_fAngle = 0.f;
	m_eObjType = OBJID::OBJ_PLAYER;




}



void CPlayer::Late_InitPlayerObj()
{
	CPlayerUI* pUI = new CPlayerUI;
	pUI->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pUI);				// hp,mp,exp 바 UI

	
	CQuickSlotUI* pQuickUI = new CQuickSlotUI;
	pQuickUI->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pQuickUI);			// 퀵 슬롯 바 UI
	m_pQuickslotUI = pQuickUI;

	CStatUI* pStatUI = new CStatUI;
	pStatUI->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pStatUI);			// Stat창 UI
	m_pStatUI = pStatUI;


	CSkillUI* pSkillUI = new CSkillUI;
	pSkillUI->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pSkillUI);			// Skill창 UI
	m_pSkillUI = pSkillUI;


	CInventoryUI* pInventoryUI = new CInventoryUI;
	pInventoryUI->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pInventoryUI);			// Skill창 UI
	m_pInventory = pInventoryUI;

	CEquipUI* pEquipUI = new CEquipUI;
	pEquipUI->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pEquipUI);			// Skill창 UI
	m_pEquipUI = pEquipUI;

	
	CStoreUI* pStoreUI = new CStoreUI;
	pStoreUI->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pStoreUI);
	m_pStoreUI = pStoreUI;


	CDamageEffectUI* pDamageEffectUI = new CDamageEffectUI;
	pDamageEffectUI->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pDamageEffectUI);
	m_pDamageEffectUI = pDamageEffectUI;


	m_tSkill[SKILL_TYPE::SIX] = new CSixSkill;
	m_tSkill[SKILL_TYPE::SIX]->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PLAYER_SKILL, m_tSkill[SKILL_TYPE::SIX]);

}

int CPlayer::Update()
{
	if(!m_bCastingskill)
		m_CurState = PLAYER_STATE::IDLE;


	if (m_bDead)
		return OBJ_DEAD;

	if (m_bFirstCollision && !m_bFakeDead)
	{
		m_fHitDelay -= fDT;

		if (m_Alphabyte == 255)
			m_Alphabyte = 150;
		else if (m_Alphabyte == 0)
			m_Alphabyte = 255;

		BLENDFUNCTION bf = GetBf();
		bf.SourceConstantAlpha = m_Alphabyte;		// 피격당한후 딜레이동안 무적 상태를 나타냄 

		SetBf(bf);

		if (m_fHitDelay <= 0.f)
		{ 
			m_fHitDelay = 1.5f;
			m_bFirstCollision = false;
		}			
	}
	else
	{
		BLENDFUNCTION bf = GetBf();
		bf.SourceConstantAlpha = 255;
		SetBf(bf);
	}
		


	if (m_bFakeDead)
		FakeDead();


	if (m_iExp >= m_iMaxExp)
	{
		if (m_iLevel != 9)
		{
			CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"levelup");
			pNewSound1->Play(false);
			pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
			pNewSound1->SetVolume(100.f); // 소리 볼륨 크기


			CEffect* pEff = new CEffect;
			pEff->Initialize();
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_EFFECT, pEff);

			m_iExp = 0;
			++m_iLevel;
			m_iAbilityPoint += 5;
		}
			
	}


	

	if(m_bCameraCheck)
	{ 
		if(m_tSkill[DEATHFAULT]!= nullptr && m_tSkill[DEATHFAULT]->GetSkillActivate())
			CCamera::CreateSingleTonInst()->SetTarget(nullptr);
		else
			CCamera::CreateSingleTonInst()->SetTarget(this);
	}	
	else
		CCamera::CreateSingleTonInst()->SetTarget(nullptr);

	


	

	float fY(0);
	if (m_PreState == PLAYER_STATE::ROPE_NOMOVE)
	{
		m_CurState = PLAYER_STATE::ROPE_NOMOVE;
	}

	Key_Input();
	

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{				
	if (!m_bRope)
	{
		Jump();

		m_PreState = PLAYER_STATE::STATE_END;
	}
		

	if (m_eDir == PLAYER_DIR::RIGHT)	// 오른쪽방향
	{
		switch (m_CurState)
		{
		case PLAYER_STATE::IDLE:
			GetAnimator()->Play(L"player_stand_right", true);
			break;
		case PLAYER_STATE::WALK:
			GetAnimator()->Play(L"player_walk_right", true);
			break;
		case PLAYER_STATE::DEATHFAULT:
		{
			
			GetAnimator()->Play(L"player_deathfault_right", true);
		}				
			break;
		case PLAYER_STATE::ORABLADE:
		{
			
			GetAnimator()->Play(L"player_orablade_right", true);
		}
			break;

		case PLAYER_STATE::RUSH:
		{

			GetAnimator()->Play(L"player_rush_right", true);
		}
			break;

		case PLAYER_STATE::UPPERCHAGE:
		{
			
			GetAnimator()->Play(L"player_upperchage_right", true);
		}	
			break;

		case PLAYER_STATE::RAGINGBLOW:
		{
			
			GetAnimator()->Play(L"player_ragingblow_right", true);
		}		
			break;

		case PLAYER_STATE::SIX:
		{

			GetAnimator()->Play(L"player_stand_right", true);
		}
		break;

		case PLAYER_STATE::DEAD:
		{
			
			GetAnimator()->Play(L"player_dead_right", true);
		}
			break;
		case PLAYER_STATE::JUMP:
		{
			CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"player_jump");
			pNewSound->Play(false);
			pNewSound->SetPosition(1.f); // 백분률 , 소리위치
			pNewSound->SetVolume(50.f); // 소리 볼륨 크기
			GetAnimator()->Play(L"player_jump_right", true);
		}
			break;
		case PLAYER_STATE::ROPE_NOMOVE:
			GetAnimator()->Play(L"player_rope_nomove", true);
			break;
		case PLAYER_STATE::ROPE_MOVE:
			GetAnimator()->Play(L"player_rope_move", true);
			break;
		case PLAYER_STATE::STATE_END:
			break;
		default:
			break;
		}
	}
	else if(m_eDir == PLAYER_DIR::LEFT)  // 왼쪽
	{
		switch (m_CurState)
		{
		case PLAYER_STATE::IDLE:
			GetAnimator()->Play(L"player_stand_left", true);
			break;
		case PLAYER_STATE::WALK:
			GetAnimator()->Play(L"player_walk_left", true);
			break;

		case PLAYER_STATE::DEATHFAULT:
		{

			GetAnimator()->Play(L"player_deathfault_left", true);
		}
			break;

		case PLAYER_STATE::ORABLADE:
		{

	
			GetAnimator()->Play(L"player_orablade_left", true);
		}
			break;

		case PLAYER_STATE::RUSH:
		{

			GetAnimator()->Play(L"player_rush_left", true);
		}
		break;

		case PLAYER_STATE::UPPERCHAGE:
		{
			
			GetAnimator()->Play(L"player_upperchage_left", true);
		}
			break;

		case PLAYER_STATE::RAGINGBLOW:
		{
			
			GetAnimator()->Play(L"player_ragingblow_left", true);
		}
			break;

		case PLAYER_STATE::SIX:
		{

			GetAnimator()->Play(L"player_stand_left", true);
		}
		break;

		case PLAYER_STATE::DEAD:
		{

			GetAnimator()->Play(L"player_dead_left", true);
		}
			break;
		case PLAYER_STATE::JUMP:
		{
			CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"player_jump");
			pNewSound->Play(false);
			pNewSound->SetPosition(1.f); // 백분률 , 소리위치
			pNewSound->SetVolume(50.f); // 소리 볼륨 크기
			GetAnimator()->Play(L"player_jump_left", true);
		}
			break;
		case PLAYER_STATE::ROPE_NOMOVE:
			GetAnimator()->Play(L"player_rope_nomove", true);
			break;
		case PLAYER_STATE::ROPE_MOVE:
			GetAnimator()->Play(L"player_rope_move", true);
			break;
		case PLAYER_STATE::STATE_END:
			break;
		default:
			break;
		}
	}

	GetAnimator()->Update();
}

void CPlayer::Render(HDC hDC)
{	
	GetAnimator()->GetCurAnimation()->Render(hDC);


	//SelectGDI p(hDC, PEN_TYPE::GREEN);
	//SelectGDI b(hDC, BRUSH_TYPE::HOLLOW);
	//
	//
	//
	//Vec2 vPos = CCamera::CreateSingleTonInst()->GetRenderPos(Vec2(m_tInfo.fX, m_tInfo.fY));
	//
	//Rectangle(hDC
	//	, (int)(vPos.x - m_tInfo.fCX / 2.f)
	//	, (int)(vPos.y - m_tInfo.fCY / 2.f)
	//	, (int)(vPos.x + m_tInfo.fCX / 2.f)
	//	, (int)(vPos.y + m_tInfo.fCY / 2.f));

}

void CPlayer::Release()
{
	
}

void CPlayer::Wall_Check()
{
	//float f_deltaX(0.f);
	//float f_deltaY(0.f);
	//
	//float m_f_Recently_FX = m_tInfo.fX;
	//float m_f_Recently_FY = m_tInfo.fY;
	////float m_f_Recently_FX_left = m_tInfo.fX - m_tInfo.fCX * 0.5f;
	////float m_f_Recently_FX_right = m_tInfo.fX + m_tInfo.fCX * 0.5f;
	//
	//
	//bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line_WALL(m_f_Recently_FX, m_f_Recently_FY, &f_deltaX, &f_deltaY);  //여기서 fx,fY update
	//
	//
	//
	//if (bLineCol) //충돌했으면 플레이어의 X축좌표  
	//{
	//	m_tInfo.fX = f_deltaX;
	//	if (m_f_Recently_FX <= f_deltaX)  
	//	{
	//		m_tInfo.fX = f_deltaX - m_tInfo.fCX * 0.5f;
	//		m_tInfo.fX = f_deltaX - m_tInfo.fCX * 2.f;
	//	}
	//	else
	//	{
	//		m_tInfo.fX = f_deltaX + m_tInfo.fCX * 0.5f;
	//	}
	//}
}

void CPlayer::QuestCheck()
{

}


void CPlayer::SetCreateSkill(SKILL_TYPE _e)
{
	if (nullptr == m_tSkill[_e])
	{	
		switch (_e)
		{
		case DEATHFAULT:
			m_tSkill[_e] = new CDeathfault;
			m_tSkill[_e]->Initialize();
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PLAYER_SKILL, m_tSkill[_e]);
			break;
		case ORABLADE:
			m_tSkill[_e] = new COrablade;
			m_tSkill[_e]->Initialize();
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PLAYER_SKILL, m_tSkill[_e]);
			break;
		case RAGINGBLOW:
			m_tSkill[_e] = new CRagingblow;
			m_tSkill[_e]->Initialize();
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PLAYER_SKILL, m_tSkill[_e]);
			break;
		case RUSH:
			m_tSkill[_e] = new CRush;
			m_tSkill[_e]->Initialize();
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PLAYER_SKILL, m_tSkill[_e]);
			break;
		case UPPERCHARGE:
			m_tSkill[_e] = new CUpperCharge;
			m_tSkill[_e]->Initialize();
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PLAYER_SKILL, m_tSkill[_e]);
			break;
		case WARRIORLEAP:
			m_tSkill[_e] = new CWarriorLeap;
			m_tSkill[_e]->Initialize();
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PLAYER_SKILL, m_tSkill[_e]);
			break;
		case SKILL_END:
			break;
		default:
			break;
		}
	}
}




void CPlayer::CheckPotal()
{
	CScene* pCurscene = CSceneMgr::CreateSingleTonInst()->GetCurScene();
	vector<CPotal*>& vecPotal = pCurscene->GetCurScenePotalvec();

	for (auto& iter : vecPotal)
	{
		RECT rt = iter->Get_Rect();

		float xPos = rt.left + (rt.right - rt.left) / 2.f;
		float yPos = rt.top+150 + (rt.bottom - rt.top) / 2.f;

		if (abs(xPos - m_tInfo.fX) < (rt.right - rt.left) / 2.f + m_tInfo.fCX / 2.f
			&& abs(yPos - m_tInfo.fY) < (rt.bottom - rt.top) / 2.f + m_tInfo.fCY / 2.f)
		{
			CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"Potal");
			pNewSound->Play(false);
			pNewSound->SetPosition(1.f); // 백분률 , 소리위치
			pNewSound->SetVolume(50.f); // 소리 볼륨 크기

			ChangeScene(iter->GetMoveSceneType());   // 전역함수 에서 이벤트 매니저에 등록
		}
		
	}

	

	

}


void CPlayer::CalculeAngle()
{
	
 
	
}


void CPlayer::Key_Input()
{
	CScene* pCurScene = CSceneMgr::CreateSingleTonInst()->GetCurScene();

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::ESC) == KEY_STATE::TAP)
	{
		CPlayerUI* pUI = CUIMgr::CreateSingleTonInst()->GetFocusUI();
		if (pUI)
		{
			switch (pUI->GetUI_Type())
			{
			case UI_TYPE::CONVERSATION:
			{
				pUI->SetActivate(false);
			}
				break;

			case UI_TYPE::STORE:
			{
				CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"ui_close");
				pNewSound1->Play(false);
				pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
				pNewSound1->SetVolume(100.f); // 소리 볼륨 크기

				pUI->SetActivate(false);
			}
				break;

			case UI_TYPE::NOGOLD:
			{
				CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"ui_close");
				pNewSound1->Play(false);
				pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
				pNewSound1->SetVolume(100.f); // 소리 볼륨 크기

				pUI->Set_Dead();
			}
				break;

			case UI_TYPE::DIE:
			{
				m_pDieUI = nullptr;
				pUI->Set_Dead();
				m_fHp = m_fMaxHp;
				m_fMp = m_fMaxMp;
				m_bFakeDead = false;
			}
			break;

			default:
				break;
			}
			
		}
	}

	if (m_bFakeDead)
		return;


	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
	{
		for (auto& iter : CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_NPC))
		{
			CNpc* pNpc = static_cast<CNpc*>(iter);

			if (pNpc->IsRecognize())		// NPC 종류에 따라 상호작용이 달라야함
			{
				switch (pNpc->GetNpcType())
				{
				case NPC_TYPE::TALK:
				{
					if (!m_pConversationUI)
					{
						CConversationUI* pUI = new CConversationUI;
						pUI->Initialize(NPC_TYPE::TALK);
						CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pUI);
						m_pConversationUI = pUI;
					}
					else
					{
						if (m_pQuest->IsSuccess())
						{
							CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"quest_success");
							pNewSound1->Play(false);
							pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
							pNewSound1->SetVolume(100.f); // 소리 볼륨 크기

							m_pConversationUI->SetActivate(true);
							((CConversationUI*)m_pConversationUI)->SetReText();
						}
							
					}
						
				}
					break;

				case NPC_TYPE::STORE:
				{
					if (m_pStoreUI->GetActivate() == false)
						m_pStoreUI->SetActivate(true);
					else
						m_pStoreUI->SetActivate(false);
				}
					break;
							
				default:
					break;
				}	
			}
		}
	}


	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
	{
		if (m_tInfo.fX >= 50)
		{
			if (!m_bRope && m_bLineride)
			{
				m_tInfo.fX -= m_fSpeed;
			}
		}

		m_eDir = PLAYER_DIR::LEFT;

		if(!m_bCastingskill)
			m_CurState = PLAYER_STATE::WALK;



		if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::UP) == KEY_STATE::HOLD)
			m_fAngle = 135.f;
		else if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
			m_fAngle = 225.f;
		else
			m_fAngle = 180.f;

	}


	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		if (m_tInfo.fX < pCurScene->GetMapTex()->Width() - 50)
		{
			if (!m_bRope && m_bLineride)
			{
				m_tInfo.fX += m_fSpeed;
			}
				
		}

		m_eDir = PLAYER_DIR::RIGHT;

		if (!m_bCastingskill)
			m_CurState = PLAYER_STATE::WALK;
		

		if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::UP) == KEY_STATE::HOLD)
			m_fAngle = 45.f;
		else if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
			m_fAngle = 315.f;
		else
			m_fAngle = 0.f;

	}


	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::D) == KEY_STATE::TAP)
	{
		if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
		{
			m_bDownJump = true;
		}

		if (m_iJumpCount > 0)		
		{
			m_bJump = true;
			--m_iJumpCount;
			
		}
	

		if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD
			|| CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
				m_bRope = false;
	}


	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::UP) == KEY_STATE::TAP)
	{
		CheckPotal();
	}


	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::UP) == KEY_STATE::HOLD)
	{
		float fY = 0.f;
		
		if (CLineMgr::Get_Instance()->Collisiong_UpRopeLine(this, &fY))
		{
			m_bRope = true;
			m_PreState = PLAYER_STATE::ROPE_NOMOVE;
			m_CurState = PLAYER_STATE::ROPE_MOVE;
			m_tInfo.fY -= m_fSpeed;
			
			if (m_tInfo.fY <= fY)
			{
				m_tInfo.fY = fY - 5;
				m_bRope = false;
			}
				
		}
		else
		{
			m_bRope = false;
			m_PreState = PLAYER_STATE::STATE_END;
		}
		
		if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LEFT) == KEY_STATE::NONE
			&& CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::NONE)
			m_fAngle = 90.f;
	}

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
	{
		
		float fY = 0.f;
		
		if (CLineMgr::Get_Instance()->Collisiong_DownRopeLine(this, &fY))
		{
			m_bRope = true;
			m_PreState = PLAYER_STATE::ROPE_NOMOVE;
			m_CurState = PLAYER_STATE::ROPE_MOVE;
			m_tInfo.fY += m_fSpeed;

			if (m_tInfo.fY >= fY)
			{
				m_tInfo.fY = fY;
		
			}
				
		}
		else
		{
			m_bRope = false;
			m_PreState = PLAYER_STATE::STATE_END;
		}

		if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LEFT) == KEY_STATE::NONE
			&& CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::NONE)
			m_fAngle = 270.f;
	}


	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::P) == KEY_STATE::TAP) // Stat UI 나오기
	{	
		if (m_pStatUI->GetActivate() == false)
		{
			CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"ui_open");
			pNewSound1->Play(false);
			pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
			pNewSound1->SetVolume(100.f); // 소리 볼륨 크기

			m_pStatUI->SetActivate(true);
		}
		else
		{
			CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"ui_close");
			pNewSound1->Play(false);
			pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
			pNewSound1->SetVolume(100.f); // 소리 볼륨 크기

			m_pStatUI->SetActivate(false);
		}
	}


	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::O) == KEY_STATE::TAP) // Skill UI 나오기
	{		
		if (m_pSkillUI->GetActivate() == false)
		{
			CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"ui_open");
			pNewSound1->Play(false);
			pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
			pNewSound1->SetVolume(100.f); // 소리 볼륨 크기

			m_pSkillUI->SetActivate(true);
		}
		else
		{
			CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"ui_close");
			pNewSound1->Play(false);
			pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
			pNewSound1->SetVolume(100.f); // 소리 볼륨 크기

			m_pSkillUI->SetActivate(false);
		}
	}


	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::I) == KEY_STATE::TAP) // Skill UI 나오기
	{
		if (m_pInventory->GetActivate() == false)
		{
			CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"ui_open");
			pNewSound1->Play(false);
			pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
			pNewSound1->SetVolume(100.f); // 소리 볼륨 크기

			m_pInventory->SetActivate(true);
		}
		else
		{
			CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"ui_close");
			pNewSound1->Play(false);
			pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
			pNewSound1->SetVolume(100.f); // 소리 볼륨 크기

			m_pInventory->SetActivate(false);
		}
	}

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::U) == KEY_STATE::TAP) // Skill UI 나오기
	{
		if (m_pEquipUI->GetActivate() == false)
		{
			CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"ui_open");
			pNewSound1->Play(false);
			pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
			pNewSound1->SetVolume(100.f); // 소리 볼륨 크기

			m_pEquipUI->SetActivate(true);
		}			
		else
		{
			CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"ui_close");
			pNewSound1->Play(false);
			pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
			pNewSound1->SetVolume(100.f); // 소리 볼륨 크기

			m_pEquipUI->SetActivate(false);
		}		
	}

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::Y) == KEY_STATE::TAP) // Skill UI 나오기
	{
		if (m_pDamageEffectUI->GetActivate() == false)
		{
			CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"ui_open");
			pNewSound1->Play(false);
			pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
			pNewSound1->SetVolume(100.f); // 소리 볼륨 크기

			m_pDamageEffectUI->SetActivate(true);
		}
		else
		{
			CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"ui_close");
			pNewSound1->Play(false);
			pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
			pNewSound1->SetVolume(100.f); // 소리 볼륨 크기

			m_pDamageEffectUI->SetActivate(false);
		}
	}




	if (!m_bRope && !m_bCastingskill &&  CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::A) == KEY_STATE::TAP) // 어퍼차지
	{
		if (0.f == m_tSkill[SKILL_TYPE::UPPERCHARGE]->GetSkillDelay() 
			|| UPPERCHARGE_DELAY <= m_tSkill[SKILL_TYPE::UPPERCHARGE]->GetSkillDelay())
		{
			if (!m_tSkill[SKILL_TYPE::UPPERCHARGE]->GetSkillActivate())
			{
				CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"uppercharge");
				pNewSound->Play(false);
				pNewSound->SetPosition(1.f); // 백분률 , 소리위치
				pNewSound->SetVolume(50.f); // 소리 볼륨 크기
			
				m_tSkill[SKILL_TYPE::UPPERCHARGE]->SetSkillDelay(0.f);
				m_tSkill[SKILL_TYPE::UPPERCHARGE]->SetSkillActivate(true); // 언제 비활성화?
				m_bCastingskill = true;
			}
		}

	}


	else if (!m_bRope && !m_bCastingskill && CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::W) == KEY_STATE::TAP) // 러쉬
	{
		if (0.f == m_tSkill[SKILL_TYPE::RUSH]->GetSkillDelay() 
			|| RUSH_DELAY <= m_tSkill[SKILL_TYPE::RUSH]->GetSkillDelay())
		{
			if (!m_tSkill[SKILL_TYPE::RUSH]->GetSkillActivate())
			{			
				CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"rush");
				pNewSound->Play(false);
				pNewSound->SetPosition(1.f); // 백분률 , 소리위치
				pNewSound->SetVolume(50.f); // 소리 볼륨 크기


				m_tSkill[SKILL_TYPE::RUSH]->SetSkillDelay(0.f);
				m_tSkill[SKILL_TYPE::RUSH]->SetSkillActivate(true); // 언제 비활성화?
				m_tSkill[SKILL_TYPE::RUSH]->SetFirstAttack(true);
				m_bCastingskill = true;
			}
		}
	}


	else if (!m_bRope && !m_bCastingskill && CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::R) == KEY_STATE::TAP) // 데스폴트
	{	
		if (0.f == m_tSkill[SKILL_TYPE::DEATHFAULT]->GetSkillDelay() 
			|| DEATHDAULT_DELAY <= m_tSkill[SKILL_TYPE::DEATHFAULT]->GetSkillDelay())
		{
			if (!m_tSkill[SKILL_TYPE::DEATHFAULT]->GetSkillActivate())
			{
				CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"deathfault");
				pNewSound->Play(false);
				pNewSound->SetPosition(1.f); // 백분률 , 소리위치
				pNewSound->SetVolume(65.f); // 소리 볼륨 크기

				CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"player_voice_deathfault");
				pNewSound1->Play(false);
				pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
				pNewSound1->SetVolume(80.f); // 소리 볼륨 크기

				m_tSkill[SKILL_TYPE::DEATHFAULT]->SetSkillDelay(0.f);
				m_tSkill[SKILL_TYPE::DEATHFAULT]->SetSkillActivate(true); // 언제 비활성화?
				m_tSkill[SKILL_TYPE::DEATHFAULT]->SetFirstAttack(true);
				m_bCastingskill = true;
			}
		}
	}


	else if (!m_bRope && !m_bCastingskill && CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::X) == KEY_STATE::TAP) //  6 차 스킬
	{
		if (QUEST_TYPE::TICKSIX == m_pQuest->GetCurQuest())
			m_pQuest->SetSuccess(true);


		if (0.f == m_tSkill[SKILL_TYPE::SIX]->GetSkillDelay()
			|| DEATHDAULT_DELAY <= m_tSkill[SKILL_TYPE::SIX]->GetSkillDelay())
		{
			if (!m_tSkill[SKILL_TYPE::SIX]->GetSkillActivate())
			{
				CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"player_six_sound");
				pNewSound->Play(false);
				pNewSound->SetPosition(1.f); // 백분률 , 소리위치
				pNewSound->SetVolume(65.f); // 소리 볼륨 크기

				CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"player_six_voice");
				pNewSound1->Play(false);
				pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
				pNewSound1->SetVolume(80.f); // 소리 볼륨 크기

				m_tSkill[SKILL_TYPE::SIX]->SetSkillDelay(0.f);
				m_tSkill[SKILL_TYPE::SIX]->SetSkillActivate(true); // 언제 비활성화?
				m_tSkill[SKILL_TYPE::SIX]->SetFirstAttack(true);
				m_bCastingskill = true;
			}
		}
	}


	else if (!m_bRope && !m_bCastingskill && CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::S) == KEY_STATE::TAP) // 레인지블로우
	{
		if (0.f == m_tSkill[SKILL_TYPE::RAGINGBLOW]->GetSkillDelay() 
			|| RAGINGBLOW_DELAY <= m_tSkill[SKILL_TYPE::RAGINGBLOW]->GetSkillDelay())
		{
			if (!m_tSkill[SKILL_TYPE::RAGINGBLOW]->GetSkillActivate())
			{
				CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"ragingblow");
				pNewSound->Play(false);
				pNewSound->SetPosition(1.f); // 백분률 , 소리위치
				pNewSound->SetVolume(50.f); // 소리 볼륨 크기

				static bool bCheck = false;

				if (!bCheck)
				{
					CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"player_voice_ragingblow");
					pNewSound1->Play(false);
					pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
					pNewSound1->SetVolume(70.f); // 소리 볼륨 크기
					bCheck = true;
				}
				else
				{
					CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"player_voice2_ragingblow");
					pNewSound1->Play(false);
					pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
					pNewSound1->SetVolume(70.f); // 소리 볼륨 크기
					bCheck = false;
				}
				

				m_tSkill[SKILL_TYPE::RAGINGBLOW]->SetSkillDelay(0.f);
				m_tSkill[SKILL_TYPE::RAGINGBLOW]->SetSkillActivate(true); // 언제 비활성화?
				m_tSkill[SKILL_TYPE::RAGINGBLOW]->SetFirstAttack(true);
				m_bCastingskill = true;
			}
		}
	}


	else if (!m_bRope && !m_bCastingskill && CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::Q) == KEY_STATE::TAP) // 오라블레이드
	{
		if (0.f == m_tSkill[SKILL_TYPE::ORABLADE]->GetSkillDelay() 
			|| ORABLADE_DELAY <= m_tSkill[SKILL_TYPE::ORABLADE]->GetSkillDelay())
		{
			if (!m_tSkill[SKILL_TYPE::ORABLADE]->GetSkillActivate())
			{
				CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"orablade");
				pNewSound->Play(false);
				pNewSound->SetPosition(1.f); // 백분률 , 소리위치
				pNewSound->SetVolume(50.f); // 소리 볼륨 크기


				CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"player_voice_orablade");
				pNewSound1->Play(false);
				pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
				pNewSound1->SetVolume(70.f); // 소리 볼륨 크기

				m_tSkill[SKILL_TYPE::ORABLADE]->SetSkillDelay(0.f);
				m_tSkill[SKILL_TYPE::ORABLADE]->SetSkillActivate(true); // 언제 비활성화?
				m_tSkill[SKILL_TYPE::ORABLADE]->SetFirstAttack(true);
				m_bCastingskill = true;
			}
		}
	}

	if (!m_bRope && !m_bCastingskill && CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::ONE) == KEY_STATE::TAP) // 오라블레이드
	{
		CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"Portion");
		pNewSound->Play(false);
		pNewSound->SetPosition(1.f); // 백분률 , 소리위치
		pNewSound->SetVolume(80.f); // 소리 볼륨 크기

		m_fHp = m_fMaxHp;
		m_fMp = m_fMaxMp;
	}

	//if (!m_bRope && !m_bCastingskill && CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::Z) == KEY_STATE::TAP) // 오라블레이드
	//{
	//	m_tSkill[SKILL_TYPE::SIX] = new CSixSkill;
	//	m_tSkill[SKILL_TYPE::SIX]->Initialize();
	//	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PLAYER_SKILL, m_tSkill[SKILL_TYPE::SIX]);
	//
	//
	//	//if (!m_tSkill[SKILL_TYPE::SIX]->GetSkillActivate())
	//	//{
	//	//	m_tSkill[SKILL_TYPE::SIX]->SetSkillDelay(0.f);
	//	//	m_tSkill[SKILL_TYPE::SIX]->SetSkillActivate(true); // 언제 비활성화?
	//	//	m_bCastingskill = true;
	//	//}
	//
	//}

	if (m_tInfo.fX < 50)
	{
		m_tInfo.fX = 50;
	}
	else if (m_tInfo.fX > pCurScene->GetMapTex()->Width() - 50)
	{
		m_tInfo.fX = pCurScene->GetMapTex()->Width() - 50;
	}

}



void CPlayer::Jump()
{
	float pY = 0.f;
	float pX = 0.f;


	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &pY, &pX );
	m_bLineride = bLineCol;  // 이거 건드리면 A, D 이동안댐 삭제 X


	if (m_bDownJump)
	{
		if (!m_bCastingskill)
			m_CurState = PLAYER_STATE::JUMP;

		m_tInfo.fY += 4.f;
		
		if (m_tInfo.fY + (m_tInfo.fCY / 2.f)  > pY)
		{
			m_tInfo.fY = pY - m_tInfo.fCY / 2;
			m_bDownJump = false;
		}

	}

	if (m_bJump)
	{	
		if (!m_bCastingskill)
 			m_CurState = PLAYER_STATE::JUMP;

		m_tInfo.fY -= (m_fPower  * m_fTime - ((9.8f * m_fTime * m_fTime) * 0.5));
		m_fTime += 0.015f;
		m_bLand = false;

		if (m_iJumpCount == 0)
		{
			if (m_tSkill[SKILL_TYPE::WARRIORLEAP])
			{
				CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"warriareap");
				pNewSound->Play(false);
				pNewSound->SetPosition(1.f); // 백분률 , 소리위치
				pNewSound->SetVolume(40.f); // 소리 볼륨 크기
				m_tSkill[SKILL_TYPE::WARRIORLEAP]->SetSkillActivate(true); // 언제 비활성화?
			}

			if (m_eDir == PLAYER_DIR::LEFT)
			{
				m_tInfo.fX -= m_fSpeed * 5;
				m_tInfo.fY -= m_fSpeed * 0.6;
			}
			else if (m_eDir == PLAYER_DIR::RIGHT)
			{
				m_tInfo.fX += m_fSpeed * 5;
				m_tInfo.fY -= m_fSpeed * 0.6;
			}
		
			// 메이플에서 방향이 의미있나? 어짜피 8방향인데 각도를 쓸까
   			//m_tInfo.fX += 1000 * cos(m_fAngle * PI /180.f) * fDT * 2;
			//m_tInfo.fY -= 800 * sin(m_fAngle * PI / 180.f) * fDT * 2;
		}

		if (bLineCol)
		{
			if (m_tInfo.fY + (m_tInfo.fCY / 2.f) - 5> pY) // 착지하는 순간
			{
				
				m_tInfo.fY = pY - m_tInfo.fCY / 2;
				m_fTime = 0.f;
				m_bJump = false;
				m_bLand = true;
				m_iJumpCount = 2;
			}
		}
	}


	else if (!m_bJump)			// 내가 점프하지 않고 내려갈 타겟라인을 찾았다면
	{
		if (bLineCol)
		{
			if (m_tSkill[SKILL_TYPE::UPPERCHARGE])
			{
				if (!m_tSkill[SKILL_TYPE::UPPERCHARGE]->GetSkillActivate())
				{
					if (m_tInfo.fY + (m_tInfo.fCY / 2.f) + 5 < pY)
					{
						if (!m_bCastingskill)
							m_CurState = PLAYER_STATE::JUMP;

						m_tInfo.fY += 3.f;
						m_bLand = false;
					}

					else if (m_tInfo.fY + (m_tInfo.fCY / 2.f) + 5 >= pY)
					{
						m_tInfo.fY = pY - m_tInfo.fCY / 2;
						m_bLand = true;
					}
				}
			}
			else 
			{
				if (m_tInfo.fY + (m_tInfo.fCY / 2.f) + 5 < pY)
				{
					if (!m_bCastingskill)
						m_CurState = PLAYER_STATE::JUMP;

					m_tInfo.fY += 3.f;
					m_bLand = false;
				}

				else if (m_tInfo.fY + (m_tInfo.fCY / 2.f) + 5 >= pY)
				{
					m_tInfo.fY = pY - m_tInfo.fCY / 2;
					m_bLand = true;
				}
			}

			
		}
	}




	m_fTargetLinefY = pY;
}

void CPlayer::FakeDead()
{
	m_CurState = PLAYER_STATE::DEAD;

	if (!m_pDieUI)
	{
	
		CStone* pStone = new CStone;
		pStone->Initialize();
		CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BACKGROUD, pStone);

		CDieUI* pDieUI = new CDieUI;
		pDieUI->Initialize();
		CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pDieUI);
		m_pDieUI = pDieUI;
	}

}




