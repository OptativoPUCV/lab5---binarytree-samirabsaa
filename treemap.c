#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"
#include <stdbool.h>

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
  /*comparar la clave del elemento a insertar con la clave del nodo raíz si es mayor va a la derecha si es menor va a la izquierda, si llegamos al final y no encontramos debemos reservar memoria */
  TreeNode* nuevoNodo = createTreeNode(key,value); 

  if(tree->root == NULL){
    tree->root = nuevoNodo; 
    tree->current = nuevoNodo; 
  }
  else{
    tree->current = tree->root;
    while(true){
      if(tree->lower_than(key,tree->current->pair->key)==0){
        if(tree->current->right==NULL){
          tree->current->right = nuevoNodo; 
          break; 
        }
        tree->current= tree->current->right; 
      }
      else if(tree->lower_than(key, tree->current->pair->key)==1){
        if(tree->current->left==NULL){
          tree->current->left = nuevoNodo; 
          break; 
        }
        tree->current= tree->current->left;
        
      }
      else{
        //actualizar valor o no hacer acción 
        //tree->current->pair->value = value;
        return;
      }
    }
  } 
}


  /*else{ //hacer búsqueda la estructura nuevo_dato y  
    TreeNode *current = tree->root; 
    while(true){
      if(key < current->pair->key){//nuevo nodod debiese ir a la izq MENOR
        if(current->left == NULL) current->left = nuevoNodo; 
      }
      else if(key > current->pair->key){// si nuevo nodo es MAYOR al current y clave 
        if(current->right == NULL) current->right = nuevoNodo; 
        //else if (){
          
        //}
        
      }
      else{// si la clave ya existe en este caso debemos sobreescribir o no hacer alguna acción
        return; 
      }    
    }
    
  }
}*/

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
  tree->current = tree->root;
  
  while(tree->current!= NULL){
    if(is_equal(tree,key,tree->current->pair->key)){ 
      return tree->current->pair; 
    }
    else if(tree->lower_than( key, tree->current->pair->key)==0){ //derecha
      tree->current = tree->current->right;
    }
    else if (tree->lower_than(key, tree->current->pair->key)==1){ //izquierda
      tree->current= tree->current->left;  
    }
  }
    return NULL; 
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
