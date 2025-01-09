/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkahil <pkahil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:30:00 by pkahil            #+#    #+#             */
/*   Updated: 2025/01/02 15:30:01 by pkahil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		size;
	int		i;
	char	*str;

	i = 0;
	size = (ft_strlen(s1) + ft_strlen(s2));
	str = malloc(sizeof(char) * size + 1);
	str[size] = '\0';
	if (str == NULL)
		return (NULL);
	while (s1 && *s1)
	{
		str[i] = *s1;
		i++;
		s1++;
	}
	while (s2 && *s2)
	{
		str[i] = *s2;
		i++;
		s2++;
	}
	return (str);
}
