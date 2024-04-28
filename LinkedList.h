#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H
#define MAX_SLOTS 5
typedef struct patient_Node patient;
static void displayAvailableTimeSlots(void);

static void reserveAppointment(u32 userID);

void printReservedSlots(void);

static void cancelReservation(void);

void chosenMode(u8 mode);

void printMenu (void);

void updatePatientData(patient *current);

void displayAllPatients(void);

patient* checkPatientID(u32 ID);
patient* inputData(patient *p);

void addPatient(patient *pat);
void printPatientData(patient *pat);
struct patient_Node
{
    u8 name[60];
	u8 gender[8]; 
	u32 ID;
	u32 age;
	patient *next;
};
#endif