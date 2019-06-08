//
//  Map.cpp
//  MineSweeper
//
//  Created by 还有醋v on 2019/5/26.
//

#include "TileLayer.h"
#include "GameScene.h"

CTileLayer::CTileLayer()
:m_pCurTile(nullptr)
{

}

CTileLayer::~CTileLayer()
{

}

bool CTileLayer::init()
{
	if (!Node::init())
	{
		return false;
	}
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Glb* pGlb = Glb::getInstance();
	m_nMaxCol = pGlb->getColCount();
	m_nMaxRow = pGlb->getRowCount();
	m_nMineCount = pGlb->getMineCount();

	this->createTile();
	this->setListener();

	return true;
}

//////////////////////////////////////////////////////////////////////////
// 根据坐标获得Tile
CTile* CTileLayer::getTileByPos(Vec2 pos)
{
	for (int nCol = 0; nCol < m_nMaxCol; nCol++)
	{
		for (int nRow = 0; nRow < m_nMaxRow; nRow++)
		{
			CTile* pCurTile = m_ArrTile[nCol][nRow];
			if (pCurTile != nullptr)
			{
				Rect rectTile = m_ArrTile[nCol][nRow]->getBoundingBox();
				if (rectTile.containsPoint(pos))
				{
					return m_ArrTile[nCol][nRow];
				}
			}
		}
	}
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
// 根据列行获得Tile
CTile* CTileLayer::getTileByRank(int nCol, int nRow)
{
	return m_ArrTile[nCol][nRow];
}

//////////////////////////////////////////////////////////////////////////
// 创建Tile
void CTileLayer::createTile()
{
	for (int nCol = 0; nCol < m_nMaxCol; nCol++)
	{
		for (int nRow = 0; nRow < m_nMaxRow; nRow++)
		{
			CTile* pTile = CTile::create();
			pTile->setPosition(nCol * 32, nRow * 32);
			pTile->setCol(nCol);
			pTile->setRow(nRow);
			this->addChild(pTile);
			m_ArrTile[nCol][nRow] = pTile;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// 失败（点到雷）要做的事情
void CTileLayer::gameOver()
{
	for (int nCol = 0; nCol < m_nMaxCol; nCol++)
	{
		for (int nRow = 0; nRow < m_nMaxRow; nRow++)
		{
			CTile* pTile = m_ArrTile[nCol][nRow];	// 当前Tile
			CMine* pMine = CGameScene::getInstance()->getMineLayer()->getMineByRank(nCol, nRow);	// 当前Mine

			if (pTile->getState() == CTile::TILE_STATE::FLAG && pMine->getMineNum() == 9)	// 如果Tile是旗帜且Mine是雷
			{
				pMine->setState(CMine::MINE_STATE::CLEAR);
			}

			if (pTile->getState() == CTile::TILE_STATE::FLAG && pMine->getMineNum() != 9)	// 如果Tile是旗帜但Mine不是雷
			{
				pMine->setState(CMine::MINE_STATE::ERR);
			}
			pTile->setVisible(false);
		}
	}
}

// 重新加载
void CTileLayer::reload()
{
	for (int nCol = 0; nCol < m_nMaxCol; nCol++)
	{
		for (int nRow = 0; nRow < m_nMaxRow; nRow++)
		{
			m_ArrTile[nCol][nRow]->setVisible(true);	// 设置成显示
			m_ArrTile[nCol][nRow]->setState(CTile::TILE_STATE::DEFAULT);	// 设置成 DEFAULT 状态
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// 设置监听
void CTileLayer::setListener()
{
	EventListenerMouse* pMouseListener = EventListenerMouse::create();
	pMouseListener->onMouseDown = CC_CALLBACK_1(CTileLayer::onMouseDown, this);
	pMouseListener->onMouseMove = CC_CALLBACK_1(CTileLayer::onMouseMove, this);
	pMouseListener->onMouseUp = CC_CALLBACK_1(CTileLayer::onMouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pMouseListener, this);
}

// 鼠标按下
void CTileLayer::onMouseDown(Event* event)
{
	if(CGameScene::getInstance()->getState() != CGameScene::GAME_STATE::GAME){	// 如果当前不是游戏状态
		return;
	}

	EventMouse* e = (EventMouse*)event;
	Vec2 worldPos = e->getLocationInView();
	Vec2 pos = this->convertToNodeSpaceAR(worldPos);

	m_pCurTile = this->getTileByPos(pos);	// 记录当前选中的Tile
	if (m_pCurTile == nullptr)	// 如果没有点到Tile
	{
		return;
	}

	if (m_pCurTile->getState() == CTile::TILE_STATE::FLAG)	// 如果点到的Tile是旗帜
	{
		return;
	}

	if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)	// 鼠标左键
	{
		m_pCurTile->select();	// 切换选中状态
		return;
	}
}

// 鼠标移动
void CTileLayer::onMouseMove(Event* event)
{
	if (CGameScene::getInstance()->getState() != CGameScene::GAME_STATE::GAME)
	{	// 如果当前不是游戏状态
		return;
	}

	EventMouse* e = (EventMouse*)event;
	Vec2 worldPos = e->getLocationInView();
	Vec2 pos = this->convertToNodeSpaceAR(worldPos);

	CTile* pTile = this->getTileByPos(pos);
	if (m_pCurTile == pTile)	// 如果当前的Tile就是当前选中的Tile
	{
		return;
	}

	if (m_pCurTile != nullptr)	// 如果Tile非空
	{
		m_pCurTile->cancel();	// 上一个Tile（当前记录的Tile）切换为取消状态
	}
	m_pCurTile = pTile;	// 记录当前选中的Tile
	if (m_pCurTile == nullptr)	// 如果当前选中的Tile为空
	{
		return;
	}

	if (m_pCurTile->getState() == CTile::TILE_STATE::FLAG)	// 如果当前选中的Tile为旗帜
	{
		return;
	}

	m_pCurTile->select();	// 切换为选中状态
}

// 鼠标抬起
void CTileLayer::onMouseUp(Event* event)
{
	if (CGameScene::getInstance()->getState() != CGameScene::GAME_STATE::GAME)
	{	// 如果当前不是游戏状态
		return;
	}

	EventMouse* e = (EventMouse*)event;
	Vec2 worldPos = e->getLocationInView();
	Vec2 pos = this->convertToNodeSpaceAR(worldPos);

	CTile* pTile = this->getTileByPos(pos);	// 获得抬起时鼠标所指的Tile
	if (pTile == nullptr)	// 如果这个Tile为空
	{
		return;
	}

	if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)	// 如果鼠标右键抬起
	{
		pTile->mouseRightClick();	// 当前Tile执行被鼠标右键点击的方法
		return;
	}

	if (pTile->getState() == CTile::TILE_STATE::FLAG)	// 如果当前Tile是旗帜则无效
	{
		return;
	}

	int nCol = pTile->getCol();	// 获取坐标
	int nRow = pTile->getRow();
	CMine* pMine = CGameScene::getInstance()->getMineLayer()->getMineByRank(nCol, nRow);	// 获取当前格子的Mine
	if (pMine->getMineNum() == 9)	// 如果当前格子是9（雷）
	{
		pTile->setVisible(false);
		pMine->setState(CMine::MINE_STATE::BLOOD);
		CGameScene::getInstance()->setState(CGameScene::GAME_STATE::LOST);
		this->gameOver();
		return;
	}

	if (pTile != nullptr && pTile->isVisible())	// 如果这个Tile不是空的或者没有隐藏则搜索附近的Tile
	{	
		m_VecSearch.pushBack(pTile);	// 加入搜索队列
		this->search();					// 执行搜索方法
		m_VecSearch.clear();			// 清空队列
		m_VecSearched.clear();
		if (this->isWin())	// 判断是否赢了游戏
		{
			CGameScene::getInstance()->setState(CGameScene::GAME_STATE::WIN);
			this->gameOver();
		}		
	}
}

//////////////////////////////////////////////////////////////////////////
// 搜索
void CTileLayer::search()
{
	while (m_VecSearch.size() > 0)
	{
		CTile* pTile = m_VecSearch.at(0);
		int nCol = pTile->getCol();
		int nRow = pTile->getRow();

		CMine* pCurMine = CGameScene::getInstance()->getMineLayer()->getMineByRank(nCol, nRow);
		if (pCurMine->getMineNum() == 9)
		{	// 是炸弹
			pTile->setVisible(false);
			return;
		}

		if (pCurMine->getMineNum() != 0)
		{	// 不是0
			pTile->setVisible(false);
			return;
		}

		//是0
		if (nCol != 0
			&& m_ArrTile[nCol - 1][nRow]->isVisible()
			&& !m_ArrTile[nCol - 1][nRow]->getSearched()
			&& m_ArrTile[nCol - 1][nRow]->getState() != CTile::TILE_STATE::FLAG)
		{	// 左
			CMine* pMine = CGameScene::getInstance()->getMineLayer()->getMineByRank(nCol - 1, nRow);
			if (pMine->getMineNum() == 0)
			{
				m_VecSearch.pushBack(m_ArrTile[nCol - 1][nRow]);
			}
		}

		if (nCol != m_nMaxCol - 1
			&& m_ArrTile[nCol + 1][nRow]->isVisible()
			&& !m_ArrTile[nCol + 1][nRow]->getSearched()
			&& m_ArrTile[nCol + 1][nRow]->getState() != CTile::TILE_STATE::FLAG)
		{	// 右
			CMine* pMine = CGameScene::getInstance()->getMineLayer()->getMineByRank(nCol + 1, nRow);
			if (pMine->getMineNum() == 0)
			{
				m_VecSearch.pushBack(m_ArrTile[nCol + 1][nRow]);
			}
		}

		if (nRow != m_nMaxRow - 1
			&& m_ArrTile[nCol][nRow]->isVisible()
			&& !m_ArrTile[nCol][nRow + 1]->getSearched()
			&& m_ArrTile[nCol][nRow + 1]->getState() != CTile::TILE_STATE::FLAG)
		{	// 上
			CMine* pMine = CGameScene::getInstance()->getMineLayer()->getMineByRank(nCol, nRow + 1);
			if (pMine->getMineNum() == 0)
			{
				m_VecSearch.pushBack(m_ArrTile[nCol][nRow + 1]);
			}
		}

		if (nRow != 0
			&& m_ArrTile[nCol][nRow - 1]->isVisible()
			&& !m_ArrTile[nCol][nRow - 1]->getSearched()
			&& m_ArrTile[nCol][nRow - 1]->getState() != CTile::TILE_STATE::FLAG)
		{	// 下
			CMine* pMine = CGameScene::getInstance()->getMineLayer()->getMineByRank(nCol, nRow - 1);
			if (pMine->getMineNum() == 0)
			{
				m_VecSearch.pushBack(m_ArrTile[nCol][nRow - 1]);
			}
		}

		pTile->setSearched(true);
		m_VecSearched.pushBack(pTile);
		m_VecSearch.erase(m_VecSearch.begin());
	}
	for (CTile* pTile : m_VecSearched)
	{
		this->openTileByTile(pTile);
		pTile->setSearched(false);
	}
}

void CTileLayer::openTileByTile(CTile* pTile)
{
	int nCol = pTile->getCol();
	int nRow = pTile->getRow();

	pTile->setVisible(false);

	if (nCol != 0
		&& m_ArrTile[nCol - 1][nRow]->isVisible()
		&& m_ArrTile[nCol - 1][nRow]->getState() == CTile::TILE_STATE::DEFAULT)
	{	// 左
		int pMineNum = CGameScene::getInstance()->getMineLayer()->getMineByRank(nCol - 1, nRow)->getMineNum();
		if (pMineNum != 0 && pMineNum != 9)
		{
			m_ArrTile[nCol - 1][nRow]->setVisible(false);
		}
	}
	if (nCol != m_nMaxCol - 1
		&& m_ArrTile[nCol + 1][nRow]->isVisible()
		&& m_ArrTile[nCol + 1][nRow]->getState() == CTile::TILE_STATE::DEFAULT)
	{	// 右
		int pMineNum = CGameScene::getInstance()->getMineLayer()->getMineByRank(nCol + 1, nRow)->getMineNum();
		if (pMineNum != 0 && pMineNum != 9)
		{
			m_ArrTile[nCol + 1][nRow]->setVisible(false);
		}
	}

	if (nRow != m_nMaxRow - 1
		&& m_ArrTile[nCol][nRow + 1]->isVisible()
		&& m_ArrTile[nCol][nRow + 1]->getState() == CTile::TILE_STATE::DEFAULT)
	{	// 上
		int pMineNum = CGameScene::getInstance()->getMineLayer()->getMineByRank(nCol, nRow + 1)->getMineNum();
		if (pMineNum != 0 && pMineNum != 9)
		{
			m_ArrTile[nCol][nRow + 1]->setVisible(false);
		}
	}

	if (nRow != 0
		&& m_ArrTile[nCol][nRow - 1]->isVisible()
		&& m_ArrTile[nCol][nRow - 1]->getState() == CTile::TILE_STATE::DEFAULT)
	{	// 下
		int pMineNum = CGameScene::getInstance()->getMineLayer()->getMineByRank(nCol, nRow - 1)->getMineNum();
		if (pMineNum != 0 && pMineNum != 9)
		{
			m_ArrTile[nCol][nRow - 1]->setVisible(false);
		}
	}

	if (nCol != 0 && nRow != m_nMaxRow - 1
		&& m_ArrTile[nCol - 1][nRow + 1]->isVisible()
		&& m_ArrTile[nCol - 1][nRow + 1]->getState() == CTile::TILE_STATE::DEFAULT)
	{	// 左上
		int pMineNum = CGameScene::getInstance()->getMineLayer()->getMineByRank(nCol - 1, nRow + 1)->getMineNum();
		if (pMineNum != 0 && pMineNum != 9)
		{
			m_ArrTile[nCol - 1][nRow + 1]->setVisible(false);
		}
	}

	if (nCol != m_nMaxCol - 1 && nRow != m_nMaxRow - 1
		&& m_ArrTile[nCol + 1][nRow + 1]->isVisible()
		&& m_ArrTile[nCol + 1][nRow + 1]->getState() == CTile::TILE_STATE::DEFAULT)
	{	// 右上
		int pMineNum = CGameScene::getInstance()->getMineLayer()->getMineByRank(nCol + 1, nRow + 1)->getMineNum();
		if (pMineNum != 0 && pMineNum != 9)
		{
			m_ArrTile[nCol + 1][nRow + 1]->setVisible(false);
		}
	}

	if (nCol != 0 && nRow != 0
		&& m_ArrTile[nCol - 1][nRow - 1]->isVisible()
		&& m_ArrTile[nCol - 1][nRow - 1]->getState() == CTile::TILE_STATE::DEFAULT)
	{	// 左下
		int pMineNum = CGameScene::getInstance()->getMineLayer()->getMineByRank(nCol - 1, nRow - 1)->getMineNum();
		if (pMineNum != 0 && pMineNum != 9)
		{
			m_ArrTile[nCol - 1][nRow - 1]->setVisible(false);
		}
	}

	if (nCol != m_nMaxCol - 1 && nRow != 0
		&& m_ArrTile[nCol + 1][nRow - 1]->isVisible()
		&& m_ArrTile[nCol + 1][nRow - 1]->getState() == CTile::TILE_STATE::DEFAULT)
	{	// 右下
		int pMineNum = CGameScene::getInstance()->getMineLayer()->getMineByRank(nCol + 1, nRow - 1)->getMineNum();
		if (pMineNum != 0 && pMineNum != 9)
		{
			m_ArrTile[nCol + 1][nRow - 1]->setVisible(false);
		}
	}
}

// 判断是否赢了
bool CTileLayer::isWin()
{
	for (int nCol = 0; nCol < m_nMaxCol; nCol++)
	{
		for (int nRow = 0; nRow < m_nMaxRow; nRow++)
		{
			CMine* pMine = CGameScene::getInstance()->getMineLayer()->getMineByRank(nCol, nRow);
			if (m_ArrTile[nCol][nRow]->isVisible() && pMine->getMineNum() != 9)
			{
				return false;
			}
		}
	}
	return true;
}

