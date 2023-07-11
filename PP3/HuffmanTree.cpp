#include "HuffmanTree.hpp"
#include "TestStrings.hpp"
// Includes:
// const std::string turing       turingCode        turingTree
// const std::string dijkstra     dijkstraCode      dijkstraTree
// const std::string wikipedia    wikipediaCode     wikipediaTree
// const std::string constitution constitutionCode  constitutionTree
std::string HuffmanTree::compress(const std::string inputStr)
{
    serializedOutput = "";
    std::map<int, int> myMap; //<ascii value, frequency>
    std::map<int, int>::iterator it;
    int len = inputStr.length();

    for (int i = 0; i < len; i++) // Increments the frequency
    {
        it = myMap.find(int(inputStr[i]));
        myMap[int(inputStr[i])] = it->second + 1;
    }

    if (it == myMap.end()) // Check if empty list
    {
        std::cout << "nonexistent\n";
    }

    HeapQueue<HuffmanNode *, HuffmanNode::Compare> priorityQ; // <Node, Compare> Something to to with comparison no idea how to implement | isLess(a,b): Return true if a < b and false otherwise.
    for (it = myMap.begin(); it != myMap.end(); ++it)
    {
        if (it->second != 0)
        {
            HuffmanNode *neo = new HuffmanNode(it->first, it->second); // create a one-node binary tree containing the  character and the frequency as its priority
            priorityQ.insert(neo);                                     // Inserts into  priority queue
        }
    }

    while (priorityQ.size() != 1)
    {
        HuffmanNode *t1 = priorityQ.min(); // Dequeue two trees t1 and t2
        priorityQ.removeMin();
        HuffmanNode *t2 = priorityQ.min();
        priorityQ.removeMin();
        HuffmanNode *t = new HuffmanNode('\0', (t1->getFrequency() + t2->getFrequency()), nullptr, t1, t2); // priorityQ(t) = priorityQ(t1) + priorityQ(t2);
        t1->parent = t;
        t2->parent = t;
        priorityQ.insert(t); // insert t in its proper location in the priority queue
    }

    std::map<int, std::string> finalMap; //<ascii value, binary>
    std::map<int, std::string>::iterator fit;
    std::string codeWord = "";

    tipTop = priorityQ.min();                         // Used for serialize
    serializeTreeButCooler(tipTop, serializedOutput); // Serialized input here
    for (it = myMap.begin(); it != myMap.end(); ++it)
    {
        if (it->second != 0)
        {
            find(priorityQ.min(), finalMap, codeWord);
        }
    }

    std::string output = "";
    for (auto i : inputStr)
    {
        output += finalMap[i];
    }
    compressedInput = output; // DELETE ME
    return output;
}

void HuffmanTree::serializeTreeButCooler(const HuffmanNode *point, std::string &out) const
{
    if (point != nullptr)
    {
        serializeTreeButCooler(point->left, out);
        serializeTreeButCooler(point->right, out);
        if (point->isBranch())
        {
            out = out + "B";
        }
        else if (point->isLeaf())
        {
            out = out + "L" + point->getCharacter();
        }
    }
    else
    {
        return; // soup
    }
}

// Serialize the tree using the above method. We do not need the frequency values to rebuild the tree, just the characters on the leaves and where the branches are in the post order. Done with recursion above
std::string HuffmanTree::serializeTree() const
{
    return serializedOutput;
}

// Given a string created with the compress method and a serialized version of the tree, return the decompressed original string
std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree)
{
    std::string output = "";
    std::stack<HuffmanNode *> priorityS;
    HuffmanNode *topTip;
    int test = 0;
    for (auto soup : serializedTree)
    {
        if(test == 1) // L means to add the next char
        {
            test = 0;
            HuffmanNode *neo = new HuffmanNode(soup, 0);
            priorityS.push(neo);
        }else if (soup == 'L')
        {
            test = 1;
            continue; // Move on
        }
        else if ((soup != 'B') && (soup != 'L'))
        {
            HuffmanNode *neo = new HuffmanNode(soup, 0);
            priorityS.push(neo);
        }
        else if (soup == 'B')
        {
            HuffmanNode *t1 = priorityS.top(); // Dequeue two trees t1 and t2
            priorityS.pop();
            HuffmanNode *t2 = priorityS.top();
            priorityS.pop();
            HuffmanNode *t = new HuffmanNode('\0', 0, nullptr, t2, t1);
            t1->parent = t;
            t2->parent = t;
            priorityS.push(t);
        }
    }

    topTip = priorityS.top();
    priorityS.pop();
    HuffmanNode *point = topTip;
    for (auto soup : inputCode)
    {
        if (soup == '0') // find logic go until the char is found
        {
            point = point->left;
        }
        else if (soup == '1')
        {
            point = point->right;
        }
        if (point->isLeaf()) // I can't read, if it's 1 it goes
        {
            output += point->getCharacter();
            point = topTip;
        }
    }
    return output;
}

void HuffmanTree::find(const HuffmanNode *point, std::map<int, std::string> &myMap, std::string out)
{
    if (point != nullptr)
    {
        if (point->isLeaf())
        {
            myMap[(int)point->getCharacter()] = out;
        }
        find(point->left, myMap, out + "0");
        find(point->right, myMap, out + "1");
    }
    else
    {
        return; // soup
    }
}