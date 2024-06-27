/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:18 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/06/27 15:04:47 by cjoao-de         ###   ########.fr       */
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
	init_env[1] = ft_strdup("SHLVL=1");
	if (!init_env[1])
		free_and_error(init_env[0], NULL, init_env);
	init_env[2] = ft_strdup("_=/usr/bin/env");
	if (!init_env[2])
		free_and_error(init_env[0], init_env[1], init_env);
	init_env[3] = NULL;
	return (init_env);
}

	// if (!init_env[1])
	// {
	// 	free_and_error(init_env[0], init_env[1], NULL)
	// 	// free(init_env[0]);
	// 	// free(init_env);
	// 	// error_msg("strdup");
	// }
	// // TODO * Break Func Here
	// init_env[2] = ft_strdup("_=/usr/bin/env");
	// if (!init_env[2])
	// {
	// 	free_and_error(init_env[0], init_env[1], init_env)
	// 	// free(init_env[0]);
	// 	// free(init_env[1]);
	// 	// free(init_env);
	// 	// error_msg("strdup");
	// }

void	free_and_error(char *one, char *two, char **three)
{
	free(one);
	free(two);
	free(three);
	error_msg("strdup");
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
	total_len = key_len + value_len + 1;
	join = (char *)malloc(total_len + 1);
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

void	free_env_array(char **env_array)
{
	int	i;

	i = 0;
	if (!env_array)
		return ;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}
