#! /bin/bash

make
#.././minishell
echo "VALID SYNTAX"
echo "ls:" | ./minishell
echo -e
echo "hey < test | ls -la" | ./minishell
echo -e
echo "ls -la && cat" | ./minishell
echo -e
echo "< test" | ./minishell

echo "INVALID SYNTAX"
echo -e
echo "|" | ./minishell
echo -e
echo "hey && <" | ./minishell
echo -e
echo "hey &&&& > outfile" | ./minishell
echo -e 
echo "< <" | ./minishell
echo -e
echo "hey < test | |" | ./minishell
echo -e
echo "hey < test | ls -la &&" | ./minishell
echo -e
echo "hey&&|lol" | ./minishell
echo -e
echo "hey && < |" | ./minishell
echo -e
echo "&& hey" | ./minishell

#echo "
#EMPTY BLOCK FOR EASY COPY PASTING
#REPLACE [PLACEHOLDER WITH COMMAND]


# # -----begin test block-------
# BASHOUT=$([PLACEHOLDER])
# # echo $BASHOUT
# USEROUT=$(./../minishell "[PLACEHOLDER]")
# # echo $USEROUT

# echo -e "\n[PLACEHOLDER]"
# if [ "$BASHOUT" == "$USEROUT" ];
# then
# 	echo -e "${GREEN}output is the same${NC}"
# else
# 	echo -e "${RED}output differs, check error.log for more info${NC}"
# 	echo -e "\n\nCOMMAND: '[PLACEHOLDER]'\n" >> error.log
# 	echo -e "bash output:\n\t"+$BASHOUT >> error.log
# 	echo -e "\nuser output:\n\t"+$USEROUT >> error.log
# fi
# # -----end of test block-------



#RED='\033[0;31m'
#GREEN='\033[0;32m'
#NC='\033[0m'

#rm error.log &> /dev/null

#echo "ls:"
## -----begin test block-------
#BASHOUT=$(ls) #put commands in the $()
## echo $BASHOUT
#USEROUT=$(./../minishell ls) #replace tester.sh with the input
## echo $USEROUT

#echo "ls"
#if [ "$BASHOUT" == "$USEROUT" ];
#then
#	echo -e "${GREEN}output is the same${NC}"
#else
#	echo -e "${RED}output differs, check error.log for more info${NC}"
#	echo -e "\n\nCOMMAND: 'ls'\n" >> error.log #change per block to reflect command 
#	echo -e "bash output:\n\t"+$BASHOUT >> error.log #puts bash output in error.log 
#	echo -e "\nuser output:\n\t"+$USEROUT >> error.log #puts user output in error.log
#fi
## -----end of test block-------

## -----begin test block-------
#BASHOUT=$(ls -la) #put commands in the $()
## echo $BASHOUT
#USEROUT=$(./../minishell "ls -la") #replace tester.sh with the input
## echo $USEROUT

#echo -e "\nls -la"
#if [ "$BASHOUT" == "$USEROUT" ];
#then
#	echo -e "${GREEN}output is the same${NC}"
#else
#	echo -e "${RED}output differs, check error.log for more info${NC}"
#	echo -e "\n\nCOMMAND: 'ls -la'\n" >> error.log #change per block to reflect command 
#	echo -e "bash output:\n\t"+$BASHOUT >> error.log #puts bash output in error.log 
#	echo -e "\nuser output:\n\t"+$USEROUT >> error.log #puts user output in error.log
#fi
## -----end of test block-------

