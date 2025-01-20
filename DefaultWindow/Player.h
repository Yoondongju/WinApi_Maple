#pragma once

#include "Obj.h"

#include "LineMgr.h"
#include "ObjMgr.h"
#include "CHitDamageEffect.h"



class CTexture;

class CStatUI;
class CSkillUI;
class CInventoryUI;
class CEquipUI;
class CStoreUI;
class CPlayerUI;
class CQuickSlotUI;
class CDieUI;
class CDamageEffectUI;



class CPet;

class CPlayerSkill;
class CItem;

class CQuest;


enum class PLAYER_STATE
{
	IDLE,
	WALK,
	JUMP,
	DEAD,			// 여기 공격스킬 타입에 맞게 enum추가해야함
	DEATHFAULT,
	RAGINGBLOW,
	UPPERCHAGE,
	ORABLADE,
	RUSH,
	SIX,

	ROPE_NOMOVE,
	ROPE_MOVE,
	STATE_END
};

enum PLAYER_DIR
{
	LEFT,
	RIGHT,
	PLAYER_DIR_END
};




class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
	
public:
	virtual void Initialize() override;
	void		 Late_InitPlayerObj();

	virtual int Update() override;
	virtual void Late_Update()override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	void		Wall_Check();  // 이준식

public:
	void		QuestCheck();

	void		SetQuest(CQuest* _p) { m_pQuest = _p; }
	CQuest*		GetQuest() { return m_pQuest; }


public:
	void SetStatUI(CStatUI* _p) { m_pStatUI = _p; }
	CStatUI* GetStatrUI() { return m_pStatUI; }

	void SetSkillUI(CSkillUI* _p) { m_pSkillUI = _p; }
	CSkillUI* GetSKillUI() { return m_pSkillUI; }


	int GetAbilityPoint() { return m_iAbilityPoint; }
	void SetAbilityPoint(int _i) { m_iAbilityPoint = _i; }

	int GetSTR() { return m_iSTR; }
	int GetDEX() { return m_iDEX; }
	int GetINT() { return m_iINT; }
	int GetLUK() { return m_iLUK; }

	void SetSTR(int _i) { m_iSTR = _i; }
	void SetDEX(int _i) { m_iDEX = _i; }
	void SetINT(int _i) { m_iINT = _i; }
	void SetLUK(int _i) { m_iLUK = _i; }


	int GetSkillPoint() { return m_iSkillPoint; }
	void SetSkillPoint(int _i) { m_iSkillPoint = _i; }


	CPlayerSkill** GetAllSkill() { return m_tSkill; }
	CPlayerSkill* GetSkill(SKILL_TYPE _e) { return m_tSkill[_e]; }
	void SetCreateSkill(SKILL_TYPE _e);


public:
	void SetMaxHP(float _f) { m_fMaxHp = _f; }
	void SetHp(float _f)
	{
		if (PLAYER_STATE::DEATHFAULT == m_CurState
			|| PLAYER_STATE::SIX == m_CurState)
		{
			if (nullptr == m_pHitEffect)
			{
				CHitDamageEffect* pHitEffect = new CHitDamageEffect;

				INFO tInfo = this->Get_Info();
				pHitEffect->SetCreatePos(Vec2(tInfo.fX, tInfo.fY - 70));
				pHitEffect->Initialize();
				pHitEffect->Set_CXY(110.f, 70.f);
				pHitEffect->SetDamage(-1);
				m_pHitEffect = pHitEffect;

				CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_DAMAGE_EFFECT, pHitEffect);
			}
			
		}
		else
		{
			if (nullptr == m_pHitEffect)
			{
				CHitDamageEffect* pHitEffect = new CHitDamageEffect;

				INFO tInfo = this->Get_Info();
				pHitEffect->SetCreatePos(Vec2(tInfo.fX - 100.f, tInfo.fY - 70));
				pHitEffect->Initialize();

				CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_DAMAGE_EFFECT, pHitEffect);

				m_fHp = _f;   // 대미지 입을때만 
			}	
		}

	}

	CHitDamageEffect*	m_pHitEffect;


	void SetAttackInfo(float _f) { m_fAttackInfo = _f; }

	float GetMaxHP() { return m_fMaxHp; }
	float GetHp() { return m_fHp; }
	float GetAttackInfo() { return m_fAttackInfo; }


	void SetMaxMP(float _f) { m_fMaxMp = _f; }
	void SetMp(float _f) { m_fMp = _f; }


	float GetMaxMP() { return m_fMaxMp; }
	float GetMp() { return m_fMp; }


public:
	PLAYER_DIR	GetPlayerDir() { return m_eDir; }


public:
	PLAYER_STATE GetPlayerState() { return m_CurState; }
	void		SetPlayerState(PLAYER_STATE _e) { m_CurState = _e; }


