# Vertex Cover Optimization with C++ and Python using Inter Process Communication (IPC) in Linux.


# ece650-a1.py
Minimize the number of cameras police need to install, and still be as effective as possible with their monitoring at traffic intersections.

### Inputs and Outputs

##### Input Commands :
- add is used to add a street. It is specified as: “add "Street Name" (x1, y1) (x2, y2) . . . (xn,yn)”. Each (xi, yi) is a GPS coordinate. We interpret the coordinates as a poly-line segment. That is, we draw a line segment from (xi, yi) to (xi+1, yi+1). You are allowed to assume that each xi and yi is an integer. (Note, however, that the coordinates of an intersection may not be integers.)
- mod is used to modify the specification of a street. Its format is the same as for add. It is a new specification for a street you’ve specified before.
- rm is used to remove a street. It is specified as “rm "Street Name"”.
- gg causes the program to output the corresponding graph.

##### Sample Input :
The input comprises lines each of which specifies a command. There are 4 kinds of commands.
- add a street
- modify a street
- remove a Street
-  generate a graph (prints the vertices and edges of a graph to stdout). Here is an example of how your program should work. Visualizing this example using the Cartesian coordinate system may help you understand what’s going on.
  

##### Example :
add "Weber Street" (2,-1) (2,2) (5,5) (5,6) (3,8)  
add "King Street S" (4,2) (4,8)  
add "Davenport Road" (1,4) (5,8)  
gg 

V = 10  
E = { <1,3>, <2,3>, <3,4>, <3,6>, <7,6>, <6,5>, <9,6>, <6,8>, <6,10> }  

mod "Weber Street" (2,1) (2,2)  
gg  
V = 5  
E = { <2,6>, <6,5>, <6,8>, <6,10> }  

rm "King Street S"  
gg  
V = {}  
E = {}  
## Authors

- [@DhruvDholakia](https://www.github.com/DhruvDholakiaCE)


