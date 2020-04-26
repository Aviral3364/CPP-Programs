#include <iostream>
#include<string.h>
#include<malloc.h> 
using namespace std;
#define COUNT 10 


struct node{
    int data;
    struct node *left;
    struct node *right;
    struct node *parent;
    char colour;
};

// Function to print binary tree in 2D 
// It does reverse inorder traversal 
void print2DUtil(struct node *root, int space) 
{ 
    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += COUNT; 
  
    // Process right child first 
    print2DUtil(root->right, space); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = COUNT; i < space; i++) 
        printf(" "); 
    printf("%d%c\n", root->data,root->colour); 
  
    // Process left child 
    print2DUtil(root->left, space); 
} 
  
// Wrapper over print2DUtil() 
void print2D(struct node *root) 
{ 
   // Pass initial space count as 0 
   print2DUtil(root, 0); 
}

struct node* rightrotation(struct node* root,struct node *p) {
    if(root==NULL)
        return NULL;
    struct node *q=p->left;
    p->left=q->right;
    if((p->left)!=NULL)
        p->left->parent=p;
    q->parent=p->parent;
    if(p==(p->parent->left))
        p->parent->left=q;
    else if((p->parent)==p)
        root=q;
    else
        p->parent->right=q;
    q->right=p;
    p->parent=q;
    return root;
}

struct node* leftrotation(struct node* root,struct node *p){
    if(root==NULL)
        return NULL;
    struct node *q=p->right;
    p->right=q->left;
    if((p->right)!=NULL)
        p->right->parent=p;
    q->parent=p->parent;
    if(p==(p->parent->left))
        p->parent->left=q;
    else if((p->parent)==p)
        root=q;
    else
        p->parent->right=q;
    q->left=p;
    p->parent=q;
    return root;
}

int search(struct node *root,int x){
    if(root==NULL)
        return 0;
    else
    {
        if((root->data)==x){
            return 1;
        }
        else if((root->data)>x)
            return search(root->left,x);
        else
            return search(root->right,x);
    }
}

struct node *newnode(int x){
    struct node *temp=(struct node*)malloc(sizeof(struct node));
    temp->data=x;
    temp->left=NULL;
    temp->right=NULL;
    temp->colour='r';
    temp->parent=temp;
    return temp;
}

struct node *insert(struct node *root,int x){
    if(root==NULL)
        return newnode(x);
    else if(x<(root->data)) {
        root->left=insert(root->left,x);
    }
    else if(x>(root->data)){
        root->right=insert(root->right,x);
    }
    return root;
}

struct node *getparent(struct node *root,int x,struct node *parent){
    if(root==NULL)
        return NULL;
    if(parent->data==x)
        return NULL;
    if(root->data==x)
        return parent;
    else if((root->data)>x){
        return getparent(root->left,x,root);
    }
    else{
        return getparent(root->right,x,root);
    }
}

struct node *fixRBT(struct node *root,struct node *p){ 
    struct node *par = NULL; 
    struct node *gpar = NULL; 
    struct node *uncle=NULL;
    while((p!=root)&&((p->colour)!='b')&&((p->parent->colour)=='r')){ 
        par=p->parent; 
        gpar=p->parent->parent; 
        if((gpar->left)==par){ 
            uncle=gpar->right; 
            if(((uncle!=NULL)&&((uncle->colour)=='r'))){ 
                par->colour='b'; 
                uncle->colour='b'; 
                gpar->colour='r';
                p=gpar; 
            } 
            else{ 
                if ((par->right)==p){ 
                    root=leftrotation(root,par); 
                    p=par; 
                    par=p->parent; 
                }
                root=rightrotation(root,gpar);
                char c=par->colour;
                par->colour=gpar->colour;
                gpar->colour=c;  
                p=par; 
            } 
        }
        else{ 
            uncle=gpar->left; 
            if ((uncle!=NULL)&&((uncle->colour)=='r')){ 
                par->colour='b'; 
                uncle->colour='b';
                gpar->colour='r';  
                p=gpar; 
            } 
            else{ 
                if((par->left)==p){ 
                    root=rightrotation(root,par); 
                    p=par; 
                    par=p->parent; 
                } 
                root=leftrotation(root,gpar); 
                char c=par->colour;
                par->colour=gpar->colour;
                gpar->colour=c; 
                p=par; 
            } 
        } 
    } 

    root->colour='b';
    return root; 
} 

struct node* learn(struct node *root,int x){
    root=insert(root,x);
    struct node *par=NULL;
    par=getparent(root,x,root);
    if(par==NULL){
        root->colour='b';
        return root;
    }
    struct node *p;
    if(par!=NULL){
        if((par->left)!=NULL){
            if((par->left->data)==x){
                p=par->left;
                p->parent=par;
            }
        }
        if((par->right)!=NULL){
            if((par->right->data)==x){
            p=par->right;
            p->parent=par;
            }
        }
    }
    root=fixRBT(root,p);
    return root;
}

//All functions from here will be helping in deletion of node

struct node *sibling(struct node *p,struct node *par){ 
    // sibling null if no parent 
    if(par==NULL) 
        return NULL; 
    if((par->left)!=NULL){
        if((par->left)==p){
            return par->right;
        }
    } 
    return par->left; 
} 

int lor(struct node *root,struct node *p){
    struct node *par=p->parent;
    if((par->left)!=NULL){
        if((par->left)==p){
            return -1;
        }
    }
    return 1;
}

int hrc(struct node *p){ 
    if(((p->left)!=NULL)&&((p->left->colour)=='r')) 
        return 1; 
    if(((p->right)!=NULL)&&((p->right->colour)=='r')) 
        return 1;
    return -1;
}

