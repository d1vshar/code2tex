# a script to convert code snippets to a tex file.

## Building and Usage

You need gcc (mine was v9.3.0 but I guess v8.x.x+ will be fine) to compile and run it.
 
```
g++ code2tex.cpp -o code2tex
./code2tex <arguments>
```

### Folder setup
Make a file named `order.txt` that specifies the order of code to be included in the tex file. Each filename with extension on it's own line.

Example `order.txt`
```
QUE1.c
QUE2.c
QUE2.java
QUE3.sh
Part1/Q1.cpp
Part1/Q2.cpp
Part2/Q1.cpp
```

### File setup

The script extracts questions from the first multiline comment in your code.

```cpp
/*
Write a program that says Hello World.
*/
#include <iostream>

void sayHello();

int main() {
	sayHello();
}

/* Says Hello
and this comment will not be in the question
*/
void sayHello() {
	cout << "Hello world!";
}
```
	
### Arguments:

No arguments are optional and are to be entered in the same order.

| argument        | description |
|-----------------|-------------|
| targetfolder    | your homework folder where all code files are present. order.txt needs to be present in the root of this folder. |
| homework title  | your homework title |
| author name     | your name |
| author detail#1 | your detail. maybe roll no? course name? |
| author detail#2 | another detail? section? literally anything |
| organization    | your school/university name |

### Example Usage

```
git clone https://github.com/l0llygag/pdf2tex
```
```
cd pdf2tex
```
Suppose your homework is in a folder name `ihatehw` in `~/Documents`. This folder has `order.txt` that provides the order in which the files are to be added.
```
./pdf2tex ~/Documents/ihatehw/ "Homework name" "My name" "my roll no" "my course name" "university name"
```
This will generate a generated.tex file in `~/Documents/ihatehw/`.

Now if you want to convert this tex into pdf, you need a TeX runtime. (Like TexLive for linux). You will also need to install the minted package (texlive-latexextra for arch/manjaro)

## Known Issues

- Missing special characters in questions: latex special characters in questions don't get escaped. easy fix but * efforts * .
- Latex code snippets are weird: Yes cause runtime thinks your code has valid latex markdown. If the latex markdown is in a string in your code, then escaping the backslashes and other special characters will not work because of a limitation in the python library `pygments` (any latex code in strings does not get escaped). I need help with this.
