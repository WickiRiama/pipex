/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:58:40 by mriant            #+#    #+#             */
/*   Updated: 2022/03/28 13:20:46 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <sys/wait.h>
#include <stdio.h>

void	ft_do_cmd1(char **cmd, int fd_in, int fd_pipe[2], char **aenv)
{
	int	fd_stdin;
	int	fd_stdout;

	close (fd_pipe[0]);
	fd_stdin = dup2(fd_in, 0);
	close(fd_in);
	fd_stdout = dup2(fd_pipe[1], 1);
	close(fd_pipe[1]);
	if (fd_stdin == -1 || fd_stdout == -1)
		exit (1);
	if (execve(cmd[0], cmd, aenv) == -1)
		exit (1);
}

void	ft_do_cmd2(char **cmd, int fd_out, int fd_pipe[2], char **aenv)
{
	int	fd_stdin;
	int	fd_stdout;

	close(fd_pipe[1]);
	fd_stdin = dup2(fd_pipe[0], 0);
	close(fd_pipe[0]);
	fd_stdout = dup2(fd_out, 1);
	close(fd_out);
	if (fd_stdin == -1 || fd_stdout == -1)
		exit (1);
	if (execve(cmd[0], cmd, aenv) == -1)
		exit (1);
}

void	ft_do_fork(char **cmd[2], int fd_file[2], char **aenv)
{
	pid_t	pid_child[2];
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		ft_error("pipe_error", cmd);
	pid_child[0] = fork();
	if (pid_child[0] == -1)
		ft_error("fork_error", cmd);
	if (pid_child[0] == 0)
		ft_do_cmd1(cmd[0], fd_file[0], fd_pipe, aenv);
	close (fd_pipe[1]);
	waitpid(pid_child[0], 0, 0);
	pid_child[1] = fork();
	if (pid_child[1] == -1)
		ft_error("fork_error", cmd);
	if (pid_child[1] == 0)
		ft_do_cmd2(cmd[1], fd_file[1], fd_pipe, aenv);
	close (fd_pipe[0]);
	waitpid(pid_child[1], 0, 0);
}

int	main(int ac, char **av, char **aenv)
{
	char	**cmd[2];
	int		fd_file[2];

	cmd[0] = NULL;
	cmd[1] = NULL;
	if (ac != 5)
		ft_error("nb_ac", cmd);
	ft_parse_all(cmd, fd_file, av, aenv);
	ft_do_fork(cmd, fd_file, aenv);
	ft_clean_array(cmd[0]);
	ft_clean_array(cmd[1]);
	return (0);
}
