#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

    TreeMap * new = (TreeMap*) malloc(sizeof(TreeMap));
    new->root = NULL; 
    new->current = NULL; 
    new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  /*comparar la claved del elemento a insertar con la clave del nodo raíz si es mayor va a la derecha si es menor va a la izquierda, si llegamos al final y no encontramos debemos reservar memoria */
  
  // ver los elemnetos que igresan a función (clave)
  /*TreeNode* nuevoNodo = createTreeMap(int (*lower_than)(void * key, void * value)); 

  if(tree->root == NULL){
    map->root = nuevoNodo; 
    map->current = nuevoNodo; 
    
  }
  else{
    //recorrer la estructura 
    TreeNode *current = map->root; 
    while(true){
      if(key < current->key){//nuevo nodod debiese ir a la izq MENOR
        if(current->left == NULL) current->left = nuevoNodo; 
        else if(){
          
        }
      
      }
      else if(key > current->key){// si nuevo nodo es MAYOR al current y clave 
        if(current->right == NULL) current->right = nuevoNodo; 
        else if (){
          
        }
        
      }
      else{// si la clave ya existe en este caso debemos sobreescribir o no hacer alguna acción
        return; 
      }    
    }
    
  }
  */
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  
  TreeNode * current;
  tree->current = tree->root; 

  while(current!= NULL){
      if(is_equal(tree,key,current->pair->key)){ 
        return current->pair->key; 
      }

    if(tree->lower_than( key, current->pair->key)==0){//derecha
            current = current->right;
    }
    else{
      current= current->right;  
    }

    return NULL; 
  //tree->current = NULL;
  //return 0; 
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
