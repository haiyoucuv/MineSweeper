#ifndef GLB_h
#define GLB_h

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Glb
{
public:
	~Glb();
	static Glb* getInstance();

	CC_SYNTHESIZE(int, m_nColCount, ColCount);
	CC_SYNTHESIZE(int, m_nRowCount, RowCount);
	CC_SYNTHESIZE(int, m_nMineCount, MineCount);

private:
	Glb();

private:
	static Glb* m_pInstance;
};

#endif // GLB_h
