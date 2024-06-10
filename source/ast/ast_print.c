
#include "../../include/minishell.h"

void	print_2d(char **ptr, int padding)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	if (ptr == NULL)
		return ;
	while (ptr[i] != NULL)
	{
		while (p++ < padding)
			printf("\t");
		p = 0;
		printf("%s\n", ptr[i++]);
	}
}

void	print_ast(t_ms *s, t_cmd *ptr, int padding)
{
	int	p;

	p = 0;
	if (s->ast == NULL)
	{
		printf("empty input, nothing to print");
		return ;
	}
	if (ptr->type == EXEC)
	{
		padding++;
		while (p++ < padding)
			printf("\t");
		printf("type EXEC, args: \n");
		print_2d(ptr->argv, padding);
		p = 0;
	}
	else if (ptr->type == PIPE)
	{
		padding++;
		while (p++ < padding)
			printf("\t");
		p = 0;
		printf("type PIPE, \n");
		while (p++ < padding)
			printf("\t");
		p = 0;
		printf("LEFT leaf, \n");
		// if (ptr->left->type == PIPE)
		// padding++;
		print_ast(s, ptr->left, padding);
		// if (ptr->right->type == PIPE)
		// padding++;
		while (p++ < padding)
			printf("\t");
		p = 0;
		printf("RIGHT leaf, \n");
		print_ast(s, ptr->right, padding);
	}
	else if (ptr->type == REDIR)
	{
		padding++;
		while (p++ < padding)
			printf("\t");
		p = 0;
		printf("type REDIR, \n");
		while (p++ < padding)
			printf("\t");
		p = 0;
		printf("FILE: %s \n", ptr->file);
		// if (ptr->left->type == PIPE)
		// padding++;
		// print_ast(s, ptr->file, padding);
		// if (ptr->right->type == PIPE)
		// padding++;
	}
}
