#include <stdio.h>
#include <stdlib.h>

typedef struct DataLink {
    int vertex;
    struct DataLink* next;
} Link;

void Initialize(Link** p_adj,int* p_Ver);
void InsertVertex(Link* p_adj,int* p_Ver);
void InsertEdge(Link* p_adj,int* p_Ver);
void PrintGraph(Link* p_adj,int* p_Ver);
void BFS(Link* p_adj,int* p_Ver);
void DFS(Link* p_adj,int* p_Ver);
void enqueue(int Vertex);
int dequeue();
void push(int Vertex);
int pop();
void ReturnMemory(Link* p_adj, int Ver);
int queue[10];
int front = -1;
int rear = -1;
int stack[10];
int top = -1;
int main()
{
    Link* adj = NULL; //인접 리스트를 할당받을 변수
    int VertexC = 0; //정점의 갯수
    printf("[----- 2021041046 전설민 -----]\n"); //학번 이름 출력
    char command;
    do
    {
		printf("\n----------------------------------------------------------------\n");
		printf("                          Graph Searches                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = i      Insert Edge                  = e \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");
        scanf(" %c",&command); //명령어 입력
        switch (command)
        {
        case 'z': case 'Z':
            Initialize(&adj,&VertexC); //adj와 VertexC 초기화
            break;
        case 'i': case 'I':
            InsertVertex(adj,&VertexC); //정점 추가
            break;
        case 'e': case 'E':
            InsertEdge(adj,&VertexC); //간선 추가
            break;
        case 'p': case 'P':
            PrintGraph(adj,&VertexC); //그래프 인접 리스트 출력
            break;
        case 'B': case 'b':
            BFS(adj,&VertexC); //너비 우선 탐색
            break;
        case 'D': case 'd':
            DFS(adj,&VertexC); //깊이 우선 탐색
            break;
        case 'q': case 'Q':
            ReturnMemory(adj,VertexC); //adj의 메모리 반환
            break;
        default:
            printf("잘못된 값을 입력하셨습니다.\n");
            break;
        }
    } while (command != 'Q' && command != 'q');
    
}

void Initialize(Link** p_adj,int* p_Ver)
{
     //adj가 선언되어 있을 경우 초기화
     if(*p_adj != NULL)
     {
        for(int i = 0;i < *p_Ver;i++) //정점의 수만큼 반복
        {
            Link* p = (*p_adj)[i].next; //p_adj의 링크 메모리 반환용
            Link* temp;
            while(p != NULL) //p가 범위를 벗어날 때 까지
            {
                temp = p->next; //메모리 반환 시 p에 있는 링크가 사라지므로 기억용 변수 temp를 사용한다
                free(p); //링크 메모리 할당 해제
                p = temp; //p는 다음 링크로 이동
            }
        }
        free(*p_adj);
     }
    
    *p_adj = (Link*)malloc(sizeof(Link) * 10); //10개의 인접 리스트의 메모리 할당
    for(int i = 0;i < 10;i++)
    {
        (*p_adj)[i].next = NULL; //인접 리스트 초기화
    }

    *p_Ver = 0; //정점 갯수 초기화
    printf("초기화 성공\n");
}

void InsertVertex(Link* p_adj,int* p_Ver)
{
    if(p_adj == NULL) //인접 리스트가 초기화되지 않았을 경우
    {
        printf("인접 리스트가 초기화되지 않았습니다.\n");
        return;
    }
    if(*p_Ver < 10) //vertex는 10개까지의 제한이 있다
    {
        *p_Ver += 1; //정점 수 1개 추가
        printf("%d번째 정점 삽입 성공\n",*p_Ver);
    } else {
        printf("가능한 최대의 정점을 삽입했습니다.\n");
    }
}

void InsertEdge(Link* p_adj,int* p_Ver)
{
    if(p_adj == NULL) //인접 리스트가 초기화되지 않았을 경우
    {
        printf("인접 리스트가 초기화되지 않았습니다.\n");
        return;
    }
    int from, to;
    printf("from : ");
    scanf("%d", &from);
    printf("to : ");
    scanf("%d", &to);

    if(from >= 0 && from <= 9 && to >= 0 && to <= 9 && to < *p_Ver && from < *p_Ver) //간선의 시작점과 종점이 제약조건에 맞는지 확인한다
    {
        Link *seek = p_adj[from].next; //간선 탐색용 seek 선언 후 탐색
        while(seek != NULL)
        {
            if(seek->vertex == to) //seek가 탐색하던 도중 추가하려는 간선의 종점과 같은 번호의 정점을 발견했을 경우
            {
                printf("이미 해당하는 간선이 있습니다.\n");
                return; //즉시 해당 함수에서 빠져나옴
            }
            seek = seek->next; //다음 seek 탐색
        }

        Link* p, *prev; //인접 리스트에 대입할 위치를 결정짓는 포인터 p와 prev 선언
        p = p_adj[from].next; //p는 시작점에 해당하는 인접 리스트의 헤드에 접근
        prev = NULL;
        while(p != NULL) //p가 해당 인접리스트의 범위에서 벗어날 때 까지
        {
            if(to <= p->vertex) //p가 가르키고 있는 정점의 번호가 추가하는 정점의 번호보다 크거나 같을 경우
                break; //즉시 while을 빠져나간다
            prev = p; //prev는 p로
            p = p->next; //p는 다음 가르키는 포인터로 이동
        }
        
        Link* node = (Link*)malloc(sizeof(Link));
        node->vertex = to;
        if(prev != NULL)
        {
            node->next = prev->next;
            prev->next = node;
        } else {
            node->next = p_adj[from].next;
            p_adj[from].next = node;
        } 
        //해당하는 위치에 노드 대입(오름차순)

        //그래프는 Undirected graph이기 때문에 종점에서 시점으로 가는 간선도 추가한다
        if(from != to) //from과 to가 다를 경우
        {
            p = p_adj[to].next;
            prev = NULL;
            while(p != NULL)
            {
                if(from <= p->vertex)
                break;
                prev = p;
                p = p->next;
            }
        
            Link* rnode = (Link*)malloc(sizeof(Link));
            rnode->vertex = from;
            if(prev != NULL)
            {
                rnode->next = prev->next;
                prev->next = rnode;
            } else {
                rnode->next = p_adj[to].next;
                p_adj[to].next = rnode;
            }
        }
    } else {
        printf("해당 정점은 존재하지 않습니다.\n");
    }
}

