#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h> 
#include <fstream>
#include <vector>
using namespace std;

vector<pair<char,int>> create_table(FILE *p, int &tamanho){
    char ch;
    tamanho = 0;
    int novo = 1;
    vector<pair<char,int>> table;
    ch = fgetc(p);
    while(ch!=EOF){
        if(tamanho == 0){
            table.push_back(make_pair(ch,1));
            tamanho = 1;
        }else{
            for(int i=0; i<tamanho; i++){
                if(ch == table[i].first){
                    table[i].second++;
                    novo = 0;
                }
            }
            if(novo == 1){
                table.push_back(make_pair(ch,1));
                tamanho++;
            }
        }
        novo = 1;
        ch = fgetc(p);
    }
    return table;
}

void print_table(vector<pair<char,int>> table, int tamanho){
    int i;
    for(i=0; i<tamanho; i++){
        if(table[i].first == '\n'){
            cout << "jump" << " " << table[i].second << endl;
        }else{
            cout << table[i].first << " " << table[i].second << endl;
        }
    }
}

void merge(vector<pair<char,int>>& lista, int inicio, int meio, int fim){
    int size_left = meio-inicio+1;
    int size_right = fim-meio;
    int top_left=0,top_right=0;
    int k, i, j;
    vector<pair<char,int>> left(size_left);
    vector<pair<char,int>> right(size_right);

    for(i = 0; i < size_left; i++)
    {
        left[i] = lista[inicio+i];
    }
    for(j = 0; j < size_right; j++)
    {
        right[j]=lista[meio+j+1];
    }
    for(k = inicio; k <= fim; k++)
    {
        if(top_left >= size_left){
            lista[k] = right[top_right];
            top_right++;
        }else if(top_right >= size_right){
            lista[k] = left[top_left];
            top_left++;
        }else if(left[top_left].second <= right[top_right].second){
            lista[k] = left[top_left];
            top_left++;
        }else if(left[top_left].second > right[top_right].second){
            lista[k] = right[top_right];
            top_right++;
        }
    }
}

void merge_sort(vector<pair<char,int>>& lista, int inicio, int fim){
    if(inicio < fim)
    {
        int meio = (inicio+fim)/2;
        merge_sort(lista, inicio, meio);
        merge_sort(lista, meio+1, fim);
        merge(lista, inicio, meio, fim);
    }
}

class newnode{
    private:
        pair<char,int> content;
        newnode *right;
        newnode *left;
        string cod;
    public:
        newnode(){}
        newnode(pair<char,int> content){
            this->content = content;
            right = NULL;
            left = NULL;
        }
        void copy(newnode& node){
            content = node.content;
            left = node.left;
            right = node.right;
        }
        void set_content(pair<char,int> content){
            this->content = content;
        }
        void set_left(newnode *left){
            this->left = left;
        }
        void set_right(newnode *right){
            this->right = right;
        }
        pair<char,int> get_pair(){
            return content;
        }
        newnode* get_left(){
		    return left;
	    }
        newnode* get_right(){
		    return right;
	    }
        void set_cod(string codigo){
            cod = cod + codigo;
        }
        string get_cod(){
            return cod;
        }
};

void merge2(vector<newnode>& lista, int inicio, int meio, int fim){
    int size_left = meio-inicio+1;
    int size_right = fim-meio;
    int top_left=0,top_right=0;
    int k, i, j;
    vector<newnode> left(size_left);
    vector<newnode> right(size_right);

    for(i = 0; i < size_left; i++)
    {
        left[i] = lista[inicio+i];
    }
    for(j = 0; j < size_right; j++)
    {
        right[j]=lista[meio+j+1];
    }
    for(k = inicio; k <= fim; k++)
    {
        if(top_left >= size_left){
            lista[k] = right[top_right];
            top_right++;
        }else if(top_right >= size_right){
            lista[k] = left[top_left];
            top_left++;
        }else if(left[top_left].get_pair().second <= right[top_right].get_pair().second){
            lista[k] = left[top_left];
            top_left++;
        }else if(left[top_left].get_pair().second > right[top_right].get_pair().second){
            lista[k] = right[top_right];
            top_right++;
        }
    }
}

void merge_sort2(vector<newnode>& lista, int inicio, int fim){
    if(inicio < fim)
    {
        int meio = (inicio+fim)/2;
        merge_sort2(lista, inicio, meio);
        merge_sort2(lista, meio+1, fim);
        merge2(lista, inicio, meio, fim);
    }
}

vector<newnode> create_node(vector<pair<char,int>> &table){
    vector<newnode> nos;
    newnode aux(table[0]);
    for(int i=0;i<table.size();i++){
        aux.set_content(table[i]);
        nos.push_back(aux);
    }
    return nos;
}

vector<newnode> create_tree(vector<newnode> &nos){
    while(nos.size()!= 1){
        newnode *aux = new newnode;
        aux->set_content(make_pair(NULL, nos[0].get_pair().second + nos[1].get_pair().second)); //cria um novo nó
        newnode *aux1 = new newnode; 
        aux1->copy(nos[0]);
        newnode *aux2 = new newnode; 
        aux2->copy(nos[1]);
        aux->set_left(aux1);
        aux->set_right(aux2);
        nos.erase(nos.begin());
        nos.erase(nos.begin());
        nos.push_back(*aux);
        merge_sort2(nos,0,nos.size()-1);
    }
    return nos;
}

