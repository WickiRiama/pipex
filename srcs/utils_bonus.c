/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:35:16 by mriant            #+#    #+#             */
/*   Updated: 2022/04/04 15:19:20 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "pipex_bonus.h"

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

void	ft_error(char *error, char ***cmd, int *fd, int fd_len)
{
	int	i;

	if (error && ft_strcmp(error, "nb_ac") == 0)
		ft_fprintf(2,
			"Error\nPipex takes at least 4 arguments file1 cmd1 cmd2 file2.\n");
	else if (error)
		perror(error);
	i = 0;
	while (cmd && cmd[i])
	{
		ft_clean_array(cmd[0]);
		i++;
	}
	i = 0;
	while (fd && i < fd_len)
	{
		if (fd[i] >= 0)
			close(fd[i]);
		i++;
	}
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