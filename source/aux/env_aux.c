#include "../../include/minishell.h"

//! ========================== NULL_ENV_CREATION =======================================//

char	*find_cwd()
{
	char *cwd;

	cwd = malloc(1024);
	if (!cwd)
		error_msg("find_cwd");
	if (!getcwd(cwd, 1024))
	{
		free(cwd);
		error_msg("getcwd");
	}
	return (cwd);
}

char	**null_env_init()
{
	char	**init_env;
	char	*cwd;
	size_t	key_len;
	size_t	cwd_len;

	init_env = malloc(sizeof(char *) * 5);
	if (!init_env)
		error_msg("malloc nulla");
	cwd = find_cwd();
	key_len = ft_strlen("PWD=");
	cwd_len = ft_strlen(cwd);
	init_env[0] = malloc(key_len + cwd_len + 1);
	if (!init_env[0])
	{
		free(cwd);
		error_msg("malloc");
	}
	ft_strlcpy(init_env[0], "PWD=", key_len + 1);
	ft_strlcpy(init_env[0] + key_len, cwd, cwd_len + 1);
	free(cwd);

	//* Break Func Here

	init_env[1] = ft_strdup("SHLVL=1");
	if (!init_env[1])
	{
		free(init_env[0]);
		free(init_env);
		error_msg("strdup");
	}

	//* Break Func Here

	init_env[2] = ft_strdup("_=/usr/bin/env");
	if(!init_env[2])
	{
		free(init_env[0]);
		free(init_env[1]);
		free(init_env);
		error_msg("strdup");
	}

	init_env[3] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin");
	if(!init_env[3])
	{
		free(init_env[0]);
		free(init_env[1]);
		free(init_env[2]);
		free(init_env);
		error_msg("strdup");
	}

	init_env[4] = NULL;
	return (init_env);
}	

void initialize_env(char ***envp) 
{
	if (!(*envp) || !(*envp)[0]) 
		*envp = null_env_init();
}
//! ===============================================================================//


//! ========================== ENV_ARRAY_UPDATE =======================================//
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
		error_msg("join malloc env");
	ft_strlcpy(join, key, key_len + 1);
	//ft_strjoin(join, key);				//? posso usar strjoin em vez de alocar?
	if(value)
	{
		join[key_len]= '=';
		ft_strlcpy(join + key_len + 1, value, value_len + 1);
	}
/* 	else
		join[key_len] = '\0'; */
	return (join);
}

char	**env_convert(t_env *env)
{
	int		i;
	int		ctd;
	char	**env_array;
	t_env	*current;
	
	ctd = 0;
	current = env;
	while (current)
	{
		ctd++;
		current = current->next;
	}
	env_array = create_argv(ctd);
	if (!env_array)
		error_msg ("malloc env array");
	current = env;
	i = 0;
	while (i < ctd)
	{
		env_array[i] = join_key_value(current->key, current->value);
		current = current->next;
		i++;
	}
	env_array[ctd] = NULL;
	return (env_array);
}

void	env_arr_update(t_ms *s)
{			
	s->env_tmp = env_convert(s->env);
}
//! ===============================================================================//