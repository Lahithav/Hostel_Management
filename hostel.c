#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Method Declarations
void enter_student();
void find_name();
void find_rollno();
void checkout_student();
void view_bookings();
void approve_request();
int count_students_in_room(const char *roomno);
void view_available_rooms();
int is_room_full(const char *roomno);

// Instance Field Declarations
FILE *view;
FILE *fp;
FILE *enter;
char admin_entry[20] = {'y'};
char user_entry[20] = {'y'};

// Structure defined to store student details
struct hostel {
    char name[20];
    char branch[20];
    char phoneno[20];
    char rollno[20];
    char place[20];
    char roomno[20]; // New field for room number
} h;

// Main method
int main() {
    int a, b, c;

    // Welcome screen
    printf("\n\n\t\t*************************************************\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*       -----------------------------           *\n");
    printf("\t\t*            WELCOME TO HOSTEL MUJ              *\n");
    printf("\t\t*       -----------------------------           *\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*                ARNAV AGARWAL                  *\n");
    printf("\t\t*                  199301***                    *\n");
    printf("\t\t*            SECTION *, EL PROJECT              *\n");
    printf("\t\t*************************************************\n\n\n");

    printf("\n>>>>>>>>>>>>\tFor ADMIN access enter --> 1 \t\t\t<<<<<<<<<<<<");
    printf("\n>>>>>>>>>>>>\tFor USER access enter --> 2 \t\t\t<<<<<<<<<<<<");
    printf("\n>> ");
    scanf("%d", &a);

    switch (a) {
        case 1: {
            char pass[10];
            char filepass[10];
            int i;

            FILE *passw;
            passw = fopen("pass.txt", "r");

            // Admin password prompt
            printf("\n Hello admin!\n Please enter the password to continue --> ");

            for (i = 0; i < 6; i++) {
                scanf("%s", pass);
                fscanf(passw, "%s", filepass);
                if (strcmp(filepass, pass) == 0) {
                    printf("\n\nAccess granted!\n");
                    fclose(passw);
                    break;
                } else {
                    printf("\nIncorrect password, please try again.");
                    printf("\nYou have %d tries left ", 5 - i - 1);
                    printf("\n\nEnter password >> ");
                }
                if (i == 4) {
                    fclose(passw);
                    return 0;
                }
            }

            // Re-entry if
            while (admin_entry[0] == 'y') {
                printf("\n>>>>>>>>>>>>\tTo VIEW booking requests --> 1 \t\t\t<<<<<<<<<<<<");
                printf("\n>>>>>>>>>>>>\tTo VIEW booked students details --> 2 \t\t\t<<<<<<<<<<<<");
                printf("\n>>>>>>>>>>>>\tTo ENTER new student --> 3 \t\t\t<<<<<<<<<<<<");
                printf("\n>>>>>>>>>>>>\tTo FIND roll number of existing student --> 4 \t<<<<<<<<<<<<");
                printf("\n>>>>>>>>>>>>\tTo FIND student of occupied room --> 5 \t<<<<<<<<<<<<");
                printf("\n>>>>>>>>>>>>\tTo CHECKOUT roll number of existing student --> 6 <<<<<<<<<<<<\n");
                printf(">> ");
                scanf("%d", &b);

                switch (b) {
                    case 1: {
                        view_bookings();
                        approve_request();
                        break;
                    }
                    case 2: {
                        FILE *fpi;
                        fpi = fopen("hostelnew.txt", "r");

                        printf("Name\t\tBranch\t\tPhone Number\tRoll Number\tPlace\t\tRoom Number\n");
                        printf("------------------------------------------------------------------------------------------\n");

                        while (fscanf(fpi, "%s %s %s %s %s %s", h.name, h.branch, h.phoneno, h.rollno, h.place, h.roomno) != -1) {
                            printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", h.name, h.branch, h.phoneno, h.rollno, h.place, h.roomno);
                        }
                        fclose(fpi);
                        break;
                    }
                    case 3: {
                        enter_student();
                        break;
                    }
                    case 4: {
                        find_rollno();
                        break;
                    }
                    case 5: {
                        find_name();
                        break;
                    }
                    case 6: {
                        checkout_student();
                        break;
                    }
                    default: {
                        printf("\n Wrong entry!");
                    }
                }
                // Enter again?
                printf("Would you like to continue? (y/n)\n");
                scanf("%s", admin_entry);
            }
            if (strcmp(admin_entry, "n") == 0) {
                printf("Exiting...\n");
                printf("\e[1;1H\e[2J");
                printf("\n >Exited<\n\n");
                return 0;
            } else {
                printf("Wrong entry!\nExiting...\n");
                return 0;
            }
            break;
        }
        case 2: {
            while (user_entry[0] == 'y') {
                printf("\nHello user and welcome to the Hostel!");
                printf("\n>>>>>>>>>>>>\tTo view available rooms --> 1 \t\t\t<<<<<<<<<<<<");
                printf("\n>>>>>>>>>>>>\tTo request booking of room --> 2 \t<<<<<<<<<<<<");
                printf("\n>> ");
                scanf("%d", &c);
                switch (c) {
                    case 1: {
                        view_available_rooms();
                        break;
                    }
                    case 2: {
                        printf("Enter your name: ");
                        scanf("%s", h.name);
                        printf("Enter branch: ");
                        scanf("%s", h.branch);
                        printf("Enter phone number: ");
                        scanf("%s", h.phoneno);
                        printf("Enter roll number: ");
                        scanf("%s", h.rollno);
                        printf("Enter place: ");
                        scanf("%s", h.place);
                        printf("Enter preferred room number (1-50) or 'any': ");
                        scanf("%s", h.roomno);

                        if (strcmp(h.roomno, "any") != 0 && (atoi(h.roomno) < 1 || atoi(h.roomno) > 50)) {
                            printf("\nInvalid room number! Request will be made for any available room.\n");
                            strcpy(h.roomno, "any");
                        }

                        enter = fopen("bookings.txt", "a");

                        fprintf(enter, "%s %s %s %s %s %s\n", h.name, h.branch, h.phoneno, h.rollno, h.place, h.roomno);

                        printf("Successfully requested booking\n");
                        fclose(enter);

                        break;
                    }
                    default: {
                        printf("\n Wrong entry!");
                    }
                }
                printf("Would you like to continue? (y/n)\n");
                scanf("%s", user_entry);
            }
            if (strcmp(user_entry, "n") == 0) {
                printf("Exiting...\n");
                printf("\e[1;1H\e[2J");
                printf("\n >Exited<\n\n");
                return 0;
            } else {
                printf("Wrong entry!\nExiting...\n");
                return 0;
            }
            break;
        }
    }
}

