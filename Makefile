all:
	make -C libft
	gcc *.c libft/libft.a -ltermcap -lreadline
clean:
	make fclean -C libft