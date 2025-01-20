// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once


#include "targetver.h"

// Windows ��� ����:
#include <windows.h>

#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus")


//#pragma comment(lib,"winmm.lib")
#pragma comment(lib, "msimg32.lib")

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>




// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <vector>



#include <list>
#include <map>
#include <string>


#include <algorithm>
#include <math.h>
#include <assert.h>

#include <mmsystem.h>


#include <sstream>
using std::stringstream;
using std::wstringstream;


enum  SCENE_TYPE
{
	LOBBY,
	HUNTING_GROUND,
	HUNTING_GROUND2,

	BOSS_LOBBY,
	BOSS_PAGE1,
	BOSS_PAGE2,
	BOSS_PAGE3,

	MINIGAME,

	SCENE_END,
};




void ChangeScene(SCENE_TYPE _Next);


#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif

using namespace std;


