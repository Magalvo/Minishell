/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:12:38 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/09/23 15:20:41 by cjoao-de         ###   ########.fr       */
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
