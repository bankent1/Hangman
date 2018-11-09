# Hangman
** WORK IN PROGRESS **

Allows the user to play a game of hangman against a computer AI. The AI uses 
stats built from LetterPairFreq.cpp, which finds the frequency of letter pairs,
to decide which letter to guess.

The ai struggles with guessing the final letter in the word as the model only
gives support for reading left to right. An additional model is needed to 
correct this issue.
