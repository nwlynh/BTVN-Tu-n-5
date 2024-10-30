#include <iostream>
using namespace std;

struct Node {
    int he_so;
    int bac;
    Node* next;

    Node(int he_so, int bac) : he_so(he_so), bac(bac), next(nullptr) {}
};

class DaThuc {
    Node* head;

public:
    DaThuc() : head(nullptr) {}

    void them(int he_so, int bac) {
        if (he_so == 0) return;
        
        Node* newNode = new Node(he_so, bac);
        newNode->next = head;
        head = newNode;
    }

    void in() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->he_so << "x^" << temp->bac;
            if (temp->next != nullptr) cout << " + ";
            temp = temp->next;
        }
        cout << endl;
    }

    ~DaThuc() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    DaThuc daThuc;
    int n;

    cout << "Nhap so luong hang tu cua da thuc: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int he_so, bac;
        cout << "Nhap he so va bac cua hang tu thu " << i + 1 << ": ";
        cin >> he_so >> bac;
        daThuc.them(he_so, bac);
    }

    cout << "Da thuc vua nhap la: ";
    daThuc.in();
    
    return 0;
}
