#include "STD_TYPES.h"
#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>
extern patient *head;
s8 appointmentSlots[MAX_SLOTS]={-1,-1,-1,-1,-1};
static void displayAvailableTimeSlots(void)
{
    printf("Available Slots:\n");
    if (appointmentSlots[0] == -1)
        printf("- 2:00 PM to 2:30 PM...Press 1 to reserveAppointment.\n");
    if (appointmentSlots[1] == -1)
        printf("- 2:30 PM to 3:00 PM...Press 2 to reserveAppointment.\n");
    if (appointmentSlots[2] == -1)
        printf("- 3:00 PM to 3:30 PM...Press 3 to reserveAppointment.\n");
    if (appointmentSlots[3] == -1)
        printf("- 4:00 PM to 4:30 PM...Press 4 to reserveAppointment.\n");
    if (appointmentSlots[4] == -1)
        printf("- 4:30 PM to 5:00 PM...Press 5 to reserveAppointment.\n");
}

static void reserveAppointment(u32 userID)
{
    displayAvailableTimeSlots(); // Show available slots
    u32 chosenSlot;
    printf("Enter your choice: ");
    scanf("%d", &chosenSlot);

    if (chosenSlot > 0 && chosenSlot < MAX_SLOTS) {
        u32 slotIndex = chosenSlot - 1; // Convert user choice to index
        if (appointmentSlots[slotIndex] == -1) {
            appointmentSlots[slotIndex] = userID; // Book the slot
            printf("Appointment successfully booked!\n");
        } else {
            printf("Slot already booked. Please choose another slot.\n");
        }
    } else {
        printf("Invalid choice. Please select a slot between 1 and 5.\n");
    }
}

void printReservedSlots(void) {
    printf("Reserved Slots:\n");
    if (appointmentSlots[0] != -1) {
        printf("1. From 2pm to 2:30pm, booked by ID: %d\n", appointmentSlots[0]);
    }
    if (appointmentSlots[1] != -1) {
        printf("2. From 2:30pm to 3pm, booked by ID: %d\n", appointmentSlots[1]);
    }
    if (appointmentSlots[2] != -1) {
        printf("3. From 3pm to 3:30pm, booked by ID: %d\n", appointmentSlots[2]);
    }
    if (appointmentSlots[3] != -1) {
        printf("4. From 4pm to 4:30pm, booked by ID: %d\n", appointmentSlots[3]);
    }
    if (appointmentSlots[4] != -1) {
        printf("5. From 4:30pm to 5pm, booked by ID: %d\n", appointmentSlots[4]);
    }
    if (appointmentSlots[0] == -1 && appointmentSlots[1] == -1 && appointmentSlots[2] == -1 && appointmentSlots[3] == -1 && appointmentSlots[4] == -1)
        printf("No slots are booked!\n");
}

static void cancelReservation(void) {
    printReservedSlots();
    u32 chosenSlot;
    printf("Enter the slot number to cancel reservation: ");
    scanf("%d", &chosenSlot);
    
    if (chosenSlot >= 1 && chosenSlot <= MAX_SLOTS) {
        int slotIndex = chosenSlot - 1; // Convert slot number to array index
        if (appointmentSlots[slotIndex] != -1) { // If the chosen slot is not empty
            appointmentSlots[slotIndex] = -1; // Cancel the reservation
            printf("Reservation for slot %d cancelled successfully.\n", chosenSlot);
        } else {
            printf("Slot %d is already empty.\n", chosenSlot);
        }
    } else {
        printf("Invalid slot number. Please choose a slot between 1 and %d.\n", MAX_SLOTS);
    }
}


void chosenMode(u8 mode)
{
    if(mode == 3) // Reserve Appointment Mode
    {
        u32 patientID;
        printf("Enter the Patient ID: ");
        scanf("%d", &patientID); // Taking the ID to reserve an appointment.
        if(checkPatientID(patientID) != NULL) // Check if the ID is in the patient list.
        {
            reserveAppointment(patientID);
        }   
        else 
        {
            printf("Patient ID does not exist!\n"); // If the ID does not exist.
        }
    }
    else if (mode == 4) // Cancel Reservation Mode
    {
        cancelReservation();
    }
    else
    {
        printf("Incorrect mode!\n"); // If the mode chosen is incorrect.
    }
}

void printMenu(void)
{
    printf("\n-Press 1 to add a new patient.");
    printf("\n-Press 2 to edit existing patient information.");
    printf("\n-Press 3 to reserve an appointment with the doctor.");
    printf("\n-Press 4 to cancel a reservation.\n");
    printf("-Press 5 to display all patient data.\n");
    printf("-Press 6 to exit Admin mode.\n");
    printf("-Press 7 to exit the program.\n");
}

