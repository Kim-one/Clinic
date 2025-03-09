/*
Name: Kimone Barrett
Candidate Number: 1000100097
Purpose: Program to add, delete, update, search for and view all patients and employee records in a file.
*/

// libraries
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <dos.h>
#include <ctype.h>
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_MAGENTA (FOREGROUND_RED | FOREGROUND_BLUE)
#define FOREGROUND_CYAN (FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_INTENSE_CYAN (FOREGROUND_CYAN | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_MAGENTA (FOREGROUND_MAGENTA | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_YELLOW (FOREGROUND_YELLOW | FOREGROUND_INTENSITY)

// HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
WORD wOldColorAttrs;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
char ans;

// employee structure
struct employee
{
    int IDnum; // employee identification number
    int parish;
    int gender;
    char fname[25];        // employee first name
    char sname[25];        // employee surname
    char mname[25];        // employee middle name
    char type[25];         // nurse or doctor
    char dob[15];          // employee date of birth
    char TRN[12];          // employee tax registration number
    char address[30];      // employee address
    char emailaddress[50]; // employee email address
    char telephone[15];    // employee telephone number
    char NIS[10];          // employees NIS number
    char position[30];     // time that the worker logged out of the system
}; // end of employee structure

// patient structure
struct patient
{
    int docNum;               // patient id number
    int age;                  // patient age
    char dob[15];             // patient date of birth
    char fname[25];           // patient first name
    char lname[25];           // patient last name
    char midname[25];         // patient middle name
    int genderOption;         // male or female
    char lastvisit[15];       // patient's date of last visit to the hospitol
    char medicalHistory[200]; // patient medical history
    char address[30];         // patient address
    int parish;
    char emailaddress[50];          // patient email address
    char telephone[15];             // patient telephone number
    float height;                   // patient height
    float weight;                   // patient weight
    char bp[8];                     // blood pressure
    char reasonforvisit[30];        // reason why they visited
    int temperature;                // patients temperature
    char comments[50];              // comments about the patient
    int cholesterol;                // patients cholesterol level
    char prescription[100];         // patients prescription
    char prescriptionHistory[1000]; // patients prescription history
    char nextofkinfname[25];        // next of kin first name
    char nextofkinLname[25];        // next of kin last name
    char nextofkinaddress[50];      // next of kin address
    int nextofkinparish;
    char nextofkintelephone[15]; // next of kin telephone
    char relationship[20];       // relationship between patient and next of kin
}; // end of patient structure

// appointment structure
struct appointmentdate
{
    int appointmentID;
    int year;             // year of appointment
    int appointmentmonth; // appointment month
    int appointmentday;   // appointment day
    char reason[80];      // reason for appointment
    struct patient patientapp;
}; // end of appointment structure

// function prototypes
void addEmployee(FILE *employeePtr);             // function to add employee
void updateEmployee(FILE *employeePtr);          // function to update employee
void deleteEmployee(FILE *employeePtr);          // function to delete employee
void searchEmployee(FILE *employeePtr);          // function to search for an employee
void viewALLEmployee(FILE *employeePtr);         // function to view all employees
void createEmployeeTextFile(FILE *reademployee); // function to create a readable text file
void addPatient(FILE *patientPtr);               // function to add patients
void updatePatient(FILE *patientPtr);            // function to update patients
void deletePatient(FILE *patientPtr);            // function to delete patients
void searchPatient(FILE *patientPtr);            // function to search for a patient
void viewALLPatient(FILE *patientPtr);           // function to view all patients
void createPatientTextFile(FILE *readpatient);   // function to create readable text file
void addAppointment(FILE *appointmentPtr);       // function to add and create appointment file
void updateAppointment(FILE *appointmentPtr);
void viewallappointment(FILE *appointmentPtr);
void textfileappointment(FILE *readAppointment);
int appointmentMenu();
void welcomescreen(); // function to display a welcome message to the users
void gotoxy();        // function to position the cursor at a specific point on the console for printing
int menu();           // function to display menu

// beginning of function gotoxy
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
} // end of function gotoxy

// beginning of function title
void title()
{
    system("cls");
    gotoxy(33, 9);
    printf("##################################################");
    gotoxy(31, 10);
    printf("  #\t\tRUNAWAY BAY HEALTH CENTER \t  #");
    gotoxy(33, 11);
    printf("##################################################");
    getch();
} // end of fucntion title

// beginning of updatePatientMenu
int updatePatientMenu()
{
    int updateOption;

    system("cls");
    system("COLOR 06");
    title();
    // saves the current colour information
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes;
    printf("\n\n\t\t\t\t*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*"
           "\n\t\t\t\t\t UPDATE PATIENT MENU"
           "\n\t\t\t\t  Choose the option for updating: "
           "\n\t\t\t\t\t1  - Update Vitals"
           "\n\t\t\t\t\t2  - Update Medical History"
           "\n\t\t\t\t\t3  - Update Prescription"
           "\n\t\t\t\t\t4  - Update Surname"
           "\n\t\t\t\t\t5  - Update Telephone Number"
           "\n\t\t\t\t\t6  - Update Address"
           "\n\t\t\t\t\t7  - Update Height"
           "\n\t\t\t\t\t8  - Update Next of Kin"
           "\n\t\t\t\t\t9  - Update Existing Next of Kin"
           "\n\t\t\t\t\t10 - Update Comments"
           "\n\t\t\t\t\t11 - Exit"
           "\n\t\t\t\t*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*  ==> ");
    scanf("%d", &updateOption);

    return updateOption;
} // end of function updatePatientMenu

// beginning of function updateEmployeeMenu
int updateEmployeeMenu()
{
    int updateOption;
    system("cls");
    system("COLOR 06");
    title();

    // saves the current colour information
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes;

    printf("\n\t\t\t**~**~**~**~**~**~**~**~**~**~**~**"
           "\n\t\t\t\tUPDATE EMPLOYEE MENU"
           "\n\t\t\tSelect the option for updating"
           "\n\t\t\t\t1 - Update Surname"
           "\n\t\t\t\t2 - Update Telephone Number"
           "\n\t\t\t\t3 - Update Address"
           "\n\t\t\t\t4 - Exit "
           "\n\t\t\t**~**~**~**~**~**~**~**~**~**~**~** ==> ");
    scanf("%d", &updateOption);

    return updateOption;
} // end of function updateEmployeeMenu

// beginning of function gender
void gender()
{
    printf("Select gender:"
           "\n1 - Female"
           "\n2 - Male:--> ");
} // end of function gender

// beginning of function parish
void addressParish()
{
    printf("\n\nPlease enter your parish of residence\n"
           "1 - St. Ann\n"
           "2 - Trelawny\n"
           "3 - St. Mary\n"
           "4 - St. James\n"
           "5 - Manchester\n"
           "6 - St. Catherine\n"
           "7 - St. Elizabeth\n"
           "8 - St. Thomas\n"
           "9 - Hanover\n"
           "10 - Westmoreland\n"
           "11 - Portland\n"
           "12 - Clarendon\n"
           "13 - Kingston\n"
           "14 - St. Andrew:--> ");
}
// beginning of login screen
void loginscreen(FILE *employeePtr)
{
    struct employee worker = {0, 0, 0, " ", " ", " ", " ", " ", " ", " ", " ", " ", " "};
    int loginType;
    int username;
    char exitProgram;
    char password[8] = "USER";
    char newpassword[8];
    int attempts = 3;
    char guestpwd[12] = "developer";
    char Tempguestpwd[12];
    system("COLOR F2");

    // saves the current colour information
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes;

    title();
menu:
    printf("\n\n\n\n\n\t\t\t\t==================================================");
    printf("\n\t\t\t\t||\t------------LOGIN SCREEN---------- \t||"
           "\n\t\t\t\t||\t\tChoose login type \t\t||"
           "\n\t\t\t\t||\t1 - Log in as Employee \t\t\t||"
           "\n\t\t\t\t||\t2 - Log in as Guest \t\t\t||"
           "\n\t\t\t\t||\t3 - Exit \t\t\t\t||");
    printf("\n\t\t\t\t==================================================");
    printf("\n\t\t\t\tEnter choice here ==> ");
    scanf("%d", &loginType);

    if (loginType == 1)
    {
        goto worker;
    } // end of if
    else if (loginType == 2)
    {
        goto guest;
    } // end of else if
    else if (loginType == 3)
    {
        printf("Are you sure you want to exit the program (Y/N)? ");
        scanf(" %c", &exitProgram);
        if (exitProgram == 'Y')
        {
            printf("\n\t\t\t\t\tGOODBYE :)");
            getch();
            exit(0);
        } // end of if
        else if (exitProgram == 'N')
        {
            system("cls");
            goto menu;
        }
        else
        {
            printf("Incorrect input. please enter Y or N.");
            getch();
            system("cls");
            goto menu;
        } // end of else
    } // end of else if
    else
    {
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("\n\t\t\t\t\t\tIncorrect Input.");
        SetConsoleTextAttribute(h, wOldColorAttrs);
        getch();
        exit(0);
    } // end of else

// employee log in screen
worker:
    for (int i = 1; i <= attempts; ++i)
    {
        system("cls");
        //	system("COLOR 05");
        gotoxy(5, 10);
        printf("\n\n\t\t\t\t*****************************************************************");
        printf("\n\t\t\t\t*\t\t\t  WELCOME USER\t\t\t\t*");
        printf("\n\t\t\t\t*****************************************************************");
        getch();

        printf("\n\n\t\t\t\t\t\tEnter any key to continue to login page. ");
        printf("\n\t\t\t\t-----------------------------------------------------------------");
        getch();

        printf("\n\n\t\t\t\t\t-----------------LOGIN PAGE-------------------");
        printf("\n\n\t\t\t\t\t\tEnter username: ");
        scanf("%d", &username);
        printf("\n\t\t\t\t\t\tEnter password: ");
        scanf("%s", &newpassword);
        printf("\n\t\t\t\t------------------------------------------------------------------");

        fseek(employeePtr, (username - 1) * sizeof(struct employee), SEEK_SET);
        fread(&worker, sizeof(struct employee), 1, employeePtr);

        if ((worker.IDnum != 0) && (strcmp(password, newpassword)) == 0)
        {
            SetConsoleTextAttribute(h, FOREGROUND_YELLOW | FOREGROUND_INTENSE_YELLOW); // changes colour of text to yellow
            printf("\n\t\t\t\t\t\t\t _________________");
            printf("\n\t\t\t\t\t\t\t|LOGIN SUCCESSFUL |");
            printf("\n\t\t\t\t\t\t\t|_________________|");
            SetConsoleTextAttribute(h, wOldColorAttrs);
            getch();
            return;
        } // end of if
        else
        {
            printf("\n\n\t\t\t\t\t\t  Access Denied.");
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY); // changes colour of text to red
            printf("\n\t\t\t\t\tIncorrect username or password.");
            SetConsoleTextAttribute(h, wOldColorAttrs); // sets the colour of text to the original colour
            printf("\n\t\t\t\t\t\t  Please try again.");
            getch();
        } // end of else
        if (i >= attempts)
        {
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("\n\n\t\t\tYou have reached the maximum number of attempts. Please try again later.");
            SetConsoleTextAttribute(h, wOldColorAttrs);
            exit(0);
        } // end of if
    } // end of for loop
    worker.IDnum = username;

