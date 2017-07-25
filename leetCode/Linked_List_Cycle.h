  ListNode *detectCycle(ListNode *head) {
		if(head == NULL || head->next == NULL) {
			return head;
		}

		ListNode* fptr = head;
		ListNode* sptr = head;

		while(fptr->next->next != NULL || sptr->next != NULL) {
			if(fptr->next->next == sptr->next) {
				return sptr->next;
			}

			fptr = fptr->next->next;
			sptr = sptr->next;
		}

		return NULL;
	}
