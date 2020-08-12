#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <regex>
#include <vector>
using namespace std;


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

bool isEmpty(vector<packet*>& buffer){
  for (size_t i = 0; i < buffer.size(); i++)
  {
      if(buffer[i] != NULL){
        return false;
        break;
      }
  }
  return true;
}



iandB* thereIsSpace(vector<packet*>& buffer){
    
    int index = 0;
    bool b = false;
    int space_left = 0;
    packet* temp =  new packet();
    for (size_t i = 0; i < buffer.size(); i++)
    {
        temp = buffer.at(i);
        if(temp == NULL){
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

void processing_packets(vector<packet*>& buffer){

      int max_val = numeric_limits<int>::min();
      int temp = 0;
      int index = 0;
      int totransmit = 0;
      packet* p = new packet();
      for (size_t i = 0; i < buffer.size(); i++)
      {
        if(buffer[i] == NULL){
          continue;
        }
        temp = buffer[i]->value;
        if(temp > max_val){
          max_val = temp;
          index = i;
          totransmit = buffer[i]->value;
        }
      }

      for (size_t i = 0; i < buffer.size(); i++)
      {
        if(i == index){
          delete buffer[index];
              buffer[index] = NULL;

        }
       
      }
      
      
    transmitted_value += totransmit;
    transmitted_packets++;
}

void edf_algo(vector<packet*>& buffer,packet* p){

  iandB* result = thereIsSpace(buffer);
  if(result->b == true){
    buffer[result->index] = p;
    arrived_packets++;
  }
  else if(result->b == false){

      int min_value=0;
      int temp_value = 0;
      int toCompare = p->value;
      int index = 0;
      for (size_t i = 0; i < buffer.size(); i++)
      {
        temp_value = buffer[i]->value;
        if(temp_value <= toCompare){
          min_value = temp_value;
          index = i;
        }
      }
        if(min_value <= toCompare){
          buffer[index] = p;
          arrived_packets++;
          num_of_dropped_packs++;
        }
        else{
          num_of_dropped_packs++;
        }   
    }
  
}

int linesNum(string s){
  int number_of_lines = 0;
    std::string line;
    std::ifstream myfile(s);

    while (std::getline(myfile, line))
        ++number_of_lines;
   
    return number_of_lines;

}

int main(int argc, char *argv[]){

    int arr_size = atoi(argv[1]);
    vector<packet*> buffer(arr_size);
    ifstream file(argv[2]);
    int numOfLines = linesNum(argv[2]);
    int counter = 0;
    string line;
    string reader;
    int amount,slack,value = 0; 
    if(file.is_open()){
        while(getline(file,line)){
          counter++;
          reader.clear();
         for (size_t i = 0; i < line.size(); i++)
         {
           if(line[i]==' '){
             continue;
           }
           reader+=line[i];
           if(line[i]==')'){
            regex words_regex("[^(.,)!?]+");
            auto words_begin = sregex_iterator(reader.begin(), reader.end(), words_regex);
            auto words_end = sregex_iterator();

            vector<int> v;
           for (sregex_iterator i = words_begin; i != words_end; ++i){
               int a = stoi((*i).str());
               v.push_back(a);
           }
              amount = v[0]; 
              slack = v[1]; 
              value = v[2];
              v.clear();
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
         processing_packets(buffer);

         if(counter == numOfLines){
           while(!(isEmpty(buffer))){
             for (size_t i = 0; i < buffer.size(); i++)
              {
                  if(buffer[i] == NULL){
                    continue;
                  }
                  buffer[i]->slack -= 1;
                   if(buffer[i]->slack == 0){
                    delete buffer[i];
                    buffer[i] = NULL;
                    num_of_dropped_packs++;
                   }
              }
              if(isEmpty(buffer)){
                break;
              }
              processing_packets(buffer);
          }
        }
      }
    }
    else{
    cout << "Unable to open the file"; 
    }
    cout << "-------------BOUNDED DELAY POLICY-------------" << endl;
    cout << "total dropped packets:" << num_of_dropped_packs << endl;
    cout << "total arrived packets:" << arrived_packets << endl;
    cout << "total transmitted value:" << transmitted_value << endl;
    cout << "total transmitted packets:" << transmitted_packets << endl;
     cout << "---------------------------------------------" << endl;
    
}