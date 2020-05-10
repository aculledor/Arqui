#4 valores posibles de Q
make cleanall
make
clear
for i in 0 1 2 3
do
	#10 pruebas por Q
	#5 pruebas por numero de fios
	for k in 0 1 2 3 4
	do
		echo  "#################    Q = $i  F = $k     #################"
		echo  "#################    Q = $i  F = $k     #################" >> resultado_$i$k.log

		
		for j in 0 1 2 3 4 5 6 7 8 9
		do
			echo "~~~~~~~~~ ITERACCION $j ~~~~~~~~~"
			echo "~~~~~~~~~ ITERACCION $j ~~~~~~~~~" >> resultado_$i$k.log
			./ejecutable $i $k >> resultado_$i$k.log
		done
	done
done
