/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:56:19 by mriant            #+#    #+#             */
/*   Updated: 2022/04/05 11:03:51 by mriant           ###   ########.fr       */
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
	if (error && ft_strcmp(error, "nb_ac") == 0)
		ft_fprintf(2, "Error\nPipex takes 4 arguments file1 cmd1 cmd2 file2.\n");
	else if (error)
		perror(error);
	if (cmd[0])
		ft_clean_array(cmd[0]);
	if (cmd[1])
		ft_clean_array(cmd[1]);
	if (fd_file)
	{
		if (fd_file[0] != -1)
			close(fd_file[0]);
		if (fd_file[1] != -1)
			close(fd_file[1]);
	}
	if (fd_pipe)
	{
		if (fd_pipe[0] != -1)
			close(fd_pipe[0]);
		if (fd_pipe[1] != -1)
			close(fd_pipe[1]);
	}
	exit(1);
}
