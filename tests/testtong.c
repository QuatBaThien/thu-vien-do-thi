#include"library/graph_by_jrb_with_ID_total.h"

int main(){
    FILE* fptr = fopen("../testcase.txt","r"); if(fptr == NULL) return 0;
    int n, m;
    int id1, id2;
    double weight;
    int i;
    fscanf(fptr, "%d %d\n", &n, &m);
    Graph g = createGraph();
    for(i = 0; i< m; i++){
        fscanf(fptr, "%d %d %lf\n", &id1, &id2, &weight);
        addEdgeNew(g, id1, id2, weight, 1);
        addVertex(g, id1, (char*)id1);
        addVertex(g, id2, (char*)id2);
    }
   

    printf("DFS tu 0:\n");
    DFS(g, 0, -1, PrintVertex);
    printf("\nBFS tu 0:\n");
    BFS(g, 0, -1, PrintVertex);
    printf("\n");
    getComponents(g, n);
    int s, t;
    printf("\nNHap diem di va diem den :\n"); scanf("%d %d",&s, &t);
    int prev[100];
    double w = shortestPath_s_To_t(g, s, t, prev);
    printf("Dijkstra :\n");
    w = shortestPath_s_To_t(g, s, t, prev);
    if(w == INFINITIVE_VALUE) printf("Khong ton tai duong di tu %d den %d\n", s, t);
    else {
        printf("Duong di ngan nhat tu %d den %d la \n", s, t);
        printf("Do dai = %.0lf \n", w);
        printf("Duong di :\n"); i = t;
        do{
           printf("%d <--- ", i);    //v3 
            i = prev[i];                       
        }
        while(i != s);
        printf("%d", s);
    // }
    }
    fclose(fptr);
    //dropGraph(g);

    
}