// Method to enter student
void enter_student() {
    FILE *tmp1;
    FILE *tmp2;
    int roomChoice;
    char roomNumber[20];
    char tempRoom[20];

    printf("\nEnter student name --> ");
    scanf("%s", h.name);
    printf("\nEnter branch --> ");
    scanf("%s", h.branch);
    printf("\nEnter phone number --> ");
    scanf("%s", h.phoneno);
    printf("\nEnter roll number --> ");
    scanf("%s", h.rollno);
    printf("\nEnter place --> ");
    scanf("%s", h.place);

    printf("\nWould you like to generate a random room number (1) or enter a room number (2)? ");
    scanf("%d", &roomChoice);

    if (roomChoice == 1) {
        srand(time(0));
        int randomRoom;
        do {
            randomRoom = rand() % 50 + 1; // Generates a random room number between 1 and 50
            sprintf(roomNumber, "%d", randomRoom);
        } while (count_students_in_room(roomNumber) >= 2);
    } else if (roomChoice == 2) {
        printf("\nEnter preferred room number (1-50): ");
        scanf("%s", tempRoom);
        if (atoi(tempRoom) < 1 || atoi(tempRoom) > 50 || count_students_in_room(tempRoom) >= 2) {
            printf("\nRoom is either invalid or already full! Please choose another room.\n");
            return;
        }
        strcpy(roomNumber, tempRoom);
    } else {
        printf("\nInvalid choice! Exiting...\n");
        return;
    }

    strcpy(h.roomno, roomNumber);

    tmp1 = fopen("hostelnew.txt", "a");
    tmp2 = fopen("hostel.txt", "a");

    fprintf(tmp1, "%s %s %s %s %s %s\n", h.name, h.branch, h.phoneno, h.rollno, h.place, h.roomno);
    fprintf(tmp2, "%s %s %s %s %s %s\n", h.name, h.branch, h.phoneno, h.rollno, h.place, h.roomno);

    printf("\nSuccessfully entered student data\n");

    fclose(tmp1);
    fclose(tmp2);
}

// Method to count the number of students in a room
int count_students_in_room(const char *roomno) {
    FILE *fp;
    int count = 0;
    struct hostel temp;

    fp = fopen("hostelnew.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    while (fscanf(fp, "%s %s %s %s %s %s", temp.name, temp.branch, temp.phoneno, temp.rollno, temp.place, temp.roomno) != -1) {
        if (strcmp(temp.roomno, roomno) == 0) {
            count++;
        }
    }

    fclose(fp);
    return count;
}

