/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:35:16 by mriant            #+#    #+#             */
/*   Updated: 2022/04/08 16:33:17 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "pipex.h"

void	ft_clean_all(char ***cmd, int *fd)
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
	while (fd && i < 4)
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

void	ft_error(char *error, char ***cmd, int *fd)
{
	if (error && ft_strcmp(error, "nb_ac") == 0)
		ft_fprintf(2,
			"Error\nPipex takes 4 arguments file1 cmd1 cmd2 file2.\n");
	else if (error)
		perror(error);
	ft_clean_all(cmd, fd);
	exit(1);
}

void	ft_init_fd(int *fd)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		fd[i] = -2;
		i++;
	}
}