void updatePatientData(patient *current) {
    u32 choice;
    // Check if the pointer is valid
    if (current == NULL) {
        printf("Patient Not Found!\n");
        return;
    }
    printf("\nCurrent Patient Data:\n");
    printPatientData(current);
    printf("- Enter 1 To Update ID.\n");
    printf("- Enter 2 To Update Name.\n");
    printf("- Enter 3 To Update Age.\n");
    printf("- Enter 4 To Update Gender.\n");
    printf("Enter your choice: ");
    // Ensure input is numeric
    if (scanf("%u", &choice) != 1) {
        printf("Invalid input! Please enter a number.\n");
        return;
    }
    switch (choice) {
    case 1:
        printf("Enter The New ID: ");
        if (scanf("%d", &current->ID) != 1) {
            printf("Invalid input! Please enter a number.\n");
            return;
        }
        printf("ID Updated!\n");
        break;
    case 2:
        printf("Enter The New Name (max 29 characters): ");
        // Limit input length to prevent buffer overflow
        if (scanf("%29s", current->name) != 1) {
            printf("Invalid input! Please enter a valid name.\n");
            return;
        }
        printf("Name Updated!\n");
        break;
    case 3:
        printf("Enter The New Age: ");
        if (scanf("%d", &current->age) != 1) {
            printf("Invalid input! Please enter a number.\n");
            return;
        }
        printf("Age Updated!\n");
        break;
    case 4:
        printf("Enter The New Gender (max 9 characters): ");
        // Limit input length to prevent buffer overflow
        if (scanf("%9s", current->gender) != 1) {
            printf("Invalid input! Please enter a valid gender.\n");
            return;
        }
        printf("Gender Updated!\n");
        break;
    default:
        printf("Invalid Choice!\n");
        break;
    }
}

void displayAllPatients(void)
{
    patient *current = head;
    if (current == NULL)
    {
        printf("No Patients Found!\n");
        return;
    }
    printf("List of Patients:\n");
    while (current != NULL)
    {
        printPatientData(current);
        current = current->next;
    }
}

patient* checkPatientID(u32 ID) //Check If The ID is Exist or not.
{
	patient *current = head;
		while(current!=NULL) // Loop On The List
		{
			if(current->ID==ID)
			{
					return current; //ID Exist
			}
			current=current->next;
		}
		return NULL; //ID Not Exist
}

patient* inputData(patient *p)
{
	u32 ID;
	u32 check=0;
	while(check==0)
	{
		printf("Enter Patient ID:");
		scanf("%d",&ID);
		if(checkPatientID(ID)==NULL)
		{
			p->ID=ID;
			check=-1;
		}
		else 
		{
			printf("ID Already Taken !\n");
		}
	}

	printf("Enter Patient Name:");
	scanf("%s",p->name);
	printf("Enter Patient Age:");
	scanf("%d",&p->age);
	printf("Enter Patient Gender:");
	scanf("%s",p->gender);
	printf("\n======================================\n");

	return p;
}

void printPatientData(patient *pat)
{
	//Function To Print The Data of The patient that had been passed to the function.
	printf("\n======================================");
	printf("\nPatient ID :%d",pat->ID);
	printf("\nPatient Name :%s",pat->name);
	printf("\nPatient Age :%d",pat->age);
	printf("\nPatient Gender :%s",pat->gender);
	printf("\n======================================\n");
}

void addPatient(patient *pat)
{
	u32 size = sizeof(pat->name) / sizeof(pat->name[1]) ;
	// Function to add new record of a patient.
	patient *current = head; //pointer to loop on the list
	patient *temp = (patient*)malloc(sizeof(patient));	// create new node
	for(u16 i=0;i<=size;i++)
	{
		temp->name[i]=pat->name[i];
	}
	size = sizeof(pat->gender) / sizeof(pat->gender[1]) ;
	for(u16 i=0;i<=size;i++)
	{
		temp->gender[i]=pat->gender[i];
	}
	temp->ID=pat->ID;               //Put The Data Into Temp .
	temp->age=pat->age;
	temp->next=NULL;
	if(head==NULL) // If List is Empty
	{
		head=temp;
	}
	else 
	{
		while((current->next)!=NULL) // Move Until Founding the last record.
		{
			current=(current->next); // if not found move to next one.
		// This Loop "Must" exit with the last node in 'current'
		}
		(current->next)=temp; //but the new record at the end of the list.
	}
}

