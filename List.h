typedef struct List List;

/** Cria uma nova lista */
List *List_alloc();

/** Destroi a lista liberando-a da memoria */
void List_free(List *list);

/** Insere um elemento no inicio da lista */
void List_insertBegin(List* list, void *value);

/** Insere um elemento no final da lista */
void List_insertEnd(List* list, void *value);

/** Remove um elemento no inicio da lista */
void *List_removeBegin(List* list);

/** Remove um elemento no final da lista */
void *List_removeEnd(List* list);

/** Busca e remove um elemento especifico na lista, e retorna este elemento.
 *  Parâmetros:
 *  - list:    uma lista, 
 *  - value:   valor usado como referencia para a busca,
 *  - compar:  ponteiro para uma funcao que compara dois elementos.
 *             Esta funcao e' chamada repetidamente para comparar o 
 *             parâmetro 'value' com os elementos da lista.
 * 
 *             Deve seguir o seguinte prototipo: 
 *                       int compar(void* p1, void* p2);
 *  
 *             Usando dois ponteiros como argumentos (ambos convertidos 
 *             para void *).
 *             A funcao define a igualdade entre os elementos retornando:
 *                  +-----------------+-----------------------+
 *                  | VALOR RETORNADO |        DESCRICAO      |
 *                  +-----------------+-----------------------+
 *                  |        1        | o primeiro e' maior   |
 *                  |        0        | os valores sao iguais |
 *                  |       -1        | o segundo e' maior    |
 *                  +-----------------+-----------------------+
 */
void *List_findAndRemove(List* list, void *value, int (*compar)(void*, void*) );

/** Busca um elemento especifico na lista e retorna este elemento. Tem
 *  o funcionamento semelhante a funcao List_findAndRemove, mas não
 *  remove o elemento buscado.
 */
void *List_find(List* list, void *value, int (*compar)(void*, void*) );

/** Retorna o tamanho da lista */
int List_getLength(List *list);

/** Imprime os valores da lista.
 *  Parametros:
 *  - list: uma lista,
 *  - print: ponteiro para uma funcao que imprime um elemento.
 *           Esta funcao e' chamada repetidamente para imprimir todos 
 *           os elementos da lista.
 * 
 *           Deve seguir o seguinte prototipo: 
 *                     void print (void* p);
 *  
 *           Usando um ponteiro como argumento (convertido para void *).
 */
void  List_print(List *list, void (*print)(void *));

/** Recebe duas listas como parametro e retorna uma nova lista com a
 *  uniao delas 
 */
List *List_concatenate(const List *list_a, const List *list_b);

/** Recebe uma lista como parametro e retorna a uma nova lista ordenada. Usa
 *  uma funcao de comparacao semelhante a presente na funcao List_findAndRemove.
 */
List *List_sort(List *list, int (*compar)(void*, void*) );

/** Insere o elemento value na lista list de forma ordenada Usa uma funcao de 
 *  comparacao semelhante a presente na funcao List_findAndRemove.
 */
void List_insertSorted(List *list, void *value, int (*compar)(void*, void*) );