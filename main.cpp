#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int>numbers;
vector<int>times;
const int Iterations = 11;
string input_file, output_file, time_file, instance, algorithm_name;

void config_file_loading(){
        
    ifstream config_file("config.ini");
    if (config_file.is_open())
    {
        string line;
        while (getline(config_file, line))
        {
            if (line.find("input_file") != string::npos)
            {
                input_file = line.substr(line.find("=") + 2);
            }
            else if (line.find("output_file") != string::npos)
            {
                output_file = line.substr(line.find("=") + 2);
            }
            else if (line.find("time_file") != string::npos)
            {
                time_file = line.substr(line.find("=") + 2);
            }
            else if (line.find("instance") != string::npos)
            {
                instance = line.substr(line.find("=") + 2);
            }
            else if (line.find("algorithm_name") != string::npos)
            {
                algorithm_name = line.substr(line.find("=") + 2);
            }
        }
        config_file.close();
    }
    else
    {
        cout<<"Nie udało się otworzyć pliku konfiguracyjnego";
    }
}

void loading(){
    printf("\n\n\n");
    cout<< "\n\n\n\n\t\t\t\t\t\t\t" "Wait a minute :-)" <<endl;
}

void displayNumbers() {
    ifstream display{output_file};
    cout << display.rdbuf() << endl;

    // Pytanie użytkownika, czy zamknąć program
    string response;
    cout << "Czy chcesz zamknac program? Wpisz TAK, aby zamknac, lub NIE, aby kontynuowac." << endl;
    cin >> response;

    if (response == "TAK") {
        exit(0);
    }
}

void read(string input_file, int n) {
    ifstream read(input_file);
    if (read.is_open()) {
        string line;
        while (getline(read, line)) {
            stringstream ss(line);
            string number_str;
            while (getline(ss, number_str, ',') && n > 0) {
                int number = stoi(number_str);
                numbers.push_back(number);
                n--;
            }
            if (n == 0) {
                break;
            }
        }
        read.close();
    } else {
        cout << "Nie udało się wczytać pliku";
    }
}

void save(string output_file){
    ofstream save(output_file);
    if (save.is_open())
    {
        for (int i=0; i < numbers.size(); i++) 
        {
            save << numbers[i] << ", ";
	    }
        save.close();
    }
    else
    {
        cout<<"Nie udało się zapisać pliku";
    }

}

void bubble_sort(vector<int>& vec) {
    for (int i = 0; i < vec.size() - 1; ++i) {
        for (int j = 0; j < vec.size() - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                swap(vec[j], vec[j + 1]);
            }
        }
    }
}

void shake_sort(vector<int>& vec){
    int left = 0, right = vec.size() - 1;
    while (left < right) {
        for (int i = left; i < right; ++i) {
            if (vec[i] > vec[i + 1]) {
                swap(vec[i], vec[i + 1]);
            }
        }
        --right;
        for (int i = right; i > left; --i) {
            if (vec[i] < vec[i - 1]) {
                swap(vec[i], vec[i - 1]);
            }
        }
        ++left;
    }
}

void heapify(vector<int>& vec, int n, int i) {
    int largest = i; // indeks aktualnie największego elementu ustawiony na i
    int left = 2 * i + 1;
    int right = 2 * i + 2;
 
    if (left < n && vec[left] > vec[largest]) // Sprawdzenie czy lewy element jest większy od największego elementu
        largest = left;
 
    if (right < n && vec[right] > vec[largest])
        largest = right;
 
    if (largest != i) { // jeśli largest nie jest równy i (czyli największy element został zmieniony), zamień elementy i largest i wywołaj heapify dla largest
        swap(vec[i], vec[largest]);
        heapify(vec, n, largest);
    }
}
 
void heap_sort(vector<int>& vec) {
    int n = vec.size();
 
    for (int i = n / 2 - 1; i >= 0; i--) // utwórzenie kopca przez wywołanie heapify dla każdego elementu od połowy wektora do początku
        heapify(vec, n, i);
 
    for (int i = n - 1; i >= 0; i--) { // sortowanie elementów poprzez wymianę pierwszego (największego) elementu z ostatnim, utworzenie kopca z pozostałych elementów i powtarzanie procesu
        swap(vec[0], vec[i]); // zamiana pierwszego (największego) elementu z ostatnim
 
        heapify(vec, i, 0);  // utworzenie kopca z pozostałych elementów (bez ostatniego) i wywołaj heapify
    }
}

void bucket_sort(vector<int>& vec) {
    // Znalezienie wartości maksymalnej i minimalnej w wektorze
    int minValue = vec[0];
    int maxValue = vec[0];
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] < minValue) {
            minValue = vec[i];
        } else if (vec[i] > maxValue) {
            maxValue = vec[i];
        }
    }

    // Obliczenie szerokości przedziału dla każdego kubełka
    int bucketSize = ceil((double)(maxValue - minValue + 1) / vec.size());

    // Inicjalizacja kubełków
    vector<vector<int>> buckets(vec.size());

    for (int i = 0; i < vec.size(); i++) {
        int bucketIndex = (vec[i] - minValue) / bucketSize;
        buckets[bucketIndex].push_back(vec[i]);
    }

    for (int i = 0; i < buckets.size(); i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }

    // Sklejenie posortowanych kubełków w jedną posortowaną tablicę
    int index = 0;
    for (int i = 0; i < buckets.size(); i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            vec[index++] = buckets[i][j];
        }
    }
}

// Wybór algorytmu za pomocą pliku konfiguracyjnego
void algorithm(){
    if (algorithm_name == "bubble_sort") {
        bubble_sort(numbers);
    }
    else if (algorithm_name == "shake_sort") {
        shake_sort(numbers);
    }
    else if (algorithm_name == "heap_sort") {
        heap_sort(numbers);
    }
    else if (algorithm_name == "bucket_sort") {
        bucket_sort(numbers);
    }
    else {
        cout << "Nieznany typ sortowania: " << algorithm_name << endl;
    }
}

void save_time(string time_file)
{
    ofstream save_time(time_file);
    if (save_time.is_open())
    {
        save_time << "Czas wykonania operacji algorytmu " << algorithm_name <<  " dla "<< instance << " liczb: " <<endl;
        for (double time : times) {
            save_time <<time*10e-4 <<endl;
        }
        save_time.close();
    }
    else
    {
        cout << "Nie udało się zapisać czasu" << endl;
    }
}

int main(){

    loading();

    config_file_loading();
    
    read(input_file, stoi(instance));

    for (int i = 0; i < Iterations; i++)
    {
        auto begin = std::chrono::high_resolution_clock::now();

        algorithm();
    
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration<double, milli>(end - begin).count();

        times.push_back(elapsed);
    }

    save_time(time_file);
    save(output_file);

    string choice;
    cout << "Czy chcesz wyświetlic posortowane liczby?" << endl << " Wpisz TAK, aby wyswietlic, lub NIE, aby zakonczyc program." << endl;
    cin >> choice;

    if (choice == "Tak") {
    
    displayNumbers();
        
    } else if (choice == "Nie") {
        cout << "Nie wyświetlamy posortowanych liczb." << endl;
    } else {
        cout << "Niepoprawny wybór." << endl;
    }
    return 0;
}