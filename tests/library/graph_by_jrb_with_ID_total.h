#include <stdio.h>
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include <string.h>
#include <stdlib.h>
#define INFINITIVE_VALUE 10000
#define true 1
#define false 0

typedef struct 
{
    JRB edges;
    JRB verticles;
}Graph;
// KHOI TAO DO THI
Graph createGraph(){
    Graph g;
    g.edges = make_jrb();
    g.verticles = make_jrb();
    return g;
}
// THEM NUT VAO DO THI
void addVertex(Graph g, int id, char * name){
    //kiem tra xem dinh do co ton tai tren do thi g hay chua 
    JRB node =  jrb_find_int(g.verticles, id);
    {
        if(node == NULL){  // dinh chua ton tai
            jrb_insert_int(g.verticles, id, new_jval_s((name)));
        }
    }
}
//THEM NUT VAO DO THI - DUNG CHO TRUONG HOP DINH KO CAN GAN TEN CU THE
void addVertex_without_name(Graph g, int id){
    JRB node =  jrb_find_int(g.verticles, id);
    {
        if(node == NULL){  // dinh chua ton tai
            jrb_insert_int(g.verticles, id, (Jval)id);
        }
    }

}
//LAY GIA TRI CANH
double getEdgeValue(Graph graph, int v1, int v2){
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if(node ==  NULL) return INFINITIVE_VALUE;

    tree = (JRB)jval_v(node->val);
    node =  jrb_find_int(tree, v2);
    if(node == NULL) // v2 ko ke voi v1
    return INFINITIVE_VALUE; // graph ko co canh v1 v2
    else return jval_d(node->val); // truy cap vao truong val de lay trong so cua  canh v1, v2

}
//THEM CANH VAO DO THI
void addEdge(Graph graph, int v1, int v2, double weight){
    JRB node, tree;
    if(getEdgeValue(graph, v1, v2) == INFINITIVE_VALUE){ // neu graph chua co canh v1,v2
        node = jrb_find_int(graph.edges, v1); // tim dinh v1 tren tap canh graph.edges
        if(node == NULL){
            tree = make_jrb();
            jrb_insert_int(graph.edges, v1, new_jval_v(tree)); // them v1 vao graph.edges
        }
        else // graph.edges  da co dinh v1
           tree = (JRB) jval_v(node->val); // tree : cay do den cua dinh v1
           // them v2 vao cay do den cua dinh v2
           jrb_insert_int(tree, v2, new_jval_d(weight));

        
    }
}
//THEM CANH VA DINH VAO DO THI - DUNG TRONG TRUONG HOP DINH KO CAN GAN TEN CU THE
void addEdge_Vertex(Graph graph, int v1, int v2, double weight){
    JRB node, tree;
    if(getEdgeValue(graph, v1, v2) == INFINITIVE_VALUE){ // neu graph chua co canh v1,v2
        node = jrb_find_int(graph.edges, v1); // tim dinh v1 tren tap canh graph.edges
        if(node == NULL){
            tree = make_jrb();
            jrb_insert_int(graph.edges, v1, new_jval_v(tree)); // them v1 vao graph.edges
        }
        else // graph.edges  da co dinh v1
           tree = (JRB) jval_v(node->val); // tree : cay do den cua dinh v1
           // them v2 vao cay do den cua dinh v2
           jrb_insert_int(tree, v2, new_jval_d(weight));
   
    }
    addVertex_without_name(graph, v1);
    addVertex_without_name(graph, v2);
}
//THÊM CẠNH VÀO ĐỒ THỊ VÔ HƯỚNG
void addEdge_Vertex_WD(Graph graph, int v1, int v2, double weight){
    addEdge(graph, v1, v2, weight);
    addEdge(graph, v2, v1, weight);
    addVertex_without_name(graph, v1);
    addVertex_without_name(graph, v2);
}
void addEdge_WD(Graph graph, int v1, int v2, double weight){
    addEdge(graph, v1, v2, weight);
    addEdge(graph, v2, v1, weight);
    // addVertex_without_name(graph, v1);
    // addVertex_without_name(graph, v2);
}
//LAY NUT VA ID
JRB getfullItemVertex(Graph g, int id){
    JRB node = jrb_find_int(g.verticles, id);
    if(node == NULL) 
    return  NULL;
    else return  node;  //jval_s(node->val);
}
char *getVertex(Graph g, int id){
    JRB node = jrb_find_int(g.verticles, id);
    if(node == NULL) 
    return  NULL;
    else return jval_s(node->val);
}

