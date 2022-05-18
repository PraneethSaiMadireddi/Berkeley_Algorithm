# Implementation_of_Berkeley_Algorithm

This is implemented in C++ without using any library.
There is no need to install anything, just a C++ IDE will be fine. In my case I've used Jetbrains CLion.

Berkeley algorithm is a clock synchronization algorithm used in distributed systems. 

## What is Clock synchronization?
Clock synchronization is required for transaction processing applications, process control applications etc. This generates transmission delays and synchronization errors for processes and the clock synchronization algorithms try to synchronize the clocks in the system under the effect of these barriers.

Research paper: https://www.ijera.com/papers/Vol3_issue5/HU3513551364.pdf

Every process on the distributed system is considered to running on a different port, hence, to implement this throughout the project, I have explicitly defined the base port number globally. Then I have added the process id (base port + process id) to the base port number which helps us assign different port numbers for different processes on the distributed system. Furthermore, this also helps other member process in the distributed system to have knowledge of which process is running on which port making it easier to establish connection between processes and communicate.

## Logic - The way I did the project

Total number of processes in the distributed system and the process that is considered as the time daemon are taken as the input for this implementation. Further, sockets are used to establish the connection between various processes in the distributed system. At the beginning of every process, I randomly assigned logical clocks for every process in the distributed system to a number in the range of 1 to 50. To determine which process in the distributed system is the time daemon, every process in the distributed system compares its process id to the id of the time daemon that was given as input. If the id's being compared are equal, then that process becomes the time daemon and starts synchronizing the logical clock. Thereafter, I have implemented the steps in the Berkeley's clock synchronization algorithm. The time daemon process sends messages to all other processes in the distributed system asking for the logical clock value of the individual processes participating. The time daemon then calculates the offset and sends back a message along with the offset to all other processes in the distributes system, thus synchronizing the logical clocks.

## How to execute the code

`berkeley_algorithm/berkeley.cpp` contains the code for the Berkeley’s algorithm with the time daemon and the calculation of the logical offset.

I've created a Makefile to compile and execute the code with the commands written already which makes it easy for you.

`make compile` to compile the code.

`make run_berkeley` to run the program.

I used the shell script `shell_script.sh` to indicate the time daemon process and the total number of processes.

If you want to run using the executable file then you can type in
    ```
    ./bt.out <time_daemon> <total_number_process>
    ```
    
Example:
    ```
    ./bt.out 2 5
    ```

Sample Output:
    ```
    praneethsai@Praneeths-MacBook-Air Berkeley_Algorithm % make run_berkeley
    bash berkeley_algorithm/shell_script.sh 2 5
    Process 2 : logical time before sync: 45, logical time after sync:28  --Time Daemon--
    Process 1 : logical time before sync: 2, logical time after sync:28
    Process 3 : logical time before sync: 38, logical time after sync:28
    Process 4 : logical time before sync: 31, logical time after sync:28
    Process 5 : logical time before sync: 24, logical time after sync:28
    praneethsai@Praneeths-MacBook-Air Berkeley_Algorithm % 
    ```
