#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nopol[10];
    char jenis[20];
    char tipe[30];
    int harga;
    int status;

} Kendaraan;
typedef struct{
    int id;
    char nama[50];
    char nomorKontak[20];
} Pelanggan;

typedef struct{
    int idTransaksi;
    int idKendaraan;
    int idPelanggan;
    int durasi;

} Transaksi;

void tampilkanKendaraan(Kendaraan *knd, int jmlKendaraan) {
    printf("\n=== DAFTAR KENDARAAN ===\n");
    if (jmlKendaraan == 0) {
        printf("Belum ada kendaraan yang terdaftar.\n");
        return;
    }
    for (int i = 0; i < jmlKendaraan; i++) {
        printf("___________________________\n");
        printf("Kendaraan ke-%d\n", i + 1);
        printf("Nopol: %s\n", knd[i].nopol);
        printf("Jenis Kendaraan: %s\n", knd[i].jenis);
        printf("Tipe Kendaraan: %s\n", knd[i].tipe);
        printf("Harga Sewa: %d\n", knd[i].harga);
        if(knd[i].status == 0 ){
            printf("Status: Tersedia\n");
        }
        else{
             printf("Status: Tidak Tersedia\n");
        }
    }
}

void tambahKendaraan(Kendaraan *knd, int *jmlKendaraan){
    printf("\n=== Tambahkan Kendaraan Baru ===\n");
    printf("Plat Nomor Kendaraan: ");
    scanf(" %s", knd[*jmlKendaraan].nopol);

     printf("Jenis Kendaraan: ");
    scanf(" %s", knd[*jmlKendaraan].jenis);

     printf("Tipe Kendaraan: ");
    scanf(" %s", knd[*jmlKendaraan].tipe);

    printf("Harga Sewa Perhari: ");
    scanf("%d", &knd[*jmlKendaraan].harga);
    knd[*jmlKendaraan].status = 0;

     (*jmlKendaraan)++;



    printf("Kendaraan Berhasil Ditambahkan!\n");
}
void simpanKendaraan(Kendaraan *knd, int jmlKendaraan) {
    FILE *file = fopen("kendaraan.txt", "w");
    if (!file) {
        printf("Gagal membuka file untuk menyimpan kendaraan.\n");
        return;
    }

    for (int i = 0; i < jmlKendaraan; i++) {
        fprintf(file, "%s,%s,%s,%d,%d\n",
                knd[i].nopol, knd[i].jenis, knd[i].tipe,
                knd[i].harga, knd[i].status);
    }

    fclose(file);
    printf("Data kendaraan berhasil disimpan ke file.\n");
}



void bacaFileKendaraan(Kendaraan *knd, int *jmlKendaraan) {
    FILE *file = fopen("kendaraan.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file: %s\n", "kendaraan.txt");
        *jmlKendaraan = 0; // Set jumlah pelanggan ke 0 jika file tidak ditemukan
        return;
    }

    *jmlKendaraan = 0; // Inisialisasi jumlah pelanggan
    while (fscanf(file, "%[^,],%[^,],%[^,],%d,%d\n", knd[*jmlKendaraan].nopol, knd[*jmlKendaraan].jenis, knd[*jmlKendaraan].tipe, &knd[*jmlKendaraan].harga, &knd[*jmlKendaraan].status) != EOF) {
        (*jmlKendaraan)++;
    }

    fclose(file);
    printf("Data Kendaraan berhasil dibaca dari file %s.\n", "kendaraan.txt");
}
void updateKendaraan(Kendaraan *knd, int jmlKendaraan) {
    char nopolCari[10];
    int found = 0;

    // Mencari kendaraan berdasarkan nopol
    printf("Masukkan Nopol Kendaraan yang ingin diupdate: ");
    scanf(" %[^\n]", nopolCari);

    for (int i = 0; i < jmlKendaraan; i++) {
        if (strcmp(knd[i].nopol, nopolCari) == 0) {
            found = 1;
            // Memperbarui data kendaraan
            printf("Kendaraan ditemukan! Silakan masukkan data baru:\n");

            printf("Plat Nomor Kendaraan: ");
            scanf(" %[^\n]", knd[i].nopol);

            printf("Jenis Kendaraan: ");
            scanf(" %[^\n]", knd[i].jenis);

            printf("Tipe Kendaraan: ");
            scanf(" %[^\n]", knd[i].tipe);

            printf("Harga Sewa Perhari: ");
            scanf("%d", &knd[i].harga);

            // Status tetap tidak berubah
            printf("Kendaraan berhasil diupdate!\n");
            break;
        }
    }

    if (!found) {
        printf("Kendaraan dengan Nopol %s tidak ditemukan.\n", nopolCari);
    }
}

