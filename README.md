# Hamming
Hamming distance library and unit testing procedures

##Usage 
**Hamming.exe** command line tool can be called with 2 strings containing the 2 sequences that we want to calculate the hamming distance for.

### optional param : -binary

Specifies that the binary distance is calculated. 

#### For example:
Hamming.exe -binary "AB" "AA" will output 2. Because

"AB" -> 01000001 010000**10**

"AA" -> 01000001 010000**01**

While:
Hamming.exe  "A**B**" "A**A**" will output 1.  Because only a single character is different.

### optional param : -file

Specifies that the input string are actually paths to files that contain the strings to compare

#### For example:
Hamming.exe -binary "A.bin" "B.bin" will open the 2 files A.bin and B.bin and calculate the char or binary distance between them depending on the existence of the optional param **-binary**

##Projects

### HammingDll

Contains the main hamming distance functions. Generic functions are available that support both symbol based and binary hamming distance calculations.

### Hamming.exe

The command line application

### Hamming_UnitTest

Microsoft Native c++ test project for the logic exposed by **HammingDll**. This include simple test cases where the output is readily known. Also it includes random large strings and binary blobs generated and randomly altered in order to verify the correctness of the logic.

### Hamming_IntegTest 

Microsoft Native c++ test project for the application **Hamming.exe**. It executes the application exe from command line and pipes the *stdout* to a string which is investigated for correctness. Both string and binary file inputs are tested. 