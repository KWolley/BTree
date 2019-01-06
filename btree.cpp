// btree.cpp

#include <iostream>
#include <vector>
#include "btree.h"

using namespace std;

btree* make_leaf(vector<int> vals) {
    btree* node = new btree;
    for ( int i = 0; i = vals.size(); i++){
      node ->keys[i] = vals[i];
    }
    node->num_keys = vals.size();
    node->is_leaf = true;
    return node;
}

// find locates the node that either: (a) currently contains this key,
// or (b) the node that would contain it if we were to try to insert
// it.  Note that this always returns a non-null node.
btree* find(btree *&root, int key) {
  // if currently at root return
  if (root->is_leaf) {
    return root;
  }
  // find the smallest key
  int tmp;
  for (int i = 0 ; i < root -> num_keys; ++i){
    if (key <= root -> keys[i]){
      tmp = i;
      break;
    } 
    tmp = root -> num_keys;
  }
  //int i = key_slot(root, key);
  if (root->keys[tmp] == key) {
    return root;
  }
  return find(root->children[tmp], key);
}

int count_nodes(btree*& root) {
  // count keys in root
  if (root == NULL){
    return 0;
  }
  if (root -> is_leaf ){
    return 1;
  }
  int n = 1;
  for (int i = 0; i <= root -> num_keys; i++){
    n += count_nodes(root -> children[i]);
  }
  return n;
}

int count_keys(btree*& root) {
// count_keys returns the total number of keys stored in this
// btree. If the root node is null it returns zero; otherwise it
// returns the number of keys in the root plus however many keys are
// contained in valid child links.
  if (root -> is_leaf ){
    return root-> num_keys;;
  }
  int n = root -> num_keys;
  cout << n << endl;
  for (int i = 0; i <= root -> num_keys; i++){
    cout << root -> num_keys << endl;
    n += count_keys(root -> children[i]);
  }
  return n;
}

// rebuild tree
vector<int> get_data(btree *&root, vector <int> tree_data) {
 
  // for each node - find all keys and save in vector
  if (root == NULL){
    cout << "---------Tree empty----------------" << endl;
    return tree_data;
  }
  
  // if currently at root return
  if (root->is_leaf) {
    for (int i = 0 ; i <= root -> num_keys ; i++){
      tree_data.push_back(root -> keys[i]);
    }
    return tree_data;
  }

  for (int t = 0 ; t <= root -> num_keys ; ++t){
    tree_data = get_data(root->children[t], tree_data);
  }
}

// build tree
btree* build_tree(vector<int> input_data){
  

}

bool find_full(btree* root){
  // any changes to root will be visible outside of function
  if (root -> num_keys > 4){ // null and leaf are condidered the same in this context
    return true; // return true
  }
  //if (root != NULL) root->find_full(root);
  int i;  // initiate counter
  for (i = 0; i < root -> num_keys; i++){ // for each child
    if(root -> num_keys > 4){ // if root is full
      return true;  // return true
    }
    return find_full(root->children[i]); // recurse through each child of current node
  }
  return find_full(root->children[i]); // recurse through child i
}

// blindly insert key into a the given node 
// sorting also occurs for values in node
btree* blind_insert(btree* insert_here, int key) {
  int i = insert_here -> num_keys - 1;  // set i to # of keys - 1
  while (key < insert_here -> keys[i] && i >= 0){ // while the key < current key
    insert_here -> keys[i+1] = insert_here -> keys[i]; // shift key to the right
    i--; // decrement i
  } 
  insert_here -> keys[i+1] = key;  // when the key is found insert key
  insert_here -> num_keys = insert_here -> num_keys + 1; // reset num_keys of node
  return insert_here; // return pointer to node
}

