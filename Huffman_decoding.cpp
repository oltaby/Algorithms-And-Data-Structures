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

void huffman_decoding(string code, HuffmanNode* root){
    unordered_map<char, string> huffmanCode; 
    generateCodes(root,"", huffmanCode); 

    for(const auto& pair : huffmanCode){
        cout<< "Character: " << pair.first <<" code: "<< pair.second << endl; 
    }

    string final_string = "";
    string current_code = "";
    for(char s : code){
        current_code += s;
        for(const auto& pair : huffmanCode){
            if(pair.second == current_code ){
                final_string += pair.first;
                current_code = "";
            }    
        }
    }

    cout << "Original code: " << code << endl;
    cout << "Decompressed code: " << final_string << endl;
}

int main() {
    string code1 = "01111100010011010";
    unordered_map<char, int> map; 
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNode> minPq;

    minPq.push(new HuffmanNode('R',2));
    minPq.push(new HuffmanNode('T',4));
    minPq.push(new HuffmanNode('O',5));
    minPq.push(new HuffmanNode('G',7));
    minPq.push(new HuffmanNode('E',13));
    minPq.push(new HuffmanNode('A',17));

    while (minPq.size() > 1) {
        HuffmanNode* left = minPq.top(); minPq.pop();
        HuffmanNode* right = minPq.top(); minPq.pop();

        HuffmanNode* sum = new HuffmanNode('$', left->frequency + right->frequency);
        sum->left = left;
        sum->right = right;
        minPq.push(sum);
    }
    HuffmanNode* root = minPq.top();

    huffman_decoding(code1, root);
    return 0;
}
