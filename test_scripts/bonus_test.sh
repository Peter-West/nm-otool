../ft_nm -j $@ > testb
nm -j $@ > testb2
diff testb testb2

../ft_nm -u $@ >> testb
nm -u $@ >> testb2
diff testb testb2

../ft_nm -U $@ >> testb
nm -U $@ >> testb2
diff testb testb2

../ft_nm -r $@ >> testb
nm -r $@ >> testb2
diff testb testb2

../ft_nm -p $@ >> testb
nm -p $@ >> testb2
diff testb testb2