// guest log in screen
guest:
    system("cls");
    printf("\n\n\t\t\t\t*****************************************************************");
    printf("\n\t\t\t\t*\t\t\t  WELCOME GUEST\t\t\t\t*");
    printf("\n\t\t\t\t*****************************************************************");
    getch();

    printf("\n\n\t\t\t\t\t\tEnter any key to continue to login page. ");
    printf("\n\t\t\t\t-----------------------------------------------------------------");
    getch();

    printf("\n\n\t\t\t\t\t-----------------LOGIN PAGE-------------------");
    printf("\n\t\t\t\t\t\tEnter password: ");
    scanf("%s", &Tempguestpwd);

    if ((strcmp(guestpwd, Tempguestpwd)) == 0)
    {
        printf("\n\t\t\t\t\t\t\t ________________");
        printf("\n\t\t\t\t\t\t\t|LOGIN SUCCESSFUL|");
        printf("\n\t\t\t\t\t\t\t|________________|");
        getch();
    } // end of if
    else
    {
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("\n\n\t\t\t\t\t\tYou are not authorized to login as a guest.");
        SetConsoleTextAttribute(h, wOldColorAttrs);
        getch();
        exit(0);
    } // end of else
} // end of login function

// beginning of function main
int main()
{
    int option;

    FILE *appointmentPtr;
    FILE *employeePtr;
    FILE *patientPtr;

    appointmentPtr = fopen("AppointmentFile.dat", "rb+");
    patientPtr = fopen("PatientFile.dat", "rb+");
    if ((employeePtr = fopen("EmployeeFile.dat", "rb+")) == NULL)
    {
        printf("\a\a\aFile could not be opened.");
    } // end of if
    else
    {
        welcomescreen();
        loginscreen(employeePtr);
        while ((option = menu()) != 15)
        {
            switch (option)
            {
            case 1:
                addPatient(patientPtr);
                break;

            case 2:
                deletePatient(patientPtr);
                break;

            case 3:
                updatePatient(patientPtr);
                break;

            case 4:
                searchPatient(patientPtr);
                break;

            case 5:
                viewALLPatient(patientPtr);
                break;

            case 6:
                createPatientTextFile(patientPtr);
                break;

            case 7:
                addEmployee(employeePtr);
                break;

            case 8:
                updateEmployee(employeePtr);
                break;

            case 9:
                deleteEmployee(employeePtr);
                break;

            case 10:
                searchEmployee(employeePtr);
                break;

            case 11:
                viewALLEmployee(employeePtr);
                break;

            case 12:
                createEmployeeTextFile(employeePtr);
                break;

            case 13:
                while ((option = appointmentMenu()) != 5)
                {
                    switch (option)
                    {
                    case 1:
                        addAppointment(appointmentPtr);
                        break;
                    case 2:
                        updateAppointment(appointmentPtr);
                        break;
                    case 3:
                        viewallappointment(appointmentPtr);
                        break;
                    case 4:
                        textfileappointment(appointmentPtr);
                        break;
                    default:
                        printf("\nInvalid Input");
                        break;
                    }
                }
                break;

            case 14:
                system("cls");
                printf("\n\t\t\t\t\t\tGood Bye! :)");
                printf("\n\t\t\t\t\tTHANK YOU FOR VISITING.");
                exit(0);

            default:
                printf("\nInvalid Input.");
                getch();
                break;
            } // end of switch
        } // end of while
        fclose(employeePtr);
        fclose(patientPtr);
    } // end of else
    return 0;
} // end of function main

int appointmentMenu()
{
    int appoint;

    system("cls");
    system("COLOR 03");
    printf("\n\t\t\t\t\t APPOINTMENTS");
    printf("\n\t\t\t++-++-++-++-++-++-++-++-++-++-++-++-++-++-++");
    printf("\n\t\t\t\t1 - Add or Create Appointment\n"
           "\t\t\t\t2 - Update Appointment\n"
           "\t\t\t\t3 - View All Appointments\n"
           "\t\t\t\t4 - Text File\n"
           "\t\t\t\t5 - Exit ");
    printf("\n\t\t\t++-++-++-++-++-++-++-++-++-++-++-++-++-++-++");
    printf("\n\t\t\t\t\tChoice: ==> ");
    scanf("%d", &appoint);
    return appoint;
}

// beginning of function menu
int menu()
{
    int option;
    title();
    system("COLOR F4");
    system("cls");

    printf("\n\t\t\t_________________________________________________________________________");
    printf("\n\t\t\t|\t\tWELCOME TO THE RUNAWAY BAY CLINIC \t\t\t|"
           "\n\t\t\t|_______________________________________________________________________|"
           "\n\t\t\t|\t\t\tPlease choose an option:    \t\t\t|"
           "\n\t\t\t|-----------------------------------------------------------------------|"
           "\n\t\t\t|\t\t\t\tPATIENTS           \t\t\t|"
           "\n\t\t\t|-----------------------------------------------------------------------|"
           "\n\t\t\t|\t\t\t1  - Add Patient \t\t\t\t|"
           "\n\t\t\t|\t\t\t2  - Delete Patient \t\t\t\t|"
           "\n\t\t\t|\t\t\t3  - Update Patient \t\t\t\t|"
           "\n\t\t\t|\t\t\t4  - Search Patient \t\t\t\t|"
           "\n\t\t\t|\t\t\t5  - View All Patients \t\t\t\t|"
           "\n\t\t\t|\t\t\t6  - Create Readable Patient File \t\t|"
           "\n\t\t\t|-----------------------------------------------------------------------|"
           "\n\t\t\t|\t\t\t\tEMPLOYEES          \t\t\t|"
           "\n\t\t\t|-----------------------------------------------------------------------|"
           "\n\t\t\t|\t\t\t7  - Add Employee \t\t\t\t|"
           "\n\t\t\t|\t\t\t8  - Update Employee \t\t\t\t|"
           "\n\t\t\t|\t\t\t9  - Delete Employee \t\t\t\t|"
           "\n\t\t\t|\t\t\t10 - Search Employee \t\t\t\t|"
           "\n\t\t\t|\t\t\t11 - View All Employee \t\t\t\t|"
           "\n\t\t\t|\t\t\t12 - Create Readable Employee File \t\t|"
           "\n\t\t\t|-----------------------------------------------------------------------|"
           "\n\t\t\t|\t\t\t13 - Appointment \t\t\t\t|"
           "\n\t\t\t|-----------------------------------------------------------------------|"
           "\n\t\t\t|\t\t\t14 - Exit         \t\t\t\t|"
           "\n\t\t\t|_______________________________________________________________________|");
    printf("\n\t\tPlease enter your choice of action here.");
    printf("\n\t\tChoice ? ==> ");
    scanf("%d", &option);

    return option;
} // end of function menu

// beginning of function addPatient
void addPatient(FILE *patientPtr)
{
    struct patient person = {0, 0, " ", " ", " ", " ", 0, " ", " ", " ", 0, " ", " ", 0.0, 0.0, " ", " ", 0, " ", 0, " ", " ", " ", " ", " ", 0, " ", " "};
    int TempdocNum;
    const char *Gender[] = {" ", "Female", "Male"};
    system("COLOR 03");

    title();
    printf("\n\t\t\t\t\t\tEnter any key to continue ");
    printf("\n\t\t\t---------------------------------------------------------------------");
    getch();
    printf("\n\n\t\t\t\t\t\tADD PATIENT RECORD");
    printf("\n\t\t\t\t----------------------------------------------");
    getch();
    printf("\n\nEnter Docket Number (for e.g. 100-300): ");
    scanf("%3d", &TempdocNum);

    fseek(patientPtr, (TempdocNum - 1) * sizeof(struct patient), SEEK_SET);
    fread(&person, sizeof(struct patient), 1, patientPtr);

    if (person.docNum != 0)
    {
        // sets test to the colour red
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("\n\a\a\aDocket number already exist.");
        SetConsoleTextAttribute(h, wOldColorAttrs);
        getch();
    } // end of if
    else
    {
        printf("\n---------PATIENT INFORMATION--------\n\n");
        printf("Enter First Name: ");
        scanf("%s", &person.fname);
        printf("Enter Middle Name: ");
        scanf("%s", &person.midname);
        printf("Enter Last Name: ");
        scanf("%s", &person.lname);
        gender();
        scanf("%d", &person.genderOption);
        printf("Enter Date of Birth (eg dd/mm/yyyy): ");
        scanf("%s", &person.dob);
        printf("Enter Age: ");
        scanf("%d", &person.age);
        printf("Enter Address (street name): ");
        scanf("%s", &person.address);
        addressParish();
        scanf("%d", &person.parish);
        printf("Enter Email Address: ");
        scanf("%s", &person.emailaddress);
        printf("Enter Telephone Number: ");
        scanf("%s", &person.telephone);
        printf("Enter reason for visit: ");
        scanf("%s", &person.reasonforvisit);
        printf("Enter prescription: ");
        scanf("%s", &person.prescription);
        printf("Enter cholesterol: ");
        scanf("%d", &person.cholesterol);
        printf("Enter Last Visit (eg dd/mm/yyyy): ");
        scanf("%s", &person.lastvisit);
        printf("Enter temperature: ");
        scanf("%d", &person.temperature);
        printf("Enter Height: ");
        scanf("%f", &person.height);
        printf("Enter Weight: ");
        scanf("%f", &person.weight);
        printf("Enter Blood Pressure: ");
        scanf("%s", &person.bp);
        printf("\n\n---------NEXT OF KIN INFORMATION--------\n");
        printf("Enter Next of Kin First Name: ");
        scanf("%s", &person.nextofkinfname);
        printf("Enter Next of Kin Last Name: ");
        scanf("%s", &person.nextofkinLname);
        printf("Enter Address (street name/district): ");
        scanf("%s", &person.nextofkinaddress);
        addressParish();
        scanf("%d", &person.nextofkinparish);
        printf("Enter Next of kin Telephone Number: ");
        scanf("%s", &person.nextofkintelephone);
        printf("Enter Relationship to Patient: ");
        scanf("%s", &person.relationship);
        // set text colour to green
        SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\n\n\t\t\t******************************************");
        printf("\n\t\t\t*\tRECORD SUCCESSFULLY ADDED \t *");
        printf("\n\t\t\t******************************************");
        SetConsoleTextAttribute(h, wOldColorAttrs);

        person.docNum = TempdocNum;

        getch();

        fseek(patientPtr, (TempdocNum - 1) * sizeof(struct patient), SEEK_SET);
        fwrite(&person, sizeof(struct patient), 1, patientPtr);
    } // end of else
} // end of function addPatient

