../ft_otool $@ > test
otool -t $@ > test2
diff test test2