// Method to find a student by their room number
void find_name() {
    FILE *view;
    char roomno[20];
    int found = 0;

    printf("\nEnter room number: ");
    scanf("%s", roomno);

    view = fopen("hostelnew.txt", "r");
    if (view == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Students in room %s:\n", roomno);
    printf("Name\t\tBranch\t\tPhone Number\tRoll Number\tPlace\n");
    printf("-------------------------------------------------------------------\n");

    while (fscanf(view, "%s %s %s %s %s %s", h.name, h.branch, h.phoneno, h.rollno, h.place, h.roomno) != -1) {
        if (strcmp(h.roomno, roomno) == 0) {
            printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", h.name, h.branch, h.phoneno, h.rollno, h.place);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo student found in room number %s\n", roomno);
    }

    fclose(view);
}

// Method to find a student by their roll number
void find_rollno() {
    FILE *view;
    char rollno[20];
    int found = 0;

    printf("\nEnter roll number: ");
    scanf("%s", rollno);

    view = fopen("hostelnew.txt", "r");
    if (view == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Name\t\tBranch\t\tPhone Number\tPlace\t\tRoom Number\n");
    printf("-------------------------------------------------------------------\n");

    while (fscanf(view, "%s %s %s %s %s %s", h.name, h.branch, h.phoneno, h.rollno, h.place, h.roomno) != -1) {
        if (strcmp(h.rollno, rollno) == 0) {
            printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", h.name, h.branch, h.phoneno, h.place, h.roomno);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo student found with roll number %s\n", rollno);
    }

    fclose(view);
}

// Method to checkout a student by their roll number
void checkout_student() {
    FILE *fp1, *fp2;
    char rollno[20];
    int found = 0;

    printf("\nEnter roll number: ");
    scanf("%s", rollno);

    fp1 = fopen("hostelnew.txt", "r");
    fp2 = fopen("temp.txt", "w");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fscanf(fp1, "%s %s %s %s %s %s", h.name, h.branch, h.phoneno, h.rollno, h.place, h.roomno) != -1) {
        if (strcmp(h.rollno, rollno) == 0) {
            found = 1;
            printf("\nStudent %s checked out successfully.\n", h.name);
        } else {
            fprintf(fp2, "%s %s %s %s %s %s\n", h.name, h.branch, h.phoneno, h.rollno, h.place, h.roomno);
        }
    }

    fclose(fp1);
    fclose(fp2);

    remove("hostelnew.txt");
    rename("temp.txt", "hostelnew.txt");

    if (!found) {
        printf("\nNo student found with roll number %s\n", rollno);
    }
}

// Method to view booking requests
void view_bookings() {
    FILE *fpi;
    fpi = fopen("bookings.txt", "r");

    printf("Booking Requests:\n");
    printf("Name\t\tBranch\t\tPhone Number\tRoll Number\tPlace\t\tRoom Number\n");
    printf("-------------------------------------------------------------------\n");

    while (fscanf(fpi, "%s %s %s %s %s %s", h.name, h.branch, h.phoneno, h.rollno, h.place, h.roomno) != -1) {
        printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", h.name, h.branch, h.phoneno, h.rollno, h.place, h.roomno);
    }
    fclose(fpi);
}

// Method to approve booking requests
void approve_request() {
    FILE *bookings, *approved;
    char line[256];
    int roomNo;
    char approval[5];

    bookings = fopen("bookings.txt", "r");
    approved = fopen("approved_bookings.txt", "a");

    if (bookings == NULL || approved == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fgets(line, sizeof(line), bookings)) {
        sscanf(line, "%s %s %s %s %s %s", h.name, h.branch, h.phoneno, h.rollno, h.place, h.roomno);
        printf("Approve booking for %s (y/n)? ", h.name);
        scanf("%s", approval);
        if (strcmp(approval, "y") == 0 || strcmp(approval, "Y") == 0) {
            if (strcmp(h.roomno, "any") == 0 || count_students_in_room(h.roomno) >= 2) {
                srand(time(0));
                do {
                    roomNo = rand() % 50 + 1; // Generates a random room number between 1 and 50
                    sprintf(h.roomno, "%d", roomNo);
                } while (count_students_in_room(h.roomno) >= 2);
            }
            fprintf(approved, "%s %s %s %s %s %s\n", h.name, h.branch, h.phoneno, h.rollno, h.place, h.roomno);
        }
    }

    fclose(bookings);
    fclose(approved);

    remove("bookings.txt");
    rename("approved_bookings.txt", "bookings.txt");
}

// Method to check if a room is full
int is_room_full(const char *roomno) {
    return count_students_in_room(roomno) >= 2;
}

// Method to view available rooms
void view_available_rooms() {
    int i;

    printf("Available Rooms:\n");
    printf("Room Number\tStatus\n");
    printf("-------------------------\n");

    for (i = 1; i <= 50; i++) {
        char roomno[5];
        sprintf(roomno, "%d", i);
        if (count_students_in_room(roomno) < 2) {
            printf("%d\t\tAvailable\n", i);
        } else {
            printf("%d\t\tFull\n", i);
        }
    }
}
