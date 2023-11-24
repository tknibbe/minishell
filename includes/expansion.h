/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:48:43 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/15 13:48:44 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "structs.h"

# define NO_MATCH 0
# define MATCH 1
# define MATCH_DIR 2

/*		expander.c*/
void	expander(int state, t_exp *x, char *input);
char	**full_expansion(t_str *c, t_env_info *e);

/*		expander_wc_utils.c*/
int		skip_quoted_state(char *s, int i, int quote);
int		check_for_wildcard(char *s);
int		amount(t_str *s);
bool	check_for_more(char *s, char *file, t_str **matched, char *dir);

/*		expander_wildcard.c*/
void	expand_wildcard(char *s, t_str **matched, char *directory);

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
char	*get_brake(int *state);

#endif
