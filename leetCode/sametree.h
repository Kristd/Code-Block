
#ifndef _SAMETREE_H_
#define _SAMETREE_H_

#include "treenode.h"

bool isSameTree(TreeNode *p, TreeNode *q) {
	if(p == NULL && q == NULL) {
		return true;
	}

	if((q == NULL && p != NULL) || (p == NULL && q != NULL)){
		return false;
	}

	if(p->val != q->val){
		return false;
	}

	return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}


#endif /* _SAMETREE_H_ */
