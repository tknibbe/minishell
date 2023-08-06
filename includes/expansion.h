#ifndef EXPANSION_H
# define EXPANSION_H

# include <built_ins.h>
# include <dirent.h>

//# define WORD 1

typedef struct s_exp
{
	char	*result;
	int		star;
	t_env	*head;
}			t_exp;

typedef struct	s_str	t_str;

char	**full_expansion(t_str *start, t_env *head);
void	expander(int state, char *brake, t_exp *x, char *input);

char	*ft_join(char *s1, char *s2);
int		identify_substr(t_exp *x, int state, char *input, char **s);
int		expand_dollo(t_exp *x, char *input, char **s, int i);

char	*expand_wildcard(char *result, int count, char *d);

#endif