// beginning of function updatePatient
void updatePatient(FILE *patientPtr)
{
    struct patient person = {0, 0, " ", " ", " ", " ", 0, " ", " ", " ", 0, " ", " ", 0.0, 0.0, " ", " ", 0, " ", 0, " ", " ", " ", " ", " ", 0, " ", " "};
    int TempdocNum;
    char sname[25];
    int updateOption;
    char TempTelephone[15];
    char newbp[8];
    char TempAddress[30];
    char lastVisit[8];
    float newWeight;
    float newHeight;
    char newReasonforvisit[80];
    int option;
    int TempTemperature;
    char newPrescription[100];
    char newComments[50];
    int newcholesterol;
    char fname[25];
    char relationship[20];
    system("cls");
    system("COLOR 02");

    title();
    printf("\n\t\t\t\t\t\tEnter any key to continue ");
    printf("\n\t\t\t---------------------------------------------------------------------");
    getch();
    printf("\n\n\t\t\t\t\t\tUPDATE PATIENT RECORD");
    printf("\n\t\t\t\t----------------------------------------------");
    getch();

    printf("\n\nEnter docket number to  update: ");
    scanf("%d", &TempdocNum);
    if (TempdocNum < 100)
    {
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
        puts("Docket Number caanot be less than 3 digits.");
        getch();
        SetConsoleTextAttribute(h, wOldColorAttrs);
    }
    else
    {
        fseek(patientPtr, (TempdocNum - 1) * sizeof(struct patient), SEEK_SET);
        fread(&person, sizeof(struct patient), 1, patientPtr);
        if (person.docNum == 0)
        {
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("\n\n\t\t\t\t\a\a\aDocket number not in use.");
            SetConsoleTextAttribute(h, wOldColorAttrs);
            getch();
        } // end of if
        else
        {
        updatePatient:
            while ((updateOption = updatePatientMenu()) != 13)
            {
                switch (updateOption)
                {
                // updating vitals
                case 1:
                    printf("\n\t\t\t\t----------------Displaying Old Record-----------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-15s%-15s%-20s%-15s%-15s", "Docket #", "First Name", "Surname", "Temperature", "Cholesterol", "Blood Pressure", "Weight", "Last Visit");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-15d%-15d%-20s%-15.2f%-15s", person.docNum, person.fname, person.lname, person.temperature, person.cholesterol, person.bp, person.weight, person.lastvisit);
                    SetConsoleTextAttribute(h, wOldColorAttrs);

                    printf("\n\nEnter new temperature: ");
                    scanf("%d", &TempTemperature);
                    person.temperature = TempTemperature;
                    printf("Enter new cholesterol: ");
                    scanf("%d", &newcholesterol);
                    person.cholesterol = newcholesterol;
                    printf("Enter new blood pressure: ");
                    scanf("%s", &newbp);
                    strcpy(person.bp, newbp);
                    printf("Enter new weight: ");
                    scanf("%f", &newWeight);
                    person.weight = newWeight;
                    printf("\nEnter date of visit (eg dd/mm/yyyy): ");
                    scanf("%s", &lastVisit);
                    strcpy(person.lastvisit, lastVisit);

                    fseek(patientPtr, (TempdocNum - 1) * sizeof(struct patient), SEEK_SET);
                    fwrite(&person, sizeof(struct patient), 1, patientPtr);

                    printf("\n\n\t\t\t\t----------------Displaying Updated Record---------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-15s%-15s%-20s%-15s%-15s", "Docket #", "First Name", "Surname", "Temperature", "Cholesterol", "Blood Pressure", "Weight", "Last Visit");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-15d%-15d%-20s%-15.2f%-15%", person.docNum, person.fname, person.lname, person.temperature, person.cholesterol, person.bp, person.weight, person.lastvisit);
                    SetConsoleTextAttribute(h, wOldColorAttrs);
                    getch();
                    break;

                // updating reason for visit and medical history
                case 2:
                    // print the info from file
                    printf("\n\t\t\t\t----------------Displaying Old Record-----------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-15s%-25s%-10s", "Docket #", "First Name", "Middle Name", "Surname", "Medical History", "Reason for visit");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-15s%-25s%-10s", person.docNum, person.fname, person.midname, person.lname, person.medicalHistory, person.reasonforvisit);
                    SetConsoleTextAttribute(h, wOldColorAttrs);

                    printf("\n\nEnter new reason for visit: ");
                    scanf("%s", &newReasonforvisit);

                    strcat(person.medicalHistory, person.reasonforvisit);
                    strcat(person.medicalHistory, "--");
                    strcpy(person.reasonforvisit, newReasonforvisit);

                    fseek(patientPtr, (TempdocNum - 1) * sizeof(struct patient), SEEK_SET);
                    fwrite(&person, sizeof(struct patient), 1, patientPtr);
                    // print the updated info from file
                    printf("\n\n\t\t\t\t----------------Displaying Updated Record---------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-15s%-25s%-10s", "Docket #", "First Name", "Middle Name", "Surname", "Medical History", "Reason for Visit");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-15s%-25s%-10s", person.docNum, person.fname, person.midname, person.lname, person.medicalHistory, person.reasonforvisit);
                    SetConsoleTextAttribute(h, wOldColorAttrs);
                    getch();
                    break;

                // adding and updating prescription
                case 3:
                    printf("\n\t\t\t\t----------------Displaying Old Record-----------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-15s%-25s%-10s", "Docket #", "First Name", "Middle Name", "Surname", "Prescription History", "Prescription");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-15s%-25s%-10s", person.docNum, person.fname, person.midname, person.lname, person.prescriptionHistory, person.prescription);
                    SetConsoleTextAttribute(h, wOldColorAttrs);

                    printf("\n\nEnter new prescription: ");
                    scanf("%s", &newPrescription);

                    strcat(person.prescriptionHistory, person.prescription);
                    strcat(person.prescriptionHistory, "--");
                    strcpy(person.prescription, newPrescription);

                    fseek(patientPtr, (TempdocNum - 1) * sizeof(struct patient), SEEK_SET);
                    fwrite(&person, sizeof(struct patient), 1, patientPtr);

                    printf("\n\n\t\t\t\t----------------Displaying Updated Record---------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-15s%-25s%-10s", "Docket #", "First Name", "Middle Name", "Surname", "Prescription History", "Prescription");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-15s%-25s%-10s", person.docNum, person.fname, person.midname, person.lname, person.prescriptionHistory, person.prescription);
                    SetConsoleTextAttribute(h, wOldColorAttrs);
                    getch();
                    break;

                // updating surname
                case 4:
                    // printf to print the info from the file
                    printf("\n\t\t\t\t----------------Displaying Old Record-----------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-15s%-25s%-10s", "Docket #", "First Name", "Middle Name", "Surname", "Medical History", "Last Visit");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-15s%-25s%-10s", person.docNum, person.fname, person.midname, person.lname, person.medicalHistory, person.lastvisit);
                    SetConsoleTextAttribute(h, wOldColorAttrs);

                    printf("\nEnter new surname: ");
                    scanf("%s", &sname);

                    strcat(person.lname, "-");
                    strcat(person.lname, sname);

                    fseek(patientPtr, (TempdocNum - 1) * sizeof(struct patient), SEEK_SET);
                    fwrite(&person, sizeof(struct patient), 1, patientPtr);
                    // printf to print the updated info from the file
                    printf("\n\n\t\t\t\t----------------Displaying Updated Record---------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-15s%-25s%-10s", "Docket #", "First Name", "Middle Name", "Surname", "Medical History", "Last Visit");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-15s%-25s%-10s", person.docNum, person.fname, person.midname, person.lname, person.medicalHistory, person.lastvisit);
                    SetConsoleTextAttribute(h, wOldColorAttrs);
                    getch();
                    break;

                // updating telephone number
                case 5:
                    printf("\n\t\t\t\t----------------Displaying Old Record-----------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-15s%-25s%-20s", "Docket #", "First Name", "Middle Name", "Surname", "Medical History", "Telephone #");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-15s%-25s%-20s", person.docNum, person.fname, person.midname, person.lname, person.medicalHistory, person.telephone);
                    SetConsoleTextAttribute(h, wOldColorAttrs);

                    printf("\nEnter new telephone number: ");
                    scanf("%s", &TempTelephone);

                    strcpy(person.telephone, TempTelephone);
                    // print info from the file
                    fseek(patientPtr, (TempdocNum - 1) * sizeof(struct patient), SEEK_SET);
                    fwrite(&person, sizeof(struct patient), 1, patientPtr);

                    printf("\n\n\t\t\t\t----------------Displaying Updated Record---------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-15s%-25s%-20s", "Docket #", "First Name", "Middle Name", "Surname", "Medical History", "Telephone #");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-15s%-25s%-20s", person.docNum, person.fname, person.midname, person.lname, person.medicalHistory, person.telephone);
                    SetConsoleTextAttribute(h, wOldColorAttrs);
                    getch();
                    break;

                // updating address
                case 6:
                    printf("\n\t\t\t\t----------------Displaying Old Record-----------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-15s%-25s%-20s", "Docket #", "First Name", "Middle Name", "Surname", "Medical History", "Address");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-15s%-25s%-20s", person.docNum, person.fname, person.midname, person.lname, person.medicalHistory, person.address);
                    SetConsoleTextAttribute(h, wOldColorAttrs);

                    printf("\nEnter new address: ");
                    scanf("%s", &TempAddress);

                    strcpy(person.address, TempAddress);

                    fseek(patientPtr, (TempdocNum - 1) * sizeof(struct patient), SEEK_SET);
                    fwrite(&person, sizeof(struct patient), 1, patientPtr);
                    // print info to screen
                    printf("\n\n\t\t\t\t----------------Displaying Updated Record---------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-15s%-25s%-20s", "Docket #", "First Name", "Middle Name", "Surname", "Medical History", "Address");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-15s%-25s%-20s", person.docNum, person.fname, person.midname, person.lname, person.medicalHistory, person.address);
                    SetConsoleTextAttribute(h, wOldColorAttrs);
                    getch();
                    break;

                // updating patient height
                case 7:
                    printf("\n\t\t\t\t----------------Displaying Old Record-----------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-15s%-25s%-10s", "Docket #", "First Name", "Middle Name", "Surname", "Medical History", "Height");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-15s%-25s%-10.2f", person.docNum, person.fname, person.midname, person.lname, person.medicalHistory, person.height);
                    SetConsoleTextAttribute(h, wOldColorAttrs);

                    printf("\nEnter new height: ");
                    scanf("%f", &newHeight);

                    person.height = newHeight;

                    fseek(patientPtr, (TempdocNum - 1) * sizeof(struct patient), SEEK_SET);
                    fwrite(&person, sizeof(struct patient), 1, patientPtr);
                    // print updated info
                    printf("\n\n\t\t\t\t----------------Displaying Updated Record---------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-15s%-25s%-10s", "Docket #", "First Name", "Middle Name", "Surname", "Medical History", "Height");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-15s%-25s%-10.2f", person.docNum, person.fname, person.midname, person.lname, person.medicalHistory, person.height);
                    SetConsoleTextAttribute(h, wOldColorAttrs);
                    getch();
                    break;

                // updating the next of kin
                case 8:
                    printf("\n\t\t\t\t----------------Displaying Old Record-----------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-30s%-30s%-30s%-30s", "Docket Number", "First Name", "Surname", "Next of Kin First Name", "Next of Kin Surname", "Next of Kin Telephone#", "Next of Kin Address");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-30s%-30s%-30s%-30s", person.docNum, person.fname, person.lname, person.nextofkinfname, person.nextofkinLname,
                           person.nextofkintelephone, person.nextofkinaddress);
                    SetConsoleTextAttribute(h, wOldColorAttrs);

                    printf("\nEnter New Next of kin First Name: ");
                    scanf("%s", &fname);
                    printf("Enter Next of Kin Last Name: ");
                    scanf("%s", &sname);
                    printf("Enter Address: ");
                    scanf("%s", &TempAddress);
                    printf("Enter Next of kin Telephone Number: ");
                    scanf("%s", &TempTelephone);
                    printf("Enter Relationship to Patient: ");
                    scanf("%s", &relationship);

                    strcpy(person.nextofkinfname, fname);
                    strcpy(person.nextofkinLname, sname);
                    strcpy(person.nextofkinaddress, TempAddress);
                    strcpy(person.nextofkintelephone, TempTelephone);
                    strcpy(person.relationship, relationship);

                    fseek(patientPtr, (TempdocNum - 1) * sizeof(struct patient), SEEK_SET);
                    fwrite(&person, sizeof(struct patient), 1, patientPtr);

                    printf("\n\n\t\t\t\t----------------Displaying Updated Record---------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-30s%-30s%-30s%-30s", "Docket Number", "First Name", "Surname", "Next of Kin First Name", "Next of Kin Surname", "Next of Kin Telephone#", "Next of Kin Address");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-30s%-30s%-30s%-30s", person.docNum, person.fname, person.lname, person.nextofkinfname, person.nextofkinLname,
                           person.nextofkintelephone, person.nextofkinaddress);
                    SetConsoleTextAttribute(h, wOldColorAttrs);
                    getch();
                    break;

                // updating the information of the current next of kin
                case 9:
                    printf("\n\t\t\t\t----------------Displaying Old Record-----------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-30s%-30s%-30s%-30s", "Docket Number", "First Name", "Surname", "Next of Kin First Name", "Next of Kin Surname", "Next of Kin Telephone#", "Next of Kin Address");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-30s%-30s%-30s%-30s", person.docNum, person.fname, person.lname, person.nextofkinfname, person.nextofkinLname,
                           person.nextofkintelephone, person.nextofkinaddress);
                    SetConsoleTextAttribute(h, wOldColorAttrs);

                    printf("\nSelect the option to update for next of kin: "
                           "\n1 - Telephone number"
                           "\n2 - Address:--> ");
                    scanf("%d", &option);
                    if (option == 1)
                    {
                        printf("\nEnter new telephone number: ");
                        scanf("%s", &TempTelephone);

                        strcpy(person.nextofkintelephone, TempTelephone);

                        fseek(patientPtr, (TempdocNum - 1) * sizeof(struct patient), SEEK_SET);
                        fwrite(&person, sizeof(struct patient), 1, patientPtr);

                        printf("\n\n\t\t\t\t----------------Displaying Updated Record---------------");
                        SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        printf("\n%-15s%-15s%-15s%-30s%-30s%-30s%-30s", "Docket Number", "First Name", "Surname", "Next of Kin First Name", "Next of Kin Surname", "Next of Kin Telephone#", "Next of Kin Address");
                        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        printf("\n%-15d%-15s%-15s%-30s%-30s%-30s%-30s", person.docNum, person.fname, person.lname, person.nextofkinfname, person.nextofkinLname,
                               person.nextofkintelephone, person.nextofkinaddress);
                        SetConsoleTextAttribute(h, wOldColorAttrs);
                        getch();
                        break;
                    } // end of if
                    else if (option == 2)
                    {
                        printf("\nEnter address: ");
                        scanf("%s", &TempAddress);

                        strcpy(person.nextofkinaddress, TempAddress);
                        fseek(patientPtr, (TempdocNum - 1) * sizeof(struct patient), SEEK_SET);
                        fwrite(&person, sizeof(struct patient), 1, patientPtr);

                        printf("\n\n\t\t\t\t----------------Displaying Updated Record---------------");
                        SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        printf("\n%-15s%-15s%-15s%-30s%-30s%-30s%-30s", "Docket Number", "First Name", "Surname", "Next of Kin First Name", "Next of Kin Surname", "Next of Kin Telephone#", "Next of Kin Address");
                        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        printf("\n%-15d%-15s%-15s%-30s%-30s%-30s%-30s", person.docNum, person.fname, person.lname, person.nextofkinfname, person.nextofkinLname,
                               person.nextofkintelephone, person.nextofkinaddress);
                        SetConsoleTextAttribute(h, wOldColorAttrs);
                        getch();
                        break;
                    } // end of else if
                    else
                    {
                        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        printf("\n\a\a\aIncorrect Input.");
                        SetConsoleTextAttribute(h, wOldColorAttrs);
                        getch();
                    } // end of else
                    break;
                // updating comments about the patient
                case 10:
                    printf("\n\t\t\t\t----------------Displaying Old Record-----------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-30s", "Docket Number", "First Name", "Surname", "Comments");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-30s", person.docNum, person.fname, person.lname, person.comments);
                    SetConsoleTextAttribute(h, wOldColorAttrs);

                    printf("\nEnter new comments: ");
                    scanf("%s", &newComments);

                    strcat(person.comments, newComments);

                    fseek(patientPtr, (TempdocNum - 1) * sizeof(struct patient), SEEK_SET);
                    fwrite(&person, sizeof(struct patient), 1, patientPtr);

                    printf("\n\n\t\t\t\t----------------Displaying Updated Record---------------");
                    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\n%-15s%-15s%-15s%-30s", "Docket Number", "First Name", "Surname", "Comments");
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n%-15d%-15s%-15s%-30s", person.docNum, person.fname, person.lname, person.comments);
                    SetConsoleTextAttribute(h, wOldColorAttrs);
                    getch();
                    break;
                // exiting updatePatient
                case 11:
                    printf("Are you sure you want to return to the main menu Y/N? ");
                    scanf(" %c", &ans);
                    if (ans == 'Y' || ans == 'y')
                    {
                        puts("GOODBYE");
                        getch();
                        return;
                    } // end of if
                    else if (ans == 'N' || ans == 'n')
                    {
                        goto updatePatient;
                    } // end of else if
                    else
                    {
                        printf("Incorrect Input. Please enter Y or N");
                        getch();
                        goto updatePatient;
                    } // end of else
                    break;
                default:
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\nINCORRECT INPUT.");
                    SetConsoleTextAttribute(h, wOldColorAttrs);
                    break;
                } // end of switch
            } // end of while
        } // end of else
    } // end of else
} // end of function updatePatient

