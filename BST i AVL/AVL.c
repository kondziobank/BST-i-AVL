#include<stdio.h> 
#include<stdlib.h> 

struct wezel 
{ 
  int dane; 
  struct wezel *lewe_dziecko; 
  struct wezel *prawe_dziecko; 
  int wysokosc; 
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

int max(int a, int b); 

int wysokosc_drzewa_pomocnicza(struct wezel *wezel) 
{ 
  if (wezel == NULL) 
    return 0; 
  return wezel->wysokosc; 
} 

int max(int a, int b) 
{ 
  return (a > b)? a : b; 
} 

int minimalna_wartosc(struct wezel* korzen) 
{ 
    if (korzen->lewe_dziecko == NULL) 
        return korzen->dane; 
    return minimalna_wartosc(korzen->lewe_dziecko); 
} 

int maksymalna_wartosc(struct wezel* korzen) 
{ 
    if (korzen->prawe_dziecko == NULL) 
        return korzen->dane; 
    return maksymalna_wartosc(korzen->prawe_dziecko); 
} 

struct wezel* nowy_wezel(int dane) 
{ 
  struct wezel* wezel = (struct wezel*) 
  malloc(sizeof(struct wezel)); 
  wezel->dane = dane; 
  wezel->lewe_dziecko = NULL; 
  wezel->prawe_dziecko = NULL; 
  wezel->wysokosc = 1;
  return(wezel); 
} 

struct wezel *prawa_rotacja(struct wezel *y) 
{ 
  struct wezel *x = y->lewe_dziecko; 
  struct wezel *help = x->prawe_dziecko; 

  x->prawe_dziecko = y; 
  y->lewe_dziecko = help; 

  return x; 
} 

struct wezel *lewa_rotacja(struct wezel *x) 
{ 
  struct wezel *y = x->prawe_dziecko; 
  struct wezel *help = y->lewe_dziecko; 

  y->lewe_dziecko = x; 
  x->prawe_dziecko = help; 

  return y; 
} 

int wywazenie(struct wezel *wezel) 
{ 
  if (wezel == NULL) 
    return 0; 
  return wysokosc_drzewa_pomocnicza(wezel->lewe_dziecko) - wysokosc_drzewa_pomocnicza(wezel->prawe_dziecko); 
} 

struct wezel* wstaw_wezel(struct wezel* wezel, int dane) 
{ 
  
  if (wezel == NULL) 
    return(nowy_wezel(dane)); 

  if (dane < wezel->dane) 
    wezel->lewe_dziecko = wstaw_wezel(wezel->lewe_dziecko, dane); 
  else if (dane > wezel->dane)  
    wezel->prawe_dziecko = wstaw_wezel(wezel->prawe_dziecko, dane); 
  else
    return wezel; 

  wezel->wysokosc = 1 + max(wysokosc_drzewa_pomocnicza(wezel->lewe_dziecko), 
            wysokosc_drzewa_pomocnicza(wezel->prawe_dziecko)); 

  int wspolczynnik = wywazenie(wezel); 

  if (wspolczynnik > 1)
  {
    if (dane < wezel->lewe_dziecko->dane)
    {
      return prawa_rotacja(wezel);  
    }
    else if (dane > wezel->lewe_dziecko->dane)
    {
      wezel->lewe_dziecko = lewa_rotacja(wezel->lewe_dziecko);   
      return prawa_rotacja(wezel);
    }
  }
  if (wspolczynnik < -1)
  {
    if (dane > wezel->prawe_dziecko->dane)
    {
      return lewa_rotacja(wezel);          
    }
    else if (dane < wezel->prawe_dziecko->dane)
    {
      wezel->prawe_dziecko = prawa_rotacja(wezel->prawe_dziecko);   
      return lewa_rotacja(wezel);
    }
  }
  return wezel; 
} 

struct wezel * min_wartosc_wezla(struct wezel* wezel) 
{ 
  struct wezel* now = wezel; 
  while (now->lewe_dziecko != NULL) 
    now = now->lewe_dziecko; 
  return now; 
} 

struct wezel* usun_wezel(struct wezel* korzen, int dane) 
{ 

  if (korzen == NULL) 
    return korzen; 

  if ( dane < korzen->dane ) 
    korzen->lewe_dziecko = usun_wezel(korzen->lewe_dziecko, dane); 

  else if( dane > korzen->dane ) 
    korzen->prawe_dziecko = usun_wezel(korzen->prawe_dziecko, dane); 

  else
  { 
    if( (korzen->lewe_dziecko == NULL) || (korzen->prawe_dziecko == NULL) ) 
    { 
      struct wezel *temp = korzen->lewe_dziecko ? korzen->lewe_dziecko : 
                      korzen->prawe_dziecko; 

      if (temp == NULL) 
      { 
        temp = korzen; 
        korzen = NULL; 
      } 
      else
      *korzen = *temp; 
      
      free(temp); 
    } 
    else
    { 
      struct wezel* temp = min_wartosc_wezla(korzen->prawe_dziecko); 

      korzen->dane = temp->dane; 

      korzen->prawe_dziecko = usun_wezel(korzen->prawe_dziecko, temp->dane); 
    } 
  } 

  if (korzen == NULL) 
  return korzen; 

  korzen->wysokosc = 1 + max(wysokosc_drzewa_pomocnicza(korzen->lewe_dziecko), 
            wysokosc_drzewa_pomocnicza(korzen->prawe_dziecko)); 

  int wspolczynnik = wywazenie(korzen); 

  if (wspolczynnik > 1)
  {
    if (wywazenie(korzen->lewe_dziecko) >= 0)
    {
      return prawa_rotacja(korzen);
    }
    else
    {
      korzen->lewe_dziecko = lewa_rotacja(korzen->lewe_dziecko);
      return prawa_rotacja(korzen);
    }
  }

  if (wspolczynnik < -1)
  {
    if (wywazenie(korzen->prawe_dziecko) <= 0)
    {
      return lewa_rotacja(korzen);
    }
    else
    {
      korzen->prawe_dziecko = prawa_rotacja(korzen->prawe_dziecko);
      return lewa_rotacja(korzen);
    }
  }
  return korzen; 
} 


void usun_drzewo(struct wezel* korzen)  
{ 
    if (korzen == NULL) 
      return; 
    
    usun_drzewo(korzen->lewe_dziecko); 
    usun_drzewo(korzen->prawe_dziecko); 
    
    
    printf("\n Usuwanie wezla: %d", korzen->dane); 
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
struct wezel *korzen = NULL; 

    int opcja1, opcja2, rooted, liczba, granica=0, wartosc, del, wysokosc;
    int* tablica;
    
    printf("Wpisz wartosc korzenia: ");
    scanf("%d", &rooted);
    korzen = nowy_wezel(rooted);
    printf("\n");
    
    printf("Wpisz ile liczb chcesz miec w drzewie: ");
    scanf("%d", &liczba);
    tablica = (int*)malloc(sizeof(int)*liczba);
    printf("\n");

    printf("TERAZ UZUPELNIAMY DRZEWO WYBRANYMI PRZEZ CIEBIE WARTOSCIAMI\n");

    while(granica < liczba){
        printf("Wpisz liczbe:");
        scanf("%d",&wartosc);
        korzen = wstaw_wezel(korzen, wartosc);
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
            printf("Najmniejszy element to %d", minimalna_wartosc(korzen));
            break;
        case 2:
            printf("Najwiekszy element to %d", maksymalna_wartosc(korzen));
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
            usun_wezel(korzen, del);
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
            usun_drzewo(korzen);
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