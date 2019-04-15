#include<iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
static const char* student_id = "0416313";

// do not edit prototype
void Insert(int *, int);
void Delete(int *, int);
int Select(int *, int);
int Rank(int *, int);

// data structure : 
// tree is an array with enough space
// tree[0] is the array size
// bundle three attribute as a node data
// First attribute is color, "0" means black, "1" means red , NIL is also "0", "-1" means no data
// Second attribute is key, "0" means NIL, "1"~"999" means data,  "-1" means no data
// Third attribute is size, for Dynamic Order Statistics, "0" means NIL , "-1" means no data
//
// for example,
// if tree[0] is "256" says that the array size is 256
//
// if tree[1] is "1" says that the place of 1 is a red node
//
// if tree[2] is "5" says that the place of 1 is key of 5
//
// if tree[8] is "-1" says that the place of 3 has nothing
//
// if tree[14] is "0" says that the place of 5 is a node of NIL
//
// if tree[19] is "66" says that the place of 7 is key of 66

//
// if there is an ambiguous situation, choose the smaller ( left ) one
//

//
// do your homework here
//
class node {
public:
	node();
	~node();
	int key;
	int color;
	int Dynamic;
	int rank;
	int order;
	node *parent;
	node *left;
	node *right;
	friend class redblacktree;
};

node::node() {
	left = right = parent = NULL;
	rank = 0;
	order = 0;
	Dynamic = 1;
}
node::~node() {}

class redblacktree {
public:
	redblacktree();
	~redblacktree();
	void left_rotate(redblacktree *, node *key);
	void right_rotate(redblacktree *, node *key);
	void insert_fixup(redblacktree *, node *key);
	void delete_fixup(redblacktree *, node *key);
	void transplant(redblacktree *, node *x1, node *x2);
	void bulid_tree(redblacktree *, int *tree);
	void bulid_array(redblacktree *, int *tree);
	void in(int *array, int index, node *targe);
	int preorder(redblacktree *t, int *tree, node *index);
	void postorder(redblacktree *t, node *index);
	int count(redblacktree *t, node *index, int i);
	node *root;
	node nill;
};
redblacktree::redblacktree() {
	nill.color = 0;
	nill.key = 0;
	nill.parent = nill.left = nill.right = &nill;
	nill.Dynamic = 0;
	nill.order = 0;
}
redblacktree::~redblacktree() {

}
void redblacktree::bulid_tree(redblacktree *t, int *tree) {
	//for (int i = 0; i < 50; i++)cout << tree[i] << " ";
	int flag = 1;
	node *tmp = NULL, *idx = NULL;
	t->root = &t->nill;
	idx = t->root;
	for (int i = 1; i < tree[0] - 2 && tree[i + 1] != -1;) {
		if(tree[i + 1] == 0)i = i + 3;
		else if (flag == 1) {
			tmp = new node;
			tmp->color = tree[i];
			tmp->key = tree[i + 1];
			tmp->Dynamic = tree[i + 2];
			tmp->left = &t->nill;
			tmp->right = &t->nill;
			tmp->parent = &t->nill;
			if (t->root == &t->nill) {
				t->root = tmp;
				idx = t->root;
				i = i + 3;
			}
			else {
				idx = t->root;
				flag = 0;
			}
		}
		else if (tree[i + 1] > idx->key) {
			if (idx->right != &t->nill) {
				idx = idx->right;
			}
			else {
				idx->right = tmp;
				tmp->parent = idx;
				i = i + 3;
				flag = 1;
			}
		}
		else if (tree[i + 1] <= idx->key) {
			if (idx->left != &t->nill) {
				idx = idx->left;
			}
			else {
				idx->left = tmp;
				tmp->parent = idx;
				i = i + 3;
				flag = 1;
			}
		}
	}
	//cout << (t->root == &t->nill);
	//system("pause");
}
void redblacktree::left_rotate(redblacktree *t, node *x) {
	node *y;
	int tmp;
	y = x->right;
	x->right = y->left;
	if (y->left != &t->nill) y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == &t->nill) t->root = y;
	else if (x == x->parent->left)  x->parent->left = y;
	else  x->parent->right = y;
	y->left = x;
	x->parent = y;
}
void redblacktree::right_rotate(redblacktree *t, node *x) {
	int tmp;
	node *y;
	y = x->left;
	x->left = y->right;
	if (y->right != &t->nill) y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == &t->nill) t->root = y;
	else if (x == x->parent->right)  x->parent->right = y;
	else  x->parent->left = y;
	y->right = x;
	x->parent = y;
}

