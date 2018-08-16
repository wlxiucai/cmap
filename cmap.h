/*************************************************************************
    > File Name: cmap.h
    > Author: wlxiucai
    > Mail: wlxiucai@foxmail.com
    > Created Time: Thu 16 Aug 2018 09:37:29 AM CST
 ************************************************************************/

#ifndef __CMAP_H__
#define __CMAP_H__
struct Node
{
	unsigned long __rb_parent_color;								//color and parent point
	char* key;
	char* value;
	struct Node* left;
	struct Node* right;
} __attribute__((aligned(sizeof(long))));
typedef struct Node rb_node;
rb_node* map_put(rb_node* root, const char* key, const char* value);
int map_get(rb_node* root, char* key, char* value);
void map_print(rb_node* root);
rb_node* map_pop(rb_node* root, const char* key);
void map_drop(rb_node* root);
#endif