// beginning of function deletePatient
void deletePatient(FILE *patientPtr)
{
    // declaration
    struct patient person = {0, 0, " ", " ", " ", " ", 0, " ", " ", " ", 0, " ", " ", 0.0, 0.0, " ", " ", 0, " ", 0, " ", " ", " ", " ", " ", 0, " ", " "};
    struct patient blankperson = {0, 0, " ", " ", " ", " ", 0, " ", " ", " ", 0, " ", " ", 0.0, 0.0, " ", " ", 0, " ", 0, " ", " ", " ", " ", " ", 0, " ", " "};
    int TempdocNum;
    char deletePatient;

    system("COLOR 05");
    title();
    printf("\n\t\t\t\t\t\tEnter any key to continue ");
    printf("\n\t\t\t---------------------------------------------------------------------");
    getch();
    printf("\n\n\t\t\t\t\t\tDELETE PATIENT RECORD");
    printf("\n\t\t\t\t----------------------------------------------");
    getch();
    printf("\nEnter docket number you wish to delete: ");
    scanf("%d", &TempdocNum);
    if (TempdocNum < 100)
    {
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("\n\n\t\t\t\tDocket Number cannot contain less than 3 digits.");
        SetConsoleTextAttribute(h, wOldColorAttrs);
        getch();
    }
    else
    {

        fseek(patientPtr, (TempdocNum - 1) * sizeof(struct patient), SEEK_SET);
        fread(&person, sizeof(struct patient), 1, patientPtr);

        if (person.docNum == 0)
        {
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("\n\a\a\aDocket number does not exist.");
            SetConsoleTextAttribute(h, wOldColorAttrs);
            getch();
        } // end of if
        else
        {
            printf("\n%d %s %s %s", person.docNum, person.fname, person.lname, person.reasonforvisit);
            printf("\n\nAre you sure you want to delete this patient? Please enter (Y/N)? ");
            scanf(" %c", &deletePatient);
            if (deletePatient == 'Y' || deletePatient == 'y')
            {
                fseek(patientPtr, (TempdocNum - 1) * sizeof(struct patient), SEEK_SET);
                fwrite(&blankperson, sizeof(struct patient), 1, patientPtr);
                // set text to green
                SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("\n\t\t\t\t-----------RECORD SUCCESSFULLY DELETED----------");
                SetConsoleTextAttribute(h, wOldColorAttrs);
            } // end of if
            else if (deletePatient == 'N' || deletePatient == 'n')
            {
                printf("\n\t\tCANCELLED");
            } // end of else if
            else
            {
                // set text colour to red
                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("\n\t\tINVALID INPUT. Please enter either Y or N.");
                SetConsoleTextAttribute(h, wOldColorAttrs);
            } // end of else
            getch();
        } // end of if
    }
} // end of function deletePatient

