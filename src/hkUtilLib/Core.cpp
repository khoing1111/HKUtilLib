#include "Core.h"


//============================================================================================
#pragma region // IPtrData
//============================================================================================

hkCore::IPtrContainer::IPtrContainer()
{
    m_nextVariant = nullptr;
    m_prevVariant = nullptr;

    m_numRef = 0;
    m_numStrongRef = 0;
    m_isLock = false;

    m_size = 0;
}

hkCore::IPtrContainer::IPtrContainer(IPtrContainer& clone)
{
    Reference(&clone);

    m_numRef = 0;
    m_numStrongRef = 0;
    m_isLock = clone.m_isLock;

    m_size = 0;
}

hkCore::IPtrContainer::IPtrContainer(uint size)
{
    m_nextVariant = nullptr;
    m_prevVariant = nullptr;

    m_numRef = 0;
    m_numStrongRef = 0;
    m_isLock = false;

    m_size = size;
}

hkCore::IPtrContainer::~IPtrContainer()
{
}

void hkCore::IPtrContainer::Reference(IPtrContainer* variant)
{
    // Add variant to variant list
    if (m_nextVariant)
        m_nextVariant->Reference(variant);
    else
    {
        // If this is the last variation in the list
        m_nextVariant = variant;
        variant->m_prevVariant = this;
    }
}

bool hkCore::IPtrContainer::Unlink()
{
    // If this is the only reference
    if (!m_prevVariant && !m_nextVariant)
        return false;

    // Re link previous variation to next variation
    if (m_prevVariant)
        m_prevVariant->m_nextVariant = m_nextVariant;

    // Re link next variation to previous variation
    if (m_nextVariant)
        m_nextVariant->m_prevVariant = m_prevVariant;

    // Remove all reference
    m_prevVariant = nullptr;
    m_nextVariant = nullptr;
    return true;
}

uint hkCore::IPtrContainer::Size()
{
    return m_size;
}

void hkCore::IPtrContainer::Lock()
{
    m_isLock = true;
}

void hkCore::IPtrContainer::UnLock()
{
    m_isLock = false;
}

//============================================================================================
#pragma endregion // IPtrData
//============================================================================================
