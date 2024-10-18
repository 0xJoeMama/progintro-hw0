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

