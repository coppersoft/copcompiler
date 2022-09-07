# Planar Copperlist Compiler #

(C) 2022 - Lorenzo Di Gaetano

This is a side project of Planar Framework

https://github.com/coppersoft/planar

### What is this? ###

This is a tool that helps Amiga C graphics programming when dealing with copperlists.

Amiga's Copperlist in C are usually made with a huge UWORD static array, actually Planar engine uses it in conjuntion with some macros. This is easy but have a major problem: in arrays you don't have the chance to put labels. When you have to modify copperlist in your code you have to count manually the index of copperlist's array.

This can be often become daunting when dealing with long and complex copperlists. 