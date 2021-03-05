
#ifndef __SD_BUFFER_H
#define __SD_BUFFER_H

//缓存节点
struct sd_buffer_node {
  struct sd_buffer_node *next; //下个缓存节点
  void *buffer; //缓存
  int size; //当前未发送的缓存大小
  //int maxn; //buff的最大大小
};

//缓存列表
struct sd_buffer {
  int size; //当前未发送的缓存大小
  struct sd_buffer_node *head;
  struct sd_buffer_node *tail;
};

extern int sd_buffer_init(struct sd_buffer *list);
//增加写缓存
extern int sd_buffer_append(struct sd_buffer *list, void *buffer, int sz);
//释放写缓存
extern int sd_buffer_destroy(struct sd_buffer *list);
//移动
extern int sd_buffer_memmov(struct sd_buffer *list, size_t n);
//下一次写入数据块指针
extern void* sd_buffer_nextdata(struct sd_buffer *list);
//下一次写入数据块大小
extern int sd_buffer_nextsize(struct sd_buffer *list);

#define sd_buffer_foreach(pos, head) \
  for (pos = head; pos; pos = pos->next)

#endif //__SD_BUFFER_H
