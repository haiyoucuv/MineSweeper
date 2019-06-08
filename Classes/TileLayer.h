//
//  Map.h
//  MineSweeper
//
//  Created by 还有醋v on 2019/5/26.
//

#ifndef TileLayer_h
#define TileLayer_h

#include "cocos2d.h"
#include "Tile.h"

USING_NS_CC;

class CTileLayer : public Node {
public:
    CTileLayer();
    virtual ~CTileLayer();
    virtual bool init();
    CREATE_FUNC(CTileLayer);
	
public:
	CTile* getTileByPos(Vec2 pos);
	CTile* getTileByRank(int nCol, int nRow);
	void reload();
	
private:
	void createTile();
	void gameOver();

	void setListener();
	void onMouseDown(Event* event);
	void onMouseMove(Event* event);
	void onMouseUp(Event* event);
	
	void search();
	void openTileByTile(CTile* pTile);
	bool isWin();

private:
	CTile* m_ArrTile[30][24];
	CTile* m_pCurTile;
	Vector<CTile*> m_VecSearch;
	Vector<CTile*> m_VecSearched;
	int m_nMaxCol;
	int m_nMaxRow;
	int m_nMineCount;
};

#endif /* TileLayer_h */
