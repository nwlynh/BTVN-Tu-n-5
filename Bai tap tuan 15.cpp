#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Struct dai dien moi node trong cay
struct Node {
    string title; // Tieu de cua node
    int pageCount; // So trang cua node nay
    Node* firstChild; // Con tro toi con dau tien
    Node* nextSibling; // Con tro toi anh em ke tiep

    // Constructor tao node moi
    Node(const string& t, int pages) : title(t), pageCount(pages), firstChild(nullptr), nextSibling(nullptr) {}
};

// Them mot node con vao node cha
void addChild(Node* parent, Node* child) {
    if (!parent->firstChild) {
        parent->firstChild = child;
    } else {
        Node* temp = parent->firstChild;
        while (temp->nextSibling) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = child;
    }
}

// Dem so chuong (con truc tiep cua root)
int countChapters(Node* root) {
    if (!root) return 0;
    int count = 0;
    Node* temp = root->firstChild;
    while (temp) {
        count++;
        temp = temp->nextSibling;
    }
    return count;
}

// Tim chuong dai nhat (dua tren so trang)
Node* findLongestChapter(Node* root) {
    if (!root || !root->firstChild) return nullptr;
    Node* longest = nullptr;
    int maxPages = 0;
    Node* temp = root->firstChild;
    while (temp) {
        if (temp->pageCount > maxPages) {
            maxPages = temp->pageCount;
            longest = temp;
        }
        temp = temp->nextSibling;
    }
    return longest;
}

// Cap nhat tong so trang cua node cha sau khi xoa
void updatePageCounts(Node* parent) {
    if (!parent) return;
    Node* child = parent->firstChild;
    int total = 0;
    while (child) {
        total += child->pageCount;
        child = child->nextSibling;
    }
    parent->pageCount = total;
}

// Tim va xoa mot node theo tieu de
bool deleteNode(Node* parent, const string& title) {
    if (!parent || !parent->firstChild) return false;
    Node* current = parent->firstChild;
    Node* previous = nullptr;

    while (current) {
        if (current->title == title) {
            if (previous) {
                previous->nextSibling = current->nextSibling;
            } else {
                parent->firstChild = current->nextSibling;
            }
            delete current;
            updatePageCounts(parent);
            return true;
        }
        previous = current;
        current = current->nextSibling;
    }

    current = parent->firstChild;
    while (current) {
        if (deleteNode(current, title)) return true;
        current = current->nextSibling;
    }
    return false;
}

// In cay (de debug va hinh dung)
void printTree(Node* node, int depth = 0) {
    if (!node) return;
    for (int i = 0; i < depth; ++i) cout << "  ";
    cout << "- " << node->title << " (" << node->pageCount << " pages)\n";
    Node* child = node->firstChild;
    while (child) {
        printTree(child, depth + 1);
        child = child->nextSibling;
    }
}

int main() {
    Node* root = new Node("Book", 0);

    Node* chapter1 = new Node("Chapter 1", 16);
    Node* chapter2 = new Node("Chapter 2", 32);
    Node* chapter3 = new Node("Chapter 3", 64);

    addChild(root, chapter1);
    addChild(root, chapter2);
    addChild(root, chapter3);

    addChild(chapter1, new Node("Section 1.1", 8));
    addChild(chapter1, new Node("Section 1.2", 8));
    addChild(chapter2, new Node("Section 2.1", 10));
    addChild(chapter2, new Node("Section 2.2", 22));
    addChild(chapter3, new Node("Section 3.1", 20));
    addChild(chapter3, new Node("Section 3.2", 30));
    addChild(chapter3, new Node("Section 3.3", 14));

    cout << "Initial book structure:\n";
    printTree(root);

    cout << "\nNumber of chapters: " << countChapters(root) << "\n";

    Node* longest = findLongestChapter(root);
    if (longest) {
        cout << "Longest chapter: " << longest->title << " (" << longest->pageCount << " pages)\n";
    }

    string titleToDelete = "Section 3.3";
    if (deleteNode(root, titleToDelete)) {
        cout << "\nAfter deleting '" << titleToDelete << "':\n";
        printTree(root);
    } else {
        cout << "\nNode '" << titleToDelete << "' not found!\n";
    }

    // Giai phong bo nho da cap phat (khong thuc hien trong doan nay de ngan gon)

    return 0;
}
