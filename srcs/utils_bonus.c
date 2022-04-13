/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:35:16 by mriant            #+#    #+#             */
/*   Updated: 2022/04/13 11:17:58 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "libft.h"
#include "pipex_bonus.h"

void	ft_clean_all(char ***cmd, int *fd, int fd_len)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		ft_clean_array(&cmd[i]);
		i++;
	}
	free(cmd);
	i = 0;
	while (fd && i < fd_len)
	{
		if (fd[i] >= 0)
			fd[i] = close(fd[i]) - 2;
		i++;
	}
	free(fd);
}

void	ft_clean_array(char	***s_array)
{
	int	i;

	if (!(*s_array))
		return ;
	i = 0;
	while (s_array[0][i])
	{
		free(s_array[0][i]);
		i++;
	}
	free(*s_array);
	*s_array = NULL;
}

void	ft_error(char *error, char ***cmd, int *fd, int fd_len)
{
	if (error && ft_strcmp(error, "nb_ac") == 0)
		ft_fprintf(2,
			"Error\nPipex takes at least 4 arguments file1 cmd1 cmd2 file2.\n");
	if (error && ft_strcmp(error, "nb_ac_here") == 0)
		ft_fprintf(2, "Error\n%s%s",
			"If \"here_doc\" is specified, pipex takes at ",
			"least 5 arguments here_doc STOP cmd1 cmd2 file2.\n");
	else if (error && error[0])
		ft_fprintf(2, "%s: %s\n", strerror(errno), error);
	ft_clean_all(cmd, fd, fd_len);
	exit(1);
}

void	ft_init_fd(int *fd, int nb_fd)
{
	int	i;

	i = 0;
	while (i < nb_fd)
	{
		fd[i] = -2;
		i++;
	}
}

int	ft_tablen(char ***tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}