void deleteKendaraan(Kendaraan *knd, int *jmlKendaraan) {
    char nopolCari[10];
    int found = 0;

    // Mencari kendaraan berdasarkan nopol
    printf("Masukkan Nopol Kendaraan yang ingin dihapus: ");
    scanf(" %[^\n]", nopolCari);

    for (int i = 0; i < *jmlKendaraan; i++) {
        if (strcmp(knd[i].nopol, nopolCari) == 0) {
            found = 1;
            // Menggeser kendaraan setelah yang dihapus
            for (int j = i; j < *jmlKendaraan - 1; j++) {
                knd[j] = knd[j + 1]; // Geser elemen ke kiri
            }

            // Mengurangi jumlah kendaraan
            (*jmlKendaraan)--;

            printf("Kendaraan dengan Nopol %s telah berhasil dihapus.\n", nopolCari);
            break;
        }
    }

    if (!found) {
        printf("Kendaraan dengan Nopol %s tidak ditemukan.\n", nopolCari);
    }
}

void tambahPelanggan(Pelanggan *plg, int *jmlPelanggan) {
    printf("\n=== Tambahkan Pelanggan Baru ===\n");
    printf("ID Pelanggan: ");
    scanf("%d", &plg[*jmlPelanggan].id);

    printf("Nama Pelanggan: ");
    scanf(" %[^\n]", plg[*jmlPelanggan].nama);
    printf("Nomor Kontak: ");
    scanf(" %[^\n]", plg[*jmlPelanggan].nomorKontak);

    (*jmlPelanggan)++;

    printf("Pelanggan Berhasil Ditambahkan!\n");
}

void simpanPelanggan(Pelanggan *plg, int jmlPelanggan) {
    FILE *file = fopen("pelanggan.txt", "w");
    if (!file) {
        printf("Gagal membuka file untuk menyimpan pelanggan.\n");
        return;
    }
    for (int i = 0; i < jmlPelanggan; i++) {
        fprintf(file, "%d,%s,%s\n", plg[i].id, plg[i].nama, plg[i].nomorKontak);
    }
    fclose(file);
    printf("Data pelanggan berhasil disimpan ke file.\n");
}

void updatePelanggan(Pelanggan *plg, int jmlPelanggan) {
    int id, found = 0;
    printf("\n=== Update Pelanggan ===\n");
    printf("Masukkan ID Pelanggan yang ingin diperbarui: ");
    scanf("%d", &id);

    for (int i = 0; i < jmlPelanggan; i++) {
        if (plg[i].id == id) {
            found = 1;
            printf("Pelanggan ditemukan: Nama: %s, Nomor Kontak: %s\n", plg[i].nama, plg[i].nomorKontak);

            printf("Masukkan Nama Baru: ");
            scanf(" %[^\n]", plg[i].nama); // Input nama menggunakan scanf

            printf("Masukkan Nomor Kontak Baru: ");
            scanf(" %[^\n]", plg[i].nomorKontak); // Input nomor kontak menggunakan scanf

            printf("Data pelanggan berhasil diperbarui.\n");
            break;
        }
    }
    if (!found) {
        printf("Pelanggan dengan ID %d tidak ditemukan.\n", id);
    }
}


void deletePelanggan(Pelanggan *plg, int *jmlPelanggan) {
    int id, found = 0;
    printf("\n=== Hapus Pelanggan ===\n");
    printf("Masukkan ID Pelanggan yang ingin dihapus: ");
    scanf("%d", &id);

    for (int i = 0; i < *jmlPelanggan; i++) {
        if (plg[i].id == id) {
            found = 1;
            printf("Pelanggan ditemukan: Nama: %s, Nomor Kontak: %s\n", plg[i].nama, plg[i].nomorKontak);
            printf("Menghapus pelanggan...\n");

            // Menggeser data pelanggan berikutnya ke indeks saat ini
            for (int j = i; j < *jmlPelanggan - 1; j++) {
                plg[j] = plg[j + 1];
            }

            (*jmlPelanggan)--; // Mengurangi jumlah pelanggan
            printf("Pelanggan berhasil dihapus.\n");
            break;
        }
    }

    if (!found) {
        printf("Pelanggan dengan ID %d tidak ditemukan.\n", id);
    }
}



