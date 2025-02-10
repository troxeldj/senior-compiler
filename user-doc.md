# Senior Compiler Usage Doc

## prerequisites
To make sure you can run the output assembly using NASM make sure you have the following packages installed:
- gcc-multilib
- g++-multilib

This allows us to run x86 (32-bit) code on an x64 machine!

## Basic Usage
To Compile the compiler

``` bash
make
```

To compile a C file to x86 assmembly

```bash
./main <filename>
```

For example, let's say I have a file called test.c with the following code.

```c 
int test(int a, int b) {
	return a + b;
}

int main() {
	return test(10, 10);
}
```

I would compile this code with
```bash
./main test.c
```

## Command Line Arguments

Other command line arguments:
Positional Arg 1 (shown above): Input File Name
Positional Arg 2: Output File Name
Positional Arg 3: option
	- exec: will compile to ASM and run the output assembly with nasm using elf32 format (default)
	- object: will only compile to ASM (object)


More options will come with development