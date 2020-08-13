*** If you want to compile and run both policies at the same time : ***

1-Go in the terminal and write : make all
2-Then in the terminal write : ./eof "buffer_size" sample_input.txt && ./bd "buffer_size" sample_input.txt
    Example  : ./eof 4 sample_input.txt && ./bd 4 sample_input.txt

*** If you want to compile and run one policy at a time : ***
1-If you want to compile and run edf then write in the terminal: make edf
else write in the terminal : make bd
2-Then in the terminal write : ./edf "buffer_size" sample_input.txt  if you chose edf.
else write : ./bd "buffer_size" sample_input.txt
    Example 1: ./edf 4 sample_input.txt 
    Example 2: ./bd 4 sample_input.txt 

*** IMPORTANT : My code reads the file and takes in account that there is a space between the packets ***
*** IMPORTANT : If you already ran the code and want to re-run again ***on a different input file*** , you need to go in terminal and enter : make clean ,  and only then you can recompile and run the code ***

*** if you want to remove the compiled files from your system enter the following command in the terminal: make clean ***

*** Decreasing slack method in both policies ***
The slack is decreased for all the packets before the processing time.
If all the packets were processed, then while the buffer is not empty we remove the slack value by one and we continue processing the packets
until the buffer is empty.

