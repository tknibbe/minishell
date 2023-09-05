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
	int				last_exit_status;
	char			**env;
	t_env			*head;
}					t_env_info;

int					cd(char **cmd, t_env_info *e);
void				echo(char **cmd);
int					pwd(char **cmd);
void				history(const char *s);

int					env(char **cmd, t_env *env);
int					unset(t_env_info *e, char **to_unset);
int					export(t_env_info *e, char **to_export);
int					valid_identifier(char *s);
int					legit_export_item(char *to_export);
int					find_and_unset(t_env **env, char *unset);
int					find_and_export(t_env *head, char *to_export);

t_env_info			*env_init(char **env);
t_env				*env_new(char *s);
void				env_addback(t_env **head, t_env *new);

char				*ft_envjoin(char *s1, char *s2);
void				get_environment_for_exec(t_env_info *e);
char				*get_env(char *key, t_env_info *e);
void				free_env(char **env);

#endif
