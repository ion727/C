// n->number is syntactic sugar for (*n).number
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int number;
    struct node *next;
} node;

int append_node(node **listaddr, int n);
int insert_node(node *list, int number, int index);
void read_list(node *list);
void free_all(node *list);

int main(void){
    node *list = NULL;
    
    // appending
    int numbers[4] = {1,2,4,5};
    int lennumbers = 4;
    for (int i = 0; i < 4; i++) {
        if (append_node(&list, numbers[i]) == 2){
            free_all(list);
            return 2;
        }
    }

    // insertion
    int inserts[1] = {3};
    int leninsert = 1;
    for (int i = 0; i < leninsert; i++){
        if (insert_node(list, inserts[i], 2) != 0) {
            free_all(list);
            return 1;
        }
    }


    free_all(list);    
}


int append_node(node **listaddr, int n){
    node *list = *listaddr; // gets the address of the list variable to ensure the variable and not a copy is editted
    if (list != NULL) {    
        while (list->next != NULL) {
            list = list->next;
        }
    }
    node *new = malloc(sizeof(node));
    if (new == NULL) {
        printf("Error: Unable to allocate memory.\n");
        return 2;
    }
    new->number = n;
    new->next = NULL;
    if (list != NULL) {
        list->next = new;
    } else {
        *listaddr = new;
    }
    return 0;
}

int insert_node(node *list, int number, int index) {
    if (list == NULL) {
        printf("Error: cannot insert into an empty list.");
        return 3;
    }
    int i = 0;
    while (list != NULL && i < index -1 ){
        list = list->next;
        i++;
    }
    if (list == NULL && i != index) {
            printf("Error: list index out of range for insert_node().\n");
            return 1;
    }
    node *new = malloc(sizeof(node));
    if (new == NULL) {
        printf("Error: Unable to allocate memory.\n");
        return 2;
    }
    new->number = number;
    new->next = list->next;
    list->next = new;
    return 0;
}

void read_list(node *list){
    for (node *tmp = list; tmp != NULL; tmp = tmp->next) {
        printf("%i\n", tmp->number);
    }
}

void free_all(node *list){
    if (list == NULL) {
        return;
    }

    node *next_node = list;
    node *current_node;
    do {
        current_node = next_node;
        next_node = current_node->next;
        printf("%i freed.\n",current_node->number);
        free(current_node);
    } while (next_node != NULL);
}