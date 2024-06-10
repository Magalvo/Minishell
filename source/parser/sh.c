// Shell.

#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

// Parsed command representation
#define EXEC 1
#define REDIR 2
#define PIPE 3
// #define LIST  4
// #define BACK  5

#define MAXARGS 10

void	runcmd(struct cmd *) __attribute__((noreturn));

// Execute cmd.  Never returns.
void	runcmd(struct cmd *cmd)
{
	int					p[2];
	struct cmd_exec		*ecmd;
	struct cmd_pipe		*pcmd;
	struct cmd_redir	*rcmd;

	// struct backcmd *bcmd;
	// struct listcmd *lcmd;
	if (cmd == 0)
		exit(1);
	switch (cmd->type)
	{
	default:
		panic("runcmd");
	case EXEC:
		ecmd = (struct cmd_exec *)cmd;
		if (ecmd->argv[0] == 0)
			exit(1);
		exec(ecmd->argv[0], ecmd->argv);
		fprintf(2, "exec %s failed\n", ecmd->argv[0]);
		break ;
	case REDIR:
		rcmd = (struct cmd_redir *)cmd;
		close(rcmd->fd);
		if (open(rcmd->file, rcmd->mode) < 0)
		{
			fprintf(2, "open %s failed\n", rcmd->file);
			exit(1);
		}
		runcmd(rcmd->cmd);
		break ;
	case PIPE:
		pcmd = (struct cmd_pipe *)cmd;
		if (pipe(p) < 0)
			panic("pipe");
		if (fork1() == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->left);
		}
		if (fork1() == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->right);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
		wait(0);
		break ;
	}
	exit(0);
}

int	main(void)
{
	static char	buf[100];
	int			fd;

	// Ensure that three file descriptors are open.
	while ((fd = open("console", O_RDWR)) >= 0)
	{
		if (fd >= 3)
		{
			close(fd);
			break ;
		}
	}
	// Read and run input commands.
	while (getcmd(buf, sizeof(buf)) >= 0)
	{
		if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ')
		{
			// Chdir must be called by the parent, not the child.
			buf[strlen(buf) - 1] = 0; // chop \n
			if (chdir(buf + 3) < 0)
				fprintf(2, "cannot cd %s\n", buf + 3);
			continue ;
		}
		if (fork1() == 0)
			runcmd(parse_cmd(buf));
		wait(0);
	}
	exit(0);
}

void	panic(char *s)
{
	fprintf(2, "%s\n", s);
	exit(1);
}

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	return (pid);
}
