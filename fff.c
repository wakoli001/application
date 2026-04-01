#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//Create a structure called Student
struct Student{
    char name[50];
    char RegNo[30];
    float GPA;
    char course[50];
    int year;
};

int main(){
    int choice;
    struct Student students[1000];
    int count = 0;

    time_t Timer;
    time(&Timer);
    //Now write the display menu for the student management system

 do{
    printf("\n===========  Display Menu  =============\n");
    printf("1. Add Student\n");
    printf("2. Delete student\n");
    printf("3. Search Student By Registration number\n");
    printf("5. Display All Students\n");
    printf("6. Exit\n");
    printf("========================================\n");
    printf("%s\n",ctime(&Timer));
    printf("========================================\n");
       printf("Enter your choice: ");
         scanf("%d", &choice);

    switch(choice){
        case 1:
            printf("Enter Student's Details.\n");
            fgets(students[count].name, sizeof(name),stdin);
            printf("Enter student name: ");
            fgets(students[count].name, sizeof(name), stdin);
            printf("Enter registration number: ");
            fgets(students[count].RegNo,sizeof(RegNo), stdin);
             printf("Enter course: ");
            fgets(students[count].course, sizeof(course), stdin);
            printf("Enter GPA: ");
            scanf("%f", &students[count].GPA);
            printf("Enter year of study: ");
            scanf("%d", &students[count].year);
            count++;
            break;
        case 2:
            // Code to delete student
            printf("Enter registration number of student to delete: ");
            int regNoToDelete;
            scanf("%d", &regNoToDelete);
            for(int i = 0; i < count; i++){
                if(students[i].RegNo == regNoToDelete){
                    for(int j = i; j < count - 1; j++){
                        students[j] = students[j + 1];
                    }
                    count--;
                    printf("Student deleted successfully.\n");
                    break;
                }
            }

            break;
        case 3:
            // Code to search student by registration number
            printf("Enter registration number of student to search: ");
            int regNoToSearch;
            scanf("%d", &regNoToSearch);
            int found = 0;
            for(int i = 0; i < count; i++){
                if(students[i].RegNo == regNoToSearch){
                    printf("Student Found.\n");
                    printf("Name : %s\n", students[i].name);
                    printf("Course : %s\n", students[i].course);
                    printf("GPA : %.2f\n", students[i].GPA);
                    printf("Registration Number : %d\n", students[i].RegNo);
                    printf("Year Of Study : %d\n",students[i].year);
                    found = 1;
                    break;
                }
            }
            if(!found){
                printf("Student Not found.\n");
                break;
                }

            break;
        case 5:
            // Code to display all students
            printf("All Students:\n");
            for(int i = 0; i < count; i++){
                printf("%s\n", students[i].name);
            }
            break;

            break;
        case 6:
            printf("Exiting the program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
    }
 }while (choice !=6);

    return 0;
}
