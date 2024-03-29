//
// Created by soares on 27-03-2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "estado.h"
#include <time.h>

/**
 * Coloca Char em maiusculo.
 */
int pCima(char c)
{
    if (c >= 97 && c <= 122)
        c -= 32;

    return c;
}

/**
 * Cria um novo jogo.
 */
void newGame(ESTADO* e, int c, int check)
{
    if (c == 'X' || c == 'O')
    {
        limpar(e);

        e -> grelha[3][4] = VALOR_X;
        e -> grelha[4][3] = VALOR_X;
        e -> grelha[3][3] = VALOR_O;
        e -> grelha[4][4] = VALOR_O;
        e -> modo = 0;
        if (c == 'X')
            e -> peca = VALOR_X;
        else
            e -> peca = VALOR_O;
        e -> scoreo = 2;
        e -> scoresx = 2;
        printa(*e, check);
    }
    else
        printf("Novo jogo inválido!\n");

}

// Coloca todas as posicoes vazias
void limpar(ESTADO* e)
{
    int i,j;

    for (i = 0; i < 8; ++i)
        for (j = 0; j < 8; ++j)
            e -> grelha[i][j] = VAZIA;
}

//Imprime a peca que esta a jogar
void printaValor(VALOR v)
{
    if (v == VALOR_X)
        printf("X ");
    else
    {
        if (v == VALOR_O)
            printf("O ");
        else
            printf("- ");
    }
}
//Encontra as jogadas disponiveis a partir da nossa peca
void validarJog(ESTADO e, int validas[],int *v)
{
    int i, j;
    zerarValidas(validas);
    *v = 0;
    for (i = 0; i < 8; ++i)
        for (j = 0; j < 8; ++j)
            if (e.grelha[i][j] == e.peca)
                jogaveis(e, i, j, validas, v);

    validas[*v] = 888;
}

/**
 * Transforma três inteiros em um valor de três digitos.
 */
void darXy(int c, int *x, int *y,int *d)
{

    if (c/100 >= 1)
    {
       *x = c / 100;
       *y = (c - (*x)*100) / 10;
       *d = (c - (*x)*100 - (*y)*10);
    }
    else
    {
        if (c / 10 >= 1)
        {
            *x = 0;
            *y = c/10;
            *d = c - (*y)*10;
        }
        else
        {
            *x = 0;
            *y = 0;
            *d = c;
        }
    }
}

//Imprime o estado com '.' que simboliza as jogadas disponiveis
void valida(ESTADO e, int validas[],int *v)
{
    int i, j, z, x, y,p,a;

    i = 0;
    validarJog(e, validas,v);
    ordenar(validas, *v);
    darXy(validas[i], &x , &y, &p);

    putchar(' ');
    for (a = 1; a < 9; ++a)
        printf(" %d",a);
    putchar('\n');
    a = 1;
    for(j = 0; j < 8;j++, ++a)
    {
        printf("%d ", a);
        for (z = 0; z < 8; ++z)
        {
            if (x == j && y == z)
            {
                //printf("%d,%d\n",x,y);
                printf(". ");
                while (x == j && y == z)
                {
                    darXy(validas[i], &x, &y,&p);
                    ++i;
                }
                //darXy(validas[i], &x, &y,&p);
            }
            else
                printaValor(e.grelha[j][z]);
        }
        putchar('\n');
    }

}

/**
 * Ordena o array.
 */
void ordenar(int array[], int n)
{
    int i, key, j;

    for (i = 1; i < n; i++)
    {
        key = array[i];
        j = i - 1;

        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }

        array[j + 1] = key;
    }
}

