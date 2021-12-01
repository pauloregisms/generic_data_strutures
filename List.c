#include <stdlib.h>
#include <stdio.h>
#include "List.h"

typedef struct Node Node;

struct Node {
    void *value;
    Node *next;
};

struct List {
    Node *first;
    int length;
};

List *List_alloc() { 
    List *list = malloc(sizeof(List));
    list->first = NULL;
    list->length = 0;
    return list;
}

void  List_free(List *list) { 
    Node *node = NULL, *aux;

    if (list != NULL) {
        node = list->first;
        
        while(node != NULL) {
            aux = node->next;
            free(node);
            node = aux;
        }
        
        free(list);
    }
}

void *List_find(List* list, void *value, int (*compar)(void*, void*) ) { 
    Node *node = NULL;

    if (list && value && compar) {
        node = list->first;
        
        while (node) {
            if (compar(node->value, value) == 0)
                return node->value;
            
            node = node->next;
        }
    }

    return NULL;
}

void List_insertBegin(List* list, void *value) {
	Node *node = NULL;
	
	if (list && value) {
        node = malloc(sizeof(Node));
        node->value = value;
        node->next = list->first;
        list->first = node;
        list->length++;
    }
}

void List_insertEnd(List* list, void *value) {
	Node *node = NULL;
	
	if (list && value) {
        if (List_getLength(list) == 0) {
            list->first = malloc(sizeof(Node));
            list->first->value = value;
            list->first->next = NULL;
        }
        else {
            node = list->first;
            while (node->next)
                node = node->next;
            
            node->next = malloc(sizeof(Node));
            node->next->value = value;
            node->next->next = NULL;
        }
        list->length++;
    }
}

void *List_removeBegin(List* list) {
	Node *node = NULL;
	void *value = NULL;
	
	if (list) {
		node = list->first;
		list->first = node->next;
		value = node->value;
		free(node);
        list->length--;
	}
	
	return value;
}

void *List_removeEnd(List* list) {
	Node *node = NULL;
	void *value = NULL;
	
	if (list) {
		node = list->first;
		while (node->next)
			node = node->next;
		value = node->value;
		free(node);
        list->length--;
	}
	
	return value;
}

void *List_findAndRemove(List* list, void *value, int (*compar)(void*, void*) ) { 
    Node *node = NULL, *ant = NULL;
    void *aux = NULL;

    if (list && value && compar) {
        node = list->first;
        
        while (node) {
            if (compar(node->value, value) == 0) {
                aux = node->value;

                if (ant != NULL)
                    ant->next = node->next;
    
                free(node);
                list->length--;
                return aux;
            }
            ant = node;
            node = node->next;
        }
    }

    return NULL;
}

int List_getLength(List *list) { 
    Node *node = NULL;
    int length = 0;

    if (list) {
        return list->length;
    }

    return length;
}

void  List_print(List *list, void (*print)(void *)) { 
    Node *node = NULL;

    if (list && print) {
        node = list->first;
        
        while (node) {
            print(node->value);
            node = node->next;
        }
        
        printf("\n");
    }
}

List *List_concatenate(const List *list_a, const List *list_b) {
    List *list_c = NULL;
    Node *node = NULL;

    if (list_a && list_b) {

        list_c = List_alloc();

        node = list_a->first;
        while (node) {
            List_insertEnd(list_c, node->value);
            node = node->next;
        }
        
        node = list_b->first;
        while (node) {
            List_insertEnd(list_c, node->value);
            node = node->next;
        }
    }

    return list_c;
}

List *List_sort(List *list, int (*compar)(void*, void*) ) {
    Node *node = NULL;
    List *list_a = NULL;
    List *list_b = NULL;

    if (list && compar) {
        if (List_getLength(list) <= 1) {
            return list;
        }
        else {
            node = list->first->next;
            list_a = List_alloc();
            list_b = List_alloc();

            while (node) {
                if (compar(list->first->value, node->value) > 0)
                    List_insertEnd(list_a, node->value);
                else 
                    List_insertEnd(list_b, node->value);
                node = node->next;
            }

            List_insertEnd(list_a, list->first->value);

            return List_concatenate( List_sort(list_a, compar), List_sort(list_b, compar) );
        }
    }

    return list;
}

void List_insertSorted(List *list, void *value, int (*compar)(void*, void*) ) {
    Node *node = NULL;
    Node *newNode = NULL;
    Node *prev = NULL;
    int insertEnd = 1;

    if (list && value && compar) {
        if (List_getLength(list) == 0) {
            List_insertBegin(list, value);
        }
        else {
            node = list->first;
            
            while (node) {
                if (compar(value, node->value) <= 0) {

                    newNode = malloc(sizeof(Node));
                    newNode->value = value;

                    if (prev == NULL)
                        list->first = newNode;
                    else
                        prev->next = newNode;

                    newNode->next = node;
                    insertEnd = 0;
                    break;

                }

                prev = node;
                node = node->next;
            }

            if (insertEnd)
                List_insertEnd(list, value);
        }
    }    
}