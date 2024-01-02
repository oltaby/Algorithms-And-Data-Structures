#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <functional> 
using namespace std; 

struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode *left, *right;

    HuffmanNode(char character, int frequency) : character(character), frequency(frequency), left(nullptr), right(nullptr) {}
};

struct CompareNode {
    bool operator()(HuffmanNode* const & left, HuffmanNode* const & right) {
        return left->frequency > right->frequency; 
    }
};

void generateCodes(HuffmanNode* node, string code, unordered_map<char, string>& huffmanCode) {
    if (node == nullptr) {
        return;
    }

    if (!node->left && !node->right) {
        huffmanCode[node->character] = code;
    }

    generateCodes(node->left, code + "0", huffmanCode);
    generateCodes(node->right, code + "1", huffmanCode);
}


void huffman_coding(string text){
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNode> minPq;
    unordered_map<char,pair<int,int>> map; 

    for(char s : text){
        map[s].first++;
    }

    for (const auto& pair : map) {
        minPq.push(new HuffmanNode(pair.first, pair.second.first)); 
    }

    
   while (minPq.size() > 1) {
        HuffmanNode* left = minPq.top(); minPq.pop();
        HuffmanNode* right = minPq.top(); minPq.pop();

        HuffmanNode* sum = new HuffmanNode('$', left->frequency + right->frequency);
        sum->left = left;
        sum->right = right;
        minPq.push(sum);
    }

    HuffmanNode* root = minPq.top();

    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    int totalBits = 0;
    for (char ch : text) {
        totalBits += huffmanCode[ch].length();  
    }

    string compressedText = "";
    for (char ch : text) {
        compressedText += huffmanCode[ch];
    }

    cout << "Original text: " << text << endl;
    cout << "Compressed text: " << compressedText << endl;
    cout << "Total bits required: " << compressedText.length() << endl;  
    cout << "-----" << endl;  
}

int main() {
    string test1 = "MATEKFELELETEMKETTESLETT";
    string test2 = "EMESE MAI SMSE NEM NAIV MESE";
    string test3 = "MEDWKNCFOEJRNV";
    huffman_coding(test1);
    huffman_coding(test2);
    huffman_coding(test3);
    return 0;
}
