#pragma once

#include <comdef.h>

#import "lw9.09.dll" no_namespace

#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "OleAut32.lib")

class CLeWanHelper
{
public:
    CLeWanHelper();
    ~CLeWanHelper();

    bool Initialize();
    void Uninitialize();

    IlwsoftPtr& GetObject();

private:
    IlwsoftPtr m_lw;
    bool m_bCOMInitialized;
};