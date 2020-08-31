#include <iostream>
#include<queue>
using namespace std;

typedef struct GNode {//定义结点
	int v;//顶点编号
	struct GNode *next;//指向后继
};
typedef GNode *GLink;//结点指针

typedef struct Graph {//定义邻接表
	bool digraph;//无向图标志
	int Vcnt, Ecnt;
	GNode *adj;
	bool *visited;//访问标志

};
//实现邻接表基本操作
void Initialize(Graph *graph, int v, bool digraph)//初始化邻接表
{
	graph->adj = new GNode[v];//为单链表头分配空间
	graph->visited = new bool[v];
	graph->digraph = digraph;
	for (int i = 0; i < v; i++)
	{
		graph->visited[i] = false;//初始化赋值很重要
		graph->adj[i].v = i;
		graph->adj[i].next = NULL;
	}
}

void Dispose(Graph *graph)//销毁分配的空间
{
	GNode *p, *q;
	for (int i = 0; i < graph->Vcnt; i++)//销毁边结点
	{
		p = graph->adj[i].next;
		while (p != NULL)
		{
			q = p->next;
			delete p;
			p = q;
		}
	}
	for (int i = 0; i < graph->Vcnt; i++)//销毁单链表头
	{
		graph->adj[i].next = NULL;
		graph->visited[i] = false;
	}
	delete[] graph->adj;
	delete[] graph->visited;
	graph->Vcnt = graph->Ecnt = 0;
}

bool Edge(Graph *graph, int v, int w)//判断边是否存在
{
	GNode *p;
	for (p = graph->adj[v].next; p != NULL; p = p->next)//p初值为起点v的后继，在循环中顺着单链表不断指向下一个后继
	{
		if (p->v == w)//判断当前结点是否为终点w
		{
			return true;
		}
	}
	return false;
}

void Insert(Graph *graph, int v, int w)//插入边，v是起点w是终点
{
	GNode *newNode1//插入边的终点
		, *newNode2;//无向图时作为插入边的起点
	//三变量法转移指针数据
	if (!Edge(graph, v, w))
	{
		newNode1 = new GNode;
		newNode1->v = w;
		newNode1->next = graph->adj[v].next;//将起点的后继变成插入边的终点的后继
		if (graph->digraph = false && v != w)//处理无向图
		{
			newNode2 = new GNode;
			newNode2->v = v;
			newNode2->next = graph->adj[w].next;
			graph->adj[w].next = newNode2;//将边插入以插入边终点为单链表头的链表中
		}
		graph->adj[v].next = newNode1;//将边插入以插入边起点为单链表头的链表中
		/*
			有向图中，一条边只存在于以其起点为头结点的单链表中；
			无向图中，一条边同时存在于以两端点为头结点的单链表中，因此需要插入两次。
			插入操作需要四步：
			1.给插入结点分配空间
			2.给新结点赋顶点编号值
			3.将起点的后继指针赋值给新节点的后继指针
			4.让起点指向新节点
			1,3,4顺序不可颠倒，避免起点的指针数据丢失。
		*/
		graph->Ecnt++;
	}
}

int FirstAdjVex(Graph *graph, int v)
{
	GLink t;
	if (graph == NULL)
	{
		return -1;
	}
	t = graph->adj[v].next;
	if (t)
	{
		return t->v;
	}
	else
	{
		return -1;
	}
}

int NextAdjVex(Graph *graph, int v, int w)
{
	GLink t;
	if (graph == NULL)
	{
		return -1;
	}
	t = graph->adj[v].next;
	while (t)
	{
		if (t->v == w && t->next)
		{
			return t->next->v;
		}
		t = t->next;
	}
	return -1;
}

void DFS(Graph *graph, int v)
{
	int t;
	graph->visited[v] = true;
	cout << v << "结点已访问" << endl;
	for (t = FirstAdjVex(graph, v); t != -1; t = NextAdjVex(graph, v, t))
	{
		if (graph->visited[t] == false)
		{
			DFS(graph, t);
		}
	}
}

void BFS(Graph *graph, int v)
{
	queue<int> q;
	graph->visited[v] = true;
	q.push(v);
	int i,j;
	while (!q.empty())
	{
		i = q.front();
		q.pop();
		cout << i << "结点出队" << endl;
		for (j = FirstAdjVex(graph, i); j != -1; j = NextAdjVex(graph, i, j))
		{
			if (graph->visited[j] == false)
			{
				graph->visited[j] = true;
				q.push(j);
				cout << j << "结点入队" << endl;
			}
		}
	}
}

int main()
{
	Graph graph;
	int v, e, a, b;
	cin >> v >> e;
	Initialize(&graph, v, false);
	for (int i = 0; i < e; i++)
	{
		cin >> a >> b;
		Insert(&graph, a, b);
	}
	//cout << "开始执行DFS" << endl;
	//DFS(&graph, 0);
	//cout << "DFS执行结束" << endl;
	cout << "开始执行BFS" << endl;
	BFS(&graph, 0);
	cout << "BFS执行结束" << endl;
	return 0;
}

