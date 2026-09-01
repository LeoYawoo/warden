#pragma once

#include "Common/TRefCnt.h"

// Reverse engineered from Warcraft III binary
// Huffman coding for compression/decompression

// Huffman node structure
struct HUFFNODE {
    int weight;
    int symbol;
    HUFFNODE* left;
    HUFFNODE* right;
    HUFFNODE* parent;
    // Link for list
    HUFFNODE* next;
    HUFFNODE* prev;
};

// Forward declarations
class CBitInput;

// CHuffman - Base Huffman coding class
class CHuffman {
public:
    CHuffman();
    virtual ~CHuffman();

    void IncrementWeight(HUFFNODE* node);
    HUFFNODE* AllocNode(size_t size);

protected:
    HUFFNODE m_nodes[256];  // Huffman nodes
    void* m_list1;  // offset +12368 (simplified)
    void* m_list2;  // offset +12380 (simplified)
};

// CHuffmanDecoder - Huffman decoder
class CHuffmanDecoder : public CHuffman {
public:
    CHuffmanDecoder();
    virtual ~CHuffmanDecoder();

    int DecodeSymbol(CBitInput* input);
};

// CHuffmanEncoder - Huffman encoder
class CHuffmanEncoder : public CHuffman {
public:
    CHuffmanEncoder();
    virtual ~CHuffmanEncoder();

    void EncodeSymbol(int symbol);
};
