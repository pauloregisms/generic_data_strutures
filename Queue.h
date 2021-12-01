typedef struct Queue Queue;

Queue *Queue_alloc(int length);
void   Queue_free(Queue *queue);
int    Queue_isEmpty(Queue *queue);
int    Queue_isFull(Queue *queue);
int    Queue_getLength(Queue *queue);
void   Queue_push(Queue *queue, void *element);
void  *Queue_pop(Queue *queue);
void  *Queue_begin(Queue *queue);
void  *Queue_end(Queue *queue);

int    Queue_in(Queue *queue, void *element, int (*comp)(void*,void*));
void   Queue_print(Queue *queue, void (*print)(void *));