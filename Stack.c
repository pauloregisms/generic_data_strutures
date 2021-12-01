#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

struct Stack {
    int size;
    int top;
    void **items;
};

Stack *Stack_alloc(int size) {
    Stack *s = malloc(sizeof(Stack));
    s->top = -1;
    s->size = 0;
    s->items = calloc(size, sizeof(void *));
    return s;
}

void   Stack_free(Stack *s) {}
int    Stack_isEmpty(Stack *s){return 0;}
int    Stack_isFull(Stack *s) {return 0;}
int    Stack_getSize(Stack *s){return s->size;}

void Stack_push(Stack *s, void *element) {
    s->items[++s->top] = element;
}

void *Stack_pop(Stack *s) {
    void *temp = NULL;
    temp = s->items[s->top--];
    return temp;
}

void  *Stack_top(Stack *s) {return NULL;}

void Stack_print(Stack *s, void (*print)(void *)) {
    int i;
    for(i=s->top; i >= 0; i--)
        print(s->items[i]);
    printf("\n");
}
