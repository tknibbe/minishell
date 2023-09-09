#ifndef EXPANSION_H
# define EXPANSION_H

# include <built_ins.h>
# include <dirent.h>
# include <minishell.h>

typedef struct s_exp
{
	char		*result;
	int			star;
	t_env_info	*e;
}			t_exp;

typedef struct	s_str	t_str;

/*full expansion*/
char	**full_expansion(t_str *c, t_env_info *e);
void	expander(int state, t_exp *x, char *input);

/*wordsplitter functions*/
void	split_word(t_str *start, t_env_info *e);
void	insert_list(t_str **start, t_str *list);

/*wildcard expander*/
t_str	*expand_wildcard(char *s);

/*utils*/
char	*ft_join(char *s1, char *s2);
int		expand_dollo(t_exp *x, char *input, char **s, int i);
void	append_sub(char **s, char *input, int len);
char	*get_brake(int state);
int		identify_substr(t_exp *x, int state, char *input, char **s);
char	*create_sub(char *s, int *i, int j);
void	transform_wildcards(char **s);
void	expand_string(char *s, t_exp *x);
int		check_for_wildcard(char *s);
int		unclosed_quote(int state);
int		skip_quoted_state(char *s, int i, int quote);
int		amount(t_str *s);
void	initialize_xp(t_exp *xp, t_env_info *e);

#endif
