#include <iostream>
#include <bits/stdc++.h>

using namespace std;

string songfile = "lagu.csv";
string accountfile = "user.csv";
string historyfile = "history.csv";

struct lagu // mendeklarasikan atau membuat strukur data struct dengan nama lagu
{
    int id;                // mendeklarasikan id dgn type data integer
    string judul;          // mendeklarasikan judul dgn type data string
    string artist;         // mendeklarasikan artis dgn type data string
    string jmlh_pendengar; // mendeklarasikan jumlah pendengar dgn type data string
    string genre;          // mendeklarasikan genre dgn type data string
    string theme;          // mendeklarasikan theme dgn type data string
    string instrumen;      // mendeklarasikan instrumen dgn type data string
    lagu *next = NULL;     // mendeklarasikan pointer next pada lagu yang pada awalnya menunjuk kelokasi yang ga valid
    lagu *prev = NULL;     // mendeklarasikan pointer prev pada lagu yang pada awalnya menunjuk kelokasi yang ga valid
};

struct history // pendeklarasian atau membuat struct histori
{
    string username;    // username dari customer yang telah membuat akun
    string id_history1; // variabel yang menyimpan histori dari akun cust
    string id_history2; // variabel yang menyimpan histori dari akun cust
    string id_history3; // variabel yang menyimpan histori dari akun cust
    string id_history4; // variabel yang menyimpan histori dari akun cust
    string id_history5; // variabel yang menyimpan histori dari akun cust
};

struct user // pendeklarasian dari struct user
{
    string username; // variabel yang menyimpan username cust
    string password; // variabel yang menyimpan password cust
};

// berikut adalah fungsi untuk menambahkan data kedalam struct lagu
lagu *newnode()
{
    lagu *nodebaru = new lagu; // membuat nodebaru dengan tipe data lagu lalu menggunakan new untuk mengalokasikan memori untuk satu objek dari stuct lagu
    cout << "Masukan ID: ";
    cin >> nodebaru->id; // untuk mengambil input begitu juga untuk codingan dibawahnya
    cout << "Masukan Judul: ";
    fflush(stdin);
    getline(cin, nodebaru->judul);
    cout << "Masukan Artist: ";
    fflush(stdin);
    getline(cin, nodebaru->artist);
    cout << "Masukan Jumlah Pendengar: ";
    fflush(stdin);
    getline(cin, nodebaru->jmlh_pendengar);
    cout << "Masukan Genre: ";
    fflush(stdin);
    getline(cin, nodebaru->genre);
    cout << "Masukan Tema: ";
    fflush(stdin);
    getline(cin, nodebaru->theme);
    cout << "Masukan Instrumen: ";
    fflush(stdin);
    getline(cin, nodebaru->instrumen);
    // nodebaru->next = NULL;
    return nodebaru; // berfungsi mengembalikan nilai nodebaru
}

int length(lagu *head) // deklarasi fungsi length dengan parameter pointer ke lagu yang disebut head
{
    int panjang = 0;     // variabel panjang difungsikan untuk menyimpan panjang linked list
    lagu *temp = head;   // pointer temp diinisialisasi dengan alamat awal linkedlist
    while (temp != NULL) // perulangan dilakukan terus menuerus selama null tidak samadengan null
    {
        temp = temp->next; // pada tiap perulangan, temp diarahkan ke elemen berikutnya pada linked list
        panjang++;         // menambah satu pada setiap perulangannya, untuk menghitung panjang elemen
    }
    return panjang; // setelah perulangan selesai, return mengembalikan nilai yang telah dihitung tadi
}

bool isEmpty(lagu *head, lagu *tail) // fungsi is empty dibuat untuk mengecek apakah linked list yang ada kosong atu tidak kosong
{
    if (head == NULL && tail == NULL) // memeriksa apakah head dan tail menunjuk ke arah null, kondisi ini dapat disimpulkan bahwa linked list masih kosong
    {
        return true; // mengembalikan nilai true, artinya linked list kosong
    }
    return false; // megembalikan nilai false, artinya linked list ada isinya
}

void exportToCSV(string &filename, lagu &nodebaru)
{
    ofstream file(filename, ios::app);
    if (!file.is_open())
    {
        cerr << "Gagal membuka file " << filename << endl;
        return;
    }

    lagu *current = &nodebaru;
    file << "\n"
         << current->id << ","
         << current->judul << ","
         << current->artist << ","
         << current->jmlh_pendengar << ","
         << current->genre << ","
         << current->theme << ","
         << current->instrumen;

    file.close();
}

