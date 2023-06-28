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

typedef struct s_data
{
	int	*token;
}		t_data;

enum	e_token
{
	UNDEFINED,
	SQUOTE,
	DQUOTE,
	DOLLO,
	REDIRLEFT,
	REDIRRIGHT,
	APPLEFT,
	APPRIGHT,
	PIPESYMBOL, // couldnt call it pipe because of redefinition error
	OPTIONS, //optional
	EXEC,
	WHITESPACE,
};
//hey crissie baby <3
//hey tymoo daddy 8=D
//hey crissie deel 2 80085

int		history_management(const char *s);
char	**parse_and_execute(char *input);

// built-ins
int		change_directory(const char *path);
//TOKEN.C
int		set_tokens(char *input, t_data *data);
//TOKEN_FUNCS.C
int		count_quote(char *input, t_data *data, char c);
void	find_pipe(t_data *data, char *input);
void	find_append_redirect(t_data *data, char *input);
//EXIT_FUNCS.C
void	ft_exit(char *string, int errnum);

#endif
