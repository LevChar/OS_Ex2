# OS_Ex2
Second project(Exercise) in OS course.

## **Purpose:**

This Program was written as part of second
assgnment in OS course. This is a wrapper program of the
program that was written in first assignment (Ex 1). It
still receives 64 bit encoded input data from user.
data which represents a command and an input
of Polygon coordinates, the supported commands include
adding new Polygon to the Polygon database, and couple
of prnting operations, with different filters.

But, the main difference is that this program isn't
executing or storing the input, instead, it filters each
inserted command and data to the appropriate input file.
After proccessing all the input in this way, it starts
3 instances of helper program (the Ex1 program).
Each instance treats only commands of one type, so there
there is one instance for dealing with Hexagons, one
instance for dealing with Heptagons and one instance for
dealing with Octagons.

## **To run the program:**
Download \ clone the whole repo & run make command from the 
folder where you downloaded.

## **Compatibility:**
Program was compiled and tested in Linux (Ubunto) environment 
and in cygwin environment (under windows 10 OS).
