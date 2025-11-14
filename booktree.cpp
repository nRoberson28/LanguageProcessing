#include "booktree.h"

int max(int a, int b) {
    return a > b ? a : b;
}

BookTree::BookTree() {
    m_root = nullptr;
}

void BookTree::deleteTree(BNode* node) {
    if (!node) return;
    deleteTree(node->m_left);
    deleteTree(node->m_right);
    delete node;
}

BookTree::~BookTree() {
    deleteTree(m_root);
}

void BookTree::loadData(Book data[], int arrayLength){
    for (int i = 0; i < arrayLength; i++) {
        if (!insert(data[i].m_title, data[i].m_author, data[i].m_text)) {
            cout << "failure to insert" << endl;
            return;
        }
    }
}

bool BookTree::insert(string title, string author, string text){
    if (!m_root) {
        m_root = new BNode(title, author, text);
        return true;
    }

    m_root = splay(m_root, title);

    if (m_root->m_title == title) return false;

    BNode* newBNode = new BNode(title, author, text);

    if (title < m_root->m_title) {
        newBNode->m_right = m_root;
        newBNode->m_left = m_root->m_left;
        m_root->m_left = nullptr;
    }
    else {
        newBNode->m_left = m_root;
        newBNode->m_right = m_root->m_right;
        m_root->m_right = nullptr;
    }

    m_root = newBNode;
    return true;
}

int BookTree::findFrequency(string title, string word){
    m_root = splay(m_root, title);
    if (m_root && m_root->m_title == title) {
        return m_root->findFrequency(word);
    }
    return 0;
}

int BookTree::searchCount(string title, string word){
    m_root = splay(m_root, title);
    if (m_root && m_root->m_title == title) {
        return m_root->searchCount(word);
    }
    return 0;
}

int BookTree::getTextTreeHeight(string title){
    BNode* curr = m_root;

    while (curr) {
        if (curr->m_title == title) {
            m_root = splay(m_root, title);
            return m_root->getTextTreeHeight();
        }
        if (title < curr->m_title) curr = curr->m_left;
        else curr = curr->m_right;
    }
    return -1;
}

string BookTree::getRootKey(){
	// implementation is provided
	// do not modify this function
	return m_root->m_title;
}

bool BookTree::removeWord(string title, string word){
    if (!m_root) return false;
    m_root = splay(m_root, title);
    if (!m_root) return false;
    if (m_root->m_title != title) return false;

    bool success = m_root->m_tree.remove(word);
    return success;
}

void BookTree::dump(bool verbose) const{
    cout << "m_root is " << m_root->m_title << endl;
	dumpHelper(m_root, verbose);
    cout << endl;
}

void BookTree::dumpHelper(BNode* root, bool verbose) const{
    if (root != nullptr){
        if (verbose){
            cout << "(";
            dumpHelper( root->m_left, verbose );
            cout << root->m_title << ":" << root->m_author;
			root->m_tree.dump();
            dumpHelper( root->m_right, verbose );
            cout << ")";
        }
        else{
            cout << "(";
            dumpHelper( root->m_left, verbose );
            cout << root->m_title;
            dumpHelper( root->m_right, verbose );
            cout << ")";
        }
    }
}

BNode* BookTree::rightRotate(BNode* x) {
    BNode* y = x->m_left;
    x->m_left = y->m_right;
    y->m_right = x;
    return y;
}

BNode* BookTree::leftRotate(BNode* x) {
    BNode* y = x->m_right;
    x->m_right = y->m_left;
    y->m_left = x;
    return y;
}

BNode* BookTree::splay(BNode* root, string title) {
    if (!root || root->m_title == title)
        return root;

    if (title < root->m_title) {
        if (!root->m_left) return root;

        // Zig-Zig
        if (title < root->m_left->m_title) {
            root->m_left->m_left = splay(root->m_left->m_left, title);
            root = rightRotate(root);
        }
        // Zig-Zag
        else if (title > root->m_left->m_title) {
            if (root->m_left) {
                root->m_left->m_right = splay(root->m_left->m_right, title);
                if (root->m_left && root->m_left->m_right)
                    root->m_left = leftRotate(root->m_left);
            }
        }

        return (!root->m_left) ? root : rightRotate(root);
    }

    if (!root->m_right)
        return root;

    // Zag-Zag
    if (title > root->m_right->m_title) {
        root->m_right->m_right = splay(root->m_right->m_right, title);
        root = leftRotate(root);
    }
    // Zag-Zig
    else if (title < root->m_right->m_title) {
        if (root->m_right) {
            root->m_right->m_left = splay(root->m_right->m_left, title);
            if (root->m_right && root->m_right->m_left)
                root->m_right = rightRotate(root->m_right);
        }
    }

    return (!root->m_right) ? root : leftRotate(root);
}

//////////////////////////////////////////////////////////////////////////////////////////////
WordTree::~WordTree(){
    deleteTree(m_root);
}

void WordTree::deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->m_left);
    deleteTree(node->m_right);
    delete node;
}

Node* WordTree::find(const string& word){
    Node* curr = m_root;
     while (curr) {
         if (word == curr->getValue()) {
             return curr;
         }
         if (word < curr->getValue())
             curr = curr->m_left;
         else
             curr = curr->m_right;
     }
    return nullptr;
}

