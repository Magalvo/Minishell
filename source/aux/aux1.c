#include "../../include/minishell.h"

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
char	*get_env_expand(char *key)
{
	char *val;
	if (key[0] == '$')
		key = key + 1;
	val = getenv(key);
	return (val);
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int	export_cmd_error(char *msg)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
void	wait_till_end(t_ms *s, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (status == 13)
		s->exit_stat = s->exit_stat;
	else if (WIFEXITED(status))
		s->exit_stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		s->exit_stat = 128 + WTERMSIG(status);
	}
	if (s->exit_stat == 131)
		printf("Quit\n");
	if (s->exit_stat == 130)
		printf("\n");
	if (s->exit_stat == 2)
	{
		s->exit_stat = 130;
		printf("\n");
	}
	if (s->exit_stat > 255)
		s->exit_stat /= 256;
}
