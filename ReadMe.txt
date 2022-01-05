*I love doing these big programs they are fun

*In this program there is many thing I had to really think about to help me finish it here are some of what I had to do

*First for read the files it was getting to complicated first i was reading everything in the file and save it in a string array then printing them 
sepreatly insted I decided to make a structure that held all the data in the orderthat i had it in the file, then I labled each data type to a spicific
value while the program was reading the file.

*Then it was getting the date and time from the system after doing some reserch I came upon this code from this website: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
			
			time_t now = time(0);
			char* dt = ctime(&now);
			cout << "The local date and time is: " << dt << endl;
			tm *gmtm = gmtime(&now);
			dt = asctime(gmtm);

but this code would print it out in this format:
		
		The local date and time is: Wed May 05 02:47:58 2021

so I came up with the solution to make a seperate function that would take the first chuck of it and return the date it by using a for loop:
		
		time_t now = time(0);
		char* dt = ctime(&now);
		string todayDate = "";
		for (int x = 0; x < 10; x++)
		{
		todayDate = todayDate + dt[x];
		}
		return todayDate;

after using it the returned value would look like this:
	
		Tue May 4 

and for also had to use #define _CRT_SECURE_NO_WARNINGS or the date function wont work.


*For my final report display I decide to go with it appering in the program insted of making a file, so I ended up making a file that records the data per transaction with
the data values like product type, number of units, and prices the file stored them as strings then when it came time to display daliy sales it would go through the transaction file "salesLogFile.txt"
and read thourgh each one to match the date for todays date then it will take all the data and transfer everthing into its right data type for example it would take a string price then convert it using stod(string to double)
so it can apper like a price should with .00 for cents.

*Another neat trick I learned is the system("Cls") this line of code can only work if you add the #include<stdlib.h> at the beging of the program this make it look like it is moving form one window to another but its only
clearing out all the old cluter of code that was used before.