/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:31:22 by brandebr          #+#    #+#             */
/*   Updated: 2023/07/17 20:34:10 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	size_t	i;
	size_t	len;
	
	i =  0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*willy;


	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(s2));
	willy =(char *)malloc(sizeof(char) * (ft_strlen(s1) +ft_strlen(s2) + 1));
	if (!willy)
		return (NULL);
	while (s1[i])
	{
		willy[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		willy[i] = s2[j];
		i++;
		j++;
	}
	willy[i] = '\0';
	return (willy);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*c;

	i = 0;
	c = s;
	while (n > 0)
	{
		c[i] = '\0';
		i++;
		n--;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*willy;
	
	willy = (void *)malloc(count * size);
	if (!willy)
		return (0);
	ft_bzero(willy, count * size);
	return (willy);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize <= 0)
		return (ft_strlen(src));
	while (src[i] && i < dstsize -1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*willy;

	len = ft_strlen(s1) + 1;
	willy = (char *) malloc(len * sizeof(char));
	if (!willy)
		return (NULL);
	ft_strlcpy(willy, s1, len);
	return (willy);
}

