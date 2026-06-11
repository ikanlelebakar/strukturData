/*
 * File: models.cpp
 * Deskripsi: Definisi struct, variabel global, dan fungsi queue
 *            yang digunakan di seluruh sistem turnamen.
 *
 * Struktur data utama:
 *   - Tim          : Singly Linked List node untuk daftar tim
 *   - NodeAntrian  : Singly Linked List node untuk antrian pertandingan (Queue)
 */

#include <iostream>
#include <string>
using namespace std;

// ==========================================
// KONSTANTA GLOBAL
// ==========================================
const int MAX_TIM    = 8;  // harus pangkat 2: 4, 8, 16, 32...
const int MIN_PEMAIN = 1;
const int MAX_PEMAIN = 7;

// ==========================================
// STRUCT TIM (node singly linked list)
// ==========================================
struct Tim {
    string namaTim;       // nama tim, juga sebagai username login
    string password;      // untuk autentikasi login tim
    int    jumlahPemain;  // jumlah anggota tim, valid: 1-7
    int    poin;          // jumlah kemenangan, untuk sorting klasemen
    bool   isEliminated;  // status eliminasi tim
    Tim*   next;          // pointer ke node berikutnya
};

// ==========================================
// STRUCT NODE ANTRIAN PERTANDINGAN
// ==========================================
struct NodeAntrian {
    Tim*         timA;          // pointer ke tim pertama
    Tim*         timB;          // pointer ke tim kedua
    string       tanggalTanding; // format: "YYYY-MM-DD"
    string       ronde;         // label ronde (misal: "Ronde 1", "Semifinal", dll.)
    NodeAntrian* next;
};

// ==========================================
// VARIABEL GLOBAL — STATE LINKED LIST TIM
// ==========================================
Tim* headTim          = nullptr;  // head linked list tim
int  jumlahTimAktif   = 0;        // counter jumlah tim yang terdaftar
bool pendaftaranDitutup  = false; // false = masih bisa daftar
bool bracketSudahDibuat  = false; // true = braket sudah terbentuk

// ==========================================
// VARIABEL GLOBAL — ANTRIAN PERTANDINGAN
// ==========================================
NodeAntrian* frontAntrian = nullptr;  // kepala antrian (FIFO)
NodeAntrian* backAntrian  = nullptr;  // ekor antrian

// ==========================================
// VARIABEL GLOBAL — BRACKET & RONDE
// ==========================================
int rondeSekarang  = 0;    // ronde yang sedang berjalan
int matchDiRonde   = 0;    // jumlah match yang sudah terjadi di ronde ini
string tanggalTerakhir = ""; // tanggal pertandingan terakhir di ronde ini

// Untuk logika juara ke-3: semi-finalis yang kalah
Tim* semifinalisKalah1 = nullptr;
Tim* semifinalisKalah2 = nullptr;
bool matchKetiga       = false;  // flag: pertandingan berikutnya adalah juara ke-3

// ==========================================
// FUNGSI QUEUE — ANTRIAN PERTANDINGAN
// ==========================================

/*
 * pushAntrian: enqueue satu match ke belakang antrian
 */
void pushAntrian(Tim* timA, Tim* timB, string tanggal, string ronde) {
    NodeAntrian* node  = new NodeAntrian;
    node->timA          = timA;
    node->timB          = timB;
    node->tanggalTanding = tanggal;
    node->ronde         = ronde;
    node->next          = nullptr;

    if (backAntrian == nullptr) {
        frontAntrian = node;
        backAntrian  = node;
    } else {
        backAntrian->next = node;
        backAntrian       = node;
    }
}

/*
 * popAntrian: dequeue pertandingan paling depan
 */
void popAntrian() {
    if (frontAntrian == nullptr) return;

    NodeAntrian* temp = frontAntrian;
    frontAntrian      = frontAntrian->next;
    if (frontAntrian == nullptr) {
        backAntrian = nullptr;
    }
    delete temp;
}

/*
 * isAntrianKosong: cek apakah antrian kosong
 */
bool isAntrianKosong() {
    return frontAntrian == nullptr;
}
