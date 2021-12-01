#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "Queue.h"

Graph *Graph_alloc(int (*compar)(void*,void*)) {
	Graph *g = NULL;

	if (compar) {
		g = malloc(sizeof(Graph));
		g->n = 0;
		g->compar = compar;
		g->first = NULL;
	}

	return g;
}

void Graph_free(Graph *g) {
	Edge *e, *tmp_e;
	Vertex *v, *tmp_v;

	if (g) {
		v = g->first;
		while (v) {
			e = v->edge;
			while (e) {
				tmp_e = e->next;
				free(e);
				e = tmp_e;
			}
			tmp_v = v->next;
			free(v);
			v = tmp_v;
		}
	}
}

static Vertex *Graph_newVertex(void *value) {
	Vertex *new_v = NULL;
	if (value) {
		new_v = malloc(sizeof(Vertex));
		new_v->value = value;
		new_v->edge = NULL;
		new_v->next = NULL;
		new_v->vizited = 0;
	}
	return new_v;
}

void Graph_addVertex(Graph *g, void *value) {
	Vertex *tmp;

	if (g && value) {
		if (g->n == 0)
			g->first = Graph_newVertex(value);
		else {
			tmp = g->first;
			g->first = Graph_newVertex(value);
			g->first->next = tmp;
		}
		g->n++;
	}
}

Vertex *Graph_findVertex(Graph *g, void *value) {
	Vertex *v;
	if (g && value) {
		v = g->first;
		while (v) {
			if (g->compar(v->value, value) == 0)
				break;
			v = v->next;
		}
	}
	return v;
}

Edge *Graph_findEdge(Graph *g, void *val0, void *val1) {
	Vertex *v = NULL;
	Edge   *e = NULL;
	
	if (g && val0 && val1) {
		if (v = Graph_findVertex(g, val0)) {
			e = v->edge;
	
			while (e) {
				if (g->compar(e->end->value, val1) == 0)
					return e;
				e = e->next;
			}
		}
	}

	return NULL;
}

static Edge *Graph_newEdge(Vertex *end) {
	Edge *new_e = NULL;
	if (end) {
		new_e = malloc(sizeof(Edge));
		new_e->next = NULL;
		new_e->end = end;
	}
	return new_e;
}

void Graph_addEdge(Graph *g, void *val0, void *val1) {
	Vertex *vert1 = NULL;
	Vertex *vert2 = NULL;
	Edge   *tmp_e = NULL;
	
	if (g && val0 && val1) {
		vert1 = Graph_findVertex(g, val0);
		vert2 = Graph_findVertex(g, val1);

		if (vert1 && vert2) {
			if (vert1->edge) {
				tmp_e = vert1->edge;
				vert1->edge = Graph_newEdge(vert2);
				vert1->edge->next = tmp_e;
			}
			else
				vert1->edge = Graph_newEdge(vert2);
		}
	}
}

static Vertex *Graph_notVizited(Edge *edge) {
	Edge *e = NULL;
	if (edge) {
		e = edge;
		while (e) {
			if (e->end->vizited == 0)
				return e->end;
			e = e->next;
		}
	}
	return NULL;
}

static void dfs(Vertex *v, Vertex **path, int *count) {
	Vertex *k = NULL;

	if (v) {
		v->vizited = 1;
		path[*count] = v;
		
		while (k = Graph_notVizited(v->edge)) {
			*count += 1;
			dfs(k, path, count);
		}
	}
}

Vertex **Graph_dfs(Graph *g, void *val0) {
	Vertex **path = NULL;
	Vertex *v = NULL;
	int i, count = 0;

	if (g && val0) {
		if (v = Graph_findVertex(g, val0)) {

			path = malloc(g->n * sizeof(Vertex*));

			for (i=0; i<g->n; i++)
				path[i] = NULL;

			dfs(v, path, &count);
		}
	}
	
	return path;
}

Vertex **Graph_bfs(Graph *g, void *val0) {
	Vertex **path = NULL;
	Vertex *v = NULL, *k = NULL;
	Queue  *q = NULL;
	int i, count = 0;

	if (g && val0) {
		if (v = Graph_findVertex(g, val0)) {
			
			path = malloc(g->n * sizeof(Vertex*));			
			for (i=0; i<g->n; i++)
				path[i] = NULL;

			q = Queue_create(g->n);

			v->vizited = 1;
			path[count++] = v;
			Queue_push(q, v);

			while (!Queue_isEmpty(q)) {
				v = Queue_begin(q);
				
				while (k = Graph_notVizited(v->edge)) {
					k->vizited = 1;
					path[count++] = k;
					Queue_push(q, k);
				}
				
				Queue_pop(q);
			}
		}
	}
	
	return path;
}


void Graph_print(Graph *g, void (*print)(void *)) {
    Vertex *v = NULL;
    Edge *a = NULL;
    if (g) {
        v = g->first;
        while (v) {
            printf("(v) ");
			print(v->value);
            printf(":\n\t(e)");

            a = v->edge;
			if (a == NULL)
            	printf("-> ~");

            while (a) {
				printf("-> ");
				print(a->end->value);
				printf(" ");
                a = a->next;
            }
			printf("\n");
            v = v->next;
        }
    }
}

int *predecessors(Graph *g) {
	Vertex *v = NULL, *k = NULL;
	Edge *e = NULL;
	int i=0, *pred, in=0;
	if (g) {
		for (v = g->first, i=0; v; v = v->next) {
			pred[i] = 0;
			for (k = g->first; k && k!=v; v = k->next) {
				for (e = v->edge; e; e = e->next) {
					if (v == e->end) {
						pred[i]++;
						break;
					}
				}
			}
		}
	}
	return pred;
}

Vertex **Graph_ts(Graph *g) {
	Vertex **path = NULL, **adj = NULL;
	Vertex *v = NULL, *k = NULL;
	Queue  *q = NULL;
	Edge *e = NULL;
	int i=0, j=0, *pred;

	if (g) {
		path = calloc(g->n, sizeof(Vertex*));
		pred = predecessors(g);

		q = Queue_alloc(g->n);
		for (i=0, v=g->first; v; i++, v=v->next) {
			if (pred[i] == 0)
				Queue_push(q, v);
		}

		i=0;
		while (!Queue_isEmpty(q)) {
			v = Queue_pop(q);
			path[i++] = v;

			for (e = v->edge; e; e = e->next) {
				if (v == e->end) {
					pred[i]++;
					break;
				}
			}
		}
	}
}