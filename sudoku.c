#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int i,j, k,p,cont, matrizaux[10];
  for(i=0; i<9; i++){
    for(cont=0; cont<10; cont++){
      matrizaux[cont]=0;
    }
      for(j=0; j<9; j++){
        if(n->sudo[i][j]!=0){
          if(matrizaux[n->sudo[i][j]] == 1) return 0;
        }
        matrizaux[n->sudo[i][j]] = 1;
      }
  }

  
  for(j=0; j<9; j++){
    for(cont=0; cont<10; cont++){
      matrizaux[cont]=0;
    }
    for(i=0; i<9; i++){
      if(n->sudo[i][j]!=0){
        if(matrizaux[n->sudo[i][j]] == 1) return 0;
      }
      matrizaux[n->sudo[i][j]] = 1;
    }
  }

  
  for(k=0; k<9; k++){
    for(cont=0; cont<10; cont++){
      matrizaux[cont]=0;
    }
    for(p=0; p<9; p++){ 
      i=3*(k/3) + (p/3) ;
      j=3*(k%3) + (p%3) ;
      if(n->sudo[i][j] != 0){ 
        if(matrizaux[n->sudo[i][j]] == 1){
          return 0;
        }
      }
      matrizaux[n->sudo[i][j]] = 1;
    }
  }
  return 1;
}

List* get_adj_nodes(Node* n){
    List* list=createList();
    int i,j,cont;
    for(i=0; i<9; i++){
      for(j=0; j<9; j++){
      if(n->sudo[i][j]==0){
        for(cont=1; cont<=9; cont++){
          Node* nuevo= copy(n);
          nuevo->sudo[i][j]= cont;
          if(is_valid(nuevo)){ 
            pushBack(list, nuevo);
          }
        }
        return list;
      }
    }
  }
  return list;
}



int is_final(Node* n){
  int i,j;
  for(i=0; i<9; i++){
      for(j=0; j<9; j++){
        if(n->sudo[i][j]==0){
          return 0;
          }
        }
      }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* S=createStack();
  push(S,initial);
  while (is_empty(S) == 0){
     Node* n = top(S);
     pop(S);
     if(is_final(n)){
       return n;
     }
     List* adj=get_adj_nodes(n);
     Node* aux= first(adj);
     while(aux != NULL){
        push(S,aux);
        aux=next(adj);
     }
  }

  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;*/
