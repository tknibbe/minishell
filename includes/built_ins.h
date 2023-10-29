#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "structs.h"

/*				echo_pwd_exit.c*/
int				echo(char **cmd, int fd);
void			ms_exit(char **cmd);
int				pwd(int fd);

/*				env_builtins.c*/
int				export(t_env_info *e, char **to_export, int fd);
int				unset(t_env_info *e, char **to_unset);
int				env(t_env *env, int fd);

/*				cd.c*/
int				cd(char **cmd, t_env_info *e, int fd);

/*				env_export_unset.c*/
int				find_and_export(t_env_info *e, t_env *head, char *to_export);
int				find_and_unset(t_env **env, char *unset);
int				legit_export_item(char *to_export);
int				valid_identifier(char *s);

/*				env_init.c*/
void			env_addback(t_env **head, t_env *new);
t_env_info		*env_init(char **env);
t_env			*env_new(char *s);

/*				env_utils.c*/
void			update_env(t_env *to_update, t_env_info *e);
void			get_environment_for_exec(t_env_info *e);
char			*get_env(char *key, t_env_info *e);
char			*ft_envjoin(char *s1, char *s2);

#endif
