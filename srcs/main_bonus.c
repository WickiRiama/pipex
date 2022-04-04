/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:22:12 by mriant            #+#    #+#             */
/*   Updated: 2022/04/04 10:22:28 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include <sys/wait.h>
#include <stdio.h>

void	ft_do_cmd1(char **cmd[2], int fd_file[2], int fd_pipe[2], char **aenv)
{
	int	fd_stdin;
	int	fd_stdout;

	close(fd_pipe[0]);
	close(fd_file[1]);
	fd_stdin = dup2(fd_file[0], 0);
	fd_stdout = dup2(fd_pipe[1], 1);
	close(fd_file[0]);
	close(fd_pipe[1]);
	if (fd_stdin == -1 || fd_stdout == -1)
		ft_error(NULL, cmd, fd_file, fd_pipe);
	if (execve(cmd[0][0], cmd[0], aenv))
		ft_error(cmd[0][0], cmd, fd_file, fd_pipe);
}

void	ft_do_cmd2(char **cmd[2], int fd_file[2], int fd_pipe[2], char **aenv)
{
	int	fd_stdin;
	int	fd_stdout;

	close(fd_pipe[1]);
	close(fd_file[0]);
	fd_stdin = dup2(fd_pipe[0], 0);
	close(fd_pipe[0]);
	fd_stdout = dup2(fd_file[1], 1);
	close(fd_file[1]);
	if (fd_stdin == -1 || fd_stdout == -1)
		ft_error(NULL, cmd, fd_file, fd_pipe);
	if (execve(cmd[1][0], cmd[1], aenv) == -1)
		ft_error(cmd[1][0], cmd, fd_file, fd_pipe);
}

int	ft_do_fork(char **cmd[2], int fd_file[2], int fd_pipe[2], char **aenv)
{
	pid_t	pid_child[2];
	int		status;

	pid_child[0] = fork();
	if (pid_child[0] == -1)
		ft_error("Fork_error", cmd, fd_file, fd_pipe);
	if (pid_child[0] == 0)
		ft_do_cmd1(cmd, fd_file, fd_pipe, aenv);
	close (fd_pipe[1]);
	pid_child[1] = fork();
	if (pid_child[1] == -1)
		ft_error("Fork_error", cmd, fd_file, fd_pipe);
	if (pid_child[1] == 0)
		ft_do_cmd2(cmd, fd_file, fd_pipe, aenv);
	close (fd_pipe[0]);
	waitpid(pid_child[1], &status, 0);
	return (WEXITSTATUS(status));
}

int	main(int ac, char **av, char **aenv)
{
	char	**cmd[2];
	int		fd_file[2];
	int		fd_pipe[2];
	int		status;

	cmd[0] = NULL;
	cmd[1] = NULL;
	if (ac != 5)
		ft_error("nb_ac", cmd, NULL, NULL);
	ft_parse_all(cmd, fd_file, av, aenv);
	if (pipe(fd_pipe) == -1)
		ft_error("Pipe error", cmd, fd_file, NULL);
	status = ft_do_fork(cmd, fd_file, fd_pipe, aenv);
	close(fd_file[0]);
	close(fd_file[1]);
	ft_clean_array(cmd[0]);
	ft_clean_array(cmd[1]);
	return (status);
}
