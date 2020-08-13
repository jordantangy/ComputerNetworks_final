#include <iostream>
#include <string.h>
#include <algorithm>
#include <fstream>
using namespace std;


int entry = 0;
int num_of_nodes = 1;
int g_depth = 0;



typedef struct node {
char number;
int depth;
char action;
node* right;
node* left;
node* previous;
} Node;


typedef struct trie {
Node* root;
} Trie;

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
    delete(root);
    root = NULL;
}

int ADD(string& ip_add,Node* root){
  string prfx;
  char letter;
  int flag = 0;
  for (size_t i = 0; i < ip_add.size(); i++)
  {
    if(ip_add[i] >= 65 && ip_add[i] <= 90){
      letter = ip_add[i];
    }
    if(ip_add[i] == '/'){
      flag = 1;
      continue;
    }
    if(flag == 1){
      if(ip_add[i] == ' '){
        continue;
      }
      prfx += ip_add[i];
    }
  }
  int prefix = stoi(prfx);
  
  string s = string_parser(ip_add);

    for (size_t i = 0; i < prefix; i++)
    {
 
        if(s[i] == '1'){
          if(root->right != NULL){
            root = root->right;
            continue;
          }
          else {
             Node* n = new Node();
                num_of_nodes++;
                n->number = s[i];
                n->left = NULL;
                n->right = NULL;
                n->previous = root;
                n->depth = n->previous->depth+1;
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
               Node* n = new Node();
               num_of_nodes++;
                n->number = s[i];
                n->left = NULL;
                n->right = NULL;
                n->previous = root;
                n->depth = n->previous->depth+1;
                root->left = n;
                root = root->left;
               
                
            }
          }
        }
        root->action = letter;   
        return root->depth;
    }


char FIND(string& ip_add,Node* root){
    string s = string_parser(ip_add);
    char c ;
    for (size_t i = 0; i < s.size(); i++)
    {
        if(s[i] == '1'){
          if(root->right != NULL){
            if(root->right->action >= 65 && root->right->action <= 90){
              c = root->right->action;
              g_depth = root->right->depth;
              return c;
            }
          root = root->right;
          }
          else{return 0;}
        }
          else {
            if(root->left != NULL){
              if(root->left->action >= 65 && root->left->action <= 90){
              c = root->left->action;
              g_depth = root->left->depth;
              return c;
            }
              root = root->left;
            }
            else{return 0;}
          }
    }
 
return 0;

}

void remove(Node* last,Node* root){

     last = last->previous;
    if(last->right != NULL){
      num_of_nodes--;
      delete(last->right);
    } 
    if(last->left != NULL){
      num_of_nodes--;
      delete(last->left);
    } 
  while((last->right != NULL && last->left == NULL) || (last->right == NULL && last->left != NULL)){
     if(last->right != NULL){
       num_of_nodes--;
      delete(last->right);
    } 
    else if(last->left != NULL){
      num_of_nodes--;
      delete(last->left);
    }  
    last = last->previous;
    if(last == root){
      num_of_nodes--;
      delete(last);  
      break;
    }
    
  }
}

int REMOVE(string& ip_add,Node* root){
  char ans = ip_add[ip_add.size()-1];
  string bin_add = string_parser(ip_add);
   Node* copy = root;
   Node* last = NULL;
   char c = bin_add[32];
   // if the ip was found in the tree than search for the last node of this ip address
   if(FIND(ip_add,root) == ans ){
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
int main(int argc, char *argv[]){
  Node* theRoot = new Node();
  theRoot->depth = 0;
  Trie* trie = new Trie();
  theRoot->number = '\0';
  trie->root = theRoot;
  string line;
  string ip_address;
  int action = 0;
  char c = 0;
  ifstream myfile (argv[1]);
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
        int ans = ADD(ip_address,theRoot);
        cout << "-------------ADD-------------" << endl;
        cout <<  "Added: " << ip_address.c_str() << endl ;   
        cout << "at the depth " << ans << ", total nodes: " << num_of_nodes << endl;
        cout << "-----------------------------" << endl;


      }
      else if(action == 4){
       
       char c = FIND(ip_address,theRoot);
       if (c != 0){
         cout << "------------FIND-------------" << endl;
         cout << "Found "<< ip_address << endl; 
         cout << "with action : " << c << endl;
         cout << "at the depth " << g_depth << endl;
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
         //cout << "at the depth " << depth << endl;
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