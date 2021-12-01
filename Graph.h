typedef struct Graph Graph;
typedef struct Vertex Vertex;
typedef struct Edge Edge;

struct Graph {
    int n;
    Vertex *first;
    int (*compar)(void*, void*);
};

struct Vertex {
    void   *value;
    Vertex *next;
    Edge   *edge;
    int vizited;
};

struct Edge {
    Vertex *end;
    Edge   *next;
};

Graph *Graph_alloc(int (*compar)(void*,void*));
void   Graph_free(Graph *g);

void   Graph_addVertex(Graph *g, void *value);
void   Graph_addEdge(Graph *g, void *value1, void *value2);

Vertex *Graph_findVertex(Graph *g, void *value);
Edge   *Graph_findEdge(Graph *g, void *value1, void *value2);

Vertex *Graph_removeVertex(Graph *g, void *value);
Edge   *Graph_removeEdge(Graph *g, void *value1, void *value2);

Vertex **Graph_dfs(Graph *g, void *startValue);
Vertex **Graph_bfs(Graph *g, void *value);

void Graph_print(Graph *g, void (*print)(void *));
