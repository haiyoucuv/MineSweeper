#ifndef __Game_Scene_h__
#define __Game_Scene_h__

#include "cocos2d.h"
#include "TileLayer.h"
#include "MineLayer.h"
#include "GLB.h"

USING_NS_CC;
class CGameScene : public Scene
{
public:
	enum class GAME_STATE
	{
		GAME = 0,
		WIN	 = 1,
		LOST = 2
	};

public:
	static CGameScene* getInstance();
	static void destroy();
    //static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(CGameScene);
	
	CC_SYNTHESIZE_READONLY(CTileLayer*, m_pTileLayer, TileLayer);
	CC_SYNTHESIZE_READONLY(CMineLayer*, m_pMineLayer, MineLayer);

public:
	GAME_STATE getState();
	void setState(GAME_STATE state);
	
private:;
	void onBtnClick(Ref* pSender);
	void loadRes();

private:
	static CGameScene* m_pInstance;
	GAME_STATE m_State;
	MenuItemImage* m_pBtnAgain;
	MenuItemImage* m_pBtnBack;
};

#endif // __Game_Scene_h__
