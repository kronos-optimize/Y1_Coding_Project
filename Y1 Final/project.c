#include <stdio.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define FILE_NAME "employees.bin"

struct employee {
    int id;
    char name[50];
    char department[30];
    float salary;
};

struct employee employeeList[MAX_EMPLOYEES];
int CURRENT_EMPLOYEES = 0;

void writeEmployees() {
    FILE *fp = fopen(FILE_NAME, "wb");
    if (fp == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }
    fwrite(employeeList, sizeof(struct employee), CURRENT_EMPLOYEES, fp);
    fclose(fp);
}

void loadEmployees() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("Failed to read file.\n");
        return;
    }
    CURRENT_EMPLOYEES = fread(employeeList, sizeof(struct employee), MAX_EMPLOYEES, fp);
    fclose(fp);
}

void addEmployee() {
    if (CURRENT_EMPLOYEES >= MAX_EMPLOYEES) {
        printf("Employee list is full.\n");
        return;
    }

    struct employee emp;
    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Employee Name: ");
    scanf(" %[^\n]", emp.name);
    printf("Enter Employee Department: ");
    scanf(" %[^\n]", emp.department);
    printf("Enter Employee Salary: ");
    scanf("%f", &emp.salary);

    employeeList[CURRENT_EMPLOYEES++] = emp;
    writeEmployees();
    printf("Employee added successfully.\n");
}

void updateEmployee(int id) {
    int found = 0;
    for (int i = 0; i < CURRENT_EMPLOYEES; i++) {
        if (employeeList[i].id == id) {
            printf("Enter new name: ");
            scanf(" %[^\n]", employeeList[i].name);
            printf("Enter new department: ");
            scanf(" %[^\n]", employeeList[i].department);
            printf("Enter new salary: ");
            scanf("%f", &employeeList[i].salary);
            writeEmployees();
            printf("Employee updated successfully.\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }
}

void deleteEmployee(int id) {
    int found = 0;
    for (int i = 0; i < CURRENT_EMPLOYEES; i++) {
        if (employeeList[i].id == id) {
            for (int j = i; j < CURRENT_EMPLOYEES - 1; j++) {
                employeeList[j] = employeeList[j + 1];
            }
            CURRENT_EMPLOYEES--;
            writeEmployees();
            printf("Employee deleted successfully.\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }
}

void showEmployee(struct employee emp) {
    printf("---------------------------------------------\n");
    printf("ID: %d\n", emp.id);
    printf("Name: %s\n", emp.name);
    printf("Department: %s\n", emp.department);
    printf("Salary: %.2f\n", emp.salary);
    printf("---------------------------------------------\n");
}

void displayAllEmployees() {
    if (CURRENT_EMPLOYEES == 0) {
        printf("No employees to display.\n");
        return;
    }

    printf("\nAll Employees:\n");
    for (int i = 0; i < CURRENT_EMPLOYEES; i++) {
        showEmployee(employeeList[i]);
    }
}

int main() {
    loadEmployees();
    int opt, id;

    do {
        printf("\n*************** Employee Management System ***************\n");
        printf("1. Add Employee\n2. Display Employees\n3. Update Employee\n4. Delete Employee\n0. Exit\n");
        printf("Please select an option: ");
        scanf("%d", &opt);

        switch (opt) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayAllEmployees();
                break;
            case 3:
                printf("Enter Employee ID to update: ");
                scanf("%d", &id);
                updateEmployee(id);
                break;
            case 4:
                printf("Enter Employee ID to delete: ");
                scanf("%d", &id);
                deleteEmployee(id);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option, please try again.\n");
        }
    } while (opt != 0);

    return 0;
}
