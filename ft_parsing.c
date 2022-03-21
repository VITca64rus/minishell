/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazelda <sazelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 10:22:46 by natalia           #+#    #+#             */
/*   Updated: 2022/03/21 10:05:52 by sazelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void   	ft_parsing(char *str)
{
	int	i;
	int	count_quotes;
	int	count_dquotes;

	count_dquotes = 0;
	count_quotes = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '"') && (count_quotes % 2 == 0))
			count_dquotes++;
		else if ((str[i] == '\'') && (count_dquotes % 2 == 0))
			count_quotes++;
		else if ((str[i] == ' ') && (count_quotes % 2 == 0) && (count_dquotes % 2 == 0))
			printf("add for %d\n", i);
		i++;
	}
	if (count_quotes % 2 == 0 && count_dquotes % 2 == 0)
		printf("add for %d\n", i);
	else
		printf("Error parsing");
}

int main(void)
{
    char *str = "ls -l | 'echo pine apple'";
    ft_parsing(str);
}