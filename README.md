# wordle-cplusplus

This is a simple Wordle clone coded in C++ for playing on the terminal, in
the vein of the terminal games you'd find poking around on a Linux box in /usr/bin/games.

## Compilation
I've compiled on Windows 10 using both Mingw/Msys64 and WSL2. There's a Makefile in the
project, but if you need to compile manually:

```
g++ -Wall -Wextra src/wordle.cpp -o bin/wordle.exe
cp assets/words.txt bin/words.txt
cd bin && .\wordle.exe
```

## Gameplay demo
```
PS ..\bin> .\wordle.exe
Loading wordlist... done

You have 6 guesses to guess the five-letter word.

Legend:
* Correct letter, correct location
. Incorrect, not in puzzle
^ Correct letter, wrong location

 A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
1/6 > darth
You must enter a valid 5-letter word.
1/6 > worth
worth
...**
 A  B  C  D  E  F  G *H  I  J  K  L  M  N     P  Q     S *T  U  V     X  Y  Z
2/6 > filth
filth
...**
 A  B  C  D  E     G *H     J  K     M  N     P  Q     S *T  U  V     X  Y  Z
3/6 > heath
heath
^****
*A  B  C  D *E     G *H     J  K     M  N     P  Q     S *T  U  V     X  Y  Z
4/6 > death
death
*****

Congratulations; you won in 4 guesses.
PS ..\bin> .\wordle.exe
Loading wordlist... done

You have 6 guesses to guess the five-letter word.

Legend:
* Correct letter, correct location
. Incorrect, not in puzzle
^ Correct letter, wrong location

 A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
1/6 > wrath
wrath
.....
    B  C  D  E  F  G     I  J  K  L  M  N  O  P  Q     S     U  V     X  Y  Z
2/6 > bends
bends
....^
       C        F  G     I  J  K  L  M     O  P  Q    ^S     U  V     X  Y  Z
3/6 > quips
quips
..^.^
       C        F  G    ^I  J  K  L  M     O          ^S        V     X  Y  Z
4/6 > quit
The word was silly.
```
