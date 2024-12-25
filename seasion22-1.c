#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
};

void readFile(struct Student students[], int *n) {
    FILE *file = fopen("students.bin", "rb");
    if (!file) {
        *n = 0;
        return;
    }
    fread(n, sizeof(int), 1, file);
    fread(students, sizeof(struct Student), *n, file);
    fclose(file);
}

void writeFile(struct Student students[], int n) {
    FILE *file = fopen("students.bin", "wb");
    if (!file) {
        printf("Loi khi mo file.\n");
        return;
    }
    fwrite(&n, sizeof(int), 1, file);
    fwrite(students, sizeof(struct Student), n, file);
    fclose(file);
}

void printStudents(struct Student students[], int n) {
    printf("\nDanh sach sinh vien:\n");
    printf("%-5s%-20s%-10s\n", "ID", "Name", "Age");
    for (int i = 0; i < n; i++) {
        printf("%-5d%-20s%-10d\n", students[i].id, students[i].name, students[i].age);
    }
}

void addStudent(struct Student students[], int *n) {
    if (*n >= 100) {
        printf("Danh sach sinh vien da day.\n");
        return;
    }
    struct Student newStudent;
    printf("Nhap ID: ");
    scanf("%d", &newStudent.id);
    getchar();
    printf("Nhap ten: ");
    fgets(newStudent.name, 50, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;
    printf("Nhap tuoi: ");
    scanf("%d", &newStudent.age);

    students[*n] = newStudent;
    (*n)++;
    writeFile(students, *n);
    printf("Sinh vien da duoc them.\n");
}

void editStudent(struct Student students[], int n) {
    int id;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (students[i].id == id) {
            printf("Nhap ten moi: ");
            getchar();
            fgets(students[i].name, 50, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;
            printf("Nhap tuoi moi: ");
            scanf("%d", &students[i].age);
            writeFile(students, n);
            printf("Thong tin sinh vien da duoc cap nhat.\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID %d.\n", id);
}

void deleteStudent(struct Student students[], int *n) {
    int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);

    for (int i = 0; i < *n; i++) {
        if (students[i].id == id) {
            for (int j = i; j < *n - 1; j++) {
                students[j] = students[j + 1];
            }
            (*n)--;
            writeFile(students, *n);
            printf("Sinh vien da duoc xoa.\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID %d.\n", id);
}

void searchStudent(struct Student students[], int n) {
    int id;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (students[i].id == id) {
            printf("\nSinh vien tim thay: \n");
            printf("%-5s%-20s%-10s\n", "ID", "Name", "Age");
            printf("%-5d%-20s%-10d\n", students[i].id, students[i].name, students[i].age);
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID %d.\n", id);
}

void sortStudents(struct Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (students[i].id > students[j].id) {
                struct Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    writeFile(students, n);
    printf("Danh sach sinh vien da duoc sap xep.\n");
}

int main() {
    struct Student students[100];
    int n = 0;
    readFile(students, &n);

    int choice;
    do {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printStudents(students, n);
                break;
            case 2:
                addStudent(students, &n);
                break;
            case 3:
                editStudent(students, n);
                break;
            case 4:
                deleteStudent(students, &n);
                break;
            case 5:
                searchStudent(students, n);
                break;
            case 6:
                sortStudents(students, n);
                break;
            case 7:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
                break;
        }
    } while (choice != 7);

    return 0;
}

