#include "vector.h"

typedef struct {
    Address *CurrentAddress;
    Vector *Mails;
} Post;

Post *CreatePost(Address *current) {
    Post *post = (Post*)malloc(sizeof(Post));
    if (!post) {
        return NULL;
    }
    post->CurrentAddress = current;
    post->Mails = CreateVector(2);
    if (!post->Mails) {
        free(post);
        return NULL;
    }
    return post;
}

void DisplayAllMails(Post *p) {
    for (int i = 0; i < p->Mails->len; i++) {
        PrintMail(p->Mails->buffer[i]);
    }
}

Mail *FindElement(Post *post, char *id) {
    String *compare = NewString(id);
    for (int i = 0; i < post->Mails->len; i++) {
        if (StringEqual(post->Mails->buffer[i]->ID, compare)) {
            return post->Mails->buffer[i];
        }
    }
    return NULL;
}

void ChangeMailGetStatus(Post *post, char *id, bool status){
    Mail *dest = FindElement(post, id);
    dest->GetStatus = status;
    return;
}

void FindExpiredMails(Post *p) {
    printf("\n--- Timed up mails ---\n");

    for (int i = 0; i < p->Mails->len; i++) {
        struct tm creationTime = {0};
        char *receiveTimeStr = p->Mails->buffer[i]->ReceiveTime->buffer;

        if (sscanf(receiveTimeStr, "%d:%d:%d %d:%d:%d",
                   &creationTime.tm_mday, &creationTime.tm_mon, &creationTime.tm_year,
                   &creationTime.tm_hour, &creationTime.tm_min, &creationTime.tm_sec) != 6) {
            fprintf(stderr, "Error: Invalid time format for ID: %s\n",
                    p->Mails->buffer[i]->ID->buffer);
            continue;
        }

        if (!p->Mails->buffer[i]->GetStatus) {
            PrintMail(p->Mails->buffer[i]);
        }
    }
}

bool RemoveElement(Post *post, char *id) {
    String *compare = NewString(id);
    for (int i = 0; i < post->Mails->len; i++) {
        if (StringEqual(post->Mails->buffer[i]->ID, compare)) {
            VectorPop(post->Mails, i);
            return true;
        }
    }
    return false;
}

void DestroyPost(Post *p) {
    DestroyVector(p->Mails);
    DestroyAddress(p->CurrentAddress);
    free(p);
}
