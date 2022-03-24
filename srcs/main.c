/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:58:40 by mriant            #+#    #+#             */
/*   Updated: 2022/03/24 14:27:34 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <fcntl.h>

int	main(int ac, char **av, char **aenv)
{
	char	**cmd1;
	char	**cmd2;
	int		fd_f1;
	int		fd_f2;
	int		fd_stdin;

	if (ac != 5)
	{
		ft_fprintf(2, "Error\nPipex takes 4 arguments file1 cmd1 cmd2 file2.\n");
		return (1);
	}
	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');
	if (ft_parse_cmd(cmd1, cmd2, aenv))
		return (1);
	fd_f1 = open(av[1], O_RDONLY);
	fd_f2 = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 00700);
	if (fd_f1 == -1 || fd_f2 == -1)
	{
		ft_fprintf(2, "Error\nCan't open file.\n");
		ft_clean_array(cmd1);
		ft_clean_array(cmd2);
		return (1);
	}
	fd_stdin = dup2(fd_f1, 0);
	ft_printf("%d\n", fd_stdin);
	execve(cmd1[0], cmd1, aenv); // verifier le retour
	ft_clean_array(cmd1);
	ft_clean_array(cmd2);
	return (0);
}
