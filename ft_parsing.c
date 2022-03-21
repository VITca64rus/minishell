/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalia <natalia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 10:22:46 by natalia           #+#    #+#             */
/*   Updated: 2022/03/20 11:54:15 by natalia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_check_quotes(int x, char *str)
{
	int i;
	int count_dquotes;
	int count_quotes;

	i = 0;
	count_dquotes = 0;
	count_quotes = 0;
	while (i < x)
	{
		if (str[i] == '"' && count_quotes % 2 == 0)
			count_dquotes++;
		if (str[i] == '\'' && count_dquotes % 2 == 0)
			count_quotes++;
		i++;
	}
	if (count_dquotes == 0 && count_quotes == 0)
		return (0);
	else
	{
		i++;
		while (str[i] != '\0')
		{
			if (str[i] == '"' && count_quotes % 2 == 0)
				count_dquotes++;
			if (str[i] == '\'' && count_dquotes % 2 == 0)
				count_quotes++;
			i++;
		}
		if (count_dquotes % 2 == 0 && count_quotes % 2 == 0)
			return (1);
		else
		{
			printf("error parser");
			return (-1);
		}
	}
	
}

void   	ft_parsing(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && printf("%d", ft_check_quotes(i, str)))
			//ft_split_own(i, &str);
			printf("\n");
		i++;
	}
}

int main(void)
{
    char *str = "ls -l | 'echo pine apple";
    ft_parsing(str);
}