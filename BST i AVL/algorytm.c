#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;                                   //node will store an integer
    struct node *right_child;                   // right child
    struct node *left_child;                    // left child
};

//recursive function
int tree_height(struct node* root) {
    // Get the height of the tree
    if (!root)
        return 0;
    else {
        // Find the height of both subtrees
        // and use the larger one
        int left_height = tree_height(root->left_child);
        int right_height = tree_height(root->right_child);
        if (left_height >= right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
}
 

//function to find the minimum value in a node
struct node* find_minimum(struct node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->left_child != NULL) // node with minimum value will have no left child
        return find_minimum(root->left_child); // left most element will be minimum
    return root;
}


int minValue(struct node* root) 
{ 
    if (root->left_child == NULL) {
    } 
    printf(" %d ", root->data);
    return minValue(root->left_child); 
} 

int maxValue(struct node* root) 
{ 
    printf("->");
    if (root->right_child == NULL){
    }
    printf(" %d ", root->data);
    return maxValue(root->right_child); 
} 

//function to create a node
struct node* new_node(int x)
{
    struct node *p;
    p = malloc(sizeof(struct node));
    p->data = x;
    p->left_child = NULL;
    p->right_child = NULL;

    return p;
}

struct node* insert(struct node *root, int x)
{
    //searching for the place to insert
    if(root==NULL)
        return new_node(x);
    else if(x>root->data) // x is greater. Should be inserted to right
        root->right_child = insert(root->right_child, x);
    else // x is smaller should be inserted to left
        root->left_child = insert(root->left_child,x);
    return root;
}

// funnction to delete a node
struct node* delete(struct node *root, int x)
{
    //searching for the item to be deleted
    if(root==NULL)
        return NULL;
    if (x>root->data)
        root->right_child = delete(root->right_child, x);
    else if(x<root->data)
        root->left_child = delete(root->left_child, x);
    else
    {
        //No Children
        if(root->left_child==NULL && root->right_child==NULL)
        {
            free(root); //delete root
            return NULL;
        }

        //One Child
        else if(root->left_child==NULL || root->right_child==NULL)
        {   
            //make the parent element to be deleted
            struct node *temp = root->left_child ? root->left_child : root->right_child ; 
            free(root);  //delete free node
            return temp;
        }

        //Two Children
        else
        {
            struct node *temp = find_minimum(root->right_child);  //find minimum el right subtree             
            root->data = temp->data;        //replace the data of the node to be deleted with data of this node
            root->right_child = delete(root->right_child, temp->data); //delete node found by the min func
        }
    }
    return root;
}

void deleteTree(struct node* root)  
{ 
    if (root == NULL) 
        return; 
    /* first delete both subtrees */
    deleteTree(root->left_child); 
    deleteTree(root->right_child); 
    
    /* then delete the node */
    printf("\n Usuwam wezel: %d", root->data); 
    free(root); 
}  

void inorder(struct node *root)
{
    if(root!=NULL) // checking if the root is not null
    {
        inorder(root->left_child); // visiting left child
        printf(" %d ", root->data); // printing data at root
        inorder(root->right_child);// visiting right child
    }
}

void preorder(struct node *root)
{
    if(root!=NULL)
    {
        printf(" %d ", root->data);
        preorder(root->left_child);
        preorder(root->right_child);
    }
}

void postorder(struct node *root)
{
    if(root!=NULL)
    {
        postorder(root->left_child);
        postorder(root->right_child);
        printf(" %d ", root->data);
    }
}


int main()
{
    struct node *root;
    int option1, option2, rooted, number, border=0, value, del, height;
    int* table_of_elements;
    
    printf("Wpisz wartosc korzenia: ");
    scanf("%d", &rooted);
    root = new_node(rooted);
    printf("\n");
    
    printf("Wpisz ile liczb chcesz miec w drzewie: ");
    scanf("%d", &number);
    table_of_elements = (int*)malloc(sizeof(int)*number);
    printf("\n");

    printf("TERAZ UZUPELNIAMY DRZEWO WYBRANYMI PRZEZ CIEBIE WARTOSCIAMI\n");

    while(border < number){
        printf("Wpisz liczbe:");
        scanf("%d",&value);
        insert(root, value);
        printf("\n");
        border++;
    }
    printf("Wybierz w jakim porzadku chcesz wypisac liczby\n");
    printf("Wybierz 1 jezeli chcesz wypisac wszystkie elementy w porzadku PRE-ORDER\n");
    printf("Wybierz 2 jezeli chcesz wypisac wszystkie elementy w porzadku IN-ORDER\n");
    printf("Wybierz 3 jezeli chcesz wypisac wszystkie elementy w porzadku POST-ORDER\n");
    scanf("%d", &option1);

    switch(option1)
    {
        case 1:
            printf("\n");
            preorder(root);
            break;
        case 2:
            printf("\n");  
            inorder(root);
            break;
        case 3:
            printf("\n");
            postorder(root);
            break;
    }
    printf("\n\n");


    printf("Wybierz operacje, ktora chcesz wykonac\n");
    printf("Wybierz 1 jezeli chcesz znalezc najmniejszy element\n");
    printf("Wybierz 2 jezeli chcesz znalezc najwiekszy element\n");
    printf("Wybierz 3 jezeli chcesz usunac wybrany element\n");
    printf("Wybierz 4 jezeli chcesz usunac CALE drzewo element po elemencie\n");
    printf("Wybierz 5 jezeli chcesz obliczyc wysokosc drzewa\n");
    scanf("%d", &option2);

    switch(option2)
    {
        case 1:
            printf("Najmniejszy element to %d", minValue(root));
            break;
        case 2:
            printf("Najwiekszy element to %d", maxValue(root));
            break;
        case 3:
            printf("\n");
            printf("Wpisz wartosc ktora chcesz usunac:");
            scanf("%d", &del);
            printf("Drzewo 'W' wybranym wczesniej porzadku:\n");
            if(option1 == 1){
                preorder(root);
            } else if(option1 == 2){
                inorder(root);
            } else if(option1 == 3){
                postorder(root);
            }
            delete(root, del);
            printf("\n\n");
            printf("Drzewo 'PO' wybranym wczesniej porzadku:\n");
            if(option1 == 1){
                preorder(root);
            } else if(option1 == 2){
                inorder(root);
            } else if(option1 == 3){
                postorder(root);
            }
            break;
        case 4:
            printf("\n");
            printf("Usuwanie drzewa...");
            deleteTree(root);
            break;
        case 5:
            printf("\n");
            height = tree_height(root);
            printf("Wysokosc drzewa: %d\n", height);
            break;
        default:
            printf("\n");
            printf("Nieznana operacja");
            break;
    }

    return 0;
}