# cmdline Problems

## byte0
cd into the deepest level.
Though to be honest, the pokemon reference was funny. Didn't know byte0 was a man of culture

Solution:
```sh
$ cd i_wanna_be/.../ # to go to the deepest level
$ ls # to see the files in the current folder
treasure
$ cat treasure # print the contents of treasure
```
*PS: after learning how find works we can use 'find i_wanna_be -type f | xargs cat'

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

*PS: A somewhat cheaty way to do this, would be to search for \_\*\_ instead, since thats the pattern we've followed until now for the solutions and I doubt that '_' existed when Shakespeare was around:
This gives a bunch of ACT_x SC_x results, our result and KING_HENRY_VIII|EPILOGUE. For more info on what \_\*\_ matches, go [here](https://en.wikipedia.org/wiki/Regular_expression)*

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

## byte4
After entering the environment, using 'la' an alias for 'ls -a' I saw that there is a 'maze' folder.
I tried using find and failed miserably.  
There is a program that I have been using for years called 'fd', which is basically just a more modern version of 'find'.  
The issue is, the search syntax for that program is completely different.
Normally I would run something like: `fd cup.txt . --hidden`
Trying the same with find, was not fun:

```sh
$ find cup.txt maze
find: ‘cup.txt’: No such file or directory
maze
maze/right
maze/right/right
maze/right/right/5
maze/right/right/5/box.txt
maze/right/right/7
maze/right/right/7/box.txt
maze/right/right/3
maze/right/right/3/box.txt
...
```

"No such file or directory", meant that this is not the right syntax for 'find' and that  
cup.txt was being passed in as a file.
So now I needed to check for instructions for find.

```sh
$ find --help
Usage: find [-H] [-L] [-P] [-Olevel] [-D debugopts] [path...] [expression]

Default path is the current directory; default expression is -print.
Expression may consist of: operators, options, tests, and actions.

Operators (decreasing precedence; -and is implicit where no others are given):
      ( EXPR )   ! EXPR   -not EXPR   EXPR1 -a EXPR2   EXPR1 -and EXPR2
      EXPR1 -o EXPR2   EXPR1 -or EXPR2   EXPR1 , EXPR2

Positional options (always true):
      -daystart -follow -nowarn -regextype -warn

Normal options (always true, specified before other expressions):
      -depth -files0-from FILE -maxdepth LEVELS -mindepth LEVELS
       -mount -noleaf -xdev -ignore_readdir_race -noignore_readdir_race

Tests (N can be +N or -N or N):
      -amin N -anewer FILE -atime N -cmin N -cnewer FILE -context CONTEXT
      -ctime N -empty -false -fstype TYPE -gid N -group NAME -ilname PATTERN
      -iname PATTERN -inum N -iwholename PATTERN -iregex PATTERN
      -links N -lname PATTERN -mmin N -mtime N -name PATTERN -newer FILE
      -nouser -nogroup -path PATTERN -perm [-/]MODE -regex PATTERN
      -readable -writable -executable
      -wholename PATTERN -size N[bcwkMG] -true -type [bcdpflsD] -uid N
      -used N -user NAME -xtype [bcdpfls]

Actions:
      -delete -print0 -printf FORMAT -fprintf FILE FORMAT -print
      -fprint0 FILE -fprint FILE -ls -fls FILE -prune -quit
      -exec COMMAND ; -exec COMMAND {} + -ok COMMAND ;
      -execdir COMMAND ; -execdir COMMAND {} + -okdir COMMAND ;

Other common options:
      --help                   display this help and exit
      --version                output version information and exit

Valid arguments for -D:
exec, opt, rates, search, stat, time, tree, all, help
Use '-D help' for a description of the options, or see find(1)

Please see also the documentation at https://www.gnu.org/software/findutils/.
You can report (and track progress on fixing) bugs in the "find"
program via the GNU findutils bug-reporting page at
https://savannah.gnu.org/bugs/?group=findutils or, if
you have no web access, by sending email to <bug-findutils@gnu.org>.
```

Apparently 'find' works using a predicate-like system, where you can specify multiple criteria to match on.  
Since we know the name of the file, we can use '-name'. It also looks like it runs on the cwd by default,
therefore I can just use something like `find -name cup.txt` to get the path of the file.
Then assuming at least one such file exists, I can just pipe it into cat. However, piping something into cat,
just leads to it being printed. So the following commands, prints whatever was passed in to cat's stdin.

```sh
$ find -name cup.txt | cat
./maze/left/right/8/cup.txt
```

This isn't that useful. So instead, I can use xargs, which turns stdin into arguments for the command passed into it.
Thus we get something like:

```sh
$ find -name cup.txt | xargs cat
you_just_found_the_triwizard_cup
```

and out comes our solution.

*PS: Why so many references?*

## byte5
After logging in, I first run 'la' and see that there is a C file in the byte5's home directory.
I tried compiling it(while thinking that there is no chance it will work, because I assume others have also done this exercise, and thus an executable would already be here, if it was that easy) and sure enough,
I get a permission error. I read the PDF and apparently /tmp/ has proper permissions for this. Thus I can just compile and run the C file there.
After running I am given a usage error that request my SDI. I rerun, passing in my SDI(which in this case is omitted for obvious reasons):

```sh
$ la # list all files
.bash_logout  .bashrc  .profile  byte5.c
$ gcc -o byte5 byte5.c # try to compile in cwd and fail spectacularly
/usr/bin/ld: cannot open output file byte5: Permission denied
collect2: error: ld returned 1 exit status
$ mkdir /tmp/joemama # make a new directory under /tmp/
$ gcc -o /tmp/joemama/byte5 byte5.c
$ /tmp/joemama/byte5 # run the program I just compiled
Usage: /tmp/joemama/byte5 <SDI>
$ /tmp/joemama/byte5 <sdi-not-written-because-at-some-point-this-may-be-public> # rerun with proper arguments
Here is your key: <not-written-for-the-same-reason>
```

I was quite curious as to what this program was doing, so I also 'cat'-ed the byte5.c file.
Turns out I was lucky I passed sdiNNNNNNN instead of just NNNNNNN because otherwise the program would just exit with failure.
There is also a check that there is an active ssh client in the current shell, which of course I am using otherwise I couldn't have connected.
Finally, the result I was given is actually of the format:
sdiNNNNNNN\_epoch_\epoch * (NNNNNNN + 4)\_ip\_myport\_serverport
where 
* sdiNNNNNNN is the argument provided 
* NNNNNNN is the numerican part of the argument provided, since that's how 'atoi' works
* ip is the IPV4 address of the computer I am connecting to the server with
* myport is the port I connected with(this one I am not that certain about but it seems to be the case)
* serverport is the default 22 SSH port

The last 3 parts of the answer are given by the 'SSH\_CLIENT' environment variable, but with '.' and ' ' replaced by _

## byte6
There are 2 ways of solving this problem.
One way(probably the intended one) is to use the 'unzip' command as advised in the PDF.
However assuming the same problem as before, the unzip command cannot possibly work in the cwd.
Therefore I tried to use it on the /tmp/joemama directory I created before.

```sh
$ mkdir -p /tmp/joemama/ # just to make sure the server didn't restart while I was gone which would've emptied the tmp directory.
$ unzip byte6.zip -d /tmp/joemama # -d to specify the output directory, otherwise cwd is used
Archive:  byte6.zip
error:  cannot create /tmp/joemama/byte6.txt
        Permission denied
```
Well in that case, I can try something else.

```sh
$ unzip --help
  Default action is to extract files in list, except those in xlist, to exdir;
  file[.zip] may be a wildcard.  -Z => ZipInfo mode ("unzip -Z" for usage).

  -p  extract files to pipe, no messages     -l  list files (short format)
  -f  freshen existing files, create none    -t  test compressed archive data
  -u  update files, create if necessary      -z  display archive comment only
  -v  list verbosely/show version info       -T  timestamp archive to latest
  -x  exclude files that follow (in xlist)   -d  extract files into exdir
modifiers:
  -n  never overwrite existing files         -q  quiet mode (-qq => quieter)
  -o  overwrite files WITHOUT prompting      -a  auto-convert any text files
  -j  junk paths (do not make directories)   -aa treat ALL files as text
  -U  use escapes for all non-ASCII Unicode  -UU ignore any Unicode fields
  -C  match filenames case-insensitively     -L  make (some) names lowercase
  -X  restore UID/GID info                   -V  retain VMS version numbers
  -K  keep setuid/setgid/tacky permissions   -M  pipe through "more" pager
  -O CHARSET  specify a character encoding for DOS, Windows and OS/2 archives
  -I CHARSET  specify a character encoding for UNIX and other archives
```

Seems like the -p option is perfect because it will just show the contents of the file on stdout.

```sh
$ unzip -p byte6.zip
unzipping_was_never_so_easy
```

Well, it could be easier.

As for the second solution: did you know that the newer versions of vim have built-in zip integration?

```sh
$ vim byte6.zip
```

just opens a netrw explorer inside the zip file from which one can just press Enter to instantly open the
compressed byte6.txt file and view(but not overwrite) its contents ;).

