# cmdline Problems

## byte0
Not that hard to solve. Just autocomplete like 5 million folders when 'cd'-ing.  
Though to be honest, the pokemon reference was funny. Didn't know byte0 was a man of culture

Solution:
```sh
$ cd i_wanna_be/.../ # to go to the deepest level
$ ls # to see the files in the current folder
treasure
$ cat treasure # print the contents of treasure
```

## byte1
"The output is not a manual page"...sure.
Hearing manual page literally lead to:
```sh
$ supercalifragilisticexpialidocious
The output is not a manual page - look elsewhere
$ man supercalifragilisticexpialidocious
```
and the answer was right there at the man page.

Though the idea of the man page being an output got me confused, so I dag a bit deeper:

```sh
$ which supercalifragilisticexpialidocious
/usr/bin/supercalifragilisticexpialidocious
```
revealed the location of the program being run

```sh
$ file /usr/bin/supercalifragilisticexpialidocious
/usr/bin/supercalifragilisticexpialidocious: Bourne-Again shell script, ASCII text executable
```

showed that the file being run is actually a bash script. This meant the content of the file was ASCII text,  
therefore we could 'cat' it and it would actually show what is being run(though I was let down when I saw what was actually happening):


```sh
$ cat /usr/bin/supercalifragilisticexpialidocious
#!/bin/bash
echo The output is not a manual page - look elsewhere
```
**Just a bash script that printed a single line**. Here I was, thinking this would be running some sort of 
program that would generate the man page on the spot and refresh the man database. Oh well!

*PS: Love the references by the way.*

## byte2
Simple 'grep' search looking up the sequence "will find" in the file shakespeare.txt:

```sh
$ ls
shakespeare.txt
$ grep "will find" shakespeare.txt
                He that sweetest rose will find
    That draw his knives i' th' war. Well, I will find him;
    If circumstances lead me, I will find
    But I will find him when he lies asleep,
    The Cardinal instantly will find employment,
    In time will find their fit rewards. That seal
    Cranmer will find a friend will not shrink from him.
    If you do love me, you will find me out.
    I will find you twenty lascivious turtles ere one chaste
  FORD.  [Aside]  I will be patient; I will find out this.
  THESEUS. She will find him by starlight. Here she comes; and her
    when she is sated with his body, she will find the error of her
    required conveniences, her delicate tenderness will find itself
    Post you to London, and you will find it so;
No one will find this: grep_is_your_friend
  Fellow. I have a head, sir, that will find out logs
    Can couch for fear but I will find them out;
    will breed no terror in the youth: he will find it comes from a
    The crown will find an heir. Great Alexander
```

Do note that the command:

```sh
$ grep will find shakespeare.txt
```

would not work, because it would look up the word "will" in the files "find" and "shakespeare.txt".
Since "find" does not exist, it would just error out and instead it would look up "will" in Shakespeare's works,
which results in beautiful stdout spam. We need to group the strings we are looking up into a single string and pass  
that as the first argument to 'grep'.

*PS: A somewhat cheaty way to do this, would be to search for _\*_ instead, since thats the pattern we've followed until now for the solutions and I doubt that '_' existed when Shakespeare was around:
This gives a bunch of ACT_x SC_x results, our result and KING_HENRY_VIII|EPILOGUE. For more info on what _\*_ matches, go [here](https://en.wikipedia.org/wiki/Regular_expression)*

## byte3
Pretty straight-forward solution:

```sh
$ ls
shakespeare.modified.txt  shakespeare.txt
$ diff shakespeare.txt shakespeare.modified.txt
11542c11542
<     And all the men and women merely players;
---
>     And all the men and women merely programmers;
```

The file passed first is the first line. Therefore the old word was 'players'.
The new old is 'programmers'(which makes logical sense, considering there couldn't be programmers in Shakespeare's works).

Interesting thing is that using 'man' to see how diff works(specifically how it treats files passed into it),  
I found the 'cmp' command, which finds the first byte that is different between two files. That might prove useful in the future.
One could also generate a patch file by redirecting the output of diff to a file and then use that file with the 'patch' command to transform shakespeare.txt to the modified version.

