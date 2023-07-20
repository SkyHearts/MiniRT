/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:01:26 by jyim              #+#    #+#             */
/*   Updated: 2022/11/09 17:07:20 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*p_map;
	t_list	**p_map2;

	if (!lst || !f || !del)
		return (0);
	p_map = NULL;
	p_map2 = &p_map;
	while (lst != NULL)
	{
		temp = ft_lstnew(f(lst->content));
		ft_lstadd_back(p_map2, temp);
		lst = lst->next;
	}
	return (p_map);
}
