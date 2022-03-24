/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:40:02 by mriant            #+#    #+#             */
/*   Updated: 2022/03/24 11:58:02 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

char	**ft_get_path(char **aenv)
{
	char	**result;
	int		i;

	if (!aenv)
		return (NULL);
	i = 0;
	while (aenv[i] && ft_strncmp(aenv[i], "PATH=", 5) != 0)
		i++;
	if (!aenv[i])
		return (NULL);
	result = ft_split(aenv[i] + 5, ':');
	return (result);
}

char	**ft_get_cmdpath(char **cmd, char **paths)
{
	int		i;
	char	*s;

	if (!cmd || !paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		s = ft_strjoin(paths[i], cmd[0], "/");
		if (!s)
			break ;
		if (access(s, X_OK) == 0)
			break ;
		free(s);
		i++;
	}
	if (!paths[i] || !s)
	{
		ft_clean_array(cmd);
		return (NULL);
	}
	free(cmd[0]);
	cmd[0] = s;
	return (cmd);
}

int	ft_parse_cmd(char **cmd1, char **cmd2, char **aenv)
{
	char	**paths;

	paths = ft_get_path(aenv);
	cmd1 = ft_get_cmdpath(cmd1, paths);
	cmd2 = ft_get_cmdpath(cmd2, paths);
	if (!paths || !cmd1 || !cmd2)
	{
		ft_fprintf(2, "Error\nCommand not recognized.\n");
		ft_clean_array(paths);
		ft_clean_array(cmd1);
		ft_clean_array(cmd2);
		return (1);
	}
	ft_clean_array(paths);
	return (0);
}