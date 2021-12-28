#include <iostream>
#include <string>

#include <map>
#include <algorithm>
#include <vector>
#include <queue>

void printCode(std::map<char, int> map) { //just to see what value each char has
    for (const auto&[key, value]: map) {
        std::cout << key << " : " << value << std::endl;
    }
    std::cout << "-------------------------------------------" << std::endl;
}

struct TreeNode{
    int freq;
    char letter;
    struct TreeNode *right;
    struct TreeNode *left;
};

TreeNode * getNode(int freq, char letter, TreeNode *right, TreeNode *left){ //create new leaf for tree
    TreeNode *node = new TreeNode();
    node->freq = freq;
    node->letter = letter;
    node->left = left;
    node->right = right;

    return node;
}

struct comparator { //to order heap by comparing frequency of the nodes
    bool operator()(TreeNode *left, TreeNode *right) {
        return left->freq > right->freq;
    }

};

void createHuffman(TreeNode *root, std::string str, std::map<char, std::string> &huffmanCode){

    if(root == nullptr){ //if root points at nothing return nothing
        return;
    }
    if (!root->left && !root->right) { // if root has no left or right child return the string value
        huffmanCode[root->letter] = str;
    }

    createHuffman(root->left, str + "0", huffmanCode);  // travel to the left child add 0 to string
    createHuffman(root->right, str + "1", huffmanCode); // travel to right child add 1 to string
}

void minHeap(std::map<char, int> list) {
    std::priority_queue<TreeNode*, std::vector<TreeNode*>, comparator> minimumHeap;
    for (auto val: list){
        minimumHeap.push(getNode(val.second, val.first, nullptr, nullptr));
    }

    while(!minimumHeap.size() != 1){ //repeat until only one node is left
//remove the two nodes with minimum value from minimumHeap and save them in left and right node
        TreeNode *left = minimumHeap.top();
        minimumHeap.pop();
        TreeNode *right = minimumHeap.top();
        minimumHeap.pop();
// add value together in sum and add it to minimumHeap
        int sum = left->freq + right->freq;
        minimumHeap.push(getNode(sum, '\0', right, left));

    }
    TreeNode *root = minimumHeap.top(); //last node becomes root of tree
    std::map<char, std::string> huffmanCode;// map to store huffman code for each char
    createHuffman(root, "", huffmanCode);

    for(const auto &pair : huffmanCode){ //print out each char and the huffman code belonging to it
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
}

std::map<char, int> sortingChar(std::string text) {
    std::map<char, int> list;
    std::transform(text.begin(), text.end(), text.begin(), toupper);
    //enter chars from string in to a map and count the frequency of the char
    for (char c : text) {
        if (c == ' ') {
            continue;
        }
        if (list.empty()) {             // if map is empty enter == new entry no matter which char
            list.insert(std::pair<char, int>(c, 1));

        } else {   //map not empty
            if (list.find(c) == list.end()) {       // look for char in entire map, if it doesn't exist new char entry
                list.insert(std::make_pair(c, 1));
            } else {      //char does exist increase value of char
                auto it = list.find(c);
                //if (it != list.end()) {
                it->pair::second++;
                //}
            }
        }
    }
    printCode(list);
    minHeap(list);

    return list;
}

int main() {
    // std::string str;
    // std::getline(std::cin, str);
    sortingChar("hello world");

    return 0;
}
