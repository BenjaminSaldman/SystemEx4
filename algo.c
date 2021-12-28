#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void build_graph_cmd(pnode *head)
{
    if (head!=NULL)
        free(head);
    int size=0;
    scanf("%d",&size);
    *head=(pnode)malloc(sizeof(struct GRAPH_NODE_));
    if(head==NULL)
    {
        printf("Couldn't allocate memory, try again\n");
        return;
    }
    (*head)->node_num=0;
    (*head)->edges=NULL;//(pedge)malloc(sizeof(struct edge_));
    (*head)->next=NULL;
    pnode temp=(*head);
    for(int i=1;i<size;i++)
    {
        pnode curr=(pnode)malloc(sizeof(struct GRAPH_NODE_));
        if(curr==NULL)
        {
            printf("Couldn't allocate memory, try again\n");
            return;
        }
        curr->node_num=i;
        curr->edges=NULL;
        temp->next=curr;
        temp=temp->next;
    }
    char c=' ';
    int t=0;
    t=scanf("%c",&c);
    while(t!=0)
    {
        int id=0,node=0,weight=0;
        scanf("%d",&id);
        int p=0;
        p=scanf("%d",&node);
        if(p==0)
            break;
        while(p!=0)
        {
            scanf("%d",&weight);
            pnode e=*head;
            while(e->node_num!=id)
                e=e->next;
            pnode e2=*head;
            while(e2->node_num!=node)
                e2=e2->next;
            pedge edge=(pedge)malloc(sizeof(struct edge_));
            if(edge == NULL)
            {
                printf("Couldn't create edge: %d--->%d\n",id,node);
                return;
            }
            edge->weight=weight;
            edge->endpoint=e2;
            edge->next=NULL;
            pedge l=e->edges;
            if(l==NULL)
                e->edges=edge;
            else{
            while(l->next!=NULL)
                l=l->next;
            l->next=edge;
            }
            p=scanf("%d",&node);
        }
        t=scanf("%c",&c);
    }    
}
void insert_node_cmd(pnode *head)
{
    pnode temp=*head;
    pnode prev=*head;
    int num=0;
    scanf("%d",&num);
    while(temp!=NULL && temp->node_num !=num)
    {
        prev=temp;
        temp=temp->next;
    }
    if(temp !=NULL)
    {
        pedge p=temp->edges;
        pedge next=p;
        while(p!=NULL)
        {
            next=p->next;
            free(p);
            p=next;
        }
        (*head)->edges=NULL;
    }
    pedge edges=NULL;
    int id=0;
    int a=scanf("%d",&id);
    while(a!=0)
    {
        int weight=0;
        scanf("%d",&weight);
        pedge add=(pedge)malloc(sizeof(struct edge_));
        pnode dest=*head;
        while(dest->node_num!=id)
            dest=dest->next;
        add->weight=weight;
        add->endpoint=dest;
        add->next=NULL;
        if(edges==NULL)
            edges=add;
        else{
            pedge l=edges;
            while(l->next!=NULL)
                l=l->next;
            l->next=add;
        }
        a=scanf("%d",&id);
    }
    if(temp!=NULL)
    {
        temp->edges=edges;
    }
    else{
        pnode n=(pnode)malloc(sizeof(struct GRAPH_NODE_));
        prev->next=n;
        n->edges=edges;
        n->next=NULL;
    }
}
void delete_node_cmd(pnode *head)
{
    int id =0;
    scanf("%d",&id);
    pnode temp=*head;
    pnode prev=temp;
    while(temp->node_num != id){
        prev=temp;
        temp=temp->next;
    }
    temp=*head;
    while(temp!=NULL)
    {
        pnode curr=temp;
        if(curr->node_num == id){
            temp=temp->next;
            continue;
        }
        pedge p=curr->edges;
        pedge p2=p;
        if(p->endpoint->node_num == id)
        {
            p2=p;
            p=curr->edges->next;
            free(p2);
        }
        else{
            while(p->next!=NULL)
            {
                if(p->next->endpoint->node_num == id)
                {
                    p2=p->next;
                    p->next=p->next->next;
                    free(p2);
                }
                else
                    p=p->next;
            }
            if(p->endpoint->node_num==id)
                free(p);
        }
        temp=temp->next;
    }
    pedge pa=prev->next->edges;
    while(pa->next!=NULL)
    {
        pedge k=pa->next;
        free(pa);
        pa=k;
    }
    free(pa);
    pnode del=prev->next;
    if((*head)->node_num==id)
    {
        del=*head;
        (*head)=(*head)->next;
        free(del);
    }
    else{
        prev->next=prev->next->next;
        free(del);
    }

}
int** shortsPath_cmd(pnode head)
{
    int size=max_ID(head);
    int **MAT=(int **)malloc(size*sizeof(int*));
    for(int i=0;i<size;i++)
        MAT[i]=(int*)malloc(size*sizeof(int));
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++){
            MAT[i][j]=INF;
            if(i==j)
                MAT[i][j]=0;
        }
    }
    for(int i=0;i<size;i++)
    {
        pnode p=get_Node(head,i);
        if(p==NULL)
            continue;
        pedge ed=p->edges;
        while(ed!=NULL)
        {
            MAT[i][ed->endpoint->node_num]=ed->weight;
            ed=ed->next;
        }
    }
    for(int k=0;k<size;k++)
    {
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<size;j++)
            {
                if(MAT[i][j]>MAT[i][k]+MAT[k][j])
                {
                    MAT[i][j]=MAT[i][k]+MAT[k][j];
                }
            }
        }
    }
   
    return MAT;
    
}

pnode get_Node(pnode head,int id){
    pnode temp=head;
    while(temp!=NULL)
    {
        if(temp->node_num==id)
            return temp;
        temp=temp->next;
    }
    return NULL;
}
int max_ID(pnode head)
{
    int max=0;
    pnode temp=head;
    while(temp!=NULL)
    {
        if(temp->node_num>max)
            max=temp->node_num;
        temp=temp->next;
    }
    return max+1;
}
int main()
{
    int size=3;
    int **MAT=(int **)malloc(size*sizeof(int*));
    for(int i=0;i<size;i++)
        MAT[i]=(int*)malloc(size*sizeof(int));
    MAT[0][1]=3;
    MAT[0][2]=1;
    MAT[1][0]=1;
    MAT[1][2]=4;
    MAT[2][1]=1;
    MAT[2][0]=1;
    MAT[0][0]=0;
    MAT[1][1]=0;
    MAT[2][2]=0;
    int counter=0;
    for(int k=0;k<size;k++)
    {
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<size;j++)
            {
                //printf("%d to %d is %d\n",i,j,MAT[i][j]);
                if(MAT[i][j]>MAT[i][k]+MAT[k][j])
                {
                    MAT[i][j]=MAT[i][k]+MAT[k][j];
                }
                counter++;
            }
        }
    }
    printf("%d\n",counter);
    printf("%d",MAT[0][1]);

   
}

