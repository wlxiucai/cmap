/*************************************************************************
    > File Name: cmap.c
    > Author: wlxiucai
    > Mail: wlxiucai@foxmail.com
    > Created Time: Thu 16 Aug 2018 09:37:33 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmap.h"
typedef enum{
	CMAP_OK = 0,
	CMAP_FAIL_MALLOC = -1,
	CMAP_FAIL_EXIST = -2
}map_code;
typedef enum
{
	RED = 0,
	BLACK = 1
}map_color;
static inline void map_delete(rb_node* node)
{
	if (!node)
		return;
	if (!node->left && !node->right)
	{
		free(node->key);
		free(node->value);
		free(node);
		return;
	}
	printf("try delete have child node!!!!!\r\n");
}
static inline int isBlack(rb_node* node)
{
	return (node->__rb_parent_color & 3);
}
static inline void map_set_parent(rb_node* node, rb_node* parent)
{
	node->__rb_parent_color |= (unsigned long)parent;
}
static inline void map_set_color(rb_node* node, map_color color)
{
	if (color == RED)
		node->__rb_parent_color = (node->__rb_parent_color & ~3);
	else
		node->__rb_parent_color = (node->__rb_parent_color | 1);
}
static inline void map_color_flip(rb_node* node)
{
	map_set_color(node->left, !isBlack(node->left));
	map_set_color(node->right, !isBlack(node->right));
	map_set_color(node, !isBlack(node));
}
static inline rb_node* map_rotate_left(rb_node* node)
{
	if (node && node->right && !isBlack(node->right))
	{
		rb_node* temp = node->right;
		node->right = temp->left;
		temp->left = node;
		map_set_color(temp, isBlack(node));
		map_set_color(temp->left, RED);
		return temp;
	}
	return node;
}

static inline rb_node* map_rotate_right(rb_node* node)
{
	if (node && node->left && !isBlack(node->left))
	{
		rb_node* temp = node->left;
		node->left = temp->right;
		temp->right = node;
		map_set_color(temp, isBlack(node));
		map_set_color(temp->right, RED);
		return temp;
	}
	return node;
}
static inline rb_node* new_node(const char* key, const char* value)
{
	rb_node* node = (rb_node*)malloc(sizeof(*node));
	char* rb_key = (char*)malloc(strlen(key));
	char* rb_value = (char*)malloc(strlen(value));
	if (!node || !rb_key || !rb_value)
		return NULL;
	strcpy(rb_key, key);
	strcpy(rb_value, value);

	node->__rb_parent_color = RED;
	node->key = rb_key;
	node->value = rb_value;
	node->left = NULL;
	node->right = NULL;
	return node;
}
rb_node* map_put(rb_node* root, const char* key, const char* value)
{
	if (!root)
		return new_node(key, value);
	if (root->left && root->right && !isBlack(root->left) && !isBlack(root->right))
	{
		map_color_flip(root);
	}
	int temp = strcmp(key, root->key);
	if (temp == 0)
	{
		free(root->value);
		root->value = (char*)malloc(strlen(value));
		strcpy(root->value, value);
		return root;
	}
	else if (temp < 0)
		root->left = map_put(root->left, key, value);
	else
		root->right = map_put(root->right, key, value);
	if (root->right && !isBlack(root->right))
	{
		root = map_rotate_left(root);
	}
	if (root->left && root->left->left && !isBlack(root->left) && !isBlack(root->left->left))
	{
		root = map_rotate_right(root);
	}
	return root;
}
int map_get(rb_node* root, char* key, char* value)
{
	if (!root)
		return CMAP_FAIL_EXIST;
	int temp = strcmp(key, root->key);
	if (temp == 0)
	{
		strcpy(value, root->value);
		return CMAP_OK;
	}
	else if (temp < 0)
		return map_get(root->left, key, value);
	else
		return map_get(root->right, key, value);
}
void map_print(rb_node* root)
{
	if (!root)
		return;
	map_print(root->left);
	printf("[%s]:%s %s\t", root->key, root->value, isBlack(root)?"BLACK":"RED");
	map_print(root->right);
}
static inline rb_node* moveRedRight(rb_node* node)
{
	map_color_flip(node);
	if (node->left && node->left->left && !isBlack(node->left->left))
	{
		node = map_rotate_right(node);
		map_color_flip(node);
	}
	return node;
}
rb_node* fixup(rb_node* node)
{
	if (node->right && !isBlack(node->right))
	{
		node = map_rotate_left(node);
	}
	if (node->left && node->left->left && !isBlack(node->left) && !isBlack(node->left->left))
	{
		node = map_rotate_right(node);
	}
	if (node->left && node->right && !isBlack(node->left) && !isBlack(node->right))
		map_color_flip(node);
	return node;
}
rb_node* map_pop_max(rb_node* root)
{
	if (!root)
		return NULL;
	if (root->left && !isBlack(root->left))	
		root = map_rotate_right(root);
#if 0
	/*		为什么这样合理
	 *		因为基于2-3-4树，所以不可能有偏移过多的node存在
	 *		又因为这是左倾二叉树，当左节点为红点时，由于之上的判断会转移到右点
	 * */
