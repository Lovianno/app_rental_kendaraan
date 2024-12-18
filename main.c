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
    char KodeTransaksi[20];
    char nopol[10];
    int idPelanggan;
    int durasi;
    int totalHarga;

} Transaksi;


int getIndexKendaraan; // untuk mendapatkan index kendaraan
int getIndexPelanggan; // untuk mendapatkan index pelanggan

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

 void cariKendaraan(Kendaraan *knd, int jmlKendaraan) {
    char cari[10];

    if (jmlKendaraan == 0) {
        printf("Belum ada data kendaraan untuk dicari\n");
        return;
    }

    printf("Masukkan Nopol Kendaraan yang ingin dicari: ");
    scanf(" %[^\n]", cari);

    sortingKendaraan(knd, jmlKendaraan, 'n', 'a'); // Pastikan data sudah terurut

    int flag = 0; // Menandai apakah data ditemukan
    int jump = floor(sqrt(jmlKendaraan)); // Langkah lompat
    int start = 0; // Awal iterasi
    int end = jump;

    // Jumping Search: Mencari blok yang mungkin mengandung data
    while (start < jmlKendaraan && strcmp(knd[end - 1].nopol, cari) < 0) {
        start = end;
        end += jump;
        if (end >= jmlKendaraan) {
            end = jmlKendaraan; // Pastikan tidak melebihi batas array
        }
    }

    // Linear Search dalam blok yang ditemukan
    for (int i = start; i < end; i++) {
        if (strcmp(knd[i].nopol, cari) == 0) {
            flag = 1;
            printf("_________\n");
            printf("Nopol: %s\n", knd[i].nopol);
            printf("Jenis Kendaraan: %s\n", knd[i].jenis);
            printf("Tipe Kendaraan: %s\n", knd[i].tipe);
            printf("Harga Sewa: %d\n", knd[i].harga);
            if (knd[i].status == 0) {
                printf("Status: Tersedia\n");
            } else {
                printf("Status: Tidak Tersedia\n");
            }
            getIndexKendaraan = i; // Simpan indeks kendaraan yang ditemukan
            printf("_________\n");
            break; // Hentikan pencarian setelah data ditemukan
        }
    }

    // Jika data tidak ditemukan, beri output
    if (!flag) {
        getIndexKendaraan = -1; // Tandai bahwa data tidak ditemukan
        printf("Data Tidak Ditemukan\n");
    }
    else{
        printf("Data Ditemukan\n");
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
        //printf("Data kendaraan berhasil disimpan ke file.\n");
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
       // printf("Data Kendaraan berhasil dibaca dari file %s.\n", "kendaraan.txt");
    }
    void updateKendaraan(Kendaraan *knd, int jmlKendaraan) {
        // Mencari kendaraan berdasarkan nopol
        cariKendaraan(knd,jmlKendaraan);
        if(getIndexKendaraan != -1){
        printf("Silakan Masukan Kendaraan Baru:\n");

                printf("Plat Nomor Kendaraan: ");
                scanf(" %[^\n]", knd[getIndexKendaraan].nopol);

                printf("Jenis Kendaraan: ");
                scanf(" %[^\n]", knd[getIndexKendaraan].jenis);

                printf("Tipe Kendaraan: ");
                scanf(" %[^\n]", knd[getIndexKendaraan].tipe);

                printf("Harga Sewa Perhari: ");
                scanf("%d", &knd[getIndexKendaraan].harga);

                // Status tetap tidak berubah
                printf("Data Kendaraan Berhasil Diperbarui.\n");
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
    void sortPelangganById(Pelanggan *plg, int jmlPelanggan, char mode) {
    if (jmlPelanggan == 0) {
        printf("Belum ada pelanggan yang terdaftar. Sorting tidak dapat dilakukan.\n");
        return;
    }

    int i, j;
    Pelanggan temp;

    // Insertion Sort
    for (i = 1; i < jmlPelanggan; i++) {
        temp = plg[i];
        j = i - 1;

        if (mode == 'a') { // Ascending
            while (j >= 0 && plg[j].id > temp.id) {
                plg[j + 1] = plg[j];
                j--;
            }
        }
        else if (mode == 'b') { // Descending
            while (j >= 0 && plg[j].id < temp.id) {
                plg[j + 1] = plg[j];
                j--;
            }
        } else {
            printf("Mode tidak valid! Gunakan 'a' untuk ascending atau 'd' untuk descending.\n");
            return;
        }


        plg[j + 1] = temp;
    }
    }
    void sortPelangganByName(Pelanggan *plg, int jmlPelanggan, char mode) {
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

      //  printf("Sorting pelanggan berdasarkan nama selesai. Berikut daftar pelanggan yang telah diurutkan:\n");
       // tampilkanPelanggan(plg, jmlPelanggan);
    }

   void cariPelanggan(Pelanggan *plg, int jmlPelanggan, char mode) {
    if (jmlPelanggan == 0) {
        printf("Belum ada data pelanggan untuk dicari\n");
        return;
    }

    // Variabel pencarian
    char cariNama[50];
    int cariId;

    if (mode == 'n') {
        printf("Masukkan Nama Pelanggan yang ingin dicari: ");
        scanf(" %[^\n]", cariNama);

        // Sort pelanggan berdasarkan nama (ascending)
        sortPelangganByName(plg, jmlPelanggan, 'a');
    } else if (mode == 'i') {
        printf("Masukkan ID Pelanggan yang ingin dicari: ");
        scanf("%d", &cariId);

        // Sort pelanggan berdasarkan ID (ascending)
        sortPelangganById(plg, jmlPelanggan, 'a');
    } else {
        printf("Mode pencarian tidak valid.\n");
        return;
    }

    // Jumping Search
    int flag = 0;
    int jump = sqrt(jmlPelanggan); // langkah pencarian
    int start = 0;                // indeks awal
    int end = jump;

    while (start < jmlPelanggan) {
        // Tentukan batas akhir agar tidak melewati indeks array
        if (end > jmlPelanggan) end = jmlPelanggan;

        // Cek apakah data mungkin ada dalam rentang ini
        if (mode == 'n' && strcmp(plg[end - 1].nama, cariNama) >= 0) {
            break;
        }
        if (mode == 'i' && plg[end - 1].id >= cariId) {
            break;
        }

        start = end;
        end += jump;
    }

    // Pencarian linear pada rentang yang ditemukan
    for (int i = start; i < end; i++) {
        if ((mode == 'n' && strcmp(plg[i].nama, cariNama) == 0) ||
            (mode == 'i' && plg[i].id == cariId)) {
            flag = 1;
            printf("_\n");
            printf("ID: %d\n", plg[i].id);
            printf("Nama Pelanggan: %s\n", plg[i].nama);
            printf("Nomor Kontak: %s\n", plg[i].nomorKontak);
            getIndexPelanggan = i; // Simpan indeks pelanggan
            printf("_\n");
            break;
        }
    }

    if (flag) {
        printf("Data Ditemukan\n");
    } else {
        getIndexPelanggan = -1; // Tandai data tidak ditemukan
        printf("Data Tidak Ditemukan\n");
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
        //printf("Data pelanggan berhasil disimpan ke file.\n");
    }

    void updatePelanggan(Pelanggan *plg, int jmlPelanggan) {
        printf("\n=== Update Data Pelanggan ===\n");
        cariPelanggan(plg,jmlPelanggan, 'i');
        if(getIndexPelanggan != -1){
        printf("Silakan Masukkan Data Pelanggan Baru:\n");
               printf("Masukkan Nama Baru: ");
                scanf(" %[^\n]", plg[getIndexPelanggan].nama); // Input nama

                printf("Masukkan Nomor Kontak Baru: ");
                scanf(" %[^\n]", plg[getIndexPelanggan].nomorKontak); // Input nomor kontak

                printf("Data Pelanggan berhasil Diperbarui.\n");
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
       // printf("Data pelanggan berhasil dibaca dari file %s.\n", "pelanggan.txt");
    }

 void tambahTransaksi(Transaksi *tr, int *jmlTransaksi, Kendaraan *knd, int jmlKendaraan ,Pelanggan *plg, int jmlPelanggan) {

    tampilkanKendaraan(knd, jmlKendaraan);
    do{
    printf("\n");
    cariKendaraan(knd, jmlKendaraan);

    if(knd[getIndexKendaraan].status != 0 || getIndexKendaraan == -1){
        printf("Kendaraan Tidak Tersedia, Harap Pilih Kendaraan Lain\n");
     }
    }
    while(knd[getIndexKendaraan].status != 0 || getIndexKendaraan == -1);

    sortPelangganById(plg, jmlPelanggan, 'a');
    tampilkanPelanggan(plg, jmlPelanggan);
    do{
    printf("\n");
    cariPelanggan(plg, jmlPelanggan, 'i');
    if(getIndexPelanggan == -1){
        printf("Pelanggan Tidak Ditemukan, Tambahkan Pelanggan Jika Belum Terdaftar!\n");
     }
    }
     while( getIndexPelanggan == -1);

    printf("\nMasukkan durasi sewa (dalam hari): ");
    scanf("%d", &tr[*jmlTransaksi].durasi);

    sprintf(tr[*jmlTransaksi].KodeTransaksi, "TR%03d", *jmlTransaksi + 1);
    strcpy(tr[*jmlTransaksi].nopol, knd[getIndexKendaraan].nopol);
    tr[*jmlTransaksi].idPelanggan = plg[getIndexPelanggan].id;
    tr[*jmlTransaksi].totalHarga = knd[getIndexKendaraan].harga * tr[*jmlTransaksi].durasi;
    knd[getIndexKendaraan].status = 1;
    (*jmlTransaksi)++;

    printf("\n=== Transaksi Berhasil ===\n");
    printf("Kode Transaksi: %s\n", tr[*jmlTransaksi - 1].KodeTransaksi);
    printf("No. Polisi: %s\n", tr[*jmlTransaksi - 1].nopol);
    printf("ID Pelanggan: %d\n", tr[*jmlTransaksi - 1].idPelanggan);
    printf("Durasi: %d hari\n", tr[*jmlTransaksi - 1].durasi);
    printf("Total Harga: %d\n", tr[*jmlTransaksi - 1].totalHarga);
}

void ubahStatusKendaraan(Kendaraan *knd, int jmlKendaraan){
    do{
    printf("\n");
    cariKendaraan(knd, jmlKendaraan);


    if(getIndexKendaraan == -1){
        printf("Kendaraan Tidak Tersedia, Harap Pilih Kendaraan Lain\n");
     }
    }
  while(getIndexKendaraan == -1);
  knd[getIndexKendaraan].status = 0;

  printf("Status Kendaraan Telah di Ubah || Pesanan Selesai \n");
}

void tampilkanTransaksi(Transaksi *tr, int jmlTransaksi) {
    printf("\n=== DAFTAR TRANSAKSI ===\n");
    if (jmlTransaksi == 0) {
        printf("Belum ada transaksi.\n");
        return;
    }
    for (int i = 0; i < jmlTransaksi; i++) {
        printf("_________\n");
        printf("Transaksi ke-%d\n", i + 1);
        printf("Kode Transaksi: %s\n", tr[i].KodeTransaksi);
        printf("Nopol: %s\n", tr[i].nopol);
        printf("Durasi: %d Hari\n", tr[i].durasi);
        printf("Total Harga: %d\n", tr[i].totalHarga);
    }
}

void simpanTransaksi(Transaksi *tr, int jmlTransaksi) {
    FILE *file = fopen("transaksi.txt", "w");
    if (!file) {
        printf("Gagal membuka file untuk menyimpan transaksi.\n");
        return;
    }
    for (int i = 0; i < jmlTransaksi; i++) {
        fprintf(file, "%s,%s,%d,%d,%d\n", tr[i].KodeTransaksi, tr[i].nopol, tr[i].idPelanggan, tr[i].durasi, tr[i].totalHarga);
    }
    fclose(file);
  //  printf("Data Transaksi berhasil disimpan ke file.\n");
}

void bacaFileTransaksi(Transaksi *tr, int *jmlTransaksi) {
    FILE *file = fopen("transaksi.txt", "r");
    if (!file) {
        printf("Gagal membuka file untuk membaca transaksi.\n");
        return;
    }

    *jmlTransaksi = 0; // Reset jumlah transaksi sebelum membaca

    while (fscanf(file, "%[^,],%[^,],%d,%d,%d\n",
                  tr[*jmlTransaksi].KodeTransaksi,
                  tr[*jmlTransaksi].nopol,
                  &tr[*jmlTransaksi].idPelanggan,
                  &tr[*jmlTransaksi].durasi,
                  &tr[*jmlTransaksi].totalHarga) != EOF)
    {
        (*jmlTransaksi)++;
    }

    fclose(file);
   // printf("Data Transaksi berhasil dibaca dari file.\n");
}


    // Fungsi utama
    int main() {
        Pelanggan plg[100];
        Kendaraan knd[100];
        Transaksi tr[100];

        int jmlKendaraan = 0;
        int jmlPelanggan = 0;
        int jmlTransaksi = 0;

        char mode; // ascending or descending

        int subMenuPelanggan;
        int subMenuKendaraan;
        int subMenuTransaksi;

        int subMenuTampilPelanggan;
        int subMenuTampilKendaraan;

        int pilihanUtama;

        bacaFileKendaraan(knd, &jmlKendaraan);
        bacaFilePelanggan(plg, &jmlPelanggan);
        bacaFileTransaksi(tr, &jmlTransaksi);


        do {
            printf("\n=== SISTEM MANAJEMEN RENTAL ===\n");
            printf("1. Data Kendaraan\n");
            printf("2. Data Pelanggan\n");
            printf("3. Transaksi\n");
            printf("4. Laporan Transaksi\n");
            printf("5. Simpan dan Keluar\n");
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
                                sortPelangganById(plg, jmlPelanggan, mode);
                                tampilkanPelanggan(plg,jmlPelanggan);
                                break;

                            case 3:
                                printf("\n=== URUTKAN KENDARAAN BERDASARKAN NAMA ===\n");
                                sortPelangganByName(plg, jmlPelanggan, mode);
                                tampilkanPelanggan(plg, jmlPelanggan);
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
                            cariPelanggan(plg, jmlPelanggan, 'n');
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
                                        printf("\n=== TRANSAKSI ===\n");
                    printf("1. Tambah Transaksi\n");
                    printf("2. Selesaikan Transaksi\n");
                    printf("3. Kembali ke Menu Utama\n");
                    printf("Pilih Menu : ");
                    scanf("%d", &subMenuTransaksi);

                    switch(subMenuTransaksi){
                    case 1 :
                        printf("\n=== TAMBAH TRANSAKSI ===\n");
                        tambahTransaksi(tr, &jmlTransaksi, knd, jmlKendaraan, plg, jmlPelanggan);
                    // printf("%s", plg[getIndexPelanggan].nama);
                        break;
                    case 2 :
                        ubahStatusKendaraan(knd, jmlKendaraan);
                        break;
                    case 3 :
                        printf("Kembali Ke Menu Utama\n");
                        break;
                    default:
                        printf("Pilihan tidak valid.\n");
                        break;
                    }
                break;
                case 4:
                tampilkanTransaksi(tr, jmlTransaksi);
               // printf("Keluar dari program.\n");
                break;
            case 5:
                simpanKendaraan(knd, jmlKendaraan);
                simpanPelanggan(plg, jmlPelanggan);
                simpanTransaksi(tr, jmlTransaksi);
                printf("Keluar dari program.\n");
                break;
                default:
                    printf("Pilihan tidak valid.\n");
                    break;
            }
        } while (pilihanUtama != 5);

        return 0;
    }
