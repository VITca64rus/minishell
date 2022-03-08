all:
	make -C libft
	gcc libft/libft.a *.c -ltermcap
clean:
	make clean -C libft