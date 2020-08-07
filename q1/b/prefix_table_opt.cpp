#include <iostream>
#include <string.h>
#include <algorithm>
#include <fstream>
using namespace std;
#define depth 34

int entry = 0;
int num_of_nodes = 1;

typedef struct node {
char number;
node* right;
node* left;
node* previous;
} Node;

string toBinary(string& ip_add){

	int num = stoi(ip_add);
	string ans;
	string zeros;
	int rest = 0;
	string temp;
	while(num != 0){
		 rest = num%2;
		 num /=2;
		temp += to_string(rest);
	}
	if(temp.size() != 8){
		int dif = 8-temp.size();
		for (size_t i = 0; i < dif; i++)
		{
			zeros += '0';
		}
	}

	reverse(temp.begin(),temp.end());
	ans = zeros + temp;
	return ans;
}


string string_parser(string& ip_add){
  string delimiter = ".";
  string ans;
  string partition;
  string temp;
  char c;
  int action;
	for (size_t i = 0; ip_add[i] != '\0'; i++)
	{
    action = ip_add[i];
    if(action >= 65 && action <=90){
      c = ip_add[i];
    }
		if(ip_add[i] != '.'){
			temp += ip_add[i];
		}
    
		else{  
    partition = toBinary(temp);
    ans += partition;
		temp.clear();
    partition.clear();
		}
	}
  partition = toBinary(temp);
  ans += partition;

    return ans+c;
}

void deallocate(Node* root){
    if (root == NULL){
      return;
    }
    else{
      deallocate(root->right);
      deallocate(root->left);
    }
    free(root);
}

void ADD(string& ip_add,Node* root){
  Node* copy = root;
  entry++;
  string s = string_parser(ip_add);
  if(entry == 1){
    for (size_t i = 0; i < s.size(); i++)
    {
        Node* n = (Node*)malloc(sizeof(Node));
        n->number = s[i];
        n->left = NULL;
        n->right = NULL;
        if(s[i] == '0'){
          n->previous = root;
          root->left = n;
          num_of_nodes++;
        }
        else{
           n->previous = root;
          root->right = n;
          num_of_nodes++;
        }
        root = n;
    }
  }
  else{
      root = copy;
    for (size_t i = 0; i < s.size(); i++)
    {
      
    
    /* 
    Optimization:
    First of all, if we are adding a totally different string to the trie, then eventually, this if statement won't
    happen. Because root->right and root->left are null at this stage (adding a new string).
    However, if we add a similar string, we want to check wether the next node has a different number than the actual 
    string we are working on.(for exemple it we are adding 1101 to the trie and 1100 already exist) so we want 
    to check the last bit. if they are different, let's check the action of the string of we want to add and the action
    that is already in the trie. If everythin matches, then we are changing the last bit to a "*" and we break the for loop
    cause there is nothing more to add.
    */
    ////////////****************************optimization*********************************////////////////
            if(i == 31){
            char right_char ;
            char left_char;
            char action;
              if(root->right != NULL){
                right_char = root->right->number;
                if(root->right->right != NULL && root->right->left == NULL) action = root->right->right->number;
                if(root->right->right == NULL && root->right->left != NULL) action = root->right->left->number;
                if( (right_char != s[i+1]) && (action ==s[i+2])){
                  root->right->number = '*';
                  break;
                }
              }
              else{
                if(root->left != NULL){
                left_char = root->left->number;
                if(root->left->left != NULL && root->left->right == NULL) action = root->left->left->number;
                if(root->left->left == NULL && root->left->right != NULL) action = root->left->right->number;
                if( (left_char != s[i+1]) && (action ==s[i+2])){
                  root->left->number = '*';
                  break;
              }
            }    
          }     
        }
    ////////////***************************optimization ends here********************************************////////////


      /*
          if the element is a letter (A,B,C....), then add it to the right place at the bottom of the trie.
      */
      int c = s[i];
      if(c >= 65 && c <= 90){
        
         Node* n = (Node*)malloc(sizeof(Node));
                num_of_nodes++;
                n->number = s[i];
                n->left = NULL;
                n->right = NULL;
                if(root->left == NULL && root->right == NULL){
                  n->previous = root;
                  root->right = n;
                  root = root->right;
                } 
                if(root->right != NULL && root->left == NULL){
                  root->left = n;
                  n->previous = root;
                } 
                if(root->right != NULL && root->left != NULL) throw "impossible to add another node";
                break;
      }
      ////////////////////////////////
        if(s[i] == '1'){
          if(root->right != NULL){
            root = root->right;
            continue;
          }
          else {
             Node* n = (Node*)malloc(sizeof(Node));
                num_of_nodes++;
                n->number = s[i];
                n->left = NULL;
                n->right = NULL;
                n->previous = root;
                root->right = n;
                root = root->right;
               
          }
        }
          else {
            if(root->left != NULL){
              root = root->left;
              continue;
            }
            else {
               Node* n = (Node*)malloc(sizeof(Node));
               num_of_nodes++;
                n->number = s[i];
                n->left = NULL;
                n->right = NULL;
                n->previous = root;
                root->left = n;
                root = root->left;
                
            }
          }
          
          
        }
    }
}

