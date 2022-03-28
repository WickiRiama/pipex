/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:40:02 by mriant            #+#    #+#             */
/*   Updated: 2022/03/28 13:22:31 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <fcntl.h>

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

char	**ft_get_cmdpath(char **cmd, char **paths)
{
	int		i;
	char	*s;

	if (!cmd || !paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		s = ft_strjoin(paths[i], cmd[0], "/");
		if (!s)
			break ;
		if (access(s, X_OK) == 0)
			break ;
		free(s);
		i++;
	}
	if (!paths[i] || !s)
	{
		ft_clean_array(cmd);
		return (NULL);
	}
	free(cmd[0]);
	cmd[0] = s;
	return (cmd);
}

void	ft_parse_cmd(char **cmd[2], char **av, char **aenv)
{
	char	**paths;

	paths = ft_get_path(aenv);
	cmd[0] = ft_split(av[2], ' ');
	cmd[0] = ft_get_cmdpath(cmd[0], paths);
	cmd[1] = ft_split(av[3], ' ');
	cmd[1] = ft_get_cmdpath(cmd[1], paths);
	if (!paths || !cmd[0] || !cmd[1])
	{
		ft_clean_array(paths);
		ft_error("cmd_error", cmd);
	}
	ft_clean_array(paths);
}

void	ft_parse_file(char **cmd[2], int fd_file[2], char **av)
{
	fd_file[0] = open(av[1], O_RDONLY);
	fd_file[1] = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 00700);
	if (fd_file[0] == -1 || fd_file[1] == -1)
		ft_error("file_error", cmd);
}

void	ft_parse_all(char **cmd[2], int fd_file[2], char **av, char **aenv)
{
	ft_parse_cmd(cmd, av, aenv);
	ft_parse_file(cmd, fd_file, av);
}
