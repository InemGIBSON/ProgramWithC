#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASS     _MARKS 40

typedef struct {
    char name[50];
    int rollNumber;
    int marks;
} Student;

Student *students = NULL;
int studentCount = 0;

void greetUser() {
    char username[50];
    printf("Welcome to  SRSv.1 - Your Dynamic Student Record System, Please Enter your name: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    printf("Welcome, %s!\n", username);
}

void addStudent() {
    students = realloc(students, (studentCount + 1) * sizeof(Student));
    if (!students) {
        printf("Memory allocation failed!\n");
        return;
    }
    printf("Enter student's name: ");
    fgets(students[studentCount].name, sizeof(students[studentCount].name), stdin);
    students[studentCount].name[strcspn(students[studentCount].name, "\n")] = '\0';

    printf("Enter roll number: ");
    scanf("%d", &students[studentCount].rollNumber);

    printf("Enter marks: ");
    scanf("%d", &students[studentCount].marks);
    getchar(); // To consume newline after scanf

    printf("Student %s has %s.\n", students[studentCount].name,
           students[studentCount].marks >= PASS_MARKS ? "passed" : "failed");

    studentCount++;
}

void displayStudents() {
    printf("\nStudent Records:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("Name: %s, Roll Number: %d, Marks: %d\n",
               students[i].name, students[i].rollNumber, students[i].marks);
    }
}

void modifyStudent() {
    int rollNumber;
    printf("Enter roll number of the student to modify: ");
    scanf("%d", &rollNumber);
    getchar();

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("Enter new name: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';

            printf("Enter new marks: ");
            scanf("%d", &students[i].marks);
            getchar();

            printf("Record updated!\n");
            return;
        }
    }
    printf("Student with roll number %d not found.\n", rollNumber);
}

void deleteStudent() {
    int rollNumber;
    printf("Enter roll number of the student to delete: ");
    scanf("%d", &rollNumber);
    getchar();

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            students = realloc(students, studentCount * sizeof(Student));
            printf("Student deleted!\n");
            return;
        }
    }
    printf("Student with roll number %d not found.\n", rollNumber);
}

void searchStudent() {
    int rollNumber;
    printf("Enter roll number to search: ");
    scanf("%d", &rollNumber);
    getchar();

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("Name: %s, Marks: %d\n", students[i].name, students[i].marks);
            return;
        }
    }
    printf("Student with roll number %d not found.\n", rollNumber);
}

void saveToFile() {
    FILE *file = fopen("student_records.txt", "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%s %d %d\n", students[i].name, students[i].rollNumber, students[i].marks);
    }
    fclose(file);
    printf("Records saved to file.\n");
}

void loadFromFile() {
    FILE *file = fopen("student_records.txt", "r");
    if (!file) {
        printf("Error opening file for reading.\n");
        return;
    }
    studentCount = 0;
    while (fscanf(file, "%s %d %d", students[studentCount].name,
                  &students[studentCount].rollNumber, &students[studentCount].marks) != EOF) {
        studentCount++;
        students = realloc(students, studentCount * sizeof(Student));
    }
    fclose(file);
    printf("Records loaded from file.\n");
}

void calculateAverageMarks() {
    if (studentCount == 0) {
        printf("No students available.\n");
        return;
    }
    int sum = 0;
    for (int i = 0; i < studentCount; i++) {
        sum += students[i].marks;
    }
    printf("Average marks: %.2f\n", (float)sum / studentCount);
}

int compareAscending(const void *a, const void *b) {
    return ((Student *)a)->marks - ((Student *)b)->marks;
}

int compareDescending(const void *a, const void *b) {
    return ((Student *)b)->marks - ((Student *)a)->marks;
}

void sortStudents(int order) {
    qsort(students, studentCount, sizeof(Student), order == 1 ? compareAscending : compareDescending);
    printf("Students sorted.\n");
}

int main() {
    greetUser();
    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Student\n2. Display Students\n3. Modify Student\n");
        printf("4. Delete Student\n5. Search Student\n6. Save to File\n");
        printf("7. Load from File\n8. Calculate Average Marks\n");
        printf("9. Sort Students\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: modifyStudent(); break;
            case 4: deleteStudent(); break;
            case 5: searchStudent(); break;
            case 6: saveToFile(); break;
            case 7: loadFromFile(); break;
            case 8: calculateAverageMarks(); break;
            case 9: {
                int order;
                printf("Enter 1 for ascending, 2 for descending: ");
                scanf("%d", &order);
                sortStudents(order);
                break;
            }
            case 0:
                free(students);
                printf("Exiting...\n");
                return 0;
            default: printf("Invalid choice!\n");
        }
    }
}

