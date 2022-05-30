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
    Link* adj; //���� ����Ʈ�� �Ҵ���� ����
    int VertexC; //������ ����
    printf("[----- 2021041046 ������ -----]\n"); //�й� �̸� ���
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
        scanf(" %c",&command); //��ɾ� �Է�
        switch (command)
        {
        case 'z': case 'Z':
            Initialize(&adj,&VertexC); //adj�� VertexC �ʱ�ȭ
            for(int i = 0;i < 10;i++)
            {
                adj[i].next = NULL;
            }
            break;
        case 'i': case 'I':
            InsertVertex(&VertexC); //���� �߰�
            break;
        case 'd': case 'D':
            InsertEdge(adj,&VertexC); //���� �߰�
            break;
        case 'p': case 'P':
            PrintGraph(adj,&VertexC);
            break;
        default:
            printf("�߸��� ���� �Է��ϼ̽��ϴ�.\n");
            break;
        }
    } while (command != 'Q' && command != 'q');
    
}

void Initialize(Link** p_adj,int* p_Ver)
{
    if(*p_adj != NULL) //adj�� ����Ǿ� ���� ��� �ʱ�ȭ
        free(*p_adj);

    *p_adj = (Link*)malloc(sizeof(Link) * 10); //10���� ���� ����Ʈ�� �޸� �Ҵ�

    *p_Ver = 0; //���� ���� �ʱ�ȭ
    printf("�ʱ�ȭ ����\n");
}

void InsertVertex(int* p_Ver)
{
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
        prev = &p_adj[from]; //prev�� �������� �ش��ϴ� ���� ����Ʈ�� ���� ����
        while(p != NULL) //p�� �ش� ��������Ʈ�� �������� ��� �� ����
        {
            prev = p; //prev�� p��
            p = p->next; //p�� ���� ����Ű�� �����ͷ� �̵�
            if(to <= p->vertex) //p�� ����Ű�� �ִ� ������ ��ȣ�� �߰��ϴ� ������ ��ȣ���� ũ�ų� ���� ���
                break; //��� while�� ����������
        }
        
        Link* node = (Link*)malloc(sizeof(Link));
        node->vertex = to;
        node->next = prev->next;
        prev->next = node;
        //�ش��ϴ� ��ġ�� ��� ����(��������)

        //�׷����� Undirected graph�̱� ������ �������� �������� ���� ������ �߰��Ѵ�
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
        printf("�ش� ������ �������� �ʽ��ϴ�.\n");
    }
}

void PrintGraph(Link* p_adj,int* p_Ver)
{
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