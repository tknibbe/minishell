# include <expansion.h>
#include <sys/errno.h>
#include <minishell.h>

int	condition(int f, int s)
{
	if (!s && f)
		return (0);
	if (!s && !f)
		return (1);
	if (f && s != '*')
		return (0);
	if (f && s == '*')
		return (-1);
	return (-2);
}

int	is_compatible(char *f, char *input)
{
	int	i;

	while (*input)
	{
		if (*input == '*')
		{
			while (*input == '*')
				input++;
			while (*f && *input != *f)
				f++;
				
		}
		while (*input && *input == *f)
		{
			input++;
			f++;
		}
	}
	return (0);
}

void	expand_wildcard(char **result, int count)
{
	//printf("is compatible? = %d\n", is_compatible("kaas", *result));
	DIR				*dir_p;
	struct dirent	*dir_info;

	dir_p = opendir(".");
	if (dir_p < 0)
		ft_exit("opendir()\n", errno);
	while (1)
	{
		dir_info = readdir(dir_p);
		if (!dir_info)
			return ;
		printf("check\n");
		if (is_compatible(dir_info->d_name, *result))
			printf("> %s\n", dir_info->d_name);
	}
	closedir(dir_p);
}
