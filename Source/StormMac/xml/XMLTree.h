#pragma once

#include <cstdint>

class XMLNode;

struct XMLTree {
    XMLNode *root;
    XMLNode *leaf;
};

void XMLTree_Cleanup();

void XMLTree_Free(XMLTree *tree);

XMLNode *XMLTree_GetRoot(XMLTree *tree);

XMLTree *XMLTree_Load(const char *data, uint32_t length);

