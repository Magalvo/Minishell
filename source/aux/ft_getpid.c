#include "../../include/minishell.h"

// if $$ found replace with result from:	char pid_res = ft_getpid();
char	*ft_getpid(void)
{
	char		*pid_res;
	int			fd;
	char		**stat;

	fd = open("/proc/self/stat", O_RDONLY);
	if (!fd)
		return (NULL);
	pid_res = get_next_line(fd);
	if (!pid_res)
		return (NULL);
	stat = ft_split(pid_res, ' ');
	free(pid_res);
	if (!stat)
		return (NULL);
	pid_res = ft_strdup(stat[0]);
	ft_free_dptr(&stat);
	if (!pid_res)
		return (NULL);
	return (pid_res);
}

// for historical reasons this monstrosity shall remain here.
// If it's stupid and it works is not stupid, then there's this function...
/*
char	*get_pid(t_ms *s)
{
	pid_t		pid;
	char		*pid_res;
	int			fd[2];
	char		**stat;
	static char	*command[3] = {"/bin/cat", "/proc/self/stat", NULL};
	int			stdin_copy;

	pipe(fd);
	pid = fork();
	if (pid == -1)
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
		close(stdin_copy); // Close the copy
		close(fd[0]);
		wait(0);
		stat = ft_split(pid_res, ' ');
		pid_res = ft_strdup(stat[3]);
		free(stat);
		return (pid_res);
	}
	return (NULL);
}*/
