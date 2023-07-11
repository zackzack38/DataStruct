#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include <cstddef>
#include <string>
#include <iostream>
#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include <map>
#include <iterator>
#include <stack>

class HuffmanTree : HuffmanTreeBase
{
public:
    //HuffmanTree();
    //~HuffmanTree();
    std::string compress(const std::string inputStr);
    std::string serializeTree() const;
    std::string decompress(const std::string inputCode, const std::string serializedTree);
    void endMe(HuffmanNode *node);
    HuffmanNode *tipTop;

private:
    std::string compressedInput;
    std::string serializedOutput;
    void find(const HuffmanNode *point, std::map<int, std::string> &myMap, std::string out);
    void serializeTreeButCooler(const HuffmanNode *point, std::string &out) const;
};

#endif // HUFFMANTREE_H