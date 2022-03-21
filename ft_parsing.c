/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalia <natalia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 10:22:46 by natalia           #+#    #+#             */
/*   Updated: 2022/03/21 21:34:26 by natalia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void   	ft_parsing(char *str)
{
	int	i;
	int	count_quotes;
	int	count_dquotes;
	int	start;
	t_tokens	*tokens=NULL;
	t_tokens	*new;

	count_dquotes = 0;
	count_quotes = 0;
	i = 0;
	start = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '"') && (count_quotes % 2 == 0) && str[i - 1] != '\\')
			count_dquotes++;
		else if ((str[i] == '\'') && (count_dquotes % 2 == 0) && str[i - 1] != '\\')
			count_quotes++;
		else if ((str[i] == ' ') && (count_quotes % 2 == 0) && (count_dquotes % 2 == 0))
		{
			printf("add for %d\n", i);
			new = (t_tokens *)malloc(sizeof(t_tokens));
			new->str = ft_strdup(str);
			new->str[i] = '\0';
			ft_lstadd_back(&tokens, new);
			str = &str[i+1];
			i = -1;
		}
		i++;
	}
	if (count_quotes % 2 == 0 && count_dquotes % 2 == 0)
	{
		printf("add for %d\n", i);
		new = (t_tokens *)malloc(sizeof(t_tokens));
		new->str = ft_strdup(str);
		new->str[i] = '\0';
		ft_lstadd_back(&tokens, new);
	}
	else
		printf("Error parsing");
	
	while (tokens)
	{
		printf("%s\n", tokens->str);
		tokens = tokens->next;
	}
}

int main(void)
{
    char *str = "ls -l| \"echo\\\" pine apple\"";
	printf("TEST\n");
	ft_parsing(str);
	printf("STR = %s\n", str);
}