// BAC VAO
int indegree(Graph graph,  int v, int *output){      // tim bac vao cua dinh
    JRB tree, node;
    int total = 0;
    jrb_traverse(node, graph.edges){
        tree =  (JRB) jval_v(node->val);
        if(jrb_find_int(tree, v)){
            output[total] == jval_i(node->key);
            total ++;
        }
    }
    return total;
}

// int indegree1(Graph graph,  int v, int *output){      // tim bac vao cua dinh
//     JRB tree, node;
//     int total = 0;
//     jrb_traverse(node, graph.edges){
//         tree =  (JRB) jval_v(node->val);
//         if(jrb_find_int(tree, v)){
//             output[total] == jval_i(node->key);
//             total ++;
//             if(getEdgeValue(graph, output[total-1], v)== 0) total--;
//         }
//     }
//     return total;
// }
void addEdgeNew(Graph graph, int v1, int v2, double weight,int flag)
{
    JRB node, tree;
    if (getEdgeValue(graph, v1, v2) == INFINITIVE_VALUE)
    {
        node = jrb_find_int(graph.edges, v1);
        if (node == NULL)
        {
            tree = make_jrb();
            jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        }
        else
            tree = (JRB)jval_v(node->val);

        jrb_insert_int(tree, v2, new_jval_d(weight));
    }

    if(flag)
    {
        if(getEdgeValue(graph, v2, v1) == INFINITIVE_VALUE)
            addEdgeNew(graph, v2, v1, weight,0);
    }
}
// BAC RA
int outdegree(Graph graph, int v, int *output){   // tim bac ra cua dinh
    int total = 0;
    JRB node  = jrb_find_int(graph.edges, v);
    if(node == NULL) return 0;
    JRB tree =  (JRB)jval_v(node->val);
    jrb_traverse(node, tree)
    {
        output[total] =  jval_i(node->key);
        total++;
    }
    return total;
    
} 
//HÀM KIỂM TRA XEM CÓ TỒN TẠI CẠNH TRONG ĐỒ THỊ HAY KHÔNG


int hasEdge(Graph graph, int v1, int v2)
{
    JRB node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
        return 0;
    JRB tree = (JRB)jval_v(node->val);
    if (jrb_find_int(tree, v2) == NULL)
        return 0;
    else
        return 1;
}

// GIAI PHONG BO NHO 
void dropGraph(Graph graph){
    JRB node, tree;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.verticles);
}
// KIEM TRA XEM DO THI CO DAG HAY KO ( DAG LA KO CO CHU TRINH )
//Do thi khong co chu trinh va co huong
int DFS_DAG(Graph graph, int start)
{
    int visited[1000] = {};
    int output[100];
    Dllist node, stack;

    stack = new_dllist();
    dll_append(stack, new_jval_i(start));

    while (!dll_empty(stack))
    {
        node = dll_last(stack);
        int u = jval_i(node->val);
        dll_delete_node(node);

        if (!visited[u])
        {
            visited[u] = 1;
            int n = outdegree(graph, u, output);
            for (int i = 0; i < n; i++)
            {
                int v = output[i];
                if (v == start)
                    return 0;
                if (!visited[v])
                    dll_append(stack, new_jval_i(v));
            }
        }
    }
    return 1;
}

int DAG(Graph graph) // Khong cho chu trinh return 1
{
    int start, notCycles;
    JRB node;

    jrb_traverse(node, graph.verticles)
    {
        start = jval_i(node->key);
        // printf("Goi DFS xuat phat tu dinh %d\n", start);
        notCycles = DFS_DAG(graph, start);
        if (notCycles == 0)
            return 0;
    }
    return 1;
}


