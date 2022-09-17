#include "stdafx.h"
#include "CTunnel.h"

CTunnel::CTunnel()
{
}


CTunnel::~CTunnel()
{
    Release();
}

void CTunnel::Initialize(void)
{
    CBlock::Initialize();

    m_tInfo.fCX = 100.f;
    m_tInfo.fCY = 150.f;
}