void create_cod(newnode *raiz, int &first, vector<pair<string, int>> &coded_table){   
    /*if(raiz->get_pair().first == '\n'){
        cout << raiz->get_pair().second << "(" << '@' << ") " << "  " << raiz->get_cod();
        cout << endl;
    }else{
        cout << raiz->get_pair().second << "(" << raiz->get_pair().first << ") " << "  " << raiz->get_cod();
        cout << endl;
    }*/
    if(raiz->get_pair().first != (int)NULL){
        coded_table.push_back(make_pair(raiz->get_cod(), raiz->get_pair().first));
    }
    if(raiz->get_left() != NULL){
        if(first == 1){
            raiz->get_left()->set_cod(raiz->get_cod());
        }
        raiz->get_left()->set_cod("0");
        first = 1;
        create_cod(raiz->get_left(), first, coded_table);
    }
    if (raiz->get_right() != NULL){
        if(first == 1){
                raiz->get_right()->set_cod(raiz->get_cod());
        }
        raiz->get_right()->set_cod("1");
        create_cod(raiz->get_right(), first, coded_table);
    }
}

void merge3(vector<pair<string,int>>& lista, int inicio, int meio, int fim){
    int size_left = meio-inicio+1;
    int size_right = fim-meio;
    int top_left=0,top_right=0;
    int k, i, j;
    vector<pair<string,int>> left(size_left);
    vector<pair<string,int>> right(size_right);

    for(i = 0; i < size_left; i++)
    {
        left[i] = lista[inicio+i];
    }
    for(j = 0; j < size_right; j++)
    {
        right[j]=lista[meio+j+1];
    }
    for(k = inicio; k <= fim; k++)
    {
        if(top_left >= size_left){
            lista[k] = right[top_right];
            top_right++;
        }else if(top_right >= size_right){
            lista[k] = left[top_left];
            top_left++;
        }else if(left[top_left].second <= right[top_right].second){
            lista[k] = left[top_left];
            top_left++;
        }else if(left[top_left].second > right[top_right].second){
            lista[k] = right[top_right];
            top_right++;
        }
    }
}

void merge_sort3(vector<pair<string,int>>& lista, int inicio, int fim){
    if(inicio < fim)
    {
        int meio = (inicio+fim)/2;
        merge_sort3(lista, inicio, meio);
        merge_sort3(lista, meio+1, fim);
        merge3(lista, inicio, meio, fim);
    }
}

int busca_binaria(vector<pair<string,int>>& lista, int inicio, int fim, int chave){
    //calcula-se a metade da lista
    int meio = (inicio + fim)/2;
    //compara chave com o valor medio da lista, se for maior
    if(chave > lista[meio].second){
        //condição de parada(verifica se eu cheguei numa lista unitaria)
        if(fim - meio <=1){
            //compara a chave com esse unico elemento da lista
            if(lista[meio].second == chave){
                return meio;
            }else{
                return -1;
            }
            //caso nao chegeui em lista unitaria, refaço a busca a partir da metade até o final
        }else{
            busca_binaria(lista, meio, fim, chave);
        }
        //tudo aqui é analogo ao de cima
    }else if(chave < lista[meio].second){
        if(meio - inicio <=0){
            if(lista[meio].second == chave){
                return meio;
            }else{
                return -1;
            }
        }else{
            busca_binaria(lista, inicio, meio, chave);
        }
        //achei a chave
    }else if(chave == lista[meio].second){
        return meio;
    }
}

void coded_txt(vector<pair<string, int>> &coded_table){
    FILE *p;
    p = fopen("input.txt", "r");
    ofstream arq;
    arq.open("txt_coded.txt");
    char ch;
    int chave, pos;
    ch = fgetc(p);
    while(ch!=EOF){
        chave = (int)ch;
        pos = busca_binaria(coded_table, 0, coded_table.size(), chave);
        arq << coded_table[pos].first;
        ch = fgetc(p);
    }
    fclose(p);
    arq.close();
}

void decode_txt(newnode *raiz){
    newnode *aux = raiz;
    FILE *p;
    p = fopen("txt_coded.txt", "r");
    ofstream arq;
    arq.open("txt_decoded.txt");
    char ch;
    ch = fgetc(p);

    while(ch!=EOF){
        if(ch=='0'){
            aux=aux->get_left();
        }
        if(ch=='1'){
            aux=aux->get_right();
        }
        if(aux->get_pair().first != (int)NULL){
            arq << aux->get_pair().first;
            aux=raiz;
        }
        ch = fgetc(p);
    }

    fclose(p);
    arq.close();
}

void printpre (newnode *raiz)
{   
    cout<<raiz->get_pair().second<<"("<<raiz->get_pair().first<<")"<<raiz<<" ";
    if (raiz->get_left() != NULL){printpre (raiz->get_left());}
    if (raiz->get_right() != NULL){printpre (raiz->get_right());}
}


int main(){
    FILE *p;
    p = fopen("input.txt", "r");
    int tamanho, first;
    first = 0;
    vector<pair<string, int>> coded_table;
    vector<pair<char,int>> table;
    vector<newnode> huff;
    table = create_table(p, tamanho);
    fclose(p);
    merge_sort(table, 0, tamanho-1);
    huff = create_node(table);
    huff = create_tree(huff);
    create_cod(&huff[0], first, coded_table);
    merge_sort3(coded_table, 0, coded_table.size()-1);
    /*for(int i=0; i<coded_table.size(); i++){
        cout << coded_table[i].first << "  " << coded_table[i].second << endl;
    }*/
    coded_txt(coded_table);
    cout << endl;

//    printpre(&huff[0]);

    decode_txt(&huff[0]);
    fclose(p);


}
