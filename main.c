#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[50];
    char phone[15];
    char email[50];
} Contact;

Contact *contacts = NULL;
int contactCount = 0;
int contactCapacity = 0;

void ensureCapacity()
{
    if (contactCount >= contactCapacity)
    {
        contactCapacity = (contactCapacity == 0) ? 10 : contactCapacity * 2;
        contacts = realloc(contacts, contactCapacity * sizeof(Contact));
        if (!contacts)
        {
            printf("\nAlokasi Memori Gagal!\n");
            exit(1);
        }
    }
}

void saveContactsToFile()
{
    FILE *file = fopen("contacts.txt", "w");
    if (!file)
    {
        printf("\nGagal Membuka File Untuk Menyimpan!\n");
        return;
    }

    for (int i = 0; i < contactCount; i++)
    {
        fprintf(file, "%s,%s,%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }

    fclose(file);
}

void loadContactsFromFile()
{
    FILE *file = fopen("contacts.txt", "r");
    if (!file)
    {
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file))
    {
        ensureCapacity();

        char *token = strtok(line, ",");
        if (token)
            strncpy(contacts[contactCount].name, token, sizeof(contacts[contactCount].name));

        token = strtok(NULL, ",");
        if (token)
            strncpy(contacts[contactCount].phone, token, sizeof(contacts[contactCount].phone));

        token = strtok(NULL, "\n");
        if (token)
            strncpy(contacts[contactCount].email, token, sizeof(contacts[contactCount].email));

        contactCount++;
    }

    fclose(file);
}

int validatePhone(const char *phone)
{
    for (int i = 0; i < strlen(phone); i++)
    {
        if (phone[i] < '0' || phone[i] > '9')
        {
            return 0;
        }
    }
    return 1;
}

int validateEmail(const char *email)
{
    char *domain = strstr(email, "@gmail.com");
    return domain && strcmp(domain, "@gmail.com") == 0;
}

int isDuplicateName(const char *name)
{
    for (int i = 0; i < contactCount; i++)
    {
        if (strcmp(contacts[i].name, name) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void addContact()
{
    ensureCapacity();

    char name[50];
    printf("\nMasukkan Nama: ");
    scanf(" %[^\n]", name);

    if (isDuplicateName(name))
    {
        printf("\nNama '%s' sudah ada dalam kontak! Tidak boleh duplikat.\n", name);
        return;
    }

    strncpy(contacts[contactCount].name, name, sizeof(contacts[contactCount].name));

    do
    {
        printf("Masukkan Nomor Telepon (hanya angka): ");
        scanf(" %[^\n]", contacts[contactCount].phone);
        if (!validatePhone(contacts[contactCount].phone))
        {
            printf("Nomor telepon tidak valid! Coba lagi.\n");
        }
        else
        {
            break;
        }
    } while (1);

    do
    {
        printf("Masukkan Email (harus berakhiran @gmail.com): ");
        scanf(" %[^\n]", contacts[contactCount].email);
        if (!validateEmail(contacts[contactCount].email))
        {
            printf("Email tidak valid! Coba lagi.\n");
        }
        else
        {
            break;
        }
    } while (1);

    printf("\nKontak %s Berhasil Ditambahkan!\n", contacts[contactCount].name);
    contactCount++;
    saveContactsToFile();
}

void showMenu()
{
    // Data Kelompok
    printf("+-------------------------------------------------------+\n");
    printf("|      Final Project Mata Kuliah Pemrograman Lanjut     |\n");
    printf("+-------------------------------------------------------+\n");
    printf("| Kelas      : F081                                     |\n");
    printf("| Kelompok   : 3                                        |\n");
    printf("+-------------------------------------------------------+\n");
    printf("| NPM               | Nama                              |\n");
    printf("+-------------------+-----------------------------------+\n");
    printf("| 23081010106       | Nurul Saadeh                      |\n");
    printf("| 23081010110       | Aril Ponco Nugroho                |\n");
    printf("| 23081010113       | Narendra Putra Arianto            |\n");
    printf("| 23081010115       | Mikail Zamakhsyari                |\n");
    printf("+-------------------------------------------------------+\n");

    // Menu Utama
    printf("\n+-------------------------------------------------------+\n");
    printf("|                Sistem Manajemen Kontak                |\n");
    printf("+-------------------------------------------------------+\n");
    printf("| 1. Tambah Kontak                                      |\n");
    printf("| 2. Daftar Kontak                                      |\n");
    printf("| 3. Edit Kontak                                        |\n");
    printf("| 4. Hapus Kontak                                       |\n");
    printf("| 5. Cari Kontak                                        |\n");
    printf("| 6. Keluar                                             |\n");
    printf("+-------------------------------------------------------+\n");
    printf("Masukkan Pilihan Anda: ");
}

int main()
{
    loadContactsFromFile();

    int choice;

    do
    {
        system("cls");
        showMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            system("cls");
            addContact();
            break;
        case 2:
            system("cls");
            printf("Daftar Kontak");
            break;
        case 3:
            system("cls");
            printf("Edit Kontak");
            break;
        case 4:
            system("cls");
            printf("Hapus Kontak");
            break;
        case 5:
            system("cls");
            printf("Cari Kontak");
            break;
        case 6:
            printf("\nKeluar...\n");
            break;
        default:
            printf("\nPilihan Tidak Valid.\n");
        }

        if (choice != 6)
        {
            printf("\nTekan Enter untuk kembali ke menu utama...");
            while (getchar() != '\n')
                ;
            getchar();
        }
    } while (choice != 6);

    free(contacts);
    return 0;
}
