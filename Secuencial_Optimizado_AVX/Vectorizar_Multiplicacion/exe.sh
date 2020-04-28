#4 valores posibles de Q
make cleanall
make
clear
for i in 0 1 2 3
do
	echo  "#################      Q = $i     #################"
	echo  "#################      Q = $i     #################" >> resultado$i.log

	#10 pruebas por Q
	for j in 0 1 2 3 4 5 6 7 8 9
	do
		echo "~~~~~~~~~ ITERACCION $j ~~~~~~~~~"
		echo "~~~~~~~~~ ITERACCION $j ~~~~~~~~~" >> resultado$i.log
		./ejecutable $i >> resultado$i.log
	done
done
