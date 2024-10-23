#include <iostream>
using namespace std;

void timSoDanTrung(int a[], int m) {
	int mang[100], tanso[100], dem = 0;
	mang[0] = a[0], tanso[0] = 1;

	for (int i = 1; i < m; i++) {
		bool timthay = false;
		for (int j = 0; j <= dem; j++) {
			if (a[i] == mang[j]) {
				tanso[j]++;
				timthay = true;
				break;
			}
		}
		if (!timthay) {
			dem++;
			mang[dem] = a[i], tanso[dem] = 1;
		}
	}
	for (int i = 0; i <= dem; i++) {
		cout << "So nam co " << mang[i] << " nguoi la: " << tanso[i] << " nam\n";
	}
}

int timMax(int a[], int m) {
	int max = a[0];
	for (int i = 1; i < m; i++) 
		if (a[i] > max) max = a[i];
	return max;
}

int timMin(int a[], int m) {
	int min = a[0];
	for (int i = 1; i < m; i++) 
		if (a[i] < min) min = a[i];
	return min;
}

void timNam(int songuoi, int a[], int b[], int m) {
	for (int i = 0; i < m; i++) 
		if (a[i] == songuoi) cout << b[i] << " ";
}

int main() {
	int n, year[150], people[150];
	cout << "Nhap tong so nam: ";
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		cout << "Nhap nam: ";
		cin >> year[i];
		cout << "So nguoi trong nam " << year[i] << " la: ";
		cin >> people[i];
	}

	timSoDanTrung(people, n);
	int maxPeople = timMax(people, n), minPeople = timMin(people, n);

	cout << "Cac nam co so nguoi sinh ra lon nhat la: ";
	timNam(maxPeople, people, year, n);
	cout << "\nCac nam co so nguoi sinh ra nho nhat la: ";
	timNam(minPeople, people, year, n);

	return 0;
}