//Deteta as posicoes jogaveis a partir de uma posicao
void jogaveis(ESTADO e, int a, int b, int validas[], int* v)
{
    int i, sit, fim, x, y;


    sit = fim = 0;

    //Cima
    x = a;
    y = b;
    for (i = 0, x -= 1; i < 8 && fim != 1 && x != -1 && y != -1 && x != 8 && y != 8; ++i,--x)
    {
        if (sit == 1 && e.grelha[x][y] == VAZIA)
        {
            fim = 1;
            validas[*v] = (x * 100) + (y * 10) + 0;
            //printf("%d\n", validas[*v]);
            ++*v;
        }
        if (e.grelha[x][y] == contrario(e.peca) && x >= 0 && y >= 0 && x < 8 && y < 8)
            sit = 1;
        else
        {
            sit = 0;
            fim = 1;
        }
    }
    //Baixo
    x = a;
    y = b;
    sit = fim = 0;
    for (i = 0, x += 1; i < 8 && fim != 1 && x != -1 && y != -1 && x != 8 && y != 8; ++i,++x)
    {
        if (sit == 1 && e.grelha[x][y] == VAZIA)
        {
            fim = 1;
            validas[*v] = x * 100 + y * 10 + 4;
            //printf("%d\n", validas[*v]);
            ++*v;
            //printf("%d %d\n", x, y);
        }
        if (e.grelha[x][y] == contrario(e.peca) && x >= 0 && y >= 0 && x < 8 && y < 8)
            sit = 1;
        else
        {
            sit = 0;
            fim = 1;
        }
    }
    //Esquerda
    x = a;
    y = b;
    sit = fim = 0;
    for (i = 0, y -= 1; i < 8 && fim != 1 && x != -1 && y != -1 && x != 8 && y != 8; ++i,--y)
    {
        if (sit == 1 && e.grelha[x][y] == VAZIA)
        {
            fim = 1;
            validas[*v] = x * 100 + y * 10 + 6;
            //printf("%d\n", validas[*v]);
            ++*v;
            //printf("%d %d\n", x, y);
        }
        if (e.grelha[x][y] == contrario(e.peca) && x >= 0 && y >= 0 && x < 8 && y < 8)
            sit = 1;
        else
        {
            sit = 0;
            fim = 1;
        }
    }
    //Direita
    x = a;
    y = b;
    sit = fim = 0;
    for (i = 0, y += 1; i < 8 && fim != 1 && x != -1 && y != -1 && x != 8 && y != 8; ++i,++y)
    {
        if (sit == 1 && e.grelha[x][y] == VAZIA)
        {
            fim = 1;
            validas[*v] = x * 100 + y * 10 + 2;
            //printf("%d\n", validas[*v]);
            ++*v;
            //printf("%d %d\n", x, y);
        }
        if (e.grelha[x][y] == contrario(e.peca) && x >= 0 && y >= 0 && x < 8 && y < 8)
            sit = 1;
        else
        {
            sit = 0;
            fim = 1;
        }
    }
    //Esquerda cima
    x = a;
    y = b;
    sit = fim = 0;
    for (i = 0, y -= 1, x -= 1; i < 8 && fim != 1 && x != -1 && y != -1 && x != 8 && y != 8; ++i,--y, --x)
    {
        if (sit == 1 && e.grelha[x][y] == VAZIA)
        {
            fim = 1;
            validas[*v] = x * 100 + y * 10 + 7;
            //printf("%d\n", validas[*v]);
            ++*v;
            //printf("lol %d %d\n", x, y);
        }
        if (e.grelha[x][y] == contrario(e.peca) && x >= 0 && y >= 0 && x < 8 && y < 8)
            sit = 1;
        else
        {
            sit = 0;
            fim = 1;
        }
    }
    //Esquerda baixo
    x = a;
    y = b;
    sit = fim = 0;
    for (i = 0, y -= 1, x += 1; i < 8 && fim != 1 && x != -1 && y != -1 && x != 8 && y != 8; ++i,--y, ++x)
    {
        if (sit == 1 && e.grelha[x][y] == VAZIA)
        {
            fim = 1;
            validas[*v] = x * 100 + y * 10 + 5;
            //printf("%d\n", validas[*v]);
            ++*v;
            //printf("%d %d\n", x, y);
        }
        if (e.grelha[x][y] == contrario(e.peca) && x >= 0 && y >= 0 && x < 8 && y < 8)
            sit = 1;
        else
        {
            sit = 0;
            fim = 1;
        }
    }
    //Direita cima
    x = a;
    y = b;
    sit = fim = 0;
    for (i = 0, y += 1, x -= 1; i < 8 && fim != 1 && x != -1 && y != -1 && x != 8 && y != 8; ++i,++y, --x)
    {
        if (sit == 1 && e.grelha[x][y] == VAZIA)
        {
            fim = 1;
            validas[*v] = x * 100 + y * 10 + 1;
            //printf("%d\n", validas[*v]);
            ++*v;
            //printf("%d %d\n", x, y);
        }
        if (e.grelha[x][y] == contrario(e.peca) && x >= 0 && y >= 0 && x < 8 && y < 8)
            sit = 1;
        else
        {
            sit = 0;
            fim = 1;
        }
    }
    //Direita baixo
    x = a;
    y = b;
    sit = fim = 0;
    for (i = 0, y += 1, x += 1; i < 8 && fim != 1 && x != -1 && y != -1 && x != 8 && y != 8; ++i,++y, ++x)
    {
        if (sit == 1 && e.grelha[x][y] == VAZIA)
        {
            fim = 1;
            validas[*v] = x * 100 + y * 10 + 3;
            //printf("%d\n", validas[*v]);
            ++*v;
            //printf("%d %d\n", x, y);
        }
        if (e.grelha[x][y] == contrario(e.peca) && x >= 0 && y >= 0 && x < 8 && y < 8)
            sit = 1;
        else
        {
            sit = 0;
            fim = 1;
        }
    }
}
/**
 * Retorna 1 se uma posiçao é valida a partir de coordenadas e de uma determinada direção, retorna 0 caso não seja valida.
 */
