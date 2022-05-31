/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:03:59 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/31 20:04:03 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*ft_lstlast(t_tokens *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*last;

	last = ft_lstlast(*lst);
	if (last)
		last->next = new;
	else
		*lst = new;
}

t_data	*ft_lstlast1(t_data *lst)
{
	t_data	*last;

	last = lst;
	while (last && last->next)
		last = last->next;
	return (last);
}


void	ft_lstadd_back1(t_data **lst, t_data *new)
{
	t_data	*end;

	if (!*lst)
		*lst = new;
	else
	{
		end = ft_lstlast1(*lst);
		end->next = new;
	}
}
