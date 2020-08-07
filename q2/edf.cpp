#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void edf_algo(){

}

int main(int argc, char *argv[]){

    int queue_size = atoi(argv[1]);
    string file_name = argv[2];
    ifstream file(argv[2]);
    cout << queue_size << endl;
    cout << file_name << endl;
    
}