#ifndef Mine_h
#define Mine_h

#include "cocos2d.h"
USING_NS_CC;

class CMine : public Node
{
public:
	enum class MINE_STATE
	{
		DEFAULT = 0,
		CLEAR	= 1,
		BLOOD	= 2,
		ERR		= 3
	};

public:
	CMine();
	virtual ~CMine();
	virtual bool init();
	CREATE_FUNC(CMine);

	CC_SYNTHESIZE_READONLY(int, m_nMineNum, MineNum);
	CC_SYNTHESIZE(int, m_nCol, Col);
	CC_SYNTHESIZE(int, m_nRow, Row);

public:
	void changeImgByNum(int nNumber);	// 0 - 8 空白或数字   9 雷
	Rect getBoundingBox();
	void setState(MINE_STATE state);

private:
	Sprite* m_pImg;
	MINE_STATE m_State;
};

#endif // Mine_h