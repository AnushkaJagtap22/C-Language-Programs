#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int roll;
    char name[50];
    int attendance;
};

void addStudent();
void markAttendance();
void displayRecords();
void searchStudent();

int main()
{
    int choice;
    while (1)
    {
        printf("\n===== Attendance Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Mark Attendance\n");
        printf("3. Display All Records\n");
        printf("4. Search Student by Roll Number\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            markAttendance();
            break;
        case 3:
            displayRecords();
            break;
        case 4:
            searchStudent();
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void addStudent()
{
    struct Student s;
    FILE *fp;
    fp = fopen("attendance.dat", "ab");
    if (!fp)
    {
        printf("Error in opening file!\n");
        return;
    }
    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    getchar(); // clear newline
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0; // remove newline
    s.attendance = 0;
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Student added successfully!\n");
}

void markAttendance()
{
    FILE *fp;
    struct Student s;
    int roll, found = 0;
    char status;
    fp = fopen("attendance.dat", "rb+");
    if (!fp)
    {
        printf("No records found!\n");
        return;
    }
    printf("Enter Roll Number to mark attendance: ");
    scanf("%d", &roll);
    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.roll == roll)
        {
            found = 1;
            printf("Mark attendance for %s (P/A): ", s.name);
            scanf(" %c", &status);
            if (status == 'P' || status == 'p')
                s.attendance++;
            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            printf("Attendance updated!\n");
            break;
        }
    }
    fclose(fp);
    if (!found)
        printf("Student not found!\n");
}

void displayRecords()
{
    FILE *fp;
    struct Student s;
    fp = fopen("attendance.dat", "rb");
    if (!fp)
    {
        printf("No records found!\n");
        return;
    }
    printf("\n--- Attendance Records ---\n");
    printf("%-10s %-20s %-10s\n", "Roll", "Name", "Attendance");
    while (fread(&s, sizeof(s), 1, fp))
    {
        printf("%-10d %-20s %-10d\n", s.roll, s.name, s.attendance);
    }
    fclose(fp);
}

void searchStudent()
{
    FILE *fp;
    struct Student s;
    int roll, found = 0;
    fp = fopen("attendance.dat", "rb");
    if (!fp)
    {
        printf("No records found!\n");
        return;
    }
    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);
    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.roll == roll)
        {
            printf("\nStudent Found!\n");
            printf("Roll: %d\nName: %s\nAttendance: %d\n", s.roll, s.name, s.attendance);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (!found)
        printf("Student not found!\n");
}
