#pragma once

#include "Engine/Source/Tempest/C3Vector.h>
#include "Engine/Source/Agile/CHandleObject.h"
#include "Common/TSFixedArray.h"
#include "Common/TSExplicitList.h"
#include "CBaseManaged.h"
#include "TManaged.h"

using namespace Tempest;

class CDataMgr : public CHandleObject {
public:
    // Member variables
    TSFixedArray<CBaseManaged *> m_managedArray;
    STORM_EXPLICIT_LIST(CBaseManaged, m_link) m_updateList;

    // Member functions
    void AddManaged(CBaseManaged *managed, uint32_t fieldId, uint32_t flags, uint32_t dataTypeId);

    void AddManaged(TManaged<C3Vector> *managed, uint32_t fieldId, uint32_t flags);

    void AddManaged(TManaged<float> *managed, uint32_t fieldId, uint32_t flags);

    void LinkManaged(CBaseManaged *managed);
};


