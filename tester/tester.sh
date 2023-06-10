#! /bin/bash

rm error.log

# -----begin test block-------
BASHOUT=$(ls) #put commands in the $()
echo $BASHOUT
USEROUT=$(./../minishell tester.sh) #replace tester.sh with the input
echo $USEROUT

if [ "$BASHOUT" == "$USEROUT" ];
then
	echo "output is the same"
else
	echo "output differs"
	echo -e "\nCOMMAND: 'ls'\n" >> error.log #change per block to reflect command 
	echo -e "bash output:\n\t"+$BASHOUT >> error.log #puts bash output in error.log 
	echo -e "\nuser output:\n\t"+$USEROUT >> error.log #puts user output in error.log
fi
# -----end of test block-------

