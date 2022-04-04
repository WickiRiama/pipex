/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:34:21 by mriant            #+#    #+#             */
/*   Updated: 2022/04/04 10:34:27 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

void	ft_clean_array(char	**s_array);
void	ft_error(char *error, char **cmd[2], int fd_file[2], int fd_pipe[2]);
void	ft_parse_all(char **cmd[2], int fd_file[2], char **av, char **aenv);

#endif