// beginning of function searchPtaient
void searchPatient(FILE *patientPtr)
{
    struct patient person = {0, 0, " ", " ", " ", " ", 0, " ", " ", " ", 0, " ", " ", 0.0, 0.0, " ", " ", 0, " ", 0, " ", " ", " ", " ", " ", 0, " ", " "};
    int selection;
    int TempdocNum;
    char fname[25];
    char lname[25];
    system("COLOR 06");
    title();
    printf("\n\t\t\t\t\t\tEnter any key to continue ");
    printf("\n\t\t\t---------------------------------------------------------------------");
    getch();
    printf("\n\n\t\t\t\t\t\tSEARCH PATIENT RECORD");
    printf("\n\t\t\t\t----------------------------------------------");
    getch();
patientSearch:
    printf("\n\n\t\tSelect Search criteria"
           "\n\t\t\t\t1 - Search by docket number"
           "\n\t\t\t\t2 - Search by Name"
           "\n\t\t\t\t3 - Exit: --> ");
    scanf("%d", &selection);

    switch (selection)
    {
    // case 1 to search for a patient by their ID number
    case 1:
        printf("\nEnter the docket number you wish to search for: ");
        scanf("%d", &TempdocNum);
        if (TempdocNum < 100)
        {
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
            puts("Docket Number cannot be less than 3 digits.");
            SetConsoleTextAttribute(h, wOldColorAttrs);
            getch();
        }
        else
        {
            fseek(patientPtr, (TempdocNum - 1) * sizeof(struct patient), SEEK_SET);
            fread(&person, sizeof(struct patient), 1, patientPtr);
            if (person.docNum == 0)
            {
                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                puts("\n\t\t\a\a\aThis record could not be found.");
                SetConsoleTextAttribute(h, wOldColorAttrs);
                getch();
            } // end of if
            else
            {
                SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("\n\t\t%-15s%-15s%-15s%-25s%-15s", "Docket #", "First Name", "Last Name", "Prescription History", "Medical History");
                printf("\n\t\t%-15d%-15s%-15s%-25s%-15s", person.docNum, person.fname, person.lname, person.prescriptionHistory, person.medicalHistory);
                SetConsoleTextAttribute(h, wOldColorAttrs);
                getch();
            } // end of else
        } // end of else
        break;
    // case 2 search patient by first name and last name
    case 2:
        printf("\nEnter the name of the patient you wish to find (first name followed by surname): ");
        scanf("%s%s", &fname, &lname);

        for (;;)
        {
            fread(&person, sizeof(struct patient), 1, patientPtr);
            if (feof(patientPtr))
            {
                // set text colour to red
                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("\n\t\t\a\a\aPatient record not found.");
                SetConsoleTextAttribute(h, wOldColorAttrs);
                getch();
                break;
            } // end of if
            if ((strcmpi(person.fname, fname) == 0) && (strcmpi(person.lname, lname) == 0))
            {
                printf("\n\t\t%-15s%-15s%-15s%-25s%-15s", "Docket #", "First Name", "Last Name", "Prescription History", "Medical History");
                printf("\n\t\t%-15d%-15s%-15s%-25s%-15s", person.docNum, person.fname, person.lname, person.prescriptionHistory, person.medicalHistory);
                getch();
                break;
            } // end of if
        } // end of for
        break;
    case 3:
        printf("Are you sure you want to return to the main menu (Y/N)? ");
        scanf(" %c", &ans);
        if (ans == 'Y' || ans == 'y')
        {
            puts("GOODBYE");
            getch();
            return;
        } // end of if
        else if (ans == 'N' || ans == 'n')
        {
            goto patientSearch;
        } // end of else if
        else
        {
            printf("\n\t\t\tINCORRECT INPUT. Please enter Y or N.");
            getch();
            goto patientSearch;
        } // end of else
        break;
    default:
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("\n\t\t\tINCORRECT INPUT");
        SetConsoleTextAttribute(h, wOldColorAttrs);
        break;
    } // end of switch
} // end of function searchPatient

// beginning of function viewPatients
void viewALLPatient(FILE *patientPtr)
{
    struct patient person = {0, 0, " ", " ", " ", " ", 0, " ", " ", " ", 0, " ", " ", 0.0, 0.0, " ", " ", 0, " ", 0, " ", " ", " ", " ", " ", 0, " ", " "};
    int optionView;
    char date[8];
    const char *Gender[] = {" ", "Female", "Male"};

    system("COLOR 0E");
    title();

    printf("\n\t\t\t\t\t\tEnter any key to continue ");
    printf("\n\t\t\t---------------------------------------------------------------------");
    getch();
    printf("\n\n\t\t\t\t\t\tVIEW ALL PATIENT RECORD");
    printf("\n\t\t\t\t----------------------------------------------");
    getch();

viewPatients:
    printf("\n\t\t\tEnter view option"
           "\n\t\t\t1 - View all patients"
           "\n\t\t\t2 - View patients from  a specific date (dd/mm/yyyy)"
           "\n\t\t\t3 - View all patients with the same type of illness"
           "\n\t\t\t4 - Exit:--> ");
    scanf("%d", &optionView);

    switch (optionView)
    {
    // case 1 view all patient records within the file
    case 1:
        printf("\n\t\t\t\t----------------PATIENT RECORDS--------------");
        printf("\n\t_________________________________________________________________________________________________");
        printf("\n\t|%-15s|%-15s|%-15s|%-30s |%-15s|", "Docket #", "First Name", "Surname", "Medical History", "Gender");
        printf("\n\t|---------------|---------------|---------------|-------------------------------|---------------|");
        while (!feof(patientPtr))
        {
            fread(&person, sizeof(struct patient), 1, patientPtr);
            if (feof(patientPtr))
            {
                printf("\n\t|\t\t\t\a\a\aEND OF RECORDS\t\t\t\t\t\t\t\t|");
                printf("\n\t|_______________________________________________________________________________________________|");
                getch();
                break;
            } // end of if
            if (person.docNum != 0)
            {
                printf("\n\t|%-15d|%-15s|%-15s|%-30s |%-15s|", person.docNum, person.fname, person.lname, person.medicalHistory, Gender[person.genderOption]);
                printf("\n\t|---------------|---------------|---------------|-------------------------------|---------------|");
                getch();
            } // end of if
        } // end of while
        getch();
        break;

    // case 2 view all patients within the file that visited on a specific day
    case 2:
        printf("\nEnter the patient on a specific date (eg dd/mm/yyyy): ");
        scanf("%s", &date);

        printf("\nThe patients that visited on %s include:", date);
        printf("\n\t_________________________________________________________________________________________________");
        printf("\n\t|%-15s|%-15s|%-15s|%-30s |%-15s|", "Docket #", "First Name", "Surname", "Medical History", "Last Visit");
        printf("\n\t|---------------|---------------|---------------|-------------------------------|---------------|");
        for (;;)
        {
            fread(&person, sizeof(struct patient), 1, patientPtr);
            if (feof(patientPtr))
            {
                printf("\n\t|\t\t\t\a\a\aEND OF RECORDS\t\t\t\t\t\t\t\t|");
                printf("\n\t|_______________________________________________________________________________________________|");
                getch();
                break;
            } // end of if
            if (strcmpi(person.lastvisit, date) == 0)
            {
                printf("\n\t|%-15d|%-15s|%-15s|%-30s |%-15s|", person.docNum, person.fname, person.lname, person.medicalHistory, person.lastvisit);
                printf("\n\t|---------------|---------------|---------------|-------------------------------|---------------|");
                getch();
            } // end of if
        } // end of for
        break;

    // case 3 to view all the patients with similar reason for visit
    case 3:
        char reasonforvisit[80];
        printf("\nEnter type of illness you wish to see: ");
        scanf("%s", &reasonforvisit);

        printf("\n%s patients include: ", reasonforvisit);
        printf("\n\t_________________________________________________________________________________________________________");
        printf("\n\t|%-15s|%-15s|%-15s|%-30s |%-23s|", "Docket #", "First Name", "Surname", "Medical History", "Reason for Visit");
        printf("\n\t|---------------|---------------|---------------|-------------------------------|-----------------------|");
        for (;;)
        {
            fread(&person, sizeof(struct patient), 1, patientPtr);
            if (feof(patientPtr))
            {
                printf("\n\t|\t\t\t\a\a\aEND OF RECORDS\t\t\t\t\t\t\t\t\t|");
                printf("\n\t|_______________________________________________________________________________________________________|");
                getch();
                break;
            } // end of if
            if ((strcmpi(person.reasonforvisit, reasonforvisit)) == 0)
            {
                printf("\n\t|%-15d|%-15s|%-15s|%-30s |%-23s|", person.docNum, person.fname, person.lname, person.medicalHistory, person.reasonforvisit);
                printf("\n\t|---------------|---------------|---------------|-------------------------------|-----------------------|");
                getch();
            } // end of if
        } // end of for
        break;
    case 4:
        printf("Are you sure you want to return to the main menu (Y/N)? ");
        scanf(" %c", &ans);
        if (ans == 'Y' || ans == 'y')
        {
            puts("GOODBYE");
            getch();
            return;
        } // end of if
        else if (ans == 'N' || ans == 'n')
        {
            goto viewPatients;
        } // end of else if
        else
        {
            printf("\n\t\t\tINCORRECT INPUT. Please enter Y or N.");
            getch();
            goto viewPatients;
        } // end of else
        break;
    default:
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("\n\t\t\tINCORRECT INPUT");
        SetConsoleTextAttribute(h, wOldColorAttrs);
        break;
    } // end of switch
} // end of function viewPatients

