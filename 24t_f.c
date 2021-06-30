#include<stdio.h>
#include<stdlib.h>
#include"header.h"

node* create(int val)
{
    node *temp=(node*)malloc(sizeof(node));
    for(int i=0;i<4;i++)
    {
        temp->val[i]=__INT_MAX__;
        temp->child[i]=NULL;
    }
    temp->child[4]=NULL;
    temp->numVal=0;
    temp->val[temp->numVal++]=val;
    temp->p=NULL;
    return temp;
}

void disp(node *root)
{
    if(root==NULL)
        return;

    int i;
    for(i=0;i<root->numVal;i++)
    {
        disp(root->child[i]);
        printf("%d\t",root->val[i]);
    }
    disp(root->child[i]);
}

void shiftR(int *a,int pos,int lim)
{
    for(int i=lim;i>pos;i--)
        a[i]=a[i-1];
}
void shiftRi(node **a,int pos,int lim)
{
    for(int i=lim;i>pos;i--)
        a[i]=a[i-1];
}

node* split(node *root,node *cur)
{
    if(root==NULL||cur==NULL)
        return NULL;

    
    node *t1=create(cur->val[0]);
    t1->val[1]=cur->val[1];
    t1->child[0]=cur->child[0];
    t1->child[1]=cur->child[1];
    t1->child[2]=cur->child[2];
    t1->numVal=2;

    node *t2=create(cur->val[3]);
    t2->child[0]=cur->child[3];
    t2->child[1]=cur->child[4];
    t2->numVal=1;

    if(cur==root)
    {
        node *temp=create(cur->val[2]);
        temp->numVal=1;
        temp->child[0]=t1;
        temp->child[1]=t2;
        t1->p=temp;
        t2->p=temp;
        free(cur);
        return temp;
    }

    t1->p=cur->p;
    t2->p=cur->p;
    node* p=cur->p;

    int i;
    for(i=0;i<4;i++)
        if(p->child[i]==cur)
            break;

    shiftR(p->val,i,p->numVal);
    shiftRi(p->child,i+1,p->numVal+1);  
    p->val[i]=cur->val[2];  
    p->child[i]=t1;
    p->child[i+1]=t2;
    p->numVal++;
    free(cur);

    if(p->numVal>3)
        root=split(root,p);   

    return root;
}

node* insert(node *root,int val)
{
    if(root==NULL)
    {
        printf("Here\n");
        node *temp=create(val);
        return temp;
    }
    node *temp=root;
    int i=0; 
    while(i<temp->numVal)
    {
        /*printf("Here out\n");
        for(int j=0;j<=temp->numVal;j++)
            printf("%d\t",temp->val[j]);
        printf("\ni=%d\n",i);
        */
        if(val<temp->val[i])
        {
            if(temp->child[i]==NULL)
                break;
            temp=temp->child[i];
            i=0;
        }
        else if(i+1<temp->numVal && val<temp->val[i+1])
        {
            if(temp->child[i+1]==NULL)
            {
                i++;
                break;
            }
            temp=temp->child[i+1];
            i=0;  
        }
        else if(val < temp->val[i+1] && temp->child[i+1]!=NULL)
        {
            temp=temp->child[i+1];
            i=0;
        }
        else
            i++;
    }

    shiftR(temp->val,i,temp->numVal);
    /*
    for(int j=0;j<temp->numVal;j++)
        printf("%d\t",temp->val[j]);
    printf("\ni=%d\n",i);
    */
    temp->val[i]=val;
    temp->numVal++;

    
    
    if(temp->numVal>3)  //split condition
    {
        root=split(root,temp);
    }
    return root;
}