struct node *getnode(struct node *root,int x){
    if(root==NULL)
        return NULL;
    if((root->data)==x)
        return root;
    else if((root->data)>x)
        return getnode(root->left,x);
    else
        return getnode(root->right,x);
}


struct node *maxval(struct node *root){
    if(root->right==NULL)
        return root;
    else
        return maxval(root->right);
}

struct node *predhelper(struct node *root,struct node *p){
    struct node *par=p->parent;
    if((par->right)!=NULL){
        if((par->right->data)==(p->data))
            return par;
    }
    return predhelper(root,p->parent);
}

struct node *pred(struct node *root,struct node *p){
    if(p->left!=NULL)
        return maxval(p->left);
    else{
        struct node *par=p->parent;
        if((par->left)!=NULL){
            if((par->left->data)==(p->data)){
                return predhelper(root,p);
            }
        }
        if((par->right)!=NULL){
            if((par->right->data)==(p->data))
                return par;
        }
    }
    return p;
}

struct node *replace(struct node *root,struct node *x){ 
    if(((x->left)!=NULL)&&((x->right)!=NULL)) 
        return pred(root,x->left); 
    if(((x->left)==NULL)&&((x->right)==NULL)) 
        return NULL; 
    if((x->left)!=NULL) 
        return x->left; 
    else
        return x->right; 
} 


struct node *fixDoubleBlack(struct node *root,struct node *p){ 
    if(p==root) 
        return root; 
    struct node *par=p->parent;
    struct node *sib=sibling(p,par);
    if(sibling==NULL){ 
        root=fixDoubleBlack(root,par); 
    } 
    else { 
        if((sib->colour)=='r'){ 
            par->colour='r'; 
            sib->colour='b'; 
            if (lor(root,sib)==-1){ 
                root=rightrotation(root,par); 
            }
            else{
                root=leftrotation(root,par); 
            } 
            root=fixDoubleBlack(root,p); 
        } 
        else{  
            if(hrc(sib)==1){  
                if(((sib->left)!=NULL)&&((sib->left->colour)=='r')){ 
                    if(lor(root,sib)==-1){ 
                        sib->left->colour=sib->colour; 
                        sib->colour=par->colour; 
                        root=rightrotation(root,par); 
                    } 
                    else{  
                        sib->left->colour=par->colour; 
                        root=rightrotation(root,sib); 
                        root=leftrotation(root,par); 
                    } 
                } 
                else{ 
                    if(lor(root,sib)==-1){ 
                        sib->right->colour=par->colour; 
                        root=leftrotation(root,sib); 
                        root=rightrotation(root,par); 
                    }
                    else { 
                        sib->right->colour=sib->colour; 
                        sib->colour=par->colour; 
                        root=leftrotation(root,par); 
                    } 
                } 
                par->colour='b'; 
            } 
            else{  
                sib->colour='r'; 
                if((par->colour)=='b') 
                    root=fixDoubleBlack(root,par); 
                else
                    par->colour='b'; 
            } 
        } 
    } 
    return root;
}

struct node *deletenode(struct node *root,struct node *p,struct node *q){ 
    q=replace(root,p);
    int pqb;
    if(((q==NULL)||((q->colour)=='b'))&&((p->colour)=='b'))
        pqb=1;
    struct node *par=p->parent; 
    struct node *sib=sibling(p,par);
    if(q==NULL){ 
        if(p==root){  
            root=NULL; 
        } 
        else{ 
            if(pqb==1){ 
                root=fixDoubleBlack(root,p); 
            }
            else{ 
                if (sib!=NULL) 
                    sib->colour='r'; 
            }  
            if(lor(root,p)==-1){ 
                par->left = NULL; 
            }
            else{ 
                par->right=NULL; 
            } 
        } 
        delete p; 
        return root; 
    } 
    if(((p->left)==NULL)||((p->right)==NULL)){ 
        if(p==root){ 
            p->data=q->data; 
            p->left=NULL;
            p->right=NULL; 
            delete q; 
        }
        else{ 
            if(lor(root,p)==-1){ 
                par->left=q; 
            }
            else{ 
                par->right=q; 
            } 
        delete p; 
        q->parent=par; 
        if(pqb==1){ 
            root=fixDoubleBlack(root,q); 
        }
        else{ 
            q->colour='b'; 
        } 
    } 
    return root; 
    } 
    int z=p->data;
    p->data=q->data;
    q->data=z;  
    root=deletenode(root,q,q); 
    return root;
} 

struct node *forget(struct node *root,int x){
    if(root==NULL)
        return root;
    struct node *del=getnode(root,x);
    if(del==NULL)
        return root;
    struct node *q;
    if(((del->left)!=NULL)&&((del->right)!=NULL)) 
        q=pred(root,del->left);
    else if(((del->left)==NULL)&&((del->right)==NULL)) 
        q=NULL; 
    else{
        if((del->left)!= NULL) 
            q=del->left; 
        else
            q=del->right; 
    }
    root=deletenode(root,del,q);
    return root;
}


int main() {
    int q,x,y=0;
    struct node *root=NULL;
    scanf("%d",&q);
    char str[10];
    for(int i=0;i<q;++i){
        scanf("%s",str);
        if(strcmp(str,"learn")==0){
            scanf("%d",&x);
            root=learn(root,x);
        }
        else if(strcmp(str,"forget")==0){
            scanf("%d",&x);
            root=forget(root,x);
            print2D(root); 
        }
        else{
            scanf("%d",&x);
            y=search(root,x);
            if(y==1) printf("yes\n");
            else printf ("no\n");
        }
    }
    //print2D(root); 
    return 0;
}