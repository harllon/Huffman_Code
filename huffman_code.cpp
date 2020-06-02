#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h> 
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

int main(){
    FILE *p;
    int tamanho;
    p = fopen("texto1.txt", "r");
    vector<pair<char,int>> table;
    table = create_table(p, tamanho);
    print_table(table, tamanho);
    merge_sort(table, 0, tamanho-1);
    print_table(table, tamanho);

}
