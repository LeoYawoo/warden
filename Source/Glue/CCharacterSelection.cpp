#include "CCharacterSelection.h"
#include "StormMac/String.h"
#include "UI/CSimpleModelFFX.h"
#include "Engine/Source/Anim/CM2Model.h"
#include "Engine/Source/Anim/CM2Shared.h"

TSGrowableArray<CharacterSelectionDisplay> CCharacterSelection::s_characterList;
CSimpleModelFFX *CCharacterSelection::s_modelFrame;

void CCharacterSelection::RenderPrep() {
    // TODO
}

void CCharacterSelection::SetBackgroundModel(const char *modelPath) {
    if (!CCharacterSelection::s_modelFrame || !modelPath || !*modelPath) {
        return;
    }

    auto model = CCharacterSelection::s_modelFrame->m_model;

    // Check if already set
    if (model && !SStrCmpI(modelPath, model->m_shared->m_filePath, STORM_MAX_STR)) {
        return;
    }

    CCharacterSelection::s_modelFrame->SetModel(modelPath);

    // TODO BYTE1(CCharacterSelection::m_modelFrame->simplemodelffx_dword510[3]) = 1;

    model = CCharacterSelection::s_modelFrame->m_model;

    if (model) {
        // TODO lighting callback + arg

        model->IsDrawable(1, 1);
    }
}
