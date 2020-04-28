#9 valorres posibles de NLC
for i in 0 1 2 3 4 5 6 7 8
do
	echo  "#################      NLC = $i     #################"
	echo  "#################      NLC = $i     #################" >> resultado.log

	#15 pruebas por NLC
	for j in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
	do
		echo "~~~~~~~~~ ITERACCION $j ~~~~~~~~~"
		echo "~~~~~~~~~ ITERACCION $j ~~~~~~~~~" >> resultado.log
		./ejecutable $i >> resultado.log
	done
done
