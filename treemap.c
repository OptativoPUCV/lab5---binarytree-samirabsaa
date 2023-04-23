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
  /*comparar la clave del elemento a insertar con la clave del 
  nodo raíz si es mayor va a la derecha si es menor va a la izquierda, 
  si llegamos al final y no encontramos debemos reservar memoria */
  TreeNode* nuevoNodo = createTreeNode(key,value); 

  if(tree->root == NULL){ //caso de que raíz sea nula
    tree->root = nuevoNodo; 
    tree->current = nuevoNodo; 
  }
  else{
    tree->current = tree->root;
    
    while(tree->current!=NULL){ 
      //caso de existir y ser igual, se puede sobreescribir o hacer nada
      if(is_equal(tree, key, tree->current->pair->key)){ 
        return; 
      }
      
      if(tree->lower_than(key,tree->current->pair->key)==1){ //menor
        if(tree->current->left==NULL){
          tree->current->left = nuevoNodo;
          nuevoNodo->parent= tree->current;
        }
        tree->current= tree->current->left; 
      }
      else{ //if(tree->lower_than(key, tree->current->pair->key)==0){ //mayor
        if(tree->current->right==NULL){
          tree->current->right = nuevoNodo;
          nuevoNodo->parent= tree->current; 
        }
        tree->current= tree->current->right;
        
      }
    }
  } 
}


TreeNode * minimum(TreeNode * x){
  //caso base 
  //if(aux->left==NULL) return NULL;  
  while(x->left != NULL){
      x=x->left; 
  }
  return x;
  
}

void removeNode(TreeMap * tree, TreeNode* node) {

//CASO 1 -> NODO SIN HIJOS 
  if(node->left==NULL && node->right == NULL){
    if(node->parent!= NULL){
      if(node == node->parent->left){
        node->parent->left = NULL; 
        //free(node);
      }
      else{
        node->parent->right= NULL; 
        //free(node);
      }
    }
    else{
      tree->root = NULL;
    }
    free(node);
  }//CASO 2 -> NODO CON UN HIJO 
  else if(node->left == NULL || node->right == NULL){
    
    if(node->left!= NULL){ //IZQUIERDA
      node = node->left;
      node->parent->left = node->left; 
    }
    else{
      node->parent->left = node->right; 
    }

    if(node->right != NULL){ //DERECHA
      node = node->right; 
      node->parent->right = node->right; 
    }
    else{
      node->parent->right = node->left;
    }
    
    free(node); 
    node = NULL; 

  }
  else{ //CASO 3 -> NODO CON DOS HIJOS
    TreeNode *min = minimum(node->right);

    node->pair->key = min->pair->key; 
    node->pair->value = min->pair->value; 

    removeNode(tree, min);
    
  }
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
  TreeNode *node = tree->root; 
  Pair* aux = NULL; 

  while(node!= NULL){
    if(tree->lower_than(node->pair->key, key)==0){
    aux = node->pair; 
    node = node->left;
    }
    else{
      node = node->right;
    }
  }
    return aux;
}

Pair * firstTreeMap(TreeMap * tree) {

  TreeNode * node = tree->root; 
  Pair *aux = NULL; 

  while(node != NULL){
    aux = node->pair;
    node = node->left;
  }
    return aux;
}

Pair * nextTreeMap(TreeMap * tree) {
  //retorna el siguiente PAIR a partir del TreeNode * current
  //actualizar current 

  //CASO BASE
  if(tree == NULL)return NULL;

  TreeNode * current = minimum(tree->root); 
  
  
  
  if(current->right != NULL){
    current = current->right; 
    while(current->left != NULL){
      current = current->left; 
    }
  }
  else{
    TreeNode  * aux = current->parent; 
    while(aux != NULL && current == aux->right){
      current = aux; 
      aux = aux->parent; 
    }
    current = aux; 
  }
  return current->pair; 
  

}
