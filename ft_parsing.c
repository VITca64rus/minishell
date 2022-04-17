/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 10:22:46 by natalia           #+#    #+#             */
/*   Updated: 2022/04/17 13:42:37 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "minishell.h"

void	ft_print_data(t_data *data)
{
	int i;

	printf("TOKENS\n");
	while (data)
	{
		printf("TYPE = %s\nARGS = ", data->type);
		i = 0;
		while (data->args[i])
		{
			printf("%s, ", data->args[i]);
			i++;
		}
		printf("\n---------------\n");
		data = data->next;
	}
}

char	*ft_get_type(char *str)
{
	int		i;
	char	*arr[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	i = 0;
	while (arr[i])
	{
		if (!strcmp(arr[i], str))
			return("BUILTINS");
		i++;
	}
	return("COMMAND");
}

t_data	*ft_get_data(t_tokens *tmp)
{
	t_tokens	*tokens=NULL;
	int i = 0;
	
	tokens = tmp;
	t_data	*data = NULL;
	t_data	*n;
	i = 0;
	while (tokens)
	{
		printf("%s\n", tokens->str);
		if ((tokens->str[0] == '<' || tokens->str[0] == '>'))
		{
			if (i > 0)
			{
				printf("i = %d\n", i);
				printf("TMP = %s\n", tmp->str);
				n = (t_data *)malloc(sizeof(t_data));
				n->args = (char **)malloc(sizeof(char *) * (i + 1));
				i = 0;
				while (tmp && tmp->str[0] != '<' && tmp->str[0] != '>')
				{
					n->args[i] = tmp->str;
					i++;
					tmp = tmp->next;
				}
				n->args[i] = NULL;
				n->type = ft_get_type(n->args[0]);
				ft_lstadd_back1(&data, n);
			}
			n = (t_data *)malloc(sizeof(t_data));
			n->type = tokens->str;
			n->args = (char **)malloc(sizeof(char *) * 2);
			n->args[0] = tokens->next->str;
			n->args[1] = NULL;
			ft_lstadd_back1(&data, n);
			tokens = tokens->next;
			tmp = tmp->next->next;
			i = -1;
		}
		else if (tokens->str[0] == '|')
		{
			if (i > 0)
			{
				n = (t_data *)malloc(sizeof(t_data));
				n->args = (char **)malloc(sizeof(char *) * (i + 1));
				i = 0;
				while (tmp && tmp->str[0] != '|')
				{
					n->args[i] = tmp->str;
					i++;
					tmp = tmp->next;
				}
				n->args[i] = NULL;
				n->type = ft_get_type(n->args[0]);
				ft_lstadd_back1(&data, n);
			}
			n = (t_data *)malloc(sizeof(t_data));
			n->type = tokens->str;
			n->args = (char **)malloc(sizeof(char *) * 1);
			n->args[0] = NULL;
			ft_lstadd_back1(&data, n);
			i = -1;
			tmp = tmp->next;
		}
		tokens = tokens->next;
		i++;
	}
	if (i > 0)
	{
		n = (t_data *)malloc(sizeof(t_data));
		n->args = (char **)malloc(sizeof(char *) * (i + 1));
		i = 0;
		while (tmp && tmp->str[0] != '|')
		{
			n->args[i] = tmp->str;
			i++;
			tmp = tmp->next;
		}
		n->args[i] = NULL;
		n->type = ft_get_type(n->args[0]);
		ft_lstadd_back1(&data, n);
	}

	return(data);
}

t_data	*ft_parsing(char *str)
{
	int	i;
	int	count_quotes;
	int	count_dquotes;
	int	start;
	t_tokens	*tokens = NULL;
	t_tokens	*new;
	t_tokens	*tmp;

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
			new = (t_tokens *)malloc(sizeof(t_tokens));
			new->str = ft_strdup(str);
			new->str[i] = '\0';
			new->next = NULL;
			ft_lstadd_back(&tokens, new);
			str = &str[i+1];
			i = -1;
		}
		i++;
	}
	if (count_quotes % 2 == 0 && count_dquotes % 2 == 0)
	{
		new = (t_tokens *)malloc(sizeof(t_tokens));
		new->str = ft_strdup(str);
		new->str[i] = '\0';
		new->next = NULL;
		ft_lstadd_back(&tokens, new);
	}
	else
		printf("Error parsing");
	tmp = tokens;
	while (tokens)
	{
		i = 0;
		if (tokens->str[0] != '\'' && tokens->str[0] != '"')
		{
			while (tokens->str[i] != '\0')
			{
				if ((tokens->str[i] == '|' || tokens->str[i] == '>' || tokens->str[i] == '<' ) && (i != 0))
				{
					new = (t_tokens *)malloc(sizeof(t_tokens));
					new->str = ft_strdup(&tokens->str[i]);
					tokens->str[i] = '\0';
					new->next = tokens->next;
					tokens->next = new;
					break;
		
				}
				else if ((tokens->str[i] == '|' || tokens->str[i] == '>' || tokens->str[i] == '<' ) && (i == 0) && (tokens->str[i + 1] != '\0'))
				{
					new = (t_tokens *)malloc(sizeof(t_tokens));
					if (((tokens->str[i] == '>' && tokens->str[i + 1] == '>') || (tokens->str[i] == '<' && tokens->str[i + 1] == '<')))
					{
						if (tokens->str[i + 2] == '\0')
							break;
						new->str = ft_strdup(&tokens->str[i + 2]);
						tokens->str[i + 2] = '\0';
					}
					else
					{
						new->str = ft_strdup(&tokens->str[i + 1]);
						tokens->str[i + 1] = '\0';
					}
					new->next = tokens->next;
					tokens->next = new;
					break;
				}
				i++;
			}
		}
		tokens = tokens->next;
	}

	t_data	*data = NULL;
	data = ft_get_data(tmp);
	ft_print_data(data);
	return(data);
}

int main(int argc, char **argv, char **envp)
{
    char *str;
	t_data *data;
	str = ft_strdup("< infile.txt cat | wc -l > outfile.txt");
	//str = ft_strdup("<< infile ls -l > file| echo 'pine | echo apple'");
	data = ft_parsing(str);
	ft_search_command(data, envp);
	printf("STR = %s\n", str);
}


