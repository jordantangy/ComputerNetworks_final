#include <iostream>
#include <string>
#include <vector>
using namespace std;



vector<int>& func(vector<int>& arr){

    arr[2] = 5;

   
   return arr;


}

int main(){
vector<int*> arr = {0,0};

int i = 3;
int* ptr = &i;

// for (size_t i = 0; i < arr.size(); i++)
// {
//     arr[i] = ptr;
// }

bool b = arr.empty();
cout << b << endl;




    
}