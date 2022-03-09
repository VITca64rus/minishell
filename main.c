#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "libft/libft.h"

typedef struct s_data
{
	char			*in_file;
	char			*outfile;
	char			end_symbol;
	char			**comands;
	int				pype[2];
	struct s_data	*next;
}	t_data;

void ft_builtins(char *str, char **env)
{
	if (!strcmp(str, "exit"))
	{
		free(str);
		exit(0);
	}
	else if (!strncmp(str, "echo", 4))
	{
		if (!strncmp(str, "echo -n ", 8))
			write(1, &str[8], strlen(&str[8]));
		else
		{
			write(1, &str[5], strlen(&str[5]));
			write(1, "\n", 1);
		}
	}
	else if (!strcmp(str, "env"))
	{
		while (*env)
		{
			write(1, *env, strlen(*env));
			write(1, "\n", 1);
			env++;
		}
	}
}


t_data	*ft_lstlast(t_data *lst)
{
	t_data	*last;

	last = lst;
	while (last && last->next)
		last = last->next;
	return (last);
}


void	ft_lstadd_back(t_data **lst, t_data *new)
{
	t_data	*end;

	if (!*lst)
		*lst = new;
	else
	{
		end = ft_lstlast(*lst);
		end->next = new;
	}
}

t_data	*ft_parse(char *str)
{
	t_data	*buf;
	t_data	*data;
	char	**find1;
	char	**find2;

	data = NULL;
	find1 = ft_split(str, '|');
	while (*find1)
	{
		find2 = ft_split(*find1, ';');
		while (*find2)
		{
			buf = (t_data *)malloc(sizeof(t_data));
			buf->comands = ft_split(*find2, ' ');
			ft_lstadd_back(&data, buf);
			find2++;
		}
		find1++;
	}
	buf = data;
	int i;
	i = 0;

		while (str[i] != '\0')
		{
			if (str[i] == ';')
			{
				buf->end_symbol = ';';
				buf = buf->next;
			}
			else if (str[i] == '|')
			{
				buf->end_symbol = '|';
				buf = buf->next;
			}
			i++;
		}

	return (data);
}

void ft_print_data(t_data *data)
{
	while (data)
	{
		while (*data->comands)
		{
			printf("%s ", *data->comands);
			data->comands++;
		}
		printf("%c\n", data->end_symbol);
		data = data->next;
	}
}

int main(int argc, char **argv, char **env)
{
	char	*str;
	t_data	*data;

	while(1)
	{
		str = NULL;
		str = readline("\033[32mminishell> \033[0m");
		if (str)
		{
			if (*str)
			{
				add_history(str);
				data = ft_parse(str);
			}
			ft_print_data(data);
			free(str);
		}
		else
			break;
	}
	write(1, "\n", 1);
}
