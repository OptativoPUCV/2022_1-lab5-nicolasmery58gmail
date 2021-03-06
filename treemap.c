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
  TreeMap * tree = (TreeMap*) malloc (sizeof(TreeMap));
  
  tree->lower_than = lower_than;
    return tree;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  TreeNode * aux;
  tree->current = tree->root;
  while(tree->current != NULL){
    if(is_equal(tree,key,tree->current->pair->key) == 1){
      return;
    }else{
      aux = createTreeNode(key,value);
      if(tree->lower_than(tree->current->pair->key,key) == 1){
        if(tree->current->right != NULL){
          tree->current = tree->current->right;
        }else{
          tree->current->right = aux;
          aux->parent = tree->current;
          tree->current = tree->current->right;
        }
      }else{
        if(tree->current->left != NULL){
          tree->current = tree->current->left;
        }else{
          tree->current->left = aux;
          aux->parent = tree->current;
          tree->current = tree->current->left;
        }
      }
    }
  }
}

TreeNode * minimum(TreeNode * x){

    while(x->left != NULL){
      x = x->left;
    }
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}



//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

Pair * searchTreeMap(TreeMap * tree, void* key) {
  TreeNode * aux = tree->root;
  while(aux != NULL){
    if (is_equal( tree, aux->pair->key, key) == 1){
      tree->current = aux;
      return aux->pair;
    }else{
      if(tree->lower_than(aux->pair->key,key) == 1){
        aux = aux->right;
      }else{
        aux = aux->left;
      }
    }
  }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
  Pair * aux;
  if(searchTreeMap(tree,key) != NULL){
    aux = searchTreeMap(tree,key);
  }else{
    if(tree->lower_than(tree->current->pair->key,key) != 1){
      return tree->current->pair;
    }
    aux = nextTreeMap(tree);
  }
  return aux;
}

Pair * firstTreeMap(TreeMap * tree) {
  TreeNode * node = tree->root;
  
  return minimum(node)->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  TreeNode * node;
  if(tree->current->right != NULL){
    node = minimum(tree->current->right);
  }else{
    while(tree->current->parent != NULL && tree->lower_than(tree->current->pair->key,tree->current->parent->pair->key) != 1){
      tree->current = tree->current->parent;
    }
    node = tree->current->parent;
  }
  tree->current = node;
  if(tree->current == NULL) return NULL;
  return node->pair;
}
