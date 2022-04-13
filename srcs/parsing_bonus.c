/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:34:56 by mriant            #+#    #+#             */
/*   Updated: 2022/04/13 11:20:55 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

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
			ft_error("Join error ", all_cmd, NULL, 0);
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

void	ft_parse_cmd(char ***cmd, char **av, char **aenv, int nb_cmd)
{
	char	**paths;
	int		i;
	int		here_doc;

	paths = ft_get_path(aenv);
	if (!paths)
		ft_fprintf(2, "Can't find PATH\n");
	here_doc = 0;
	if (ft_strcmp(av[1], "here_doc") == 0)
		here_doc = 1;
	i = 0;
	while (i < nb_cmd)
	{
		cmd[i] = ft_split(av[i + 2 + here_doc], ' ');
		if (!cmd[i])
		{
			ft_clean_array(&paths);
			ft_error("Split error", cmd, NULL, 0);
		}
		ft_get_cmdpath(cmd, cmd[i], paths);
		i++;
	}
	cmd[i] = NULL;
	ft_clean_array(&paths);
}

void	ft_parse_here(int *fd, char **av)
{
	char	*str;
	char	*delim;

	fd[0] = open("temp_here_doc.txt",
			O_CREAT | O_TRUNC | O_WRONLY, 00644);
	str = get_next_line(0);
	delim = ft_strjoin(av[2], "\n", "");
	while (ft_strcmp(str, delim) != 0)
	{
		ft_fprintf(fd[0], "%s", str);
		free(str);
		str = get_next_line(0);
	}
	free(str);
	free(delim);
	close(fd[0]);
	fd[0] = open("temp_here_doc.txt", O_RDONLY);
	unlink("temp_here_doc.txt");
}

void	ft_parse_file(int *fd, int fd_len, char **av, int here_doc)
{
	if (here_doc == 0)
	{
		fd[0] = open(av[1], O_RDONLY);
		fd[fd_len - 1] = open(av[(fd_len / 2) + 2],
				O_CREAT | O_TRUNC | O_WRONLY, 00644);
	}
	else
	{
		ft_parse_here(fd, av);
		fd[fd_len - 1] = open(av[fd_len / 2 + 3],
				O_CREAT | O_APPEND | O_WRONLY, 00644);
	}
	if (fd[0] == -1)
		ft_fprintf(2, "%s: %s\n", strerror(errno), av[1]);
	if (fd[fd_len - 1] == -1)
		ft_fprintf(2, "%s: %s\n", strerror(errno), av[(fd_len / 2) + 2]);
}
