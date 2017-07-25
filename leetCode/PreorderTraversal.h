/*
Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [1,2,3]. 
*/

#ifndef _PREORDERTRAVERSAL_H_
#define _PREORDERTRAVERSAL_H_

#include "treenode.h"
#include <vector>


void fn(TreeNode *root, vector<int>& vec) {
	if(root == NULL) {
		return;	
	}
	
	vec.push_back(root->val);
	fn(root->left, vec);
	fn(root->right, vec);
}

vector<int> preorderTraversal(TreeNode *root) {
	vector<int> vec(0);
	fn(root, vec);

	return vec;       
}

#endif /* _PREORDERTRAVERSAL_H_ */
