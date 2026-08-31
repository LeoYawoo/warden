#pragma once


#include "Common/TSGrowableArray.h"


class CSimpleModelFFX;

struct CharacterSelectionDisplay {
    // TODO
};

class CCharacterSelection {
public:
    // Static variables
    static TSGrowableArray<CharacterSelectionDisplay> s_characterList;
    static CSimpleModelFFX *s_modelFrame;

    // Static functions
    static void RenderPrep();

    static void SetBackgroundModel(const char *modelPath);
};


