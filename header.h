
typedef struct node
{
    int val[4];             //extra to help with splitting
    struct node *child[5];  //extra to help with splitting
    int numVal;             //number of keys present
    struct node *p;         //parent
}node;

node* insert(node *root,int val);
void disp(node *root);