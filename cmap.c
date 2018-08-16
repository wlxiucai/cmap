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
	printf("[%s]:%s\t", root->key, root->value);
	map_print(root->right);
}
rb_node* map_pop(rb_node* root, const char* key)
{

}
void map_drop(rb_node* root)
{

}
