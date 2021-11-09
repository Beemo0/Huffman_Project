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

void printList(Node* node) {
  if (!node)
    return;

    printf("Character: %c, Occurence: %d\n", node->box.name, node->box.freq);

    printList(node->next);
}

void AddChar(Node* node, char name) {
  if (node != NULL) {

    Node tmpNode_v;
    tmpNode_v.box = node->box;
    tmpNode_v.next = NULL;

    Box tmpBox_v;
    tmpBox_v.name = node->box.name;
    tmpBox_v.freq = 0;

    Node* tmpNode = malloc(sizeof(*tmpNode));
    tmpNode = &tmpNode_v;

    if (node->box.name == name)
        node->box.freq ++;

    else {
      if (node->next == NULL)
          node->next = tmpNode;
      else
          AddChar(node->next, name);
    }
  }
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
      AddChar(node, buffer);
      buffer = fgetc(file);
    }
    fclose(file);
    printList(node);
  }
  else printf("Error : file not found\n");



  return 0;
}
