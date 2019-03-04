#include <iostream>
#include <vector>
#include <stack>

using namespace std;

template<class A, class B>
struct Node
{
    Node(const A key, const B priority):
        key(key),
        priority(priority),
        left(nullptr),
        right(nullptr),
        parent(nullptr)
    {}
    Node(const A value, Node* parent) :
        key(value),
        parent(parent),
        left(nullptr),
        right(nullptr)
    {}

    Node* parent;
    Node* left;
    Node* right;
    A key;
    B priority;
};

template<class A, class B>
class Treap
{
public:
    Treap() : root(nullptr) {}
    Treap(const Treap& tree) = delete;
    Treap(const Treap&& tree) = delete;
    Treap& operator =(const Treap& tree) = delete;
    Treap& operator =(const Treap&& tree) = delete;
    ~Treap();

    void insert(const A& data, const B& priority);
    size_t depth();

private:
    void split(Node<A,B>* current, const A key, Node<A,B>*& left_tree, Node<A,B>*& right_tree);
    size_t depth_tree(Node<A,B> * node);
    Node<A, B>* root;
};

template<class A, class B>
void Treap<A,B>::insert(const A &data, const B &priority)
{
    if(root == nullptr){
        root = new Node<A, B>(data, priority);
        return;
    }
    Node<A, B>* current = root;
    Node<A, B>* parent = nullptr;

    while (current != nullptr && current->priority > priority){
        parent = current;
        if(current->key > data){
            current = current->left;
        } else {
            current = current->right;
        }
    }
    Node<A, B>* new_node = new Node<A, B>(data, priority);
    if(parent != nullptr){
        parent->key > new_node->key ? parent->left = new_node : parent->right = new_node;
    } else{
        new_node->key > current->key ? new_node->left = current : new_node->right = current;
        root = new_node;
    }
    split(current, data, new_node->left, new_node->right);
}

template<class A, class B>
void Treap<A,B>::split(Node<A, B> *current, const A key, Node<A, B>*& left, Node<A, B>*& right)
{
    if(current == nullptr){
        left = right = nullptr;
    } else if(current->key <= key){
        split(current->right, key, current->right, right);
        left = current;
    } else {
        split(current->left, key, left, current->left);
        right = current;
    }
}

template<class A, class B>
size_t Treap<A, B>::depth()
{
    return depth_tree(root);
}

template<class A, class B>
size_t Treap<A,B>::depth_tree(Node<A, B> *node)
{
    if(node == nullptr)
        return 0;
    int left_depth = 0;
    int right_depth = 0;
    if (node->left != nullptr){
        left_depth = depth_tree(node->left);
    }else
        left_depth = -1;
    if (node->right != nullptr) {
        right_depth = depth_tree(node->right);
    }else
        right_depth = -1;
    int max = left_depth > right_depth ? left_depth : right_depth;
    return max + 1;

}

template<class A, class B>
Treap<A,B>::~Treap()
{
    std::stack<Node<A,B> *> stack;
    Node<A,B>* current = root;
    Node<A,B>* lastNode = nullptr;
    Node<A,B>* peek = nullptr;

    while (!stack.empty() || current != nullptr){
        if(current != nullptr){
            stack.push(current);
            current = current->left;
        } else {
            peek = stack.top();
            if(peek->right != nullptr && lastNode != peek->right){
                current = peek->right;
            } else {
                if (stack.top()->parent == nullptr){
                    stack.pop();
                    delete peek;
                    return;
                }
                stack.pop();
                lastNode = stack.top();
                if(lastNode->left == peek){
                    delete peek;
                    lastNode->left = nullptr;
                } else {
                    delete peek;
                    lastNode->right = nullptr;
                }
            }
        }
    }
}

template<class T>
class BinaryTree final
{
public:
    BinaryTree() : root(nullptr), height(0) {}
    BinaryTree(const BinaryTree& tree) = delete;
    BinaryTree(const BinaryTree&& tree) = delete;
    BinaryTree& operator =(const BinaryTree& tree) = delete;
    BinaryTree& operator =(const BinaryTree&& tree) = delete;
    ~BinaryTree();

    void insert(const T& data);
    size_t depth();

private:
    size_t depth_tree(Node<T, T> *root);
    Node<T, T>* root;
    size_t height;
};

template<class T>
size_t BinaryTree<T>::depth()
{
    return depth_tree(root);
}

template<class T>
size_t BinaryTree<T>::depth_tree(Node<T, T>* root)
{
    size_t depth = 0;
    std::stack<Node<T, T>*> add_nodes;
    std::stack<Node<T, T>*> path_to_root;

    add_nodes.push(root);
    while (!add_nodes.empty()) {
        root = add_nodes.top();
        if (!path_to_root.empty() && root == path_to_root.top()) {
            if (path_to_root.size() > depth)
                depth = path_to_root.size() - 1;
            path_to_root.pop();
            add_nodes.pop();
        } else {
            path_to_root.push(root);
            if (root->right != nullptr)
                add_nodes.push(root->right);
            if (root->left != nullptr)
                add_nodes.push(root->left);
        }
    }
    return depth;
}


template<class T>
void BinaryTree<T>::insert(const T &data)
{
    if(root == nullptr){
        root = new Node<T,T>(data, nullptr);
        return;
    }
    Node<T,T>* current = root;
    Node<T,T>* parent = nullptr;
    size_t temp_hgt = 0;

    while(current != nullptr){
        parent = current;
        if(data < current->key){
            current = current->left;
        } else {
            current = current->right;
        }
        temp_hgt++;
    }
    if(data < parent->key){
        parent->left = new Node<T,T>(data, parent);
    } else {
        parent->right = new Node<T,T>(data, parent);
    }
    if(temp_hgt > height)
        height = temp_hgt;
}

template<class T>
BinaryTree<T>::~BinaryTree()
{
    std::stack<Node<T,T> *> stack;
    Node<T,T>* current = root;
    Node<T,T>* lastNode = nullptr;
    Node<T,T>* peek = nullptr;

    while (!stack.empty() || current != nullptr){
        if(current != nullptr){
            stack.push(current);
            current = current->left;
        } else {
            peek = stack.top();
            if(peek->right != nullptr && lastNode != peek->right){
                current = peek->right;
            } else {
                if (stack.top()->parent == nullptr){
                    stack.pop();
                    delete peek;
                    return;
                }
                stack.pop();
                lastNode = stack.top();
                if(lastNode->left == peek){
                    delete peek;
                    lastNode->left = nullptr;
                } else {
                    delete peek;
                    lastNode->right = nullptr;
                }
            }
        }
    }
}
int main()
{
    BinaryTree<int> bi_tree;
    Treap<int, int> treap;

    size_t countNode = 0;
    cin >> countNode;
    int value = 0;
    int priority = 0;
    for(size_t i = 0; i < countNode; i++){
        cin >> value >> priority;
        bi_tree.insert(value);
        treap.insert(value, priority);
    }
    cout << bi_tree.depth() - treap.depth();
    return 0;
}
