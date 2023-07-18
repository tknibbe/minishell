#ifndef EXPANSION_H
# define EXPANSION_H

# include <built_ins.h>
# include <dirent.h>

# define WORD 1

typedef struct s_exp
{
	char	*input;
	int		*token;
	char	*result;
	int		star;
	t_env	*head;
}			t_exp;

char	*full_expansion(char *input, int *token, t_env *head);
void	expander(int state, char *brake, t_exp *x);

char	*ft_join(char *s1, char *s2);
int		identify_substr(t_exp *x, int state, char *brake, char **s);
int		expand_dollo(t_exp *x, char **s, int i);

#endif