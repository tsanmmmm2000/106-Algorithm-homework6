#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES_NUMBER 1001
#define MAX_EDGES_NUMBER 10001
#define TRUE 1
#define FALSE 0
#define START 0
#define DEFAULT_VALUE -1

struct set_blob {
    int key_set[MAX_VERTICES_NUMBER];
    int parent_set[MAX_VERTICES_NUMBER];
    int visited_set[MAX_VERTICES_NUMBER];
    int edge_set[MAX_VERTICES_NUMBER][MAX_VERTICES_NUMBER];
};

struct edge {
    int vertex_one;
    int vertex_two;
};

struct mst_result {
    struct edge edge_set[MAX_EDGES_NUMBER];
    int edge_size;
    int option_num;
    int sum;
};

struct set_blob sb;

int find_max(int a, int b) {
    return (a > b) ? a : b;
}

int find_min(int a, int b) {
    return (a < b) ? a : b;
}

int edge_compare(const void *a, const void *b) {
    struct edge *edge_a = (struct edge *)a;
    struct edge *edge_b = (struct edge *)b;
    if (edge_a->vertex_one > edge_b->vertex_one 
        || (edge_a->vertex_one == edge_b->vertex_one && edge_a->vertex_two > edge_b->vertex_two)) {
        return 1;
    } else if (edge_a->vertex_one < edge_b->vertex_one 
        || (edge_a->vertex_one == edge_b->vertex_one && edge_a->vertex_two < edge_b->vertex_two)) {
        return -1;
    } else {
        return 0;
    }
}

void init_set() {
    for (int i = 0; i < MAX_VERTICES_NUMBER; i++) {
        for (int j = 0; j < MAX_VERTICES_NUMBER; j++) {
            sb.edge_set[i][j] = DEFAULT_VALUE;
        }
        sb.key_set[i] = (i == START) ? DEFAULT_VALUE : INT_MAX;
        sb.parent_set[i] = DEFAULT_VALUE;
        sb.visited_set[i] = FALSE;
    }
}

void add_edge(int vertex_one, int vertex_two, int weight) {
    if (sb.edge_set[vertex_one][vertex_two] == DEFAULT_VALUE) {
        sb.edge_set[vertex_one][vertex_two] = weight;
        sb.edge_set[vertex_two][vertex_one] = weight;        
    } else {
        if (weight < sb.edge_set[vertex_one][vertex_two]) {
            sb.edge_set[vertex_one][vertex_two] = weight;
            sb.edge_set[vertex_two][vertex_one] = weight;
        }
    }
}

int extract_min(int vertex_num) {
    int min = INT_MAX;
    int vertex = DEFAULT_VALUE;
    for (int i = 0; i < vertex_num; i++) {       
        if (sb.visited_set[i] == FALSE && sb.key_set[i] < min) {
            min = sb.key_set[i];
            vertex = i;
        }
    }
    return vertex;
}

struct mst_result prim(int vertex_num) {

    struct mst_result result;
    result.edge_size = 0;
    result.sum = 0;

    for (int i = 0; i < vertex_num; i++) {
        int vertex = extract_min(vertex_num);
        sb.visited_set[vertex] = TRUE;

        if (vertex != START) {
            int index = result.edge_size;
            int parent = sb.parent_set[vertex];
            int weight = sb.edge_set[vertex][parent];      
            result.edge_set[index].vertex_one = find_min(vertex, parent);
            result.edge_set[index].vertex_two = find_max(vertex, parent);
            result.edge_size += 1;
            result.sum += weight;            
        }
        for (int j = 0; j < vertex_num; j++) {
            if (sb.visited_set[j] == FALSE && sb.edge_set[vertex][j] != DEFAULT_VALUE && sb.edge_set[vertex][j] < sb.key_set[j]) {
                sb.parent_set[j] = vertex;
                sb.key_set[j] = sb.edge_set[vertex][j];
            }
        }
    }

    qsort(result.edge_set, result.edge_size, sizeof(struct edge), edge_compare);
    
    return result;
}

int main() {
    int input_num;
    scanf("%i", &input_num);

    struct mst_result result[input_num];

    for (int i = 0; i < input_num; i++) {
        
        int vertex_num;
        int edge_num;
        int option_num;
        scanf("%d %d %d", &vertex_num, &edge_num, &option_num);

        init_set();

        for (int j = 0; j < edge_num; j++) {
            int vertex_one;
            int vertex_two;
            int weight;
            scanf("%d %d %d", &vertex_one, &vertex_two, &weight);
            add_edge(vertex_one, vertex_two, weight);
        }
        result[i] = prim(vertex_num);
        result[i].option_num = option_num;
    }

    for (int i = 0; i < input_num; i++) {
        if (result[i].option_num == 1) {
            for (int j = 0; j < result[i].edge_size; j++) {
                printf("%d %d\n", result[i].edge_set[j].vertex_one, result[i].edge_set[j].vertex_two);
            }
        }
        printf("%d\n", result[i].sum);
    }
}
