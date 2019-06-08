//
//  Map.cpp
//  MineSweeper
//
//  Created by 还有醋v on 2019/5/27.
//

#include "MineLayer.h"

CMineLayer::CMineLayer()
{

}

CMineLayer::~CMineLayer()
{

}

bool CMineLayer::init()
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

	this->createMine();
	this->addMine();
	this->setAllMine();
	return true;
}

//////////////////////////////////////////////////////////////////////////
// 通过坐标获取Mine
CMine* CMineLayer::getMineByPos(Vec2 pos)
{
	for (int nCol = 0; nCol < m_nMaxCol; nCol++)
	{
		for (int nRow = 0; nRow < m_nMaxRow; nRow++)
		{
			CMine* pCurMine = m_ArrMine[nCol][nRow];
			if (pCurMine != nullptr)
			{
				Rect rectMine = m_ArrMine[nCol][nRow]->getBoundingBox();
				if (rectMine.containsPoint(pos))
				{
					return m_ArrMine[nCol][nRow];
				}
			}
		}
	}
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
// 根据列行获得Mine
CMine* CMineLayer::getMineByRank(int nCol, int nRow)
{
	return m_ArrMine[nCol][nRow];
}

//////////////////////////////////////////////////////////////////////////
// 重新加载
void CMineLayer::reload()
{
	// 全都设置成默认状态以及默认图片
	for (int nCol = 0; nCol < m_nMaxCol; nCol++)
	{
		for (int nRow = 0; nRow < m_nMaxRow; nRow++)
		{
			m_ArrMine[nCol][nRow]->setState(CMine::MINE_STATE::DEFAULT);
		}
	}
	this->addMine();	// 随机添加地雷
	this->setAllMine();	// 设置全部Mine
}

//////////////////////////////////////////////////////////////////////////
// 创建初始化所有Mine
void CMineLayer::createMine()
{
	for (int nCol = 0; nCol < m_nMaxCol; nCol++)
	{
		for (int nRow = 0; nRow < m_nMaxRow; nRow++)
		{
			CMine* pMine = CMine::create();
			pMine->setPosition(nCol * 32, nRow * 32);
			pMine->setCol(nCol);
			pMine->setRow(nRow);
			this->addChild(pMine);
			m_ArrMine[nCol][nRow] = pMine;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// 随机添加地雷
void CMineLayer::addMine()
{
	for (int i = 0; i < m_nMineCount; i++)
	{
		int nCol = rand() % m_nMaxCol;
		int nRow = rand() % m_nMaxRow;
		if (m_ArrMine[nCol][nRow]->getMineNum() == 9)
		{
			i--;
			continue;
		}
		m_ArrMine[nCol][nRow]->changeImgByNum(9);
	}
}

//////////////////////////////////////////////////////////////////////////
// 设置全部Mine
void CMineLayer::setAllMine()
{
	for (int nCol = 0; nCol < m_nMaxCol; nCol++)
	{
		for (int nRow = 0; nRow < m_nMaxRow; nRow++)
		{
			if (m_ArrMine[nCol][nRow]->getMineNum() != 9)
			{
				int nNum = 0;

				if (nCol != 0 && m_ArrMine[nCol - 1][nRow]->getMineNum() == 9)
				{	// 左
					nNum++;
				}
				if (nCol != m_nMaxCol - 1 && m_ArrMine[nCol + 1][nRow]->getMineNum() == 9)
				{	// 右
					nNum++;
				}

				if (nRow != m_nMaxRow - 1 && m_ArrMine[nCol][nRow + 1]->getMineNum() == 9)
				{	// 上
					nNum++;
				}

				if (nRow != 0 && m_ArrMine[nCol][nRow - 1]->getMineNum() == 9)
				{	// 下
					nNum++;
				}

				if (nCol != 0 && nRow != m_nMaxRow - 1 && m_ArrMine[nCol - 1][nRow + 1]->getMineNum() == 9)
				{	// 左上
					nNum++;
				}

				if (nCol != m_nMaxCol - 1 && nRow != m_nMaxRow - 1 && m_ArrMine[nCol + 1][nRow + 1]->getMineNum() == 9)
				{	// 右上
					nNum++;
				}

				if (nCol != 0 && nRow != 0 && m_ArrMine[nCol - 1][nRow - 1]->getMineNum() == 9)
				{	// 左下
					nNum++;
				}

				if (nCol != m_nMaxCol - 1 && nRow != 0 && m_ArrMine[nCol + 1][nRow - 1]->getMineNum() == 9)
				{	// 右下
					nNum++;
				}

				m_ArrMine[nCol][nRow]->changeImgByNum(nNum);
			}
		}
	}
}
