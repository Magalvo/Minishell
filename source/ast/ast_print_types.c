/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:12:30 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/29 17:52:51 by cjoao-de         ###   ########.fr       */
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
		printf("type %sEXEC%s, args: \n", GREEN_B, RST);
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
		printf("type %sPIPE%s: \n", GREEN_B, RST);
		while (p++ < padding)
			printf("\t");
		p = 0;
		printf("%sLEFT leaf%s\n", BLUE_B, RST);
		print_ast(s, ptr->left, padding);
		while (p++ < padding)
			printf("\t");
		printf("%sRIGHT leaf%s\n", YELLOW_B, RST);
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
			printf("type %sREDIR > TRUNC%s:\n", GREEN_B, RST);
		else if (ptr->mode == 1089)
			printf("type %sREDIR > APPEND%s:\n", GREEN_B, RST);
		else if (ptr->mode == 0)
			printf("type %sREDIR < RDONLY%s:\n", GREEN_B, RST);
		while (p++ < padding)
			printf("\t");
		p = 0;
		printf("FILE: %s%s%s\n", MAGENTA_B, ptr->file, RST);
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
		printf("type %sHEREDOC%s:\n", GREEN_B, RST);
		while (p++ < padding)
			printf("\t");
		printf("DELIM: %s%s%s\n", MAGENTA_B, ptr->delim, RST);
		print_ast(s, ptr->cmd, padding);
	}
}