int posv(ESTADO e,int validas[],int k,int l,int p,int*v)
{
    int x,y,i,z;

    zerarValidas(validas);
    validarJog(e, validas,v);
    ordenar(validas, *v);

    for(i = 0;validas[i] != 888;i++)
    {
        darXy(validas[i], &x , &y,&z);
        if(k == x && l == y && p == z)
            return 1;
    }
    return 0;
}

/**
 * Altera as peças do tabuleiro conforme as peças jogadas.
 */
void capturapecas(ESTADO* e,int *a,int *b,int *validas,int *v, int *check)
{
    int a_it,b_it;

    *check = 0;
    //Come Baixo
    if(posv(*e,validas,*a,*b,0,v))
    {
        //e->grelha[a][b] = e->peca;
        //printf("\n%d %d\n", *a, *b);
        *check = 1;
        a_it = *a + 1, b_it = *b;
        while(e->grelha[a_it][b_it] == contrario(e->peca))
        {
            e->grelha[a_it][b_it] = e->peca;
            a_it += 1;
        }
        //e->peca = contrario(e->peca);
    }
    //Come Cima
    if(posv(*e,validas,*a,*b,4,v))
    {
        //e->grelha[a][b] = e->peca;
        //printf("\n%d %d\n", *a, *b);
        *check = 1;
        a_it = *a - 1, b_it = *b;
        while(e->grelha[a_it][b_it] == contrario(e->peca))
        {
            e->grelha[a_it][b_it] = e->peca;
            a_it -= 1;
        }

        //e->peca = contrario(e->peca);
    }
    //Come Direita
    if(posv(*e,validas,*a,*b,6,v))
    {
        //e->grelha[a][b] = e->peca;
        //printf("\n%d %d\n", *a, *b);
        *check = 1;
        a_it = *a, b_it = *b + 1;
        while(e->grelha[a_it][b_it] == contrario(e->peca))
        {
            e->grelha[a_it][b_it] = e->peca;
            b_it += 1;
        }
        //e->peca = contrario(e->peca);
    }
    //Come Esquerda
    if(posv(*e,validas,*a,*b,2,v))
    {
        //e->grelha[a][b] = e->peca;
        //printf("\n%d %d\n", *a, *b);
        *check = 1;
        a_it = *a, b_it = *b - 1;
        while(e->grelha[a_it][b_it] == contrario(e->peca))
        {
            e->grelha[a_it][b_it] = e->peca;
            b_it -= 1;
        }
        //e->peca = contrario(e->peca);
    }
    //Come Cima Esquerda
    if(posv(*e,validas,*a,*b,3,v))
    {
        //e->grelha[a][b] = e->peca;
        //printf("\n%d %d\n", *a, *b);
        *check = 1;
        a_it = *a - 1, b_it = *b - 1;
        while(e->grelha[a_it][b_it] == contrario(e->peca))
        {
            e->grelha[a_it][b_it] = e->peca;
            b_it -= 1;
            a_it -= 1;
        }
        //e->peca = contrario(e->peca);
    }
    //Come Baixo Esquerda
    if(posv(*e,validas,*a,*b,1,v))
    {
        //e->grelha[a][b] = e->peca;
        //printf("\n%d %d\n", *a, *b);
        *check = 1;
        a_it = *a+1, b_it = *b - 1;
        while(e->grelha[a_it][b_it] == contrario(e->peca))
        {
            e->grelha[a_it][b_it] = e->peca;
            b_it -= 1;
            a_it += 1;
        }
        //e->peca = contrario(e->peca);
    }
    //Come Cima Direita
    if(posv(*e,validas,*a,*b,5,v))
    {
        //e->grelha[a][b] = e->peca;
        //printf("\n%d %d\n", *a, *b);
        *check = 1;
        a_it = *a -1, b_it = *b + 1;
        while(e->grelha[a_it][b_it] == contrario(e->peca))
        {
            e->grelha[a_it][b_it] = e->peca;
            b_it += 1;
            a_it -= 1;
        }
        //e->peca = contrario(e->peca);
    }
    //Come Baixo Direita
    if(posv(*e,validas,*a,*b,7,v))
    {
        //e->grelha[a][b] = e->peca;
        //printf("\n%d %d\n", *a, *b);
        *check = 1;
        a_it = *a + 1, b_it = *b + 1;
        while(e->grelha[a_it][b_it] == contrario(e->peca))
        {
            e->grelha[a_it][b_it] = e->peca;
            a_it += 1;
            b_it += 1;
        }
        //e->peca = contrario(e->peca);
    }
    if (*check == 1)
    {
        e->grelha[*a][*b] = e->peca;
        e->peca = contrario(e->peca);
        scores(e);
        push(*e);
        *a = 8;
        *b = 8;
    }
}