//HÀM KIỂM TRA XEM ĐỒ THỊ VÔ HƯỚNG CÓ CHU TRÌNH HAY KHÔNG
int DFS_Cycle(Graph graph, int start){
    int visited[1000] = {};
    int n, output[100], i, u , v;
    int color[1000] = {0}; //khởi tạo tất cả đỉnh là màu trắng _ tức là ch dc thăm
    Dllist node, stack;
    stack = new_dllist();
    dll_append(stack, new_jval_i(start));
    color[start] = 1; // dinh dc dua vao stack thi co màu xám
    while(! dll_empty(stack)){
        node = dll_last(stack);
        u = jval_i(node->val);
        dll_delete_node(node);
        if(color[u] == 1 || color[u] == 2){
            //PrintVertex(u);
           // visited[u] =  1;
            color[u]++; // ghé thăm và đã ra khỏi stack r thì màu đen
            n = outdegree(graph, u, output);
            for(i =0; i < n ; i++){
                v = output[i];
                // if(v == start) return 0; //cycle deleted
                if(color[v] == 0|| color[v] == 1) {
                    dll_append(stack, new_jval_i(v));
                    color[v] ++; // đưa vào stack sẽ mang màu xám
                }
            }
        }
    }
    for(int i = 0 ; i< 10; i++){
      //  printf("%d\n", color[i]);
       if(color[i] == color[start] + 1 && color[i]!= start) return 1; // tồn tại cycle
    }
    return 0; // ko tồn tại cycle
}





int count;
// THUAT TOAN DIJSKTRA
double shortestPath_s_To_t(Graph g, int s, int t, int* p ){
    double d[1000], k[1000], min, w;
    int n, output[100], i, u ,v;
    Dllist ptr, queue;
    JRB node;
    //printf("a");
    for (i = 0;  i <1000; i++){
        d[i] = INFINITIVE_VALUE;
        k[i] =  0; // chua tim duoc duong di tu s den i
    }
    d[s] = 0; p[s] = s;
    // bo sung tat ca dinh cua do thi vao hang doi Q
    queue = new_dllist();
    jrb_traverse(node, g.verticles)
       dll_append(queue, new_jval_i(jval_i(node->key)));
       while( !dll_empty(queue)){
            //printf("a");
            min =  INFINITIVE_VALUE +1;
            dll_traverse(ptr, queue)
            {
                 v = jval_i(ptr->val);
                 if(min > d[v]){
                     min = d[v];
                     node = ptr; 
                     u = v;
                 }
            }
            k[u] = 1; // da tim dc ddnn tu s den u
            dll_delete_node((Dllist)node);

            if(u == t) break;
            n = outdegree(g, u, output);
            for( i = 0; i < n; i++){
                v = output[i];
                if(k[v] == 0){
                    w = getEdgeValue(g, u, v);
                    if(d[v] > d[u] + w){
                        d[v] = d[u] + w;
                        p[v]  = u;
                    }
                }
            }

       }
    return d[t];
}
//HAMĐẾM SỐ DỈNH CỦA ĐỒ THỊ

int getNumOfV(Graph graph)
{
    int count = 0;
    JRB node;
    jrb_traverse(node, graph.verticles)
        count++;
    return count;
}


//ĐÉM SÓ THÀNH PHẦN LIÊN THÔNG VÀ LIỆT KÊ THÀNH PHẦN LIEN THONG CỦA ĐỒ THI
void BFS_Connected(Graph g, int start, int* id, int lt){
    int n, output[100], i , u, v;
    Dllist node, queue;

    queue = new_dllist();
    dll_append(queue, new_jval_i(start));
    while(! dll_empty(queue))
    {
        node = dll_first(queue);
        u = jval_i(node->val);
        dll_delete_node(node);
        if(id[u] == -1)
        {
            id[u] = lt;
            n = outdegree(g, u, output);
            for(int i = 0; i< n; i++){
                v = output[i];
                if(id[v] == -1)
                    dll_append(queue, new_jval_i(v));
            }
        }
    }
}

