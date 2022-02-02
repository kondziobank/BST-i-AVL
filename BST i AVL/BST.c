#include <stdio.h>
#include <stdlib.h>

struct wezel
{
    int dane;                                   
    struct wezel *prawe_dziecko;                   
    struct wezel *lewe_dziecko;                   
};


int wysokosc_drzewa(struct wezel* korzen) {
    
    if (!korzen)
        return 0;
    else {
        
        
        int lewa_wysokosc = wysokosc_drzewa(korzen->lewe_dziecko);
        int prawa_wysokosc = wysokosc_drzewa(korzen->prawe_dziecko);
        if (lewa_wysokosc >= prawa_wysokosc)
            return lewa_wysokosc + 1;
        else
            return prawa_wysokosc + 1;
    }
}
 


struct wezel* znajdz_najmniejszy_pomocnicza_funkcja(struct wezel *korzen)
{
    if(korzen == NULL)
        return NULL;
    else if(korzen->lewe_dziecko != NULL) 
        return znajdz_najmniejszy_pomocnicza_funkcja(korzen->lewe_dziecko); 
    return korzen;
}


int wartosc_minimum(struct wezel* korzen) 
{ 
    if (korzen->lewe_dziecko == NULL) {
    } 
    printf(" %d ", korzen->dane);
    return wartosc_minimum(korzen->lewe_dziecko); 
} 

int wartosc_maximum(struct wezel* korzen) 
{ 
    printf("->");
    if (korzen->prawe_dziecko == NULL){
    }
    printf(" %d ", korzen->dane);
    return wartosc_maximum(korzen->prawe_dziecko); 
} 


struct wezel* nowy_wezel(int x)
{
    struct wezel *p;
    p = malloc(sizeof(struct wezel));
    p->dane = x;
    p->lewe_dziecko = NULL;
    p->prawe_dziecko = NULL;

    return p;
}

struct wezel* wstaw(struct wezel *korzen, int x)
{
    
    if(korzen==NULL)
        return nowy_wezel(x);
    else if(x>korzen->dane) 
        korzen->prawe_dziecko = wstaw(korzen->prawe_dziecko, x);
    else 
        korzen->lewe_dziecko = wstaw(korzen->lewe_dziecko,x);
    return korzen;
}


struct wezel* usun(struct wezel *korzen, int x)
{
    
    if(korzen==NULL)
        return NULL;
    if (x>korzen->dane)
        korzen->prawe_dziecko = usun(korzen->prawe_dziecko, x);
    else if(x<korzen->dane)
        korzen->lewe_dziecko = usun(korzen->lewe_dziecko, x);
    else
    {
        
        if(korzen->lewe_dziecko==NULL && korzen->prawe_dziecko==NULL)
        {
            free(korzen); 
            return NULL;
        }

        
        else if(korzen->lewe_dziecko==NULL || korzen->prawe_dziecko==NULL)
        {   
            
            struct wezel *temp = korzen->lewe_dziecko ? korzen->lewe_dziecko : korzen->prawe_dziecko ; 
            free(korzen);  
            return temp;
        }

        
        else
        {
            struct wezel *temp = znajdz_najmniejszy_pomocnicza_funkcja(korzen->prawe_dziecko);               
            korzen->dane = temp->dane;        
            korzen->prawe_dziecko = usun(korzen->prawe_dziecko, temp->dane); 
        }
    }
    return korzen;
}

void usuwanie_drzewa(struct wezel* korzen)  
{ 
    if (korzen == NULL) 
        return; 
    
    usuwanie_drzewa(korzen->lewe_dziecko); 
    usuwanie_drzewa(korzen->prawe_dziecko); 
    
    
    printf("\n Usuwam wezel: %d", korzen->dane); 
    free(korzen); 
}  

void inorder(struct wezel *korzen)
{
    if(korzen!=NULL) 
    {
        inorder(korzen->lewe_dziecko); 
        printf(" %d ", korzen->dane); 
        inorder(korzen->prawe_dziecko);
    }
}

