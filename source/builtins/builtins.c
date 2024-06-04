/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:25 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/27 15:50:24 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//! Executar Builtins no processo pai a nao ser o printenv;
// ? Talvez possa ser no filho segundo o Mindmap  D:  :')

/* int	exec_input(t_ms *s)
{
	ft_exec_buitltins_chr(s, s->cmd_temp);
 	int id = fork();
	if (id < 0)
		return (exit_minishell(s,"error"), 0);
	if (id == 0)
		execve(s->cmd_temp[0], s->cmd_temp, s->env_tmp);
	wait(NULL); 
	return (1);
} 
*/
int	ft_sw_builtins(const char *s1, const char *s2) {
    size_t s1_len = ft_strlen(s1);
    size_t s2_len = ft_strlen(s2);

    if (s1_len != s2_len) {
        return (s1_len - s2_len);
    }
    return ft_strncmp(s1, s2, s1_len);
}

int	ft_exec_buitltins_chr(t_ms *s, char **cmds)  //[{laskdl}{kjhalsd}{jakskdj}]
{
	(void)s;
	if (ft_strncmp(cmds[0], "echo", 4) == 0)
		return (echo_cmd_test(cmds));
	else if (ft_strncmp(cmds[0], "cd", 2) == 0)
		return (cd_cmd(s, cmds));
	else if (ft_strncmp(cmds[0], "env", 3) == 0)
		return (env_cmd(s));
	else if (ft_strncmp(cmds[0], "pwd", 3) == 0)
		return (pwd_cmd());
	else if (ft_strncmp(cmds[0], "export", 6) == 0)
	 	return (export_cmd(s, cmds));
	else if (ft_strncmp(cmds[0], "unset", 5) == 0)
		return (unset_cmd(s, cmds));
	else if (ft_strncmp(cmds[0], "exit", 4) == 0)
		return (exit_cmd(s), 1); 
	else
		return (0);
}

/* int	ft_exec_buitltins(t_ms *s, char **cmds)
{
	if (ft_strcmp(cmds->cmd_args[0], "echo") == 0)
		return (echo_cmd(cmds));
	if (ft_strcmp(cmds->cmd_args[0], "cd") == 0)
		return (cd_cmd(s));
	if (ft_strcmp(cmds->cmd_args[0], "env") == 0)
		return (env_cmd(s));
	if (ft_strcmp(cmds->cmd_args[0], "pwd") == 0)
		return (pwd_cmd(s));
	if (ft_strcmp(cmds->cmd_args[0], "export") == 0)
		return (export_cmd(s, cmds));
	if (ft_strcmp(cmds->cmd_args[0], "unset") == 0)
		return (unset_cmd(s, cmds));
	if (ft_strcmp(cmds->cmd_args[0], "exit") == 0)
		return (exit_cmd(s));
	return (1);
} */
