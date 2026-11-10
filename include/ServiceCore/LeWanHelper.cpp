#include "../../pch.h"
#include "LeWanHelper.h"

CLeWanHelper::CLeWanHelper()
{
    m_bCOMInitialized = false;
}

CLeWanHelper::~CLeWanHelper()
{
    Uninitialize();
}

bool CLeWanHelper::Initialize()
{
    if (m_bCOMInitialized && m_lw != nullptr)
        return true;

    // Khởi tạo COM trên luồng hiện tại
    HRESULT hr = CoInitializeEx(
        nullptr,
        COINIT_APARTMENTTHREADED
    );

    if (FAILED(hr))
    {
        LogE(_T("CoInitializeEx failed: 0x%08X"),
            static_cast<unsigned int>(hr));

        return false;
    }

    m_bCOMInitialized = true;

    // Tạo đối tượng LeWan trên luồng hiện tại
    hr = m_lw.CreateInstance(__uuidof(lwsoft));

    if (FAILED(hr))
    {
        LogE(_T("LeWan CreateInstance failed: 0x%08X"),
            static_cast<unsigned int>(hr));

        Uninitialize();
        return false;
    }

    LogD(_T("LeWan initialized successfully"));

    return true;
}

void CLeWanHelper::Uninitialize()
{
    // Giải phóng đối tượng COM
    m_lw.Release();

    // Giải phóng môi trường COM
    if (m_bCOMInitialized)
    {
        CoUninitialize();
        m_bCOMInitialized = false;
    }
}

IlwsoftPtr& CLeWanHelper::GetObject()
{
    return m_lw;
}