void preorder(struct wezel *korzen)
{
    if(korzen!=NULL)
    {
        printf(" %d ", korzen->dane);
        preorder(korzen->lewe_dziecko);
        preorder(korzen->prawe_dziecko);
    }
}

void postorder(struct wezel *korzen)
{
    if(korzen!=NULL)
    {
        postorder(korzen->lewe_dziecko);
        postorder(korzen->prawe_dziecko);
        printf(" %d ", korzen->dane);
    }
}


int main()
{
    struct wezel *korzen;
    int opcja1, opcja2, rooted, liczba, granica=0, wartosc, del, wysokosc;
    int* table_of_elements;
    
    printf("Wpisz wartosc korzenia: ");
    scanf("%d", &rooted);
    korzen = nowy_wezel(rooted);
    printf("\n");
    
    printf("Wpisz ile liczb chcesz miec w drzewie: ");
    scanf("%d", &liczba);
    table_of_elements = (int*)malloc(sizeof(int)*liczba);
    printf("\n");

    printf("TERAZ UZUPELNIAMY DRZEWO WYBRANYMI PRZEZ CIEBIE WARTOSCIAMI\n");

    while(granica < liczba){
        printf("Wpisz liczbe:");
        scanf("%d",&wartosc);
        wstaw(korzen, wartosc);
        printf("\n");
        granica++;
    }
    printf("Wybierz w jakim porzadku chcesz wypisac liczby\n");
    printf("Wybierz 1 jezeli chcesz wypisac wszystkie elementy w porzadku PRE-ORDER\n");
    printf("Wybierz 2 jezeli chcesz wypisac wszystkie elementy w porzadku IN-ORDER\n");
    printf("Wybierz 3 jezeli chcesz wypisac wszystkie elementy w porzadku POST-ORDER\n");
    scanf("%d", &opcja1);

    switch(opcja1)
    {
        case 1:
            printf("\n");
            preorder(korzen);
            break;
        case 2:
            printf("\n");  
            inorder(korzen);
            break;
        case 3:
            printf("\n");
            postorder(korzen);
            break;
    }
    printf("\n\n");


    printf("Wybierz operacje, ktora chcesz wykonac\n");
    printf("Wybierz 1 jezeli chcesz znalezc najmniejszy element\n");
    printf("Wybierz 2 jezeli chcesz znalezc najwiekszy element\n");
    printf("Wybierz 3 jezeli chcesz usunac wybrany element\n");
    printf("Wybierz 4 jezeli chcesz usunac CALE drzewo element po elemencie\n");
    printf("Wybierz 5 jezeli chcesz obliczyc wysokosc drzewa\n");
    scanf("%d", &opcja2);

    switch(opcja2)
    {
        case 1:
            printf("Najmniejszy element to %d", wartosc_minimum(korzen));
            break;
        case 2:
            printf("Najwiekszy element to %d", wartosc_maximum(korzen));
            break;
        case 3:
            printf("\n");
            printf("Wpisz wartosc ktora chcesz usunac:");
            scanf("%d", &del);
            printf("Drzewo 'W' wybranym wczesniej porzadku:\n");
            if(opcja1 == 1){
                preorder(korzen);
            } else if(opcja1 == 2){
                inorder(korzen);
            } else if(opcja1 == 3){
                postorder(korzen);
            }
            usun(korzen, del);
            printf("\n\n");
            printf("Drzewo 'PO' wybranym wczesniej porzadku:\n");
            if(opcja1 == 1){
                preorder(korzen);
            } else if(opcja1 == 2){
                inorder(korzen);
            } else if(opcja1 == 3){
                postorder(korzen);
            }
            break;
        case 4:
            printf("\n");
            printf("Usuwanie drzewa...");
            usuwanie_drzewa(korzen);
            break;
        case 5:
            printf("\n");
            wysokosc = wysokosc_drzewa(korzen);
            printf("Wysokosc drzewa: %d\n", wysokosc);
            break;
        default:
            printf("\n");
            printf("Nieznana operacja");
            break;
    }

    return 0;
}