void PrintGraph(Link* p_adj,int* p_Ver)
{
    if(p_adj == NULL) //인접 리스트가 초기화되지 않았을 경우
    {
        printf("인접 리스트가 초기화되지 않았습니다.\n");
        return;
    }
    for(int i = 0;i < *p_Ver;i++) //모든 정점의 갯수만큼 반복
    {
        printf("[%d]",i); //정점 출력
        Link* p = p_adj[i].next; //해당 정점의 인접 리스트에 접근
        while(p != NULL) //p가 범위에서 벗어날 때 까지
        {
            printf("->[%d]",p->vertex);
            p = p->next; //p의 정점 번호를 출력 후 다음으로 이동
        }
        printf("\n");
    }
}

void BFS(Link* p_adj,int* p_Ver)
{
    if(p_adj == NULL) //인접 리스트가 초기화되지 않았을 경우
    {
        printf("인접 리스트가 초기화되지 않았습니다.\n");
        return;
    }
    int* visited = (int*)malloc(sizeof(int) * *p_Ver);
    for(int i = 0;i < *p_Ver;i++)
    {
        visited[i] = 0;
    }
    //방문된 노드를 기억하는 변수를 선언 후 초기화
    enqueue(0); //시작 노드를 큐에 넣음
    visited[0] = 1;
    while(front != rear) //큐가 빌 때 까지
    {
        int temp = dequeue(); //큐에서 노드를 뺌
        printf(" [%d] ->",temp); //노드를 출력
        Link* p = p_adj[temp].next;
        while(p != NULL) //인접 리스트를 통해 인접 노드를 탐색
        {
            if(visited[p->vertex] == 0)
            {
                enqueue(p->vertex); //인접 노드 중 방문하지 않은 노드들을 큐에 추가
                visited[p->vertex] = 1; //해당 노드는 방문한 것으로 처리
            }
            p = p->next;
        }
    }
    printf(" end\n");
    free(visited); //visited 메모리 할당 해제
}

void DFS(Link* p_adj,int* p_Ver)
{
    if(p_adj == NULL) //인접 리스트가 초기화되지 않았을 경우
    {
        printf("인접 리스트가 초기화되지 않았습니다.\n");
        return;
    }
    int* visited = (int*)malloc(sizeof(int) * *p_Ver);
    for(int i = 0;i < *p_Ver;i++)
    {
        visited[i] = 0;
    }
    //방문된 노드를 기억하는 변수를 선언 후 초기화
    int curr = 0; //현재 탐색하는 노드의 위치를 저장
    push(0); //현재 탐색하는 노드를 스택에 넣음
    visited[0] = 1;
    printf(" [%d] ->",curr);
    while(top != -1) //스택이 빌 때 까지
    {
        Link* p = p_adj[curr].next; //인접노드 탐색용 p
        while(p != NULL) //p가 범위를 벗어날 때 까지
        {
            if(visited[p->vertex] == 0) //만약 방문하지 않은 정점을 p가 가르킨다면
                break; //즉시 반복문 탈출
            p = p->next; //p를 다음 인접노드로 이동
        }
        if(p == NULL) //방문하지 않은 인접노드가 없을 경우
        {
            curr = pop(); //스택에 저장된 노드를 pop함
        } else { //방문하지 않은 노드가 있을 경우
            curr = p->vertex; //탐색중인 노드를 해당 노드로 이동
            push(p->vertex); //해당 노드를 스택에 저장
            printf(" [%d] ->",p->vertex); //해당 노드 출력
            visited[p->vertex] = 1;
        }
    }
    printf(" end\n");
    free(visited); //visited 메모리 할당 해제
}

void enqueue(int Vertex)
{
    rear = (rear + 1) % 10; //큐 추가(큐의 크기가 최대 가능한 정점의 수와 같으므로 큐가 찰 가능성은 없다)
    queue[rear] = Vertex;
}

int dequeue()
{
    front = (front + 1) % 10;
    return queue[front];
}

void push(int Vertex)
{
    top += 1; //스택 추가(스택의 크기가 최대 가능한 정점의 수와 같으므로 스택이 찰 가능성은 없다)
    stack[top] = Vertex;
}

int pop()
{
    int temp = stack[top]; //top을 줄이기 전에 return을 먼저 하는 것이 불가능하므로 임시로 top의 값을 저장할 변수를 선언한다
    top -= 1;
    return temp;
}

void ReturnMemory(Link* p_adj,int Ver)
{
    if(p_adj != NULL)
    {
        for(int i = 0;i < Ver;i++) //정점의 수만큼 반복
        {
            Link* p = p_adj[i].next; //p_adj의 링크 메모리 반환용
            Link* temp;
            while(p != NULL) //p가 범위를 벗어날 때 까지
            {
                temp = p->next; //메모리 반환 시 p에 있는 링크가 사라지므로 기억용 변수 temp를 사용한다
                free(p); //링크 메모리 할당 해제
                p = temp; //p는 다음 링크로 이동
            }
        }
        free(p_adj); //p_adj의 메모리를 반환
    }
}