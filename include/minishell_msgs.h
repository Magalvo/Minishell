/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_msgs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:07:20 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/08/02 10:19:07 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_MSGS_H
# define MINISHELL_MSGS_H

/* defin error messages*/
# define MISSING_REDIRECT	"redirect without file"
# define INVALID_TOKEN		"syntax error: unexpected token"
# define MISSING_QUOTE		"missing quote or double quote"
# define SINGLE_AMPERSAND	"background tasks not implemented"
# define SEMICOLON			"command list not implemented"
# define EXPANSION_ERROR		"could not expand variable" // ! needed?
# define CURLY_ERROR			"bad substitution" // ! needed?
# define GETPID_ERROR		"Who am I? What I'm doing here?" // ! needed?
# define PARENTHESIS			"blocks (parenthesis) not implemented"
# define BLOCK_MISSING		"missing parenthesis"
# define BLOCK_UNCLOSED		"missing closing parenthesis"
# define BLOCK_WTF			"missing opening parenthesis"
# define EXEC_MISSING_CMD	"input not parsed. BIG BIG PROBLEM"
# define EXEC_FAIL			"error executing execve"
# define PIPE_FAIL			"error creating pipe"
# define FORK_FAIL			"error creating fork"
# define CD_FAIL				"cannot change directory"
# define LOGICAL_TOKEN		"logic operators (&& ||) not implemented"
# define NOT_A_VALID_TOKEN	"invalid token found"
# define INCOMPLETE_PARSE	"not parsed, double check parser"
# define PIPE_SYNTAX			"syntax error, check pipes"
# define REDIR_SYNTAX		"ambiguous redirect"

#endif
