###############################################################
#	Program:
#	Week 13, Genealogy
#     	Brother Falin, CS235
# 	Author:
#     	Ian Petty
# 	Summary:
#     Simply type "make" and press enter. 
#     Then type "./a.out cameron.ged" and
#     then press enter again. This should execute the program.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: main.o
	g++ -o a.out main.o -g
	tar -cf main.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week12.o     : the driver program
#      spellCheck.o   : the spell-check program and driver
##############################################################
main.o: main.cpp list1.h node.h
	g++ -c main.cpp -g

