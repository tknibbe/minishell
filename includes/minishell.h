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

typedef struct s_data
{
	int	*token;
}		t_data;


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
//hey crissie baby <3
//hey tymoo daddy 8=D
//hey crissie deel 2 80085

int		history_management(const char *s);
char	**parse_and_execute(char *input);

//TOKEN.C
int		set_tokens(char *input, t_data *data);

//EXIT_FUNCS.C
void	ft_exit(char *string, int errnum);

#endif
