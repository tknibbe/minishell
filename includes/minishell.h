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

//hey crissie baby <3
//hey tymoo daddy 8=D
//hey crissie deel 2 80085

int		history_management(const char *s);
char	**parse_and_execute(char *input);

// built-ins
int		change_directory(const char *path);
//EXIT_FUNCS.C
void	ft_exit(char *string, int errnum);

#endif
