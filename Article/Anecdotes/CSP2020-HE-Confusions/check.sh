#!/bin/bash

Problems="julian zoo call snakes"
Racer=0
CE=0
NoFILE=0
if [ ! -d tmp ]
then
    mkdir tmp
fi
for fold in HE-*;
do
	Racer=$[${Racer}+1];
	state=${fold}$" : ";
	for name in ${Problems};
	do
		if [ -e ${fold}/${name}/${name}.cpp ]
		then
			cp ${fold}/${name}/${name}.cpp tmp/${name}.cpp;
			g++ -lm -o tmp/${name} tmp/${name}.cpp 2>tmp/CE.txt;
			if [ $? -eq 1 ]
			then
				CE=$[${CE}+1];
				state=${state}$" [ "${name}$" CE ] ";
			fi
		else
			NoFILE=$[${NoFILE}+1];
			state=${state}$" [ "${name}$" no file ] "
		fi
	done;
	echo ${state};
done

echo ${Racer} racers, ${NoFILE} files can\'t be found, ${CE} files CE.
