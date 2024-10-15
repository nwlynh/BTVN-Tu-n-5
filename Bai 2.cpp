#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

//Ham kiem tra so nguyen to 
bool isPrime(int n) {
	if(n<2) 
		return false;
	for (int i = 2; i <= sqrt(n);i++) {
		if(n%i==0) return false;
	}
	return true;
}

//Tạo danh sach cac so nguyen to co dang p mod 4 = 3
vector <int> generatePrimes(int N) {
	vector<int> primes;
    for (int i = 3; i <= sqrt(N); i++) {
        if (isPrime(i) && i % 4 == 3) {
            primes.push_back(i);
        }
    }
    return primes;
}

vector<int> generateBlumNumbers(int N) {
    vector<int> primes = generatePrimes(N);
    vector<int> blumNumbers;

    for (size_t i = 0; i < primes.size(); i++) {
        for (size_t j = i; j < primes.size(); j++) {
            int blum = primes[i] * primes[j];
            if (blum < N) {
                blumNumbers.push_back(blum);
            }
        }
    }
    sort(blumNumbers.begin(), blumNumbers.end());
    return blumNumbers;
}

// Hàm tìm các cặp số Blum có tổng là số Blum
void findBlumPairs(const vector<int>& blumNumbers, int N) {
    cout << "Cac cap so Blum cung co tong la so Blum nho hon " << N << ":\n";
    for (size_t i = 0; i < blumNumbers.size(); i++) {
        for (size_t j = i + 1; j < blumNumbers.size(); j++) {
            int sum = blumNumbers[i] + blumNumbers[j];
            if (sum < N && binary_search(blumNumbers.begin(), blumNumbers.end(), sum)) {
                cout << blumNumbers[i] << " + " << blumNumbers[j] << " = " << sum << "\n";
            }
        }
    }
}

// Hàm kiểm tra xem số Blum M có tồn tại hay không
bool checkBlumExistence(const vector<int>& blumNumbers, int M) {
    return binary_search(blumNumbers.begin(), blumNumbers.end(), M);
}

int main() {
    int N, M;
    cout << "Nhap so N: ";
    cin >> N;
    cout << "Nhap so Blum M: ";
    cin >> M;

    // Tạo mảng số Blum
    vector<int> blumNumbers = generateBlumNumbers(N);

    // Hiển thị mảng số Blum
    cout << "Danh sach cac so Blum nho hon " << N << ":\n";
    for (int blum : blumNumbers) {
        cout << blum << " ";
    }
    cout << "\n";

    // Tìm các cặp số Blum có tổng là số Blum
    findBlumPairs(blumNumbers, N);

    // Kiểm tra số Blum M có tồn tại hay không
    if (checkBlumExistence(blumNumbers, M)) {
        cout << "So Blum " << M << " ton tai trong mang.\n";
    } else {
        cout << "So Blum " << M << " khong ton tai trong mang.\n";
    }

    return 0;
}