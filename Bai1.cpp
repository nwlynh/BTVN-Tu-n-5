#include <iostream>
#include <vector>
#include <string>

using namespace std;

void sortColors(vector<string>& colors) {
    int low = 0, mid = 0, high = colors.size() - 1;

    while (mid <= high) {
        if (colors[mid] == "do") {
            swap(colors[low], colors[mid]);
            low++;
            mid++;
        } else if (colors[mid] == "trang") {
            mid++;
        } else { // colors[mid] == "xanh"
            swap(colors[mid], colors[high]);
            high--;
        }
    }
}

int main() {
    int n;  
    cout << "Nhap so luong mau: ";
    cin >> n;
    vector<string> colors(n);
    cout << "Nhap cac mau (do, trang, xanh):" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> colors[i];
        }
    sortColors(colors);
    cout << "Mang mau sau khi sap xep: ";
    for (const string& color : colors) {
        cout << color << " ";
    }
    cout << endl;
    return 0;
}
