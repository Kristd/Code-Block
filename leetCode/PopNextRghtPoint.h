/*
 Given a binary tree

    struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
    }

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

    You may only use constant extra space.
    You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).

For example,
Given the following perfect binary tree,

         1
       /  \
      2    3
     / \  / \
    4  5  6  7

After calling your function, the tree should look like:

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL
*/

#ifndef _POPNEXTRIGHTPOINT_H_
#define _POPNEXTRIGHTPOINT_H_

struct TreeLinkNode {
	int val;
	TreeLinkNode *left, *right, *next;
	TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

void connect(TreeLinkNode *root) {
	TreeLinkNode* cur = root;
	TreeLinkNode* head = root;

	if(cur == NULL) {
		return;
	}

	while(cur->left != NULL) {
		while(cur) {
			cur->left->next = cur->right;
			if (cur->next != NULL) {
				cur->right->next = cur->next->left;
			}
			else {
				cur->right->next = NULL;
			}
			cur = cur->next;
		}
		cur = head->left;
		head = cur;
	}
}

#endif
