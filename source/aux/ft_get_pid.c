#include "../../include/minishell.h"

// void	set_pid(t_pid pid)
// {
// 	pid->env_arg[0] = "ps";
// 	pid->env_arg[1] = "-p";
// 	pid->env_arg[2] = "$$";
// 	pid->env_arg[3] = "-o";
// 	pid->env_arg[4] = "pid=";
// 	pid->env_arg[5] = NULL;
// }

char	*get_pid(t_ms *s)
{
	pid_t		pid;
	char		*pid_res;
	int			fd[2];
	char		**stat;
	static char	*command[3] = {"/bin/cat", "/proc/self/stat", NULL};
	int			stdin_copy;

	pipe(fd);
	if ((pid = fork()) == -1)
		error_msg("error on pid");
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(command[0], command, s->env_tmp);
	}
	else
	{
		close(fd[1]);
		stdin_copy = dup(STDIN_FILENO); // Save the original STDIN
		dup2(fd[0], STDIN_FILENO);
		pid_res = get_next_line(fd[0]);
		dup2(stdin_copy, STDIN_FILENO); // Restore the original STDIN
		close(stdin_copy);  // Close the copy
		close(fd[0]);
		wait(0);
		stat = ft_split(pid_res, ' ');
		pid_res = ft_strdup(stat[3]);
		free(stat);
		return (pid_res);
	}
	return (NULL);
}

// if $$ found replace with result from:   char pid_res = ft_get_pid(&s);
