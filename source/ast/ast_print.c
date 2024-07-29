/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:12:38 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/29 16:52:59 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (s->ast == NULL)
	{
		printf("empty input, nothing to print");
		return ;
	}
	if (ptr->type == EXEC)
	{
		print_ast_exec(s, ptr, padding);
	}
	else if (ptr->type == PIPE)
	{
		print_ast_pipe(s, ptr, padding);
	}
	else if (ptr->type == REDIR)
	{
		print_ast_redir(s, ptr, padding);
	}
	else if (ptr->type == HEREDOC)
	{
		print_ast_heredoc(s, ptr, padding);
	}
}

void	free2(char *one, char *two)
{
	if (one)
	{
		free(one);
		one = NULL;
	}
	if (two)
	{
		free(two);
		two = NULL;
	}
}

/* bak

void	print_ast(t_ms *s, t_cmd *ptr, int padding)
{
	int p;

	p=0;
	if (s->ast == NULL)
	{
		printf("empty input, nothing to print");
		return ;
	}
	if (ptr->type == EXEC)
	{
		print_ast_exec(s, ptr, padding)
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
		print_ast(s, ptr->left, padding);
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
		print_ast(s, ptr->cmd, padding);
	}
	else if (ptr->type == HEREDOC)
	{
		padding++;
		while (p++ < padding)
			printf("\t");
		p = 0;
		printf("type HEREDOC, \n");
		while (p++ < padding)
			printf("\t");
		p = 0;
		printf("DELIM: %s \n", ptr->delim);
		print_ast(s, ptr->cmd, padding);
	}
}
*/
