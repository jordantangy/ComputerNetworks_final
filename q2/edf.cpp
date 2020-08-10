#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

int num_of_dropped_packs = 0;
int arrived_packets = 0;
int transmitted_packets=0;
int transmitted_value = 0;





class packet{
  public:
  int slack;
  int value;

  packet(){
    this->slack = 0;
    this->value=0;
  }
  
  packet(int slack,int value){
    this->slack = slack;
    this->value = value;
  }
};

typedef struct indexAndBoolean{
  int index;
  bool b;
} iandB;



iandB* thereIsSpace(vector<packet*>& buffer){
    
    int index = 0;
    bool b = false;
    int space_left = 0;
    for (size_t i = 0; i < buffer.size(); i++)
    {
        if(buffer[i] == NULL){
          space_left++;
          index = i;
          break;  
        }
    }
    if(space_left > 0){
      
        b= true;
    }
    else{
      b = false;
    }
    
    iandB* i = new iandB();
    i->index = index;
    i->b = b;

    return i;
    
}

void transmitter(vector<packet*>& buffer){

      int max_val = 0;
      int temp = 0;

      packet* p = new packet();
      for (vector<packet*>::iterator it = buffer.begin() ; it != buffer.end(); it++)
      
      {
          temp =(*(it))->value ;
          if(temp > max_val){
            max_val = temp;
             p = *it;
          }
      }
              delete p;
              p = NULL;
              transmitted_value += max_val;
              transmitted_packets++;

}

void edf_algo(vector<packet*>& buffer,packet* p){

  iandB* result = thereIsSpace(buffer);
  if(result->b == true){
    buffer[result->index] = p;
    arrived_packets++;
  }
  else if(result->b == false){
      int min_slack=0;
      int temp_slack = 0;
      int toCompare = p->slack;
      int index = 0;
      for (size_t i = 0; i < buffer.size(); i++)
      {
        temp_slack = buffer[i]->slack;
        if(toCompare > temp_slack){
          min_slack = temp_slack;
          index = i;
        }
      }
        if(min_slack < toCompare){
          buffer.erase(buffer.begin()+index);
          buffer.push_back(p);
          num_of_dropped_packs++;
        }
        else{
          num_of_dropped_packs++;
        }   
  }
  
}


int main(int argc, char *argv[]){

    int arr_size = atoi(argv[1]);
    vector<packet*> buffer(arr_size);
    ifstream file(argv[2]);
    string line;
    string reader;
    int amount,slack,value,index = 0; 
    if(file.is_open()){
        while(getline(file,line)){
          reader.clear();
         for (size_t i = 0; i < line.size(); i++)
         {
           if(line[i]==' '){
             continue;
           }

           reader+=line[i];
           if(line[i]==')'){
           
              amount = reader[1]-'0'; //3
              slack = reader[3]-'0'; //4
              value = reader[5]-'0';//5
              for (size_t i = 0; i < amount; i++)
              {
              packet* p = new packet(slack,value);
              edf_algo(buffer,p);
                reader.clear();
              }
           }
         }
         for (size_t i = 0; i < buffer.size(); i++)
              {
                  
                  buffer[i]->slack -= 1;
              }
         transmitter(buffer);

     }
    }
    else{
    cout << "Unable to open the file"; 
    }
  for(packet* i : buffer){
      cout << i->slack<< ","<<i->value << endl;
    }
    cout << "dropped:" << num_of_dropped_packs << endl;
    cout << "arrived:" << arrived_packets << endl;
     cout << "val:" << transmitted_value << endl;
       cout << "transmitted packets:" << transmitted_packets << endl;
     
    
}