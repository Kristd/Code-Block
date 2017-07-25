/*
Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3. 
*/

#ifndef _REMOVEDUPLFROMSORTLIST_H_
#define _REMOVEDUPLFROMSORTLIST_H_

struct ListNode {
    int val;
    ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

ListNode *deleteDuplicates(ListNode *head) {
	if(head == NULL) {
		return NULL;
	}

	ListNode* cur = head;
	
	while(cur->next != NULL) {
		if((cur->val^cur->next->val) == 0) {
			cur->next = cur->next->next;
			continue;
		}
		else {
			cur = cur->next;
		}
	}

	return head;
}

#endif