int FIND(string& ip_add,Node* root){
    string s = string_parser(ip_add);
    string buffer;
    char c ;
    for (size_t i = 0; i < s.size(); i++)
    {
      
        if(s[i] == '1'){
          if(root->right != NULL){
            buffer +=s[i];
          root = root->right;
          }
        }
          else {
            if(root->left != NULL){
              buffer +=s[i];
              root = root->left;
            }
          }
    }
 
  if ( s.substr(0,23) == buffer.substr(0,23)){
    
      return 1  ;
    }
return 0;
}

void remove(Node* last,Node* root){

     last = last->previous;
    if(last->right != NULL){
      num_of_nodes--;
      free(last->right);
    } 
    if(last->left != NULL){
      num_of_nodes--;
      free(last->left);
    } 
  while((last->right != NULL && last->left == NULL) || (last->right == NULL && last->left != NULL)){
     if(last->right != NULL){
       num_of_nodes--;
      free(last->right);
    } 
    else if(last->left != NULL){
      num_of_nodes--;
      free(last->left);
    }  
    last = last->previous;
    if(last == root){
      num_of_nodes--;
      free(last);   
      break;
    }
    
  }
}

int REMOVE(string& ip_add,Node* root){
      
   string bin_add = string_parser(ip_add);
  Node* copy = root;
   Node* last = NULL;
   char c = bin_add[32];
   // if the ip was found in the tree than search for the last node of this ip address
   if(FIND(ip_add,root) == 1 ){
    for (size_t i = 0; i < bin_add.size(); i++)
    {
        char c = bin_add[i];
        if(bin_add[i] == '1'){
          if(root->right != NULL){
            
          root = root->right;
          }
        }
          else {
            if(root->left != NULL){
              root = root->left;
             
            }
          }
          if(c >= 65 || c <= 90){
            if(root->right != NULL){
              if(root->right->number == bin_add[i]){
              last = root->right;
            }
          }
            
            else{
              if(root->left != NULL){
                 last = root->left;
              }
            }
          }
    }

// once the last node node was found, send it to remove function(it will remove node by node from the bottom to the top).
  remove(last,copy);
      
      return 1;    
  }
  return 0;

  
}
int main(){
  Node* root = (Node*)malloc(sizeof(Node));
  Node* theRoot = root;
  theRoot->number = '\0';
  string line;
  string ip_address;
  int action = 0;
  char c = 0;
  ifstream myfile ("file.txt");
  if (myfile.is_open())
  {
    while (getline (myfile,line))
    {
        int i = 0;
        action = 0; 
        while(line[i] != ' '){
        action++;
        i++;
        }

      if(action == 3 || action == 6){
        int start_add = i+1;
        int end = 0;
        int letter = 0;
        for (int j = i+1; j < line.size(); j++)
        { 
            letter = line[j];
             if(line[j] == ' '){
              end = j;
            }
            if(letter >= 65 && letter <= 90){
              c = letter;
            }
        }
        ip_address = line.substr(start_add);
      }
      else{
        ip_address = line.substr(action+1);
      }

      if(action == 3){
        ADD(ip_address,theRoot);
        cout << "-------------ADD-------------" << endl;
        cout <<  "Added: " << ip_address.c_str() << endl ;   
        cout << "at the depth " << depth << ", total nodes: " << num_of_nodes << endl;
        cout << "-----------------------------" << endl;


      }
      else if(action == 4){
       
       int s = FIND(ip_address,theRoot);
       if (s == 1){
         cout << "------------FIND-------------" << endl;
         cout << "Found "<< ip_address << endl; 
         cout << "with action : " << c << endl;
         cout << "at the depth " << depth << endl;
         cout << "-----------------------------" << endl;
       }
       else {
         cout << "------------FIND-------------" << endl;
         cout << "Unable to find this ip address because it wasn't added to the trie" << endl;
         cout << "-----------------------------" << endl;
       }
      }
      else{
       int ans =  REMOVE(ip_address,theRoot);
       if(ans == 1){
         cout << "-------------REMOVE-----------"<< endl;
         cout << "Removed: " << ip_address << endl;
         cout << "at the depth " << depth << endl;
         cout << "total nodes: " << num_of_nodes << endl;
         cout <<"-------------------------------" << endl;
       }
       else{
          cout << "-------------REMOVE-----------"<< endl;
          cout << "Unable to remove this ip address because it wasn't added to the trie" << endl;
          cout <<"-------------------------------" << endl;
       }
      }
    }
    myfile.close();
  }
  else{
    cout << "Unable to open the file"; 
  }
  deallocate(theRoot);
  return 0;
}