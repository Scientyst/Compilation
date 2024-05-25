#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIZE 201

#define MAX 100




typedef enum {
    TYPE_ERROR,
    TYPE_INT,
    TYPE_VOID,
    TYPE_STRUCT
} SymboleType;


const char* TypesNames[] = {"TYPE_ERROR","TYPE_INT","TYPE_VOID","TYPE_STRUCT"};

typedef struct {
    char* name;
    SymboleType type;
} Symbole;


typedef struct Node {
    Symbole symbole;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int length;
} LinkedList;

LinkedList symbol_table[SIZE];


//definition de la pile d'execution
typedef struct {
    LinkedList *list[MAX];
    int length;
}Tas;

Tas tas;

int isEmpty(Tas t){
    if(t.length == 0){
        return 1;
    }
    return 0;
}

void addinTas(Tas t,LinkedList ts){
    t.length++;
    t.list[t.length]=&ts;
}

void popTas(Tas t){
    t.length--;
}

LinkedList getTopTas(Tas t){
    t.length--;
    return *t.list[t.length-1];
}

int fonction_hash(char* name) {
    int hash = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        hash += name[i];
    }
    return hash % SIZE;
}

void initialize_tas(Tas *t){
    for(int i=0;i<MAX;i++){
        t->list[i]=NULL;
    }
}

void initialize_table(LinkedList* table) {
    for (int i = 0; i < SIZE; i++) {
        table[i].head = NULL;
    }
}

void clear_table(LinkedList* table) {
    for (int i = 0; i < SIZE; i++) {
        Node* current = table[i].head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp->symbole.name);
            free(temp);
        }
        table[i].head = NULL;
    }
}

Symbole* find_symbol(LinkedList* table, char* name) {
    int index = fonction_hash(name);
    Node* current = table[index].head;
    while (current != NULL) {
        if (strcmp(current->symbole.name, name) == 0) {
            return &(current->symbole);
        }
        current = current->next;
    }
    return NULL;
}

void insert_symbol(LinkedList* table, char* name, SymboleType type) {
    int index = fonction_hash(name);
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->symbole.name = strdup(name);
    new_node->symbole.type = type;
    new_node->next = NULL;

    if (table[index].head == NULL) {
        table[index].head = new_node;
    } else {
        new_node->next = table[index].head;
        table[index].head = new_node;
    }
}

void update_symbol(LinkedList* table, char* name, SymboleType type) {
    Symbole* symbol = find_symbol(table, name);
    if (symbol != NULL) {
        symbol->type = type;
    }
}

void print_symbol_table(LinkedList* table) {
    printf("\n%15s | %15s | %15s |\n", "TABLE", "NOM", "TYPE");

    for (int i = 0; i < SIZE; i++) {
        Node* current = table[i].head;
        while (current != NULL) {
            printf("table[%d]\t| %15s | %15s |\n", i, current->symbole.name, TypesNames[current->symbole.type]);
            current = current->next;
        }
    }
}




LinkedList* copyLinkedList(LinkedList* l){
    printf("TESTESEEZT");
    LinkedList* newll;
    initialize_table(newll);
    for(int i=0;i<SIZE;i++){
        
        Node* current = l[i].head;
        Node* newcurrent= newll[i].head;
        while(current != NULL){
            insert_symbol(newll,current->symbole.name,current->symbole.type);
        }
    }
    return newll;
}

int main(void){
    LinkedList L;
    Tas t;
    initialize_tas(&t);
    initialize_table(&L);
    
    SymboleType st;
    st=TYPE_INT;
    //printf("Info: %d",st);
    insert_symbol(&L,"Bi",st);
    insert_symbol(&L,"Zon",TYPE_STRUCT);
    insert_symbol(&L,"Fu",TYPE_VOID);
    insert_symbol(&L,"T",TYPE_ERROR);
    //print_symbol_table(&L);
    Symbole *s = find_symbol(&L,"Fu");
    printf("Le symbloeleeeee trouvé:%s et type: %d",s->name,s->type);

    addinTas(t,L);

    LinkedList test = getTopTas(t);
    
    print_symbol_table(&test);

    LinkedList *ll = copyLinkedList(&L);
    print_symbol_table(ll);

    return(0);
}

