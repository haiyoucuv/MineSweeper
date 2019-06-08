#include "GameMenu.h"
#include "GameScene.h"

CGameMenu::CGameMenu()
{
}

CGameMenu::~CGameMenu()
{
}

Scene* CGameMenu::createScene()
{
	return CGameMenu::create();
}

bool CGameMenu::init()
{
	if (!Scene::init())
	{
		return false;
	}

	this->loadRes();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();

	m_pBtnLow = MenuItemImage::create();
	m_pBtnLow->setNormalSpriteFrame(pCache->getSpriteFrameByName("btn_low_normal.png"));
	m_pBtnLow->setSelectedSpriteFrame(pCache->getSpriteFrameByName("btn_low_select.png"));
	m_pBtnLow->setCallback(CC_CALLBACK_1(CGameMenu::onBtnClick, this));
	m_pBtnLow->setPosition(origin.x + visibleSize.width / 2, origin.x + visibleSize.height / 3 * 2);

	m_pBtnMiddle = MenuItemImage::create();
	m_pBtnMiddle->setNormalSpriteFrame(pCache->getSpriteFrameByName("btn_middle_normal.png"));
	m_pBtnMiddle->setSelectedSpriteFrame(pCache->getSpriteFrameByName("btn_middle_select.png"));
	m_pBtnMiddle->setCallback(CC_CALLBACK_1(CGameMenu::onBtnClick, this));
	m_pBtnMiddle->setPosition(origin.x + visibleSize.width / 2, origin.x + visibleSize.height / 2);

	m_pBtnHigh = MenuItemImage::create();
	m_pBtnHigh->setNormalSpriteFrame(pCache->getSpriteFrameByName("btn_high_normal.png"));
	m_pBtnHigh->setSelectedSpriteFrame(pCache->getSpriteFrameByName("btn_high_select.png"));
	m_pBtnHigh->setCallback(CC_CALLBACK_1(CGameMenu::onBtnClick, this));
	m_pBtnHigh->setPosition(origin.x + visibleSize.width / 2, origin.x + visibleSize.height / 3);

	Menu* pMenu = Menu::create(m_pBtnLow, m_pBtnMiddle, m_pBtnHigh, nullptr);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu);

	return true;
}

void CGameMenu::loadRes()
{
	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	pCache->addSpriteFramesWithFile("image/Btn_Res.plist");
}

void CGameMenu::onBtnClick(Ref* pSender)
{
	Glb* pGlb = Glb::getInstance();
	if (pSender == m_pBtnLow)
	{
		pGlb->setColCount(9);
		pGlb->setRowCount(9);
		pGlb->setMineCount(10);
	}
	else if(pSender == m_pBtnMiddle)
	{
		pGlb->setColCount(16);
		pGlb->setRowCount(16);
		pGlb->setMineCount(40);
	}
	else if (pSender == m_pBtnHigh)
	{
		pGlb->setColCount(30);
		pGlb->setRowCount(16);
		pGlb->setMineCount(99);
	}
	CGameScene::destroy();
	Director::getInstance()->replaceScene(CGameScene::getInstance());
}