Node* WordTree::BSTRemove(Node* root, const string& word, bool &success) {
    if (!root) return root;

    if (word < root->m_word) {
        root->m_left = BSTRemove(root->m_left, word, success);
    }
    else if (word > root->m_word) {
        root->m_right = BSTRemove(root->m_right, word, success);
    }
    else {
        success = true;

        if (!root->m_left && !root->m_right) {
            delete root;
            return nullptr;
        }
        if (!root->m_left) {
            Node* temp = root->m_right;
            delete root;
            return temp;
        }
        if (!root->m_right) {
            Node* temp = root->m_left;
            delete root;
            return temp;
        }
        else {
            Node* temp = minValueNode(root->m_right);

            root->m_word = temp->m_word;
            root->m_count = temp->m_count;

            root->m_right = BSTRemove(root->m_right, temp->m_word, success);
        }
    }
    return root;
}

Node* WordTree::minValueNode(Node* node) {
    Node* curr = node;
    while (curr->m_left) {
        curr = curr->m_left;
    }
    return curr;
}

int WordTree::getHeight(Node* node) {
    if (!node) return -1;
    return node->m_height;
}

int WordTree::BF(Node* node) {
    if (!node) return 0;
    return getHeight(node->m_left) - getHeight(node->m_right);
}

bool WordTree::remove(const string& word){
    if (!m_root) return false;
    bool success = false;
    m_root = BSTRemove(m_root, word, success);
    return success;
}

Node* WordTree::rightRotate(Node* y) {
    if (!y || !y->m_left) return y;
    Node* x = y->m_left;
    Node* T2 = x->m_right;

    x->m_right = y;
    y->m_left = T2;

    y->m_height = 1 + max(getHeight(y->m_left), getHeight(y->m_right));
    x->m_height = 1 + max(getHeight(x->m_left), getHeight(x->m_right));

    return x;
}

Node* WordTree::leftRotate(Node* x) {
    if (!x || !x->m_right) return x;
    Node* y = x->m_right;
    Node* T2 = y->m_left;

    y->m_left = x;
    x->m_right = T2;

    y->m_height = 1 + max(getHeight(y->m_left), getHeight(y->m_right));
    x->m_height = 1 + max(getHeight(x->m_left), getHeight(x->m_right));

    return y;
}

Node* WordTree::insertHelper(Node* root, const string& word) {
    if (!root) {
        Node* newNode = new Node(word);
        newNode->m_height = 0;
        newNode->m_count = 1;
        return newNode;
    }

    // Standard BST insertion
    if (word < root->m_word) {
        root->m_left = insertHelper(root->m_left, word);
    }
    else if (word > root->m_word) {
        root->m_right = insertHelper(root->m_right, word);
    }
    else {
        root->m_count++;
        return root;
    }

    // Update height
    root->m_height = 1 + max(getHeight(root->m_left), getHeight(root->m_right));

    // Get balance factor
    int balance = getHeight(root->m_left) - getHeight(root->m_right);

    // Left-heavy cases
    if (balance > 1) {
        // Left-Left case
        if (word < root->m_left->m_word) {
            return rightRotate(root);
        }
        // Left-Right case
        else {
            root->m_left = leftRotate(root->m_left);
            return rightRotate(root);
        }
    }

    // Right-heavy cases
    if (balance < -1) {
        // Right-Right case
        if (word > root->m_right->m_word) {
            return leftRotate(root);
        }
        // Right-Left case
        else {
            root->m_right = rightRotate(root->m_right);
            return leftRotate(root);
        }
    }

    return root;
}

void WordTree::insert(const string& word) {
        m_root = insertHelper(m_root, word);
}

int WordTree::searchCount(string word){
    int count = 0;
    Node* curr = m_root;
    while (curr) {
        count++;
        if (word == curr->getValue()) {
            return count;
        }
        if (word < curr->getValue()) {
            curr = curr->m_left;
        }
        else {
            curr = curr->m_right;
        }
    }
    return count;
}

int WordTree::getTreeHeight(){
    // implementation is provided
	// do not modify this function
    return m_root->m_height;
}

void WordTree::dump(std::ostream& ostr){
    dump(m_root, ostr);
}

void WordTree::dump(Node* aNode, std::ostream& ostr){
    if (aNode != nullptr){
        ostr << "[";
        dump(aNode->m_left, ostr);//first visit the left child
        ostr << aNode->m_word << ":" << aNode->m_count << ":" << aNode->m_height;//second visit the node itself
        dump(aNode->m_right, ostr);//third visit the right child
        ostr << "]";
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
BNode::BNode() {
    m_left = nullptr;
    m_right = nullptr;
    m_title = "";
    m_author = "";
}

BNode::BNode(string title, string author, string text) {
    m_left = nullptr;
    m_right = nullptr;
    m_title = title;
    m_author = author;
    parseText(text);
}

void BNode::parseText(string text) {
    string currWord;
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        if (c == DELIMITER) {
            if (!currWord.empty())
                m_tree.insert(currWord);
            currWord = "";
        } else {
            currWord += c;
        }
    }
    if (!currWord.empty())
        m_tree.insert(currWord);
}


BNode::~BNode()= default;

int BNode::findFrequency(string word){
    Node* temp = m_tree.find(word);
    if (temp == nullptr) return 0;
    return temp->getFrequency();
}

int BNode::searchCount(string word){
    return m_tree.searchCount(word);
}

int BNode::getTextTreeHeight(){
    return m_tree.getTreeHeight();
}