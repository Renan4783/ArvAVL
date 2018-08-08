/*
 ============================================================================
 Name        : ArvAVL.c
 Author      : Renan
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Avl
{
    int info;
    struct Avl *dir;
    struct Avl *esq;

} No;

void balancearArvore(No **T);
void rotacaoEsquerda(No **T);
void rotacaoDireita(No **T);
int fatBal(No *T);
int altura( No *T);
void RemoveAbb( No **T, int x);
void PercorrePosOrdem (No *T);
void PercorrePreOrdem (No *T);
void PercorreEmOrdem (No *T);
void buscaABB (No *T, int x);
int InsereElementos (No **T, int x);
void inicializaArvore(No **T);


void inicializaArvore(No **T)
{
    *T = NULL;
}


int InsereElementos (No **T, int x)
{
    if (*T == NULL)
    {
        *T = ((No *) malloc (sizeof(No)));
        if (*T != NULL)
        {
            (*T)->info = x;
            (*T)->dir = NULL;
            (*T)->esq = NULL;
        }

        else
            printf("Erro de Memoria\n");

    }
    else
    {
        if ((*T)->info > x)
        {
            InsereElementos(&(*T)->dir, x);

        }

        else
        {
            if ((*T)->info < x)
            {
                InsereElementos(&(*T)->esq, x);
            }
            else
                printf("Elemento ja existe\n");
        }


    }

    balancearArvore(&*T);

}

void buscaABB (No *T, int x)
{

    No *P;
    P = T;

    if (T == NULL)
    {
        printf("Valor %d não encontrado\n", x);

    }
    else
    {
        if (T->info == x)
        {
            printf ("Elemento %d encontrado \n", T->info);

        }
        else
        {
            if (T->info > x)
            {
                if (T->dir == NULL)
                    P = NULL;
                else
                    P = P->dir;

                buscaABB(P, x);
            }

            else
            {
                if (T->info < x)
                {
                    {
                        if (T->esq == NULL)
                            P = NULL;
                        else
                            P = P->esq;
                        buscaABB(P, x);
                    }
                }

            }

        }
    }
}

void PercorreEmOrdem (No *T)
{

    if (T != NULL)
    {
        PercorreEmOrdem (T->esq);
        printf("%d\n", T->info);
        PercorreEmOrdem(T->dir);
    }

}

void PercorrePreOrdem (No *T)
{
    if (T != NULL)
    {
        printf("%d\n", T->info);
        PercorrePreOrdem (T->esq);
        PercorrePreOrdem(T->dir);
    }

}

void PercorrePosOrdem (No *T)
{
    if (T != NULL)
    {

        PercorrePosOrdem (T->esq);
        PercorrePosOrdem(T->dir);
        printf("%d\n", T->info);
    }

}
void RemoveAbb( No **T, int x)
{
    No *Aux;
    No *P;

    if (*T == NULL)

    {
        printf("Elemento nao Existe \n");
    }

    else
    {

        if (x  >(*T)->info)
        {
            RemoveAbb(&(*T)->esq, x);
        }
        if (x < (*T)->info )
        {
            RemoveAbb(&(*T)->dir, x);
        }
        if (x == (*T)->info)
        {
            if (((*T)->dir == NULL ) && ((*T)->esq == NULL))
            {
                printf("%d, removido com sucesso!\n", (*T)->info);
                free(*T);
                *T = NULL;
            }
            else
            {
                if  ((*T)->esq == NULL )
                {
                    printf("%d, removido com sucesso!\n", (*T)->info);
                    (*T) = (*T)->dir;

                }
                else
                {
                    if  ((*T)->dir == NULL )
                    {
                        printf("%d, removido com sucesso !\n", (*T)->info);
                        *T = (*T)->esq;
                    }
                    else
                    {
                        Aux = (*T)->dir;
                        Aux = Aux->esq;
                        P = *T ;
                        (*T)->info = Aux->info;
                        Aux->info = P->info;
                        RemoveAbb(&P->dir, Aux->info);

                    }
                }

            }
        }

    }
    balancearArvore(&*T);
}



int altura( No *T)
{
    if (T == NULL)
        return 0;
    else
    {
        int esq = altura( T->esq);
        int dir = altura( T->dir);
        if (esq < dir) return dir + 1;
        else return esq + 1;
    }
}

int fatBal(No *T)
{
    if (T == NULL)
        return 0;
    return altura(T->esq)- altura(T->dir);
}

void rotacaoDireita(No **T)
{

    No *Aux;
    No *P;

    P= (*T)->esq;
    Aux =P->dir;
    P->dir = (*T);
    (*T)->esq = Aux;
    (*T) = P;

}
void rotacaoEsquerda(No **T)
{

    No *Aux;
    No *P;

    P= (*T)->dir;
    Aux=P->esq;
    P->esq = *T;
    (*T)->dir= Aux;
    (*T) = P;

}

void balancearArvore(No **T)
{

    int Barvore = fatBal(*T);
    int Bdireito = fatBal((*T)->dir);
    int Besquerdo = fatBal((*T)->esq);

    if (Barvore != 1 || Barvore != -1 || Barvore != 0)
    {

        if(Barvore > 0)
        {
            if ( ( (Bdireito < 0) && (Besquerdo < 0) ) || ( (Bdireito > 0) && (Besquerdo > 0) ) || ( (Bdireito > 0) && (Besquerdo == 0) ) || ( (Bdireito < 0) && (Besquerdo == 0) ) || ( (Bdireito == 0) && (Besquerdo < 0) ) || ( (Bdireito == 0) && (Besquerdo > 0) ) )  //sinais iguais rotacao simples
            {
                rotacaoDireita(T);
            }
            if (((Bdireito > 0) && (Besquerdo < 0)) || ((Bdireito > 0) && (Besquerdo < 0)))  //sinais DIFERENTES rotacao DUPLA
            {
                rotacaoDireita(&(*T)->dir);
                rotacaoEsquerda(T);
            }

        }

        if(Barvore < 0)
        {
            if ((Bdireito <0 && Besquerdo <0) || (Bdireito >0 && Besquerdo >0) || (Bdireito > 0 && Besquerdo == 0) || (Bdireito < 0 && Besquerdo == 0) || (Bdireito == 0 && Besquerdo < 0) || (Bdireito == 0 && Besquerdo > 0))  //sinais iguais rotacao simples
            {
                rotacaoEsquerda(T);
            }
            if ((Bdireito >0 && Besquerdo <0) || (Bdireito >0 && Besquerdo <0))  //sinais DIFERENTES rotacao DUPLA
            {
                rotacaoEsquerda(&(*T)->esq);
                rotacaoDireita(T);
            }

        }

    }
}

int main(){
No  *T;

inicializaArvore(&T);


    InsereElementos(&T, 130);
    InsereElementos(&T, 220);
    InsereElementos(&T, 510);
    InsereElementos(&T, 250);
    InsereElementos(&T, 370);
   // InsereElementos(&T, 7);
   // InsereElementos(&T, 6);
   // InsereElementos(&T, 3);
   // InsereElementos(&T, 5);
   // InsereElementos(&T, 4);

    PercorreEmOrdem(T);
    return 0;
}
