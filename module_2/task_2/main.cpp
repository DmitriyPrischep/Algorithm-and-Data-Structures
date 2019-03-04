#include <iostream>
#include <stack>
#include <vector>

using namespace std;

template<class T>
struct Node final
{
public:
    Node(const T value, Node* parent) :
        parent(parent),
        key(value),
        left(nullptr),
        right(nullptr)
    {}
    Node* right;
    Node* parent;
    Node* left;
    T key;
};

template<class T>
class BinaryTree final
{
public:
    BinaryTree() : root(nullptr) {}
    BinaryTree(const BinaryTree& tree) = delete;
    BinaryTree(const BinaryTree&& tree) = delete;
    BinaryTree& operator =(const BinaryTree& tree) = delete;
    BinaryTree& operator =(const BinaryTree&& tree) = delete;
    ~BinaryTree();

    void insert(const T data);
    void printInOrder(std::vector<T> &result);
    void visit(const Node<T>* node);
private:
    Node<T>* root;
};



template<class T>
void BinaryTree<T>::printInOrder(std::vector<T>& result)
{
    Node<T> *current = root;
    std::stack<Node<T> *> stack;
    while (!stack.empty() || current != nullptr){
        if(current != nullptr){
            stack.push(current);
            current = current->left;
        } else {
            current = stack.top();
            stack.pop();
            result.push_back(current->key);
            current = current->right;
        }
    }
}

template<class T>
void BinaryTree<T>::insert(const T data)
{
    if(root == nullptr){
        root = new Node<T>(data, nullptr);
        return;
    }
    Node<T>* current = root;
    Node<T>* parent = root;

    while(current != nullptr){
        parent = current;
        if(data < current->key){
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if(data < parent->key){
        parent->left = new Node<T>(data, parent);
    } else {
        parent->right = new Node<T>(data, parent);
    }
}

template<class T>
BinaryTree<T>::~BinaryTree()
{
    std::stack<Node<T> *> stack;
    Node<T>* current = root;
    Node<T>* lastNode = nullptr;
    Node<T>* peek = nullptr;

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
    BinaryTree<int> tree;
    size_t countNode = 0;
    cin >> countNode;
    std::vector<int> orderList;
    int input = 0;
    for(size_t i = 0; i < countNode; i++){
        cin >> input;
        tree.insert(input);
    }
    tree.printInOrder(orderList);

    for(size_t i = 0; i < orderList.size(); i++){
        cout << orderList[i] << " ";
    }
    return 0;
}
