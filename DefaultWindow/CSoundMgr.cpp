#include "stdafx.h"
#include "CSoundMgr.h"
#include "CResMgr.h"
#include "CSound.h" 



CSoundMgr::CSoundMgr()
	: m_pSound(nullptr)
	, m_pBGM(nullptr)
{
}

CSoundMgr::~CSoundMgr()
{
}

int CSoundMgr::init(void)
{
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
	{
		MessageBox(NULL, L"사운드디바이스생성실패", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// 사운드 디바이스 협조레벨 설정.
	HWND hWnd = g_hWnd;
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag값 정리
	{
		MessageBox(NULL, L"사운드디바이스 협조레벨 설정", L"SYSTEM ERROR", MB_OK);
		return false;
	}


	CResMgr::CreateSingleTonInst()->LoadSound(L"Lobby_BGM", L"../API/sound/BGM/Lobby.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"Hunting1_BGM", L"../API/sound/BGM/Hunting_1.wav");

	CResMgr::CreateSingleTonInst()->LoadSound(L"Hunting2_First_BGM", L"../API/sound/BGM/Hunting_2_First.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"Hunting2_Second_BGM", L"../API/sound/BGM/Hunting_2_Second.wav");

	CResMgr::CreateSingleTonInst()->LoadSound(L"Boss_Lobby_BGM", L"../API/sound/BGM/Boss_Lobby.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"Boss_Page1_BGM", L"../API/sound/BGM/Boss_Page1.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"Boss_Page2_BGM", L"../API/sound/BGM/Boss_Page2.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"Boss_Page3_BGM", L"../API/sound/BGM/Boss_Page3.wav");

	CResMgr::CreateSingleTonInst()->LoadSound(L"MiniGame_BGM", L"../API/sound/BGM/minigame.wav");

	


	CResMgr::CreateSingleTonInst()->LoadSound(L"ui_open", L"../API/sound/UI/openUI.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"ui_close", L"../API/sound/UI/closeUI.wav");

	CResMgr::CreateSingleTonInst()->LoadSound(L"ui_click", L"../API/sound/UI/ClickUI.wav");	  // UI 누를때 
	CResMgr::CreateSingleTonInst()->LoadSound(L"Item_Click", L"../API/sound/UI/ClickItem.wav");  // 아이템 집을때 
	CResMgr::CreateSingleTonInst()->LoadSound(L"Item_Drop", L"../API/sound/UI/dropItem.wav");    // 아이템 장착할때 

	CResMgr::CreateSingleTonInst()->LoadSound(L"levelup", L"../API/sound/UI/levelup.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"nomeso", L"../API/sound/UI/noMeso.wav");     // 메소 없을때




	CResMgr::CreateSingleTonInst()->LoadSound(L"quest", L"../API/sound/quest/quest.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"quest_success", L"../API/sound/quest/quest_success.wav");










	CResMgr::CreateSingleTonInst()->LoadSound(L"player_die", L"../API/sound/player/die.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"player_jump", L"../API/sound/player/Jump.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"pet", L"../API/sound/player/pet.wav");

	CResMgr::CreateSingleTonInst()->LoadSound(L"meso", L"../API/sound/player/meso.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"Portion", L"../API/sound/player/Portion.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"Potal", L"../API/sound/player/potal.wav");

	CResMgr::CreateSingleTonInst()->LoadSound(L"Appear", L"../API/sound/Skill/Appear.wav");

	CResMgr::CreateSingleTonInst()->LoadSound(L"railmove", L"../API/sound/Skill/move.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"collboom", L"../API/sound/Skill/collboom.wav");





	CResMgr::CreateSingleTonInst()->LoadSound(L"deathfault", L"../API/sound/Skill/deathfault.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"deathfault_hit", L"../API/sound/Skill/deathfault_hit.wav");
	
	CResMgr::CreateSingleTonInst()->LoadSound(L"orablade", L"../API/sound/Skill/orablade.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"rush", L"../API/sound/Skill/rush.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"uppercharge", L"../API/sound/Skill/uppercharge.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"warriareap", L"../API/sound/Skill/warriareap.wav");
	
	CResMgr::CreateSingleTonInst()->LoadSound(L"ragingblow", L"../API/sound/Skill/ragingblow.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"ragingblow_hit", L"../API/sound/Skill/ragingblow_hit.wav");
	
	CResMgr::CreateSingleTonInst()->LoadSound(L"player_voice_deathfault", L"../API/sound/Skill/player_voice_deathfault.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"player_voice_orablade", L"../API/sound/Skill/player_voice_orablade.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"player_voice_ragingblow", L"../API/sound/Skill/player_voice_ragingblow.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"player_voice2_ragingblow", L"../API/sound/Skill/player_voice2_ragingblow.wav");

	CResMgr::CreateSingleTonInst()->LoadSound(L"player_six_voice", L"../API/sound/Skill/six_voice.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"player_six_sound", L"../API/sound/Skill/six_sound.wav");

	CResMgr::CreateSingleTonInst()->LoadSound(L"black_jack", L"../API/sound/Skill/black_jack.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"black_jack_hit", L"../API/sound/Skill/black_jack_hit.wav");
	//CResMgr::CreateSingleTonInst()->LoadSound(L"carema", L"../API/sound/Skill/carema.wav");



	CResMgr::CreateSingleTonInst()->LoadSound(L"rain_voice", L"../API/sound/rain_voice.wav");


	CResMgr::CreateSingleTonInst()->LoadSound(L"LM_attack1", L"../API/sound/LM/attack1.wav.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"LM_attack2", L"../API/sound/LM/attack2.wav.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"LM_attack3", L"../API/sound/LM/attack3.wav.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"LM_die", L"../API/sound/LM/die.wav.wav");
	CResMgr::CreateSingleTonInst()->LoadSound(L"LM_gen", L"../API/sound/LM/gen.wav.wav");



	return true;
}

void CSoundMgr::RegisterToBGM(CSound* _pSound)
{
	if (m_pBGM != nullptr)
		m_pBGM->Stop(true);

	m_pBGM = _pSound;
}