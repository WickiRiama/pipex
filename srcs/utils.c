/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:56:19 by mriant            #+#    #+#             */
/*   Updated: 2022/03/28 13:24:24 by mriant           ###   ########.fr       */
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

void	ft_error(char *error, char **cmd[2])
{
	if (ft_strcmp(error, "nb_ac") == 0)
		ft_fprintf(2, "Error\nPipex takes 4 arguments file1 cmd1 cmd2 file2.\n");
	if (ft_strcmp(error, "cmd_error") == 0)
		perror("Command error\n");
	if (ft_strcmp(error, "file_error") == 0)
		perror("File error\n");
	if (ft_strcmp(error, "pipe_error") == 0)
		perror("Pipe error\n");
	if (ft_strcmp(error, "fork_error") == 0)
		perror("Fork error\n");
	if (cmd[0])
		ft_clean_array(cmd[0]);
	if (cmd[1])
		ft_clean_array(cmd[1]);
	exit(1);
}
