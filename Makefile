all:
	make -C libft
	gcc libft/libft.a *.c -ltermcap -lreadline
clean:
	make clean -C libft