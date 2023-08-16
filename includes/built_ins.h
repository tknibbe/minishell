#ifndef BUILT_INS_H
# define BUILT_INS_H

# include <unistd.h>
# include <libft.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_env_info
{
	int				count;
	int				has_changed;
	char			**env;
	t_env			*head;
}					t_env_info;

void				cd(char *path, t_env *env);
void				pwd(void);
void				history(const char *s);
void				echo(char **echo);

void				env(t_env *env);
void				unset(t_env_info *e, char **to_unset);
void				export(t_env_info *e, char **to_export);
int					valid_identifier(char *s);
int					legit_export_item(char *to_export);
int					find_and_unset(t_env **env, char *unset);
int					find_and_export(t_env *head, char *to_export);

t_env_info			*env_init(char **env);
t_env				*env_new(char *s);
void				env_addback(t_env **head, t_env *new);

char				*ft_envjoin(char *s1, char *s2);
void				get_environment_for_exec(t_env_info *e);
char				*get_env(char *key, t_env *head);
void				free_env(char **env);

#endif
