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
	char			*joined_value;
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

int					cd(char **cmd, t_env_info *e, int fd);
int					echo(char **cmd, int fd);
int					pwd(int fd);
int					history(char *s);
void				ms_exit(char **cmd);

int					env(t_env *env, int fd);
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
// void				free_env(char **env);
void				update_var(t_env_info *e);
void				update_env(t_env *to_update, t_env_info *e);
void				swap(t_env *pwd, t_env *oldpwd, t_env_info *e);

#endif
