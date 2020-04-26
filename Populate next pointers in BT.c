//Populate next pointers in BT interviewbit

//Given the following binary tree,
//
//         1
//       /  \
//      2    3
//     / \  / \
//    4  5  6  7
//After calling your function, the tree should look like:
//
//         1 -> NULL
//       /  \
//      2 -> 3 -> NULL
//     / \  / \
//    4->5->6->7 -> NULL


/**
 * Definition for binary tree
 *
 * struct TreeLinkNode {
 *     int val;
 *     struct TreeLinkNode *left, *right, *next;
 * };
 *
 * typedef struct TreeLinkNode treelinknode;
 */
/**
 * @input A : Root pointer of the tree 
 * 
 * @Output Void. Just modifies the args passed by reference 
 */

struct TreeLinkNode *nextright(struct TreeLinkNode *root){
    if((root->next)==NULL)
        return NULL;
    else{
        while((root->next)!=NULL){
            root=root->next;
            if((root->left)!=NULL)
                return root->left;
            else if((root->right)!=NULL)
                return root->right;
            else
                continue;
        }
    }
    return NULL;
} 
 
void connect(treelinknode* A) {
    if(A==NULL)
        return;
    A->next=NULL;
    struct TreeLinkNode *root=A;
    struct TreeLinkNode *p=A;
    while(root!=NULL){
        p=root;
        while(p!=NULL){
            if((p->left)!=NULL){
                if((p->right)!=NULL){
                    p->left->next=p->right;
                }
                else{
                    p->left->next=nextright(p);
                }
            }
            if((p->right)!=NULL){
                p->right->next=nextright(p);
            }
        p=p->next;
        }
        if((root->left)!=NULL)
            root=root->left;
        else if((root->right)!=NULL)
            root=root->right;
        else
            root=nextright(root);
    }
    return;
}
