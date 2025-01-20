#pragma once



extern	HWND		g_hWnd;

#define			WINCX		1280
#define			WINCY		768

#define			PURE		= 0

#define			OBJ_NOEVENT		0
#define			OBJ_DEAD		1

#define			PI			3.141592f



#define			PLAYER_CX 30.f




#define SINGLE(type)\
private:\
	type();\
	~type();\
public:\
	static type* CreateSingleTonInst()\
	{\
		static type mgr;\
		return &mgr;\
	}\


#define fDT CTimeMgr::CreateSingleTonInst()->GetfDT()
#define DT CTimeMgr::CreateSingleTonInst()->GetDT()

struct Vec2
{
	float x;
	float y;

public:
	bool IsZero()
	{
		if (x == 0.f && y == 0.f)
			return true;
		return false;
	}

	float Length()
	{
		return sqrt(x * x + y * y);

	}

	Vec2& Normalize()
	{
		float fLen = Length();

		assert(fLen != 0.f);

		x /= fLen;
		y /= fLen;

		return *this;
	}

	Vec2 operator - ()
	{
		return Vec2(-x, -y);
	}


	Vec2 operator +(Vec2 vOther)
	{
		return Vec2(x + vOther.x, y + vOther.y);
	}

	Vec2 operator +=(Vec2 vOther)
	{
		*this = *this + vOther;

		return Vec2(*this);
	}

	Vec2 operator +(float fOther)
	{
		return Vec2(x + fOther, y + fOther);
	}

	Vec2 operator -(Vec2 vOther)
	{
		return Vec2(x - vOther.x, y - vOther.y);
	}

	Vec2 operator -(float _fOther)
	{
		return Vec2(x - _fOther, y - _fOther);
	}

	void operator -= (Vec2 _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

	void operator -= (float _fOther)
	{
		x -= _fOther;
		y -= _fOther;
	}

	Vec2 operator *(Vec2 vOther)
	{
		return Vec2(x * vOther.x, y * vOther.y);
	}

	Vec2 operator *(int _nOther)
	{
		return Vec2(x * (float)_nOther, y * (float)_nOther);
	}

	Vec2 operator *(float _nOther)
	{
		return Vec2(x * _nOther, y * _nOther);
	}

	Vec2 operator / (Vec2 vOther)
	{
		assert(!(0.f == vOther.x || 0.f == vOther.y));

		return Vec2(x / vOther.x, y / vOther.y);
	}

	Vec2 operator / (float _f)
	{
		assert(!(0.f == _f));

		return Vec2(x / _f, y / _f);
	}

	Vec2 operator = (POINT pOther)
	{
		return Vec2(x = (float)pOther.x, y = (float)pOther.y);
	}


public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(POINT _pOther)
		: x((float)_pOther.x)
		, y((float)_pOther.y)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec2(float _f)
		: x(_f)
		, y(_f)
	{}

};

template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		CObject* pObjvec = dynamic_cast<CObject*>(_vec[i]);
		if (pObjvec != nullptr && !pObjvec->IsDead())
		{
			delete pObjvec;
		}

	}

	_vec.clear();
}


template<typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();

	for (; iter != _map.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}

	_map.clear();
}


typedef struct tagPoint
{
	float	fX;
	float	fY;

	tagPoint() { ZeroMemory(this, sizeof(tagPoint)); }
	tagPoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}LINEPOINT; // 한점의 좌표고 


typedef struct tagInfo
{
	float		fX;
	float		fY;

	float		fCX;
	float		fCY;

}INFO;


enum  OBJID 
{
	OBJ_BACKGROUD,
	OBJ_WALL,
	OBJ_MINIGAMEOBJ,
	OBJ_POTAL,
	OBJ_NPC,
	OBJ_MONSTER,
	OBJ_BOSS_BULLET,
	OBJ_BOSS,
	OBJ_BOSS_SKILL,
	OBJ_PLAYER_SKILL,
	OBJ_PET,
	OBJ_PLAYER,
	OBJ_PLAYER_SKILL_EFFECT,
	
	OBJ_ITEM,
	OBJ_MESO,

	
	OBJ_DAMAGE_EFFECT,
	OBJ_EFFECT,
	OBJ_UI, 
	OBJ_MOUSE, 
	OBJ_END
};


enum class ITEM_TYPE
{
	RING,
	BELT,
	EYE_PATCH,
	NECKLACE,
	EARRING,
	PORTION,
	PET,


	ITEM_END
};


enum class NPC_TYPE
{
	TALK,
	STORE,
	BOSS_SIGN,

	NPC_TYPE_END
};



enum  LINETYPE
{
	NONE,
	WALL,
	ROPE,
	FLOOR,

	LINEEND,
};

enum class DamageEffectType
{
	NONE,
	VOLCANO,
	PATICLE,
};


typedef struct tagLine
{
	LINEPOINT		tLPoint;   // 라인은 각 왼쪽점, 오른쪽점이 필요함
	LINEPOINT		tRPoint;   // 라인은 각 왼쪽점, 오른쪽점이 필요함
	

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& _tLPoint, LINEPOINT& _tRPoint)   // 라인하나 만들때 점 두개를 받아옴
		: tLPoint(_tLPoint), tRPoint(_tRPoint) {}

}LINE;



enum BRUSH_TYPE
{
	HOLLOW,
	BLACK,
	WHITE,
	BRUSH_TYPE_END
};

enum  PEN_TYPE
{
	RED,
	GREEN,
	BULE,
	PEN_TYPE_END
};



enum  MON_STATE
{
	IDLE,	 // 기본
	PATROL,  // 순찰
	TRACE,   // 추적
	CODEMODE, // CodeMode 걍 내가 짠 코드에 의해 스토리가 진행될수 있게 만든 상태임
	CODEMODE_MT, // 학생회장 부학생회장이 동작하는 AI
	GETDIRECTIONS, // 길 찾기
	ATT,	 // 공격
	RUN,     // 도망가기
	DEAD,    // 사망

	MON_STATE_END
};

enum SKILL_TYPE
{
	DEATHFAULT,
	ORABLADE,
	RAGINGBLOW,
	RUSH,
	UPPERCHARGE,
	WARRIORLEAP,

	SIX,

	SKILL_END,
};


template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

template<typename T>
void Safe_Delete_Array(T& Temp)
{
	if (Temp)
	{
		delete[] Temp;
		Temp = nullptr;
	}
}



