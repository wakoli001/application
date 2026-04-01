#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// ================= ARRAY =================
struct Employee {
    int id;
    char name[50];
    char department[50];
};

struct Employee arr[MAX];
int count = 0;

// ================= LINKED LIST =================
struct Node {
    int id;
    char name[50];
    char department[50];
    struct Node* next;
};

struct Node* head = NULL;

// ================= STACK (for undo delete) =================
struct Stack {
    int id;
    char name[50];
    char department[50];
};

struct Stack stack[MAX];
int top = -1;

// Push to stack
void push(struct Employee emp) {
    if (top == MAX - 1) {
        printf("Stack overflow!\n");
        return;
    }
    top++;
    stack[top].id = emp.id;
    strcpy(stack[top].name, emp.name);
    strcpy(stack[top].department, emp.department);
}

// Pop from stack
struct Employee pop() {
    struct Employee emp;
    if (top == -1) {
        printf("Stack underflow!\n");
        emp.id = -1;
        return emp;
    }
    emp.id = stack[top].id;
    strcpy(emp.name, stack[top].name);
    strcpy(emp.department, stack[top].department);
    top--;
    return emp;
}

// ================= ADD EMPLOYEE =================
void addEmployee() {
    struct Employee emp;

    if (count >= MAX) {
        printf("Array full!\n");
        return;
    }

    printf("\nEnter Employee ID: ");
    scanf("%d", &emp.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", emp.name);

    printf("Enter Department: ");
    scanf(" %[^\n]", emp.department);

    // Add to ARRAY
    arr[count++] = emp;

    // Add to LINKED LIST
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->id = emp.id;
    strcpy(newNode->name, emp.name);
    strcpy(newNode->department, emp.department);
    newNode->next = head;
    head = newNode;

    printf("Employee added successfully!\n");
}

// ================= DISPLAY =================
void displayEmployees() {
    if (count == 0) {
        printf("\nNo records!\n");
        return;
    }

    printf("\n--- Employees (ARRAY) ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Dept: %s\n",
               arr[i].id, arr[i].name, arr[i].department);
    }

    printf("\n--- Employees (LINKED LIST) ---\n");
    struct Node* temp = head;
    while (temp != NULL) {
        printf("ID: %d | Name: %s | Dept: %s\n",
               temp->id, temp->name, temp->department);
        temp = temp->next;
    }
}

// ================= DELETE =================
void deleteEmployee() {
    int id, found = 0;

    printf("\nEnter Employee ID to delete: ");
    scanf("%d", &id);

    // Delete from ARRAY
    for (int i = 0; i < count; i++) {
        if (arr[i].id == id) {
            push(arr[i]); // save to stack

            for (int j = i; j < count - 1; j++) {
                arr[j] = arr[j + 1];
            }
            count--;
            found = 1;
            break;
        }
    }

    // Delete from LINKED LIST
    struct Node *temp = head, *prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL) {
        if (prev == NULL)
            head = temp->next;
        else
            prev->next = temp->next;

        free(temp);
    }

    if (found)
        printf("Employee deleted (can undo)\n");
    else
        printf("Employee not found!\n");
}

// ================= UNDO DELETE =================
void undoDelete() {
    struct Employee emp = pop();

    if (emp.id == -1)
        return;

    // Restore to ARRAY
    arr[count++] = emp;

    // Restore to LINKED LIST
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->id = emp.id;
    strcpy(newNode->name, emp.name);
    strcpy(newNode->department, emp.department);
    newNode->next = head;
    head = newNode;

    printf("Undo successful! Employee restored.\n");
}

// ================= SEARCH =================
void searchEmployee() {
    int id, found = 0;

    printf("\nEnter Employee ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (arr[i].id == id) {
            printf("Found: %s (%s)\n", arr[i].name, arr[i].department);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Employee not found!\n");
}

// ================= MAIN =================
int main() {
    int choice;

    do {
        printf("\n==== Morgan Enterprises Management System ====\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Undo Delete (Stack)\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: deleteEmployee(); break;
            case 5: undoDelete(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}
