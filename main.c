#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct osoba
{
    char imie[50];
    char nazwisko[50];
    int rok;
    int id;
}Osoba;

typedef struct baza_danych
{
    Osoba osoby[100];
    int ile_osob;
    int max_id;
}Baza_danych;

Baza_danych baza;

Osoba utworz_osobe(char* imie, char* nazwisko, int rok)
{
    Osoba o;
    strcpy(o.imie,imie);
    strcpy(o.nazwisko,nazwisko);
    o.rok = rok;
    return o;
}

void dodaj_osobe(Osoba o)
{
    baza.max_id++;
    o.id = baza.max_id;
    baza.osoby[baza.ile_osob] = o;
    baza.ile_osob++;
}

void dodaj_osobe_id(Osoba o,int id)
{
    o.id = id;
    baza.osoby[baza.ile_osob] = o;
    baza.ile_osob++;
}

void usun_osobe(int id)
{
    int i,j;
    for(i=0; i<baza.ile_osob; i++)
    {
        if(id==baza.osoby[i].id)
        {
            baza.ile_osob--;
            for(j=i; j<baza.ile_osob; j++)
            {
                baza.osoby[j] = baza.osoby[j+1];
            }
        }
    }
}

void wyswietl_baze()
{
    printf("Ilosc osob w bazie: %d\n",baza.ile_osob);
    
    int i;
    for(i=0; i<baza.ile_osob; i++)
    {
        printf("ID: %d Imie: %s Nazwisko: %s Rok urodzenia: %d\n",baza.osoby[i].id,baza.osoby[i].imie,baza.osoby[i].nazwisko,baza.osoby[i].rok);
    }
}

void zapisz_plik(FILE* file)
{
    int i;
    fprintf(file,"%d\n",baza.ile_osob);
    fprintf(file,"%d\n",baza.max_id);
    for(i=0; i<baza.ile_osob; i++)
    {
        fprintf(file,"%d %s %s %d\n",baza.osoby[i].id,baza.osoby[i].imie,baza.osoby[i].nazwisko,baza.osoby[i].rok);
    }
}

void wczytaj_plik()
{
    int ilosc_osob,id,rok,i;
    char nazwa_pliku[50];
    char imie[50];
    char nazwisko[50];
    
    printf("Podaj nazwe pliku: \n");
    scanf("%s",&nazwa_pliku);
    FILE* plik_wczytaj;
    if ((plik_wczytaj = fopen(nazwa_pliku,"r")) == NULL )
    {
        printf("Problem z plikiem");
        exit(112);
    }
    printf("Nazwa pliku - %s\n",nazwa_pliku);
    fscanf(plik_wczytaj,"%d",&ilosc_osob);
    printf("Ilosc osob - %d\n",ilosc_osob);
    fscanf(plik_wczytaj,"%d",&baza.max_id);
    printf("Max ID - %d\n",baza.max_id);
    for(i=0; i<ilosc_osob; i++)
    {
        fscanf(plik_wczytaj,"%d %s %s %d",&id,&imie,&nazwisko,&rok);
        printf("Imie - %s Nazwisko - %s Rok ur. - %d\n",imie,nazwisko,rok);
        dodaj_osobe_id(utworz_osobe(imie,nazwisko,rok),id);
    }
    fclose(plik_wczytaj);
}
    
void sort()
{
    int i, j;
    char C;
    Osoba pom;
    
    printf("Sortowanie po: (N) - nazwisku, (R) - roku urodzenia lub (I) - imieniu\n");
    scanf(" %c",&C);
    
    while(C!='N' && C!='R' && C!='I')
    {
        printf("Podales zla wartosc,podaj N, R lub I\n");
        scanf(" %c",&C);
    }
    if(C == 'N')
    {
        for (i=baza.ile_osob-1; i>0; i--)
        {
            for (j=0; j<i; j++)
            {
                if (strcmp(baza.osoby[j].nazwisko, baza.osoby[j+1].nazwisko) > 0)
                {
                    pom = baza.osoby[j];
                    baza.osoby[j] = baza.osoby[j+1];
                    baza.osoby[j+1] = pom;
                }
            }
        }
    }
    else if(C == 'I')
    {
        for (i=baza.ile_osob-1; i>0; i--)
        {
            for (j=0; j<i; j++)
            {
                if (strcmp(baza.osoby[j].imie, baza.osoby[j+1].imie) > 0)
                {
                    pom = baza.osoby[j];
                    baza.osoby[j] = baza.osoby[j+1];
                    baza.osoby[j+1] = pom;
                }
            }
        }
    }
    else
    {
        for (i=baza.ile_osob-1; i>0; i--)
        {
            for (j=0; j<i; j++)
            {
                if (baza.osoby[j].rok > baza.osoby[j+1].rok)
                {
                    pom = baza.osoby[j];
                    baza.osoby[j] = baza.osoby[j+1];
                    baza.osoby[j+1] = pom;
                }
            }
        }
    }
}

