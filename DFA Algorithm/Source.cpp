#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class DFAMachine
{
public:
	vector<string> states;
	string alphabets;
private:
	vector<string> acceptStates;
	map<string, int> statesMap;
	map<char, int> alphabetsMap;
	map<string, bool> isAcceptMap;
	string startState;
	vector<vector<string>> transitions;
	int startStateIndex;

public:
	void setTransitions(vector<string> goingStates)
	{
		transitions.push_back(goingStates);
	}

	void displayMachine()
	{
		cout << "-> States : {";
		for (int i = 0; i < states.size(); i++)
		{
			cout << states[i];
			if (i != states.size() - 1)
				cout << ", ";
		}
		cout << "}\n\n";

		cout << "-> Alphabet : {";
		for (int i = 0; i < alphabets.size(); i++)
		{
			cout << alphabets[i];
			if (i != alphabets.size() - 1)
				cout << ", ";
		}
		cout << "}\n\n";

		cout << "-> transition function : \n (with";
		for (int i = 0; i < alphabets.size(); i++)
		{
			cout << " " << alphabets[i];
		}
		cout << " respectively) : \n";
		for (int i = 0; i < transitions.size(); i++)
		{
			cout << "- " << states[i] << " : \t";
			for (int j = 0; j < transitions[i].size(); j++)
			{
				if (transitions[i][j] == "T")
					cout << "Phai\t";
				else
					cout << transitions[i][j] << "\t";
			}
			cout << endl;
		}

		cout << "\n-> Start state : " << startState << "\n";

		cout << "\n-> Accept states : {";
		for (int i = 0; i < acceptStates.size(); i++)
		{

			cout << acceptStates[i];
			if (i != acceptStates.size() - 1)
				cout << ", ";
		}
		cout << "}\n\n";
	}


	void setMapStatesAndAlphabets()
	{
		for (int i = 0; i < states.size(); i++)
		{
			statesMap[states[i]] = i;
		}

		for (int i = 0; i < alphabets.size(); i++)
		{
			alphabetsMap[alphabets[i]] = i;
		}
	}

	void setStartState(string startState)
	{
		this->startStateIndex = statesMap[startState];
		this->startState = startState;
	}

	void setAcceptStates(vector<string> acceptStates)
	{
		this->acceptStates = acceptStates;
		for (int i = 0; i < this->acceptStates.size(); i++)
		{
			isAcceptMap[this->acceptStates[i]] = true;
		}
	}

	bool isAccept(string word)
	{
		int nextStateIndex = startStateIndex;
		string nextState;
		for (int i = 0; i < word.size(); i++)
		{
			int indexOfThisAlphabet = alphabetsMap[word[i]];
			nextState = transitions[nextStateIndex][indexOfThisAlphabet];
			if (nextState == "T")
				return false;
			nextStateIndex = statesMap[nextState];
		}

		if (isAcceptMap[nextState]) return true;
		else return false;
	}
};

int main()
{
	cout << "******************\n";
	cout << "*DFA generic code*\n";
	cout << "******************\n";
	DFAMachine myMachine;

	//entering the states
	int numberOfStates;
	cout << "-> please enter the number of states : ";
	cin >> numberOfStates;
	cin.ignore();
	cout << "-----------------------------------\n";
	vector<string> states(numberOfStates);
	for (int i = 0; i < numberOfStates; i++)
	{
		cout << "   - please enter the name of state number " << i + 1 << " : ";
		getline(cin, states[i]);
	}
	myMachine.states = states;
	cout << "\n\n*******************************************************************************\n";
	//entering the alphabets
	string alphabets;
	cout << "->please enter the alphabet as a one word(one string) : ";
	getline(cin, alphabets);
	myMachine.alphabets = alphabets;
	cout << "\n\n*******************************************************************************\n";
	//setting the map of the states and alphabets
	myMachine.setMapStatesAndAlphabets();
	//entering the transition function
	string goingState;
	vector<string> goingStates;
	cout << "-> enter the transitions (enter only state name)\n";
	cout << "------------------------------------------------\n";
	for (int i = 0; i < states.size(); i++)
	{
		cout << "   - From state " << states[i] << " : \n";
		for (int j = 0; j < alphabets.size(); j++)
		{
			cout << "   \t\t.on \"" << alphabets[j] << "\" (if there is none enter \"T\") : ";
			getline(cin, goingState);
			goingStates.push_back(goingState);
		}
		myMachine.setTransitions(goingStates);
		goingStates.clear();
	}
	cout << "\n\n*******************************************************************************\n";
	//entering the start state
	string startState;
	cout << "please enter the start state : ";
	cin >> startState;
	myMachine.setStartState(startState);
	cout << "\n\n*******************************************************************************\n";
	//entering the accept states
	int numberOfAcceptStates;
	cout << "please enter the number of accept states : ";
	cin >> numberOfAcceptStates;
	cout << "-------------------------------------------\n";
	cin.ignore();
	vector<string> acceptStates(numberOfAcceptStates);
	for (int i = 0; i < numberOfAcceptStates; i++)
	{
		cout << "-> enter accept state number " << i + 1 << " : ";
		getline(cin, acceptStates[i]);
	}
	myMachine.setAcceptStates(acceptStates);
	cout << "\n\n***********************************************************************************************\n";
	myMachine.displayMachine();
	cout << "***********************************************************************************************\n\n";

	cout << "->enter numbers of tries (entering words and see if it's accepted or not) : ";
	int tries;
	cin >> tries;
	cout << endl;
	while (tries--)
	{
		string word;
		cout << "* enter the word : ";
		cin >> word;
		if (myMachine.isAccept(word))
			cout << "ACCEPTED" << endl;
		else
			cout << "NOT ACCEPTED" << endl;
	}

	return 0;
}
