/*
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [1,3,2]. 
*/


#ifndef _INORDERTRAVERSAL_H_
#define _INORDERTRAVERSAL_H_

#include <stack>

typedef struct _TreeNode_ {
	int val;
	_TreeNode_ *left;
	_TreeNode_ *right;
	_TreeNode_(int x) : val(x), left(NULL), right(NULL) {}
}TreeNode;

vector<int> inorderTraversal(TreeNode *root) {
	vector<int> vec;
	stack<TreeNode*> st;
	TreeNode* cur = root;
	
	while(cur != NULL || st.size() != 0) {
		if(cur) {
			st.push(cur);
			cur = cur->left;
		}
		else if(st.size() != 0) {
			vec.push_back(st.top()->val);
			cur = st.top()->right;
			st.pop();
		}
	}
	return vec;
}

#endif
