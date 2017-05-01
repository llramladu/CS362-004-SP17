//Leanne Vermillion
//4/30/17
//randomstring.c as text assignment
//I started by looking at Piazza's to see what kinds of questions people were having about this assignment
//That helped me figure out that I needed to pull random chracaters using the ASCII table.
//The inputChar is only one line of code, return a random value from the ASCII table.
//The inputString is a little more complicated since it requires an array.
//It randomly fills the array with characters making sure the last character is always the /0.
//I thought about trying to set most of the values by hand and so the random was only a more
//limited random, but it seems to run so quickly with even with not everything set that I decided to be
//a bit more actually random.
//Here are my results.
//First Attempt:

//Iteration 4704981: c = Y, s = twfht, state = 9
//Iteration 4704982: c = A, s = vlcea, state = 9
//Iteration 4704983: c = <, s = reset, state = 9
//error $

//Second Attempt:

//Iteration 3600210: c = Y, s = twfht, state = 9
//Iteration 3600211: c = A, s = vlcea, state = 9
//Iteration 3600212: c = <, s = reset, state = 9
//error $ 

//I got it to print the error!