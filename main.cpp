#include <iostream>
#include <string>

#include <map>
#include <algorithm>
#include <vector>
#include <queue>

void printCode(std::map<char, int> map) { //only there to see frequency of chars
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
    auto *node = new TreeNode();
    node->freq = freq;
    node->letter = letter;
    node->left = left;
    node->right = right;

    return node;
}

struct comparator {
    bool operator()(TreeNode *left, TreeNode *right) {
        return left->freq > right->freq;
    }

};

void createHuffman(TreeNode *root, std::string str, std::map<char, std::string> &huffmanCode){ //create code

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

    std::priority_queue<TreeNode*, std::vector<TreeNode*>, comparator> minimumHeap; //priority queue for nodes

    for (auto val: list){ //enter char with frequency in minimumHeap, by creating Nodes
        minimumHeap.push(getNode(val.second, val.first, nullptr, nullptr));
    }

    while(!minimumHeap.size() != 1){ // repeat until only one node is left

        // remove the Nodes with minimal value and temporarily save them
        TreeNode *left = minimumHeap.top();
        minimumHeap.pop();
        TreeNode *right = minimumHeap.top();
        minimumHeap.pop();
        // add the nodes together and add new value as a new Node into minimumHeap
        int sum = left->freq + right->freq;
        minimumHeap.push(getNode(sum, '\0', right, left));

    }
    // last Node is root
    TreeNode *root = minimumHeap.top();
    std::map<char, std::string> huffmanCode; //map for huffman code
    createHuffman(root, "", huffmanCode);

    for(const auto &pair : huffmanCode){ //print huffman code
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
                it->pair::second++;
            }
        }
    }
    printCode(list); // to see what frequency each char has
    minHeap(list); // start of creation of tree

    return list;
}

int main() {
   // std::string str;
   // std::getline(std::cin, str);


    sortingChar("hello world");

    return 0;
}