## byte7
Following the same logic as I did for byte6, I needed to extract the contents of a tar file to stdout.
Even though I use tars quite a lot I have never needed to do this before, so I had to search up the available options with 'man':


```sh
$ man tar
```

shows that the -O option extracts contents to stdout which is exactly the same as 'unzip''s -p option.
With previous tar knowledge I can create the command.
I need to e**x**tract to std**O**ut the contents of a g**z**ipped **f**ile called byte7.tar.gz.

```sh
$ tar xOzf byte7.tar.gz
tar_jokes_dont_stick
```

and this way we get out answer.


*PS: the vim solution from above also works here with `vim byte7.tar.gz`*

## byte8
Re-trying the command given by the PDF gives the expected result:

```sh
$ cat carriage_return.txt
There is absolutely nothing to see here. Move along.
```

if we open the file with vim(as advised by the PDF) however, things are different.

```sh
$ vim carriage_return.txt
# inside the vim window
no_more_secrets_from_you                                        ^MThere is absolutely nothing to see here. Move along.
```

the character ^M is actually a vim control sequence for \r. Thus we can see that what was actually happening,
is that cat was printing the file, including the carriage return, which of course leads to the first part of the file being overwritten by the much larger second part.

Alternatively, we can use the `strings` command to print ASCII string sequences from within the file:

