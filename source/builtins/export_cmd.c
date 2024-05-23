/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:58:59 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/23 17:55:02 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int export_cmd(t_ms *s, char **str)
{
	t_env	*env;
	t_env	*new_node;
	char	*key;
	char	*value;
	size_t	key_len;
	char	*delimiter;

	if (str[1] == NULL) 
		return (printf("\n"), 0);
	delimiter = ft_strchr(str[1], '=');
	if (!delimiter) 
		return (printf("Invalid format for export"), 0);
	key_len = delimiter - str[1];
	key = ft_substr(str[1], 0, key_len);
	value = ft_strdup(delimiter + 1);
	env = s->env;
	while (env) 
	{
		if (ft_strcmp(env->key, key) == 0)  //! Update the value
		{
			free(env->value);
			env->value = value;
			free(key);
			return (1);
		}
		env = env->next;
	}
	new_node = new_env_node(str[1]); //! If the key was not found, add a new node
	if (!new_node) 
	{
		free(key);
		free(value);
		return (error_msg("Failed to create new env node"), 0);
	}
	if (!s->env) //! Append the new node to the end of the list
		s->env = new_node;
	else 
	{
		env = s->env;
		while (env->next) 
			env = env->next;
		env->next = new_node;
		new_node->prev = env;
	}
	free(key);
	return (1);
}


/*  int	export_cmd(t_ms *s, char **cmds)
{
	char **envp;
	int i = 0;

	envp = s->env_tmp;
	while (*envp)
	{
		if (s->cmd_temp[1] != NULL && (ft_strcount(s->cmd_temp[1], '=') == 1))
		{
			while (ft_isalnum(s->cmd_temp[1][i]) && )
			{
				env->value = cmd->cmd_args[1];
			}
			else if (cmd->cmd_args[1] || env->value == NULL)
			{
				add_env_node();
				printf("exporting...");
				break;
			}
			envp++;
		}
		else
			return(error_msg("Export need Args!"), 0);
	}
	return (1);
} */

