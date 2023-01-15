#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATIENTS 100

typedef struct patient {
    char name[30];
    char guardian[30];
    char phone[15];
    char address[50];
    int room_number;
    char doctor[30];
    int unique_number;
} Patient;

Patient patients[MAX_PATIENTS];
int patient_count = 0;

int free_room_numbers[30] = {101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 
                              111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 
                              121, 122, 123, 124, 125, 126, 127, 128, 129, 130};
int top = 29;

char doctors[15][30] = {"John Smith", "Jane Doe", "Michael Johnson", "Emily Davis", 
                       "Jacob Brown", "Madison Garcia", "Ethan Rodriguez", 
                       "Sofia Wilson", "Isabella Martinez", "Mia Anderson", 
                       "Jacob Thompson", "Ethan Garcia", "Emily Martinez", 
                       "Madison Thompson", "Isabella Anderson"};
int doctor_top = 14;

void push_room(int room_number) {
    free_room_numbers[++top] = room_number;
}

int pop_room() {
    return free_room_numbers[top--];
}

char* pop_doctor() {
    return doctors[doctor_top--];
}

void add_patient() {
    Patient new_patient;
    printf("Enter patient name: ");
    scanf("%s", new_patient.name);
    printf("Enter guardian name: ");
    scanf("%s", new_patient.guardian);
    printf("Enter phone number: ");
    scanf("%s", new_patient.phone);
    printf("Enter home address: ");
    scanf("%s", new_patient.address);
    new_patient.room_number = pop_room();
        strcpy(new_patient.doctor, pop_doctor());
    new_patient.unique_number = rand() % 9000 + 1000;
    patients[patient_count++] = new_patient;
    printf("Patient added successfully!\n");
}

void view_patients() {
    if (patient_count == 0) {
        printf("No patients to display.\n");
        return;
    }
    printf("%-30s %-30s %-15s %-50s %-5s %-30s %-5s\n", "Patient Name", "Guardian Name", "Phone Number", "Home Address", "Room", "Doctor", "Unique Number");
    for (int i = 0; i < patient_count; i++) {
        Patient patient = patients[i];
        printf("%-30s %-30s\n", patient.name, patient.guardian);
        printf("%-15s %-50s\n", patient.phone, patient.address);
        printf("%-5d %-30s %-5d\n", patient.room_number, patient.doctor, patient.unique_number);
        printf("\n");
    }
}

void delete_patient() {
int unique_number;
printf("Enter patient unique number: ");
scanf("%d", &unique_number);
int patient_index = -1;
for (int i = 0; i < patient_count; i++) {
if (patients[i].unique_number == unique_number) {
patient_index = i;
break;
}
}
if (patient_index == -1) {
printf("Patient not found.\n");
return;
}
char confirm;
printf("Are you sure you want to delete patient %s (y/n)? ", patients[patient_index].name);
scanf(" %c", &confirm);
if (confirm == 'y') {
push_room(patients[patient_index].room_number);
for (int i = patient_index; i < patient_count - 1; i++) {
patients[i] = patients[i + 1];
}
patient_count--;
printf("Patient deleted successfully!\n");
} else {
printf("Delete cancelled.\n");
}
}

int main() {
srand(time(0));
int choice;
do {
printf("\nHospital Management System\n");
printf("1. Add patient\n");
printf("2. View patients\n");
printf("3. Delete patient\n");
printf("4. Exit\n");
printf("Enter choice: ");
scanf("%d", &choice);
switch (choice) {
case 1:
add_patient();
break;
case 2:
view_patients();
break;
case 3:
delete_patient();
break;
case 4:
printf("Exiting program.\n");
break;
default:
printf("Invalid choice.\n");
}
} while (choice != 4);
return 0;
}
