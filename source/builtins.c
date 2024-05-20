#include "../include/minishell.h"

t_builtin builtins[] = {
	{"echo", cmd_echo},
	{"cd", cmd_cd},
	{"pwd", cmd_pwd},
	{"export", cmd_export},
	{"unset", cmd_unset},
	{"env", cmd_env},
	{"exit",cmd_exit},
}

int	builtin_num()
{
	return (sizeof(builtins) / sizeof(t_builtin));
}

//? Should this receive fd's too?
int	cmd_echo(char **args)
{
	int i;

	i = 1;
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		i++;
	}
	printf("\n");
	return (1);
}

int	cmd_pwd(char **args)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf ("%s\n", cwd);
	else
		perror("pwd");
	return (1);
}

int	cmd_cd(char	**args)
{
	if (args[1] == NULL)
		ft_sprintf(stderr,"cd need arguments");
	else
	{
		if (chdir(args[1] != 0))
			perror ("cd");
	}
	return (1);
}

int	cmd_exit(char **args)
{
	return (0);
}

int	cmd_env(char **args)
{
	extern char **__environ;
	int i = 0;

	while(args[i] != NULL)
	{
		printf("%s", __environ[i]);
		i++;	
	}
	return (1);
}

//! NOT YET WORKING

int	cmd_export(char **args)
{
	ft_sprintf(stdout, "export not implemented");
	return (1);
}
int cmd_unset(char **args)
{
	ft_sprintf(stdout, "unset not implemented");
	return (1);
}
