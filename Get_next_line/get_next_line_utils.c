/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:32:44 by mriant            #+#    #+#             */
/*   Updated: 2021/12/14 15:27:46 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i ++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;
	size_t	i;
	char	*str;

	result = malloc(count * size);
	if (!result)
		return (NULL);
	str = (char *)result;
	i = 0;
	while (i < count * size)
	{
		str[i] = '\0';
		i++;
	}
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *) s;
	while (str[i])
	{
		if (str[i] == (unsigned char) c)
			return ((char *)s + i);
		i ++;
	}
	if (str[i] == (unsigned char) c)
		return ((char *)s + i);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	if (!s || start > ft_strlen(s))
	{
		result = ft_calloc(1, 1);
		return (result);
	}
	if (ft_strlen(s) - start < len)
		i = ft_strlen(s) - start;
	else
		i = len;
	result = ft_calloc(sizeof(char), (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i + start] && i < len)
	{
		result[i] = s[i + start];
		i ++;
	}
	return (result);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		i;

	dest = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i ++;
	}
	dest[i] = '\0';
	return (dest);
}
