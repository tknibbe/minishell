#ifndef EXPANSION_H
# define EXPANSION_H

# include "structs.h"
# include "minishell.h"

/*		expander.c*/
void	expander(int state, t_exp *x, char *input);
char	**full_expansion(t_str *c, t_env_info *e);

/*		expander_wc_utils.c*/
int		skip_quoted_state(char *s, int i, int quote);
void	initialize_xp(t_exp *xp, t_env_info *e);
int		check_for_wildcard(char *s);
int		unclosed_quote(int state);
int		amount(t_str *s);

/*		expander_wildcard.c*/
t_str	*expand_wildcard(char *s);

/*		expander_ws_utils.c*/
char	*create_sub(char *s, int *i, int j);
void	expand_string(char *s, t_exp *x);
void	transform_wildcards(char **s);

//		expander_wordsplit.c
void	split_word(t_str *start, t_env_info *e);
void	insert_list(t_str **start, t_str *list);

//		expander_utils.c
int		expand_dollo(t_exp *x, char *input, char **s, int i);
void	append_sub(char **s, char *input, int len);
char	*ft_join(char *s1, char *s2);
char	**lst_to_dp(t_str *c);
char	*get_brake(int state);

#endif
