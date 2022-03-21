#include "minishell.h"

t_tokens	*ft_lstlast(t_tokens *lst)
{
	t_tokens	*last;

	last = lst;
	while (last && last->next)
		last = last->next;
	return (last);
}


void	ft_lstadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*end;

	if (!*lst)
		*lst = new;
	else
	{
		end = ft_lstlast(*lst);
		end->next = new;
	}
}
