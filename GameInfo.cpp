#include "GameInfo.h"


bool GameInfo::isConsistent(const std::vector<int>& newGuess) const
{
	bool isConsistentBulls = true;
	bool isConsistentCows = true;

	for (const Guess& g : m_PastGuesses)
	{
		isConsistentBulls = checkBulls(g,newGuess);

		isConsistentCows = checkCows(g, newGuess);

		if (!isConsistentBulls || !isConsistentCows) {
			break;
		}
	}

	return isConsistentBulls && isConsistentCows;

}

void GameInfo::generateSecret()
{

	while (m_Secret.size() < n) {

		// generate a random number up to k

		int digit = 1 + std::rand() % k;

		// checking if the digits already exists inside the secret, if its not we are adding it.

		bool exists = false;

		for (int i : m_Secret) {

			if (i == digit) {
				exists = true;
				break;
			}
		}

		if (!exists) {
			m_Secret.push_back(digit);
		}

	}
	std::srand(std::time(nullptr));
}


bool GameInfo::generateNewGuessBacktrack(std::vector<int>& guess)
{
	if (guess.size() == n)
		return isConsistent(guess);

	for (int digit = 1; digit <= k; ++digit)
	{

		bool duplicate = false;
		for (int i = 0; i < guess.size(); ++i)
		{
			if (guess[i] == digit)
			{
				duplicate = true;
				break;
			}
		}

		if (duplicate)
			continue; 

		guess.push_back(digit);

		if (generateNewGuessBacktrack(guess)) {
			return true;
		}

		guess.pop_back();
	}
	return false;

}


std::vector<int> GameInfo::generateNewGuess()
{
	std::vector<int> guess; // start empty

	if (!generateNewGuessBacktrack(guess))
		throw std::runtime_error("No consistent guess possible!");

	return guess;
}



bool GameInfo::checkBulls(const Guess& g, const std::vector<int>& newGuess) const
{
	int count = 0;
	for (int i = 0; i < g.getGuess().size(); ++i)
	{
		if (g.getGuess()[i] == newGuess[i])
			++count;
	}

	return count == g.getBulls();
}


bool GameInfo::checkCows(const Guess& g, const std::vector<int>& newGuess) const
{
	int count = 0;

	for (int i = 0; i < newGuess.size(); ++i)
	{
		for (int j = 0; j < g.getGuess().size(); ++j)
		{
			if (i != j && newGuess[i] == g.getGuess()[j])
			{
				++count;
			}
		}
	}

	return count == g.getCows();

}

GameInfo::GameInfo(int numberOfGuesses,int numbersRange)
{
	m_WinCon = false;
	n = numberOfGuesses;
	k = numbersRange;
	generateSecret();
}

bool GameInfo::validateGuess(std::vector<int>& newGuess)
{
	if (!isConsistent(newGuess)) {
		std::cout << "guess invalid \n";
		return false;
	}

	int bulls = 0;
	int cows = 0;

	for (int i = 0; i < n; ++i)
	{
		if (newGuess[i] == m_Secret[i])
		{
			++bulls;
		}
		else
		{
			for (int j = 0; j < n; ++j)
			{
				if (i != j && newGuess[i] == m_Secret[j])
				{
					++cows;
					break;
				}
			}
		}
	}
	if (bulls == n) {
		m_WinCon = true;
	}
	Guess g(newGuess, bulls, cows);
	m_PastGuesses.push_back(g);
	printGuess(g);
	return true;  // guess is valid and stored
}

void GameInfo::printSecret() const
{
	printVector(m_Secret);
}


void GameInfo::printGuess(const Guess& g) const {  
printVector(g.getGuess());  
std::cout << "| Bulls: " << g.getBulls() << ", Cows: " << g.getCows() << "\n\n";  
}  

void GameInfo::printVector(const std::vector<int>& vec) const {  
for (int d : vec)  
	std::cout << d << " ";  
std::cout << "\n";  
}





