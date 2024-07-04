/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:15:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/03 23:01:29 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_dptr_ast(t_cmd **cmd)
{
	int	i;

	i = 0;
	if (!*cmd)
		return ;
	if ((*cmd)->left)
		free_ast((*cmd)->left);
	if ((*cmd)->right)
		free_ast((*cmd)->right);
	if ((*cmd)->cmd)
		free_ast((*cmd)->cmd);
	if ((*cmd)->argv)
	{
		i = 0;
		while ((*cmd)->argv[i])
		{
			free((*cmd)->argv[i]);
			(*cmd)->argv[i] = NULL;
			i++;
		}
		free((*cmd)->argv);
		(*cmd)->argv = NULL;
	}
	if ((*cmd)->file)
	{
		free((*cmd)->file);
		(*cmd)->file = NULL;
	}
	if ((*cmd)->delim)
		free((*cmd)->delim);
	free((*cmd));
		*cmd = NULL;
}


void	free_ast(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->left)
		free_ast(cmd->left);
	if (cmd->right)
		free_ast(cmd->right);
	if (cmd->cmd)
		free_ast(cmd->cmd);
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			cmd->argv[i] = NULL;
			i++;
		}
		free(cmd->argv);
		cmd->argv = NULL;
	}
	if (cmd->file)
	{
		free(cmd->file);
		cmd->file = NULL;
	}
	if (cmd->delim)
		free(cmd->delim);
	free(cmd);
		cmd = NULL;
}

void	reset_ast(t_ms *s)
{
	if (s->ast)
	{
		free_ast(s->ast);
		s->ast = NULL;
	}
}