/**
 * Zera o array das válidas.
 */
void zerarValidas(int validas[])
{
    int i = 0;

    while(validas[i])
        validas[i] = 0;
}

/**
 * Função que passa a jogada caso não haja nenhuma jogada válida para o jogador.
 */
void passaJogada(ESTADO* e, int validas[], int* v)
{
    zerarValidas(validas);
    validarJog(*e,validas,v);
    if(validas[0] == 888 && (e->scoresx !=0 || e->scoreo != 0))
    {
        e->peca = contrario(e->peca);
        printf("O jogador tem de passar!\n");
        validarJog(*e, validas, v);
        if (validas[0] == 888)
            win(*e);
    }
}

/**
 * Devolve a peça contraria à dada.
 */
VALOR contrario(VALOR v)
{

    if (v == VALOR_X)
        v = VALOR_O;
    else
        v = VALOR_X;

    return v;
}

/**
 * Acrescenta um ou mais pontos a um jogador.
 */
void scores(ESTADO* e)
{
    e->scoreo = 0;
    e->scoresx = 0;
    int i,j;
    for(i = 0;i<8;i++)
    {
        for(j = 0;j<8;j++)
        {
            if(e->grelha[i][j] == VALOR_X)
                e->scoresx++;
            if(e->grelha[i][j] == VALOR_O)
                e->scoreo++;
        }
    }
}

/**
 * Coloca um estado no topo de uma stack, server para desfazer as jogadas.
 */
void push(ESTADO e){
    struct Node* temp;
    temp = (struct Node*)malloc(sizeof(struct Node));
    if (!temp) {
        printf("\nStack sobrelotada");
        exit(1);
    }
    temp->e = e;
    temp->next = top;
    top = temp;
}

/**
 * Retira o estado do topo da stack e coloca-o no estado do jogo.
 */
ESTADO pop(){
    struct Node* temp;
    if (top == NULL)
    {
        printf("\nStack vazia");
    }
    else {
        temp = top;
        top = top->next;
        free(temp);
    }
    return (top->e);
}

/**
 * Guarda um estado num ficheiro.
 */
