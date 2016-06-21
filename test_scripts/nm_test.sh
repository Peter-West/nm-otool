../ft_nm $@ > test
nm $@ > test2
diff test test2