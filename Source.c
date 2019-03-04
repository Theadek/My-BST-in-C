#include <stdio.h>
#include <stdlib.h> //malloc

typedef struct Node {
	int value;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
}Node;

Node* initNode(int value,Node* parent){
	Node* p = (Node*)malloc(sizeof(Node));
	p->value = value;
	p->parent = parent;
	p->left = NULL;
	p->right = NULL;
	return p;
}

typedef struct Tree { //bst
	Node* root;
}Tree;

Tree* initTree() {
	Tree* p = (Tree*)malloc(sizeof(Tree));
	p->root = NULL;
	return p;
}

void addToTree(Tree* tree, int value) {
	if (tree->root == NULL){
		tree->root = initNode(value, NULL);
	}
	else {
		Node* pointer = tree->root;
		while (1) {
			if (value < pointer->value){
				if (pointer->left == NULL) { //dodawania do drzewa
					pointer->left = initNode(value, pointer);
					break;
				}
				else pointer = pointer->left;
			}
			else {
				if (pointer->right == NULL) {
					pointer->right = initNode(value, pointer);
					break;
				}
				else pointer = pointer->right;
			}
		}
	}
}

Node* searchInTree(Tree* tree, int value) {
	Node* pointer = tree->root;
	while (pointer->value != value && pointer != NULL) {
		if (value < pointer->value)pointer = pointer->left;
		else pointer = pointer->right;
	}
	return pointer;
}


void dFT(Tree* tree, Node* pointer) {
	if (pointer == NULL)return;
	if (pointer->left == NULL && pointer->right == NULL){
		if (pointer == tree->root) {
			tree->root = NULL;
		}
		else {
			if (pointer->parent->left == pointer)pointer->parent->left = NULL;
			else pointer->parent->right = NULL;
		}
		free(pointer);

	}
	else if (pointer->right != NULL && pointer->left == NULL) {
		if (pointer == tree->root) {
			tree->root = tree->root->right;
			free(tree->root->parent);
			tree->root->parent = NULL;
		}
		else {
			pointer->value = pointer->right->value;
			pointer = pointer->right;
			pointer->parent->left = pointer->left;
			pointer->parent->right = pointer->right;
			free(pointer);
		}
	}
	else if (pointer->right == NULL && pointer->left != NULL) {
		if (pointer == tree->root) {
			tree->root = tree->root->left;
			free(tree->root->parent);
			tree->root->parent = NULL;
		}
		else {
			pointer->value = pointer->left->value;
			pointer = pointer->left;
			pointer->parent->left = pointer->left;
			pointer->parent->right = pointer->right;
			free(pointer);
		}
	}
	else {
		Node* pointer2 = pointer->right;
		while (pointer2->left != NULL)pointer2 = pointer2->left;
		pointer->value = pointer2->value;
		dFT(tree, pointer2);
	}
}

void deleteFromTree(Tree* tree, int value) {
	Node* pointer = searchInTree(tree, value);
	dFT(tree, pointer);
}

int BSTCheck(Tree* tree, Node* node) {
	if (node->left != NULL)
		if (node->left->value > node->value)return 0;
		else if (BSTCheck(tree, node->left) == 0)return 0;
	if (node->right != NULL)
		if (node->right->value < node->value)return 0;
		else if (BSTCheck(tree, node->right) == 0)return 0;
	return 1;
}

int isBST(Tree* tree) {
	return BSTCheck(tree, tree->root);
}



int main() {
	Tree* drzewo = initTree();
	addToTree(drzewo, 5);
	addToTree(drzewo, 3);
	addToTree(drzewo, 4);
	addToTree(drzewo, 7);
	addToTree(drzewo, 2);
	addToTree(drzewo, 6);
	addToTree(drzewo, 9);
	addToTree(drzewo, 8);

	deleteFromTree(drzewo, 5);
	deleteFromTree(drzewo, 3);
	deleteFromTree(drzewo, 7);

	if (isBST(drzewo) == 1)printf("Jest BST\n");
	else printf("Nie jest BST\n");

	drzewo->root->value = 1000;

	if (isBST(drzewo) == 1)printf("Jest BST\n");
	else printf("Nie jest BST\n");

	return 0;
}