// beginning of function createPateint textFile
void createPatientTextFile(FILE *readpatient)
{
    struct patient person = {0, 0, " ", " ", " ", " ", 0, " ", " ", " ", 0, " ", " ", 0.0, 0.0, " ", " ", 0, " ", 0, " ", " ", " ", " ", " ", 0, " ", " "};
    const char *Gender[] = {"", "Female", "Male"};
    const char *parish[] = {"", "St. Ann", "Trelawny", "St. Mary", "St. James", "Manchester", "St. Cathrine", "St. Elizabeth", "St. Thomas", "Hanover", "Westmoreland", "Portland", "Clarendon", " Kingston", "St. Andrew"};

    FILE *writepatient;

    if ((writepatient = fopen("Patient.txt", "w+")) == NULL)
    {
        puts("\a\a\aFile could not be opened.");
        getch();
    } // end of if
    else
    {
        rewind(readpatient);
        fprintf(writepatient, "\n\t\t\t\t\t\tRUNAWAY BAY HEALTH CENTER PATIENT FILES");
        while (!feof(readpatient))
        {

            fread(&person, sizeof(struct patient), 1, readpatient);
            if (person.docNum != 0)
            {

                fprintf(writepatient, "\n\t\t\t\t-------------------------------------------------------------------------------------------");
                fprintf(writepatient, "\n\t\t\t\t\t\t\tPATIENT INFORMATION");
                fprintf(writepatient, "\n\t\t\t\t-------------------------------------------------------------------------------------------");
                fprintf(writepatient, "\n\t\t\t\t\tDocket Number:  \t %d", person.docNum);
                fprintf(writepatient, "\n\t\t\t\t\tName: \t\t\t %-15s%-15s%-15s", person.fname, person.midname, person.lname);
                fprintf(writepatient, "\n\t\t\t\t\tDate of Birth: \t\t %s", person.dob);
                fprintf(writepatient, "\n\t\t\t\t\tAge: \t\t\t %d", person.age);
                fprintf(writepatient, "\n\t\t\t\t\tGender: \t\t %s", Gender[person.genderOption]);
                fprintf(writepatient, "\n\t\t\t\t\tHeight: \t\t %.2f", person.height);
                fprintf(writepatient, "\n\t\t\t\t\tWeight: \t\t %.2f", person.weight);
                fprintf(writepatient, "\n\t\t\t\t\tDate of last visit: \t %s", person.lastvisit);
                fprintf(writepatient, "\n\t\t\t\t\tAddress: \t\t %s, %s", person.address, parish[person.parish]);
                fprintf(writepatient, "\n\t\t\t\t\tTelephoneNumber: \t %s", person.telephone);
                fprintf(writepatient, "\n\t\t\t\t\tEmail Address: \t\t %s", person.emailaddress);
                fprintf(writepatient, "\n\t\t\t\t-------------------------------------------------------------------------------------------");
                fprintf(writepatient, "\n\t\t\t\t\t\t\tMEDICAL INFORMATION");
                fprintf(writepatient, "\n\t\t\t\t-------------------------------------------------------------------------------------------");
                fprintf(writepatient, "\n\t\t\t\t\tReason for visit: \t %s", person.reasonforvisit);
                fprintf(writepatient, "\n\t\t\t\t\tMedical History: \t %s", person.medicalHistory);
                fprintf(writepatient, "\n\t\t\t\t\tBlood Pressure: \t %s", person.bp);
                fprintf(writepatient, "\n\t\t\t\t\tTemperature: \t\t %d", person.temperature);
                fprintf(writepatient, "\n\t\t\t\t\tPrescription: \t\t %s", person.prescription);
                fprintf(writepatient, "\n\t\t\t\t\tPrescription History: \t %s", person.prescriptionHistory);
                fprintf(writepatient, "\n\t\t\t\t\tCholesterol: \t\t %d", person.cholesterol);
                fprintf(writepatient, "\n\t\t\t\t\tComments: \t\t %s", person.comments);
                fprintf(writepatient, "\n\t\t\t\t-------------------------------------------------------------------------------------------");
                fprintf(writepatient, "\n\t\t\t\t\t\t\tNEXT OF KIN");
                fprintf(writepatient, "\n\t\t\t\t-------------------------------------------------------------------------------------------");
                fprintf(writepatient, "\n\t\t\t\t\tName: \t\t\t %-15s%-15s", person.nextofkinfname, person.nextofkinLname);
                fprintf(writepatient, "\n\t\t\t\t\tAddress: \t\t %s, %s", person.nextofkinaddress, parish[person.nextofkinparish]);
                fprintf(writepatient, "\n\t\t\t\t\tTelephone Number: \t %s", person.nextofkintelephone);
                fprintf(writepatient, "\n\t\t\t\t\tRelationship to Patient: %s", person.relationship);
                fprintf(writepatient, "\n\t\t\t\t-------------------------------------------------------------------------------------------");
            } // end of if
            fread(&person, sizeof(struct patient), 1, readpatient);
        } // end of while
        fclose(writepatient);
    } // end of else
} // end of function createPatientTextFile

// beginning of function addEmployee
void addEmployee(FILE *employeePtr)
{
    struct employee worker = {0, 0, 0, " ", " ", " ", " ", " ", " ", " ", " ", " ", " "};
    // declaration
    int TempIDnum;
    system("COLOR 03");
    title();
    printf("\n\t\t\t\t\t\tEnter any key to continue ");
    printf("\n\t\t\t---------------------------------------------------------------------");
    getch();
    printf("\n\n\t\t\t\t\t\tADD EMPLOYEE RECORD");
    printf("\n\t\t\t\t----------------------------------------------");
    getch();
    printf("\nEnter employee ID Number (for e.g. 1000): ");
    scanf("%4d", &TempIDnum);

    fseek(employeePtr, (TempIDnum - 1) * sizeof(struct employee), SEEK_SET);
    fread(&worker, sizeof(struct employee), 1, employeePtr);

    if (worker.IDnum != 0)
    {
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("\n\a\a\aID number already used.");
        SetConsoleTextAttribute(h, wOldColorAttrs);
        getch();
    } // end of if
    else
    {
        printf("Enter First Name: ");
        scanf("%s", &worker.fname);
        printf("Enter Middle Name: ");
        scanf("%s", &worker.mname);
        printf("Enter Last Name: ");
        scanf("%s", &worker.sname);
        gender();
        scanf("%d", &worker.gender);
        printf("Enter Date of Birth: ");
        scanf("%s", &worker.dob);
        printf("Enter Taxpayer Registration Number: ");
        scanf("%s", &worker.TRN);
        printf("Enter Type of employee (Nurse or doctor): ");
        scanf("%s", &worker.type);
        printf("Enter Telephone number: ");
        scanf("%s", &worker.telephone);
        printf("Enter email address: ");
        scanf("%s", &worker.emailaddress);
        printf("Enter address (street): ");
        scanf("%s", &worker.address);
        addressParish();
        scanf("%d", &worker.parish);
        printf("Enter NIS number: ");
        scanf("%s", &worker.NIS);
        printf("Enter position: ");
        scanf("%s", &worker.position);

        // set text colour to green
        SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\n\n\t\t\t******************************************");
        printf("\n\t\t\t*\tRECORD SUCCESSFULLY ADDED \t *");
        printf("\n\t\t\t******************************************");
        SetConsoleTextAttribute(h, wOldColorAttrs);
        getch();

        worker.IDnum = TempIDnum;

        fseek(employeePtr, (TempIDnum - 1) * sizeof(struct employee), SEEK_SET);
        fwrite(&worker, sizeof(struct employee), 1, employeePtr);
    } // end of else
} // end of function addEmployee

// beginning of function updateEmployee
void updateEmployee(FILE *employeePtr)
{
    struct employee worker = {0, 0, 0, " ", " ", " ", " ", " ", " ", " ", " ", " ", " "};
    int TempIDnum;
    int updateOption;
    char sname[25];
    char TempTelephone[15];
    char newAddress[30];
    system("COLOR 02");
    title();
    printf("\n\t\t\t\t\t\tEnter any key to continue ");
    printf("\n\t\t\t---------------------------------------------------------------------");
    getch();
    printf("\n\n\t\t\t\t\t\tUPDATE EMPLOYEE RECORD");
    printf("\n\t\t\t\t----------------------------------------------");
    getch();
    printf("\nEnter employee ID number to update: ");
    scanf("%d", &TempIDnum);
    if (TempIDnum < 1000)
    {
        printf("ID# cannot be less than 4 digits");
    } // end of if
    else
    {

        fseek(employeePtr, (TempIDnum - 1) * sizeof(struct employee), SEEK_SET);
        fread(&worker, sizeof(struct employee), 1, employeePtr);

        if (worker.IDnum == 0)
        {
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("\n\a\a\aID number does not contain any information.");
            SetConsoleTextAttribute(h, wOldColorAttrs);
            getch();
        } // end of if
        else
        {
        updateEmployee:
            while ((updateOption = updateEmployeeMenu()) != 5)
            {
                switch (updateOption)
                {
                // updating employee surname
                case 1:
                    printf("\n%-6s%-15s%-15s%-15s%-15s", "ID #", "First Name", "Middle Name", "Surname", "Type");
                    printf("\n%-6d%-15s%-15s%-15s%-15s", worker.IDnum, worker.fname, worker.mname, worker.sname, worker.type);

                    printf("\nEnter updated surname: ");
                    scanf("%s", &sname);
                    strcat(worker.sname, sname);

                    fseek(employeePtr, (TempIDnum - 1) * sizeof(struct employee), SEEK_SET);
                    fwrite(&worker, sizeof(struct employee), 1, employeePtr);

                    printf("\n%-6s%-15s%-15s%-15s%-15s", "ID #", "First Name", "Middle Name", "Surname", "Type");
                    printf("\n%-6d%-15s%-15s%-15s%-15s", worker.IDnum, worker.fname, worker.mname, worker.sname, worker.type);

                    getch();
                    break;

                // updating employee telephone
                case 2:
                    printf("\n%-6s%-15s%-15s%-15s%-15s%-15s", "ID #", "First Name", "Middle Name", "Surname", "Type", "Telephone #");
                    printf("\n%-6d%-15s%-15s%-15s%-15s%-15s", worker.IDnum, worker.fname, worker.mname, worker.sname, worker.type, worker.telephone);

                    printf("\nEnter new telephone number: ");
                    scanf("%s", &TempTelephone);

                    strcpy(worker.telephone, TempTelephone);

                    fseek(employeePtr, (TempIDnum - 1) * sizeof(struct employee), SEEK_SET);
                    fwrite(&worker, sizeof(struct employee), 1, employeePtr);

                    printf("\n%-6s%-15s%-15s%-15s%-15s%-15s", "ID #", "First Name", "Middle Name", "Surname", "Type", "Telephone #");
                    printf("\n%-6d%-15s%-15s%-15s%-15s%-15s", worker.IDnum, worker.fname, worker.mname, worker.sname, worker.type, worker.telephone);

                    getch();
                    break;

                // updating employee address
                case 3:
                    printf("\n%-6s%-15s%-15s%-15s%-15s%-15s", "ID #", "First Name", "Middle Name", "Surname", "Type", "Address");
                    printf("\n%-6d%-15s%-15s%-15s%-15s%-15s", worker.IDnum, worker.fname, worker.mname, worker.sname, worker.type, worker.address);

                    printf("\nEnter new address: ");
                    scanf("%s", &newAddress);

                    strcpy(worker.address, newAddress);

                    fseek(employeePtr, (TempIDnum - 1) * sizeof(struct employee), SEEK_SET);
                    fwrite(&worker, sizeof(struct employee), 1, employeePtr);

                    printf("\n%-6s%-15s%-15s%-15s%-15s%-15s", "ID #", "First Name", "Middle Name", "Surname", "Type", "Address");
                    printf("\n%-6d%-15s%-15s%-15s%-15s%-15s", worker.IDnum, worker.fname, worker.mname, worker.sname, worker.type, worker.address);

                    getch();
                    break;
                // exiting search Employee
                case 4:
                    printf("Are you sure you want to return to the main menu Y/N? ");
                    scanf(" %c", &ans);
                    if (ans == 'Y' || ans == 'y')
                    {
                        puts("\nGOODBYE");
                        getch();
                        return;
                    } // end of if
                    else if (ans == 'N' || ans == 'n')
                    {
                        goto updateEmployee;
                    } // end of else if
                    else
                    {
                        printf("Incorrect Option. Please enter Y or N.");
                        getch();
                        goto updateEmployee;
                    } // end of else
                default:
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\nINVALID CHOICE.");
                    SetConsoleTextAttribute(h, wOldColorAttrs);
                    break;
                } // end of switch
            } // end of while
        } // end of else
    } // end of else
} // end of function update employee

