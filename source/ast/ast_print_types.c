/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:12:30 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/29 09:15:48 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_ast_exec(t_ms *s, t_cmd *ptr, int padding)
{
	int	p;

	(void)s;
	p = 0;
	if (ptr->type == EXEC)
	{
		padding++;
		while (p++ < padding)
			printf("\t");
		printf("type EXEC, args: \n");
		print_2d(ptr->argv, padding);
		p = 0;
	}
}

void	print_ast_pipe(t_ms *s, t_cmd *ptr, int padding)
{
	int	p;

	p = 0;
	if (ptr->type == PIPE)
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
}

void	print_ast_redir(t_ms *s, t_cmd *ptr, int padding)
{
	int	p;

	p = 0;
	if (ptr->type == REDIR)
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
}

void	print_ast_heredoc(t_ms *s, t_cmd *ptr, int padding)
{
	int	p;

	p = 0;
	if (ptr->type == HEREDOC)
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