void redblacktree::insert_fixup(redblacktree *t, node *x) {
	node *y;
	while (x->parent->color == 1) {
		if (x->parent == x->parent->parent->left) {
			y = x->parent->parent->right;
			if (y->color == 1) {
				x->parent->color = 0;
				y->color = 0;
				x->parent->parent->color = 1;
				x = x->parent->parent;
			}
			else if (x == x->parent->right) {
				x = x->parent;
				left_rotate(t, x);
			}
			x->parent->color = 0;
			x->parent->parent->color = 1;
			right_rotate(t, x->parent->parent);
		}
		else if (x->parent == x->parent->parent->right) {
			y = x->parent->parent->left;
			if (y->color == 1) {
				x->parent->color = 0;
				y->color = 0;
				x->parent->parent->color = 1;
				x = x->parent->parent;
			}
			else if (x == x->parent->left) {
				x = x->parent;
				right_rotate(t, x);
			}
			x->parent->color = 0;
			x->parent->parent->color = 1;
			left_rotate(t, x->parent->parent);
		}
		t->root->color = 0;
	}
}

void redblacktree::transplant(redblacktree *t, node *u, node *v) {
	if (u->parent == &nill) t->root = v;
	else if (u == u->parent->left) u->parent->left = v;
	else  u->parent->right = v;
	v->parent = u->parent;
}

