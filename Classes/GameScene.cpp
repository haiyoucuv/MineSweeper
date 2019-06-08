#include "GameScene.h"
#include "GameMenu.h"

CGameScene* CGameScene::m_pInstance = nullptr;

//Scene* CGameScene::createScene()
//{
//    return CGameScene::create();
//}

CGameScene* CGameScene::getInstance() {
	if (!m_pInstance) {
		m_pInstance = CGameScene::create();
	}
	return m_pInstance;
}

void CGameScene::destroy() {
	m_pInstance = nullptr;
}

bool CGameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
	
	this->loadRes();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int nMaxCol = Glb::getInstance()->getColCount();
	int nMaxRow = Glb::getInstance()->getRowCount();

	// 创建Mine层
	m_pMineLayer = CMineLayer::create();
	m_pMineLayer->setPosition(origin.x + visibleSize.width / 2 - 32 * nMaxCol / 2, origin.x + visibleSize.height / 5);
	this->addChild(m_pMineLayer);
	
	// 创建Tile层
 	m_pTileLayer = CTileLayer::create();
	m_pTileLayer->setPosition(origin.x + visibleSize.width / 2 - 32 * nMaxCol / 2, origin.x + visibleSize.height / 5);
 	this->addChild(m_pTileLayer);

	m_State = CGameScene::GAME_STATE::GAME;

	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	m_pBtnAgain = MenuItemImage::create();
	m_pBtnAgain->setNormalSpriteFrame(pCache->getSpriteFrameByName("state_go.png"));
	m_pBtnAgain->setSelectedSpriteFrame(pCache->getSpriteFrameByName("state_select.png"));
	m_pBtnAgain->setCallback(CC_CALLBACK_1(CGameScene::onBtnClick, this));
	m_pBtnAgain->setPosition(origin.x + visibleSize.width / 2, origin.x + visibleSize.height - 70);

	m_pBtnBack = MenuItemImage::create();
	m_pBtnBack->setNormalSpriteFrame(pCache->getSpriteFrameByName("back_btn_normal.png"));
	m_pBtnBack->setSelectedSpriteFrame(pCache->getSpriteFrameByName("back_btn_select.png"));
	m_pBtnBack->setCallback(CC_CALLBACK_1(CGameScene::onBtnClick, this));
	float fX = origin.x + m_pBtnBack->getContentSize().width / 2 + 20;
	float fY = origin.x + visibleSize.height - m_pBtnBack->getContentSize().height / 2 - 20;
	m_pBtnBack->setPosition(fX, fY);
	
	Menu* pMenu = Menu::create(m_pBtnAgain, m_pBtnBack, nullptr);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu);

    return true;
}


CGameScene::GAME_STATE CGameScene::getState()
{
	return m_State;
}

// 设置状态
void CGameScene::setState(GAME_STATE state)
{
	if (m_State == state)
	{
		return;
	}

	m_State = state;

	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();

	switch (m_State)
	{
		case CGameScene::GAME_STATE::GAME:
			m_pBtnAgain->setNormalSpriteFrame(pCache->getSpriteFrameByName("state_go.png"));
			break;
		case CGameScene::GAME_STATE::WIN:
			m_pBtnAgain->setNormalSpriteFrame(pCache->getSpriteFrameByName("state_win.png"));
			break;
		case CGameScene::GAME_STATE::LOST:
			m_pBtnAgain->setNormalSpriteFrame(pCache->getSpriteFrameByName("state_dead.png"));
			break;
		default:
			break;
	}

}

void CGameScene::onBtnClick(Ref* pSender)
{
	if (pSender == m_pBtnAgain)
	{
		this->setState(CGameScene::GAME_STATE::GAME);
		m_pTileLayer->reload();
		m_pMineLayer->reload();
	}
	else if (pSender == m_pBtnBack)
	{
		Scene* pGameMenu = CGameMenu::createScene();
		Director::getInstance()->replaceScene(pGameMenu);
	}
}

// 加载资源
void CGameScene::loadRes() { 
	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	pCache->addSpriteFramesWithFile("image/Mine_Res.plist");
}
