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
	root = map_put(root, "88", "hello1");
	root = map_put(root, "66", "hello");
	root = map_put(root, "90", "hello2");
	root = map_put(root, "30", "123");
	root = map_put(root, "35", "123");
	root = map_put(root, "38", "123");
	root = map_put(root, "40", "123");
	root = map_put(root, "45", "123");
	root = map_put(root, "50", "123");
	root = map_put(root, "36", "123");
	root = map_put(root, "39", "123");
	root = map_put(root, "48", "123");
	map_get(root, "nihao", value);
	printf("get [nihao] = %s\r\n\r\n", value);
	while (root)
	{
		map_print(root);
		printf("\n\n");
		root = map_pop(root, "40");
		sleep(10);
	}
}