#endif
	if (!root->right)					
	{
		if (root->left)
			printf("delete root->left\r\n");
		map_delete(root);
		return NULL;
	}
	if (root->right && isBlack(root->right) && (!root->right->left || isBlack(root->right->left)))
	{
		root = moveRedRight(root);
	}
	root->right = map_pop_max(root->right);
	return	fixup(root);
}
rb_node* moveRedLeft(rb_node* node)
{
	map_color_flip(node);
	if (node->right && node->right->left && !isBlack(node->right->left))
	{
		node->right = map_rotate_right(node->right);
		node = map_rotate_left(node);
		map_color_flip(node);
	}
	return node;
}
rb_node* map_pop_min(rb_node* root)
{
	if (!root)
		return NULL;
	if (!root->left)
	{
		if (root->right)
			printf("delete root->right");
		map_delete(root);
		return NULL;
	}
	if (root->left && isBlack(root->left) && (!root->left->left || isBlack(root->left->left)))
		root = moveRedLeft(root);
	root->left = map_pop_min(root->left);
	return fixup(root);
}
rb_node* map_get_min(rb_node* root)
{
	if (!root->left)
		return root;
	if (root->left)
		return map_get_min(root->left);
}
rb_node* map_pop_select(rb_node* root, const char* key)
{
	if (!root)
		return NULL;
	rb_node *left, *right;
	left = root->left;
	right = root->right;
	int cmp = strcmp(root->key, key);
	if (cmp > 0)
	{
		if (root->left && isBlack(root->left) && (!root->left->left || isBlack(root->left->left)))
			root = moveRedLeft(root);
		root->left = map_pop_select(root->left, key);
	}
	else
	{
		if (root->left && !isBlack(root->left))
			root = map_rotate_right(root);
		if (cmp == 0 && !root->right && !root->left)
		{
			map_delete(root);	
			return NULL;
		}
		if (root->right && isBlack(root->right) && (!root->right->left || isBlack(root->right->left)))
			root = moveRedRight(root);
		if (cmp == 0)
		{
			rb_node* temp = map_get_min(root);
			char* str_temp = root->key;
			root->key = temp->key;
			temp->key = str_temp;
			str_temp = root->value;
			root->value = temp->value;
			temp->value = str_temp;
			root->right = map_pop_min(root->right);
		}
		else
			root->right = map_pop_select(root->right, key);
	}
	return fixup(root);
}
rb_node* map_pop(rb_node* root, const char* key)
{
	if (!strcmp("___map_max", key))
	{
		root = map_pop_max(root);
		if (root)
			map_set_color(root, BLACK);
	}
	else if(!strcmp("___map_min", key))
	{
		root = map_pop_min(root);
		if (root)
			map_set_color(root, BLACK);
	}
	else
	{
		root = map_pop_select(root, key);
		if (root)
			map_set_color(root, BLACK);
	}
	return root;
}
void map_drop(rb_node* root)
{
	while (root)
		root = map_pop(root, "___map_max");
}
