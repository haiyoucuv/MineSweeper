#ifndef GameMenu_h
#define GameMenu_h

#include "cocos2d.h"
#include "GLB.h"

USING_NS_CC;
using namespace std;

class CGameMenu : public Scene
{
public:
	CGameMenu();
	virtual ~CGameMenu();
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(CGameMenu);

private:
	void loadRes();
	void onBtnClick(Ref* pSender);

private:
	MenuItemImage* m_pBtnLow;
	MenuItemImage* m_pBtnMiddle;
	MenuItemImage* m_pBtnHigh;
};

#endif // GameMenu_h