#include <iostream>
#include <string>

using namespace std;

struct FileNode {
    string Name;
    string creationTime;
    double Size;
    FileNode *next;
};

// Tao node moi
FileNode *makeNode(const string &name, const string &time, double size) {
    FileNode *newNode = new FileNode();
    newNode->Name = name;
    newNode->creationTime = time;
    newNode->Size = size;
    newNode->next = nullptr;
    return newNode;
}

// Them node moi vao dau danh sach
void pushFront(FileNode **head, const string &name, const string &time, double size) {
    FileNode *newNode = makeNode(name, time, size);
    newNode->next = *head;
    *head = newNode;
}

// Them file vao danh sach theo thu tu thoi gian
void themFile(FileNode **head, const string &name, const string &time, double size) {
    FileNode *newNode = makeNode(name, time, size);
    if (!*head || (*head)->creationTime > time) {
        pushFront(head, name, time, size);
    } else {
        FileNode *current = *head;
        while (current->next && current->next->creationTime < time) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Copy-paste mot file tu thu muc khac sang danh sach hien tai
void copyFile(FileNode **head, const string &name, const string &time, double size) {
    cout << "Copy-paste file " << name << " vao danh sach.\n";
    themFile(head, name, time, size);
}

// Ham tinh tong kich thuoc cac file trong danh sach
double tinhTongKichThuoc(FileNode *head) {
    double tongKichThuoc = 0;
    FileNode *current = head;
    while (current) {
        tongKichThuoc += current->Size;
        current = current->next;
    }
    return tongKichThuoc;
}


FileNode* insertionSort(FileNode *head) {
	if(!head||!head->next) return head;
	FileNode *sorted= nullptr;
	FileNode *current= head;
	while (current) {
		FileNode *nextNode = current->next;
		if(sorted||current->Size < sorted->Size) {
			current->next = sorted;
            sorted = current;
		}
		else {
			FileNode *temp = sorted;
            while (temp->next && temp->next->Size < current->Size) {
                temp = temp->next;
            }
		}
		current = nextNode;
	} 
	return sorted;
}

// Sao luu cac file vao USB voi gioi han dung luong
void saoLuuUSB(FileNode **head, double USB_SIZE_LIMIT) {
    double kichThuocHienTai = tinhTongKichThuoc(*head);
    if (kichThuocHienTai <= USB_SIZE_LIMIT) {
        cout << "Tat ca cac file da duoc sao luu vao USB.\n";
        return;
    }

    cout << "Dung luong vuot qua gioi han USB. Dang xoa cac file nho nhat...\n";

    while (kichThuocHienTai > USB_SIZE_LIMIT && *head) {
        FileNode *nhoNhat = *head;
        FileNode *nhoNhatPrev = nullptr;
        FileNode *current = *head;
        FileNode *prev = nullptr;

        while (current) {
            if (current->Size < nhoNhat->Size) {
                nhoNhat = current;
                nhoNhatPrev = prev;
            }
            prev = current;
            current = current->next;
        }

        if (nhoNhatPrev) {
            nhoNhatPrev->next = nhoNhat->next;
        } else {
            *head = (*head)->next;
        }

        kichThuocHienTai -= nhoNhat->Size;
        delete nhoNhat;
    }

    if (kichThuocHienTai <= USB_SIZE_LIMIT) {
        cout << "Cac file da duoc dieu chinh. Sao luu thanh cong vao USB.\n";
    } else {
        cout << "Dung luong van qua lon sau khi xoa file nho nhat.\n";
    }
}

// In thong tin cac file trong danh sach
void inDanhSachFile(FileNode *head) {
    FileNode *current = head;
    while (current) {
        cout << "File: " << current->Name
             << ", Size: " << current->Size
             << " MB, Creation Time: " << current->creationTime << endl;
        current = current->next;
    }
}

// Giai phong bo nho cua danh sach
void giaiPhongDanhSach(FileNode *head) {
    while (head) {
        FileNode *temp = head;
        head = head->next;
        delete temp;
    }
}

// Ham nhap thong tin file tu ban phim
void nhapFile(FileNode **head) {
    string name, time;
    double size;

    cout << "Nhap ten file: ";
    cin >> name;
    cout << "Nhap thoi gian tao file (YYYY-MM-DD HH:MM:SS): ";
    cin.ignore(); // Bo qua ky tu newline trong luong dong truoc
    getline(cin, time);
    cout << "Nhap kich thuoc file (MB): ";
    cin >> size;

    themFile(head, name, time, size);
}

int main() {
    FileNode *folder = nullptr;
    int choice;
    
    do {
        cout << "\nMenu:\n";
        cout << "1. Them file moi\n";
        cout << "2. Copy-paste file tu thu muc khac\n";
        cout << "3. In danh sach cac file\n";
        cout << "4. Tinh tong kich thuoc cac file\n";
        cout << "5. Sao luu file vao USB\n";
        cout << "0. Thoat\n";
        cout << "Lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
            case 1:
                nhapFile(&folder);
                break;
            case 2: {
                string name, time;
                double size;
                cout << "Nhap ten file can copy: ";
                cin >> name;
                cout << "Nhap thoi gian tao file (YYYY-MM-DD HH:MM:SS): ";
                cin.ignore();
                getline(cin, time);
                cout << "Nhap kich thuoc file (MB): ";
                cin >> size;
                copyFile(&folder, name, time, size);
                break;
            }
            case 3:
                cout << "\nDanh sach cac file trong thu muc:\n";
                inDanhSachFile(folder);
                break;
            case 4:
                cout << "Tong kich thuoc cac file: " << tinhTongKichThuoc(folder) << " MB\n";
                break;
            case 5: {
                double USB_SIZE_LIMIT = 32.0 * 1024; // Gioi han USB 32GB (MB)
                saoLuuUSB(&folder, USB_SIZE_LIMIT);
                break;
            }
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai.\n";
                break;
        }
    } while (choice != 0);

    // Giai phong bo nho
    giaiPhongDanhSach(folder);

    return 0;
}
