#include "stdafx.h"
#include "CConversationUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CKeyMgr.h"

#include "Player.h"
#include "ObjMgr.h"

#include "CConversationBtn.h"

#include "MainGame.h"
#include "CNpc.h"
#include "CQuest.h"

#include "CSound.h"

#include "CSixEffect.h"

CConversationUI::CConversationUI()
    : m_pInteractionObj(nullptr)
	, m_iCount(0)
	, m_pRenderTex(nullptr)
{
	m_pNpcTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"NPC_FACE", L"../API/UI/rain_talk.png");
	m_pPlayerTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"PLAYER_FACE", L"../API/UI/player_talk.png");

	m_pRenderTex = m_pPlayerTex;


	BLENDFUNCTION bf = GetBf();
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;

	SetBf(bf);

	m_vecText.reserve(10);
}

CConversationUI::~CConversationUI()
{
	Release();
}

void CConversationUI::Initialize(NPC_TYPE _e)
{
	m_tInfo = { WINCX / 2.f  , WINCY / 2.f   , 520.f ,200.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::CONVERSATION;
	
	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"TALKUI", L"../API/UI/NPC_TALK.png");


	CPlayerUI* pUIBtn = new CConversationBtn;
	pUIBtn->SetParentUI(this);
	pUIBtn->Initialize();
	m_childUI_List.push_back(pUIBtn);


	m_eActionType = _e;
	switch (m_eActionType)
	{
	case NPC_TYPE::TALK:
	{
		CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"rain_voice");
		pNewSound1->Play(false);
		pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
		pNewSound1->SetVolume(90.f); // 소리 볼륨 크기

		m_iMaxCount = 9;
		m_vecText.push_back(make_pair(L" 엇..? 방금 뭐라고..", 0));
		m_vecText.push_back(make_pair(L" 에스페라는 현재 위협받고 있어요.",1));
		m_vecText.push_back(make_pair(L" '윌' 이라는 존재가 거울 세계 속에 몸을 숨겨 공격 중이에요.", 1));
		m_vecText.push_back(make_pair(L" 그를 처치하려면 어디로 가야 하죠?!", 0));
		m_vecText.push_back(make_pair(L" '윌' 은 에스페라 끝 쪽 거울을 통해 만날 수 있어요.", 1));

		m_vecText.push_back(make_pair(L" 하지만 아직 그에게 다가가기 어려워 보여요..\n\n 제가 내리는 임무를 완수하면 그에게 보내드릴게요.", 1));
		m_vecText.push_back(make_pair(L" 어떤 것부터 하면 될까요?", 0));
		m_vecText.push_back(make_pair(L" 우선 오른쪽 상점에 가서 물약을 구매해 보세요.", 1));
		m_vecText.push_back(make_pair(L" 그 후, 'I' 키를 눌러 \n\n 소비창에서 물약을 1번 퀵 슬롯에 배치하세요.", 1));
	}
	break;
	case NPC_TYPE::BOSS_SIGN:
	{
		m_iMaxCount = 2;
		m_vecText.push_back(make_pair(L"이 너머에 윌이 존재할 것 같다..",0));
		m_vecText.push_back(make_pair(L"그를 처치하러 가자.",0));
	}
		break;
	case NPC_TYPE::NPC_TYPE_END:
		break;
	default:
		break;
	}
}


int CConversationUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bActivate)
	{
		if (m_iMaxCount == m_iCount)
		{
			StartAction();
			m_bActivate = false;
			return OBJ_NOEVENT;
		}

		if (m_vecText[m_iCount].second == 0)
		{
			m_pRenderTex = m_pPlayerTex;
		}
		else
			m_pRenderTex = m_pNpcTex;



		__super::Update_Rect();

		for (auto& iter : m_childUI_List)			// 자식은 항상 부모 위에 그려져야하니까 !
			iter->Update();


		return OBJ_NOEVENT;
	}

	
}

void CConversationUI::Late_Update()
{
	if (m_bActivate)
	{
		MouseOnCheck();


		for (auto& iter : m_childUI_List)			// 자식은 항상 부모 위에 그려져야하니까 !
			iter->Late_Update();
	}

}

