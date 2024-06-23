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
	if(!cmd)
		return ;
	if (cmd->argv)
	{
		while(cmd->argv[i])
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


void free_env_list(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if(tmp->key)
			free(tmp->key);
		if(tmp->value)
			free(tmp->value);
		if(tmp)
			free(tmp);
	}
}

void cleanup_shell(t_ms *s)
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
/* 	if (s->env)
	{
		free_env_list(s->env);
		s->env = NULL;
	} */
/* 	if (s->ast)
	{
		clear_cmd(s->ast);
		s->ast = NULL;
	} */
}

void	set_exit(int stat, t_ms *s)
{	
	if (s)
		s->exit_stat = stat;
	exit(stat);
}