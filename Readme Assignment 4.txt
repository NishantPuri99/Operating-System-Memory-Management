This Folder contains 2 separate codes (FixedPartitioning.cpp and VariablePartitioning.cpp) 
and 1 Readme File.
To run the codes,
(1) Extract The files.
(2) In the extracted folder, go to the address bar and type 'cmd'. This opens the command line.
(or open command line and navigate to the folder manually)
(3) In the command line, type
	->	g++ FixedPartitioning.cpp
			or
	->	g++ VariablePartitioning.cpp
	To compile the respective codes
(4) Once compiled, type 'a' to run the executable file created.
(5) The programs are designed to be intuitive. Follow the instructions as and when prompted.

**NOTE 1:
	Only The Number of Iterations are to be inputed by the user,
	The Number of Partitions, the Partition Sizes, their availability as well as 
	the Number of Processes and Process Sizes are being kept random.
**NOTE 2:
	While Finding The external fragmentation, initially the total free memory is calculated.
	Then out of all the unallocated processes, the one with the maximum size that could have
	been fit into the free memory space is taken as the External Fragmentation.