#include <stdio.h>
#include <stdlib.h>

typedef struct Box {
  char name;
  int freq;
} Box;

typedef struct Node {
  Box box;
  struct Node* next;
} Node;

void printNode(Node* node) {
  if (!node) return;
  printf("Character: %c, Occurence: %d\n", node->box.name, node->box.freq);
  printNode(node->next);
}

int LenghtList(Node* node) {
  if (!node) return 0;
  return LenghtList(node->next)+1;
}

void AddChar(Node* node, char name) {
  if (node != NULL) {
    
    if (node->box.name == name) node->box.freq ++;
    
    else {
      if (node->next == NULL) {

        Node* new = malloc(sizeof(*new));

        if (!node || !new) exit(EXIT_FAILURE);

        new->box.name = name;
        new->box.freq = 1;

        node->next = new;    

      } else AddChar(node->next, name);
    }
  }
}

int main(int argc, char const *argv[]) {
  FILE* file = NULL;
  file = fopen("test.txt","r");
  if (file != NULL) {

    fseek(file,0,SEEK_SET); //set cursor to the beginning

    char buffer;
    buffer = fgetc(file); //get the first char

    Node node_v;
    node_v.box.name = buffer;
    node_v.box.freq = 0;
    node_v.next = NULL;

    Node* node = &node_v;

    while(buffer != EOF){
      AddChar(node, buffer);
      buffer = fgetc(file);
    }
    fclose(file);
    printNode(node);
    printf("lenght : %d\n", LenghtList(node));
  }
  else printf("Error : file not found\n");



  return 0;
}
