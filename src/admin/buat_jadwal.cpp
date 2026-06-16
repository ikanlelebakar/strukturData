// File: buat_jadwal.cpp
// Deskripsi: Fungsi untuk membuat jadwal pertandingan ronde pertama

#include <ctime>
#include <sstream>
#include <iomanip>

// Fungsi tambah hari ke tanggal YYYY-MM-DD
string tambahHari(const string& tanggal, int hari) {
    struct tm t = {};
    t.tm_year = stoi(tanggal.substr(0, 4)) - 1900;
    t.tm_mon  = stoi(tanggal.substr(5, 2)) - 1;
    t.tm_mday = stoi(tanggal.substr(8, 2));

    t.tm_mday += hari;
    mktime(&t);

    ostringstream oss;
    oss << setfill('0')
        << (t.tm_year + 1900) << "-"
        << setw(2) << (t.tm_mon + 1) << "-"
        << setw(2) << t.tm_mday;
    return oss.str();
}

// Fungsi validasi format tanggal YYYY-MM-DD
bool validasiTanggal(const string& tgl) {
    if (tgl.size() != 10) return false;
    if (tgl[4] != '-' || tgl[7] != '-') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(tgl[i])) return false;
    }
    return true;
}

// Fungsi buat jadwal pertandingan Ronde 1
void buatJadwal() {
    if (!pendaftaranDitutup) {
        cout << "Admin harus menutup pendaftaran terlebih dahulu." << endl;
        return;
    }

    if (jumlahTim < 2) {
        cout << "Minimal 2 tim dibutuhkan untuk membuat jadwal." << endl;
        return;
    }

    if (!adalahPangkatDua(jumlahTim)) {
        cout << "Jumlah tim (" << jumlahTim << ") harus pangkat 2 (4, 8, 16...)." << endl;
        return;
    }

    if (jadwalSudahDibuat) {
        cout << "Braket sudah pernah dibuat sebelumnya." << endl;
        return;
    }

    string tanggalMulai;
    do {
        cout << "Masukkan tanggal mulai Ronde 1 (format YYYY-MM-DD): ";
        cin >> tanggalMulai;
        cin.ignore(10000, '\n');
        if (!validasiTanggal(tanggalMulai)) {
            cout << "[ERROR] Format tanggal tidak valid. Gunakan YYYY-MM-DD." << endl;
        }
    } while (!validasiTanggal(tanggalMulai));

    // Kumpulkan tim ke array sementara untuk pairing
    Tim **arrTim = new Tim*[MAX_TIM];
    int n = 0;
    Tim *curr = kepala;
    while (curr != NULL) {
        arrTim[n++] = curr;
        curr = curr->berikutnya;
    }

    string labelRonde = (n == 4) ? "Semifinal" : "Ronde 1";

    cout << "\n=== JADWAL " << labelRonde << " ==="  << endl;
    for (int i = 0; i < n / 2; i++) {
        string tgl = tambahHari(tanggalMulai, i);
        tambahAntrian(arrTim[i], arrTim[n - 1 - i], tgl, labelRonde);
        catatPertandingan(arrTim[i], arrTim[n - 1 - i], labelRonde);
        cout << "  " << arrTim[i]->nama << " vs " << arrTim[n - 1 - i]->nama
             << " (" << tgl << ")" << endl;
    }

    tanggalTerakhir = tambahHari(tanggalMulai, n / 2 - 1);
    rondeSekarang = 1;
    jadwalSudahDibuat = true;

    cout << "Jadwal " << labelRonde << " berhasil dibuat. Braket siap!" << endl;
    delete[] arrTim;
}
