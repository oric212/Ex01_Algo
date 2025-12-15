#pragma once
#include "Guess.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <functional>
#include <stdexcept>

class GameInfo
{
private:
	// class members

	int n;
	int k;
	bool m_WinCon;
	std::vector<Guess> m_PastGuesses;
	std::vector<int> m_Secret;

	// private functions

	bool checkBulls(const Guess& g, const std::vector<int>& newGuess) const;
	bool checkCows(const Guess& g, const std::vector<int>& newGuess) const;
	bool isConsistent(const std::vector<int>& newGuess) const;
	void printGuess(const Guess& g) const;
	void printVector(const std::vector<int>& vec) const;
	bool generateNewGuessBacktrack(std::vector<int>& guess);
	


public:
	GameInfo(int numberOfGuesses,int numbersRange);
	bool validateGuess(std::vector<int>& newGuess);
	void generateSecret();
	std::vector<int> generateNewGuess();
	void printSecret() const;
	bool getWinCon() const {return m_WinCon;}
};

