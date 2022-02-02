#include<stdio.h> 
#include<stdlib.h> 

struct node 
{ 
  int data; 
  struct node *left_child; 
  struct node *right_child; 
  int height; 
}; 

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

int max(int a, int b); 

int height(struct node *node) 
{ 
  if (node == NULL) 
    return 0; 
  return node->height; 
} 

int max(int a, int b) 
{ 
  return (a > b)? a : b; 
} 

int minValue(struct node* root) 
{ 
    if (root->left_child == NULL) 
        return root->data; 
    return minValue(root->left_child); 
} 

int maxValue(struct node* root) 
{ 
    if (root->right_child == NULL) 
        return root->data; 
    return maxValue(root->right_child); 
} 

struct node* newNode(int data) 
{ 
  struct node* node = (struct node*) 
  malloc(sizeof(struct node)); 
  node->data = data; 
  node->left_child = NULL; 
  node->right_child = NULL; 
  node->height = 1;
  return(node); 
} 

struct node *rightRotate(struct node *y) 
{ 
  struct node *x = y->left_child; 
  struct node *T2 = x->right_child; 

  x->right_child = y; 
  y->left_child = T2; 

  return x; 
} 

struct node *leftRotate(struct node *x) 
{ 
  struct node *y = x->right_child; 
  struct node *T2 = y->left_child; 

  y->left_child = x; 
  x->right_child = T2; 

  return y; 
} 

int getBalanceFactor(struct node *node) 
{ 
  if (node == NULL) 
    return 0; 
  return height(node->left_child) - height(node->right_child); //height of the node
} 

struct node* insertNode(struct node* node, int data) 
{ 
  //searching for the place to insert
  if (node == NULL) 
    return(newNode(data)); 

  if (data < node->data) //// data is smaller should be inserted to left
    node->left_child = insertNode(node->left_child, data); 
  else if (data > node->data)  // data is greater. Should be inserted to right
    node->right_child = insertNode(node->right_child, data); 
  else
    return node; 

  node->height = 1 + max(height(node->left_child), //finding height of node
            height(node->right_child)); 

  int balanceFactor = getBalanceFactor(node); 

  if (balanceFactor > 1)
  {
    if (data < node->left_child->data)
    {
      return rightRotate(node);  // R rotate
    }
    else if (data > node->left_child->data)
    {
      node->left_child = leftRotate(node->left_child);   // LR rotate
      return rightRotate(node);
    }
  }
  if (balanceFactor < -1)
  {
    if (data > node->right_child->data)
    {
      return leftRotate(node);          // L rotate
    }
    else if (data < node->right_child->data)
    {
      node->right_child = rightRotate(node->right_child);   // Rl rotate
      return leftRotate(node);
    }
  }
  return node; 
} 

struct node * minValueNode(struct node* node) 
{ 
  struct node* current = node; 
  while (current->left_child != NULL) 
    current = current->left_child; 
  return current; 
} 

struct node* deleteNode(struct node* root, int data) 
{ 

  if (root == NULL) 
    return root; 

  if ( data < root->data ) 
    root->left_child = deleteNode(root->left_child, data); 

  else if( data > root->data ) 
    root->right_child = deleteNode(root->right_child, data); 

  else
  { 
    if( (root->left_child == NULL) || (root->right_child == NULL) ) 
    { 
      struct node *temp = root->left_child ? root->left_child : 
                      root->right_child; 

      if (temp == NULL) 
      { 
        temp = root; 
        root = NULL; 
      } 
      else
      *root = *temp; 
      
      free(temp); 
    } 
    else
    { 
      struct node* temp = minValueNode(root->right_child); 

      root->data = temp->data; 

      root->right_child = deleteNode(root->right_child, temp->data); 
    } 
  } 

  if (root == NULL) 
  return root; 

  root->height = 1 + max(height(root->left_child), 
            height(root->right_child)); 

  int balanceFactor = getBalanceFactor(root); 

  if (balanceFactor > 1)
  {
    if (getBalanceFactor(root->left_child) >= 0)
    {
      return rightRotate(root);
    }
    else
    {
      root->left_child = leftRotate(root->left_child);
      return rightRotate(root);
    }
  }

  if (balanceFactor < -1)
  {
    if (getBalanceFactor(root->right_child) <= 0)
    {
      return leftRotate(root);
    }
    else
    {
      root->right_child = rightRotate(root->right_child);
      return leftRotate(root);
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
    printf("\n Usuwanie wezla: %d", root->data); 
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
struct node *root = NULL; 

    int option1, option2, rooted, number, border=0, value, del, height;
    int* table_of_elements;
    
    printf("Wpisz wartosc korzenia: ");
    scanf("%d", &rooted);
    root = newNode(rooted);
    printf("\n");
    
    printf("Wpisz ile liczb chcesz miec w drzewie: ");
    scanf("%d", &number);
    table_of_elements = (int*)malloc(sizeof(int)*number);
    printf("\n");

    printf("TERAZ UZUPELNIAMY DRZEWO WYBRANYMI PRZEZ CIEBIE WARTOSCIAMI\n");

    while(border < number){
        printf("Wpisz liczbe:");
        scanf("%d",&value);
        root = insertNode(root, value);
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
            deleteNode(root, del);
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