/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:58:40 by mriant            #+#    #+#             */
/*   Updated: 2022/03/24 18:05:25 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <sys/wait.h>

int	ft_do_cmd1(char **cmd, int fd_in, int fd_pipe[2], char **aenv)
{
	int	fd_stdin;
	int	fd_stdout;

	fd_stdin = dup2(fd_in, 0);
	close(fd_in);
	fd_stdout = dup2(fd_pipe[1], 1);
	close(fd_pipe[1]);
	if (fd_stdin == -1 || fd_stdout == -1)
		return (1);
	if (execve(cmd[0], cmd, aenv) == -1)
		return (1);
	return (0);

}

int	ft_do_cmd2(char **cmd, int fd_out, int fd_pipe[2], char **aenv)
{
	int	fd_stdin;
	int	fd_stdout;

	fd_stdin = dup2(fd_pipe[0], 0);
	close(fd_pipe[0]);
	ft_printf("ici\n");
	fd_stdout = dup2(fd_out, 1);
	close(fd_out);
	if (fd_stdin == -1 || fd_stdout == -1)
		return (1);
	if (execve(cmd[0], cmd, aenv) == -1)
		return (1);
	return (0);

}

int	main(int ac, char **av, char **aenv)
{
	char	**cmd1;
	char	**cmd2;
	int		fd_f1;
	int		fd_f2;
	int		fd_pipe[2];
	pid_t	pid_child1;
	pid_t	pid_child2;

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
	if (fd_f1 == -1 || fd_f2 == -1 || pipe(fd_pipe) == -1)
	{
		ft_fprintf(2, "Error\nCan't open file.\n");
		ft_clean_array(cmd1);
		ft_clean_array(cmd2);
		return (1);
	}
	pid_child1 = fork();
	if (pid_child1 == 0)
	{
		if (ft_do_cmd1(cmd1, fd_f1, fd_pipe, aenv))
			exit(1);
		exit(0);
	}
	waitpid(pid_child1, 0, 0);
	close (fd_pipe[1]);
	pid_child2 = fork();
	if (pid_child2 == 0)
	{
		if (ft_do_cmd2(cmd2, fd_f2, fd_pipe, aenv))
			exit(1);
		exit(0);
	}

	waitpid(pid_child2, 0, 0);
	close (fd_pipe[0]);
	ft_clean_array(cmd1);
	ft_clean_array(cmd2);
	return (0);
	
}
