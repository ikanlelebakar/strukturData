// File: models.cpp
// Deskripsi: Definisi struct, variabel global, dan fungsi queue

#include <iostream>
#include <string>
using namespace std;

// Konstanta global
int MAX_TIM = 8;
const int MIN_PEMAIN = 1;
const int MAX_PEMAIN = 7;

// Variabel global admin
string adminUsername = "";
string adminPassword = "";
string namaTurnamen = "";
bool adminSudahDibuat = false;

// Fungsi cek pangkat 2
bool adalahPangkatDua(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

// Struktur data Tim
struct Tim {
    string nama;
    string password;
    int jumlahPemain;
    int poin;
    bool tereleminasi;
    Tim *berikutnya;
};

// Struktur data Node Antrian Pertandingan
struct NodeAntrian {
    Tim *timA;
    Tim *timB;
    string tanggalTanding;
    string jam;
    string ronde;
    NodeAntrian *berikutnya;
};

// Variabel global tim
Tim *kepala = NULL;
int jumlahTim = 0;
bool pendaftaranDitutup = false;
bool jadwalSudahDibuat = false;

// Variabel global antrian pertandingan
NodeAntrian *depanAntrian = NULL;
NodeAntrian *belakangAntrian = NULL;

// Variabel global ronde
int rondeSekarang = 0;
int matchDiRonde = 0;

// Variabel global untuk perebutan juara 3
Tim *semifinalisKalah1 = NULL;
Tim *semifinalisKalah2 = NULL;
bool matchKetiga = false;

// Struktur data hasil pertandingan
struct MatchResult {
    Tim *timA;
    Tim *timB;
    Tim *pemenang;
    string ronde;
};

const int MAX_MATCHES = 64;
MatchResult matchResults[MAX_MATCHES];
int jumlahHasil = 0;

// Fungsi tambah antrian pertandingan (Enqueue)
void tambahAntrian(Tim *timA, Tim *timB, string tanggal, string jam, string ronde) {
    NodeAntrian *baru = new NodeAntrian;
    baru->timA = timA;
    baru->timB = timB;
    baru->tanggalTanding = tanggal;
    baru->jam = jam;
    baru->ronde = ronde;
    baru->berikutnya = NULL;

    if (belakangAntrian == NULL) {
        depanAntrian = baru;
        belakangAntrian = baru;
    } else {
        belakangAntrian->berikutnya = baru;
        belakangAntrian = baru;
    }
}

// Fungsi hapus antrian pertandingan (Dequeue)
void hapusAntrian() {
    if (depanAntrian == NULL) return;

    NodeAntrian *temp = depanAntrian;
    depanAntrian = depanAntrian->berikutnya;
    if (depanAntrian == NULL) {
        belakangAntrian = NULL;
    }
    delete temp;
}

// Fungsi cek apakah antrian kosong
bool antrianKosong() {
    return depanAntrian == NULL;
}

// Fungsi catat pertandingan baru ke riwayat
void catatPertandingan(Tim *timA, Tim *timB, string ronde) {
    if (jumlahHasil >= MAX_MATCHES) return;
    matchResults[jumlahHasil].timA = timA;
    matchResults[jumlahHasil].timB = timB;
    matchResults[jumlahHasil].pemenang = NULL;
    matchResults[jumlahHasil].ronde = ronde;
    jumlahHasil++;
}

// Fungsi update pemenang pertandingan di riwayat
void updatePemenang(Tim *timA, Tim *timB, Tim *pemenang) {
    for (int i = 0; i < jumlahHasil; i++) {
        bool cocok = (matchResults[i].timA == timA && matchResults[i].timB == timB) ||
                     (matchResults[i].timA == timB && matchResults[i].timB == timA);
        if (cocok && matchResults[i].pemenang == NULL) {
            matchResults[i].pemenang = pemenang;
            return;
        }
    }
}
