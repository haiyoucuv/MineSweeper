//
//  Map.h
//  MineSweeper
//
//  Created by 还有醋v on 2019/5/27.
//

#ifndef MineLayer_h
#define MineLayer_h

#include "cocos2d.h"
#include "Mine.h"
#include "GLB.h"

USING_NS_CC;

class CMineLayer : public Node {
public:
	CMineLayer();
	virtual ~CMineLayer();
	virtual bool init();
	CREATE_FUNC(CMineLayer);

public:
	CMine* getMineByPos(Vec2 pos);
	CMine* getMineByRank(int nCol, int nRow);
	void reload();

private:
	void createMine();
	void addMine();
	void setAllMine();

private:
	CMine* m_ArrMine[30][24];
	int m_nMaxCol;
	int m_nMaxRow;
	int m_nMineCount;
};

#endif /* MineLayer_h */
