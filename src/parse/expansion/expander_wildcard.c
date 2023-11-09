#include "minishell.h"

#define NO_MATCH 0
#define MATCHED 1
#define DIRECTORY '/'

static int	check_first_matching_string(char **file, char **input, int w_card)
{
	int	i;

	while (*(*file))
	{
		i = 0;
		if (w_card)
			while (*(*file) && *(*file) != *(*input))
				(*file)++;
		while ((*file)[i] && (*file)[i] == (*input)[i])
			i++;
		if ((*input)[i] == -1 || (!(*file)[i] && !(*input)[i]) \
			|| (!(*file)[i] && (*input)[i] == '/'))
		{
			*input += i;
			*file += i;
			return (MATCHED);
		}
		if (!((*file)[i]) || !w_card)
			break ;
		*file += i;
	}
	return (NO_MATCH);
}

static int	pattern_match(char *f, char *input)
{
	int	wildcard;

	while (*f)
	{
		if (*input == -1)
			wildcard = *(input++);
		else
			wildcard = 0;
		if (!check_first_matching_string(&f, &input, wildcard))
			return (NO_MATCH);
		else if (*input == DIRECTORY)
			return (DIRECTORY);
	}
	return (MATCHED);
}

static void	attempt_to_match(t_str **head, struct dirent *entry, char *s)
{
	int		m;
	char	*tmp;

	m = pattern_match(entry->d_name, s);
	if (!m || (m == DIRECTORY && entry->d_type != DT_DIR))
		return ;
	tmp = ft_strdup(entry->d_name);
	if (!tmp)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	if (m == DIRECTORY && entry->d_type == DT_DIR)
		tmp = ft_join(tmp, "/");
	tstr_addback(head, tstr_new(tmp));
}

t_str	*expand_wildcard(char *s)
{
	DIR				*dir_p;
	struct dirent	*entry;
	t_str			*matched;

	matched = NULL;
	dir_p = opendir(".");
	if (!dir_p)
		ft_minishell_error("opendir()", NULL, strerror(errno), errno);
	while (1)
	{
		entry = readdir(dir_p);
		if (!entry)
			break ;
		if (*entry->d_name == '.' && *s != '.')
			continue ;
		attempt_to_match(&matched, entry, s);
	}
	closedir(dir_p);
	return (matched);
}
