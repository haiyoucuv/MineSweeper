#include "Mine.h"


CMine::CMine()
:m_nMineNum(0),
m_pImg(nullptr)
{
}

CMine::~CMine() {
}

bool CMine::init() {
	if (!Node::init()) {
		return false;
	}

	m_pImg = Sprite::createWithSpriteFrameName("0.png");
	m_pImg->setAnchorPoint(Vec2(0, 0));
	m_pImg->setContentSize(Size(32, 32));
	this->addChild(m_pImg);

	m_State = CMine::MINE_STATE::DEFAULT;

	return true;
}

//////////////////////////////////////////////////////////////////////////
// 根据数字改变图片
void CMine::changeImgByNum(int nNumber) {
	m_nMineNum = nNumber;	// 记住数字
	if (9 == m_nMineNum) {	// 判断是否为9
		m_pImg->setSpriteFrame("mine.png");	// 设置为雷的图片
		m_pImg->setContentSize(Size(32, 32));
		return;
	}

	char szName[16] = {};	// 创建一个字符串数组
	sprintf(szName, "%d.png", m_nMineNum);	// 根据雷的个数格式化数组
	m_pImg->setSpriteFrame(szName);			// 设置图片
	m_pImg->setContentSize(Size(32, 32));
}

//////////////////////////////////////////////////////////////////////////
// 覆盖
// 获得包围盒
cocos2d::Rect CMine::getBoundingBox() {
	Rect rectImg = m_pImg->getBoundingBox();
	rectImg.origin = this->getPosition();
	return rectImg;
}

void CMine::setState(MINE_STATE state)
{	
	m_State = state;
	switch (m_State)
	{
		case CMine::MINE_STATE::DEFAULT:
			this->changeImgByNum(0);
			break;
		case CMine::MINE_STATE::CLEAR:
			m_pImg->setSpriteFrame("flag_select.png");
			break;
		case CMine::MINE_STATE::BLOOD:
			m_pImg->setSpriteFrame("blood.png");
			break;
		case CMine::MINE_STATE::ERR:
			m_pImg->setSpriteFrame("error.png");
			break;
		default:
			break;
	}
	m_pImg->setContentSize(Size(32, 32));
}
