#pragma once
#include <vector>
class Guess
{
private:

	int m_Bulls = 0;
	int m_Cows = 0;
	std::vector<int> m_Guess;

public:
	Guess(std::vector<int> guess,int bulls , int cows ) {
		m_Guess = guess;
		m_Bulls = bulls;
		m_Cows = cows;

	}

    int getBulls() const { return m_Bulls; }
	int getCows() const { return m_Cows; }
	std::vector<int> getGuess() const { return m_Guess; }

};

