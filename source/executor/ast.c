#include "../include/minishell.h"
										//s->ast
void exec_from_ast_recursive(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
	int     pipefd[2];
	pid_t   pid;
	int		status;
	
	if (!cmd)
		return;
/* 	while (s->here_doc != 0)
	{
		here_doc("EOF", s, cmd);
		s->here_doc -= 1;
	} */	
	if (cmd->type == EXEC)
	{
		if (ft_exec_buitltins_chr(s, cmd->argv)) 
			s->exit_stat = 0;
		else 
			single_exec(s, cmd, fd_in, fd_out);
	}
	else if (cmd->type == PIPE)
	{
		if (pipe(pipefd) == -1)
			error_msg("pipe");
		pid = fork();
		if (pid == -1)
			error_msg("fork");
		else if (pid == 0) 
		{
			close(pipefd[0]);
			dup2(fd_in, STDIN_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			exec_from_ast_recursive(s, cmd->left, fd_in, STDOUT_FILENO);
			exit(s->exit_stat);
		} 
		else 
		{
			close(pipefd[1]);
			exec_from_ast_recursive(s, cmd->right, pipefd[0], fd_out);
			close(pipefd[0]);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status)) 
				s->exit_stat = WEXITSTATUS(status);
		}
	} 
	else if (cmd->type == REDIR || cmd->type == HEREDOC) 
		exec_redir(s, cmd, fd_in, fd_out);
}


void	free_ast(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	free_ast(cmd->left);
	free_ast(cmd->right);
	free_ast(cmd->cmd);
	if(cmd->argv)
	{
		i = 0;
		while(cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
	}
	if (cmd->file)
		free(cmd->file);
	if (cmd->delim)
		free(cmd->delim);

	if (cmd->temp)
	{
		i = 0;
		while (cmd->temp[i])
			free(cmd->temp[i++]);
		free(cmd->temp);
	}
	free(cmd);
}

void	reset_ast(t_ms *s)
{
	if(s->ast)
	{
		free_ast(s->ast);
		s->ast = NULL;
	}
}
