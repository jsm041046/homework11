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
    Link* adj = NULL; //���� ����Ʈ�� �Ҵ���� ����
    int VertexC = 0; //������ ����
    printf("[----- 2021041046 ������ -----]\n"); //�й� �̸� ���
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
        scanf(" %c",&command); //��ɾ� �Է�
        switch (command)
        {
        case 'z': case 'Z':
            Initialize(&adj,&VertexC); //adj�� VertexC �ʱ�ȭ
            break;
        case 'i': case 'I':
            InsertVertex(adj,&VertexC); //���� �߰�
            break;
        case 'e': case 'E':
            InsertEdge(adj,&VertexC); //���� �߰�
            break;
        case 'p': case 'P':
            PrintGraph(adj,&VertexC); //�׷��� ���� ����Ʈ ���
            break;
        case 'B': case 'b':
            BFS(adj,&VertexC); //�ʺ� �켱 Ž��
            break;
        case 'D': case 'd':
            DFS(adj,&VertexC); //���� �켱 Ž��
            break;
        case 'q': case 'Q':
            ReturnMemory(adj,VertexC); //adj�� �޸� ��ȯ
            break;
        default:
            printf("�߸��� ���� �Է��ϼ̽��ϴ�.\n");
            break;
        }
    } while (command != 'Q' && command != 'q');
    
}

void Initialize(Link** p_adj,int* p_Ver)
{
     //adj�� ����Ǿ� ���� ��� �ʱ�ȭ
     if(*p_adj != NULL)
     {
        for(int i = 0;i < *p_Ver;i++) //������ ����ŭ �ݺ�
        {
            Link* p = (*p_adj)[i].next; //p_adj�� ��ũ �޸� ��ȯ��
            Link* temp;
            while(p != NULL) //p�� ������ ��� �� ����
            {
                temp = p->next; //�޸� ��ȯ �� p�� �ִ� ��ũ�� ������Ƿ� ���� ���� temp�� ����Ѵ�
                free(p); //��ũ �޸� �Ҵ� ����
                p = temp; //p�� ���� ��ũ�� �̵�
            }
        }
        free(*p_adj);
     }
    
    *p_adj = (Link*)malloc(sizeof(Link) * 10); //10���� ���� ����Ʈ�� �޸� �Ҵ�
    for(int i = 0;i < 10;i++)
    {
        (*p_adj)[i].next = NULL; //���� ����Ʈ �ʱ�ȭ
    }

    *p_Ver = 0; //���� ���� �ʱ�ȭ
    printf("�ʱ�ȭ ����\n");
}

void InsertVertex(Link* p_adj,int* p_Ver)
{
    if(p_adj == NULL) //���� ����Ʈ�� �ʱ�ȭ���� �ʾ��� ���
    {
        printf("���� ����Ʈ�� �ʱ�ȭ���� �ʾҽ��ϴ�.\n");
        return;
    }
    if(*p_Ver < 10) //vertex�� 10�������� ������ �ִ�
    {
        *p_Ver += 1; //���� �� 1�� �߰�
        printf("%d��° ���� ���� ����\n",*p_Ver);
    } else {
        printf("������ �ִ��� ������ �����߽��ϴ�.\n");
    }
}

