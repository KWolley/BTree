// btree.cpp

#include <iostream>
#include "btree.h"
#include <vector>
#include <cmath>

using namespace std;


// insert adds the given key into a b-tree rooted at 'root'.  If the
// key is already contained in the btree this should do nothing.
// 
// On exit: 
// -- the 'root' pointer should refer to the root of the
//    tree. (the root may change when we insert or remove)
// -- the btree pointed to by 'root' is valid.

	

btree* blind_insert(btree* insert_here, int key){
	int i = insert_here->num_keys - 1;
	while (key < insert_here->keys[i] && i >= 0){
		insert_here->keys[i + 1] = insert_here->keys[i];
		i--;
	}
	insert_here->keys[i+1] = key;
	insert_here->num_keys = insert_here->num_keys + 1;
	return insert_here; 
}

void split(btree* root, int key){
	int median_index = root->num_keys / 2; 
}

void insert(btree*& root, int key) {
	//call find to decide where the key should go
	btree* insert_here = find(root, key);
  if (insert_here == NULL) {
    cout << "ERROR find returned null;" << endl;
    return;
  }
	if(insert_here->num_keys < 4){ // check to see if num keys < 4
		insert_here = blind_insert(insert_here, key); // insert key in correct node
		return;
	}
  if (false) {
		blind_insert(insert_here, key);
    btree *left_child = make_leaf(insert_here->keys[0],insert_here->keys[1]);
    btree *right_child = make_leaf(insert_here->keys[3], insert_here->keys[4]);
    // adding children
    insert_here->num_keys = 1;
    insert_here->keys[0] = insert_here->keys[2];
    insert_here->children[0] = left_child;
    insert_here->children[1] = right_child;
    insert_here->is_leaf = false;
    return;
  }
  if (true) {
		blind_insert(insert_here, key);
    btree *left_child = make_leaf(insert_here->keys[0],insert_here->keys[1]);
    btree *right_child = make_leaf(insert_here->keys[3], insert_here->keys[4]);
    // adding children
    blind_with_kids(left_child, right_child)
    insert_here->num_keys = 1;
    insert_here->keys[0] = insert_here->keys[2];
    insert_here->children[0] = left_child;
    insert_here->children[1] = right_child;
    insert_here->is_leaf = false;
    return;
  }
}

btree* make_leaf(int key0, int key1) {
    btree* node = new btree;
    node->keys[0] = key0;
    node->keys[1] = key1;
    node->num_keys = 2;
    node->is_leaf = true;
    return node;
}

// remove deletes the given key from a b-tree rooted at 'root'. If the
// key is not in the btree this should do nothing.
//
// On exit:
// -- the 'root' pointer should refer to the root of the
//    tree. (the root may change when we insert or delete)
// -- the btree pointed to by 'root' is valid.

void remover(btree*& root, int key, int level, btree*& target){
	int child;
	if (target->is_leaf && (level == 0 || target->num_keys >= ceil(BTREE_ORDER / 2.0))) {
		for(int i = 0; target->num_keys; i++)
		{
			if(target->keys[i] == key) {
				for(int j = i + 1; j < target->num_keys; ++j) {
					target->keys[j - 1] = target->keys[j];
				}
				target->num_keys--;
				if (target->num_keys == 0) {
					delete target;
					root = nullptr;
					target = nullptr;
				}
				return;
			}
		}
	}
	for(child=0; child < root->num_keys; child++){
		if(key == root->keys[child]){
			//deal with current level
			return;
		}
		if(key < root->keys[child]){
			break;
		}
	}
	if(root->children[child]->num_keys < ceil(BTREE_ORDER/2.0)){
		if(child != root->num_keys && root->children[child + 1]->num_keys > ceil(BTREE_ORDER / 2.0)){
			root->children[child]->keys[root->children[child]->num_keys++]
				= root->children[child + 1]->keys[0];
			root->children[child]->children[root->children[child]->num_keys] 
				= root->children[child + 1]->children[0];
			for(int i = 1; i < root->children[child + 1]->num_keys; ++i){
				root->children[child + 1]->keys[i - 1] = root->children[child + 1]->keys[i];
			}
			for(int i = 1; i <= root->children[child + 1]->num_keys; ++i){
				root->children[child +1]->children[i-1] 
					=root->children[child +1]->children[i];
			}
			root->children[child + 1]->num_keys--;
		}
		else if(child > 0 && root->children[child - 1]->num_keys > ceil(BTREE_ORDER / 2.0)){
			for(int i = root->children[child]->num_keys-1; i >= 0; --i) {
				root->children[child]->keys[i + 1] = root->children[child]->keys[i];
			}
			for(int i = root->children[child]->num_keys; i >= 0; --i){
				root->children[child]->children[i-1] = root->children[child]->children[i];
			}
			root->children[child]->children[0] 
				= root->children[child-1]->children[root->children[child-1]->num_keys];
			root->children[child]->keys[0]
				= root->children[child - 1]->keys[--(root->children[child - 1]->num_keys)];
			root->children[child]->num_keys++;
		}
	}
}

void remove(btree*& root, int key) {
	if(root == NULL || root->num_keys == 0){
		return;
	}
	btree* found = find(root, key);
	int i;
	for(i = 0; i < found->num_keys; i++){
		if(found->keys[i] == key){
			break;
		}
		if(i+1 == found->num_keys){
			return;
		}
	} 
	remover(root, key, 0, found);
}



// find locates the node that either: (a) currently contains this key,
// or (b) the node that would contain it if we were to try to insert
// it.  Note that this always returns a non-null node.
btree* find(btree*& root, int key) {
	if(root->is_leaf){
		return root;
	}
	int i;
	for(i = 0; i < root->num_keys; i++){
		if(key == root->keys[i]){
			return root;
		}
		if(key < root->keys[i]){
			return find(root->children[i], key);
		}
	}
	
	return find(root->children[i], key);
}



int count_nodes(btree*& root) {
	if(root == NULL){
		return 0;
	}
	if(root->is_leaf){
		return 1;
	}
	int n = 1;
	for(int i=0; i <= root->num_keys; i++){
		n += count_nodes(root->children[i]);
	}
	return n; 
}

int count_keys(btree*& root) {
	if(root == NULL){
		return 0;
	}
	if(root->is_leaf){
		return root->num_keys;
	}
	int n = root->num_keys;
	for(int i = 0; i <= root->num_keys; i++){
		n+= count_keys(root->children[i]);
	}
	return n;
}

