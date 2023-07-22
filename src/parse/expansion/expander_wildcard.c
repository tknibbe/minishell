# include <expansion.h>
#include <sys/errno.h>
#include <minishell.h>

#define NO_MATCH 0
#define MATCHED 1
#define DIRECTORY 47

int	check_for_first_matching_string(char **file, char **input, int w_card)
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
		if ((*input)[i] == '*' || (!(*file)[i] && !(*input)[i])\
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

int	pattern_match(char *f, char *input)
{
	int	w_mode;
	int	match;

	while (*f)
	{
		w_mode = 0;
		if (*input == '*')
			w_mode = *(input++);
		match = check_for_first_matching_string(&f, &input, w_mode);
		if (!match)
			return (NO_MATCH);
		else if (*input == DIRECTORY)
			return (DIRECTORY);
	}
	return (MATCHED);
}

void	match_hidden(DIR *derp, struct dirent **dir_info, int dot)
{
	*dir_info = readdir(derp);
	if (dot == '.')
		return ;
	while (*(*dir_info)->d_name == '.')
		*dir_info = readdir(derp);
}

char	*expand_wildcard(char *result, int count, char *d)
{
	DIR				*dir_p;
	struct dirent	*dir_info;
	char			*file_name;
	int				state;

	if (!d)
		ft_exit("Malloc error\n", errno);
	state = 1;
	while (state)
	{
		dir_p = opendir(d);
		if (dir_p < 0)
			ft_exit("opendir()\n", errno);
		match_hidden(dir_p, &dir_info, *result);
		while (dir_info)
		{
			state = pattern_match(dir_info->d_name, result);
			if (state == MATCHED)
			{
				printf("normal match %s\n\n", dir_info->d_name);
				// name matched ! should join with other but don't yet know how
			}
			else if(state == NO_MATCH)
			{
				printf("continuing search with next dir entry<\n\n");
			}
			else if (dir_info->d_type == DT_DIR)
			{
				printf("directory match %s/\n", dir_info->d_name);
			}
			dir_info = readdir(dir_p);
		}
	}
	closedir(dir_p);
	return (NULL);
}
