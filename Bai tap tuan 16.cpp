#include <iostream>

using namespace std;

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
};

Node* taoNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->height = 1;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

int layChieuCao(Node* node) {
    return node == nullptr ? 0 : node->height;
}

int layCanBang(Node* node) {
    return node == nullptr ? 0 : layChieuCao(node->left) - layChieuCao(node->right);
}

Node* xoayTrai(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(layChieuCao(x->left), layChieuCao(x->right)) + 1;
    y->height = max(layChieuCao(y->left), layChieuCao(y->right)) + 1;

    return y;
}

Node* xoayPhai(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(layChieuCao(y->left), layChieuCao(y->right)) + 1;
    x->height = max(layChieuCao(x->left), layChieuCao(x->right)) + 1;

    return x;
}

Node* chenNode(Node* root, int key) {
    if (root == nullptr) return taoNode(key);

    if (key < root->key) root->left = chenNode(root->left, key);
    else if (key > root->key) root->right = chenNode(root->right, key);
    else return root; // Tránh trùng lặp khóa

    root->height = 1 + max(layChieuCao(root->left), layChieuCao(root->right));

    int canBang = layCanBang(root);

    // Trường hợp xoay phải
    if (canBang > 1 && key < root->left->key) return xoayPhai(root);

    // Trường hợp xoay trái
    if (canBang < -1 && key > root->right->key) return xoayTrai(root);

    // Trường hợp xoay trái-phải
    if (canBang > 1 && key > root->left->key) {
        root->left = xoayTrai(root->left);
        return xoayPhai(root);
    }

    // Trường hợp xoay phải-trái
    if (canBang < -1 && key < root->right->key) {
        root->right = xoayPhai(root->right);
        return xoayTrai(root);
    }

    return root;
}

void duyetInOrder(Node* root) {
    if (root != nullptr) {
        duyetInOrder(root->left);
        cout << root->key << " ";
        duyetInOrder(root->right);
    }
}

int main() {
    Node* root = nullptr;
    int daySo[] = {17, 23, 201, 98, 67, 83, 13, 23, 10, 191, 84, 58};
    int n = sizeof(daySo) / sizeof(daySo[0]);

    for (int i = 0; i < n; i++) {
        root = chenNode(root, daySo[i]);
    }

    cout << "Cay AVL (duyet In-order): ";
    duyetInOrder(root);
    cout << endl;

    return 0;
}
