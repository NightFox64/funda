#include "post.h"

Address *inputAddressData() {
    char city[MAX_STRING_SIZE];
    char street[MAX_STRING_SIZE];
    char building[MAX_STRING_SIZE];
    char postIndex[7];
    unsigned short house, flat;

    printf("Put the city: ");
    scanf("%s", city);

    printf("Put the street: ");
    scanf("%s", street);

    printf("Put house number: ");
    scanf("%hd", &house);

    printf("Put building body (if has): ");
    scanf("%s", building);

    printf("Put flat number: ");
    scanf("%hd", &flat);

    printf("Put index (6 symbols): ");
    scanf("%6s", postIndex);

    return CreateAddress(city, street, house, flat, building, postIndex);
}

Mail *inputMailData() {
    char id[15];
    char creationTime[20];
    char receiveTime[20];
    double weight;
    bool getStatus;
    int smth;

    printf("Put an ID (14 symbols): ");
    scanf("%14s", id);

    printf("Put the weight of mail: ");
    scanf("%lf", &weight);

    getchar();
    getchar();
    printf("Put creating time (dd:MM:yyyy hh:mm:ss): ");
    fgets(creationTime, 20, stdin);

    getchar();
    getchar();
    printf("Put recieving time (dd:MM:yyyy hh:mm:ss): ");
    fgets(receiveTime, 20, stdin);

    printf("Put '1' if reciever got the mail and '0' if not: ");
    scanf("%d", &smth);
    getStatus = smth;

    Address *addr = inputAddressData();
    if (!addr) {
        printf("Failed to create adress.\n");
        return NULL;
    }

    return CreateMail(addr, weight, id, creationTime, receiveTime, getStatus);
}

void interactiveDialog(Post *post) {
    int choice;
    char identifier[15];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add an mail\n");
        printf("2. Cancel mail\n");
        printf("3. Find mail with ID\n");
        printf("4. Show all mails\n");
        printf("5. Show all timed up mails\n");
        printf("6. Change get status for mail\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                Mail *mail = inputMailData();
                if (!mail) {
                    printf("Failed to add a sending.\n");
                }
                else if (!ValidateMail(mail)) {
                    printf("\n");
                    PrintMail(mail);
                    printf("\n");
                    DestroyMail(mail);
                    printf("Incorrect input\n");
                }
                else {
                    VectorPush(post->Mails, mail);
                    printf("Email added successfully.\n");
                }
                break;
            }
            case 2:
                printf("Put an ID for canceling: ");
                scanf("%14s", identifier);
                if (RemoveElement(post, identifier) == true) {
                    printf("Sending is canceled.\n");
                } else {
                    printf("Sending with ID: %s didn't find.\n", identifier);
                }
                break;
            case 3:
                printf("Put the ID for searching: ");
                scanf("%14s", identifier);
                Mail *m = FindElement(post, identifier);
                if (m != NULL) {
                    PrintMail(m);
                } else {
                    printf("Sending didn't find\n");
                }
                break;
            case 4:
                DisplayAllMails(post);
                break;
            case 5:
                FindExpiredMails(post);
                break;
            case 6:
                int smth;
                bool getStatus;
                printf("Put the ID for changing: ");
                scanf("%14s", identifier);
                Mail *mail = FindElement(post, identifier);
                if (mail != NULL) {
                    printf("Put '1' if reciever got the mail and '0' if not: ");
                    scanf("%d", &smth);
                    getStatus = smth;
                    ChangeMailGetStatus(post, identifier, getStatus);
                printf("\n");
                } else {
                    printf("Sending didn't find\n");
                }
                
                break;
            case 0:
                printf("Exiting the program.\n");
                return;
            default:
                printf("Bad choice. Try again.\n");
        }
    }
}

int main(void) {
    Address *postAddress = inputAddressData();
    Post *post = CreatePost(postAddress);
    interactiveDialog(post);
    DestroyPost(post);
    return 0;
}