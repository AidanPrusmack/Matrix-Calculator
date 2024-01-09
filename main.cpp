#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Node{

  float value;
  Node* right;
  Node* bottom;

};

Node* createNode(float data){
  Node* newNode = new Node();
  newNode->right = NULL;
  newNode->bottom = NULL;
  newNode->value = data;
  return newNode;
}

void insertNode(float data, Node** head, Node** node){
  Node* newNode = createNode(data);
  if(*node == NULL){
    *node = newNode;
    if (*head != NULL) {
      Node* temp = *head;
      while(temp->bottom != NULL){
        temp = temp->bottom;
      }
      temp->bottom = newNode;
    }
    else {
      *head = newNode;
    }
  }
  else{
    Node* temp = *node;
    while(temp->right != NULL){
      temp = temp->right;
    }
    temp->right = newNode;
  }
}

void printMatrix(ofstream& fout, Node* head, int rows, int columns){
  Node* row_ptr = head;
  Node* col_ptr = NULL;
  for(int i = 0; i < rows; i++){
    col_ptr = row_ptr;
    for(int j = 0; j < columns; j++){
      if(col_ptr != NULL){
        fout << fixed << setprecision(1) << col_ptr->value << " ";
        col_ptr = col_ptr->right;
      }
    }
    fout << "\n";
    if(row_ptr != NULL){
      row_ptr = row_ptr->bottom;
    }
  }
}

Node* addmatrices(Node* head_1, Node* head_2, int rows, int columns){
  Node* new_head = NULL;
  Node* new_node = NULL;

  Node* row_ptr_1 = head_1;
  Node* col_ptr_1 = NULL;
  Node* row_ptr_2 = head_2;
  Node* col_ptr_2 = NULL;

  for(int i = 0; i < rows; i++){
    col_ptr_1 = row_ptr_1;
    col_ptr_2 = row_ptr_2;

    for(int j = 0; j < columns; j++){
      if(col_ptr_1 != NULL && col_ptr_2 != NULL){
        float sum = col_ptr_1->value + col_ptr_2->value;
        insertNode(sum, &new_head, &new_node);
        col_ptr_1 = col_ptr_1->right;
        col_ptr_2 = col_ptr_2->right;
      }
    }

    if(row_ptr_1 != NULL){
      row_ptr_1 = row_ptr_1->bottom;
    }

    if(row_ptr_2 != NULL){
      row_ptr_2 = row_ptr_2->bottom;
    }

    if(new_node != NULL){
      new_node = new_node->bottom;
    }
  }
  return new_head;
}

Node* submatrices(Node* head_1, Node* head_2, int rows, int columns){
  Node* new_head = NULL;
  Node* new_node = NULL;

  Node* row_ptr_1 = head_1;
  Node* col_ptr_1 = NULL;
  Node* row_ptr_2 = head_2;
  Node* col_ptr_2 = NULL;

  for(int i = 0; i < rows; i++){
    col_ptr_1 = row_ptr_1;
    col_ptr_2 = row_ptr_2;

    for(int j = 0; j < columns; j++){
      if(col_ptr_1 != NULL && col_ptr_2 != NULL){
        float sum = col_ptr_1->value - col_ptr_2->value;
        insertNode(sum, &new_head, &new_node);
        col_ptr_1 = col_ptr_1->right;
        col_ptr_2 = col_ptr_2->right;
      }
    }

    if(row_ptr_1 != NULL){
      row_ptr_1 = row_ptr_1->bottom;
    }

    if(row_ptr_2 != NULL){
      row_ptr_2 = row_ptr_2->bottom;
    }

    if(new_node != NULL){
      new_node = new_node->bottom;
    }
  }
  return new_head;
}

Node* mulmatrices(Node* head_1, Node* head_2, int rows, int columns){
  Node* new_head = NULL;
  Node* new_node = NULL;

  Node* row_ptr_1 = head_1;
  Node* col_ptr_1 = NULL;
  Node* row_ptr_2 = head_2;
  Node* col_ptr_2 = NULL;

  for(int i = 0; i < rows * rows; i++){
    
    for(int j = 0; j < columns; j++){
      float sum = 0;
      col_ptr_1 = row_ptr_1;
      row_ptr_2 = head_2;

      for(int k = 0; k < columns; k++){
        col_ptr_2 = row_ptr_2;
        for(int l = 0; l < j; ++l){
          if(col_ptr_2 != NULL){
            col_ptr_2 = col_ptr_2->right;
          }
        }
        if(col_ptr_1 != NULL && col_ptr_2 != NULL){
          sum += col_ptr_1->value * col_ptr_2->value;
        }
        if(col_ptr_1 != NULL){
          col_ptr_1 = col_ptr_1->right;
        }
        if(col_ptr_2 != NULL){
          row_ptr_2 = row_ptr_2->bottom;
        }
      }
      insertNode(sum, &new_head, &new_node);

      row_ptr_2 = head_2;
    }
    if(row_ptr_1 != NULL){
      row_ptr_1 = row_ptr_1->bottom;
    }
    if(new_node != NULL){
      new_node = new_node->bottom;
    }
  }
  return new_head;
}

