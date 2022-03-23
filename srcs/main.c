/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:58:40 by mriant            #+#    #+#             */
/*   Updated: 2022/03/23 12:02:15 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

char	**ft_get_path(char **aenv)
{
	char	**result;
	int		i;

	if (!aenv)
		return (NULL);
	i = 0;
	while (aenv[i] && ft_strncmp(aenv[i], "PATH=", 5) != 0)
		i++;
	if (!aenv[i])
		return (NULL);
	result = ft_split(aenv[i] + 5, ':');
	return (result);
}

void	ft_clean_array(char	**s_array)
{
	int	i;

	if (!s_array)
		return ;
	i = 0;
	while (s_array[i])
	{
		free(s_array[i]);
		i++;
	}
	free(s_array);
}

char	**ft_get_cmdpath(char *cmd, char **paths)
{
	int		i;
	char	*s;
	char	**s_array;

	if (!paths)
		return (NULL);
	s_array = ft_split(cmd, ' ');
	if (!s_array)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		s = ft_strjoin(paths[i], s_array[0], "/");
		if (!s)
		{
			ft_clean_array(s_array);
			return (NULL);
		}
		if (access(s, X_OK) == 0)
			break ;
		free(s);
		i++;
	}
	if (!paths[i])
	{
		ft_clean_array(s_array);
		return (NULL);
	}
	free(s_array[0]);
	s_array[0] = s;
	return (s_array);
}

int	main(int ac, char **av, char **aenv)
{
	char	**paths;
	char	**cmd1;
	char	**cmd2;

	if (ac != 5)
	{
		ft_fprintf(2, "Error\nPipex takes 4 arguments file1 cmd1 cmd2 file2\n");
		return (1);
	}
	paths = ft_get_path(aenv);
	cmd1 = ft_get_cmdpath(av[2], paths);
	cmd2 = ft_get_cmdpath(av[3], paths);
	if (!paths || !cmd1 || !cmd2)
	{
		ft_clean_array(paths);
		ft_clean_array(cmd1);
		ft_clean_array(cmd2);
		return (1);
	}
	ft_clean_array(paths);
	ft_clean_array(cmd1);
	ft_clean_array(cmd2);
	return (0);
}
