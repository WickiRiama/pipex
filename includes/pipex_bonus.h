/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:34:21 by mriant            #+#    #+#             */
/*   Updated: 2022/04/05 11:12:58 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

void	ft_clean_array(char	**s_array);
void	ft_error(char *error, char ***cmd, int *fd, int fd_len);
void	ft_init_fd(int *fd, int nb_fd);
void	ft_parse_cmd(char ***cmd, char **av, char **aenv, int nb_cmd);
void	ft_parse_file(int *fd, int fd_len, char **av);
int		ft_tablen(char ***tab);

#endif
