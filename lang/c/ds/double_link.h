#ifndef _DOUBLE_LINK_H
#define _DOUBLE_LINK_H
// 新建“双向链表”。成功，返回表头；否则，返回NULL
extern int create_dlink();
// 销毁“双向链表”，成功，返回0；否则，返回-1
extern int destroy_dlink();

// “双向链表”是否为空。为空的话返回1；否则，返回0。
extern int dlink_is_empty();
// 返回“双向链表”大小
extern int dlink_size();

// 获取“双向链表”index位置的元素，成功返回结点指针，否则返回NULL
extern void* dlink_get(int index);
// 获取“双向链表中第1个元素”。成功，返回节点指针；否则，返回NULL。
extern void* dlink_get_first();
// 获取“双向链表中最后1个元素”。成功，返回节点指针；否则，返回NULL。
extern void* dlink_get_last();

// 查询元素value到“双向链表”index位置，成功返回0，否则返回-1
extern int dlink_insert(int index, void *pval);
// 将“value”插入到表头位置。成功，返回0；否则，返回-1。
extern int dlink_insert_first(void *pval);
// 将“value”插入到末尾位置。成功，返回0；否则，返回-1。
extern int dlink_append_last(void *pval);

// 删除“双向链表中index位置的节点”。成功，返回0；否则，返回-1
extern int dlink_delete(int index);
// 删除第一个节点。成功，返回0；否则，返回-1
extern int dlink_delete_first();
// 删除组后一个节点。成功，返回0；否则，返回-1
extern int dlink_delete_last();

#endif
