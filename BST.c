#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>



int p;
int cnt=0;


struct node {
    int data,count,l,r;
    struct node *left,*right;
};
struct node *root=NULL;

struct node *newnode(int x){
    struct node *temp=(struct node*)malloc(sizeof(struct node));
    temp->data=x;
    temp->count=1;
    temp->l=0;
    temp->r=0;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

void smallnums(struct node* root,int x){
    if(root==NULL)
        return;
    if(x==root->data){
        cnt+=root->l;
        return;
    }
    else if(x>root->data){
        cnt+=root->l;
        cnt+=root->count;
        smallnums(root->right,x);
    }
    else
        smallnums(root->left,x);  
}

void largenums(struct node* root,int x){
    if(root==NULL)
        return;
    if(root->data==x){
        cnt+=root->r;
        return;
    }
    else if(x<root->data){
        cnt+=root->r;
        cnt+=root->count;
        largenums(root->left,x);
    }
    else
        largenums(root->right,x);
    
}

struct node* search(struct node* root,int x){
    if(root==NULL||root->data==x)
        return root;
   // else if(root->data==x){
        // sflag=1;
        // return root;
    //}
    else if(root->data<x)
        return search(root->right,x);
    else
        return search(root->left,x);
    
}

struct node* insert(struct node* node,int x){
    if(node==NULL) 
        return newnode(x);
        
    if(node->data==x)
        node->count+=1;
    else if(x<node->data) {
        node->l+=1;
        node->left=insert(node->left,x);
    }
    else if(x>node->data){
        node->r+=1;
        node->right=insert(node->right,x);
    }
    return node;
}

void asc(struct node* root,int k){
    if(root==NULL)
        return;
    else if(root->l>=k){
        asc(root->left,k);
    }
    else if((k>root->l)&&(k<=((root->l)+(root->count)))){
        p=root->data;
        return;
    }
    else
        asc(root->right,k-(root->l)-(root->count));
    return;
}


void decrease(struct node* root,int x,int n){
    if(root==NULL)
        return;
    else if(x==root->data){
        root->count-=n;
        return;
    }
    else if(x<root->data){
        root->l-=n;
        decrease(root->left,x,n);
    }
    else{
        root->r-=n;
        decrease(root->right,x,n);
    }
}

void delete(struct node* root,int x,int c){
    if(root==NULL)
        return;
    else if(x==root->data){
        root->count=0;
        return;
    }
    else if(x<root->data){
        root->l-=c;
        delete(root->left,x,c);
    }
    else{
        root->r-=c;
        delete(root->right,x,c);
    }
}

void delnode(struct node* root,int x){
    if(root==NULL)
        return;
    struct node* temp1=search(root,x);
    if(temp1!=NULL)
    {
        int c=temp1->count;
        delete(root,x,c);
    }
}

int main() {
    int q,z,n;
    
    struct node *temp=NULL;
    scanf("%d",&q);
    char str[15];
    // scanf("%s",str);
    // scanf("%d",&z);
    // root=newnode(z);
    for(int i=0;i<q;++i){
    
        scanf("%s",str);
        
        if(strcmp(str,"learn")==0){
            scanf("%d",&z);
            if(root==NULL) root=newnode(z);
        
            else insert(root,z);
            
        }
        else if(strcmp(str,"forget")==0){
            scanf("%d",&z);
            delnode(root,z);
            // root = deleteNode(root,z);
            // temp=search(root,z);
            // sflag=0;
            // temp->count=0;
        }
        else if(strcmp(str,"decrease")==0){
            scanf("%d",&z);
            scanf("%d",&n);
            temp=search(root,z);
            if(temp!=NULL)
            {
                if(temp->data==z){
                if(temp->count>n)
                {
                    decrease(root,z,n);
                }
                else
                    delnode(root,z);
                }    
            }
            
        }
        else if(strcmp(str,"smaller_nums")==0){
            scanf("%d",&z);
            // temp=search(root,z);
            // sflag=0;
            cnt=0;
            smallnums(root,z);
            printf("%d\n",cnt);
        }
        else if(strcmp(str,"larger_nums")==0){
            scanf("%d",&z);
            // int cnt2=0;
            // temp=search(root,z);
            // sflag=0;
            cnt=0;
            largenums(root,z);
            printf("%d\n",cnt);
        }
        else if(strcmp(str,"asc")==0){
            scanf("%d",&z);
            if(root!=NULL)
            {
                cnt=root->l+root->r+root->count;
                asc(root,z);    
            }
            
            if(cnt>=z)
                printf("%d\n",p);
            else
                printf("-1\n");
        }
        else
            continue;
           // print2D(root);
           //  printf("\n\n");
           // printf("----------------------------------\n");
    }
    return 0;
}