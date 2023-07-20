/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:42:40 by ywong             #+#    #+#             */
/*   Updated: 2022/11/21 15:30:49 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_putchar(int c);
int	ft_putnbr_dec(int nb);
int	ft_putnbr_hex(unsigned int nb, char c);
int	ft_putnbr_uns_dec(unsigned int nb);
int	ft_putptr(unsigned long nb);
int	ft_putstr(char *s);

#endif