public:
	float	GetTargetLinefY() { return m_fTargetLinefY; }

	void SetCastingskill(bool _b) { m_bCastingskill = _b; }


	void	SetMeso(int _i) { m_iMeso = _i; }
	int		GetMeso() { return m_iMeso; }

public:
	bool	GetLand() { return m_bLand; }

	
public:
	void CheckPotal();



public:
	CItem* GetItemType(ITEM_TYPE _e) { return m_pItem[(UINT)_e]; }
	void   SetItemType(CItem* _p, ITEM_TYPE _e) { m_pItem[(UINT)_e] = _p; }

private:
	void	CalculeAngle();


public:
	CInventoryUI*	GetPlayerInventory() { return m_pInventory; }
	CEquipUI*		GetPlayerEquipUI() { return m_pEquipUI; }
	CQuickSlotUI*	GetPlayerQuickSlotUI() { return m_pQuickslotUI; }
	

	void  SetMyPet(CObj* _pPet) { m_pPet = (CPet*)_pPet; }
	CPet* GetMyPet() { return m_pPet; }


public:
	int GetMapExp() { return m_iMaxExp; }

	void SetExp(int _i) { m_iExp = _i; }
	int GetExp() { return m_iExp; }

	void SetLevel(int _i) { m_iLevel = _i; }
	int GetLevel() { return m_iLevel; }


public:
	void	SetHitDelay(float _f) { m_fHitDelay = _f; }
	float	GetHitDelay() { return m_fHitDelay; }


	bool	GetFirstCollsion() { return m_bFirstCollision; }
	void	SetFirstCollsion(bool _b) { m_bFirstCollision = _b; }
	void	SetCollsion(bool _b) { m_bCollision = _b; }


	void	SetFakeDead(bool _b) { m_bFakeDead = _b; }
	bool	GetFakeDead() { return m_bFakeDead; }


public:
	void			 SetDamageEffect(DamageEffectType _e) { m_eDamgeEffectType = _e; }
	DamageEffectType GetDamageEffect() { return m_eDamgeEffectType; }

public:
	friend bool CLineMgr::Collision_Line(float& fX, float& fY, float* pY, float* pX);


private:
	void		Key_Input();
	void		Jump();
	void		DownJump();

	void		UpperCharge();


	void		FakeDead();


private:
	CQuest*				m_pQuest;
	DamageEffectType	m_eDamgeEffectType;
	CDamageEffectUI*	m_pDamageEffectUI;

	Vec2				m_vPrePos;
	bool				m_bFakeDead;		// 삭제시키지 않고 사망 Ui만 띄워주기 위함

	float				m_fDistance;

	bool				m_bJump;
	bool				m_bDownJump;

	bool				m_bLand;
	int					m_iJumpCount;
	float				m_fTime;

	Vec2				m_vJumpTargetPos;

	bool				m_bRope;

	bool				m_bLineride;
	float				m_fTargetLinefY;

	float				m_fPower;


	PLAYER_STATE		m_CurState;
	PLAYER_STATE		m_PreState;
	PLAYER_DIR			m_eDir;



	bool				m_bCameraCheck;

	CStatUI*			m_pStatUI;
	CSkillUI*			m_pSkillUI;
	CInventoryUI*		m_pInventory;
	CEquipUI*			m_pEquipUI;
	CStoreUI*			m_pStoreUI;
	CQuickSlotUI*		m_pQuickslotUI;
	CPlayerUI*			m_pConversationUI;
	CDieUI*				m_pDieUI;

	CPet*				m_pPet;


	float				m_fMaxHp;
	float				m_fHp;
	float				m_fMaxMp;
	float				m_fMp;
	int					m_iMaxExp;
	int					m_iExp;
	int					m_iLevel;

	float				m_fAttackInfo;

	int					m_iAbilityPoint;
	int					m_iSTR;
	int					m_iDEX;
	int					m_iINT;
	int					m_iLUK;

	float				m_fHitDelay;
	bool				m_bFirstCollision;
	bool				m_bCollision;
	BYTE				m_Alphabyte;


	int					m_iSkillPoint;

	CPlayerSkill*		m_tSkill[SKILL_TYPE::SKILL_END];


	bool				m_bCastingskill;

	int					m_iMeso;
	CItem*				m_pItem[(UINT)ITEM_TYPE::ITEM_END];







	friend class CPlayerHpUI;
	friend class CPlayerMpUI;
	friend class CExpUI;
	friend class CStatUI;
	friend class CSkillUI;
};



// y = 파워(힘) * sin(90) * 시간 - (9.8f * 시간 * 시간) / 2
// 1. 플레이어 중심으로 공전하는 물체 구현하기
// 2. 스크류 미사일 구현하기
// 3. 플레이어를 따라다니는 몬스터 구현하기