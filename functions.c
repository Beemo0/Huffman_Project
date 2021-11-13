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
    printf("Character: %c, Occurence: %d\n", node->box.name, node->box.freq);
}

Node* AddChar(Node* node, char name) {
  if (node != NULL) {

    printf("char in node %c occ : %d\n", node->box.name, node->box.freq);

    if (node->box.name == name) {
      node->box.freq ++;
      printf("Node occ ++\n");
      return node;
    }

    else {
      if (node->next == NULL) {
        printf("New node created\n");
        Box tmpBox_v;
        tmpBox_v.name = name;
        tmpBox_v.freq = 1;

        Node tmpNode_v;
        tmpNode_v.box = tmpBox_v;
        tmpNode_v.next = NULL;
        
        node->next = malloc(sizeof(*node->next));
        node->next = &tmpNode_v;
        printf("char : %c occ : %d\n",node->next->box.name, node->next->box.freq);
        return node;
      }
      else {
        printf("go to the next node %c \n", node->next->box.name);
        node->next = AddChar(node->next, name);
      }
    }
  }
  return node;
}

int main(int argc, char const *argv[]) {
  FILE* file = NULL;
  file = fopen("test.txt", "r");

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
      printf("on place : %c\n", buffer );
      node = AddChar(node, buffer);
      buffer = fgetc(file);
    }
    fclose(file);
    printNode(node);
    printNode(node->next);
    printNode(node->next->next);
  }
  else printf("Error : file not found\n");



  return 0;
}