//HAM DEM SO THANH PHAN LIEN THONG CUA DO THI
int getComponents(Graph g, int ver_num){
    int lt = 0;
    int id[1000];
   // int n = ver_num;
    int n = getNumOfV(g);
    for(int i= 0; i <n; i++) id[i] = -1;
    for(int i = 0; i< n; i++)
    if(id[i] == -1)// if !visited[i]
    {
        lt++; 
        //goi thu tuc BFS lan thu lt:
        BFS_Connected(g, i , id ,lt);
    }
    if(lt == 1) printf("Do thi vo huong da cho lien thong \n");
    else
    {
        printf("Do thi vo huong da cho ko lien thong \n");
        printf("So thanh phan lien thong cua do thi : %d\n", lt);
        for(int i = 1; i <= lt; i++){
            printf("Cac dinh thuoc thanh phan lien thong thu %d : ", i);
            for(int j = 0; j <= n ; j++){
                if(id[j] == i) printf("%4d", j);
            }
            printf("\n");
        }
    }
    return lt;
}
int adjacent(Graph graph, int v1, int v2)
{
JRB node, tree;
//kiểm tra xem đồ thị g có chứa đỉnh v1 hay không:
node = jrb_find_int(graph.edges, v1);
if (node==NULL) return 0; //g ko co dinh v1
/* đồ thị g có v1: tiếp tục lấy trường value (chứa danh sách kề) của đỉnh v1 để kiểm tra xem
v1 có kề với v2 không: */
tree = (JRB) jval_v(node->val);
if (jrb_find_int(tree, v2)== NULL)
return 0;
else return 1;
}

// THUAT TOAN TO MAU DO THI
int TO_Mau(Graph g, int n, int* m, int start){ //Xu ly de cho ra ket qua vao mang m[]  
    int kt;
    int so_mau = 0;
    for(int i = start;i <=n ;i++)
        if(!m[i]) {
            so_mau++; //Dem so mau
            m[i] =so_mau;
            for(int j = i+1; j<=n ; j++) //Kiem tra xem nhung dinh nao co the gan bang mau sm nua khong
                if((getEdgeValue(g, i, j) == INFINITIVE_VALUE)&&(m[j] == 0)){
                    kt=1;
                    for(int k = i+1; k < j; k++)
                        if(getEdgeValue(g, i, j) != INFINITIVE_VALUE&&(m[i]==m[k])){
                            kt=0;
                            break;
                        }
                    if(kt==1) m[j] = so_mau;
                }                   
        }
    return so_mau;
}
void printToGraphViz(Graph g, int verte_num, int ed_num){
    FILE* output = fopen("output.dot", "w+");
    fprintf(output, "graph dothi\n {");
    for(int i = 0; i< verte_num; i++){
        for(int j = i+1; j< verte_num; j++){
            if(hasEdge(g, i, j) == 1)
            fprintf(output, "%d -- %d;\n", i, j);
        }
    }
    fprintf(output, "}");
    fclose(output);
}
//BFS
int BFS_Shortest_Path(Graph graph,int start, int stop, int*truoc){
//int find[1000];
// if(shortestPath_s_To_t(graph , start, stop ,find) == INFINITIVE_VALUE){
//     return 0; // ko co duong di
// }
int visited[1000] = {};
int n, output[100], i, u, v;
Dllist node, queue;
queue = new_dllist();
dll_append(queue, new_jval_i(start)); //thêm phần tử start vào queue
while ( !dll_empty(queue) )
{
node = dll_first(queue);
u = jval_i(node->val);
dll_delete_node(node);
if (!visited[u]) //nếu u chưa được thăm
{
visited[u] = 1;
if ( u == stop ) return 1; //đỉnh u = stop  kết thúc BFS
n = indegree(graph, u, output);
for (i=0; i<n; i++) //xét lần lượt các đỉnh kề với đỉnh u
{
v = output[i];
if (!visited[v]){
    truoc[v] = u; 
dll_append(queue, new_jval_i(v)); //thêm v vào queue nếu v chưa được thăm
}
}
}
}
return 1;
}

void PrintVertex( int v){
    printf("%4d", v);
    //printf("%d : %s\n", jval_i(getfullItemVertex(g, per[i].id)->key), jval_s(getfullItemVertex(g, per[i].id)->val));
}

