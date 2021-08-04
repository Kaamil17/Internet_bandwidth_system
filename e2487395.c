#include <stdio.h>
#include "the3.h"
#include "stdlib.h"


int compareStr(char *firstString, char *secondString) {
    int i;
    i = 0;

    while (firstString[i] == secondString[i]) {
        if (firstString[i] != '\0') return 1;
        i++;
    }
    return 0;
}

int getCount(Apartment *head) {
    int count;
    Apartment *current;

    if (head == NULL) {
        return 0;
    } else if (head->next == head) {
        return 1;
    }

    count = 1;
    current = head;

    while ((current = current->next) != head) {
        count++;
    }
    return count;
}


int flatCount(Flat *head) {
    int count;
    Flat *current;

    if (head == NULL) {
        return 0;
    } else if (head->next == NULL) {
        return 1;
    }

    count = 1;
    current = head;
    while ((current = current->next) != NULL) {
        count++;
    }
    return count;

}

/* done */

Apartment *add_apartment(Apartment *head, int index, char *apartment_name, int max_bandwidth) {

    Apartment *newApart;
    Apartment *current;
    Apartment *tailNode;
    int tempIndex;

    tailNode = head;
    if (head != NULL) {
        while (tailNode->next != head) {
            tailNode = tailNode->next;
        }
    }

    newApart = (Apartment *) malloc(sizeof(Apartment));

    newApart->flat_list = NULL;
    newApart->name = apartment_name;
    newApart->max_bandwidth = max_bandwidth;

    current = head;

    /* if there is no apartment */
    if (head == NULL) {
        head = newApart;
        newApart->next = newApart;
        return head;
    }

    /* for the last one */
    /* we reach the last node and add after it */
    if (index == getCount(head)) {

        for (tempIndex = 0; tempIndex < index; tempIndex++) {
            current = current->next;
        }
        newApart->next = current->next;
        current->next = newApart;

        return head;

        /* if we add in hte first index. we update the last node pointer to next */
    } else if (index == 0) {
        tailNode->next = newApart;
        newApart->next = head;
        head = newApart;
        return head;

    } else {
        /* if we add between them we land one before. */
        for (tempIndex = 0; tempIndex < index - 1; tempIndex++) {
            current = current->next;
        }
        newApart->next = current->next;
        current->next = newApart;
        return head;
    }
}


void add_flat(Apartment *head, char *apartment_name, int index, int flat_id, int initial_bandwidth) {

    Apartment *current;

    Flat *flatToAdd;
    Flat *flatHead;
    Flat *tempFlat;

    int totalBandOfFlat;
    int flatSize;
    int bandToAdd;
    int i;

    flatToAdd = (Flat *) malloc(sizeof(Flat));

    current = head;

    while (compareStr(current->name, apartment_name) != 1) {
        current = current->next;
    }
    /* we initilize them */
    flatHead = current->flat_list;
    flatToAdd->id = flat_id;
    flatToAdd->is_empty = 0;
    flatToAdd->initial_bandwidth = initial_bandwidth;

    totalBandOfFlat = 0;
    flatSize = 0;
    tempFlat = flatHead;

    /* finding sum of banddiwth and size of flatlist; */

    while (flatHead != NULL) {
        totalBandOfFlat += flatHead->initial_bandwidth;
        flatHead = flatHead->next;
        flatSize++;
    }
    /* checking the number to add for bandwitdh */

    bandToAdd = head->max_bandwidth - totalBandOfFlat;

    if (initial_bandwidth > bandToAdd) {
        flatToAdd->initial_bandwidth = bandToAdd;
    }


    /* if the flatlist  head has no flat */
    flatHead = current->flat_list;
    if (flatHead == NULL) {
        flatToAdd->next = NULL;
        flatToAdd->prev = NULL;
        current->flat_list = flatToAdd;

        /* for zero index */
    } else if (index == 0) {
        flatHead->prev = flatToAdd;
        flatToAdd->next = flatHead;
        flatToAdd->prev = NULL;
        current->flat_list = flatToAdd;

        /* if we wanna add at the end of flatlist */
    } else if (index == flatSize) {
        tempFlat->next = flatToAdd;
        flatToAdd->next = NULL;
        flatToAdd->prev = tempFlat;

        /* in any location but not the first and the last*/
    } else {
        tempFlat = flatHead;
        for (i = 0; i < index - 1; i++) {
            tempFlat = tempFlat->next;
        }
        tempFlat->next->prev = flatToAdd;
        flatToAdd->next = tempFlat->next;
        flatToAdd->prev = tempFlat;
        tempFlat->next = flatToAdd;
    }
}


