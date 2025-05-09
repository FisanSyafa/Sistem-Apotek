//Kelompok 9 IF05
//Ahmad Haitsam          (22.11.4812)
//fauzan Yahya Abiworo   (22.11.4817)
//Fisan Syafa Nayoma     (22.11.4836)
//Guntur Tri Atmaja      (22.11.4820)
//Muhammad Hafid Assidiqi(22.11.4828)

#include <iostream>
#include <string>
#define max 100 //deklarasi max queue
using namespace std;

struct Obat {
    string namaobat;
    int hargaobat;
    int stokobat;
};

struct Alat {
    string namaalat;
    int hargaalat;
    int stokalat;
};

struct Node {
    Obat dataobat;
    Alat dataalat;
    Node* nextobat;
    Node* nextalat;
    Node* prevobat;  // Pointer ke Node sebelumnya dalam double linked list obat
    Node* prevalat;  // Pointer ke Node sebelumnya dalam double linked list alat medis
    int stokobat;    // Jumlah stok obat
    int stokalat;    // Jumlah stok alat medis
};

struct Queue {
    int front, rear, data[max];
}Q;

void tambahObat(Node** headobat, Node** tailobat, string namaobat, int hargaobat) {
    Node* newNode = new Node;
    newNode->dataobat.namaobat = namaobat;
    newNode->dataobat.hargaobat = hargaobat;
    newNode->dataobat.stokobat = 0; // Inisialisasi stok obat menjadi 0
    newNode->nextobat = nullptr;
    newNode->prevobat = nullptr;

    if (*headobat == nullptr) {
        *headobat = newNode;
        *tailobat = newNode;
    }
    else {
        (*tailobat)->nextobat = newNode;
        newNode->prevobat = *tailobat;
        *tailobat = newNode;
    }
}

void tambahAlat(Node** headalat, Node** tailalat, string namaalat, int hargaalat) {
    Node* newNode = new Node;
    newNode->dataalat.namaalat = namaalat;
    newNode->dataalat.hargaalat = hargaalat;
    newNode->dataalat.stokalat = 0; // Inisialisasi stok alat menjadi 0
    newNode->nextalat = nullptr;
    newNode->prevalat = nullptr;

    if (*headalat == nullptr) {
        *headalat = newNode;
        *tailalat = newNode;
    }
    else {
        (*tailalat)->nextalat = newNode;
        newNode->prevalat = *tailalat;
        *tailalat = newNode;
    }
}

Node* cariObat(Node* headobat, string namaobat) {
    Node* temp = headobat;
    while (temp != nullptr) {
        if (temp->dataobat.namaobat == namaobat) {
            return temp;
        }
        temp = temp->nextobat;
    }
    return nullptr;
}

Node* cariAlat(Node* headalat, string namaalat) {
    Node* temp = headalat;
    while (temp != nullptr) {
        if (temp->dataalat.namaalat == namaalat) {
            return temp;
        }
        temp = temp->nextalat;
    }
    return nullptr;
}

bool isFull(Queue Q) {
    return Q.rear == max - 1;
}

bool isEmpty(Queue Q) {
    return Q.rear == -1;
}

void printQueue(Queue Q) {
    if (isEmpty(Q)) {
        cout << "Antrian tidak ada\n";
    }
    else
    {
        cout << "Antrian  = ";
        for (int i = Q.front; i < Q.rear; i++)
            cout << Q.data[i] << " ";
        cout << endl;
    }
}

void EnQueue(Queue* Q) {
    if (isFull(*Q))
    {
        cout << "Antrian penuh!\n";
    }
    else
    {
        int data;
        //menambahkan data ke antrian
        cout << "\nMasukan Antrian = "; cin >> data;
        Q->data[Q->rear] = data;
        //menempatkan tail pada elemen data terakhir yang di tambahkan
        Q->rear++;
        cout << "Data ditambahkan\n";
        printQueue(*Q);
    }
}

