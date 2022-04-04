/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:22:12 by mriant            #+#    #+#             */
/*   Updated: 2022/04/04 16:11:49 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include <sys/wait.h>
#include <stdio.h>

void	ft_do_dup(char ***cmd, int *fd, int len, int i)
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

int	ft_do_fork(char **cmd[2], int *fd, int nb_cmd, char **aenv)
{
	pid_t	pid_child;
	int		fd_pipe[2];
	int		status;
	int		i;

	i = 0;
	while (i < nb_cmd)
	{
		if (i != nb_cmd - 1)
		{
			if (pipe(fd_pipe) == -1)
				ft_error("Pipe error", cmd, fd_file, NULL);
			fd[i * 2 + 1] = fd_pipe[1];
			fd[i * 2 + 2] = fd_pipe[0];
		}
		pid_child = fork();
		if (pid_child == -1)
			ft_error("Fork_error", cmd, fd, nb_cmd * 2);
		if (pid_child == 0)
			ft_do_dup(cmd, fd, nb_cmd * 2, i);
		close (fd_pipe[1]);
		i++;
	}
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
	char	***cmd;
	int		*fd;
	int		nb_cmd;
	int		status;

	if (ac < 5)
		ft_error("nb_ac", cmd, NULL, NULL);
	nb_cmd = ac - 3;
	cmd = ft_calloc(sizeof(char**) * (nb_cmd + 1))
	if (!cmd)
		ft_error("malloc", cmd, NULL, NULL);
	ft_parse_cmd(cmd, av, aenv, ac - 2);
	fd = malloc(sizeof(int) * nb_cmd * 2);
	ft_init_fd(fd, nb_cmd * 2);
	if (!fd)
		ft_error("malloc", cmd, NULL, NULL);
	ft_parse_file(fd, nb_cmd * 2, av);
	status = ft_do_fork(cmd, fd, nb_cmd, aenv);
	close(fd[0]);
	close(fd[nb_cmd * 2 - 1]);
	ft_clean_array(cmd[0]);
	ft_clean_array(cmd[1]);
	return (status);
}