void CConversationUI::Render(HDC hDC)
{
	if (m_bActivate)
	{
		AlphaBlend(hDC
			, m_tRect.left		            // ( 고정위치 )						// 이미지를 출력할 x
			, m_tRect.top		            // ( 고정위치 )						// 이미지를 출력할 y
			, m_tInfo.fCX							// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
			, m_tInfo.fCY
			, m_pUITex->GetDC()
			, 0								// 가져올 이미지의 시작위치
			, 0
			, m_pUITex->Width() 			// 잘라낼 크기니까 항상 800 이여야함
			, m_pUITex->Height()
			, this->GetBf());



		RECT rt = {
		  m_tRect.left + 200.f							// 대화창 사이즈 1000 x 210임 
		, m_tRect.top + 50.f
		, m_tRect.right - 50.f
		, m_tRect.bottom - 30.f
		};


		if (m_iMaxCount > m_iCount)
			DrawTextW(hDC
				, m_vecText[m_iCount].first.c_str()				// 변수가 들어가야함
				, -1
				, &rt
				, DT_LEFT | DT_WORDBREAK);




		AlphaBlend(hDC
			, m_tRect.left + 35.f					// ( 고정위치 )						// 이미지를 출력할 x
			, m_tRect.top + 30.f		            // ( 고정위치 )						// 이미지를 출력할 y
			, 100									// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
			, 100
			, m_pRenderTex->GetDC()
			, 0										// 가져올 이미지의 시작위치
			, 0
			, m_pRenderTex->Width() 				// 잘라낼 크기니까 항상 800 이여야함
			, m_pRenderTex->Height()
			, this->GetBf());





		for (auto& iter : m_childUI_List)			// 자식은 항상 부모 위에 그려져야하니까 !
			iter->Render(hDC);
	}

}

void CConversationUI::Release()
{
	for (auto& iter : m_childUI_List)			// 자식은 항상 부모 위에 그려져야하니까 !
		Safe_Delete<CPlayerUI*>(iter);


	m_childUI_List.clear();
}

void CConversationUI::MouseLBtnDown()
{
}

void CConversationUI::MouseLBtnUp()
{
}

void CConversationUI::MouseClick()
{
}

void CConversationUI::MouseOn()
{
}

void CConversationUI::MouseOut()
{
}

void CConversationUI::StartAction()		// 대화가 끝난후 호출되는 함수임 
{
	switch (m_eActionType)
	{
	case NPC_TYPE::TALK:
	{
		// 몇번째 대화인지에 따라 분기처리 해야하고
		static UINT iQuest = (UINT)QUEST_TYPE::PORTIONBUY_DRAG;

		CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"quest");
		pNewSound1->Play(false);
		pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
		pNewSound1->SetVolume(100.f); // 소리 볼륨 크기
		m_iCount = 0;

		CQuest* pQuest = ((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->GetQuest();		
		if (pQuest->IsSuccess())
		{
			pQuest->SetCurQuest((QUEST_TYPE)++iQuest);
		}
		else
		{
			// 퀘스트 성공못햇는데 다시 대화건경우
		}
		pQuest->SetState(QUEST_STATE::PROCEED);

		if (QUEST_TYPE::KILL_WILL == (QUEST_TYPE)iQuest)
			ChangeScene(BOSS_LOBBY);
		else if (QUEST_TYPE::MINIGAME == (QUEST_TYPE)iQuest)
			ChangeScene(MINIGAME);
		else if (QUEST_TYPE::TICKSIX == (QUEST_TYPE)iQuest)
		{
			CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"Appear");
			pNewSound->Play(false);
			pNewSound->SetPosition(1.f); // 백분률 , 소리위치
			pNewSound->SetVolume(75.f); // 소리 볼륨 크기

			CSixEffect* pSixEffect = new CSixEffect;
			pSixEffect->Initialize();
			CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_EFFECT, pSixEffect);		// 대기시간 끝나면 알아서 삭제댐
		}
		else if (QUEST_TYPE::PETBUY_ACTIVE == (QUEST_TYPE)iQuest)
		{
			m_pPlayer->SetMeso(10000);
		}

		else if (QUEST_TYPE::WEARINGPARTS == (QUEST_TYPE)iQuest)
			m_pPlayer->SetMeso(50000);

		else if (QUEST_TYPE::EMD == (QUEST_TYPE)iQuest)
		{
			list<CObj*>& npcList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_NPC);
			for (auto& iter : npcList)
				iter->Set_Dead();

			list<CObj*>& backList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_BACKGROUD);
			for (auto& iter : backList)
				iter->Set_Dead();

			CCamera::CreateSingleTonInst()->SetEnd(true);
		}
			

	}
		break;
	case NPC_TYPE::STORE:
		break;
	case NPC_TYPE::BOSS_SIGN:
		ChangeScene(BOSS_PAGE1);
		break;
	case NPC_TYPE::NPC_TYPE_END:
		break;
	default:
		break;
	}
}

