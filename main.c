#include <stdio.h>
#include <stdlib.h>
#include "STD_TYPES.h"
#include "LinkedList.h"

patient *head;

void main(void) {
    u32 input;
    patient p;
    u8 i;
    u32 exitFlag2 = 0;

    while (exitFlag2 == 0) {
        printf("-Press 1 to access admin mode.\n-Press 2 to access user mode.\n");
        scanf("%d", &input);
        
        if (input == 1) { // Admin mode
            for (i = 0; i < 3; i++) { // Password entry loop
                printf("Please enter the password: ");
                scanf("%d", &input);
                if (input == 1234) { // Correct password
                    break;
                }
            }
            if (i != 3) { // Password entered correctly
                u32 exitFlag = 0;
                while (exitFlag == 0) {
                    u32 ID;
                    printMenu();
                    scanf("%d", &input);
                    switch (input) {
                        case 1: addPatient(inputData(&p));
                                break;
                        case 2: printf("Enter the patient's ID: ");
                                scanf("%d", &ID);
                                updatePatientData(checkPatientID(ID));
                                break;
                        case 3: chosenMode(3);
                                break;
                        case 4: chosenMode(4);
                                break;
                        case 5: displayAllPatients();
                                break;
                        case 6: exitFlag = -1;
                                break;
                        case 7: exitFlag2 = -1;
                                exitFlag = -1;
                                break;
                        default: printf("Invalid choice.\n");
                    }
                }
            } else {
                printf("Incorrect password entered three times.\n");
                return;
            }
        } else if (input == 2) { // User mode
            u32 exitFlag = 0;
            while (exitFlag == 0) {
                printf("-Press 1 to view patient record by ID.\n");
                printf("-Press 2 to view today's reservations.\n");
                printf("-Press 3 to exit user mode.\n");
                printf("-Press 4 to exit the program.\n");
                scanf("%d", &input);
                switch (input) {
                    u32 ID;
                    case 1: printf("Enter the patient's ID: ");
                            scanf("%d", &ID);
                            printPatientData(checkPatientID(ID));
                            break;
                    case 2: printReservedSlots();
                            break;
                    case 3: exitFlag = -1;
                            break;
                    case 4: exitFlag2 = -1;
                            exitFlag = -1;
                            break;
                    default: printf("Invalid choice.\n");
                }
            }
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
}