Apartment *remove_apartment(Apartment *head, char *apartment_name) {
    Apartment *current;
    Apartment *toDelete;

    Flat *flatHead;
    Flat *flatDelete;
    current = head;

    while (compareStr(current->name, apartment_name) != 1) {
        current = current->next;
    }

    current = head;
    if (getCount(head) != 1) {
        while (current->next != head) {
            current = current->next;
        }
    }

    /* checking if it matches and remove the last one */
    if ((compareStr(head->name, apartment_name) == 1) && getCount(head) > 1) {
        toDelete = current->next;
        flatHead = toDelete->flat_list;
        current->next = toDelete->next;
        head = current->next;
        free(toDelete);
        toDelete = NULL;

        for (; flatHead != NULL; flatHead = flatHead->next) {
            flatDelete = flatHead;
            free(flatDelete);
            flatDelete = NULL;
        }
        return head;
        /* if its the only one */
    } else if ((compareStr(head->name, apartment_name) == 1) && getCount(head) == 1) {
        toDelete = head;
        flatHead = toDelete->flat_list;
        free(toDelete);
        toDelete = NULL;

        for (; flatHead != NULL; flatHead = flatHead->next) {
            flatDelete = flatHead;
            free(flatDelete);
            flatDelete = NULL;
        }
        return NULL;
    }

    current = head;
    /* in any location we land one before that thing */
    while (compareStr(current->next->name, apartment_name) != 1) {
        current = current->next;
    }

    toDelete = current->next;
    flatHead = toDelete->flat_list;
    current->next = toDelete->next;
    free(toDelete);
    toDelete = NULL;

    for (; flatHead != NULL; flatHead = flatHead->next) {
        flatDelete = flatHead;
        free(flatDelete);
        flatDelete = NULL;
    }
    return head;
}


/*done */
void make_flat_empty(Apartment *head, char *apartment_name, int flat_id) {

    Flat *flats;
    Apartment *current;

    current = head;
    while (compareStr(current->name, apartment_name) != 1) {
        current = current->next;
    }
    flats = current->flat_list;

    while (flats->id != flat_id) {
        flats = flats->next;
    }

    flats->is_empty = 1;
    flats->initial_bandwidth = 0;

}

/* done */
int find_sum_of_max_bandwidths(Apartment *head) {

    int totalBandWidth;
    Apartment *current;
    totalBandWidth = 0;
    current = head;

    if (head == NULL) {
        return totalBandWidth;
    } else {
        do {
            current = current->next;
            totalBandWidth += current->max_bandwidth;
        } while (current != head);
    }

    return totalBandWidth;
}

Apartment *merge_two_apartments(Apartment *head, char *apartment_name_1, char *apartment_name_2) {
    Apartment *firstCurrent;
    Apartment *secondCurrent;

    Flat *firstFlat;
    Flat *secondFlat;

    firstCurrent = head;
    secondCurrent = head;

    while (compareStr(firstCurrent->name, apartment_name_1) != 1) {
        firstCurrent = firstCurrent->next;
    }

    while (compareStr(secondCurrent->name, apartment_name_2) != 1) {
        secondCurrent = secondCurrent->next;
    }


    firstFlat = firstCurrent->flat_list;
    secondFlat = secondCurrent->flat_list;

    /* first case: BOTH NULL */
    if (firstFlat == NULL && secondFlat == NULL) {
        firstCurrent->max_bandwidth += secondCurrent->max_bandwidth;
        /* second case: First one NULL: Bellow */
    } else if (firstFlat == NULL && secondFlat != NULL) {
        firstCurrent->max_bandwidth += secondCurrent->max_bandwidth;
        firstFlat = secondFlat;
        secondFlat = NULL;
    } else if (firstFlat != NULL && secondFlat == NULL) {
        firstCurrent->max_bandwidth += secondCurrent->max_bandwidth;
    } else if (firstFlat != NULL && secondFlat != NULL) {
        firstCurrent->max_bandwidth += secondCurrent->max_bandwidth;

        while (firstFlat->next != NULL) {
            firstFlat = firstFlat->next;
        }

        firstFlat->next = secondFlat;
        secondFlat->prev = firstFlat;
        secondCurrent->flat_list = NULL;
    }
    head = remove_apartment(head, apartment_name_2);

    return head;
}

void
relocate_flats_to_same_apartment(Apartment *head, char *new_apartment_name, int flat_id_to_shift,
                                 int *flat_id_list) {
/* my soul and motivation batteries died here  */
}
