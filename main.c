/*************************************************************************
    > File Name: main.c
    > Author: wlxiucai
    > Mail: wlxiucai@foxmail.com
    > Created Time: Thu 16 Aug 2018 10:19:52 AM CST
 ************************************************************************/

#include <stdio.h>
#include "cmap.h"
int main(void)
{
	char value[100];
	rb_node* root = NULL;
	root = map_put(root, "nihao1", "hello1");
	root = map_put(root, "nihao", "hello");
	root = map_put(root, "nihao2", "hello2");
	root = map_put(root, "age", "123");
	root = map_put(root, "age1", "123");
	root = map_put(root, "age2", "123");
	root = map_put(root, "age3", "123");
	root = map_put(root, "age4", "123");
	root = map_put(root, "age65", "123");
	root = map_put(root, "age342", "123");
	root = map_put(root, "age21", "123");
	root = map_put(root, "age43", "123");
	map_get(root, "nihao", value);
	printf("get [nihao] = %s\r\n\r\n", value);
	map_print(root);
	printf("\r\n");
}
