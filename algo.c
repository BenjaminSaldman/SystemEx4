#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
int MATSIZE=0;
void build_graph_cmd(pnode *head)
{
    deleteGraph_cmd(head);
    int size=0;
    scanf("%d",&size);
    (*head)=(pnode)malloc(sizeof(struct GRAPH_NODE_));
    if(head==NULL)
    {
        printf("Couldn't allocate memory, try again\n");
        return;
    }
    (*head)->node_num=0;
    (*head)->edges=NULL;
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
        curr->next=NULL;
        temp->next=curr;
        temp=temp->next;
    }
    temp=(*head);
    char c=' ';
    scanf(" %c",&c);
    while(c=='n')
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
        scanf(" %c",&c);
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
        temp->edges=NULL;
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
        while(dest!=NULL && dest->node_num!=id){
            dest=dest->next;
        }
        add->weight=weight;
        add->endpoint=dest;
        add->next=NULL;
        if(edges==NULL){
            edges=add;
        }
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
        n->node_num=num;
        n->edges=edges;
        n->next=NULL;
        prev->next=n;
    }
}
void delete_node_cmd(pnode *head)
{
    int id =0;
    scanf("%d",&id);
    pnode temp=*head;
    pnode prev=temp;
    while(temp != NULL && temp->node_num!=id)
    {
        prev=temp;
        temp=temp->next;
    }
    pedge p=prev->next->edges;
    while(p!=NULL)
    {
        pedge p2=p;
        p=p->next;
        free(p2);
    }
    prev->next->edges=NULL;
    temp=*head;
    while(temp!=NULL)
    {
        pedge ed=temp->edges;
        if(ed!=NULL)
        {
            pedge t=ed;
            if(ed->endpoint->node_num == id)
            {
                temp->edges=temp->edges->next;
                free(t);
            }
            else
            {
               p=temp->edges;
               pedge k;
               pedge prev;
               while(p->next !=NULL)
               {
                   if(p->endpoint->node_num == id){
                        k=p->next;
                        p->next=p->next->next;
                        free(k);
                        break;
                   }
                   else{
                    prev=p;
                    p=p->next;
                   }
               }
               if(p!=NULL && p->endpoint->node_num == id)
               {
                   prev->next=NULL;
                   free(p);
               }
            }
        }
        temp=temp->next;
    }
    temp=*head;
    if((*head)->node_num==id)
    {
        (*head)=(*head)->next;
        free(temp);
    }
    else{
        temp=prev->next;
        prev->next=prev->next->next;
        free(temp);
    }


}
void deleteGraph_cmd(pnode* head)
{
    if((*head)== NULL)
        return;
    pnode temp=*head;
    while(temp!=NULL)
    {
        pedge curr=temp->edges;
        while(curr!=NULL)
        {
            pedge t=curr->next;
            free(curr);
            curr=t;
        }
        temp->edges=NULL;
        temp=temp->next;
    }
    temp=*head;
    while(temp!=NULL)
    {
       pnode t=temp->next;
        free(temp);
        temp=t;
    }
    *head=NULL;
    //free(head);
}
int** shortsPath_cmd(pnode head)
{
    
    int size=max_ID(head);
    //printf("size:\n");
    MATSIZE=size;
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
        while(ed!=NULL && ed->endpoint != NULL)
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
void delMat(int **MAT){
   
    for(int i=0;i<MATSIZE;i++)
        free(MAT[i]);
    free(MAT);
}
void TSP_cmd(pnode head)
{
    

    int** MAT=shortsPath_cmd(head);
    int key=0;
    int size=0;
    scanf("%d",&size);
    int *arr=(int*)malloc(size*sizeof(int));
    int s=scanf("%d",&key);
    int index=0;
    while(s==1 && s!=EOF && index<6){
        arr[index++]=key;
        s=scanf("%d",&key);
    }
    if(size==1){
        printf("TSP shortest path: 0\n");
        delMat(MAT);
        free(arr);
        return;
    }
    if(size==2){
        if(MAT[arr[0]][arr[1]]<INF || MAT[arr[1]][arr[0]]<INF){
            if(MAT[arr[0]][arr[1]]<INF)
                printf("TSP shortest path: %d\n",MAT[arr[0]][arr[1]]);
            else
                printf("TSP shortest path: %d\n",MAT[arr[1]][arr[0]]);
        }
        else
            printf("TSP shortest path: -1\n");

        delMat(MAT);
        free(arr);
        return;
    }
    int min=INF;
    if(size==3)
    {
        for(int i=0;i<size;i++)
        {
            int curr=0;
            for(int j=0;j<size;j++)
            {
                for(int k=0;k<size;k++)
                {
                    if(i!=j && i!=k && j!=k)
                    {
                        curr=MAT[arr[i]][arr[j]]+MAT[arr[j]][arr[k]];
                        if(curr<min)
                        {
                            min=curr;
                        }
                    }
                }
            }
        }
        if(min<INF){
        printf("TSP shortest path: %d\n",min);
        }
        else
            printf("TSP shortest path: -1 \n");
        delMat(MAT);
        free(arr);
        return;
    }
    if(size==4)
    {
        for(int i=0;i<size;i++)
        {
            int curr=0;
            for(int j=0;j<size;j++)
            {
                for(int k=0;k<size;k++)
                {
                    for(int m=0;m<size;m++)
                    {
                        if(i!=j && i!=k && j!=k && i!=m && j!=m && k!=m)
                        {
                            curr=MAT[arr[i]][arr[j]]+MAT[arr[j]][arr[k]]+MAT[arr[k]][arr[m]];
                            if(curr<min)
                            {
                                min=curr;
                            }
                        }
                    }
                }
            }
        }
        if(min<INF){
            printf("TSP shortest path: %d\n",min);
        }
        else
            printf("TSP shortest path: -1 \n");
        delMat(MAT);
        free(arr);
        return;
    }
    if(size==5)
    {
        for(int i=0;i<size;i++)
        {
            int curr=0;
            for(int j=0;j<size;j++)
            {
                for(int k=0;k<size;k++)
                {
                    for(int m=0;m<size;m++)
                    {
                         for(int n=0;n<size;n++)
                        {
                            if(i!=j && i!=k && j!=k && i!=m && j!=m && k!=m && i!=n && j!=n && k!=n && m!=n)
                            {
                                curr=MAT[arr[i]][arr[j]]+MAT[arr[j]][arr[k]]+MAT[arr[k]][arr[m]]+MAT[arr[m]][arr[n]];
                                if(curr<min)
                                {
                                    min=curr;
                                }
                            }
                        }
                    }
                }
            }
        }
        if(min<INF){
            printf("TSP shortest path: %d\n",min);
        }
        else
            printf("TSP shortest path: -1 \n");
        delMat(MAT);
        free(arr);
        return;
    }
    for(int i=0;i<size;i++)
    {
        int curr=0;
        for(int j=0;j<size;j++)
        {
            for(int k=0;k<size;k++)
            {
                for(int m=0;m<size;m++)
                {
                    for(int n=0;n<size;n++)
                    {
                        for(int r=0;r<size;r++)
                        {
                            if(i!=j && i!=k && i!=m && i!=n && i!=r && j!=k && j!=m && j!=n && j!=r && k!=m && k!=n && k!=r && m!=n && m!=r && n!=r)
                            {
                                
                                switch(size){
                                    case 3: curr=MAT[arr[i]][arr[j]]+MAT[arr[j]][arr[k]]; break;
                                    case 4: curr=MAT[arr[i]][arr[j]]+MAT[arr[j]][arr[k]]+MAT[arr[k]][arr[m]]; break;
                                    case 5: curr=MAT[arr[i]][arr[j]]+MAT[arr[j]][arr[k]]+MAT[arr[k]][arr[m]]+MAT[arr[m]][arr[n]]; break;
                                    case 6: curr=MAT[arr[i]][arr[j]]+MAT[arr[j]][arr[k]]+MAT[arr[k]][arr[m]]+MAT[arr[m]][arr[n]]+MAT[arr[n]][arr[r]]; break;
                                }
                                
                                if(curr<min)
                                {
                                    min=curr;
                                }
                            }
                        }
                    }
                }
            }
        }
}
      if(min<INF){
        printf("TSP shortest path: %d\n",min);
        }
        else
            printf("TSP shortest path: -1 \n");
        delMat(MAT);
        free(arr);

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
    if(head==NULL)
        return 1;
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
    pnode head=NULL;
    int check=0;
    char c=' ';
    check=scanf(" %c",&c);
    int** MAT;
    while(check!=EOF)
    {
        

        if(c=='A'){
            build_graph_cmd(&head);
          
            
            
        }
        if(c=='B'){
            insert_node_cmd(&head);
             
        }
        if(c=='D'){
            
            delete_node_cmd(&head); 
        }
        if(c=='S')
        {
            MAT=shortsPath_cmd(head);
            int p1=0, p2=0; 
            scanf(" %d %d",&p1,&p2);
            printf("Dijsktra shortest path: %d\n",MAT[p1][p2]);
            delMat(MAT);
            
        }
        if(c=='T')
        {
            TSP_cmd(head);
        }
        
       check=scanf(" %c",&c);
       
    }
    deleteGraph_cmd(&head);
}
 