void DeQueue(Queue* Q) {
    if (isEmpty(*Q))
    {
        cout << "Antrian masih kosong " << endl;
    }
    else {
        cout << "Menambil data " << Q->data[Q->front] << "..." << endl;
        //menggeser antrian data ke head
        for (int i = Q->front; i < Q->rear; i++)
            Q->data[i] = Q->data[i + 1];
        //menempatkan tail pada data terakhir yang di geser
        Q->rear--;
        printQueue(*Q);
    }
}

void tambahStokObat(Node* headobat, string namaobat, int jumlah) {
    Node* node = cariObat(headobat, namaobat);
    if (node != nullptr) {
        node->dataobat.stokobat += jumlah;
        cout << "Stok obat \"" << namaobat << "\" berhasil ditambahkan sebanyak " << jumlah << endl;
    }
    else {
        cout << "Obat \"" << namaobat << "\" tidak ditemukan." << endl;
    }
}

void tambahStokAlat(Node* headalat, string namaalat, int jumlah) {
    Node* node = cariAlat(headalat, namaalat);
    if (node != nullptr) {
        node->dataalat.stokalat += jumlah;
        cout << "Stok alat medis \"" << namaalat << "\" berhasil ditambahkan sebanyak " << jumlah << endl;
    }
    else {
        cout << "Alat medis \"" << namaalat << "\" tidak ditemukan." << endl;
    }
}

void hapusObatAkhir(Node** headobat, Node** tailobat) {
    if (*headobat == nullptr) {
        cout << "Tidak ada obat dalam stok." << endl;
        return;
    }

    Node* node = *tailobat;
    *tailobat = (*tailobat)->prevobat;

    if (*tailobat != nullptr) {
        (*tailobat)->nextobat = nullptr;
    }
    else {
        *headobat = nullptr;
    }

    cout << "Obat \"" << node->dataobat.namaobat << "\" berhasil dihapus dari linked list obat." << endl;
    delete node;
}

void hapusAlatAkhir(Node** headalat, Node** tailalat) {
    if (*headalat == nullptr) {
        cout << "Tidak ada alat medis dalam stok." << endl;
        return;
    }

    Node* node = *tailalat;
    *tailalat = (*tailalat)->prevalat;

    if (*tailalat != nullptr) {
        (*tailalat)->nextalat = nullptr;
    }
    else {
        *headalat = nullptr;
    }

    cout << "Alat medis \"" << node->dataalat.namaalat << "\" berhasil dihapus dari linked list alat medis." << endl;
    delete node;
}

void hapusObat(Node** headobat) {
    string namaobat;
    cout << "Masukkan nama obat yang akan dihapus   = ";
    cin.ignore();
    getline(cin, namaobat);

    Node* node = cariObat(*headobat, namaobat);
    if (node != nullptr) {
        if (node == *headobat) {
            *headobat = node->nextobat;
        }
        else {
            Node* temp = *headobat;
            while (temp->nextobat != node) {
                temp = temp->nextobat;
            }
            temp->nextobat = node->nextobat;
        }
        cout << "Obat \"" << namaobat << "\" berhasil dihapus dari linked list obat." << endl;
        delete node;
    }
    else {
        cout << "Obat \"" << namaobat << "\" tidak ditemukan." << endl;
    }
}

void hapusAlat(Node** headalat) {
    string namaalat;
    cout << "Masukkan nama alat medis yang akan dihapus = ";
    cin.ignore();
    getline(cin, namaalat);

    Node* node = cariAlat(*headalat, namaalat);
    if (node != nullptr) {
        if (node == *headalat) {
            *headalat = node->nextalat;
        }
        else {
            Node* temp = *headalat;
            while (temp->nextalat != node) {
                temp = temp->nextalat;
            }
            temp->nextalat = node->nextalat;
        }
        cout << "Alat medis \"" << namaalat << "\" berhasil dihapus dari linked list alat medis." << endl;
        delete node;
    }
    else {
        cout << "Alat medis \"" << namaalat << "\" tidak ditemukan." << endl;
    }
}

