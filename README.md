# PortfolioProject
Tyler Riggins' Portfolio Project for the CS201 course at the University of Alabama: Scrabble.

Inspiration for object oriented design was taken from https://www.codementor.io/michaelsafyan/object-oriented-programming-in-c-du1081gw2
Binary Search tree used in implementation of dictionary was modified from the solution found at https://www.geeksforgeeks.org/sorted-array-to-balanced-bst/.
Dictionary file represents all the words in the collins scrabble dictionary https://www.collinsdictionary.com/scrabble/scrabble-word-finder/

Interesting Pieces of Code:
cell.c line#62: Procedurally determining what type a cell on a gameboard of arbitrary size should be
dictionary.c: Given a sorted array of words creates a balance binary search tree
main.c line# 173-229: Managing Cell selections and viewframe movements
word.c line# 74-273: Checks a word formed by a set of tiles played and also any other words those tiles might be adjacent to
