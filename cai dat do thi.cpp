#include <iostream>
using namespace std;

struct DoThi {
    int soDinh;
    int** maTran;
    int** danhSach;
    int* kichThuocDanhSach;

    DoThi(int dinh) {
        soDinh = dinh;
        
        // Khoi tao ma tran lan can
        maTran = new int*[dinh];
        for (int i = 0; i < dinh; ++i) {
            maTran[i] = new int[dinh];
            for (int j = 0; j < dinh; ++j) {
                maTran[i][j] = 0;
            }
        }

        // Khoi tao danh sach lan can
        danhSach = new int*[dinh];
        kichThuocDanhSach = new int[dinh]{0};
    }

    void themCanh(int u, int v) {
        // Them canh vao ma tran lan can
        maTran[u][v] = 1;
        maTran[v][u] = 1; // Neu do thi vo huong

        // Them canh vao danh sach lan can
        kichThuocDanhSach[u]++;
        kichThuocDanhSach[v]++;
    }

    void xayDungDanhSachLanCan() {
        for (int i = 0; i < soDinh; ++i) {
            danhSach[i] = new int[kichThuocDanhSach[i]];
            kichThuocDanhSach[i] = 0;
        }
        for (int i = 0; i < soDinh; ++i) {
            for (int j = 0; j < soDinh; ++j) {
                if (maTran[i][j] == 1) {
                    danhSach[i][kichThuocDanhSach[i]++] = j;
                }
            }
        }
    }

    void BFS_MaTran(int batDau) {
        bool* daTham = new bool[soDinh]{false};
        int* hangDoi = new int[soDinh];
        int dau = 0, cuoi = 0;

        daTham[batDau] = true;
        hangDoi[cuoi++] = batDau;

        cout << "BFS (Ma tran lan can): ";

        while (dau < cuoi) {
            int hienTai = hangDoi[dau++];
            cout << hienTai << " ";

            for (int i = 0; i < soDinh; ++i) {
                if (maTran[hienTai][i] == 1 && !daTham[i]) {
                    daTham[i] = true;
                    hangDoi[cuoi++] = i;
                }
            }
        }
        cout << endl;

        delete[] daTham;
        delete[] hangDoi;
    }

    void DFS_MaTran(int batDau) {
        bool* daTham = new bool[soDinh]{false};
        int* nganXep = new int[soDinh];
        int dinh = -1;

        nganXep[++dinh] = batDau;

        cout << "DFS (Ma tran lan can): ";

        while (dinh >= 0) {
            int hienTai = nganXep[dinh--];

            if (!daTham[hienTai]) {
                daTham[hienTai] = true;
                cout << hienTai << " ";

                for (int i = soDinh - 1; i >= 0; --i) {
                    if (maTran[hienTai][i] == 1 && !daTham[i]) {
                        nganXep[++dinh] = i;
                    }
                }
            }
        }
        cout << endl;

        delete[] daTham;
        delete[] nganXep;
    }

    void BFS_DanhSach(int batDau) {
        bool* daTham = new bool[soDinh]{false};
        int* hangDoi = new int[soDinh];
        int dau = 0, cuoi = 0;

        daTham[batDau] = true;
        hangDoi[cuoi++] = batDau;

        cout << "BFS (Danh sach lan can): ";

        while (dau < cuoi) {
            int hienTai = hangDoi[dau++];
            cout << hienTai << " ";

            for (int i = 0; i < kichThuocDanhSach[hienTai]; ++i) {
                int ke = danhSach[hienTai][i];
                if (!daTham[ke]) {
                    daTham[ke] = true;
                    hangDoi[cuoi++] = ke;
                }
            }
        }
        cout << endl;

        delete[] daTham;
        delete[] hangDoi;
    }

    void DFS_DanhSach(int batDau) {
        bool* daTham = new bool[soDinh]{false};
        int* nganXep = new int[soDinh];
        int dinh = -1;

        nganXep[++dinh] = batDau;

        cout << "DFS (Danh sach lan can): ";

        while (dinh >= 0) {
            int hienTai = nganXep[dinh--];

            if (!daTham[hienTai]) {
                daTham[hienTai] = true;
                cout << hienTai << " ";

                for (int i = kichThuocDanhSach[hienTai] - 1; i >= 0; --i) {
                    int ke = danhSach[hienTai][i];
                    if (!daTham[ke]) {
                        nganXep[++dinh] = ke;
                    }
                }
            }
        }
        cout << endl;

        delete[] daTham;
        delete[] nganXep;
    }

    ~DoThi() {
        for (int i = 0; i < soDinh; ++i) {
            delete[] maTran[i];
            delete[] danhSach[i];
        }
        delete[] maTran;
        delete[] danhSach;
        delete[] kichThuocDanhSach;
    }
};

int main() {
    int soDinh, soCanh;
    cout << "Nhap so dinh va so canh: ";
    cin >> soDinh >> soCanh;

    DoThi doThi(soDinh);

    cout << "Nhap thong tin cac canh (u v):\n";
    for (int i = 0; i < soCanh; ++i) {
        int u, v;
        cin >> u >> v;
        doThi.themCanh(u, v);
    }

    doThi.xayDungDanhSachLanCan();

    int batDau;
    cout << "Nhap dinh bat dau: ";
    cin >> batDau;

    doThi.BFS_MaTran(batDau);
    doThi.DFS_MaTran(batDau);
    doThi.BFS_DanhSach(batDau);
    doThi.DFS_DanhSach(batDau);

    return 0;
}
