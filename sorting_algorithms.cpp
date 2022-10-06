/*//////////////////////////////////////
\\ Nome: Guilherme de Freitas Marques.\\
// Matrícula: 2020021600..............//
\\ ECOM03A - ANÁLISE DE ALGORITMOS....\\
// Tarefa 01 - Métodos de Ordenação...//
\\ C++................................\\
*///////////////////////////////////////

//Since this is just a simple college homework, I chose to do it all in a single .cpp file

#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

#define MAX_WORDS 40000

//recieves an array of strings, sorts it, then returns the time it took to do it
typedef int (*sort_function) (string vec[], int size);

int bubble_sort(string vec[], int size);
int selection_sort(string vec[], int size);
int insertion_sort(string vec[], int size);
int shell_sort(string vec[], int size);
int merge_sort(string vec[], int size);
int quick_sort(string vec[], int left, int right);

int main (void){
    const sort_function funcs[5] = {
        bubble_sort, 
        selection_sort, 
        insertion_sort, 
        shell_sort, 
        merge_sort, 
    };

    const int SIZES[7] = {1000, 5000, 10000, 15000, 20000, 30000, MAX_WORDS};

    //loop for every function excep quick_sort
    for(int func_n = 0; func_n < 5; func_n++){
        for (int size_n = 0; size_n < 7; size_n++){
            string word, word_array[40000];
            fstream file;
            file.open("aurelio40000.txt");

            //attributes each word in the .txt to word_array[i]
            for (int word_n = 0; file >> word; word_n++) word_array[word_n] = word;

            funcs[func_n](word_array, (int)SIZES[size_n]);

            file.close();
        }
    }

    //loop for quick_sort, since it requires different inputs
    for (int size_n = 0; size_n < 7; size_n++){
        string word, word_array[40000];
        fstream file;
        file.open("aurelio40000.txt");
        //attributes each word in the .txt to word_array[i]
        for (int word_n = 0; file >> word; word_n++) word_array[word_n] = word;

        int start_time = (int)clock();

        quick_sort(word_array, 0, (int)SIZES[size_n]-1);

        int time_spent = (((int)clock() - start_time)*1000/CLOCKS_PER_SEC);
        cout << "quick_sort: time spent for " << (int)SIZES[size_n] << " words: " << time_spent << "ms" << endl;

        file.close();
    }

    return 0;
}

int bubble_sort(string vec[], int size){
    int start_time = (int)clock();

    for (int i = 0; i < size; i++){
        for(int j = 0; j < size-1-i; j++){
            if (vec[j+1] < vec[j]){
                string aux = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = aux;
            }
        }
    }

    int time_spent = (((int)clock() - start_time)*1000/CLOCKS_PER_SEC);
    cout << "bubble_sort: time spent for " << size << " words: " << time_spent << "ms" << endl;
    return time_spent;
}

int selection_sort(string vec[], int size){
    int start_time = (int)clock();

    for (int i = 0; i < size; i++){
        string aux;
        int smaller = i;
        for(int j = i+1; j < size; j++)
            if (vec[j] < vec[smaller]) smaller = j;
        aux = vec[i];
        vec[i] = vec[smaller];
        vec[smaller] = aux;
    }

    int time_spent = (((int)clock() - start_time)*1000/CLOCKS_PER_SEC);
    cout << "selection_sort: time spent for " << size << " words: " << time_spent << "ms" << endl;
    return time_spent;
}

int insertion_sort(string vec[], int size){
    int start_time = (int)clock();

    for (int i = 0; i < size; i++){
        int j;
        string aux = vec[i];
        for (j = i-1; j >= 0 && vec[j] > aux; j--)
            vec[j+1] = vec[j];
        vec[j+1] = aux;
    }

    int time_spent = (((int)clock() - start_time)*1000/CLOCKS_PER_SEC);
    cout << "insertion_sort: time spent for " << size << " words: " << time_spent << "ms" << endl;
    return time_spent;
}

int shell_sort(string vec[], int size){
    int start_time = (int)clock();

    int j, h = size/2;
    while(h >= 1){
        for (int i = 0; i < size; i++){
            string aux = vec[i];
            for(j = i-h; (j >= 0) && (vec[j] > aux); j = j-h)
                vec[j+h] = vec[j];
            vec[j+h] = aux;
        }
        h = h/2;
    }

    int time_spent = (((int)clock() - start_time)*1000/CLOCKS_PER_SEC);
    cout << "shell_sort: time spent for " << size << " words: " << time_spent << "ms" << endl;
    return time_spent;
}

void merge_divide(string vec[], string aux[], int start, int end);
int merge_sort(string vec[], int size){
    int start_time = (int)clock();

    string aux[size];
    merge_divide(vec, aux, 0, size-1);

    int time_spent = (((int)clock() - start_time)*1000/CLOCKS_PER_SEC);
    cout << "merge_sort: time spent for " << size << " words: " << time_spent << "ms" << endl;
    return time_spent;
}

void merge_insert(string vec[], string aux[], int start, int middle, int end);
void merge_divide(string vec[], string aux[], int start, int end){
    int middle;
    if(end > start){
        middle = (end+start)/2;
        merge_divide(vec, aux, start, middle);
        merge_divide(vec, aux, middle+1, end);
        merge_insert(vec, aux, start, middle+1, end);
    }
}

void merge_insert(string vec[], string aux[], int start, int middle, int end){
    int current, halfend, size;
    current = start;
    halfend = middle-1;     
    size = end - start + 1;   

    while(start <= halfend && middle <= end){
        if(vec[start] <= vec[middle])
            aux[current++] = vec[start++];
        else
            aux[current++] = vec[middle++];
    }

    while(start <= halfend) aux[current++] = vec[start++];
    while(middle <= halfend) aux[current++] = vec[middle++];

    for(int i = 0; i < size; i++){
        vec[end] = aux[end];
        end--;
    }
}

int partition(string vec[], int left, int right);
int quick_sort(string vec[], int left, int right){
    if (left < right){
        int pivot = partition(vec, left, right);
        quick_sort(vec, left, pivot-1);
        quick_sort(vec, pivot+1, right);
    }
    return 1;
}

int partition(string vec[], int left, int right){
    string pivot = vec[left];

    int count = 0;
    for(int i = left + 1; i <= right; i++){
        if (vec[i] <= pivot)
            count++;
    }

    int pivotIndex = left + count;
    swap(vec[pivotIndex], vec[left]);
 
    // Sorting left and right parts of the pivot element
    int i = left, j = right;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (vec[i] <= pivot) {
            i++;
        }
    
        while (vec[j] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(vec[i++], vec[j--]);
        }
    }
 
    return pivotIndex;
}