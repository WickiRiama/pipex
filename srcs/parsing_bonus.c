/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:34:56 by mriant            #+#    #+#             */
/*   Updated: 2022/04/06 10:53:31 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include <fcntl.h>
#include <stdio.h>

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

void	ft_get_cmdpath(char **cmd, char **paths)
{
	int		i;
	char	*s;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		s = ft_strjoin(paths[i], cmd[0], "/");
		if (!s)
		{
			perror("Join error ");
			return ;
		}
		if (access(s, X_OK) == 0)
		{
			free(cmd[0]);
			cmd[0] = s;
			return ;
		}
		free(s);
		i++;
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
	if (ft_strcmp(av[1]) == 0)
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
		ft_get_cmdpath(cmd[i], paths);
		i++;
	}
	cmd[i] = NULL;
	ft_clean_array(&paths);
}

void	ft_parse_file(int *fd, int fd_len, char **av, int here_doc)
{
	if (here_doc == 0)
	{
		fd[0] = open(av[1], O_RDONLY);
		fd[fd_len - 1] = open(av[(fd_len / 2) + 2],
				O_CREAT | O_TRUNC | O_WRONLY, 00700);
	}
	else
	{
		fd[0] = open("temp_here_doc.txt",
				O_CREAT | O_TRUNC | O_RDWR, 00700);
		fd[fd_len - 1] = open(av[(fd_len / 2) + 2],
				O_CREAT | O_APPEND | O_WRONLY, 00700);
	}
	if (fd[0] == -1)
		perror(av[1]);
	if (fd[fd_len - 1] == -1)
		perror(av[(fd_len / 2) + 2]);
}
