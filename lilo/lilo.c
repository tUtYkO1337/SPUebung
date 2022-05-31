#include <stdio.h>
#include <stdlib.h>


 struct listelement {
    int value;
    struct listelement *next;
};
typedef struct listelement listelement;

// Start of the linked list
static listelement *head = NULL;

/*
 * Checks if value is in the list
 */
static int contains(int value) {
    listelement *list = head;
    while (list != NULL) {
        if (list->value == value) return 1;
        list = list->next;
    }
    return 0;
}

/*
 * Prints the list ind the console
 */
int export(void) {
    listelement *list = head;
    while (list != NULL) {
        printf(", %d\n",list->value);
        list = list->next;
    }
    return 0;

}

/*
 * Inserts value at the end of the list
 * returns: value if successfull, -1 if not
 */
int insertElement(int value) {
    if(value < 0 || contains(value)) return -1;
    struct listelement *newelement;
    newelement = malloc(sizeof(listelement));
    if(newelement == NULL){
        return -1;
    }
    newelement->value = value;
    newelement->next = NULL;
    if(head == NULL) head = newelement;
    else{
        listelement *last = head;
        while(last->next != NULL){
            last = last->next;
        }
        last->next = newelement;
    }
    return value;
}

/*
 * Removes first element from the list
 * returns: deleted value if successfull, -1 if list is empty
 */
int removeElement(void) {
    if (head == NULL) return -1;
    listelement *del = head;
    int x = del->value;
    head = del->next;
    free(del);
    return x;
}


int main(int argc, char *argv[]) {
    //printf("insert 47: %d\n", insertElement(47));
    //printf("insert 11: %d\n", insertElement(11));
    //printf("insert 23: %d\n", insertElement(23));
    //printf("insert 11: %d\n", insertElement(11));

    //printf("remove: %d\n", removeElement());
    //printf("remove: %d\n", removeElement());

    if (head) {
        printf("\x1B[31m[ERROR:%3d] HEAD should be NULL\n", __LINE__);
        printf("\x1B[0m");
        abort();
    }

    int mx = removeElement();
    if (mx != -1) {
        printf("\x1B[31m[ERROR:%3d] Expected: -1, but was %3d\n", __LINE__, mx);
        printf("\x1B[0m");
        abort();
    }
    int mt = insertElement(0);
    if (mt != 0) {
        printf("\x1B[31m[ERROR:%3d] Expected: -1, but was %3d\n", __LINE__, mt);
        printf("\x1B[0m");
        abort();
    }
    int mr = removeElement();
    if (mr != 0) {
        printf("\x1B[31m[ERROR:%3d] Expected: 0, but was %3d\n", __LINE__, mt);
        printf("\x1B[0m");
        abort();
    }
    printf("\x1B[32m[PASSED:%3d] Constants test\n", __LINE__);

    printf("\x1B[36m:=: Static negative numbers test :=:\n");
    for (int i = -1; i > -65536; i--) {
        int x = insertElement(i);
        if (-1 != x) {
            printf("\x1B[31m[ERROR:%3d] Expected: -1, but was %3d\n", __LINE__, i);
            printf("\x1B[0m");
            abort();
        }
    }

    printf("\x1B[32m[PASSED:%3d] Negative numbers\n", __LINE__);

    printf("\x1B[36m:=: Sequential test, this could take a while :=:\n");
    for (int i = 0; i < 32768; i++) {
        int x = insertElement(i);
        if (i != x) {
            printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, i, x);
            printf("\x1B[0m");
            abort();
        }
    }

    printf("\x1B[32m[PASSED:%3d] Sequential insertion\n", __LINE__);

    for (int i = 0; i < 32768; i++) {
        int x = insertElement(i);
        if (-1 != x) {
            printf("\x1B[31m[ERROR:%3d] Expected: -1, but was %3d\n", __LINE__, i);
            printf("\x1B[0m");
            abort();
        }
    }

    printf("\x1B[32m[PASSED:%3d] Sequential duplicate values\n", __LINE__);

    for (int i = 0; i < 32768; i++) {
        int x = removeElement();
        if (i != x) {
            printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, i, x);
            printf("\x1B[0m");
            abort();
        }
    }

    if (head) {
        printf("\x1B[31m[ERROR:%3d] HEAD should be NULL\n", __LINE__);
        printf("\x1B[0m");
        abort();
    }

    printf("\x1B[32m[PASSED:%3d] Sequential remove\n", __LINE__);

    printf("\x1B[36m:=: Repeating patterns test :=:\n");

    for (int i = 0; i < 1024; i++) {
        if (head) {
            printf("\x1B[31m[ERROR:%3d] Head should be NULL\n", __LINE__);
            printf("\x1B[0m");
            abort();
        }
        int randomValue = 0 + rand() / (RAND_MAX / ((RAND_MAX - 4) - 0 + 1) + 1);
        int x = insertElement(randomValue);
        if (randomValue != x) {
            printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__,
                   randomValue, x);
            printf("\x1B[0m");
            abort();
        }
        int y = removeElement();
        if (randomValue != y) {
            printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__,
                   randomValue, y);
            printf("\x1B[0m");
            abort();
        }
    }

    printf("\x1B[32m[PASSED:%3d] Single element shuffle\n", __LINE__);
    printf("\x1B[36m:=: Static order test :=:\n");

    for (int i = 1; i < 64; i += 2) {
        int t = insertElement(i);
        if (i != t) {
            printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, i, t);
            printf("\x1B[0m");
            abort();
        }
    }

    for (int i = 0; i < 64; i += 2) {
        listelement *start = head;
        int x = 1;
        for (int k = 0; k < i / 2; k++) {
            if (start->value != x) {
                printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, x,
                       start->value);
                printf("\x1B[0m");
                abort();
            }
            x += 2;
            start = start->next;
        }
        if (start->value != i + 1) {
            printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, i + 1,
                   start->value);
            printf("\x1B[0m");
            abort();
        }
    }
    printf("\x1B[0m");
    for (int i = 1; i < 64; i += 2) {
        int y = removeElement();
        if (y != i) {
            printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, i, y);
            printf("\x1B[0m");
            abort();
        }
        listelement *start = head;

        int x = y + 2;
        for (int k = 0; k < (64 - i) / 2; k++) {
            if (start->value != x) {
                printf("\x1B[31m[ERROR:%3d] Expected: %3d, but was %3d\n", __LINE__, i,
                       y);
                printf("\x1B[0m");
                abort();
            }
            start = start->next;
            x += 2;
        }
    }
    printf("\x1B[32m[PASSED:%3d] Static order\n", __LINE__);

    printf("\x1B[0m");

    // TODO: add more tests
    exit(EXIT_SUCCESS);
}
