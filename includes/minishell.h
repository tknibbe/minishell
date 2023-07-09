/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 14:11:50 by tknibbe       #+#    #+#                 */
/*   Updated: 2023/07/09 16:12:48 by cvan-sch      ########   odam.nl         */
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
# include <token.h>

//hey crissie baby <3
//hey tymoo daddy 8=D
//hey crissie deel 2 80085

# include <env.h>

typedef struct s_minishell
{
	t_env		*env;
	t_data		*data;
	int			exit_code;
}				t_ally;

int		history_management(const char *s);
char	**parse_and_execute(char *input);

//EXIT_FUNCS.C
void	ft_exit(char *string, int errnum);

//utils
void	print_double_array(char **x);
void	free_dp(char **dp);
int		count(char **c);

#endif