void wyszukaj()
{
    char tekst[100];
    int rok,i,id;
    int ilosc_znalezionych = 0;
    char C;
    
    printf("Wyszukaj po: (Z) - ID, (R) - roku urodzenia, (N) - nazwisku lub (I) - imieniu\n");
    scanf(" %c",&C);
    
    while(C!='Z' && C!='N' && C!='R' && C!='I')
    {
        printf("Podales zla wartosc,podaj ID, N, R lub I\n");
        scanf(" %c",&C);
    }
    if(C == 'Z')
    {
        printf("Podaj ID:\n");
        scanf("%d",&id);
        
        for(i=0; i<baza.ile_osob; i++)
        {
            if(id == baza.osoby[i].id)
            {
                ilosc_znalezionych++;
                printf("ID: %d Imie: %s Nazwisko: %s Rok urodzenia: %d\n",baza.osoby[i].id,baza.osoby[i].imie,baza.osoby[i].nazwisko,baza.osoby[i].rok);
            }
        }
        if(ilosc_znalezionych==0)
        {
            printf("Nie ma osoby o takim ID w bazie\n");
        }
    }
    if(C == 'R')
    {
        printf("Podaj rok urodzenia:\n");
        scanf("%d",&rok);
        
        for(i=0; i<baza.ile_osob; i++)
        {
            if(rok == baza.osoby[i].rok)
            {
                ilosc_znalezionych++;
                printf("ID: %d Imie: %s Nazwisko: %s Rok urodzenia: %d\n",baza.osoby[i].id,baza.osoby[i].imie,baza.osoby[i].nazwisko,baza.osoby[i].rok);
            }
        }
        if(ilosc_znalezionych==0)
        {
            printf("Nie ma osoby o takim roku urodzenia w bazie\n");
        }
    }
    if(C == 'N')
    {
        printf("Podaj nazwisko lub czesc:\n");
        scanf("%s",&tekst);
        
        for(i=0; i<baza.ile_osob; i++)
        {
            if(strstr(baza.osoby[i].nazwisko,tekst) != NULL)
            {
                ilosc_znalezionych++;
                printf("ID: %d Imie: %s Nazwisko: %s Rok urodzenia: %d\n",baza.osoby[i].id,baza.osoby[i].imie,baza.osoby[i].nazwisko,baza.osoby[i].rok);
            }
        }
        if(ilosc_znalezionych==0)
        {
            printf("Nie ma osoby o takim nazwisku w bazie\n");
        }
    }
    if(C == 'I')
    {
        printf("Podaj imie lub czesc:\n");
        scanf("%s",&tekst);
        
        for(i=0; i<baza.ile_osob; i++)
        {
            if(strstr(baza.osoby[i].imie,tekst) != NULL)
            {
                ilosc_znalezionych++;
                printf("ID: %d Imie: %s Nazwisko: %s Rok urodzenia: %d\n",baza.osoby[i].id,baza.osoby[i].imie,baza.osoby[i].nazwisko,baza.osoby[i].rok);
            }
        }
        if(ilosc_znalezionych==0)
        {
            printf("Nie ma osoby o takim imieniu w bazie\n");
        }
    }
}

int main(int argc, const char * argv[])
{
    baza.ile_osob = 0;
    baza.max_id = -1;
    int opcja,rok,id,koniec = 0;
    char imie[50];
    char nazwisko[50];
    char nazwa_pliku[50];
    
    while(koniec == 0)
    {
        printf("1 - Wczytaj z pliku\n");
        printf("2 - Wyswietl baze\n");
        printf("3 - Dodaj osobe\n");
        printf("4 - Usun osobe\n");
        printf("5 - Sortowanie\n");
        printf("6 - Wyszukaj osobe\n");
        printf("7 - Zapisz do pliku\n");
        printf("8 - Wyjscie\n");
        scanf("%d",&opcja);
        
        switch(opcja)
        {
            case 1:
                wczytaj_plik();
                break;
                
            case 2:
                wyswietl_baze();
                break;
                
            case 3:
                printf("Podaj imie: \n");
                scanf("%s",&imie);
                printf("Podaj nazwisko: \n");
                scanf("%s",&nazwisko);
                printf("Podaj rok urodzenia: \n");
                scanf("%d",&rok);
                dodaj_osobe(utworz_osobe(imie,nazwisko,rok));
                break;
            
            case 4:
                printf("Podaj ID osoby do usuniecia: \n");
                scanf("%d",&id);
                usun_osobe(id);
                break;
                
            case 5:
                sort();
                break;
                
            case 6:
                wyszukaj();
                break;
                
            case 7:
                printf("Podaj nazwe pliku: \n");
                scanf("%s",&nazwa_pliku);
                FILE* plik_zapisz = fopen(nazwa_pliku,"w");
                zapisz_plik(plik_zapisz);
                    
                fclose(plik_zapisz);
                break;
                
            case 8:
                koniec = 1;
                break;
        };
    }
    return 0;
}
