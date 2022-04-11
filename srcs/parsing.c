/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:34:56 by mriant            #+#    #+#             */
/*   Updated: 2022/04/11 18:06:37 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

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

void	ft_get_cmdpath(char ***all_cmd, char **cmd, char **paths)
{
	int		i;
	char	*s;

	i = 0;
	while (paths && paths[i])
	{
		s = ft_strjoin(paths[i], cmd[0], "/");
		if (!s)
			ft_error("Join error ", all_cmd, NULL);
		if (access(s, X_OK) == 0)
		{
			free(cmd[0]);
			cmd[0] = s;
			return ;
		}
		free(s);
		i++;
	}
	if (!ft_strchr(cmd[0], '/') || access(cmd[0], X_OK) == -1)
	{
		ft_fprintf(2, "%s: %s\n", "command not found", cmd[0]);
		cmd[0][0] = '\0';
	}
	return ;
}

void	ft_parse_cmd(char ***cmd, char **av, char **aenv, int *fd)
{
	char	**paths;
	int		i;

	paths = ft_get_path(aenv);
	if (!paths)
		ft_fprintf(2, "Can't find PATH\n");
	i = 0;
	while (i < 2)
	{
		cmd[i] = ft_split(av[i + 2], ' ');
		if (!cmd[i])
		{
			ft_clean_array(&paths);
			ft_error("Split error", cmd, fd);
		}
		ft_get_cmdpath(cmd, cmd[i], paths);
		i++;
	}
	cmd[i] = NULL;
	ft_clean_array(&paths);
}

void	ft_parse_file(int *fd, char **av)
{
	fd[0] = open(av[1], O_RDONLY);
	if (fd[0] == -1)
		ft_fprintf(2, "%s: %s\n", strerror(errno), av[1]);
	fd[3] = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 00644);
	if (fd[3] == -1)
		ft_fprintf(2, "%s: %s\n", strerror(errno), av[4]);
}