void redblacktree::delete_fixup(redblacktree *t, node *x) {
	node *w;
	while (x != t->root && x->color == 0) {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == 1) {
				w->color = 0;
				x->parent->color = 1;
				left_rotate(t, x->parent);
				w = x->parent->right;
				//system("pause");
			}
			if (w->left->color == 0 && w->right->color == 0) {
				w->color = 1;
				x = x->parent;
			}
			else {
				if (w->right->color == 0) {
					w->left->color = 0;
					w->color = 1;
					right_rotate(t, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = 0;
				w->right->color = 0;
				left_rotate(t, x->parent);
				x = t->root;
			}
		}
		else if (x == x->parent->right) {
			w = x->parent->left;
			if (w->color == 1) {
				w->color = 0;
				x->parent->color = 1;
				right_rotate(t, x->parent);
				w = x->parent->left;
			}
			if (w->right->color == 0 && w->left->color == 0) {
				w->color = 1;
				x = x->parent;
			}
			else {
				if (w->left->color == 0) {
					w->right->color = 0;
					w->color = 1;
					left_rotate(t, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = 0;
				w->left->color = 0;
				right_rotate(t, x->parent);
				x = t->root;
			}
		}
	}
	x->color = 0;
}

void Insert(int * tree, int key) {
	redblacktree *t = new redblacktree;
	t->bulid_tree(t, tree);
	node *z = new node;
	z->parent = z->left = z->right = &t->nill;
	node *x, *y;
	x = t->root;
	y = &t->nill;
	z->key = key;
	while (x != &t->nill) {
		y = x;
		if (z->key < x->key)x = x->left;
		else x = x->right;
	}
	z->parent = y;	
	if (y == &t->nill) {
		t->root = z;
	}
	else if (z->key < y->key)y->left = z;
	else y->right = z;

	z->color = 1;
	t->insert_fixup(t, z);

	//tree[0] += 3;
	t->bulid_array(t, tree);
	//for (int i = 0; i < 50; i++)cout << tree[i] << " ";
}

void Delete(int * tree, int key) {
	int y_original_colcr;
	redblacktree *t = new redblacktree;
	t->bulid_tree(t, tree);
	node *z = t->root;
	node *y, *x;
	while (z != &t->nill) {
		if (key > z->key) z = z->right;
		else if (key < z->key)z = z->left;
		else if(key == z->key)break;
	}
	if (z == &t->nill) return;
	y = z;
	y_original_colcr = y->color;
	if (z->left == &t->nill) {
		x = z->right;
		t->transplant(t, z, z->right);
	}
	else if (z->right == &t->nill) {
		x = z->left;
		t->transplant(t, z, z->left);
	}
	else {
		y = z->left;
		while (y->right != &t->nill) y = y->right;
		y_original_colcr = y->color;
		x = y->left;
		if (y->parent == z) {
			if (x != &t->nill)x->parent = y;
		}
		else {
			t->transplant(t, y, y->left);
			y->left = z->left;
			y->left->parent = y;
		}
		t->transplant(t, z, y);
		y->right = z->right;
		y->right->parent = y;
		y->color = z->color;
	}
	if (y_original_colcr == 0) t->delete_fixup(t, y);

	//cout << t->root->left->left->key << " " << t->root->left->left->color << "\n";
	t->bulid_array(t, tree);
	//tree[0] -= 3;
	//delete z;
}

int Select(int * tree, int i) {
	// use Dynamic Order Statistics to return the i'th smallest element


	return -1;
}

int Rank(int * tree, int x) {
	// use Dynamic Order Statistics to return the rank of element x in the tree
	int i = 999;
	redblacktree *t = new redblacktree;
	t->bulid_tree(t, tree);
	node *z = t->root;
	while (z != &t->nill) {
		if (x > z->key) z = z->right;
		else if (x < z->key)z = z->left;
		else break;
	}
	i = t->count(t, z, i);
	return i;
}

int redblacktree::count(redblacktree *t, node *index, int i) {
	if (index->left == &t->nill || index->right == &t->nill) return 1;

	if (count(t, index->left, i) > count(t, index->right, i)) i = count(t, index->right, i);
	else i = count(t, index->left, i);
	return i + 1;
}

void redblacktree::bulid_array(redblacktree *t, int *tree) {
	for (int w = 1; w < tree[0]; w++) tree[w] = -1;
	int i;
	t->root->order = 1;
	i = preorder(t, tree, t->root);
	//cout << i << endl;
	int j = 2;
	for (int k = 2; k <= i; k += 3) {
		while (tree[j + 1] != -1) j += 3;
		if (tree[k] != -1 && j < k) {
			tree[j - 1] = tree[k - 1];
			tree[j] = tree[k];
			tree[j + 1] = tree[k + 1];
			tree[k - 1] = -1;
			tree[k] = -1;
			tree[k + 1] = -1;
		}
	}
	postorder(t, t->root);
}

int redblacktree::preorder(redblacktree *t, int *tree, node *index) {
	int tmp = (index->order - 1) * 3 + 3;
	//if (index->color != 0 || index->Dynamic != 0 || index->key != 0) {
		in(tree, (index->order - 1) * 3 + 1, index);
		if (index->left != &t->nill) {
			index->left->order = index->order * 2;
			index = index->left;
			if (tmp < preorder(t, tree, index))tmp = preorder(t, tree, index);
			index = index->parent;
		}
		else if (index->left == &t->nill) {
			int x = index->order * 2;
			in(tree, (x - 1) * 3 + 1, &nill);
		}

		if (index->right != &t->nill) {
			index->right->order = index->order * 2 + 1;
			index = index->right;
			if (tmp < preorder(t, tree, index))tmp = preorder(t, tree, index);
			index = index->parent;
		}
		else if (index->right == &t->nill) {
			int x = index->order * 2 + 1;
			in(tree, (x - 1) * 3 + 1, &nill);
		}
	//}
	return tmp;
}

void redblacktree::postorder(redblacktree *t, node *index) {
	node *tmp;
	if (index->color != 0 || index->Dynamic != 0 || index->key != 0) {
		if (index->left != &t->nill) {
			postorder(t, index->left);
		}
		if (index->right != &t->nill) {
			postorder(t, index->right);
		}
		tmp = index;
		index = index->parent;
		delete tmp;
	}
}

void redblacktree::in(int *array, int index, node *targe) {
	array[index] = targe->color;
	array[index + 1] = targe->key;
	array[index + 2] = targe->Dynamic;
}

/*int main() {
int tree[100] = { 28, 0,11,1 , 0,2,1 , 1,14,1 , 0,1,1 , 0,7,1 , 1,13,1 , 1,15,1 , 1,5,1 , 1,8,1};
redblacktree *rdt = new redblacktree;
//cout << Rank(tree, 11)<<endl;
//Insert(tree, 4);
Delete(tree,2);
for (int i = 0; i < 50; i++)cout << tree[i] << " ";
//cout << rdt->root->left->key << " " << rdt->root->left->color << "\n";
system("pause");
return 0;
}*/