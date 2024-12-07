#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
using namespace std;

struct Node {
    char id;
    Node* leftmostchild;
    Node* rightsibling;
};

Node* makeNode(char id) {
    Node* q = new Node;
    q->id = id;
    q->leftmostchild = nullptr;
    q->rightsibling = nullptr;
    return q;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

Node* buildTree(const char* value) {
    Node* stack[100];
    int top = -1;

    for (int i = 0; value[i] != '\0'; i++) {
        char c = value[i];

        if (isalpha(c) || isdigit(c)) {
            stack[++top] = makeNode(c);
        } else if (isOperator(c)) {
            Node* opNode = makeNode(c);
            opNode->rightsibling = stack[top--];
            opNode->leftmostchild = stack[top--];
            stack[++top] = opNode;
        }
    }
    return stack[top];
}

void inOrder(Node* root) {
    if (root == nullptr) return;
    if (isOperator(root->id)) cout << "( ";
    inOrder(root->leftmostchild);
    cout << root->id << " ";
    inOrder(root->rightsibling);
    if (isOperator(root->id)) cout << ") ";
}

void preOrder(Node* root) {
    if (root == nullptr) return;
    cout << root->id << " ";
    preOrder(root->leftmostchild);
    preOrder(root->rightsibling);
}

void postOrder(Node* root) {
    if (root == nullptr) return;
    postOrder(root->leftmostchild);
    postOrder(root->rightsibling);
    cout << root->id << " ";
}

int main() {
    const char value[] = "a5*b6^c*d/-hf-e12/^*+";

    Node* root = buildTree(value);

    cout << "Trung to: ";
    inOrder(root);
    cout << endl;

    cout << "Tien to: ";
    preOrder(root);
    cout << endl;

    cout << "Hau to: ";
    postOrder(root);
    cout << endl;

    return 0;
}
