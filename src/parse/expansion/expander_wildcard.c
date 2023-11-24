/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:33:50 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/15 12:33:51 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getstr(char *dir, char *d_name, int match)
{
	char	*new;

	if (!dir)
		new = ft_strdup(d_name);
	else
		new = ft_strjoin(dir, d_name);
	if (!new)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	if (match == MATCH_DIR)
		new = ft_join(new, "/");
	return (new);
}

static int	pre_pm(char **file, char **input)
{ 
	if (*(*input) != '.' && *(*file) == '.')
		return (1);
	while (*(*input) && *(*input) == *(*file))
	{
		(*file)++;
		(*input)++;
	}
	if (*(*input) == -1)
	{
		while (*(*input) == -1)
			(*input)++;
		return (0);
	}
	return (1);
}

static int	match_condition(int i, int type, char **input, char **file)
{
	if (!(*input)[i] && !(*file)[i])
		return (MATCH);
	else if (!(*file)[i] && (*input)[i] == '/' && type == DT_DIR)
		return (MATCH_DIR);
	else if ((*input)[i] == '/' && !(*file)[i])
		return (NO_MATCH);
	else if ((*input)[i] == -1)
	{
		(*input) += i;
		(*file) += i;
		while (*(*input) == -1)
			(*input)++;
	}
	else if (*(*file))
		(*file)++;
	return (-1);
}

static int	pattern_match(char *file, char *input, const int type)
{
	int		i;
	int		condition;

	if (pre_pm(&file, &input))
		return (NO_MATCH);
	while (*file)
	{
		i = 0;
		while (*file && *file != *input)
			file++;
		while (file[i] && file[i] == input[i])
			i++;
		condition = match_condition(i, type, &input, &file);
		if (condition == -1)
			continue ;
		return (condition);
	}

	if (*input == *file)
		return (MATCH);
	else if (*input == '/' && type == DT_DIR)
		return (MATCH_DIR);
	return (NO_MATCH);
}


void	expand_wildcard(char *s, t_str **matched, char *directory)
{
	struct dirent	*entry;
	DIR				*instance;
	int				match;

	if (!directory)
		instance = opendir(".");
	else
		instance = opendir(directory);
	if (!instance)
		ft_minishell_error("opendir()", directory, strerror(errno), errno); // maybe not exit but just return and catch that somewhere els
	while (true)
	{
		entry = readdir(instance);
		if (!entry)
			break ;
		match = pattern_match(entry->d_name, s, entry->d_type);
		if (match == MATCH_DIR && check_for_more(s, entry->d_name, matched, directory))
			continue ;
		if (match)
			tstr_addback(matched, tstr_new(getstr(directory, entry->d_name, match)));
	}
	closedir(instance);
	free(directory);
}
