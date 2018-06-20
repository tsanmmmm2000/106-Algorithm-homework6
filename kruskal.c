#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES_NUMBER 1000
#define MAX_EDGES_NUMBER 10000

struct edge {
   int vertex_one;
   int vertex_two;
   int weight;
};

struct set_blob {
    int vertex_set[MAX_VERTICES_NUMBER];
    int rank_set[MAX_VERTICES_NUMBER];    
    struct edge edge_set[MAX_EDGES_NUMBER];
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
    return edge_a->weight - edge_b->weight;
}

void clear_set(int vertex_num, int edge_num) {
    for (int i = 0; i < vertex_num; i++) {
        sb.vertex_set[i] = 0;
        sb.rank_set[i] = 0;               
    }

    for (int i = 0; i < edge_num; i++) {
        sb.edge_set[i].vertex_one = 0;
        sb.edge_set[i].vertex_two = 0;
        sb.edge_set[i].weight = 0;
    }    
}

void add_edge(int index, int vertex_one, int vertex_two, int weight) {
    sb.edge_set[index].vertex_one = vertex_one;
    sb.edge_set[index].vertex_two = vertex_two;
    sb.edge_set[index].weight = weight;    
}

void make_vertex(int vertex) {
    sb.vertex_set[vertex] = vertex;
}

int find_root_vertex(int vertex) {
    int parent = sb.vertex_set[vertex];
    if (parent != vertex) {
        sb.vertex_set[vertex] = find_root_vertex(parent);
    }
    return sb.vertex_set[vertex];
}

void union_vertex(int vertex_one, int vertex_two) {
    int vertex_one_rank = sb.rank_set[vertex_one];
    int vertex_two_rank = sb.rank_set[vertex_two];    
    if (vertex_one_rank < vertex_two_rank) {
        sb.vertex_set[vertex_one] = vertex_two;
    } else {
        sb.vertex_set[vertex_two] = vertex_one;
        if (vertex_one_rank == vertex_two_rank) {
            sb.rank_set[vertex_one] += 1;
        }
    }
}

struct mst_result kruskal(int vertex_num, int edge_num) {
    
    struct mst_result result;    
    result.edge_size = 0;
    result.sum = 0;
    
    for (int i = 0; i < vertex_num; i++) {
        make_vertex(i);
    }

    qsort(sb.edge_set, edge_num, sizeof(struct edge), edge_compare);

    for (int i = 0; i < edge_num; i++) {
        int vertex_one = sb.edge_set[i].vertex_one;
        int vertex_two = sb.edge_set[i].vertex_two;
        int vertex_one_root = find_root_vertex(vertex_one);
        int vertex_two_root = find_root_vertex(vertex_two);
        if (vertex_one_root != vertex_two_root) {
            int weight = sb.edge_set[i].weight;
            int index = result.edge_size;
            result.edge_set[index].vertex_one = find_min(vertex_one, vertex_two);
            result.edge_set[index].vertex_two = find_max(vertex_one, vertex_two);
            result.edge_set[index].weight = weight;            
            result.edge_size += 1;
            result.sum += weight;
            union_vertex(vertex_one_root, vertex_two_root);
        }
    }
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

        for (int j = 0; j < edge_num; j++) {
            int vertex_one;
            int vertex_two;
            int weight;
            scanf("%d %d %d", &vertex_one, &vertex_two, &weight);
            add_edge(j, vertex_one, vertex_two, weight);
        }
        result[i] = kruskal(vertex_num, edge_num);
        result[i].option_num = option_num;
        clear_set(vertex_num, edge_num);
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
