# COSC-320-Project-3
This project you will work with a partner to learn about, implement, and document one interesting graph algorithm or data structure that was not covered during the course lecture. You will prepare a full typed report to describe the motivation for the topic, theoretical properties with some justification, and the results of your own implementation<br />
https://github.com/dawsboss/COSC-320-Project-3

### Grant Dawson and Ryan Rosiak

# Project 3 : Graphs for job scheduling

### During this project, you will
*  be exposed to the breadth of problem domains in graph theory and computer science
*  develop the skills needed to research a problem, understand its motivations and potential solutions
*  be exposed to the genesis of a problem and its historical solutions
*  practice communicating complicated material in computer science and applied mathematics



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
This program will not actually take user input, this is just for testing purposes (as of now).

## Output

**Id  Data  t-level  b-level  ALAP**<br />
\-----------------------------------------<br />
*All nodes with above data*<br />
    .<br />
    .<br />
    .<br />


start: *All nodes that are at the begining*<br />

Distance: *Distance* at i->first: *Index*<br />
    .<br />
    .<br />
    .<br />

CPU 1 Completed: *Nodes completed by CPU1*<br />
CPU 2 Completed: *Nodes completed by CPU2*<br />

**Id	Data	CPU\#	Start	Finish **<br />
\----------------------------------------- <br />
*All nodes with above data*<br />
    .<br />
    .<br />
    .<br />
**Note:** There is a slight problem with printing out. If the data is too long it will displace the following statistics 

## Post-Project Analyzing

#### Approach
Our approach was to start by taking all the code from our previous labs that applied to this. This included the very basics for our now complete Graph class along with a  Makefile. We went from this starting point and slowly added more methods based on what we needed and found from our research. We quickly realized that this problem was not fully solved, we found several research papers that applied, and although they assisted they did not give us a definite algorithm. From this point, we decided to take several ideas from several different research papers and come together all into one algorithm from our own design. This algorithm named "driver" would go from a modified BFS level to BFS level doing all nodes in the current level waiting till all nodes were done and then move to the next levels to come. This not only guaranteed that we would have all previous nodes done for the nodes below by one level but it also made some nasty edge cases. We will go on to explain this edge case in the **Deficiencies/Improvements** section.  

#### Interesting function design
1. The Graph class is all templated and as long as the data type has comparison and assignment operators it will be able to be put in this graph.
2. Memory efficiency - Although we are sure there are better and more efficient ways of doing some of our algorithms the data its self is held one of the best ways possible. Where once you give us data in a vertex that data next gets moved and other than the initial assignment that data is never moved. Our program has a master map sitting in the background so when we want to use some of the data or the data's meta-data we just have to have access to the index it is at in the main map. Once we have that we can access that vertex from anywhere without having to make any extra maps. We have a
3. Expandability - We left room for a quick upgrade so if you want to allow for more than just 2 CPUs then you are able to. The driving function has an int parameter and as of right now that does not do anything but most loops do not depend on this hardcoded 2 number so after a few fixes you can make an infinite number of CPUs possible.

#### Deficiencies/Improvements
Although we would get an answer seems correct, the algorithm would overcompensate when it could have an opportunity to move down a level and leave the other CPUs in the previous level. In our testing of the code (main.cpp) we show this edge case off in the first example. We determined that although after much time of thinking we could get past this edge case but then there would just be infinitely more edge cases. This is about the time we discovered that the problem has not been fully solved and is also NP-hard. We had a hunch throughout coding and researching this that the problem had not been solved yet but the article telling us that it is NP-hard solidified it.

#### Future plans
In the future, we would love to add the ability for our base functions to be able to handle any number of CPUs. Allowing for my diverse user inputs. We would also like to expand to another algorithm that would deal with the main edge case we found (previously stated). Once with a semi-finished product we could add it to a public website for public use of any means. 
