/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:48:49 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/15 13:49:36 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

typedef struct s_env_info	t_env_info;
typedef struct s_process	t_process;
typedef struct s_heredoc	t_heredoc;
typedef struct s_list		t_list;
typedef struct s_exec		t_exec;
typedef struct s_str		t_str;
typedef struct s_env		t_env;
typedef struct s_exp		t_exp;
typedef struct s_rdr		t_rdr;

/*linked list of strings*/
typedef struct s_str
{
	char			*str;
	struct s_str	*next;
}					t_str;

/*linked list of environment variables and their keys/values*/
typedef struct s_env
{
	char			*key;
	char			*value;
	char			*joined_value;
	struct s_env	*next;
}					t_env;

/*a structure holding information about the state of th*/
typedef struct s_env_info
{
	char			**env;
	t_env			*head;
	int				count;
	int				has_changed;
	int				last_exit_status;
}					t_env_info;

/*a structure holding variables relevant to a pipeline*/
typedef struct s_process
{
	t_env_info		*e;
	int				*p;
	char			**cmd;
	int				builtin;
	int				here_doc_nbr;
	int				fd_to_read_from;
	bool			is_single_command;
}					t_process;

/*a structure holding the result of expansion and the var*/
typedef struct s_exp
{
	char			*result;
	t_env_info		*e;
}					t_exp;

/*a structure that holds the redirection requierments for a single command*/
typedef struct s_rdr
{
	t_str			*file;
	int				type;
	struct s_rdr	*next;
}					t_rdr;

/*
	a structure that holds information about a single command 
	
	cmd			- command with its argument
	rdr			- linked list of redirection nodes
	subshell	- a list structure holding afformentioned information
*/
typedef struct s_list
{
	int				*token;
	char			*input;
	int				and_or;
	t_exec			*exec;
	struct s_list	*next;
}					t_list;

typedef struct s_exec
{
	t_str			*cmd;
	t_rdr			*rdr;
	t_list			*subshell;
	struct s_exec	*next;
}					t_exec;

typedef struct s_heredoc
{
	int				pid;
	int				expand;
	int				status;
	int				pipefd[2];
	char			*line;
	char			*delimiter;
}					t_heredoc;

#endif