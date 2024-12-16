#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
        printf("_\n");
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

void sortingKendaraan(Kendaraan *knd, int jmlKendaraan, char mode, char order) {
    // Metode Bubble Sort
    for (int i = 0; i < jmlKendaraan - 1; i++) {
        for (int j = jmlKendaraan - 1; j > i; j--) {
            int swap = 0; // swap pengkondisian untuk penggeseran (bubble sort)

            switch (mode) {
                case 'h': // Berdasarkan Harga
                    if ((order == 'a' || order == 'A') && knd[j].harga < knd[j - 1].harga)
                        swap = 1;
                    else if ((order == 'b' || order == 'B') && knd[j].harga > knd[j - 1].harga)
                        swap = 1;
                    break;

                case 'n': // Berdasarkan NOPOL
                    if ((order == 'a' || order == 'A') && strcmp(knd[j].nopol, knd[j - 1].nopol) < 0)
                        swap = 1;
                    else if ((order == 'b' || order == 'B') && strcmp(knd[j].nopol, knd[j - 1].nopol) > 0)
                        swap = 1;
                    break;

                case 'j': // Berdasarkan Jenis
                    if ((order == 'a' || order == 'A') && strcmp(knd[j].jenis, knd[j - 1].jenis) < 0)
                        swap = 1;
                    else if ((order == 'b' || order == 'B') && strcmp(knd[j].jenis, knd[j - 1].jenis) > 0)
                        swap = 1;
                    break;

                case 't': // Berdasarkan Tipe
                    if ((order == 'a' || order == 'A') && strcmp(knd[j].tipe, knd[j - 1].tipe) < 0)
                        swap = 1;
                    else if ((order == 'b' || order == 'B') && strcmp(knd[j].tipe, knd[j - 1].tipe) > 0)
                        swap = 1;
                    break;

                 case 's': // Berdasarkan Harga
                    if ((order == 'a' || order == 'A') && knd[j].status < knd[j - 1].status)
                        swap = 1;
                    else if ((order == 'b' || order == 'B') && knd[j].status > knd[j - 1].status)
                        swap = 1;
                    break;

                default:
                    printf("Mode pengurutan tidak valid.\n");
                    return;
            }

            if (swap) {
                Kendaraan temp = knd[j];
                knd[j] = knd[j - 1];
                knd[j - 1] = temp;
            }
        }
    }
}

void cariKendaraan(Kendaraan *knd, int jmlKendaraan){
    char cari[10];
    printf("Masukkan Nopol Kendaraan yang ingin dicari: ");
    scanf(" %[^\n]", cari);

   sortingKendaraan(knd, jmlKendaraan, 'n', 'a');

    int flag = 0;
    int jump = floor(sqrt(jmlKendaraan)); // jump
    int start = 0; // iterasi
    int end = jump;

    while(strcmp(knd[end].nopol, cari) < 0  && end < jmlKendaraan){
        start += jump;
        end += jump;
        if(end >= jmlKendaraan-1){
            end = jmlKendaraan;
        }
    }

    for(start; start <= end-1; start++){

        if(strcmp(knd[start].nopol, cari) == 0){
            flag = 1;
        printf("_\n");
        printf("Nopol: %s\n", knd[start].nopol);
        printf("Jenis Kendaraan: %s\n", knd[start].jenis);
        printf("Tipe Kendaraan: %s\n", knd[start].tipe);
        printf("Harga Sewa: %d\n", knd[start].harga);
            if(knd[start].status == 0 ){
                printf("Status: Tersedia\n");
            }
            else{
             printf("Status: Tidak Tersedia\n");
            }
        printf("_\n");
        }

    }
    if(flag == 1){
        printf("Data Ditemukan\n");
    }
    else {
        printf("Data Tidak Ditemukan\n");
    }
}

