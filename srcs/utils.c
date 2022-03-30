/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:56:19 by mriant            #+#    #+#             */
/*   Updated: 2022/03/30 13:55:37 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "pipex.h"

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

void	ft_error(char *error, char **cmd[2], int fd_file[2], int fd_pipe[2])
{
	if (ft_strcmp(error, "nb_ac") == 0)
		ft_fprintf(2, "Error\nPipex takes 4 arguments file1 cmd1 cmd2 file2.\n");
	else
		perror(error);
	if (cmd[0])
		ft_clean_array(cmd[0]);
	if (cmd[1])
		ft_clean_array(cmd[1]);
	if (fd_file)
	{
		close(fd_file[0]);
		close(fd_file[1]);
	}
	if (fd_pipe)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	exit(1);
}