void saveEstado(char* nome, ESTADO* estado, int validas[], int *v)
{
    FILE* file;
    int i,j,l, check;

    check = 0;

    file = fopen(nome, "w");

    if (estado->modo == 0)
        fprintf(file, "M ");
    else
        fprintf(file, "A ");
    if (estado->peca == VALOR_X)
        fprintf(file, "X\n");
    else
        fprintf(file, "O\n");

    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            if (estado->grelha[i][j] == VAZIA)
            {
                for (l = 0; check == 0 && l < 8; ++l)
                    if (posv(*estado, validas, i, j, l, v) == 1)
                        check = 1;

                if (check == 1)
                    fprintf(file, ". ");
                else
                    fprintf(file, "- ");
                check = 0;
            }
            else
            {
                if (estado->grelha[i][j] == VALOR_X)
                    fprintf(file, "X ");
                else
                    fprintf(file, "O ");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

/**
 * Carrega um estado de um determinado ficheiro.
 */
void carregaEstado(char* nome, ESTADO* estado)
{
    FILE* file;
    char modo, jogador, carac;
    int i, j;

    file = fopen(nome,"r");


    fscanf(file,"%c %c\n", &modo, &jogador);

    if (modo == 'M')
        estado -> modo = 0;
    else
        estado -> modo = 1;

    if (jogador == 'O')
        estado -> peca = VALOR_O;
    else
        estado -> peca = VALOR_X;

    for(i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            fscanf(file, "%c ", &carac);
            if (carac == '-' || carac == '.')
                estado -> grelha[i][j] = VAZIA;
            else
            {
                if (carac == 'X')
                    estado -> grelha[i][j] = VALOR_X;
                else
                    estado -> grelha[i][j] = VALOR_O;
            }
        }
        fscanf(file, "\n");
    }
    fclose(file);
}

/**
 * Devolve uma posição aleatoria.
 */
int alea(ESTADO e,int validas[], int *v)
{
    validas[0] = 0;
    validarJog(e, validas,v);
    ordenar(validas, *v);
    int r;
    time_t t;
    srand((unsigned)time(&t));
    r = (rand()%5);
    if (r < (*v-1) && r >0)
        return r;
}

/**
 * Imprime um '?' como jogada possível no ecrã.
 */
void hint(ESTADO e,int validas[],int *v)
{
    int i, j, x, y,p;

    validas[0] = 0;
    validarJog(e, validas,v);
    ordenar(validas, *v);
    darXy(validas[alea(e,validas,v)], &x , &y, &p);

    for(i = 0;i<8;i++)
    {
        for(j = 0;j<8;j++)
        {
            if(x == i && y == j)
                printf("? ");
            else
                printaValor(e.grelha[i][j]);
        }
        putchar('\n');
    }
}

/**
 * Vê se o jogo acabou e quem é que o ganhou.
 */
int checkawin(ESTADO e)
{
    int r = 1,i,j;
    for(i = 0;i<8;i++)
    {
        for(j = 0;j<8;j++)
        {
            if(e.grelha[i][j] == VAZIA)
            {
                r = 0;
                return r;

            }
        }
    }
    return r;
}

/**
 * Imprime o vencedor.
 */
void win(ESTADO e)
{
        if(e.scoresx > e.scoreo)
            printf("Ganhou o jogador X !\n");
        else
            printf("Ganhou o jogador O !\n");
}

/**
 * Devolve o valor da peça dado um char.
 */
VALOR ePeca(char c)
{
    VALOR v;

    if (c == 'X')
        v = VALOR_X;
    else
        v = VALOR_O;

    return v;
}

/**
 * Bot do jogo.
 */
void bot(ESTADO* e,char peca,int nivel,int validas[],int *v, int *check)
{
    //Bot fácil
    if (nivel == 1 && ePeca(peca) == e->peca)
    {
        int x,y,d;

        validarJog(*e,validas,v);
        darXy(validas[0],&x,&y,&d);
        capturapecas(e,&x,&y,validas,v,check);
        printa(*e,*check);
    }


    /*
    int max = 0,x,y,p,sum = 0;
    ESTADO t = e;
    ESTADO h = e;

    zerarValidas(validas);
    validarJog(t, validas,v);
    ordenar(validas,*v);
    sum = e.scoreo;//fica sempre com o score inicial do estado e que é o estado inicial
    int j;
    for(j = 0;j < (*v);j++)
    {
        t = e;
        darXy(validas[j],&x,&y,&p);
        //printf("%d",validas[j]);
        //t.peca = contrario(e.peca);
        capturapecas(&t,&x,&y,validas,v,check);
        scores(&t);
        if(t.scoreo > max)
        {
            max = t.scoreo;
            h = t;
        }
        t.scoreo = sum;
        t.grelha[x][y] = VAZIA;
    }
    darXy(validas[0],&x,&y,&p);
    capturapecas(&t,&x,&y,validas,v, check);
    *check = 1;
    h = t;
    return h;
     */ //pode vir a ser usado em outra dificuldade
}