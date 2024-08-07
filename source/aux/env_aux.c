/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:18 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/30 16:01:32 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_cwd(void)
{
	char	*cwd;

	cwd = malloc(1024);
	if (!cwd)
		error_msg("find_cwd");
	if (!getcwd(cwd, 1024))
	{
		free(cwd);
		return (NULL);
	}
	return (cwd);
}

void	free_and_error(char *one, char *two, char **three)
{
	free(one);
	free(two);
	free(three);
	three = NULL;
	error_msg("strdup");
}

char	**null_env_init(void)
{
	char	**init_env;
	char	*cwd;
	size_t	key_len;
	size_t	cwd_len;

	init_env = ft_calloc(5, sizeof(char *));
	if (!init_env)
		error_msg("malloc nulla");
	cwd = find_cwd();
	key_len = ft_strlen("PWD=");
	cwd_len = ft_strlen(cwd);
	init_env[0] = ft_calloc(key_len + cwd_len + 1, sizeof(char));
	if (!init_env[0])
		return (free(cwd), error_msg("malloc"), init_env);
	ft_strlcpy(init_env[0], "PWD=", key_len + 1);
	ft_strlcpy(init_env[0] + key_len, cwd, cwd_len + 1);
	free(cwd);
	init_env[1] = ft_strdup("SHLVL=0");
	init_env[2] = ft_strdup("_=/usr/bin/env");
	if (!init_env[2] || !init_env[1])
		free_and_error(init_env[0], init_env[1], init_env);
	init_env[3] = NULL;
	return (init_env);
}

void	initialize_env(char ***envp)
{
	if (!(*envp) || !(*envp)[0])
		*envp = null_env_init();
}

char	*join_key_value(const char *key, const char *value)
{
	size_t	key_len;
	size_t	value_len;
	size_t	total_len;
	char	*join;

	key_len = ft_strlen(key);
	if (value)
		value_len = ft_strlen(value);
	else
		value_len = 0;
	total_len = key_len + value_len + 2;
	join = ft_calloc((total_len + 1), sizeof(char));
	if (!join)
		return (NULL);
	ft_strlcpy(join, key, key_len + 1);
	if (value)
	{
		join[key_len] = '=';
		ft_strlcpy(join + key_len + 1, value, value_len + 1);
	}
	else
		join[key_len] = '\0';
	return (join);
}