void InsertEdge(Link* p_adj,int* p_Ver)
{
    if(p_adj == NULL) //���� ����Ʈ�� �ʱ�ȭ���� �ʾ��� ���
    {
        printf("���� ����Ʈ�� �ʱ�ȭ���� �ʾҽ��ϴ�.\n");
        return;
    }
    int from, to;
    printf("from : ");
    scanf("%d", &from);
    printf("to : ");
    scanf("%d", &to);

    if(from >= 0 && from <= 9 && to >= 0 && to <= 9 && to < *p_Ver && from < *p_Ver) //������ �������� ������ �������ǿ� �´��� Ȯ���Ѵ�
    {
        Link *seek = p_adj[from].next; //���� Ž���� seek ���� �� Ž��
        while(seek != NULL)
        {
            if(seek->vertex == to) //seek�� Ž���ϴ� ���� �߰��Ϸ��� ������ ������ ���� ��ȣ�� ������ �߰����� ���
            {
                printf("�̹� �ش��ϴ� ������ �ֽ��ϴ�.\n");
                return; //��� �ش� �Լ����� ��������
            }
            seek = seek->next; //���� seek Ž��
        }

        Link* p, *prev; //���� ����Ʈ�� ������ ��ġ�� �������� ������ p�� prev ����
        p = p_adj[from].next; //p�� �������� �ش��ϴ� ���� ����Ʈ�� ��忡 ����
        prev = NULL;
        while(p != NULL) //p�� �ش� ��������Ʈ�� �������� ��� �� ����
        {
            if(to <= p->vertex) //p�� ����Ű�� �ִ� ������ ��ȣ�� �߰��ϴ� ������ ��ȣ���� ũ�ų� ���� ���
                break; //��� while�� ����������
            prev = p; //prev�� p��
            p = p->next; //p�� ���� ����Ű�� �����ͷ� �̵�
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
        //�ش��ϴ� ��ġ�� ��� ����(��������)

        //�׷����� Undirected graph�̱� ������ �������� �������� ���� ������ �߰��Ѵ�
        if(from != to) //from�� to�� �ٸ� ���
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
        printf("�ش� ������ �������� �ʽ��ϴ�.\n");
    }
}

void PrintGraph(Link* p_adj,int* p_Ver)
{
    if(p_adj == NULL) //���� ����Ʈ�� �ʱ�ȭ���� �ʾ��� ���
    {
        printf("���� ����Ʈ�� �ʱ�ȭ���� �ʾҽ��ϴ�.\n");
        return;
    }
    for(int i = 0;i < *p_Ver;i++) //��� ������ ������ŭ �ݺ�
    {
        printf("[%d]",i); //���� ���
        Link* p = p_adj[i].next; //�ش� ������ ���� ����Ʈ�� ����
        while(p != NULL) //p�� �������� ��� �� ����
        {
            printf("->[%d]",p->vertex);
            p = p->next; //p�� ���� ��ȣ�� ��� �� �������� �̵�
        }
        printf("\n");
    }
}

void BFS(Link* p_adj,int* p_Ver)
{
    if(p_adj == NULL) //���� ����Ʈ�� �ʱ�ȭ���� �ʾ��� ���
    {
        printf("���� ����Ʈ�� �ʱ�ȭ���� �ʾҽ��ϴ�.\n");
        return;
    }
    int* visited = (int*)malloc(sizeof(int) * *p_Ver);
    for(int i = 0;i < *p_Ver;i++)
    {
        visited[i] = 0;
    }
    //�湮�� ��带 ����ϴ� ������ ���� �� �ʱ�ȭ
    enqueue(0); //���� ��带 ť�� ����
    visited[0] = 1;
    while(front != rear) //ť�� �� �� ����
    {
        int temp = dequeue(); //ť���� ��带 ��
        printf(" [%d] ->",temp); //��带 ���
        Link* p = p_adj[temp].next;
        while(p != NULL) //���� ����Ʈ�� ���� ���� ��带 Ž��
        {
            if(visited[p->vertex] == 0)
            {
                enqueue(p->vertex); //���� ��� �� �湮���� ���� ������ ť�� �߰�
                visited[p->vertex] = 1; //�ش� ���� �湮�� ������ ó��
            }
            p = p->next;
        }
    }
    printf(" end\n");
    free(visited); //visited �޸� �Ҵ� ����
}

void DFS(Link* p_adj,int* p_Ver)
{
    if(p_adj == NULL) //���� ����Ʈ�� �ʱ�ȭ���� �ʾ��� ���
    {
        printf("���� ����Ʈ�� �ʱ�ȭ���� �ʾҽ��ϴ�.\n");
        return;
    }
    int* visited = (int*)malloc(sizeof(int) * *p_Ver);
    for(int i = 0;i < *p_Ver;i++)
    {
        visited[i] = 0;
    }
    //�湮�� ��带 ����ϴ� ������ ���� �� �ʱ�ȭ
    int curr = 0; //���� Ž���ϴ� ����� ��ġ�� ����
    push(0); //���� Ž���ϴ� ��带 ���ÿ� ����
    visited[0] = 1;
    printf(" [%d] ->",curr);
    while(top != -1) //������ �� �� ����
    {
        Link* p = p_adj[curr].next; //������� Ž���� p
        while(p != NULL) //p�� ������ ��� �� ����
        {
            if(visited[p->vertex] == 0) //���� �湮���� ���� ������ p�� ����Ų�ٸ�
                break; //��� �ݺ��� Ż��
            p = p->next; //p�� ���� �������� �̵�
        }
        if(p == NULL) //�湮���� ���� ������尡 ���� ���
        {
            curr = pop(); //���ÿ� ����� ��带 pop��
        } else { //�湮���� ���� ��尡 ���� ���
            curr = p->vertex; //Ž������ ��带 �ش� ���� �̵�
            push(p->vertex); //�ش� ��带 ���ÿ� ����
            printf(" [%d] ->",p->vertex); //�ش� ��� ���
            visited[p->vertex] = 1;
        }
    }
    printf(" end\n");
    free(visited); //visited �޸� �Ҵ� ����
}

void enqueue(int Vertex)
{
    rear = (rear + 1) % 10; //ť �߰�(ť�� ũ�Ⱑ �ִ� ������ ������ ���� �����Ƿ� ť�� �� ���ɼ��� ����)
    queue[rear] = Vertex;
}

int dequeue()
{
    front = (front + 1) % 10;
    return queue[front];
}

void push(int Vertex)
{
    top += 1; //���� �߰�(������ ũ�Ⱑ �ִ� ������ ������ ���� �����Ƿ� ������ �� ���ɼ��� ����)
    stack[top] = Vertex;
}

int pop()
{
    int temp = stack[top]; //top�� ���̱� ���� return�� ���� �ϴ� ���� �Ұ����ϹǷ� �ӽ÷� top�� ���� ������ ������ �����Ѵ�
    top -= 1;
    return temp;
}

void ReturnMemory(Link* p_adj,int Ver)
{
    if(p_adj != NULL)
    {
        for(int i = 0;i < Ver;i++) //������ ����ŭ �ݺ�
        {
            Link* p = p_adj[i].next; //p_adj�� ��ũ �޸� ��ȯ��
            Link* temp;
            while(p != NULL) //p�� ������ ��� �� ����
            {
                temp = p->next; //�޸� ��ȯ �� p�� �ִ� ��ũ�� ������Ƿ� ���� ���� temp�� ����Ѵ�
                free(p); //��ũ �޸� �Ҵ� ����
                p = temp; //p�� ���� ��ũ�� �̵�
            }
        }
        free(p_adj); //p_adj�� �޸𸮸� ��ȯ
    }
}