void jualObat(Node* headobat, string namaobat, int jumlah) {
    Node* node = cariObat(headobat, namaobat);
    if (node != nullptr) {
        if (node->dataobat.stokobat >= jumlah) {
            int totalHarga = jumlah * node->dataobat.hargaobat;
            cout << "Total harga    = Rp." << totalHarga << endl;

            cout << "Masukkan jumlah uang yang dibayarkan   = ";
            int uangBayar;
            cin >> uangBayar;

            if (uangBayar >= totalHarga) {
                int kembalian = uangBayar - totalHarga;
                node->dataobat.stokobat -= jumlah; // Pengurangan stok obat
                cout << "Penjualan obat \"" << namaobat << "\" sebanyak " << jumlah << " berhasil." << endl;
                cout << "Uang kembalian = Rp." << kembalian << endl;
            }
            else {
                cout << "Uang yang dibayarkan tidak mencukupi." << endl;
            }
        }
        else {
            cout << "Stok obat \"" << namaobat << "\" tidak mencukupi." << endl;
        }
    }
    else {
        cout << "Obat \"" << namaobat << "\" tidak ditemukan." << endl;
    }
}

void jualAlat(Node* headalat, string namaalat, int jumlah) {
    Node* node = cariAlat(headalat, namaalat);
    if (node != nullptr) {
        if (node->dataalat.stokalat >= jumlah) {
            int totalHarga = jumlah * node->dataalat.hargaalat;
            cout << "Total harga    = Rp." << totalHarga << endl;

            cout << "Masukkan jumlah uang yang dibayarkan   = ";
            int uangBayar;
            cin >> uangBayar;

            if (uangBayar >= totalHarga) {
                int kembalian = uangBayar - totalHarga;
                node->dataalat.stokalat -= jumlah;
                cout << "Penjualan alat medis \"" << namaalat << "\" sebanyak " << jumlah << " berhasil." << endl;
                cout << "Uang kembalian = Rp." << kembalian << endl;
            }
            else {
                cout << "Uang yang dibayarkan tidak mencukupi." << endl;
            }
        }
        else {
            cout << "Stok alat medis \"" << namaalat << "\" tidak mencukupi." << endl;
        }
    }
    else {
        cout << "Obat \"" << namaalat << "\" tidak ditemukan." << endl;
    }
}

void printObat(Node* headobat) {
    if (headobat == nullptr) {
        cout << "Tidak ada obat dalam stok." << endl;
        return;
    }

    cout << "Stok Obat saat ini:\n";

    Node* temp = headobat;
    while (temp != nullptr) {
        cout << "=================================\n";
        cout << "Nama Obat  = " << temp->dataobat.namaobat << endl;
        cout << "Harga Obat = Rp." << temp->dataobat.hargaobat << endl;
        cout << "Stok Obat  = " << temp->dataobat.stokobat << endl;
        cout << endl;

        temp = temp->nextobat;
    }
}

void printAlat(Node* headalat) {
    if (headalat == nullptr) {
        cout << "Tidak ada alat medis dalam stok." << endl;
        return;
    }

    cout << "Stok Alat Medis saat ini:\n";

    Node* temp = headalat;
    while (temp != nullptr) {
        cout << "=================================\n";
        cout << "Nama Alat medis    = " << temp->dataalat.namaalat << endl;
        cout << "Harga Alat medis   = Rp." << temp->dataalat.hargaalat << endl;
        cout << "Stok Alat medis    = " << temp->dataalat.stokalat << endl;
        cout << endl;

        temp = temp->nextalat;
    }
}

