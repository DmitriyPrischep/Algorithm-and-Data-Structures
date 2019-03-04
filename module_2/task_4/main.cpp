#include <iostream>

using namespace std;

template<class T>
struct Node{
    Node(const T key) :
        key(key),
        left(nullptr),
        right(nullptr),
        height(1),
        cnt_node(1)
    {}
    ~Node();
    T key;
    size_t height;
    size_t cnt_node;
    Node* left;
    Node* right;
};

template<class T>
Node<T>::~Node() {
    delete left;
    delete right;
}

template<class T>
class AVLTree
{
public:
    AVLTree() : root(nullptr){}
    ~AVLTree();

    void insert(const T& data);
    void remove(const T& data);
    const T find_k_statistic(const size_t &k_statistic);


private:
    Node<T>* insert_node(Node<T> *node, const T& data);
    Node<T>* remove_node(Node<T>* node, const T& data);
    Node<T>* remove_min(Node<T>* tree, Node<T> *&parent);

    Node<T>* find_min(Node<T>* node);
    size_t height(const Node<T>* node);
    size_t count(const Node<T>* node);

    Node<T>* balance(Node<T>* node);
    int balance_factor(const Node<T>* node);
    void fix_height(Node<T>* node);
    void fix_cnt_node(Node<T>* node);

    Node<T>* rotate_right(Node<T>* node);
    Node<T>* rotate_left(Node<T>* node);

    Node<T>* root;
};

template<class T>
size_t AVLTree<T>::count(const Node<T>* node){
    return node == nullptr ? 0 : node->cnt_node;
}

template<class T>
void AVLTree<T>::fix_cnt_node(Node<T>* node) {
    size_t left_count = count(node->left);
    size_t right_count = count(node->right);
    node->cnt_node = left_count + right_count + 1;
}

template<class T>
size_t AVLTree<T>::height(const Node<T> *node)
{
    return node == nullptr ? 0 : node->height;
}

template<class T>
void AVLTree<T>::fix_height(Node<T>* node)
{
    size_t height_left = height(node->left);
    size_t height_right = height(node->right);
    node->height = (height_left > height_right ? height_left : height_right) + 1;
}

template<class T>
int AVLTree<T>::balance_factor(const Node<T>* node)
{
    return height(node->right) - height(node->left);
}

template<class T>
Node<T>* AVLTree<T>::rotate_right(Node<T> *node)
{
    Node<T>* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    fix_height(node);
    fix_cnt_node(node);
    fix_height(temp);
    fix_cnt_node(temp);
    return temp;
}

template<class T>
Node<T>* AVLTree<T>::rotate_left(Node<T> *node)
{
    Node<T>* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    fix_height(node);
    fix_cnt_node(node);
    fix_height(temp);
    fix_cnt_node(temp);
    return temp;
}

template<class T>
Node<T>* AVLTree<T>::balance(Node<T>* node)
{
    fix_height(node);
    fix_cnt_node(node);
    if(balance_factor(node) == 2){
        if(balance_factor(node->right) < 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    if(balance_factor(node) == -2){
        if(balance_factor(node->left) > 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    return node;
}

template<class T>
void AVLTree<T>::insert(const T& data) {
    root = insert_node(root, data);
}

template<class T>
Node<T>* AVLTree<T>::insert_node(Node<T>* node, const T& data)
{
    if(node == nullptr){
        return new Node<T>(data);
    }
    if(data < node->key){
        node->left = insert_node(node->left, data);
    } else {
        node->right = insert_node(node->right, data);
    }
    return balance(node);
}

template<class T>
void AVLTree<T>::remove(const T& data) {
    root = remove_node(root, data);
}

template<class T>
Node<T>* AVLTree<T>::remove_node(Node<T>* node, const T& data){
    if(node == nullptr){
        return nullptr;
    }

    if(data < node->key){
        node->left = remove_node(node->left, data);
    } else if (data > node->key) {
        node->right = remove_node(node->right, data);
    } else {
        Node<T>* left = node->left;
        Node<T>* right = node->right;
        delete node;
        if(right == nullptr)
            return left;

        Node<T>* min;
        Node<T>* new_node;
        if(node->left->height > node->right->height){
            new_node = remove_min(right, min);
            min->right = new_node;
            min->left = left;
        } else {
            new_node = remove_min(left, min);
            min->left = new_node;
            min->right = right;

        }
        return balance(min);
    }
    return balance(node);
}

template<class T>
Node<T>* AVLTree<T>::remove_min(Node<T>* tree, Node<T>*& parent) {
    if(tree->left == nullptr){
        parent = tree;
        return tree->right;
    }
    tree->left = remove_min(tree->left, parent);
    return balance(tree);
}

template<class T>
Node<T>* AVLTree<T>::find_min(Node<T>* node) {
    return node->left == nullptr ? node : find_min(node->left);
}

template<class T>
const T  AVLTree<T>::find_k_statistic(const size_t& k_statistic)
{
    T result = 0;
    if(k_statistic < count(root)){
        Node<T>* current = root;
        size_t index = count(root->left);
        while (index != k_statistic){
            if(k_statistic > index) {
                current = current->right;
                index += 1 + count(current->left);
            } else {
                current = current->left;
                index -= 1 + count(current->right);
            }
        }
        result = current->key;
    }
    return result;
}

template<class T>
AVLTree<T>::~AVLTree()
{
    delete root;
}

int main()
{
    size_t count_node;
    std::cin >> count_node;

    AVLTree<int> tree;
    for(size_t i = 0; i < count_node; i++){
        int data = 0;
        size_t k = 0;
        std::cin >> data >> k;
        if (data < 0) {
            tree.remove(-data);
        } else {
            tree.insert(data);
        }
        std::cout << tree.find_k_statistic(k) << std::endl;
    }
    return 0;
}
