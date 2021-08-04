#include <stdio.h>
#include "the3.h"
#include "stdlib.h"



void printApts(Apartment *apt){
    Apartment *aCurr;
    aCurr = apt;
    do{
        printf("%s, %d\n", aCurr->name, aCurr->max_bandwidth);
        if (aCurr->flat_list){
            Flat *fCurr;
            fCurr = aCurr->flat_list;
            while(fCurr){
                printf("     %d, %d, %d\n", fCurr->id, fCurr->initial_bandwidth, fCurr->is_empty);
                if (fCurr->next){
                    if(fCurr->next->prev == fCurr){
                        printf("\t|  |\n"); /* if flats are doubly linked (as intended)*/
                    }
                    else{
                        printf("\t.  .\n"); /* not doubly linked */
                    }
                }
                else
                    printf("\n");
                fCurr = fCurr->next;
            }
        }
        aCurr = aCurr->next;
    }while(aCurr != apt);
}



int main() {


    Apartment *apartment;

    apartment = (struct apartment *) malloc(sizeof(struct apartment));


    apartment = add_apartment(apartment, 9, "Z", 60);
    apartment = add_apartment(apartment, 1, "Y", 50);
    apartment = add_apartment(apartment, 2, "P", 100);

    printApts(apartment);

    return 0;
}
