#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

// void ft_builtins(char *str, char **env)
// {
// 	if (!strcmp(str, "exit"))
// 	{
// 		free(str);
// 		exit(0);
// 	}
// 	else if (!strncmp(str, "echo", 4))
// 	{
// 		if (!strncmp(str, "echo -n ", 8))
// 			write(1, &str[8], strlen(&str[8]));
// 		else
// 		{
// 			write(1, &str[5], strlen(&str[5]));
// 			write(1, "\n", 1);
// 		}
// 	}
// 	else if (!strcmp(str, "env"))
// 	{
// 		while (*env)
// 		{
// 			write(1, *env, strlen(*env));
// 			write(1, "\n", 1);
// 			env++;
// 		}
// 	}
// }

// void ft_print_data(t_data *data)
// {
// 	while (data)
// 	{
// 		while (*data->comands)
// 		{
// 			printf("%s ", *data->comands);
// 			data->comands++;
// 		}
// 		printf("%c\n", data->end_symbol);
// 		data = data->next;
// 	}
// }

int	ft_get_count_dquote(char	*str)
{
	int i;
	static int	count = 0;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' && str[i - 1] != '\\')
			count++;
		i++;;
	}
	return (count);
}

char	*ft_readline()
{
	char	*str;
	char	*str1;
	char	*tmp;
	char	lst_symbol;
	int		count_dquote;

	str = NULL;
	str1 = NULL;
	str = readline("minishell> ");
	if (!str)
		return (NULL);
	lst_symbol = str[ft_strlen(str) - 1];
	count_dquote = ft_get_count_dquote(str);
	while (str[ft_strlen(str) - 1] == '\\' || count_dquote % 2 != 0)
	{
		if (lst_symbol == '\\')
			str1 = readline("> ");
		else if (count_dquote % 2 != 0)
			str1 = readline("dquote> ");
		if (!str1)
		{
			free(str);
			return (NULL);
		}
		if (str[ft_strlen(str) - 1] == '\\' || str[ft_strlen(str) - 1] == '"')
			str[ft_strlen(str) - 1] = '\0';
		tmp = str;
		str = ft_strjoin(str, str1);
		free(tmp);
		free(str1);
		if (!str)
			return (NULL);
		count_dquote = ft_get_count_dquote(str);
	}
	if (lst_symbol == '"')
		str[ft_strlen(str) - 1] = '\0';
	return(str);
}

int main(int argc, char **argv, char **env)
{
	char	*str;
	char	*str1;
	char	*tmp;
	t_data	*data;

	str = NULL;
	while(1)
	{
		str = ft_readline();
		if (str)
		{
			if (*str)
				add_history(str);
			printf("%s\n", str);
			free(str);
		}
		else
			break;
	}
	write(1, "\n", 1);
}
