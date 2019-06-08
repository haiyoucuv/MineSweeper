#include "GLB.h"

Glb* Glb::m_pInstance = nullptr;

Glb::Glb()
:m_nColCount(0)
, m_nRowCount(0)
, m_nMineCount(0)
{
}

Glb::~Glb()
{
}

Glb* Glb::getInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new Glb();
	}

	return m_pInstance;
}


