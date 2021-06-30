#include<stdio.h>
#include<stdlib.h>
#include"header.h"

node* retPar(node *root,node *cur)
{
    int i=0; 
    node *temp=root;
    int val=cur->val[0];
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

            if(cur==temp->child[i])
                return temp;

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

            if(cur==temp->child[i+1])
                return temp;

            temp=temp->child[i+1];
            i=0;  
        }
        else if(val<temp->val[i+1] && temp->child[i+1]!=NULL)
        {
            if(cur==temp->child[i+1])
                return temp;

            temp=temp->child[i+1];
            i=0;
        }
        else
            i++;
    }
    return NULL;
}

int main()
{
    node *root=NULL;
   int a[]={3,1,5,4,2,9,10,8,7,6,11,12,13};
   for(int i=0;i<13;i++)
   {
        root=insert(root,a[i]);
        disp(root);
        printf("\n");
    }
    
    root=retPar(root,root);
      //checking tree by checking elements in the root
    printf("\n\n");
    if(root==NULL)
        printf("Hello");
    for(int i=0;i<root->numVal;i++)
        printf("%d\t",root->val[i]);
    printf("\n");
    
    
}