Node* traMatrix(Node* head, int rows, int columns){
  Node* new_head = NULL;
  Node* new_node = NULL;

  Node* origin = head;

  for(int i = 0; i < columns; i++){
    Node* row_ptr = origin;
    for(int j = 0; j < rows; j++){
      Node* col_ptr = row_ptr;
      for(int k = 0; k < i && col_ptr != NULL; k++){
        col_ptr = col_ptr->right;
      }
      if(col_ptr != NULL){
        float tempNum = col_ptr->value;
        insertNode(tempNum, &new_head, &new_node);
      }
      if(row_ptr != NULL){
        row_ptr = row_ptr->bottom;
      }
    }
    if(new_node != NULL){
      new_node = new_node->bottom;
    }
  }
  return new_head;
}

Node* shrinkMatrix(Node* head, int remove_rows, int remove_columns, int rows, int columns){
  Node* new_head = NULL;
  Node* new_node = NULL;
  Node* row_ptr = head;
  Node* col_ptr = NULL;
  for(int i = 0; i < rows; i++){
    if(i == remove_rows){
      row_ptr = row_ptr->bottom;
      continue;
    }
    col_ptr = row_ptr;
    for(int j = 0; j < columns; j++){
      if(j == remove_columns){
        col_ptr = col_ptr->right;
        continue;
      }
      insertNode(col_ptr->value, &new_head, &new_node);
      col_ptr = col_ptr->right;
    }
    row_ptr = row_ptr->bottom;
    new_node = new_node->bottom;
  }
  return new_head;
}

float detMatrix(Node* head, int rows){
  if(rows == 1){
    return head->value;
  }
  else if(rows == 2){
    Node* row_1 = head;
    Node* row_2 = row_1->bottom;
    float a = row_1->value;
    float b = row_1->right->value;
    float c = row_2->value;
    float d = row_2->right->value;
    return (a*d) - (b*c);
  }
  else{
    float determinant = 0;
    Node* row_1 = head;
    for(int i = 0; i < rows; i++){
      Node* col_ptr = row_1;
      for(int j = 0; j < i; j++){
        col_ptr = col_ptr->right;
      }
      determinant += pow(-1, i) * col_ptr->value * detMatrix(shrinkMatrix(head, 0, i, rows, rows), rows - 1);
    }
    return determinant;
  }
}

int main(){
  Node* head_1 = NULL;
  Node* head_2 = NULL;
  Node* node_1 = NULL;
  Node* node_2 = NULL;

  ifstream fin_1;
  ifstream fin_2;
  ofstream fout;

  string line;
  string command;

  cin >> command;

  int rows_1 = 0;
  int columns_1 = 0;
  int rows_2 = 0;
  int columns_2 = 0;
  float tempNum;

  fin_1.open("2_b.txt");
    while(getline(fin_1, line)){
      istringstream linestream(line);
      int current_col = 0;
      while(linestream >> tempNum){
        insertNode(tempNum, &head_1, &node_1);
        current_col++;
      }
      if(node_1 != NULL){
        rows_1++;
        if(columns_1 == 0){
          columns_1 = current_col;
        }
        node_1 = node_1->bottom;
      }
    }
  fin_1.close();

  fin_2.open("2_a.txt");
    while(getline(fin_2, line)){
      istringstream linestream(line);
      int current_col = 0;
      while(linestream >> tempNum){
        insertNode(tempNum, &head_2, &node_2);
        current_col++;
      }
      if(node_2 != NULL){
        rows_2++;
        if(columns_2 == 0){
          columns_2 = current_col;
        }
        node_2 = node_2->bottom;
      }
    }
  fin_2.close();
  
  Node* new_head = NULL;
  float determinant = 0;
  if(command == "add"){
    new_head = addmatrices(head_1, head_2, rows_1, columns_1);
  }
  else if(command == "sub"){
    new_head = submatrices(head_1, head_2, rows_1, columns_1);
  }
  else if(command == "mul"){
    new_head = mulmatrices(head_1, head_2, rows_1, columns_1);
  }
  else if(command == "tra"){
    new_head = traMatrix(head_1, rows_1, columns_1);
  }
  else if(command == "det"){
    determinant = detMatrix(head_1, rows_1);
  }
  
  if(command != "det"){
  fout.open("output.txt");
  printMatrix(fout, new_head, rows_1, columns_1);
  fout.close();
  }
  else if(command == "det"){
    fout.open("output.txt");
    fout << fixed << setprecision(1) << determinant;
    fout.close();
  }
  
  return 0;
}