int main() {
    Node* headobat = nullptr;
    Node* headalat = nullptr;
    Node* tailobat = nullptr;
    Node* tailalat = nullptr;

    int pilihan;
    do {
        system("cls");
        cout << "======================================\n";
        cout << "SELAMAT DATANG DI APOTEK RAJAWALI CARE\n";
        cout << "======================================\n";
        cout << "Pilih Anda sebagai apa hari ini :\n";
        cout << "1. Nakes\n";
        cout << "2. Supplier\n";
        cout << "3. Kasir\n";
        cout << "4. Batal\n";
        cout << "Pilihan Anda = ";
        cin >> pilihan;

        if (pilihan == 1) {
            int subpilihan;
            system("cls");
            do {
                cout << "1. Tambah Antrian" << endl;
                cout << "2. Keluarkan 1 Antrian" << endl;
                cout << "3. Tampilkan Antrian" << endl;
                cout << "4. Kembali ke menu utama" << endl;
                cout << "Pilih Menu = "; cin >> subpilihan;
                switch (subpilihan)
                {
                case 1:
                    system("cls");
                    EnQueue(&Q);
                    break;
                case 2:
                    system("cls");
                    DeQueue(&Q);
                    break;
                case 3:
                    system("cls");
                    printQueue(Q);
                    system("pause");
                    break;
                case 4:
                    // Kembali ke Menu Utama
                    break;

                default:
                    break;
                }
            } while (subpilihan != 4);
        }
        else if (pilihan == 2) {
            // menu jika menjadi Supplier
            int subpilihan;
            string namaObat;
            int hargaObat;
            string namaAlatMedis;
            int hargaAlatMedis;

            do {
                system("cls");
                cout << "=================================\n";
                cout << "\n========= Menu Supplier =========\n";
                cout << "1. Tambah Obat\n";
                cout << "2. Tambah Alat Medis\n";
                cout << "3. Tambah Stok Obat\n";
                cout << "4. Tambah Stok Alat Medis\n";
                cout << "5. Lihat stok obat\n";
                cout << "6. Lihat stok alat medis\n";
                cout << "7. Hapus Obat(Pencarian)\n";
                cout << "8. Hapus  alat medis(Pencarian)\n";
                cout << "9. Hapus Obat(Paling Belakang)\n";
                cout << "10. Hapus  alat medis(Paling Belakang)\n";
                cout << "11. Kembali ke Menu Utama\n";
                cout << "Pilihan Anda   = ";
                cin >> subpilihan;

                switch (subpilihan) {
                case 1:
                    do {
                        system("cls");
                        cout << "Masukkan nama obat     = ";
                        cin >> namaObat;
                        cout << "Masukkan harga obat    = ";
                        cin >> hargaObat;

                        tambahObat(&headobat, &tailobat, namaObat, hargaObat);


                        cout << "Obat berhasil ditambahkan!\n";

                        cout << "Ingin menambahkan obat lagi? (y/n): ";
                        char pilihanLagi;
                        cin >> pilihanLagi;

                        if (pilihanLagi != 'y' && pilihanLagi != 'Y') {
                            break;
                        }
                    } while (true);
                    printObat(headobat); // Menampilkan stok obat terbaru
                    system("pause");
                    break;

                case 2:
                    do {
                        system("cls");
                        cout << "Masukkan nama alat medis   = ";
                        cin >> namaAlatMedis;
                        cout << "Masukkan harga alat medis  = ";
                        cin >> hargaAlatMedis;

                        tambahAlat(&headalat, &tailalat, namaAlatMedis, hargaAlatMedis);


                        cout << "Alat Medis berhasil ditambahkan!\n";

                        cout << "Ingin menambahkan alat medis lagi? (y/n): ";
                        char pilihanLagi;
                        cin >> pilihanLagi;

                        if (pilihanLagi != 'y' && pilihanLagi != 'Y') {
                            break;
                        }
                    } while (true);
                    printAlat(headalat); // Menampilkan stok alat medis terbaru
                    system("pause");
                    break;
                case 3:
                    system("cls");
                    cout << "Masukkan nama obat yang akan ditambahkan stok  = ";
                    cin >> namaObat;
                    cout << "Masukkan jumlah stok yang akan ditambahkan     = ";
                    int jumlahObat;
                    cin >> jumlahObat;
                    tambahStokObat(headobat, namaObat, jumlahObat);
                    system("pause");
                    break;
                case 4:
                    system("cls");
                    cout << "Masukkan nama alat medis yang akan ditambahkan stok    = ";
                    cin >> namaAlatMedis;
                    cout << "Masukkan jumlah stok yang akan ditambahkan             = ";
                    int jumlahAlatMedis;
                    cin >> jumlahAlatMedis;
                    tambahStokAlat(headalat, namaAlatMedis, jumlahAlatMedis);
                    system("pause");
                    break;
                case 5:
                    system("cls");
                    printObat(headobat);
                    system("pause");
                    break;
                case 6:
                    system("cls");
                    printAlat(headalat);
                    system("pause");
                    break;
                case 7:
                    system("cls");
                    hapusObat(&headobat);
                    system("pause");
                    printObat(headobat); // Menampilkan stok obat terbaru setelah menghapus obat
                    break;
                case 8:
                    system("cls");
                    hapusAlat(&headalat);
                    system("pause");
                    printAlat(headalat); // Menampilkan stok alat terbaru setelah menghapus obat
                    break;
                case 9:
                    system("cls");
                    hapusObatAkhir(&headobat, &tailobat);
                    system("pause");
                    printObat(headobat); // Menampilkan stok obat terbaru setelah menghapus obat
                    break;
                case 10:
                    system("cls");
                    hapusAlatAkhir(&headalat, &tailalat);
                    system("pause");
                    printAlat(headalat); // Menampilkan stok alat terbaru setelah menghapus obat
                    break;
                case 11:
                    // Kembali ke Menu Utama
                    break;
                default:
                    cout << "Pilihan tidak valid." << endl;
                    system("pause");
                    break;
                }
            } while (subpilihan != 11);
        }
        else if (pilihan == 3) {
            // menu jika menjadi Kasir
            int subpilihan;
            string namaObat;
            string namaAlatMedis;
            int jumlah;

            do {
                system("cls");
                cout << "=================================\n";
                cout << "\n========= Menu Kasir =========\n";
                cout << "1. Jual Obat\n";
                cout << "2. Jual Alat Medis\n";
                cout << "3. Lihat Stok Obat\n";
                cout << "4. Lihat Stok Alat Medis\n";
                cout << "5. Kembali ke Menu Utama\n";
                cout << "Pilihan Anda   = ";
                cin >> subpilihan;

                switch (subpilihan) {
                case 1:
                    system("cls");
                    cout << "Masukkan nama obat   = ";
                    cin.ignore();
                    getline(cin, namaObat);
                    cout << "Masukkan jumlah obat = ";
                    cin >> jumlah;
                    jualObat(headobat, namaObat, jumlah);
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    cout << "Masukkan nama alat medis    = ";
                    cin.ignore();
                    getline(cin, namaAlatMedis);
                    cout << "Masukkan jumlah alat medis  = ";
                    cin >> jumlah;
                    jualAlat(headalat, namaAlatMedis, jumlah);
                    system("pause");
                    break;
                case 3:
                    system("cls");
                    printObat(headobat);
                    system("pause");
                    break;
                case 4:
                    system("cls");
                    printAlat(headalat);
                    system("pause");
                    break;
                case 5:
                    // Kembali ke Menu Utama
                    break;
                default:
                    cout << "Pilihan tidak valid." << endl;
                    system("pause");
                    break;
                }
            } while (subpilihan != 5);
        }
        else if (pilihan == 4) {
            // Keluar dari program
            cout << "Terima kasih telah menggunakan layanan Rajawali Care. Sehat Selalu!\n";
        }
        else {
            cout << "Pilihan tidak valid. Silakan pilih lagi.\n";
        }

    } while (pilihan != 4);

    return 0;
}