// beginning of function deleteEmployee
void deleteEmployee(FILE *employee)
{
    struct employee worker = {0, 0, 0, " ", " ", " ", " ", " ", " ", " ", " ", " ", " "};
    struct employee blankworker = {0, 0, 0, " ", " ", " ", " ", " ", " ", " ", " ", " ", " "};
    int TempIDnum;
    char deleteEmployee;
    system("COLOR 05");
    title();

    printf("\n\t\t\t\t\t\tEnter any key to continue ");
    printf("\n\t\t\t---------------------------------------------------------------------");
    getch();
    printf("\n\n\t\t\t\t\t\tDELETE EMPLOYEE RECORD");
    printf("\n\t\t\t\t----------------------------------------------");
    getch();

    printf("\nEnter ID# of employee you wish to delete: ");
    scanf("%d", &TempIDnum);
    if (TempIDnum < 1000)
    {
        printf("\nID# cannot be less than 4 digits,");
    }
    else
    {

        fseek(employee, (TempIDnum - 1) * sizeof(struct employee), SEEK_SET);
        fread(&worker, sizeof(struct employee), 1, employee);

        if (worker.IDnum == 0)
        {
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("\n\a\a\aID number does not exist.");
            SetConsoleTextAttribute(h, wOldColorAttrs);
            getch();
        } // end of if
        else
        {
            printf("\n%d %s %s %s", worker.IDnum, worker.fname, worker.sname, worker.type);
            printf("\n\nAre you sure you want to delete this employee (Y/N)? ");
            scanf(" %c", &deleteEmployee);
            if (deleteEmployee == 'Y' || deleteEmployee == 'y')
            {
                fseek(employee, (TempIDnum - 1) * sizeof(struct employee), SEEK_SET);
                fwrite(&blankworker, sizeof(struct employee), 1, employee);
                SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("\n\t\t\t-----------RECORD SUCCESSFULLY DELETED--------------");
                SetConsoleTextAttribute(h, wOldColorAttrs);
            } // end of if
            else if (deleteEmployee == 'N' || deleteEmployee == 'n')
            {
                printf("\n\t\tCANCELLED");
            } // end of else if
            else
            {
                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("\n\t\tINVALID INPUT. Please enter either Y or N");
                SetConsoleTextAttribute(h, wOldColorAttrs);
            } // end of else
        } // end of else
    } // end of else
    getch();
} // end of function deleteEmployee

// beginning of function searchEmployee
void searchEmployee(FILE *employee)
{
    struct employee worker = {0, 0, 0, " ", " ", " ", " ", " ", " ", " ", " ", " ", " "};
    int search;
    int TempIDnum;
    char fname[25];
    char lname[25];
    system("COLOR 06");

searchEmployee:
    title();
    printf("\n\t\t\t\t\t\tEnter any key to continue ");
    printf("\n\t\t\t---------------------------------------------------------------------");
    getch();
    printf("\n\n\t\t\t\t\t\tSEARCH PATIENT RECORD");
    printf("\n\t\t\t\t----------------------------------------------");
    getch();

    printf("\nSelect the criteria you wish to search by: "
           "\n1 - ID number"
           "\n2 - Search by Name"
           "\n3 - Exit:==> ");
    scanf("%d", &search);

    switch (search)
    {
    // case 1 search by ID number
    case 1:
        printf("\nEnter ID number: ");
        scanf("%d", &TempIDnum);
        if (TempIDnum < 1000)
        {
            printf("ID# cammot be less thn 4 digits.");
            getch();
        }
        else
        {

            fseek(employee, (TempIDnum - 1) * sizeof(struct employee), SEEK_SET);
            fread(&worker, sizeof(struct employee), 1, employee);

            if (worker.IDnum != 0)
            {
                printf("\n%-6s%-15s%-15s%-15s", "ID#", "First Name", "Surname", "Type");
                printf("\n%-6d%-15s%-15s%-15s", worker.IDnum, worker.fname, worker.sname, worker.type);
                getch();
            } // end of if
            else
            {
                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("\n\a\a\aEmployee not found.");
                SetConsoleTextAttribute(h, wOldColorAttrs);
                getch();
            } // end of else
        } // end of else
        getch();
        break;

    // case 2 search by employee first and last name
    case 2:
        printf("\nEnter name of employee (First name followed by last): ");
        scanf("%s%s", &fname, &lname);

        printf("\n-------------------EMPLOYEES-------------------");
        for (;;)
        {
            fread(&worker, sizeof(struct employee), 1, employee);
            if (feof(employee))
            {
                printf("\n\a\a\aEnd of Record.");
                getch();
                break;
            } // end of if
            if ((strcmpi(worker.fname, fname) == 0) && (strcmpi(worker.sname, lname) == 0))
            {
                printf("\n%-6s%-15s%-15s%-15s", "ID#", "First Name", "Surname", "Type");
                printf("\n%-6d%-15s%-15s%-15s", worker.IDnum, worker.fname, worker.sname, worker.type);
                getch();
            } // end of if
        } // end of for
        break;
    // exiting searchEmployee
    case 3:
        printf("Are you sure yo want to exit search employee: ");
        scanf(" %c", &ans);
        if (ans == 'Y' || ans == 'y')
        {
            puts("\n\t\t\tGOODBYE");
            getch();
            return;
        } // end of if
        else if (ans == 'N' || ans == 'n')
        {
            goto searchEmployee;
        } // end of else if
        else
        {
            printf("\n\t\t\tIncorrect Input. Please enter either Y or N.");
            getch();
            goto searchEmployee;
        } // end of else
        break;
    default:
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("\nINVALID CHOICE. Please enter either number 1 or 2.");
        SetConsoleTextAttribute(h, wOldColorAttrs);
        break;
    } // end of switch
} // end of function searchEmployee

// beginning of function viewEmployee
void viewALLEmployee(FILE *employee)
{
    struct employee worker = {0, 0, 0, " ", " ", " ", " ", " ", " ", " ", " ", " ", " "};
    int viewOption;
    char viewType[25];

    system("COLOR 0E");
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes;

    title();
    printf("\n\t\t\t\t\t\tEnter any key to continue ");
    printf("\n\t\t\t---------------------------------------------------------------------");
    getch();
    printf("\n\n\t\t\t\t\t\tVIEW ALL EMPLOYEE RECORD");
    printf("\n\t\t\t\t----------------------------------------------");
    getch();

viewEmployee:
    printf("\n\nEnter view option"
           "\n1 - View All Employees"
           "\n2 - View employees from search"
           "\n3 - Exit: ==> ");
    scanf("%d", &viewOption);

    switch (viewOption)
    {
    // case 1 to view all the employee record within the file
    case 1:
        printf("\n\n\t\t\t\t\t---------------EMPLOYEES--------------");
        printf("\n\t\t\t____________________________________________________________________________");
        SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\n\t\t\t|%-6s|%-25s|%-25s|%-15s|", "ID#", "First Name", "Surname", "Type");
        SetConsoleTextAttribute(h, wOldColorAttrs);
        printf("\n\t\t\t|______|_________________________|_________________________|_______________|");
        while (!feof(employee))
        {
            fread(&worker, sizeof(struct employee), 1, employee);
            if (feof(employee))
            {
                printf("\n\t\t\t|\t\t\t \a\a\aEnd of Records.                                   |");
                printf("\n\t\t\t|__________________________________________________________________________|");
                getch();
                break;
            } // end of if
            if (worker.IDnum != 0)
            {
                printf("\n\t\t\t|%-6d|%-25s|%-25s|%-15s|", worker.IDnum, worker.fname, worker.sname, worker.type);
                printf("\n\t\t\t|______|_________________________|_________________________|_______________|");
                getch();
            } // end of if
        } // end of while
        break;

    // case 2 to view all the nurses or doctors present within the file
    case 2:
        printf("\nEnter the type of employee you wish to see (Nurse or Doctor): ");
        scanf("%s", &viewType);

        printf("\nThe employees that are %ss include: ", viewType);
        printf("\n\n\t\t____________________________________________________");
        SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\n\t\t|%-6s%-15s%-15s%-15s|", "ID#", "First Name", "Surname", "Type");
        SetConsoleTextAttribute(h, wOldColorAttrs);
        for (;;)
        {
            if (strcmpi(worker.type, viewType) == 0)
            {
                printf("\n\t\t|___________________________________________________|");
                printf("\n\t\t|%-6d%-15s%-15s%-15s|", worker.IDnum, worker.fname, worker.sname, worker.type);
                getch();
            } // end of if
            fread(&worker, sizeof(struct employee), 1, employee);
            if (feof(employee))
            {
                printf("\n\t\t|___________________________________________________|");
                printf("\n\t\t|\t\t\a\a\aEnd of Records.                     |");
                printf("\n\t\t|___________________________________________________|");
                getch();
                break;
            } // end of if
        } // end of for
        break;
    case 3:
        printf("\nAre you sure you want to exit Y/N? ");
        scanf(" %c", &ans);

        if (ans == 'Y' || ans == 'y')
        {
            puts("GOODBYE");
            getch();
            return;
        } // end of if
        else if (ans == 'N' || ans == 'n')
        {
            goto viewEmployee;
        } // end of if
        else
        {
            printf("\nINCORRECT INPUT. Please enter Y or N.");
            getch();
            goto viewEmployee;
        } // end of else
        break;
    default:
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("\nINCORRECT CHOICE. Please enter either 1 or 2.");
        SetConsoleTextAttribute(h, wOldColorAttrs);
        break;
    } // end of switch
} // end of function viewEmployee

