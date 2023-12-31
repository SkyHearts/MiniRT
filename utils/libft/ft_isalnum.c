/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:30:53 by jyim              #+#    #+#             */
/*   Updated: 2022/11/07 13:31:27 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (c >= 65 && c <= 90)
		return (c);
	else if (c >= 97 && c <= 122)
		return (c);
	else if (c >= '0' && c <= '9')
		return (c);
	else
		return (0);
}
