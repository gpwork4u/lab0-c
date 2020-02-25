#include <stdio.h>
#include <string.h>

#include "queue.h"

void split(list_ele_t *source, list_ele_t **pre_head, list_ele_t **post_head)
{
    list_ele_t *fast, *slow;
    fast = source->next;
    slow = source;
    while (fast) {
        fast = fast->next;
        if (fast) {
            fast = fast->next;
            slow = slow->next;
        }
    }
    *pre_head = source;
    *post_head = slow->next;
    slow->next = NULL;
}

list_ele_t *merge(list_ele_t *pre_head, list_ele_t *post_head)
{
    list_ele_t *start, *current;
    start = pre_head;
    pre_head = pre_head->next;
    current = start;
    while (pre_head && post_head) {
        if (strcmp(pre_head->value, post_head->value) > 0) {
            current->next = post_head;
            post_head = post_head->next;
        } else {
            current->next = pre_head;
            pre_head = pre_head->next;
        }
        current = current->next;
    }
    if (pre_head)
        current->next = pre_head;
    else if (post_head)
        current->next = post_head;
    return start;
}

void merge_sort(list_ele_t **head)
{
    list_ele_t *pre_head, *post_head;
    if (!(*head))
        return;
    if (!(*head)->next)
        return;
    split(*head, &pre_head, &post_head);
    merge_sort(&pre_head);
    merge_sort(&post_head);
    if (strcmp(pre_head->value, post_head->value) <= 0) {
        *head = merge(pre_head, post_head);
    } else {
        *head = merge(post_head, pre_head);
    }
}
