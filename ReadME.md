### Grant Dawson

# Project 3 : Graphs for job scheduling

### During this project, you will
*  be exposed to the breadth of problem domains in graph theory and computer science
*  develop the skills needed to research a problem, understand its motivations and potential solutions
*  be exposed to the genesis of a problem and its historical solutions
*  practice communicating complicated material in computer science and applied mathematics

TODO THIS BELOW NEEDS UPDATING===================================================

## How to run this program
#### Project
To run this program, you will need to first compile the code:

````
make
````

Now that our code is complied and ready to execute call:

````
./main
````
The actual input comes from once the prgram is running you w0ill have the opertunity to input a sentence into the console

## Output

If there are any mis-spelled words the the out put will be:
    "*Word*" was detected as misspelled, suggestions for a one letter replace:
    *Suggestions*

		Suggestion for a two letter replace:
		*Suggestion*

		.
		.
		.



Otherwise there was nothing spelled wrong and there will be no output!

## Post-Project Analyzing

#### Approach
I approached this problem with a sense of mobility. The actual main required only 3 lines of code. It requires you too initilizes then call a init function that will make a hash table with the given text documents dictionary. Finally you can call the autoCorrect function with the words that would would like to check. This makes it extremly easy for the user to implement the Dictionary class and makes the main really clean. Now saying this, the Dictionary relies on several libraries, so there are ups and downs.

#### Interesting function design
The autoCorrect function is extremly interesting because it can take any type of strings and any length and is able to check each word.This allows for a very clean main, only draw back could be is if the user wants to change the print they will have to go to Dictionary.cpp

#### Deficiencies/Improvements
With what I know now I would have liked to add a clean autoCorrect function so that if the user would have liked to change the output it would be easier to read and do so. I am sure there are also more efficient ways of doing the same thing with less moving of linked lists and I would have liked to explore these.
