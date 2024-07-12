/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:42:53 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/07/12 22:52:43 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*path_constructor(const char *path, const char *cmd, int slashi)
{
	char	*new_path;
	char	*temp;

	if(slashi)
	{
		temp = ft_strjoin(path, "/");
		if(!temp)
			return (NULL);
		new_path = ft_strjoin(temp, cmd);
		free(temp);
	}
	if (ft_strcmp(cmd, "minishell") == 0)
		return (NULL);
	else if (access(new_path, X_OK) == 0)
		return (new_path);
	else
		return (NULL);
}

int abs_or_rel_path(const char *cmd)
{
	return(cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'));
}

char	*check_abs_or_rel(const char *cmd, t_ms *s)
{
	if (access(cmd, F_OK) != 0)
	{
		not_found((char *)cmd, 127, s);
		s->exit_stat = 127;
		return(NULL);
	}
	else if (access(cmd, X_OK) != 0)
	{
		not_found((char *)cmd, 126, s);
		s->exit_stat = 126;
		return(NULL);
	}
	else
		return (ft_strdup(cmd));
}

void	exec_one(t_ms *s, char **argv)
{
	char	*path;
	char	*cmd_name;

	if ((argv[0] && argv[0][0] == '.' && argv[0][1] == '/' && argv[0][2]) || \
		(argv[0] && argv[0][0] == '/' && argv[0][1]))
	{
		if (access(argv[0], F_OK) != 0)
		{
			not_found(argv[0], 127, s);
			s->exit_stat = 127;
			return ;
		}
		else if (access(argv[0], X_OK) != 0)
		{
			not_found(argv[0], 126, s);
			s->exit_stat = 126;
			return ;
		}
		if (!execve(argv[0], argv, s->env_tmp))
			exit(EXIT_FAILURE);
	}
	if (argv && argv[0] != NULL)
	{
		path = cmd_path(s->paths, argv[0], s);
		if (!path)
		{
			not_found(argv[0], 127, s);
			s->exit_stat = 127;
			return ;
		}
		cmd_name = ft_strchr(argv[0], '/');
		if (cmd_name)
		{
			cmd_name++;
			argv[0] = cmd_name;
		}
		execve(path, argv, s->env_tmp);
		not_found(argv[0], 127, s);
		free(path);
		s->exit_stat = 127;
	}
}


int	ft_exec_paria(t_ms *s, t_cmd *cmds)
{
	if (!cmds || cmds->type != EXEC)
		return (0);
	if (!(*s->ast->argv))
		return (1);
	if (ft_sw_builtins(cmds->argv[0], "export") == 0)
	{
		updating_cmds(s, cmds, s->ast->argv[s->ast->argc - 1]);
		export_cmd(s, cmds->argv);
		return (1);
	}
	else if (ft_sw_builtins(cmds->argv[0], "echo") == 0)
	{
		echo_cmd_test(cmds->argv, s, STDIN_FILENO, STDOUT_FILENO);
		updating_cmds(s, cmds, s->ast->argv[s->ast->argc - 1]);
		return (1);
	}
	else
		return (0);
}

void	updating_cmds(t_ms *s, t_cmd *cmd, char *value)
{
	char	*key;

	key = NULL;
	if (!value)
		value = NULL;
	(void)cmd;
	if (s->ast->type == 1)
	{
		key = ft_strdup("_");
		export_update(s->export, key, value);
		handle_kv_update(s->env, key, value, 1);
	}
	else if (s->ast->type == 2 || s->ast->type == 4)
	{
		key = ft_strdup("_");
		export_update(s->export, key, value);
		handle_kv_update(s->env, key, value, 1);
	}
}


int	builtins_parent(t_ms *s, char **cmds, int fd_in, int fd_out)
{
	(void)fd_in;
	(void)fd_out;
/* 	if (ft_sw_builtins(cmds[0], "echo") == 0)
		return (echo_cmd_test(cmds, s, fd_in, fd_out), 1); */
	if (ft_sw_builtins(cmds[0], "cd") == 0)
		return (cd_cmd(s, cmds), 1);
	else if (ft_sw_builtins(cmds[0], "env") == 0)
		return (env_cmd(s, cmds));
	else if (ft_sw_builtins(cmds[0], "pwd") == 0)
		return (pwd_cmd(s));
	else if (ft_sw_builtins(cmds[0], "export") == 0)
		return (export_cmd(s, cmds), 1);
	else if (ft_sw_builtins(cmds[0], "unset") == 0)
		return (unset_cmd(s, cmds));
	else if (ft_sw_builtins(cmds[0], "exit") == 0)
		return (exit_cmd(s, cmds), 1);
	else if (ft_sw_builtins(cmds[0], "bnf") == 0)
		return (s->bnf = true, ft_putstr_fd("bnf ON\n", 1), 1);
	else
		return (0);
}

void	aux_rec_exec(t_ms *s, t_cmd *cmd, int fd_in, int fd_out)
{
    int	i;

    if (cmd->argv && cmd->argv[0])
    {
        if (cmd->argv[0][0] == EMPTY)
        {
			i = 0;
            free(cmd->argv[0]);
			while(cmd->argv[i + 1] != NULL)
			{
				cmd->argv[i] = cmd->argv[i + 1];
				i++;
			}
            cmd->argv[i] = NULL;
            cmd->argc -= 1;
        }
        else if (ft_isspace(cmd->argv[0][0]) || cmd->argv[0][0] == '\0')
        {
            not_found(cmd->argv[0], 127, s);
            return;
        }
    }
    if (cmd && cmd->argc > 0)
        updating_cmds(s, cmd, cmd->argv[cmd->argc - 1]);
    if (!builtins_parent(s, cmd->argv, fd_in, fd_out))
        single_exec(s, cmd, fd_in, fd_out);
}

bool	check_argv(t_cmd *cmd)
{
	if (!cmd)
		return false;
	if (cmd->left)
		check_argv(cmd->left);
	if (cmd->right)
		check_argv(cmd->right);
	if (cmd->cmd)
		check_argv(cmd->cmd);
	if (cmd->type == EXEC && !cmd->argv[0])
		return false;
	return true;
}

void	exec_from_ast(t_ms *s)
{
	//char	**original;

	// ! || !check_argv(s->ast)) added to chck for faux argv:
	// ! (paste of invalid char on terminal)
	if (!s->ast || !check_argv(s->ast))
		return ;
	/* original = NULL;
    if (s->ast->argv && s->ast->type == EXEC && s->ast->argv[0][0] == '\020')
    {
		original = s->ast->argv;
        if (s->ast->argv[0][0] == '\020')
			s->ast->argv++;
    }
	if (s->ast->argv && (ft_isspace(s->ast->argv[0][0]) || s->ast->argv[0][0] == '\0'))
    {
        not_found(s->ast->argv[0], 127, s);
        return;
    } */
    if (!ft_exec_paria(s, s->ast))
	{
		exec_from_ast_recursive(s, s->ast, STDIN_FILENO, STDOUT_FILENO);
		s->wait = 0;
	}
	/* if(original)
		s->ast->argv = original; */
}
