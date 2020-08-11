# myls


Implementation of the Linux terminal's ls (LiSt) command.

Created by Yusuf Saleem and John Wu as part of CMPT 300: Operating Systems I at Simon Fraser University.

Calls to myls take the form of:
./myls (*options*) (*files*)                //parenthesis are to be omitted

# Options
the following options are supported
* -i: print the index number of each file
* -l: print additional details of each file.
* -R: recursively call myls on any subfolder found (if any).

options may be called in any permutation. The following are all valid options 

* -i -R
* -Ril
* -iR -iL

inputted options that contain an invalid character (not **i**, **l** or **R**) will cause an error.

# Files
Starting with the first passed parameter, any parameters that begin with **-** are counted as options. 
This behavior ends once the command encounters a parameter that does not start with **-**.
The first parameter that does not begin with a **-** will be considered as a target file to be searched for.
Any further parameters will be counted as list target. This includes any parameters that start with **-**

# Additional Details
If no files are declared as list targets, the command will list the current directory.
**'~'** can be used as a path to the user's home folder. 
**'\*'** can be used as a wild card, ex. *\*.c* will list all .C files in the current directory. 
Unlike Linux's implementation of ls, myls lists one file/directoy per column. This display can be replecated by calling Linux's ls with the -1 option

