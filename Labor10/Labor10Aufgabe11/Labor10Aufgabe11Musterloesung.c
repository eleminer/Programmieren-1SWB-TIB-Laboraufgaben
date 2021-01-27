#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bookings {
    struct bookings *nextBooking;
    float amount;
    char description[40];
};

struct customers {
    char forename[40];
    char surname[40];
    struct bookings *firstBooking;
    struct customers *nextCustomer;
};

struct customers *anchorCustomer = NULL;

struct customers *createCustomers(char *forname, char *surname) {
    struct customers *customer = malloc(sizeof(struct customers));
    if (customer != NULL) {
        strcpy(customer->forename, forname);
        strcpy(customer->surname, surname);
        customer->firstBooking = NULL;
        customer->nextCustomer = NULL;
    }
    return customer;
}

void addCustomers(struct customers *customer) {
    if (anchorCustomer == NULL) {
        anchorCustomer = customer;
    } else {
        struct customers *currentItem = anchorCustomer;
        while (currentItem->nextCustomer != NULL) {
            currentItem = currentItem->nextCustomer;
        }
        currentItem->nextCustomer = customer;
    }
}

void printCustomers() {
    printf("Customers:\n");
    if (anchorCustomer != NULL) {
        printf("| %3s | %-40s | %-40s |\n", "# ", "Forename", "Surname");
        for (int i = 0; i < (3 + 40 + 40 + 10); ++i) {
            printf("-");
        }
        printf("\n");
        struct customers *currentItem = anchorCustomer;
        for (int i = 0; currentItem != NULL; i++) {
            printf("| %03d | %-40s | %-40s |\n", i, currentItem->forename, currentItem->surname);
            currentItem = currentItem->nextCustomer;
        }
    }
}

struct customers *findCustomerByPos(int pos) {
    struct customers *currentItem = anchorCustomer;
    for (int i = 0; i < pos; i++) {
        currentItem = currentItem->nextCustomer;
    }
    return currentItem;
}

struct bookings *createBooking(float amount, char *description) {
    struct bookings *booking = malloc(sizeof(struct bookings));
    if (booking != NULL) {
        strcpy(booking->description, description);
        booking->amount = amount;
        booking->nextBooking = NULL;
    }
    return booking;
}

void addBookingToCustomers(struct customers *customer, struct bookings *booking) {
    struct bookings *currentItem = customer->firstBooking;
    if (currentItem == NULL) {
        customer->firstBooking = booking;
    } else {
        while (currentItem->nextBooking != NULL) {
            currentItem = currentItem->nextBooking;
        }
        currentItem->nextBooking = booking;
    }
}

void printBookingsFromCustomers(struct customers *customer) {
    printf("All Bookings from %s %s:\n", customer->forename, customer->surname);
    struct bookings *currentItem = customer->firstBooking;
    if (currentItem != NULL) {
        printf("| %3s | %12s | %-40s |\n", "#", "Amount", "Description");
        for (int i = 0; i < (3 + 12 + 40 + 10); ++i) {
            printf("-");
        }
        printf("\n");
        for (int i = 0; currentItem != NULL; i++) {
            printf("| %03d | %10.2f $ | %-40s |\n", i, currentItem->amount, currentItem->description);
            currentItem = currentItem->nextBooking;
        }
    }
}

void cleanAll() {
    struct customers *currentCustomer = anchorCustomer;
    if (currentCustomer != NULL) {
        do {
            struct customers *tmpCustomer = currentCustomer;

            struct bookings *currentBooking = currentCustomer->firstBooking;
            if (currentBooking != NULL) {
                do {
                    struct bookings *tmpBooking = currentBooking;
                    currentBooking = currentBooking->nextBooking;
                    free(tmpBooking);
                } while (currentBooking != NULL);
            }
            currentCustomer = currentCustomer->nextCustomer;
            free(tmpCustomer);
        } while (currentCustomer != NULL);
    }
    anchorCustomer = NULL;
}

int main(int argc, char *argv[]) {
    char comanmd[5];
    char type[10];
    do {
        printf("> ");
        scanf("%s", comanmd);
        if (strcmp(comanmd, "list") == 0 || strcmp(comanmd, "add") == 0) {
            scanf("%s", type);
            if (strcmp(comanmd, "list") == 0) {
                if (strcmp(type, "customer") == 0) {
                    printCustomers();
                } else if (strcmp(type, "booking") == 0) {
                    int customerPos;
                    scanf("%d", &customerPos);
                    struct customers *customer = findCustomerByPos(customerPos);
                    printBookingsFromCustomers(customer);
                }
            } else if (strcmp(comanmd, "add") == 0) {
                if (strcmp(type, "customer") == 0) {
                    char forename[40];
                    char surname[40];
                    scanf("%s %s", forename, surname);
                    addCustomers(createCustomers(forename, surname));
                } else if (strcmp(type, "booking") == 0) {
                    float amount;
                    char description[40];
                    int customerPos;
                    scanf("%d %f %s", &customerPos, &amount, description);
                    struct customers *customer = findCustomerByPos(customerPos);
                    addBookingToCustomers(customer, createBooking(amount, description));
                }
            }
        }
    } while (strcmp(comanmd, "exit") != 0);

    cleanAll();
    return 0;
}