```sh
$ strings carriage_return.txt
 no_more_secrets_from_you
There is absolutely nothing to see here. Move along.
```

*PS: how do I exit??? I'm stuck*

## byte9
After logging in and running 'ls' I see the following output:

```sh
$ ls
-
```

This means that in the current folder there exists a directory or file that has the name '-'.
To find it's nature, I use the 'file' command:

```sh
$ file ./-
./-: ASCII text
```

Note that I had to use ./- instead of just -. That is needed because otherwise '-' refers to the stdin pipe in the terminal.
That means a command like `-` would just hang and wait for input and then give this weird output:

```sh
$ file -
-
/dev/stdin: ASCII text
$ file -
./-
/dev/stdin: ASCII text
$ file -
a
/dev/stdin: ASCII text
```
To combat this we can just refer to the file with it's relative path.  

Anyways, now we know the file is ASCII text, which means we can cat it(again keeping in mind we need to refer to the file with a relative path to avoid - being turned into the stdin pipe):

```sh
$ cat ./-
filepaths_can_be_useful
```

Alternatively, we can use the redirect symbol. Since < is not actually a command but a terminal builtin, using - on it doesn't make it hang(at least that's my interpretation of it):

```sh
$ cat < -
filepaths_can_be_useful
```

This gives me flashbacks to when I made the mistake of creating a folder called ~ in my home directory.
By mistake I tried `rm ~ -r`. By the time I realised what I had done, it was already too late. From that point on,  
I aliased rm to `gio trash` which moves stuff to a 'Trash' folder which I can restore the files from in a worst case scenario.

## byte10
I log in and run 'la' to see all files in the home directory.

```sh
$ la
.bash_logout  .bashrc  .profile  i_wonder_what_this_does  names.txt
```

It seems we care about the 'names.txt' file. However there also seems to be an easter egg in here. Let's leave that for later.  

### re:byte10
We need to sort alphabetically and find the 10th name in the sorted file. For that we can use 'sort' with a combination of 'head' and 'tail':

```sh
$ sort names.txt | head -n 10 | tail -n 1
Adorne
```

and just like that we get our answer.
A bit of an explanation:

```sh
$ sort names.txt
```

sorts the lines of the file alphabetically and spews the result into stdout.


```sh
$ head -n 10 <file>
```

returns the first 10 lines of a file(NOTE: that is the default behavior of head, but I like specifying it either way because I can never remember it).
Using '|' turns the stdout of the previous command into the stdin of the new command. So head it just passed the sorted output as an input.

```sh
$ tail -n 1 <file>
```

returns the last line of a file. Again using '|' turns the stdout of head into the input for tail. This way we get the last name in the first 10 alphabetically sorted names aka the 10th name alphabetically.

### i_wonder_what_this_does

```sh
$ file i_wonder_what_this_does # let's see what this easter egg is
i_wonder_what_this_does: symbolic link to /usr/games/ninvaders
```

ninvaders? Alien invaders clone?
After launching I spent enough time trying to win that I even found a cheat code.
If you press capital H while playing, you can just add lives to yourself.