void tampilkanPelanggan(Pelanggan *plg, int jmlPelanggan) {
    printf("\n=== DAFTAR PELANGGAN ===\n");
    if (jmlPelanggan == 0) {
        printf("Belum ada pelanggan yang terdaftar.\n");
        return;
    }
    for (int i = 0; i < jmlPelanggan; i++) {
        printf("___________________________\n");
        printf("Pelanggan ke-%d\n", i + 1);
        printf("ID: %d\n", plg[i].id);
        printf("Nama: %s\n", plg[i].nama);
        printf("Nomor Kontak: %s\n", plg[i].nomorKontak);
    }
}



void bacaFilePelanggan(Pelanggan *plg, int *jmlPelanggan) {
    FILE *file = fopen("pelanggan.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file: %s\n", "pelanggan.txt");
        *jmlPelanggan = 0; // Set jumlah pelanggan ke 0 jika file tidak ditemukan
        return;
    }

    *jmlPelanggan = 0; // Inisialisasi jumlah pelanggan
    while (fscanf(file, "%d,%49[^,],%19[^\n]",
                  &plg[*jmlPelanggan].id,
                  plg[*jmlPelanggan].nama,
                  plg[*jmlPelanggan].nomorKontak) != EOF) {
        (*jmlPelanggan)++;
    }

    fclose(file);
    printf("Data pelanggan berhasil dibaca dari file %s.\n", "pelanggan.txt");
}

// Fungsi utama
int main() {
    Pelanggan plg[100];
    Kendaraan knd[100];

    int jmlKendaraan = 0;
    int jmlPelanggan = 0;

    bacaFileKendaraan(knd, &jmlKendaraan);
    bacaFilePelanggan(plg, &jmlPelanggan);

      int pilihanUtama;

    do {
        printf("\n=== SISTEM MANAJEMEN RENTAL ===\n");
        printf("1. Data Kendaraan\n");
        printf("2. Data Pelanggan\n");
        printf("3. Transaksi\n");
        printf("4. Simpan dan Keluar\n");
        printf("Pilih Menu: ");
        scanf("%d", &pilihanUtama);

        switch (pilihanUtama) {
            case 1:
                printf("\n=== DATA KENDARAAN ===\n");
                printf("1. Tampilkan Kendaraan\n");
                printf("2. Tambah Kendaraan\n");
                printf("3. Ubah Data Kendaraan\n");
                printf("4. Hapus Data Kendaraan\n");
                printf("5. Kembali ke Menu Utama\n");
                printf("Pilih Sub-menu: ");
                int subMenuKendaraan;
                scanf("%d", &subMenuKendaraan);

                switch (subMenuKendaraan) {
                    case 1:
                       tampilkanKendaraan(knd, jmlKendaraan);
                        break;
                    case 2:
                       tambahKendaraan(knd, &jmlKendaraan);
                        break;
                    case 3:
                       updateKendaraan(knd, jmlKendaraan);
                        break;
                    case 4:
                       deleteKendaraan(knd, &jmlKendaraan);
                        break;
                    case 5:
                        printf("Kembali ke Menu Utama.\n");
                        break;
                    default:
                        printf("Pilihan tidak valid.\n");
                        break;
                }
                break;

            case 2:
                printf("\n=== DATA PELANGGAN ===\n");
                printf("1. Tampilkan Pelanggan\n");
                printf("2. Tambah Pelanggan\n");
                printf("3. Update Pelanggan\n");
                printf("4. Hapus Pelanggan\n");
                printf("5. Kembali ke Menu Utama\n");
                printf("Pilih Sub-menu: ");
                  int subMenuPelanggan;
                scanf("%d", &subMenuPelanggan);

                switch (subMenuPelanggan) {
                    case 1:
                         tampilkanPelanggan(plg, jmlPelanggan);
                        break;
                    case 2:
                        tambahPelanggan(plg, &jmlPelanggan);
                        break;
                    case 3:
                         updatePelanggan(plg, jmlPelanggan);
                        break;
                    case 4:
                        deletePelanggan(plg, &jmlPelanggan);
                        break;
                    case 5:
                        printf("Kembali ke Menu Utama.\n");
                        break;
                    default:
                        printf("Pilihan tidak valid.\n");
                        break;
                }
                break;

            case 3:
                simpanPelanggan(plg, jmlPelanggan);
                printf("Keluar dari program.\n");
                break;
            case 4:
                simpanKendaraan(knd, jmlKendaraan);
                simpanPelanggan(plg, jmlPelanggan);
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    } while (pilihanUtama != 4);

    return 0;
}
