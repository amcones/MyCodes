#include<iostream>
#include<queue>
using namespace std;

typedef struct tagGNode {//结点定义
	int v;//顶点编号
	struct tagGNode* next;//指向边的终端结点的指针
}GNode;

typedef GNode* GLink;//结点的指针

typedef struct tagGraph {
	bool digraph;//有/无向图标志
	int Vcnt;//顶点数
	int Ecnt;//边数
	GNode* adj;//顶点指针
	bool* visited;//访问标记,假未真已
}Graph;

void Initialize(Graph *graph, int V, bool digraph)
{
	int i;
	graph->adj = new GNode[V];
	graph->visited = new bool[V];
	graph->digraph = digraph;
	graph->Vcnt = V;
	graph->Ecnt = 0;
	for (i = 0; i < V; i++)
	{
		graph->adj[i].next = NULL;
		graph->adj[i].v = i;
		graph->visited[i] = false;
	}
}

void Insert(Graph* graph, int v, int w)
{
	GNode *newNode1, *newNode2;
	newNode1 = new GNode;
	newNode1->v = w;
	newNode1->next = graph->adj[v].next;
	if (graph->digraph == false && v != w)
	{
		newNode2 = new GNode;
		newNode2->v = v;
		newNode2->next = graph->adj[w].next;
		graph->adj[w].next = newNode2;
	}
	graph->adj[v].next = newNode1;
	graph->Ecnt++;
}

int FirstAdjVex(Graph* graph, int v)
{
	GLink t;
	if (graph == NULL)return -1;
	t = graph->adj[v].next;
	if (t)return t->v;
	else return -1;
}

int NextAdjVex(Graph* graph, int v, int w)
{
	GLink t;
	if (graph == NULL)return -1;
	t = graph->adj[v].next;
	while (t)
	{
		if (t->v == w && t->next)
			return t->next->v;
		t = t->next;
	}
	return -1;
}

void BFS(Graph *graph, int v)
{
	int i, j;
	queue<int> q;
	graph->visited[v] = true;
	q.push(v);
	while (q.empty() != true)
	{
		i = q.front();
		q.pop();
		cout << i << "号顶点出队"<<endl;
		for (j = FirstAdjVex(graph, i); j != -1; j = NextAdjVex(graph, i, j))
		{
			if (graph->visited[j] == 0)
			{
				graph->visited[j] = 1;
				q.push(j);
				cout << j << "号顶点入队"<<endl;
			}
		}
	}
}

int main()
{
	Graph graph;
	int v,e;
	cin >> v>>e;
	Initialize(&graph, v, false);
	int a, b;
	for (int i = 0; i < e; i++)
	{
		cin >> a >> b;
		Insert(&graph, a, b);
	}
	cout << FirstAdjVex(&graph,0);
	BFS(&graph, 0);
	return 0;
}