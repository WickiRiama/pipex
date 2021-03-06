/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:22:12 by mriant            #+#    #+#             */
/*   Updated: 2022/04/13 17:18:39 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include <sys/wait.h>
#include <stdio.h>

int	ft_wait(pid_t pid_child)
{
	int		status;
	int		result;
	pid_t	i;

	i = wait(&status);
	while (i > 0)
	{
		if (i == pid_child)
			result = status;
		i = wait(&status);
	}
	return (WEXITSTATUS(result));
}

void	ft_do_cmd(char ***cmd, int *fd, int i, char **aenv)
{
	int	fd_stdin;
	int	fd_stdout;
	int	nb_cmd;

	nb_cmd = ft_tablen(cmd);
	if (i != nb_cmd - 1)
	{
		if (fd[nb_cmd * 2 - 1] >= 0)
			fd[nb_cmd * 2 - 1] = close(fd[nb_cmd * 2 - 1]) - 2;
		if (fd[i * 2 + 2] >= 0)
			fd[i * 2 + 2] = close(fd[i * 2 + 2]) - 2;
	}
	fd_stdin = dup2(fd[(i - 1) * 2 + 2], 0);
	fd_stdout = dup2(fd[i * 2 + 1], 1);
	if (fd[(i - 1) * 2 + 2] >= 0)
		fd[(i - 1) * 2 + 2] = close(fd[(i - 1) * 2 + 2]) - 2;
	if (fd[i * 2 + 1] >= 0)
		fd[i * 2 + 1] = close(fd[i * 2 + 1]) - 2;
	if (fd_stdin == -1 || fd_stdout == -1)
		ft_error(NULL, cmd, fd, nb_cmd * 2);
	if (execve(cmd[i][0], cmd[i], aenv))
		ft_error(cmd[i][0], cmd, fd, nb_cmd);
}

int	ft_do_fork(char **cmd[2], int *fd, int nb_cmd, char **aenv)
{
	pid_t	pid_child;
	int		fd_pipe[2];
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i + 1])
		{
			if (pipe(fd_pipe) == -1)
				ft_error("Pipe error", cmd, fd, nb_cmd * 2);
			fd[i * 2 + 1] = fd_pipe[1];
			fd[i * 2 + 2] = fd_pipe[0];
		}
		pid_child = fork();
		if (pid_child == -1)
			ft_error("Fork_error", cmd, fd, nb_cmd * 2);
		if (pid_child == 0)
			ft_do_cmd(cmd, fd, i, aenv);
		fd[i * 2] = close(fd[i * 2]) - 2;
		fd[i * 2 + 1] = close(fd[i * 2 + 1]) - 2;
		i++;
	}
	i = ft_wait(pid_child);
	return (i);
}

int	main(int ac, char **av, char **aenv)
{
	char	***cmd;
	int		*fd;
	int		status;
	int		here_doc;

	if (ac < 5)
		ft_error("nb_ac", NULL, NULL, 0);
	here_doc = 0;
	if (ft_strcmp(av[1], "here_doc") == 0)
		here_doc = 1;
	if (here_doc == 1 && ac < 6)
		ft_error("nb_ac_here", NULL, NULL, 0);
	cmd = ft_calloc(sizeof(char **), ((ac - 3 - here_doc) + 1));
	if (!cmd)
		ft_error("malloc", NULL, NULL, 0);
	ft_parse_cmd(cmd, av, aenv, (ac - 3 - here_doc));
	fd = malloc(sizeof(int) * (ac - 3 - here_doc) * 2);
	ft_init_fd(fd, (ac - 3 - here_doc) * 2);
	if (!fd)
		ft_error("malloc", cmd, NULL, 0);
	ft_parse_file(fd, (ac - 3 - here_doc) * 2, av, here_doc);
	status = ft_do_fork(cmd, fd, (ac - 3 - here_doc), aenv);
	ft_clean_all(cmd, fd, (ac - 3 - here_doc) * 2);
	return (status);
}