void BFS(Graph graph, int start, int stop, void (*func)(int)){
    
int visited[1000] = {};
int n, output[100], i, u, v;
Dllist node, queue;
queue = new_dllist();
dll_append(queue, new_jval_i(start)); //thêm phần tử start vào queue
while ( !dll_empty(queue) )
{
node = dll_first(queue);
u = jval_i(node->val);
dll_delete_node(node);
if (!visited[u]) //nếu u chưa được thăm
{
func(u);
visited[u] = 1;
if ( u == stop ) return; //đỉnh u = stop  kết thúc BFS
n = outdegree(graph, u, output);
for (i=0; i<n; i++) //xét lần lượt các đỉnh kề với đỉnh u
{
v = output[i];
if (!visited[v]) //thêm v vào queue nếu v chưa được thăm
dll_append(queue, new_jval_i(v));
}
}
}
}
// DFS
void DFS(Graph graph, int start, int stop, void (*func)(int)){

int visited[1000] = {};
    int n, output[100], i, u , v;
    Dllist node, stack;
    stack = new_dllist();
    dll_append(stack, new_jval_i(start));
    while(! dll_empty(stack)){
        node = dll_last(stack);
        u = jval_i(node->val);
        dll_delete_node(node);
        if(!visited[u]){
            func(u);
            visited[u] =  1;
            if ( u == stop ) return; 
            //printf("%4d", u);
            n = outdegree(graph, u, output);
            for(i =0; i < n ; i++){
               // printf("%d", output[i]);
                v = output[i];
                //if(v == start) return 0; //cycle detected
                if(!visited[v]) dll_append(stack, new_jval_i(v));
            }
            //printf("\n");
        }
    }
    return ;
}
//DFS LƯU GIỮ PATH
void swapArray(int arr[], int cnt)
{
    for (int i = 0; i < cnt / 2; i++)
    {
        int c = arr[i];
        arr[i] = arr[cnt - i - 1];
        arr[cnt - i - 1] = c;
    }
}
int DFS_PATH(Graph graph, int start, int stop, int *path)
{
    int visited[1000] = {};
    int output[100];
    int cnt = 0, u;
    int save[1000];
    Dllist stack = new_dllist();

    dll_append(stack, new_jval_i(start));

    while (!dll_empty(stack))
    {
        Dllist node = dll_last(stack);
        u = jval_i(node->val);
        dll_delete_node(node);

        if (!visited[u])
        {
            visited[u] = 1;
            if (u == stop)
                break;
            int n = outdegree(graph, u, output);
            for (int i = 0; i < n; i++)
            {
                int v = output[i];
                if (!visited[v])
                {
                    save[v] = u;
                    dll_append(stack, new_jval_i(v));
                }
            }
        }
    }
    if (u != stop)
        return 0;
    else
    {
        int i = stop;
        path[cnt++] = i;
        while (i != start)
        {
            i = save[i];
            path[cnt++] = i;
        }
        swapArray(path, cnt);
    }
    return cnt;
}
//FATHER CODE
void FatherCode(Graph g, int n, int *code){
    int out[n]; int tmp;
    int output[n];
    for(int i = 0; i < n; i++){
        int m = outdegree(g, i, output);
        double min = n;
        
        for(int j = 0 ; j < m; j++){
            if(shortestPath_s_To_t(g, 0, output[j], out ) < min){
            min = shortestPath_s_To_t(g, 0, output[j], out );
            tmp = j;
            }
        }
        
        code[i] = output[tmp];
    }
}

//THUAT TOAN DEM SO THANH PHAN LIEN THONG MANH

int check_lienthongmach(Graph graph)
{
   JRB node;
   int bool = true;
   int check = 0;


   jrb_traverse(node, graph.verticles)
   {
      JRB node_temp;

      // printf("%d ",jval_i(node->key));

      jrb_traverse(node_temp, graph.verticles)
      {
         if (jval_i(node->key) != jval_i(node_temp->key))
         {
            int out[INFINITIVE_VALUE] = {};
            int  v1 = jval_i(node->key);
            int v2 = jval_i(node_temp->key);
            // printf("%d %d\n",v1, v2);

            int check = DFS_PATH(graph, v1, v2, out);
            
            if (check < 2)
            {
               bool = false;
               break;
            }
         }
      }

      if (bool == false)
      {
         break;
      }
   }
   return bool;
}
