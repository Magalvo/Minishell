/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:54 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/27 19:58:02 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_env(char **env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env && env[i])
			free(env[i++]);
		free(env);
	}
	env = NULL;
}

void	clear_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->argv)
	{
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
	}
	if (cmd->left)
		clear_cmd(cmd->left);
	if (cmd->right)
		clear_cmd(cmd->right);
	if (cmd->cmd)
		clear_cmd(cmd->cmd);
	if (cmd->file)
		free(cmd->file);
	free(cmd);
}

void	free_env_list(t_env *list)
{
	t_env	*temp;

	while (list != NULL)
	{
		temp = list;
		list = list->next;
		free_node(temp);
	}
}

void	cleanup_shell(t_ms *s)
{
	if (s->env_tmp)
	{
		clear_env(s->env_tmp);
		s->env_tmp = NULL;
	}
	if (s->paths)
	{
		free_all_paths(s->paths);
		s->paths = NULL;
	}
}

void	set_exit(int stat, t_ms *s)
{
	if (s)
		s->exit_stat = stat;
	exit(stat);
}
