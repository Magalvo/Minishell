/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:12:30 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/25 12:15:36 by dde-maga         ###   ########.fr       */
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
		printf("%stype PIPE, \n", RED_B);
		while (p++ < padding)
			printf("\t");
		p = 0;
		printf("%sLEFT leaf, \n", GREEN_B);
		print_ast(s, ptr->left, padding);
		while (p++ < padding)
			printf("\t");
		printf("%sRIGHT leaf, \n", YELLOW_B);
		print_ast(s, ptr->right, padding);
	}
	printf("%s", RST);
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
		if (ptr->mode == 577)
			printf("%stype REDIR > TRUNC, \n", CYAN);
		else if (ptr->mode == 1089)
			printf("%stype REDIR > APPEND, \n", CYAN);
		else if (ptr->mode == 0)
			printf("%stype REDIR < RDONLY, \n", CYAN);
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
		printf("%stype HEREDOC, \n", CYAN);
		while (p++ < padding)
			printf("\t");
		printf("DELIM: %s \n", ptr->delim);
		print_ast(s, ptr->cmd, padding);
	}
}
