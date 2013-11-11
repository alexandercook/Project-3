/*
* CSci4061 F2013 Assignment 3
* section: 3
* date: 11/11/13
* name: Devon Grandahl, Alex Cook
* id: 4260296, 4123940 
*/

1. 

2. After running the makefile, you can run the Packet program by typing './packet' into the console. To run main_mm type the command './main_mm'. To run main_malloc type the command './main_malloc'. To easily compare the efficiency of our memory manager with the standard one, type the command 'make main' into the console.

3.  -Packet simulates a basic server by recieving packets asynchronously and assembling them into the desired message. To allow for the asynchronous receipt of packets, our custom memory manager was used. 

	-main_mm times the execution of 1000 mm_gets followed by 1000 mm_puts. This is used to check the efficiency of our memory manager.
	
	-main_malloc times the execution of 1000 mallocs and then 1000 frees. This can be compared with the efficiency of our memory manager.
	
	-Our memory manager... 
