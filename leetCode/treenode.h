
#ifndef _TREENODE_H_
#define _TREENODE_H_

#include <stdio.h>

typedef struct _TreeNode_ {
	int val;
	_TreeNode_ *left;
	_TreeNode_ *right;
	_TreeNode_(int x) : val(x), left(NULL), right(NULL) {}
}TreeNode;


#endif /* _TREENODE_H_ */
