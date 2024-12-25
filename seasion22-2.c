#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    char username[50];
    char password[50];
};

void readFile(struct Account accounts[], int *n) {
    FILE *file = fopen("accounts.bin", "rb");
    if (!file) {
        *n = 0; 
        return;
    }
    fread(n, sizeof(int), 1, file);
    fread(accounts, sizeof(struct Account), *n, file);
    fclose(file);
}

void writeFile(struct Account accounts[], int n) {
    FILE *file = fopen("accounts.bin", "wb");
    if (!file) {
        printf("Loi khi mo file.\n");
        return;
    }
    fwrite(&n, sizeof(int), 1, file);
    fwrite(accounts, sizeof(struct Account), n, file);
    fclose(file);
}

void registerAccount(struct Account accounts[], int *n) {
    int MAX_ACCOUNTS = 100;
    if (*n >= MAX_ACCOUNTS) {
        printf("Da du so luong tai khoan.\n");
        return;
    }

    struct Account newAccount;
    int isUnique = 1;

    printf("Nhap ten tai khoan: ");
    fgets(newAccount.username, 50, stdin);
    newAccount.username[strcspn(newAccount.username, "\n")] = 0;

    for (int i = 0; i < *n; i++) {
        if (strcmp(accounts[i].username, newAccount.username) == 0) {
            printf("Tai khoan da ton tai, vui long chon ten khac.\n");
            isUnique = 0;
            break;
        }
    }

    if (!isUnique) {
        return;
    }

    printf("Nhap mat khau: ");
    fgets(newAccount.password, 50, stdin);
    newAccount.password[strcspn(newAccount.password, "\n")] = 0;

    char confirmPassword[50];
    printf("Xac nhan mat khau: ");
    fgets(confirmPassword, 50, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0; 

    if (strcmp(newAccount.password, confirmPassword) != 0) {
        printf("Mat khau xac nhan khong khop. Dang ky that bai.\n");
        return;
    }

    accounts[*n] = newAccount;
    (*n)++;
    writeFile(accounts, *n);
    printf("Dang ky thanh cong.\n");
}

void login(struct Account accounts[], int n) {
    char username[50];
    char password[50];
    int found = 0;

    printf("Nhap ten tai khoan: ");
    fgets(username, 50, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Nhap mat khau: ");
    fgets(password, 50, stdin);
    password[strcspn(password, "\n")] = 0; 

    for (int i = 0; i < n; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
            printf("Dang nhap thanh cong!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Dang nhap that bai. Ten tai khoan hoac mat khau khong chinh xac.\n");
    }
}

int main() {
    struct Account accounts[100]; 
    int n = 0;
    readFile(accounts, &n);

    int choice;
    do {
        printf("MENU\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                login(accounts, n);
                break;
            case 2:
                registerAccount(accounts, &n);
                break;
            case 3:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}