void updateCSV(lagu *head, int &id)
{
    ofstream file(songfile, ios :: in | ios::out);
    lagu *current = head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            file.seekp(0, ios::end);
            file << "\n"
                 << current->id << ","
                 << current->judul << ","
                 << current->artist << ","
                 << current->jmlh_pendengar << ","
                 << current->genre << ","
                 << current->theme << ","
                 << current->instrumen;
        }
        current = current->next;
    }
    file.close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void tambahawal(lagu **head, lagu **tail) // fungsi untuk menambah data ke bagian awal atau pertama dari linked list
{
    lagu *nodebaru = newnode();       // mendeklarasikan pointer nodebaru dengan node baru yang dibuat dengan fungsi newnode
    exportToCSV(songfile, *nodebaru); // mengespor data baru ke dalam file csv
    if (isEmpty(*head, *tail))        // memerikasa apaka linked list yang ada kosong atau tidak menggunakan funsgi is empty
    {
        *head = nodebaru; // jika kosong, maka head dan tail akan diatur untuk menunjuk ke node baru
        *tail = nodebaru; // jika kosong, maka head dan tail akan diatur untuk menunjuk ke node baru
        cout << " ══════════════════════════════" << endl;
        cout << "     Data Berhasil Ditambah" << endl;
        cout << " ══════════════════════════════" << endl;
    }
    else
    {
        nodebaru->next = *head;   // menunjuk pointer next dari nodebaru untuk menunjuk ke elemen yang telah tersedia
        (*head)->prev = nodebaru; // mengatur prev elemen yang awalnya ada untuk menunjuk ke nodebaru
        *head = nodebaru;         // mengatur pointer head untuk menunjuk ke node baru
        cout << " ══════════════════════════════" << endl;
        cout << "     Data Berhasil Ditambah" << endl;
        cout << " ══════════════════════════════" << endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void importFromCSV_user(int &numUsers, user users[100])
{
    ifstream file("user.csv");
    if (!file.is_open())
    {
        cerr << "Gagal membuka file " << accountfile << endl;
        return;
    }
    string line;

    while (getline(file, line))
    {
        istringstream lineStream(line);
        string cell;
        user newUser;

        if (getline(lineStream, cell, ','))
        {

            newUser.username = cell;
            users[numUsers].username = cell;
        }
        if (getline(lineStream, cell, ','))
        {

            newUser.password = cell;
            users[numUsers].password = cell;
        }

        numUsers++;
    }

    file.close();
}
void importFromCSV_history(history historyuser[4])
{
    ifstream file(historyfile);
    if (!file.is_open())
    {
        cerr << "Gagal membuka file " << historyfile << endl;
        return;
    }
    string line;
    int i = 0;

    while (getline(file, line))
    {
        istringstream lineStream(line);
        string cell;
        history newHistory;

        if (getline(lineStream, cell, ','))
        {
            newHistory.username = cell;
        }
        if (getline(lineStream, cell, ','))
        {
            newHistory.id_history1 = cell;
        }
        if (getline(lineStream, cell, ','))
        {
            newHistory.id_history2 = cell;
        }
        if (getline(lineStream, cell, ','))
        {
            newHistory.id_history3 = cell;
        }
        if (getline(lineStream, cell, ','))
        {
            newHistory.id_history4 = cell;
        }
        if (getline(lineStream, cell, ','))
        {
            newHistory.id_history5 = cell;
        }

        historyuser[i] = newHistory;
        i++;
    }

    file.close();
}

void importFromCSV_lagu(lagu *&head, lagu *&tail)
{
    ifstream file(songfile);
    if (!file.is_open())
    {
        cerr << "Gagal membuka file " << songfile << endl;
        return;
    }
    string line;

    while (getline(file, line))
    {
        istringstream lineStream(line);
        string cell;
        lagu *nodebaru = new lagu;

        if (getline(lineStream, cell, ','))
        {
            nodebaru->id = stoi(cell);
        }
        if (getline(lineStream, cell, ','))
        {
            nodebaru->judul = cell;
        }
        if (getline(lineStream, cell, ','))
        {
            nodebaru->artist = cell;
        }
        if (getline(lineStream, cell, ','))
        {
            nodebaru->jmlh_pendengar = cell;
        }
        if (getline(lineStream, cell, ','))
        {
            nodebaru->genre = cell;
        }
        if (getline(lineStream, cell, ','))
        {
            nodebaru->theme = cell;
        }
        if (getline(lineStream, cell, ','))
        {
            nodebaru->instrumen = cell;
        }

        nodebaru->prev = nullptr;
        nodebaru->next = nullptr;

        if (head == nullptr)
        {
            head = nodebaru;
            tail = nodebaru;
        }
        else
        {
            tail->next = nodebaru;
            nodebaru->prev = tail;
            tail = nodebaru;
        }
    }

    file.close();
}
void tampildatahead(lagu *head, lagu *tail) // fungsi yang digunakan untuk menampilkan data pada struktur linked list
{
    if (isEmpty(head, tail)) // fungsi untuk mengecek apakah data pada linked list ada atau tidak ada
    {
        cout << "Data Kosong" << endl; // mencetak bahwa data yang ada dilinked list kosong
    }
    else
    {
        lagu *temp = head;                            // membuat pointer temp dengan alamat awal linked list, dengan tujuan untuk melakukan iterasi tanpa mengubah pointer asli
        cout << "======== DATA LAGU =======" << endl; // print header data lagu
        while (temp != NULL)                          // mengulang terus sampai dengan temp tidak sama dengan null
        {
            cout << "ID: " << temp->id << endl;                           // menampilkan id yang tersimpan pada linked list yg ditujuk temp
            cout << "Judul: " << temp->judul << endl;                     // menampilkan judul yang tersimpan pada linked list yg ditujuk temp
            cout << "Artist: " << temp->artist << endl;                   // menampilkan artis yang tersimpan pada linked list yg ditujuk temp
            cout << "Jumlah Pendengar: " << temp->jmlh_pendengar << endl; // menampilkan jumlah pendengar yang tersimpan pada linked list yg ditujuk temp
            cout << "Genre: " << temp->genre << endl;                     // menampilkan genre yang tersimpan pada linked list yg ditujuk temp
            cout << "Tema: " << temp->theme << endl;                      // menampilkan theme yang tersimpan pada linked list yg ditujuk temp
            cout << "Instrumen: " << temp->instrumen << endl;             // menampilkan instrumen yang tersimpan pada linked list yg ditujuk temp
            cout << "=================================" << endl;
            temp = temp->next; // pada tiap perulangan pointer temp diarahkan ke elemen atau data berikutnya
        }
    }
}

void tampildatatail(lagu *head, lagu *tail)
{
    if (isEmpty(head, tail))
    {
        cout << "Data Kosong" << endl;
    }
    else
    {
        lagu *temp = tail;
        cout << "======== DATA PEMESANAN TIKET =======" << endl;
        while (temp != NULL)
        {
            cout << "ID: " << temp->id << endl;
            cout << "Judul: " << temp->judul << endl;
            cout << "Artist: " << temp->artist << endl;
            cout << "Jumlah Pendengar: " << temp->jmlh_pendengar << endl;
            cout << "Genre: " << temp->genre << endl;
            cout << "Tema: " << temp->theme << endl;
            cout << "Instrumen: " << temp->instrumen << endl;
            cout << "=================================" << endl;
            temp = temp->prev;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void hapusawal(lagu **head, lagu **tail) // prosedur untuk menghapus data yang berada paling awal dalam struct
{
    if (*head == nullptr) // percabangan dimana jika struct kita kosong
    {                     // maka akan mengembalikan output berikut
        cout << "Daftar kosong, tidak ada yang bisa dihapus." << endl;
        return;
    }

    lagu *nodeToBeDeleted = *head; // mendeklarasikan node/variabel pembantu untuk menyimpan node yang akan dihapus yaitu node paling awal/head

    if ((*head)->next == nullptr) // percabangan dimana jika next dari head tidak memiliki nilai atau null
    {                             // maka program akan me assignpointer head dan tail menjadi null
        *head = nullptr;
        *tail = nullptr;
    }
    else // dan jika tidak memenuhi kondisi sebelumnya maka head akan di assign dengan node selanjutnya yang ditunjukkan oleh next dari head yang sekarang
    {    // lalu prev dari head sekarang akan disetting menjadi null unntuk memutuskan hubungan ke node sebelumnya
        *head = (*head)->next;
        (*head)->prev = nullptr;
    }

    delete nodeToBeDeleted; // disini kita akan menghapus node/variabel pembantu yang menyimpan data dari head tadi
    cout << "Data berhasil dihapus." << endl;
}

void hapusakhir(lagu **head, lagu **tail) // prosedur untuk menghapus data yang berada paling akhir dalam struct
{
    if (*head == nullptr) // percabangan dimana jika struct kita kosong
    {                     // maka akan mengembalikan output berikut
        cout << "Daftar kosong, tidak ada yang bisa dihapus." << endl;
        return;
    }

    lagu *nodeToBeDeleted = *tail; // mendeklarasikan node/variabel pembantu untuk menyimpan node yang akan dihapus yaitu node paling akhir /tail

    if ((*tail)->prev == nullptr) // percabangan dimana jika next dari head tidak memiliki nilai atau null
    {                             // maka program akan me assignpointer head dan tail menjadi null
        *head = nullptr;
        *tail = nullptr;
    }
    else // dan jika tidak memenuhi kondisi sebelumnya maka tail akan di assign dengan node sebelumnya yang ditunjukkan oleh prev dari tail yang sekarang
    {    // lalu next dari tail sekarang akan disetting menjadi null unntuk memutuskan hubungan ke node selanjutnya
        *tail = (*tail)->prev;
        (*tail)->next = nullptr;
    }

    delete nodeToBeDeleted; // disini kita akan menghapus node/variabel pembantu yang menyimpan data dari tail tadi
    cout << "Data berhasil dihapus." << endl;
}

void hapustengah(lagu **head, lagu **tail, int id) // prosedur untuk menghapus data yang memiliki id yang sama dengan yang diinput oleh admin di dalam struct
{
    if (*head == nullptr) // percabangan dimana jika struct kita kosong
    {                     // maka akan mengembalikan output berikut
        cout << "Daftar kosong, tidak ada yang bisa dihapus." << endl;
        return;
    }

    lagu *current = *head; // mendeklarasikan node/variabel pembantu untuk menyimpan node yang akan dihapus

    while (current != nullptr) // perulangan dimana selama current tidak null maka akan menjalankan prosedurnya
    {
        if (current->id == id) // percabangan dimana jika id dari current dan id yang dimasukkan oleh admin itu sama maka akan menjalankan codingan didalamnya
        {
            if (current->prev != nullptr) // percabangan dimana jika prev dari current itu tidak null
            {                             // maka akan me assign next dari node yang ditunjuk oleh prev current menjadi nilai next dari current
                current->prev->next = current->next;
            }
            else // jika prev dari current null maka akan me assign head/node paling depan menjadi node yang ditunjuk oleh next dari current
            {
                *head = current->next;
            }

            if (current->next != nullptr) // percabangan dimana jika next dari current itu tidak null
            {                             // maka akan me assign prev dari node yang ditunjuk oleh next dari current menjadi nilai prev dari current
                current->next->prev = current->prev;
            }
            else // jika next dari current null maka akan me assign tail/node paling akhir menjadi node yang ditunjuk oleh prev dari current
            {
                *tail = current->prev;
            }

            delete current; // disini kita akan menghapus node/variabel pembantu
            cout << "Data dengan ID " << id << " berhasil dihapus." << endl;
            return;
        }

        current = current->next; // disini program akan me assign current menjadi node yang ditunjuk next dari current
    }

    cout << "ID tidak ditemukan." << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ubahdata(lagu *head, int idx)
{
    lagu *temp = head;
    for (int i = 1; i < idx; i++)
    {
        if (temp != nullptr)
        {

            temp = temp->next;
        }
    }
    cout << "Masukan Judul: ";
    fflush(stdin);
    getline(cin, temp->judul);
    cout << "Masukan Artist: ";
    fflush(stdin);
    getline(cin, temp->artist);
    cout << "Masukan Jumlah Pendengar: ";
    fflush(stdin);
    getline(cin, temp->jmlh_pendengar);
    cout << "Masukan Genre: ";
    fflush(stdin);
    getline(cin, temp->genre);
    cout << "Masukan Theme: ";
    fflush(stdin);
    getline(cin, temp->theme);
    cout << "Masukan Instrumen: ";
    fflush(stdin);
    getline(cin, temp->instrumen);
}

void ubahdatajudul(lagu *head, int idx)
{
    lagu *temp = head;
    for (int i = 1; i < idx; i++)
    {
        temp = temp->next;
    }
    cout << "Masukan Judul: ";
    fflush(stdin);
    getline(cin, temp->judul);
}

void ubahdataartis(lagu *head, int idx)
{
    lagu *temp = head;
    for (int i = 1; i < idx; i++)
    {
        temp = temp->next;
    }
    cout << "Masukan Artist: ";
    fflush(stdin);
    getline(cin, temp->artist);
}

void ubahdatapndngr(lagu *head, int idx)
{
    lagu *temp = head;
    for (int i = 1; i < idx; i++)
    {
        temp = temp->next;
    }
    cout << "Masukan Jumlah Pendengar: ";
    fflush(stdin);
    getline(cin, temp->jmlh_pendengar);
}

void ubahdatagenre(lagu *head, int idx)
{
    lagu *temp = head;
    for (int i = 1; i < idx; i++)
    {
        temp = temp->next;
    }
    cout << "Masukan Genre: ";
    fflush(stdin);
    getline(cin, temp->genre);
}

void ubahdatatheme(lagu *head, int idx)
{
    lagu *temp = head;
    for (int i = 1; i < idx; i++)
    {
        temp = temp->next;
    }
    cout << "Masukan Theme: ";
    fflush(stdin);
    getline(cin, temp->theme);
}

void ubahdatainstrumen(lagu *head, int idx)
{
    lagu *temp = head;
    for (int i = 1; i < idx; i++)
    {
        temp = temp->next;
    }
    cout << "Masukan Instrumen: ";
    fflush(stdin);
    getline(cin, temp->instrumen);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

lagu *SortedMerge(lagu *a, lagu *b);                                // fungsi yang menggabungkan dua bagian dari merge sort yang sudah di urutkan
void FrontBackSplit(lagu *source, lagu **frontRef, lagu **backRef); // prosedur yang berfungsi untuk memisahkan struct/seluruh data ke dua bagian
void MergeSort(lagu **headRef)                                      // prosedur yang berfungsi untuk mengurutkan bagian depan dari data yang sudah dipisah tadi
{
    lagu *head = *headRef;                      // deklarasi head dari lagu yang di assign nilai dari headref
    lagu *a;                                    // deklarasi a
    lagu *b;                                    // deklarasi b
    if ((head == NULL) || (head->next == NULL)) // Pengecekan apakah linked list kosong atau hanya memiliki satu elemen. Jika iya, maka linked list sudah terurut, dan fungsi berakhir.
    {
        return;
    }

    FrontBackSplit(head, &a, &b); // Memanggil fungsi FrontBackSplit untuk membagi linked list menjadi dua bagian, a dan b.

    MergeSort(&a);                // Memanggil dirinya sendiri secara rekursif untuk mengurutkan kedua bagian linked list, a dan b
    MergeSort(&b);                // Memanggil dirinya sendiri secara rekursif untuk mengurutkan kedua bagian linked list, a dan b
    *headRef = SortedMerge(a, b); // Menggabungkan kedua bagian linked list yang sudah diurutkan menggunakan fungsi SortedMerge.
}

lagu *SortedMerge(lagu *a, lagu *b) // Implementasi fungsi SortedMerge yang menggabungkan dua linked list terurut (a dan b) menjadi satu linked list terurut.
{
    lagu *result = NULL; // Deklarasi dan inisialisasi pointer result yang akan menyimpan hasil penggabungan dua linked list.
    if (a == NULL)       // Pengecekan apakah linked list a sudah habis. Jika iya, kembalikan linked list b karena a sudah habis dan b masih ada.
        return (b);
    else if (b == NULL) // Pengecekan apakah linked list b sudah habis. Jika iya, kembalikan linked list a karena b sudah habis dan a masih ada.
        return (a);
    if (a->judul <= b->judul) // Pengecekan apakah judul lagu pada elemen linked list a kurang dari atau sama dengan judul lagu pada elemen linked list b. Ini menentukan urutan penggabungan.
    {
        result = a;                             // Jika judul lagu pada a lebih kecil atau sama, maka result diatur untuk menunjuk ke elemen pertama dari a.
        result->next = SortedMerge(a->next, b); // Rekursif panggilan untuk menggabungkan sisa linked list a dengan linked list b. result->next menunjuk ke hasil penggabungan sisa linked list a dengan b.
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next); // Rekursif panggilan untuk menggabungkan sisa linked list b dengan linked list a. result->next menunjuk ke hasil penggabungan sisa linked list b dengan a.
    }
    return (result);
}
void FrontBackSplit(lagu *source, lagu **frontRef, lagu **backRef) // membagi linked list (source) menjadi dua bagian, satu bagian di depan (frontRef) dan satu bagian di belakang (backRef). Menggunakan dua pointer, fast dan slow, untuk menemukan titik tengah linked list dan kemudian membaginya.
{
    lagu *fast; // Deklarasi dua pointer, fast dan slow, yang digunakan untuk membagi linked list.
    lagu *slow;
    slow = source;       // Inisialisasi pointer slow dengan alamat awal linked list (source)
    fast = source->next; // Inisialisasi pointer fast dengan elemen kedua dari linked list (source->next).
    while (fast != NULL) // Loop while yang berjalan selama pointer fast tidak NULL. Loop ini digunakan untuk menemukan titik tengah linked list dengan menggunakan dua pointer, fast yang bergerak dua langkah sekaligus dan slow yang bergerak satu langkah.
    {
        fast = fast->next; // Pemindahan pointer fast dua langkah ke depan.
        if (fast != NULL)  // Pengecekan apakah pointer fast tidak NULL setelah perpindahan dua langkah. Ini memastikan bahwa pointer slow akan bergerak satu langkah setelahnya.
        {
            slow = slow->next; // Pemindahan pointer slow satu langkah ke depan.
            fast = fast->next; // Pemindahan pointer fast dua langkah ke depan. Ini menjamin bahwa setelah loop selesai, pointer slow akan berada di tengah linked list.
        }
    }
    *frontRef = source;    // Mengatur pointer frontRef untuk menunjuk ke awal linked list.
    *backRef = slow->next; // Mengatur pointer backRef untuk menunjuk ke bagian belakang linked list (setelah titik tengah).
    slow->next = NULL;     // Memutuskan hubungan antara bagian depan dan belakang linked list dengan mengatur slow->next menjadi NULL. Ini membagi linked list menjadi dua bagian terpisah.
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

lagu *SortedMergeDesc(lagu *a, lagu *b); // Deklarasi fungsi SortedMergeDesc yang menggabungkan dua linked list terurut secara descending (urutan menurun) menjadi satu linked list terurut.

void MergeSortDesc(lagu **headRef) // Fungsi MergeSortDesc menggunakan algoritma Merge Sort untuk mengurutkan linked list secara descending. Fungsi ini memanggil FrontBackSplit untuk membagi linked list, memanggil dirinya sendiri secara rekursif untuk mengurutkan kedua bagian, dan kemudian memanggil Fungsi MergeSortDesc menggunakan algoritma Merge Sort untuk mengurutkan linked list secara descending. Fungsi ini memanggil FrontBackSplit untuk membagi linked list, memanggil dirinya sendiri secara rekursif untuk mengurutkan kedua bagian, dan kemudian memanggil SortedMergeDesc untuk menggabungkan kembali kedua bagian yang sudah diurutkan secara descending.
{
    lagu *head = *headRef; // Deklarasi dan inisialisasi pointer head dengan alamat awal linked list.
    lagu *a;               // Deklarasi dua pointer, a dan b, yang akan digunakan untuk menyimpan hasil pemisahan linked list.
    lagu *b;
    if ((head == NULL) || (head->prev == NULL)) // Pengecekan apakah linked list kosong atau hanya memiliki satu elemen. Jika iya, maka linked list sudah terurut secara descending, dan fungsi berakhir.
    {
        return;
    }

    FrontBackSplit(head, &a, &b); // Memanggil fungsi FrontBackSplit untuk membagi linked list menjadi dua bagian, a dan b.

    MergeSortDesc(&a); // Memanggil dirinya sendiri secara rekursif untuk mengurutkan kedua bagian linked list, a dan b.
    MergeSortDesc(&b);

    *headRef = SortedMergeDesc(a, b); // Menggabungkan kedua bagian linked list yang sudah diurutkan secara descending menggunakan fungsi SortedMergeDesc.
}

lagu *SortedMergeDesc(lagu *a, lagu *b) // Implementasi fungsi SortedMergeDesc yang menggabungkan dua linked list terurut secara descending (a dan b) menjadi satu linked list terurut secara descending.
{
    lagu *result = NULL;
    if (a == NULL) ////Pengecekan apakah linked list a sudah habis. Jika iya, kembalikan linked list b karena a sudah habis dan b masih ada.
        return (b);
    else if (b == NULL) // Pengecekan apakah linked list b sudah habis. Jika iya, kembalikan linked list a karena b sudah habis dan a masih ada.
        return (a);
    if (a->judul >= b->judul) // Pengecekan apakah judul lagu pada elemen linked list a lebih besar atau sama dengan judul lagu pada elemen linked list b. Ini menentukan urutan penggabungan secara descending.
    {
        result = a;                                 // Jika judul lagu pada a lebih besar atau sama, maka result diatur untuk menunjuk ke elemen pertama dari a.
        result->next = SortedMergeDesc(a->next, b); // Rekursif panggilan untuk menggabungkan sisa linked list a dengan linked list b. result->next menunjuk ke hasil penggabungan sisa linked list a dengan b.
    }
    else // Jika judul lagu pada b lebih besar dari judul lagu pada a, maka result diatur untuk menunjuk ke elemen pertama dari b.
    {
        result = b;
        result->next = SortedMergeDesc(a, b->next); // Rekursif panggilan untuk menggabungkan sisa linked list b dengan linked list a. result->next menunjuk ke hasil penggabungan sisa linked list b dengan a.
    }
    return (result); // Kembalikan pointer ke elemen pertama dari linked list yang sudah digabungkan secara terurut secara descending.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int NO_OF_CHARS = 256;                                          // mendefinisikan konstanta dengan panjang 256
void badCharHeuristic(string str, int size, int badChar[NO_OF_CHARS]) // merupakan fungsi bad character hauristic
{
    for (int i = 0; i < NO_OF_CHARS; i++) // perulangan bad character dengan inisialisasi array badchar dgn nilai -1
    {
        badChar[i] = -1; // setiap elemen pada badchardiatur ke nilai -1
    }
    for (int i = 0; i < size; i++) // perulangan untuk mengisi tabel bad char dengan munculnya posisi terakhir pada string
    {
        badChar[(int)str[i]] = i; // setiap elemen badchar diatur ke i yaitu posisi terakhir munculnya karakter dalam string
    }
}
void searchjudul(lagu *head, string pat, string &tipe) // deklarasi fungsi untuk pencarian data pada string
{
    int m = pat.size();  // deklarasi var m sebagai ukuran pencarian string atau pattern
    lagu *temp = head;   // deklarasi pointer temp dengan alamat awal linkedlist atau head
    while (temp != NULL) // pperulangan apabila temp tidak sama degan null
    {
        int n = temp->judul.size();        // deklarasi var n sebagai dan memulai dgn ukuran judul lagu
        int badChar[NO_OF_CHARS];          // deklarasi array badhar yang digunakan untuk pencarian an pencocokan string
        badCharHeuristic(pat, m, badChar); // memanggil fungsi badcharhaur
        int s = 0;                         // deklarasi variabel s dan memberi nilainya 0, ini diguakan untuk penlacakan posisi saat pencocokan string

        while (s <= (n - m)) // perulangan berjalan selama posisi s tak melebihi batas n dikurang m
        {
            int j = m - 1; // pendeklaeasian var j dan memberi nilainya m -1

            while (j >= 0 && pat[j] == temp->judul[s + j]) // perulangan berjalan untuk memerika pencocokan karakter atau pola dengan string yang ada
            {
                j--; // mengurangkan nilai j untuk pencarian selanjutnya
            }
            if (j < 0) // percabangan jika j kurang dari 0, menandakan bahwa pencarian berhasil
            {
                if (tipe == "search")
                {
                    cout << "ID: " << temp->id << endl;
                    cout << "Judul: " << temp->judul << endl;
                    cout << "Artist: " << temp->artist << endl;
                    cout << "Jumlah Pendengar: " << temp->jmlh_pendengar << endl;
                    cout << "Genre: " << temp->genre << endl;
                    cout << "Tema: " << temp->theme << endl;
                    cout << "Instrumen: " << temp->instrumen << endl;
                    cout << "=================================" << endl;
                    break;
                }
                else
                {
                    cout << "ID: " << temp->id << endl;
                    cout << "Judul: " << temp->judul << endl;
                    cout << "Artist: " << temp->artist << endl;
                    break;
                }
            }
            else
            {
                s += max(1, j - badChar[temp->judul[s + j]]); // menghitung langkah maju saat string berjalan
            }
        }
        temp = temp->next; // berpinndah ke elamen selanjurtknay pad saat pencarian string
    }
}

void searchjuduluser(lagu *head, string pat) // penjelasan sama kaya search yang diatas
{
    int m = pat.size();
    lagu *temp = head;
    cout << "|\tID\t|\tJUDUL\t|\tARTIST\t|\tJUMLAH PENDENGAR\t|\tGENRE\t|\tTEMA\t|\tINSTRUMENT\t|" << endl;
    while (temp != NULL)
    {
        int n = temp->judul.size();
        int badChar[NO_OF_CHARS];
        badCharHeuristic(pat, m, badChar);
        int s = 0;

        while (s <= (n - m))
        {
            int j = m - 1;
            while (j >= 0 && pat[j] == temp->judul[s + j])
            {
                j--;
            }
            if (j < 0)
            {
                cout << "|\t" << temp->id << "\t|\t" << temp->judul << "\t|\t" << temp->artist << "\t|\t\t" << temp->jmlh_pendengar << "\t\t|\t" << temp->genre << "\t|\t" << temp->theme << "\t|\t" << temp->instrumen << "\t\t|" << endl;
                break;
            }
            else
            {
                s += max(1, j - badChar[temp->judul[s + j]]);
            }
        }
        temp = temp->next;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int hitunglagu(int &banyakdata)
{
    ifstream file(songfile);
    string line;
    while (getline(file, line))
    {
        banyakdata++;
    }
    file.close();
    return banyakdata;
}

void Tampilhistory(lagu *head, history historyuser[100], lagu song, user users[100], string username)
{
    cout << "History" << endl;
    // tampil id, judul, artist
    int a, b, c;
    string pattern;
    string tipe = "history";
    for (a = 0; a < 100; a++)
    {
        if (historyuser[a].username == username)
        {
            c = a;
            break;
        }
    }
    b = 0;

    while (true)
    {
        if (b == 0)
        {
            pattern = historyuser[c].id_history1;
            // cout << historyuser[c].id_history1 << endl;
        }
        else if (b == 1)
        {
            pattern = historyuser[c].id_history2;
            // cout << historyuser[c].id_history2 << endl;
        }
        else if (b == 2)
        {
            pattern = historyuser[c].id_history3;
            // cout << historyuser[c].id_history3 << endl;
        }
        else if (b == 3)
        {
            pattern = historyuser[c].id_history4;
            // cout << historyuser[c].id_history4 << endl;
        }
        else if (b == 4)
        {

            pattern = historyuser[c].id_history5;
            // cout << historyuser[c].id_history5 << endl;
        }
        else
        {
            break;
        }
        b++;
        searchjudul(head, pattern, tipe);
    }
}

void enqueue(string &judul, history historyuser[100], string &username)
{
    string temp;
    for (int a = 0; a < 100; a++)
    {
        if (historyuser[a].username == username)
        {
            historyuser[a].id_history1 = historyuser[a].id_history2;
            historyuser[a].id_history2 = historyuser[a].id_history3;
            historyuser[a].id_history3 = historyuser[a].id_history4;
            historyuser[a].id_history4 = historyuser[a].id_history5;
            historyuser[a].id_history5 = judul;
            break;
        }
    }
    ofstream file(historyfile, ios::out);
    // Menulis data ke dalam file
    for (int a = 0; a < 100; a++)
    {
        file << historyuser[a].username << ","
             << historyuser[a].id_history1 << ","
             << historyuser[a].id_history2 << ","
             << historyuser[a].id_history3 << ","
             << historyuser[a].id_history4 << ","
             << historyuser[a].id_history5 << endl;
    }

    file.close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int pilih, pilihmenuadmin, idx, pilihmenuuser;
    string username, password;
    int numUsers = 0;
    int jumlahlagu = 0;
    const int maxUsers = 100;
    // const int maxHistory = 5;
    user users[maxUsers];
    history historyuser[maxUsers];
    lagu *head = NULL;
    lagu *tail = NULL;
    lagu song;
    string carijudul;

    importFromCSV_lagu(head, tail);
    importFromCSV_user(numUsers, users);
    importFromCSV_history(historyuser);
    jumlahlagu = hitunglagu(jumlahlagu);
    while (true)
    {
        cout << " ╔═════════════════════════════════════╗" << endl; // menu utama program
        cout << " ║             MENU UTAMA              ║" << endl;
        cout << " ╚═════════════════════════════════════╝" << endl;
        cout << " ╔═════════════════════════════════════╗" << endl;
        cout << " ║   Selamat Datang! di soundlist.io   ║" << endl;
        cout << " ║     1. ║ Login                      ║" << endl;
        cout << " ║     2. ║ Registrasi                 ║" << endl;
        cout << " ║     9. ║ Login Admin                ║" << endl;
        cout << " ║     0. ║ Exit Program               ║" << endl;
        cout << " ╚═════════════════════════════════════╝" << endl;
        cout << " Silahkan Masukan Pilihan [1/2/9/0]: ";
        cin >> pilih;
        if (pilih == 9)
        {
            cout << "                  LOGIN" << endl;
            cout << " ╔════════════════════════════════════╗" << endl;
            cout << "   Username: ";
            cin >> username;
            cout << "   Password: ";
            cin >> password;
            cout << " ╚════════════════════════════════════╝" << endl;

            if (username == "a" && password == "a")
            {
                while (true)
                {
                    cout << " ╔═══════════════════════════════════════╗" << endl; // menu utama
                    cout << " ║            MENU UTAMA ADMIN           ║" << endl;
                    cout << " ╚═══════════════════════════════════════╝" << endl;
                    cout << " ╔═══════════════════════════════════════╗" << endl;
                    cout << " ║  1.  ║  Menambahkan Lagu              ║" << endl;
                    cout << " ║  2.  ║  Menampilkan Lagu              ║" << endl;
                    cout << " ║  3.  ║  Mengubah Lagu                 ║" << endl;
                    cout << " ║  4.  ║  Menghapus Lagu                ║" << endl;
                    cout << " ║  5.  ║  Mencari Lagu                  ║" << endl;
                    cout << " ║  0.  ║  Logout                        ║" << endl;
                    cout << " ╚═══════════════════════════════════════╝" << endl;
                    cout << "  Silahkan Masukan Pilihan [1/2/3/4/5/6/7/8/9/10/11/12/13/14/15/0]: ";
                    cin >> pilihmenuadmin;

                    if (pilihmenuadmin == 1)
                    {
                        tambahawal(&head, &tail);
                    }

                    else if (pilihmenuadmin == 2)
                    {
                        MergeSort(&head);
                        tampildatahead(head, tail);
                    }
                    else if (pilihmenuadmin == 3)
                    {
                        int pilihubah;
                        int cariidubah;
                        MergeSort(&head);
                        tampildatahead(head, tail);
                        cout << "Ingin Ubah Data ke Berapa: ";
                        cin >> cariidubah;

                        lagu *song = head;
                        bool ditemukan = false;

                        while (song != nullptr)
                        {
                            if (song->id == cariidubah)
                            {
                                ditemukan = true;
                                cout << " ╔═══════════════════════════════╗" << endl;
                                cout << " ║           MENU UBAH           ║" << endl;
                                cout << " ╚═══════════════════════════════╝" << endl;
                                cout << " ╔═══════════════════════════════╗" << endl;
                                cout << " ║  1. ║ Ubah Judul              ║" << endl;
                                cout << " ║  2. ║ Ubah Artis              ║" << endl;
                                cout << " ║  3. ║ Ubah Jumlah Pendengar   ║" << endl;
                                cout << " ║  4. ║ Ubah Genre              ║" << endl;
                                cout << " ║  5. ║ Ubah Theme              ║" << endl;
                                cout << " ║  6. ║ Ubah Instrumen          ║" << endl;
                                cout << " ║  7. ║ Ubah Semua Data         ║" << endl;
                                cout << " ║  0. ║ Kembali                 ║" << endl;
                                cout << " ╚═══════════════════════════════╝" << endl;
                                cout << "Masukan Pilihan Ubah [1/2/3/4/5/6/7/0]: ";
                                cin >> pilihubah;
                                if (pilihubah == 1)
                                {
                                    ubahdatajudul(head, cariidubah);
                                    updateCSV(head, cariidubah);
                                }
                                else if (pilihubah == 2)
                                {
                                    ubahdataartis(head, cariidubah);
                                    updateCSV(head, cariidubah);
                                }
                                else if (pilihubah == 3)
                                {
                                    ubahdatapndngr(head, cariidubah);
                                    updateCSV(head, cariidubah);
                                }
                                else if (pilihubah == 4)
                                {
                                    ubahdatagenre(head, cariidubah);
                                    updateCSV(head, cariidubah);
                                }
                                else if (pilihubah == 5)
                                {
                                    ubahdatatheme(head, cariidubah);
                                    updateCSV(head, cariidubah);
                                }
                                else if (pilihubah == 6)
                                {
                                    ubahdatainstrumen(head, cariidubah);
                                    updateCSV(head, cariidubah);
                                }
                                else if (pilihubah == 7)
                                {
                                    ubahdata(head, cariidubah);
                                    updateCSV(head, cariidubah);
                                }
                                else if (pilihubah == 0)
                                {
                                    break;
                                }
                                else
                                {
                                    cout << "Invalid Input" << endl;
                                }
                            }
                            song = song->next;
                        }
                        if (!ditemukan)
                        {
                            cout << "ID GA DITEMUKAN" << endl;
                        }
                    }

                    else if (pilihmenuadmin == 4)
                    {
                        int pilihhapus;
                        int cariidhapus;
                        MergeSort(&head);
                        tampildatahead(head, tail);
                        cout << "Ingin Hapus Apa: ";
                        cin >> cariidhapus;
                        song.id == cariidhapus;
                        hapustengah(&head, &tail, cariidhapus);
                    }
                    else if (pilihmenuadmin == 5)
                    {
                        cout << "Ingin Cari Judul Apa: ";
                        cin >> carijudul;
                        string tipe = "search";
                        searchjudul(head, carijudul, tipe);
                    }
                    else if (pilihmenuadmin == 0)
                    {
                        break;
                    }
                }
            }
            else
            {
                cout << "Username dan Password Salah" << endl;
            }
        }

        else if (pilih == 2)
        {
            cout << "Registrasi" << endl;

            if (numUsers < maxUsers)
            {
                user newUser;
                history newHistory;
                cout << "Masukkan username baru: ";
                cin >> newUser.username;

                bool usernameExists = false;
                for (int i = 0; i < numUsers; i++)
                {
                    if (newUser.username == users[i].username)
                    {
                        usernameExists = true;
                        break;
                    }
                }

                if (usernameExists)
                {
                    cout << "Username sudah ada. Silakan coba lagi." << endl;
                }
                else
                {
                    cout << "Masukkan password: ";
                    cin >> newUser.password;

                    users[numUsers] = newUser;
                    numUsers++;
                    newHistory.username = username;
                    newHistory.id_history1 = "kosong";
                    newHistory.id_history2 = "kosong";
                    newHistory.id_history3 = "kosong";
                    newHistory.id_history4 = "kosong";
                    newHistory.id_history5 = "kosong";

                    historyuser[numUsers] = newHistory;
                    numUsers++;

                    ofstream file(accountfile, ios::app);
                    file << "\n"
                         << newUser.username << ","
                         << newUser.password;
                    file.close();
                    ofstream file2(historyfile, ios::app);
                    file2 << "\n"
                          << newUser.username << ","
                          << "kosong"
                          << ","
                          << "kosong"
                          << ","
                          << "kosong"
                          << ","
                          << "kosong"
                          << ","
                          << "kosong";
                    file2.close();
                    importFromCSV_history(historyuser);

                    cout << "Registrasi berhasil!" << endl;
                }
            }
            else
            {
                cout << "Batas maksimum pengguna telah tercapai." << endl;
            }
        }

        else if (pilih == 1)
        {
            cout << "Menu Customer" << endl;
            cout << endl;
            cout << "                  LOGIN" << endl;
            cout << " ╔════════════════════════════════════╗" << endl;
            cout << "   Username: ";
            cin >> username;
            cout << "   Password: ";
            cin >> password;
            cout << " ╚════════════════════════════════════╝" << endl;

            bool loginSuccess = false;
            for (int i = 0; i < numUsers; i++)
            {
                if (username == users[i].username && password == users[i].password)
                {
                    loginSuccess = true;
                    break;
                }
            }

            if (loginSuccess)
            {
                while (true)

                {
                    cout << "Login berhasil! Selamat datang, " << username << "!" << endl;
                    cout << " ╔════════════════════════════════╗" << endl;
                    cout << " ║       MENU UTAMA CUSTOMER      ║" << endl;
                    cout << " ╚════════════════════════════════╝" << endl;
                    cout << " ╔════════════════════════════════╗" << endl;
                    cout << " ║  1.  ║  Tampilkan Lebih Banyak ║" << endl;
                    cout << " ║  2.  ║  Cari Lagu              ║" << endl;
                    cout << " ║  3.  ║  Histori Download       ║" << endl;
                    cout << " ║  0.  ║  Logout                 ║" << endl;
                    cout << " ╚════════════════════════════════╝" << endl;
                    cout << "masukkan pilihan anda :";
                    cin >> pilihmenuuser;
                    if (pilihmenuuser == 1)
                    {
                        cout << "ID|\tJUDUL    |\tARTIST      |\tJUMLAH PENDENGAR      |\tGENRE       |\tTEMA      |\tINSTRUMENT   |" << endl;
                        lagu *temp = head;
                        while (temp != NULL)
                        {
                            cout << "|\t" << temp->id << "\t|\t" << temp->judul << "\t|\t" << temp->artist << "\t|\t\t" << temp->jmlh_pendengar << "\t\t|\t" << temp->genre << "\t|\t" << temp->theme << "\t|\t" << temp->instrumen << "\t\t|" << endl;
                            temp = temp->next;
                        }
                    }
                    else if (pilihmenuuser == 2)
                    {
                        cout << "Ingin Cari Judul Apa: ";
                        cin >> carijudul;
                        searchjuduluser(head, carijudul);
                    }
                    else if (pilihmenuuser == 3)
                    {
                        string judul;
                        cout << "Masukkan Judul Yang ingin di download: ";
                        cin >> judul;
                        enqueue(judul, historyuser, username);
                        cout << "Lagu Berhasil di Download" << endl;
                    }
                    else if (pilihmenuuser == 4)
                    {
                        Tampilhistory(head, historyuser, song, users, username);
                    }

                    else if (pilihmenuuser == 0)
                    {
                        break;
                    }
                    else
                    {
                        cout << "invalid input" << endl;
                    }
                }
            }
            else
            {
                cout << "Login gagal. Periksa kembali username dan password Anda." << endl;
            }
        }
        else if (pilih == 0)
        {
            return 0;
        }
        else
        {
            cout << "Invalid Input" << endl;
        }
    }
}