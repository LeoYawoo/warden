#pragma once

#include <cstdint>
#include "Engine/Source/Tempest/CImVector.h"
#include "Engine/Source/Agile/CStatus.h"
#include "StormMac/xml/XMLNode.h"

using namespace Tempest;

class CSimpleFontString;

class CSimpleFrame;

class CSimpleTexture;


int32_t LoadXML_Color(XMLNode *node, CImVector &color);

int32_t LoadXML_Dimensions(XMLNode *node, float &x, float &y, CStatus *status);

int32_t LoadXML_Insets(XMLNode *node, float &left, float &right, float &top, float &bottom, CStatus *status);

CSimpleFontString *LoadXML_String(XMLNode *node, CSimpleFrame *frame, CStatus *status);

CSimpleTexture *LoadXML_Texture(XMLNode *node, CSimpleFrame *frame, CStatus *status);

int32_t LoadXML_Value(XMLNode *node, float &value, CStatus *status);

