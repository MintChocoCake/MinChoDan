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
}
