#include <iostream>
#include <string>

using namespace std;

struct WordNode {
    string word;       // Luu tu vung
    int count;         // So lan xuat hien cua tu
    WordNode *next;    // Con tro den tu ke tiep

    // Khoi tao tu moi voi so lan xuat hien la 1
    WordNode(const string &w) : word(w), count(1), next(nullptr) {}
};

class WordList {
private:
    WordNode *head;    // Con tro den tu dau tien trong danh sach

public:
    WordList() : head(nullptr) {}

    // Them mot tu vao danh sach, neu tu da ton tai thi tang so lan xuat hien
    void addWord(const string &word) {
        WordNode *current = head;
        WordNode *prev = nullptr;

        // Duyet qua danh sach de kiem tra tu da ton tai
        while (current) {
            if (current->word == word) {
                current->count++;
                return;
            }
            prev = current;
            current = current->next;
        }

        // Neu tu chua ton tai, tao node moi va them vao cuoi danh sach
        WordNode *newNode = new WordNode(word);
        if (!head) {
            head = newNode;
        } else {
            prev->next = newNode;
        }
    }

    // Xac dinh tu xuat hien nhieu nhat trong danh sach
    string findMostFrequentWord() {
        if (!head) return "";

        WordNode *current = head;
        string mostFrequentWord = head->word;
        int maxCount = head->count;

        // Duyet qua danh sach de tim tu co so lan xuat hien lon nhat
        while (current) {
            if (current->count > maxCount) {
                maxCount = current->count;
                mostFrequentWord = current->word;
            }
            current = current->next;
        }

        return mostFrequentWord;
    }

    // Loai bo tu lay (cac tu giong nhau lien tiep)
    void removeRepeatingWords() {
        WordNode *current = head;
        while (current && current->next) {
            if (current->word == current->next->word) {
                WordNode *duplicate = current->next;
                current->next = duplicate->next;
                delete duplicate;
            } else {
                current = current->next;
            }
        }
    }

    // Dem so tu vung khac nhau trong danh sach
    int countUniqueWords() {
        int uniqueCount = 0;
        WordNode *current = head;

        while (current) {
            bool isUnique = true;
            WordNode *check = head;

            // Kiem tra neu tu nay da xuat hien truoc do
            while (check != current) {
                if (check->word == current->word) {
                    isUnique = false;
                    break;
                }
                check = check->next;
            }

            // Neu tu la duy nhat, tang bien dem
            if (isUnique) {
                uniqueCount++;
            }
            current = current->next;
        }

        return uniqueCount;
    }

    // Ham in danh sach cac tu va so lan xuat hien
    void printWords() {
        WordNode *current = head;
        while (current) {
            cout << current->word << " (" << current->count << ")\n";
            current = current->next;
        }
    }

    // Huy danh sach de giai phong bo nho
    ~WordList() {
        while (head) {
            WordNode *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    WordList wordList;
    string sentence;

    cout << "Nhap cau tieng viet: ";
    getline(cin, sentence);

    // Tach cau thanh tung tu va them vao danh sach lien ket
    string word;
    for (char ch : sentence) {
        if (ch == ' ') {
            if (!word.empty()) {
                wordList.addWord(word);
                word.clear();
            }
        } else {
            word += ch;
        }
    }
    if (!word.empty()) {
        wordList.addWord(word);
    }

    cout << "\nDanh sach cac tu trong cau:\n";
    wordList.printWords();

    // Tim tu xuat hien nhieu nhat
    string mostFrequentWord = wordList.findMostFrequentWord();
    cout << "\nTu xuat hien nhieu nhat: " << mostFrequentWord << endl;

    // Loai bo tu lay (cac tu giong nhau lien tiep)
    wordList.removeRepeatingWords();
    cout << "\nDanh sach sau khi loai bo tu lay:\n";
    wordList.printWords();

    // Dem so tu vung khac nhau
    int uniqueWordCount = wordList.countUniqueWords();
    cout << "\nSo tu vung khac nhau trong cau: " << uniqueWordCount << endl;

    return 0;
}
