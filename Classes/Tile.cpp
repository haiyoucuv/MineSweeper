//
//  Tile.cpp
//  MineSweeper
//
//  Created by 还有醋v on 2019/5/26.
//

#include "Tile.h"

CTile::CTile()
:m_nCol(0),
m_nRow(0),
m_bSearched(false)
{
    
}

CTile::~CTile(){
    
}

bool CTile::init(){
    if (!Node::init()) {
        return false;
    }
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	m_pImg = Sprite::createWithSpriteFrameName("blank_default.png");
	m_pImg->setAnchorPoint(Vec2(0, 0));
	m_pImg->setContentSize(Size(32, 32));
	this->addChild(m_pImg);
	
	m_State = TILE_STATE::DEFAULT;

	//m_pImg->setOpacity(200);

    return true;
}

Rect CTile::getBoundingBox() {
	Rect rectImg = m_pImg->getBoundingBox();
	rectImg.origin = this->getPosition();
	return rectImg;
}

//////////////////////////////////////////////////////////////////////////
// 设置状态
void CTile::setState(TILE_STATE state) {
	if (m_State == state)
	{
		return;
	}

	this->m_State = state;

	switch (state) {
		case CTile::TILE_STATE::DEFAULT:
			m_pImg->setSpriteFrame("blank_default.png");
			break;
		case CTile::TILE_STATE::FLAG:
			m_pImg->setSpriteFrame("flag.png");
			break;
		case CTile::TILE_STATE::ASK:
			m_pImg->setSpriteFrame("ask_default.png");
			break;
		default:
			break;
	}
	m_pImg->setContentSize(Size(32, 32));
}

//////////////////////////////////////////////////////////////////////////
// 取得当前状态
CTile::TILE_STATE CTile::getState() {
	return m_State;
}

//////////////////////////////////////////////////////////////////////////
// 选中与取消
void CTile::select() {
	if (this->m_State == CTile::TILE_STATE::DEFAULT) {
		m_pImg->setSpriteFrame("blank_select.png");
	}
	else if (this->m_State == CTile::TILE_STATE::ASK) {
		m_pImg->setSpriteFrame("ask_select.png");
	}
	m_pImg->setContentSize(Size(32, 32));
}

void CTile::cancel() {
	if (this->m_State == CTile::TILE_STATE::DEFAULT) {
		m_pImg->setSpriteFrame("blank_default.png");
	}
	else if (this->m_State == CTile::TILE_STATE::ASK) {
		m_pImg->setSpriteFrame("ask_default.png");
	}
	m_pImg->setContentSize(Size(32, 32));
}

void CTile::mouseRightClick()
{
	switch (this->getState())
	{
		case CTile::TILE_STATE::DEFAULT:
			this->setState(CTile::TILE_STATE::FLAG);
			break;
		case CTile::TILE_STATE::FLAG:
			this->setState(CTile::TILE_STATE::ASK);
			break;
		case CTile::TILE_STATE::ASK:
			this->setState(CTile::TILE_STATE::DEFAULT);
			break;
		default:
			break;
	}
}
