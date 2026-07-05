
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    char department[50];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n=====================================\n");
        printf("   STUDENT MANAGEMENT SYSTEM\n");
        printf("=====================================\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nThank you!\n");
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}

void addStudent() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "ab");

    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Department: ");
    scanf(" %[^\n]", s.department);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("\nStudent added successfully!\n");
}

void displayStudents() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "rb");

    if(fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    printf("\n----- Student Records -----\n");

    while(fread(&s, sizeof(s), 1, fp)) {
        printf("\nID: %d", s.id);
        printf("\nName: %s", s.name);
        printf("\nAge: %d", s.age);
        printf("\nDepartment: %s", s.department);
        printf("\nMarks: %.2f\n", s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp;
    struct Student s;
    int id, found = 0;

    fp = fopen("students.dat", "rb");

    if(fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    printf("\nEnter Student ID to search: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.id == id) {
            printf("\nStudent Found!\n");
            printf("ID: %d\n", s.id);
            printf("Name: %s\n", s.name);
            printf("Age: %d\n", s.age);
            printf("Department: %s\n", s.department);
            printf("Marks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("\nStudent not found.\n");

    fclose(fp);
}

void updateStudent() {
    FILE *fp;
    struct Student s;
    int id, found = 0;

    fp = fopen("students.dat", "rb+");

    if(fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    printf("\nEnter Student ID to update: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.id == id) {

            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Age: ");
            scanf("%d", &s.age);

            printf("Enter New Department: ");
            scanf(" %[^\n]", s.department);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            printf("\nRecord updated successfully!\n");
            found = 1;
            break;
        }
    }

    if(!found)
        printf("\nStudent not found.\n");

    fclose(fp);
}

void deleteStudent() {
    FILE *fp, *temp;
    struct Student s;
    int id, found = 0;

    fp = fopen("students.dat", "rb");

    if(fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    printf("\nEnter Student ID to delete: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.id == id) {
            found = 1;
        } else {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if(found)
        printf("\nRecord deleted successfully!\n");
    else
        printf("\nStudent not found.\n");
}