void tambahKendaraan(Kendaraan *knd, int *jmlKendaraan){
    printf("\n=== Tambahkan Kendaraan Baru ===\n");
    printf("Plat Nomor Kendaraan: ");
    scanf(" %[^\n]", knd[*jmlKendaraan].nopol);

     printf("Jenis Kendaraan: ");
    scanf(" %[^\n]", knd[*jmlKendaraan].jenis);

     printf("Tipe Kendaraan: ");
    scanf(" %[^\n]", knd[*jmlKendaraan].tipe);

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

void sortPelangganByName(Pelanggan *plg, int jmlPelanggan, char mode) {
    printf("\n=== Sorting Pelanggan Berdasarkan Nama ===\n");
    if (jmlPelanggan == 0) {
        printf("Belum ada pelanggan yang terdaftar. Sorting tidak dapat dilakukan.\n");
        return;
    }

    int i, j, targetIndex;
    Pelanggan temp;

    for (i = 0; i < jmlPelanggan - 1; i++) {
        targetIndex = i;
        for (j = i + 1; j < jmlPelanggan; j++) {
            // Mode ascending
            if (mode == 'a' && strcmp(plg[j].nama, plg[targetIndex].nama) < 0) {
                targetIndex = j;
            }
            // Mode descending
            else if (mode == 'b' && strcmp(plg[j].nama, plg[targetIndex].nama) > 0) {
                targetIndex = j;
            }
        }

        // Tukar pelanggan jika diperlukan
        if (targetIndex != i) {
            temp = plg[i];
            plg[i] = plg[targetIndex];
            plg[targetIndex] = temp;
        }
    }

    printf("Sorting pelanggan berdasarkan nama selesai. Berikut daftar pelanggan yang telah diurutkan:\n");
    tampilkanPelanggan(plg, jmlPelanggan);
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
        printf("_\n");
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

     int subMenuTampilPelanggan;
     int subMenuTampilKendaraan;

     char mode; // ascending or descending

     int subMenuPelanggan;
     int subMenuKendaraan;

     int pilihanUtama;

    bacaFileKendaraan(knd, &jmlKendaraan);
    bacaFilePelanggan(plg, &jmlPelanggan);


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
                printf("2. Cari Kendaraan\n");
                printf("3. Tambah Kendaraan\n");
                printf("4. Ubah Data Kendaraan\n");
                printf("5. Hapus Data Kendaraan\n");
                printf("6. Kembali ke Menu Utama\n");
                printf("Pilih Sub-menu: ");

                scanf("%d", &subMenuKendaraan);

                switch (subMenuKendaraan) {
                    case 1:
                    printf("\n=== TAMPILKAN DATA KENDARAAN ===\n");
                    printf("1. Tampilkan Seluruh Kendaraan\n");
                    printf("2. Urutkan Berdasarkan NOPOL\n");
                    printf("3. Urutkan Berdasarkan Jenis\n");
                    printf("4. Urutkan Berdasarkan Tipe\n");
                    printf("5. Urutkan Berdasarkan Harga\n");
                    printf("6. Urutkan Berdasarkan Status\n");
                    printf("7. Kembali ke Menu Utama\n");
                    printf("Pilih untuk menampilkan kendaraan: ");

                    scanf("%d", &subMenuTampilKendaraan);
                    if(subMenuTampilKendaraan >=2 && subMenuTampilKendaraan <7){
                    printf("a. Ascending\n");
                    printf("b. Descending\n");
                    printf("Urutkan berdasarkan (a-b) : ");
                    scanf(" %c", &mode);
                    }
                    switch (subMenuTampilKendaraan) {
                        case 1:
                            printf("\n=== TAMPILKAN SELURUH KENDARAAN ===\n");
                            tampilkanKendaraan(knd, jmlKendaraan);
                            break;

                        case 2:
                            printf("\n=== URUTKAN KENDARAAN BERDASARKAN NOPOL ===\n");
                            sortingKendaraan(knd, jmlKendaraan, 'n', mode); // 'n' untuk sorting berdasarkan NOPOL
                            tampilkanKendaraan(knd, jmlKendaraan);
                            break;

                        case 3:
                            printf("\n=== URUTKAN KENDARAAN BERDASARKAN JENIS ===\n");
                            sortingKendaraan(knd, jmlKendaraan, 'j', mode); // 'j' untuk sorting berdasarkan Jenis
                            tampilkanKendaraan(knd, jmlKendaraan);
                            break;

                        case 4:
                            printf("\n=== URUTKAN KENDARAAN BERDASARKAN TIPE ===\n");
                            sortingKendaraan(knd, jmlKendaraan, 't', mode); // 't' untuk sorting berdasarkan Tipe
                            tampilkanKendaraan(knd, jmlKendaraan);
                            break;

                        case 5:
                            printf("\n=== URUTKAN KENDARAAN BERDASARKAN HARGA ===\n");
                            sortingKendaraan(knd, jmlKendaraan, 'h', mode); // 'h' untuk sorting berdasarkan Harga
                            tampilkanKendaraan(knd, jmlKendaraan);
                            break;

                        case 6:
                            printf("\n=== URUTKAN KENDARAAN BERDASARKAN STATUS ===\n");
                            sortingKendaraan(knd, jmlKendaraan, 's', mode); // 's' untuk sorting berdasarkan Status
                            tampilkanKendaraan(knd, jmlKendaraan);
                            break;

                        case 7:
                            printf("Kembali ke Menu Kendaraan.\n");
                            break;

                        default:
                            printf("Pilihan tidak valid.\n");
                            break;
                        }
                        break;
                    case 2:

                      cariKendaraan(knd, jmlKendaraan);
                      break;
                    case 3:
                       tambahKendaraan(knd, &jmlKendaraan);
                        break;
                    case 4:
                       updateKendaraan(knd, jmlKendaraan);
                        break;
                    case 5:
                       deleteKendaraan(knd, &jmlKendaraan);
                        break;
                    case 6:
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
                printf("2. Cari Pelanggan\n");
                printf("3. Tambah Pelanggan\n");
                printf("4. Update Pelanggan\n");
                printf("5. Hapus Pelanggan\n");
                printf("6. Kembali ke Menu Utama\n");
                printf("Pilih Sub-menu: ");

                scanf("%d", &subMenuPelanggan);

                switch (subMenuPelanggan) {
                    case 1:
                         printf("\n=== TAMPILKAN DATA PELANGGAN ===\n");
                    printf("1. Tampilkan Seluruh Pelanggan\n");
                    printf("2. Urutkan Berdasarkan Id\n");
                    printf("3. Urutkan Berdasarkan Nama\n");
                    printf("4. Kembali ke Menu Utama\n");
                    printf("Pilih untuk menampilkan pelanggan: ");

                    scanf("%d", &subMenuTampilPelanggan);
                    if(subMenuTampilPelanggan >=2 && subMenuTampilPelanggan <4){
                    printf("a. Ascending\n");
                    printf("b. Descending\n");
                    printf("Urutkan berdasarkan (a-b) : ");
                    scanf(" %c", &mode);
                    }
                    switch (subMenuTampilPelanggan) {
                        case 1:
                            printf("\n=== TAMPILKAN SELURUH PELANGGAN ===\n");
                            tampilkanPelanggan(plg,jmlPelanggan);
                            break;

                        case 2:
                            printf("\n=== URUTKAN KENDARAAN BERDASARKAN ID ===\n");

                            break;

                        case 3:
                            printf("\n=== URUTKAN KENDARAAN BERDASARKAN NAMA ===\n");
                            sortPelangganByName(plg, jmlPelanggan, mode);
                            break;

                        case 4:
                            printf("Kembali ke Menu Kendaraan.\n");
                            break;

                        default:
                            printf("Pilihan tidak valid.\n");
                            break;
                        }
                        // tampilkanPelanggan(plg, jmlPelanggan);
                        break;
                    case 2:

                        break;
                    case 3:
                        tambahPelanggan(plg, &jmlPelanggan);
                        break;
                    case 4:
                         updatePelanggan(plg, jmlPelanggan);
                        break;
                    case 5:
                        deletePelanggan(plg, &jmlPelanggan);
                        break;
                    case 6:
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
