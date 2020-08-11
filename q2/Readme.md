*** If you want to compile and run both policies at the same time : ***

1-Go in the terminal and write : make all
2-Then in the terminal write : ./eof "buffer_size" sample_input.txt && ./bd "buffer_size" sample_input.txt
    Example  : ./eof 4 sample_input.txt && ./bd 4 sample_input.txt

*** If you want to compile and run one policy at a time : ***
1-If you want to compile and run edf then write in the terminal: make edf
else write in the terminal : make bd
2-Then in the terminal write : ./edf "buffer_size" sample_input.txt  if you chose edf 
else write : ./bd "buffer_size" sample_input.txt
    Example : ./edf 4 sample_input.txt 


*** if you want to remove the compiled files from your system enter the following command in the terminal: make clean ***

*** Decreasing slack method in both policies ***
The slack is decreased for all the packets before the processing time.
If all the packets were processed, then while the buffer is not empty we remove the slack value by one and we continue processing the packets
until the buffer is empty.

