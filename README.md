# Planar Copperlist Compiler #

(C) 2022 - Lorenzo Di Gaetano

This is a side project of Planar Framework

https://github.com/coppersoft/planar

### What is this? ###

This is a tool that helps Amiga C graphics programming when dealing with copperlists.

Amiga's Copperlist in C are usually built with a huge UWORD static array, at the moment Planar framework handles it in this way, in conjuntion with some macros. This is easy but there is a major problem: in arrays you don't have the chance to put labels. When you have to modify copperlist's values in your code you have to count manually every offsets of every register you want to modify.

This can become daunting when dealing with long and complex copperlists, especially when you have to add or remove instructions, because this lead to a totale recalc of all offsets.

Now you can define a copperlist in a special text file. This tool will take this file, compile in a binary file that you can easily load in chip RAM and will also output a text file with the offsets of all the labels you defined, freeing you from the hassle.

## Copperlist syntax ##

Copperlist files must follow a simple but powerful syntax. Actually you can define 3 instructions: MOVE, WAIT and WAIT_END.

#### MOVE ####

You can add a Copper MOVE instruction with:

```
MOVE(<REGISTER_NAME>,VALUE)
```

Where REGISTER_NAME is the actual Amiga OCS/AGA register as defined in the Amiga Hardware Manual, you can find a list of Amiga Hardware Registers here:

http://amiga-dev.wikidot.com/information:hardware

You can separate instructions with a comma

```
MOVE(<REGISTER_NAME>,VALUE),MOVE(<REGISTER_NAME>,VALUE)
```

Values MUST be in the 0x0000 hexadecimal format.

#### WAIT ####

You can add a Copper WAIT instruction with

```
WAIT(VALUE)
```

#### WAIT_END ####

As usual, at the and of the coppertlist you must add a WAIT_END instruction:

```
WAIT_END
```

that is equivalent to a
```
WAIT(0xffff)
```

but this is something you surely already know! ;-)

#### LABELS ####

The key feature of this tool is the ability to add labels 