#ifndef _MAXDEPTH_H_
#define _MAXDEPTH_H_

#include "treenode.h"


int maxDepth(TreeNode *root) {
	if(root == NULL) {
		return 0;
	}
	else {
		int left = maxDepth(root->left);
		int right = maxDepth(root->right);
		return 1 + (left >= right ? left : right);
	}
}

#endif /* _MAXDEPTH_H_ */
