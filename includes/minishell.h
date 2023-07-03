/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/29 16:02:01 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/07/03 15:41:47 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //!
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

# include <sys/wait.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <string.h>
# include "../lib/includes/libft.h"

#define TAB '	'
#define SPACE ' '

enum	e_token
{
	UNDEFINED,
	DQUOTE,
	SQUOTE,
	DOLLO,
	EXEC,
	OPTIONS, //optional
	PIPESYMBOL, // couldnt call it pipe because of redefinition error
	REDIR,
	WHITESPACE,
};

typedef struct	s_ally
{
	t_env		*env;
}				t_ally;

//hey crissie baby <3
//hey tymoo daddy 8=D
//hey crissie deel 2 80085

int		history_management(const char *s);
char	**parse_and_execute(char *input);

// built-ins
int		change_directory(const char *path);
//EXIT_FUNCS.C
void	ft_exit(char *string, int errnum);

//utils
void	print_double_array(char **x);
void	free_dp(char **dp);
int		count(char **c);
#endif