// beginning of function createEmployeeTextFile
void createEmployeeTextFile(FILE *reademployee)
{
    FILE *writeEmployee;
    struct employee worker = {0, 0, 0, " ", " ", " ", " ", " ", " ", " ", " ", " ", " "};
    const char *parish[] = {"", "St. Ann", "Trelawny", "St. Mary", "St. James", "Manchester", "St. Catherine", "St. Elizabeth", "St. Thomas", "Hanover", "Westmoreland", "Portland", "Clarendon", " Kingston", "St. Andrew"};
    const char *Gender[] = {"", "Female", "Male"};

    if ((writeEmployee = fopen("Employee.txt", "w+")) == NULL)
    {
        printf("\a\a\aFile could not be opened.");
        getch();
    } // end if
    else
    {
        rewind(reademployee);
        while (!feof(reademployee))
        {
            if (worker.IDnum != 0)
            {
                fread(&worker, sizeof(struct employee), 1, reademployee);
                fprintf(writeEmployee, "\n\t\t-----------------------------------------------------------------");
                fprintf(writeEmployee, "\n\t\t\t\tEMPLOYEE INFORMATION");
                fprintf(writeEmployee, "\n\t\t-----------------------------------------------------------------");
                fprintf(writeEmployee, "\n\t\tIdentification Number: \t%d", worker.IDnum);
                fprintf(writeEmployee, "\n\t\tName: \t\t\t%-15s%-15s%-15s", worker.fname, worker.mname, worker.sname);
                fprintf(writeEmployee, "\n\t\tDate of Birth: \t\t%s", worker.dob);
                fprintf(writeEmployee, "\n\t\tGender: \t\t%s", Gender[worker.gender]);
                fprintf(writeEmployee, "\n\t\tTRN: \t\t\t%s", worker.TRN);
                fprintf(writeEmployee, "\n\t\tAddress: \t\t%s, %s", worker.address, parish[worker.parish]);
                fprintf(writeEmployee, "\n\t\tEmail Address: \t\t%s", worker.emailaddress);
                fprintf(writeEmployee, "\n\t\tType of Employee: \t%s", worker.type);
                fprintf(writeEmployee, "\n\t\tTelephone Number: \t%s", worker.telephone);
                fprintf(writeEmployee, "\n\t\tNIS: \t\t\t%s", worker.NIS);
                fprintf(writeEmployee, "\n\t\tPosition: \t\t%s", worker.position);
                fprintf(writeEmployee, "\n\t\t-----------------------------------------------------------------");
            } // end of if
            fread(&worker, sizeof(struct employee), 1, reademployee);
        } // end of while
        fclose(writeEmployee);
    } // end of else
} // end of function createEmployeeTextFile

// beginning of function addAppointment
void addAppointment(FILE *appointmentPtr)
{
    struct appointmentdate appoint = {0, 0, 0, 0, ""};
    const char *mon[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int day, month;
    int days;
    int tempid;

    time_t now = time(0);
    struct tm now_t = *localtime(&now);

    day = now_t.tm_mday;
    appoint.appointmentmonth = now_t.tm_mon + 1;
    appoint.year = now_t.tm_year + 1900;

    printf("\nEnter appointment ID: ");
    scanf("%d", &tempid);
    fseek(appointmentPtr, (tempid - 1) * sizeof(struct appointmentdate), SEEK_SET);
    fread(&appoint, sizeof(struct appointmentdate), 1, appointmentPtr);

    if (appoint.appointmentID != 0)
    {
        printf("used!");
    } // end of if
    else
    {
        printf("\nEnter the amount of days until next appointment: ");
        scanf("%d", &days);
        printf("\nEnter First Name: ");
        scanf("%s", &appoint.patientapp.fname);
        printf("Enter Surname: ");
        scanf("%s", &appoint.patientapp.lname);
        printf("Enter reason for appointment: ");
        scanf("%s", &appoint.reason);
        printf("Enter telephone number: ");
        scanf("%s", &appoint.patientapp.telephone);

        appoint.appointmentday = day + days;

        if (appoint.appointmentday > 31)
        {
            appoint.appointmentday = appoint.appointmentday % 31;
            appoint.appointmentmonth = appoint.appointmentmonth + 1;

            printf("\nNext appointment is: %d %s %d", appoint.appointmentday, mon[appoint.appointmentmonth], appoint.year);
            getch();
        } // end of if
        appoint.appointmentID = tempid;

        fseek(appointmentPtr, (tempid - 1) * sizeof(struct appointmentdate), SEEK_SET);
        fwrite(&appoint, sizeof(struct appointmentdate), 1, appointmentPtr);
        fclose(appointmentPtr);
    } // end of else
} // end of function

// beginning function updateAppointment
void updateAppointment(FILE *appointmentPtr)
{
    struct appointmentdate appoint = {0, 0, 0, 0, ""};
    const char *mon[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int day, month;
    int tempid;
    int tempdays;
    printf("Enter appointment ID: ");
    scanf("%d", &tempid);

    fseek(appointmentPtr, (tempid - 1) * sizeof(struct appointmentdate), SEEK_SET);
    fread(&appoint, sizeof(struct appointmentdate), 1, appointmentPtr);

    if (appoint.appointmentID == 0)
    {
        printf("ID# does not exist in the file.");
        getch();
    } // end of if
    else
    {
        time_t now = time(0);
        struct tm now_t = *localtime(&now);

        day = now_t.tm_mday;
        appoint.appointmentmonth = now_t.tm_mon + 1;
        appoint.year = now_t.tm_year + 1900;

        printf("%d %s %s %d %s %d", appoint.appointmentID, appoint.patientapp.fname, appoint.patientapp.lname,
               appoint.appointmentday, mon[appoint.appointmentmonth], appoint.year);

        printf("\nEnter the number of days from today untill new appointment : ");
        scanf("%d", &tempdays);
        appoint.appointmentday = day + tempdays;
        if (appoint.appointmentday > 31)
        {
            appoint.appointmentmonth = appoint.appointmentmonth + 1;
        } // end of if
        fseek(appointmentPtr, (tempid - 1) * sizeof(struct appointmentdate), SEEK_SET);
        fwrite(&appoint, sizeof(struct appointmentdate), 1, appointmentPtr);

        printf("%d %s %s %d %s %d", appoint.appointmentID, appoint.patientapp.fname, appoint.patientapp.lname,
               appoint.appointmentday, mon[appoint.appointmentmonth], appoint.year);
    } // end of else
} // end of function

// beginning function viewallappointments
void viewallappointment(FILE *appointmentPtr)
{
    struct appointmentdate appoint = {0, 0, 0, 0, ""};
    const char *mon[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    // saves the current colour information
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes;

    while (!feof(appointmentPtr))
    {
        fread(&appoint, sizeof(struct appointmentdate), 1, appointmentPtr);
        if (feof(appointmentPtr))
        {
            printf("\n\tEnd of Appointment Records.");
            getch();
            break;
        } // end of if
        if (appoint.appointmentID != 0)
        {
            SetConsoleTextAttribute(h, FOREGROUND_MAGENTA | FOREGROUND_INTENSE_MAGENTA);
            printf("\n%-20s%-20s%-20s%-20s%-20s%-10s", "Appointment ID", "First Name", "Last Name", "Appointment Day", "Appointment Month", "Appointment Year");
            printf("\n=====================================================================================================================");
            SetConsoleTextAttribute(h, FOREGROUND_CYAN | FOREGROUND_INTENSE_CYAN);
            printf("\n%-20d%-20s%-20s%-20d%-20s%-10d", appoint.appointmentID, appoint.patientapp.fname, appoint.patientapp.lname, appoint.appointmentday,
                   mon[appoint.appointmentmonth], appoint.year);
            SetConsoleTextAttribute(h, wOldColorAttrs);
        } // end of if
    } // end of while
} // end of function

// beginning function textfileappointment
void textfileappointment(FILE *readAppointment)
{
    struct appointmentdate appoint = {0, 0, 0, 0, ""};
    const char *mon[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    FILE *writeAppointment;
    if ((writeAppointment = fopen("Appointment.txt", "a+")) == NULL)
    {
        printf("not found");
    } // end of if
    else
    {
        rewind(readAppointment);
        while (!feof(readAppointment))
        {
            fread(&appoint, sizeof(struct appointmentdate), 1, readAppointment);
            if (appoint.appointmentID != 0)
            {
                fprintf(writeAppointment, "\n\t\t---------------APPOINTMENTS---------------");
                fprintf(writeAppointment, "\n\n\tAppointment Number: \t%d", appoint.appointmentID);
                fprintf(writeAppointment, "\n\tName: \t\t\t%-15s%-15s", appoint.patientapp.fname, appoint.patientapp.lname);
                fprintf(writeAppointment, "\n\tDate of Appointment: \t%-11s%-3d%-6d", mon[appoint.appointmentmonth], appoint.appointmentday, appoint.year);
                fprintf(writeAppointment, "\n\tReason for Visit: \t%s", appoint.reason);
                fprintf(writeAppointment, "\n\tTelephone Number: \t%s", appoint.patientapp.telephone);
                fprintf(writeAppointment, "\n\t___________________________________________________");
            } // end of if
            fread(&appoint, sizeof(struct appointmentdate), 1, readAppointment);
        } // end of while
        fclose(writeAppointment);
    } // end of else
} // end of function textfileappointment

// beginning of function welcomescreen
void welcomescreen()
{
    system("COLOR B0");
    printf("\n\n\n\n\n\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("\t\t\t\t=                             WELCOME \t\t\t\t\t= \n");
    printf("\t\t\t\t=                               TO \t\t\t\t\t=\n");
    printf("\t\t\t\t=                               THE \t\t\t\t\t=\n");
    printf("\t\t\t\t=                          CLINIC RECORD \t\t\t\t=\n");
    printf("\t\t\t\t=  	                  MANAGEMENT SYSTEM \t\t\t\t=\n");
    printf("\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    getch();
    system("pause"); // pauses screen for user input
    system("cls");   // clears screen
} // end of function welcomescreen
