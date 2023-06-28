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

typedef struct s_env
{
	int		var_count;
	char	**env;
}			t_env;

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

// built-ins
int		change_directory(const char *path);
//TOKEN.C
int		set_tokens(char *input, t_data *data);
//TOKEN_FUNCS.C
int		count_quote(char *input, t_data *data, char c);
void	find_dollar(t_data *data, char *input);
//EXIT_FUNCS.C
void	ft_exit(char *string, int errnum);

// env
t_env	*env_init(char *envp[]);
void	unset(t_env *env, char **to_unset);

//utils
void	print_double_array(char **x);
#endif
