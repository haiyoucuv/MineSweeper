//
//  Tile.h
//  MineSweeper
//
//  Created by 还有醋v on 2019/5/26.
//

#ifndef Tile_h
#define Tile_h

#include "cocos2d.h"

USING_NS_CC;

class CTile : public Node
{
public:
	enum class TILE_STATE
	{
		DEFAULT = 0,
		FLAG = 1,
		ASK = 2
	};

public:
	CTile();
	virtual ~CTile();
	virtual bool init();
	CREATE_FUNC(CTile);

	CC_SYNTHESIZE(int, m_nCol, Col);
	CC_SYNTHESIZE(int, m_nRow, Row);
	CC_SYNTHESIZE(bool, m_bSearched, Searched);

public:
	Rect getBoundingBox();
	void setState(TILE_STATE state);
	TILE_STATE getState();
	void select();
	void cancel();
	void mouseRightClick();

private:
	Sprite* m_pImg;
	TILE_STATE m_State;
};

#endif /* Tile_h */
