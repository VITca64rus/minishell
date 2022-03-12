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

char	*ft_readline()
{
	char	*str;
	char	*str1;
	char	*tmp;

	str = NULL;
	str1 = NULL;
	str = readline("minishell> ");
	if (!str)
		return (NULL);
	while (str[ft_strlen(str) - 1] == '\\')
	{
		str1 = readline("> ");
		if (!str1)
		{
			free(str);
			return (NULL);
		}
		str[ft_strlen(str) - 1] = '\0';
		tmp = str;
		str = ft_strjoin(str, str1);
		free(tmp);
		free(str1);
		if (!str)
			return (NULL);
	}
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