void CConversationUI::SetReText()
{
	m_vecText.clear();


	CQuest* pQuest = ((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->GetQuest();
	       
	switch (pQuest->GetCurQuest())   // 현재 퀘스트는 대화가 끝나고 바로 부여됨 이미
	{
	case QUEST_TYPE::PORTIONBUY_DRAG:
	{
		m_iMaxCount = 2;
		m_vecText.push_back(make_pair(L" 잘하셨어요,\n\n 이번엔 제가 1만 메소를 드릴게요.", 1));
		m_vecText.push_back(make_pair(L" 이걸로 펫을 하나 구입하시고,\n\n 펫을 클릭하셔서 소환해 보세요.", 1));
	}
		break;

	case QUEST_TYPE::PETBUY_ACTIVE:
	{
		m_iMaxCount = 3;
		m_vecText.push_back(make_pair(L" 잘하셨어요,\n\n 펫은 몬스터를 사냥하고 나오는 아이템을\n 자동으로 먹어주는 역할을 하게될 거에요.", 1));
		m_vecText.push_back(make_pair(L" 넵! 알겠습니다.. 다음은 뭘 하면 좋을까요?", 0));
		m_vecText.push_back(make_pair(L" ' P ' 키를 눌러서 스텟창을 확인해보시고 능력치를 배분해보세요.", 1));
	}	
		break;
	case QUEST_TYPE::TICKSTAT:
	{
		m_iMaxCount = 3;
		m_vecText.push_back(make_pair(L" 당신은 히어로이므로 주요 능력치인 'STR (힘)'을 올려야 해요.", 1));
		m_vecText.push_back(make_pair(L" 레벨이 오를때 마다 'STR (힘)'을 올릴수 있어요.", 1));
		m_vecText.push_back(make_pair(L" 다음으로는 ' O ' 키를 눌러 모든스킬을 활성화하세요.", 1));
	}
		break;
	case QUEST_TYPE::TICKSKILL:
	{
		m_iMaxCount = 8;
		m_vecText.push_back(make_pair(L" 스킬은 총 6개에요. 각 스킬은 Q,W,R,A,S 키와 상호작용해요.", 1));
		m_vecText.push_back(make_pair(L" 스킬마다 고유한 딜레이를 보유하며, 스킬능력이 달라요.", 1));
		m_vecText.push_back(make_pair(L" 그리고, 스킬은 중첩해서 사용할수 없어요.", 1));
		m_vecText.push_back(make_pair(L" 마지막으로 이동 스킬인 'D (점프)' 키를\n 두 번 연속으로 누르시면 발동돼요.", 1));
		m_vecText.push_back(make_pair(L" ( 키를 눌러보며 스킬을 확인해야겠다.. )", 0));
		m_vecText.push_back(make_pair(L" ' Y ' 키를 눌러 데미지효과를 다르게 줄수도 있어요.\n\n 원하시는 효과를 적용해보세요.", 1));
		m_vecText.push_back(make_pair(L" 이제 오른쪽에 있는 포탈을 타고 사냥터로 가세요.", 1));
		m_vecText.push_back(make_pair(L" 그곳에서 9레벨을 달성한후 돌아오세요.", 1));
	}
		break;
	case QUEST_TYPE::HUNTING1:
	{
		m_iMaxCount = 3;
		m_vecText.push_back(make_pair(L" 오 제법 성장한 듯 보이네요!", 1));
		m_vecText.push_back(make_pair(L" 옆 광산에서 수상한 소리를 들었는데.. \n\n 가서 확인해 주실 수 있죠?", 1));
		m_vecText.push_back(make_pair(L" 넵..!", 0));
	}
		break;

	case QUEST_TYPE::MINIGAME:			// 미니게임 끝난후 대화 걸었을때 나오는 텍스트니까
	{
		m_iMaxCount = 6;
		m_vecText.push_back(make_pair(L" 그곳에서 무슨 일이 있던가요? \n\n 폭탄이 터지는 소리 같았는데..", 1));
		m_vecText.push_back(make_pair(L" ... 폭탄을 맞고 왔는걸요..", 0));
		m_vecText.push_back(make_pair(L" 안 죽었으니 됐어요. \n\n 대신 선물로 6차스킬을 드릴게요.", 1));
		m_vecText.push_back(make_pair(L" 그 힘을 받을 자격이 된것같네요.", 1));
		m_vecText.push_back(make_pair(L" ( ..알수없는기분에 힘이 넘친다 )", 0));
		m_vecText.push_back(make_pair(L" ' X ' 키를 누르면 사용할수있어요 \n\n 한번 사용해보세요.", 1));
	}
	break;

	case QUEST_TYPE::TICKSIX:
	{
		m_iMaxCount = 5;
		m_vecText.push_back(make_pair(L" 이 힘을 사용하러 가보셔야겠죠?", 1));
		m_vecText.push_back(make_pair(L" 이번엔 왼쪽 포탈을 타고 사냥터로 가보세요!", 1));
		m_vecText.push_back(make_pair(L" 그곳은 더 강한 몬스터들이 존재해요!", 1));
		m_vecText.push_back(make_pair(L" (... 쉴틈이 없군..)", 0));
		m_vecText.push_back(make_pair(L" (... 물약을 많이 소비할 것 같다..)", 0));
	}
	break;

	case QUEST_TYPE::HUNTING2:
	{
		m_iMaxCount = 7;
		m_vecText.push_back(make_pair(L" 무사하셨군요!", 1));
		m_vecText.push_back(make_pair(L" '카리아인' 을 잡는 데 어려움이 크셨을 것 같은데..", 1));
		m_vecText.push_back(make_pair(L" 갑자기 나와서 놀랬어요.. \n\n 엘리트 몬스터가 나온다는 말은..없었잖아요", 0));
		m_vecText.push_back(make_pair(L" 살아남으셨으면 됐죠, \n\n 그 정도 실력이면 '윌' 에게 맞설 수 있을 것 같아요.", 1));
		m_vecText.push_back(make_pair(L" 하지만 장비를 착용하지 않고 맨몸으로 갈 순 없죠.", 1));
		m_vecText.push_back(make_pair(L" 제가 5만 메소를 드릴게요, 상점에서 장비를 구입하세요.", 1));
		m_vecText.push_back(make_pair(L" 그 후 ' U ' 키를 눌러 장비창을열고, \n\n 아이템을 드래그하여 장착해 보세요. \n\n 인벤토리에서 아이템 위치를 변경할 수도 있답니다.", 1));
	}
		break;
	case QUEST_TYPE::WEARINGPARTS:
	{
		m_iMaxCount = 3;
		m_vecText.push_back(make_pair(L" 잘하셨어요! 이제 '윌' 에게 보내드릴게요 \n\n 준비되셨죠?", 1));
		m_vecText.push_back(make_pair(L" 넹", 0));
		m_vecText.push_back(make_pair(L" 무사히 돌아오세요!", 1));
	}
		break;

	case QUEST_TYPE::KILL_WILL:
	{
		m_iMaxCount = 1;
		m_vecText.push_back(make_pair(L" 시연회 끝 ^^", 0));
	}
		break;

	default:
		break;
	}

}