// split tree will split the given node into two children
btree* split_node(btree* root){
  int median = root -> num_keys / 2; // find median
  vector<int> vals1;
  vector<int> vals2;
  for (int i = 0; i = root-> num_keys ; i++){
    if (i < median){
      vals1.push_back(root -> keys[i]);
    }
    if (i > median){
      vals2.push_back(root -> keys[i]);
    }
  }
  int median_val = root -> keys[median]; // save median int
  root == NULL; // clear root
  root -> keys[0] = median_val; // assign root to contain median int
  root -> children[0] = make_leaf(vals1); // create left leaf
  root -> children[1] = make_leaf(vals2); // create right leaf
}



btree* clean_tree(btree* root){
  // traverse BTree to check that a maximum of four keys are in each node

  // if (root -> is_leaf){ // null and leaf are condidered the same in this context
  //   return root;
  // }
  
  // case 1) if root is full and root is leaf
  if (root-> num_keys > 4 && root -> is_leaf){
    // call parse tree to split root nodes into two children
    root = split_node( root);
    return root;
  }
  // case 2) insert into leaf
  int i;  // initiate counter
  btree* parent = root;
  btree* cursor = root;
  for (i = 0; i < root -> num_keys; i++){ // for each child
    if(cursor -> num_keys > 4){ // if number of keys > 4 (full)
      int median_val = cursor -> keys[cursor -> num_keys / 2] ;
      parent = blind_insert(parent, median_val); // insert median to parent
      // create function 
      for ( int t = 0; t= parent->num_keys;t++){
        if (parent -> keys[t] == median_val){
          
        }
      }
      int indeces = parent -> keys[median_val];
    }
    // if( cursor -> keys[i] < root -> keys[i]){ // if key< the key in root index i move to child
    //   return find(root->children[i],indeces); // recurse through child i
    // }
  }
  return root; // recurse through child i

  while (root != NULL){
    for (int i = 0; i = root -> num_keys; i++){
      btree* parent = root;
      root = root -> children[i]; 
      if (root -> num_keys > 4 ){ //if child too many keys
        root = split_node(root);
      }
    } 

  }
  // implement find_full to see if any nodes are over-full

  // case 1) root is full
  // create new node (call init node?)
  int median = root -> num_keys / 2;
  int vals[] = {root -> keys[median]};
  
  // case 2) root is not full
}


void insert(btree*& root, int key) {
  // call find to decide where the key should go
  btree* insert_here = find(root,key);

  // if root is null
  if (insert_here == NULL){
    cout << "***ERROR - find returned NULL - node could not be found***" << endl;
  }

  // case 1 - there is room in the node for the new key to be added
  if (insert_here -> num_keys < 4){ // check if num keys < than 4
      insert_here = blind_insert(insert_here,key); // insert key in correct node - blind insert
      return;
  }
  // blindly insert data into assigned node
  btree* new_tree = blind_insert(insert_here,key);
  // clean tree
  //root = clean_tree(root);
  vector<int> tree_data;
}


btree* blind_delete(btree* del_here, int key) {
  // blindly delete key into a the given node 
  // sorting also occurs for values in node
  int num_orig_keys = del_here -> num_keys;
  int i = 0;  // set i to # of keys - 1
  int k = true;
  while (k){ // while the key < current key
    if (del_here -> keys[i] == key){
      del_here -> keys[i] == NULL;
      k = false; // save where i was deleted
    }
    i++; // decrement i
  }
  while (i < num_orig_keys){
    del_here -> keys[i-1] = del_here -> keys[i];
    i++;
  }
  del_here -> keys[num_orig_keys] = NULL;
  return del_here; // return pointer to node
}

void remove(btree*& root, int key) {
  // call find to decide where the key should go
  btree* del_here = find(root,key);

  // if root is null
  if (del_here == NULL){
    cout << "***ERROR - find returned NULL - node could not be found***" << endl;
  }

  // case 1 - node del_here is leaf
  if (del_here -> num_keys < 4 && del_here -> is_leaf){ // check if num keys < than 4
      cout << "node is leaf and full" << endl;
      del_here = blind_delete(del_here,key); // insert key in correct node - blind insert
      return;
  }

  // clean tree
  root = clean_tree(root);
  // any changes to root will be visible outside of function
  return;
  // TODO
}





