#include <stdio.h>
#include <stdlib.h>

typedef struct DataLink {
    int vertex;
    struct DataLink* next;
} Link;

void Initialize(Link** p_adj,int* p_Ver);
void InsertVertex(int* p_Ver);
void InsertEdge(Link* p_adj,int* p_Ver);
void PrintGraph(Link* p_adj,int* p_Ver);
int main()
{
    Link* adj; //인접 리스트를 할당받을 변수
    int VertexC; //정점의 갯수
    printf("[----- 2021041046 전설민 -----]\n"); //학번 이름 출력
    char command;
    do
    {
		printf("\n----------------------------------------------------------------\n");
		printf("                          Graph Searches                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = i      Insert Edge                  = d \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");
        scanf(" %c",&command); //명령어 입력
        switch (command)
        {
        case 'z': case 'Z':
            Initialize(&adj,&VertexC); //adj와 VertexC 초기화
            for(int i = 0;i < 10;i++)
            {
                adj[i].next = NULL;
            }
            break;
        case 'i': case 'I':
            InsertVertex(&VertexC); //정점 추가
            break;
        case 'd': case 'D':
            InsertEdge(adj,&VertexC); //간선 추가
            break;
        case 'p': case 'P':
            PrintGraph(adj,&VertexC);
            break;
        default:
            printf("잘못된 값을 입력하셨습니다.\n");
            break;
        }
    } while (command != 'Q' && command != 'q');
    
}

void Initialize(Link** p_adj,int* p_Ver)
{
    if(*p_adj != NULL) //adj가 선언되어 있을 경우 초기화
        free(*p_adj);

    *p_adj = (Link*)malloc(sizeof(Link) * 10); //10개의 인접 리스트의 메모리 할당

    *p_Ver = 0; //정점 갯수 초기화
    printf("초기화 성공\n");
}

void InsertVertex(int* p_Ver)
{
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
        prev = &p_adj[from]; //prev는 시작점에 해당하는 인접 리스트에 직접 접근
        while(p != NULL) //p가 해당 인접리스트의 범위에서 벗어날 때 까지
        {
            prev = p; //prev는 p로
            p = p->next; //p는 다음 가르키는 포인터로 이동
            if(to <= p->vertex) //p가 가르키고 있는 정점의 번호가 추가하는 정점의 번호보다 크거나 같을 경우
                break; //즉시 while을 빠져나간다
        }
        
        Link* node = (Link*)malloc(sizeof(Link));
        node->vertex = to;
        node->next = prev->next;
        prev->next = node;
        //해당하는 위치에 노드 대입(오름차순)

        //그래프는 Undirected graph이기 때문에 종점에서 시점으로 가는 간선도 추가한다
        Link* p, *prev;
        p = p_adj[to].next;
        prev = &p_adj[to];
        while(p != NULL)
        {
            prev = p;
            p = p->next;
            if(to <= p->vertex)
                break;
        }
        
        Link* node = (Link*)malloc(sizeof(Link));
        node->vertex = from;
        node->next = prev->next;
        prev->next = node;
    } else {
        printf("해당 정점은 존재하지 않습니다.\n");
    }
}

void PrintGraph(Link* p_adj,int* p_Ver)
{
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