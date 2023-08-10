#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class State {
	public:
	int xLoc; //aka col
	int yLoc; //aka row
	State() {}
	State(int x, int y) {
		xLoc = x;
		yLoc = y;
	}
};

//global variables
double maxError;
vector<State> enviro; 				//set of states
vector<char> actions{ 'U', 'R', 'D', 'L' };	//set of actions
vector<char> policy{ '@', '@', '@', '@',	//saves best action for each non-terminal state
                     '@', 'X', '@', 'T',
                     '@', '@', '@', 'T' } ;    

vector<vector<vector<double>>> tMatrix = {{{0.1, 0.1, 0.,  0.,  0.8, 0.,  0.,  0.,  0.,  0.,  0.},
  {0.1, 0.8, 0.1, 0.,  0.,  0.,  0.,  0.,  0.,  0.,  0. },
  {0.,  0.1, 0.,  0.1, 0.,  0.8, 0.,  0.,  0.,  0.,  0. },
  {0.,  0.,  0.1, 0.1, 0.,  0.,  0.8, 0.,  0.,  0.,  0. },
  {0.,  0.,  0.,  0.,  0.2, 0.,  0.,  0.8, 0.,  0.,  0. },
  {0.,  0.,  0.,  0.,  0.,  0.1, 0.1, 0.,  0.,  0.8, 0. },
  {0.,  0.,  0.,  0.,  0.,  0.1, 0.1, 0.,  0.,  0.,  0.8},
  {0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.9, 0.1, 0.,  0. },
  {0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.1, 0.8, 0.1, 0. },
  {0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.1, 0.8, 0.1},
  {0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.1, 0.9}},

 {{0.1, 0.8, 0.,  0.,  0.1, 0.,  0.,  0.,  0.,  0.,  0. },
  {0.,  0.2, 0.8, 0.,  0.,  0.,  0.,  0.,  0.,  0.,  0. },
  {0.,  0.,  0.1, 0.8, 0.,  0.1, 0.,  0.,  0.,  0.,  0. },
  {0.,  0.,  0.,  0.9, 0.,  0.,  0.1, 0.,  0.,  0.,  0. },
  {0.1, 0.,  0.,  0.,  0.8, 0.,  0.,  0.1, 0.,  0.,  0. },
  {0.,  0.,  0.1, 0.,  0.,  0.,  0.8, 0.,  0.,  0.1, 0. },
  {0.,  0.,  0.,  0.1, 0.,  0.,  0.8, 0.,  0.,  0.,  0.1},
  {0.,  0.,  0.,  0.,  0.1, 0.,  0.,  0.1, 0.8, 0.,  0. },
  {0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.2, 0.8, 0. },
  {0.,  0.,  0.,  0.,  0.,  0.1, 0.,  0.,  0.,  0.1, 0.8},
  {0.,  0.,  0.,  0.,  0.,  0.,  0.1, 0.,  0.,  0.,  0.9}},
  
 {{0.9, 0.1, 0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0. },
  {0.1, 0.8, 0.1, 0.,  0.,  0.,  0.,  0.,  0.,  0.,  0. },
  {0.,  0.1, 0.8, 0.1, 0.,  0.,  0.,  0.,  0.,  0.,  0. },
  {0.,  0.,  0.1, 0.9, 0.,  0.,  0.,  0.,  0.,  0.,  0. },
  {0.8, 0.,  0.,  0.,  0.2, 0.,  0.,  0.,  0.,  0.,  0. },
  {0.,  0.,  0.8, 0.,  0.,  0.1, 0.1, 0.,  0.,  0.,  0. },
  {0.,  0.,  0.,  0.8, 0.,  0.1, 0.1, 0.,  0.,  0.,  0. },
  {0.,  0.,  0.,  0.,  0.8, 0.,  0.,  0.1, 0.1, 0.,  0. },
  {0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.1, 0.8, 0.1, 0. },
  {0.,  0.,  0.,  0.,  0.,  0.8, 0.,  0.,  0.1, 0.,  0.1},
  {0.,  0.,  0.,  0.,  0.,  0.,  0.8, 0.,  0.,  0.1, 0.1}},

 {{0.9, 0.,  0.,  0.,  0.1, 0.,  0.,  0.,  0.,  0.,  0. },
  {0.8, 0.2, 0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.,  0. },
  {0.,  0.8, 0.1, 0.,  0.,  0.1, 0.,  0.,  0.,  0.,  0. },
  {0.,  0.,  0.8, 0.1, 0.,  0.,  0.1, 0.,  0.,  0.,  0. },
  {0.1, 0.,  0.,  0.,  0.8, 0.,  0.,  0.1, 0.,  0.,  0. },
  {0.,  0.,  0.1, 0.,  0.,  0.8, 0.,  0.,  0.,  0.1, 0. },
  {0.,  0.,  0.,  0.1, 0.,  0.8, 0.,  0.,  0.,  0.,  0.1},
  {0.,  0.,  0.,  0.,  0.1, 0.,  0.,  0.9, 0.,  0.,  0. },
  {0.,  0.,  0.,  0.,  0.,  0.,  0.,  0.8, 0.2, 0.,  0. },
  {0.,  0.,  0.,  0.,  0.,  0.1, 0.,  0.,  0.8, 0.1, 0. },
  {0.,  0.,  0.,  0.,  0.,  0.,  0.1, 0.,  0.,  0.8, 0.1}}};



//Calculate max ultility action for each state
double maxCalc(int stateNum, vector<double> uCopy) {	
	double maxVal = 0.0;
	double rowTotal = 0.0;
	char actionDir;

	for(int i = 0; i < tMatrix.size(); i++) { 				//look through each action array
		for(int j = 0; j < tMatrix[i][stateNum].size(); j++) {			//look through corresponding state row 
			rowTotal = rowTotal + (tMatrix[i][stateNum][j] * uCopy[j]);
		}
		if(i == 0) {				//1st action initially set to best
			maxVal = rowTotal;
			actionDir = actions[i];
		}
		if(rowTotal > maxVal) {			//check for new maximum 
			maxVal = rowTotal;
			actionDir = actions[i];
		}
		rowTotal = 0.0;
	}	
	
	if(stateNum > 4){				//also record best action for the state
		policy[stateNum + 1] = actionDir; //account for (2,2) 'X' in policy
	}
	else{
		policy[stateNum] = actionDir; //otherwise record normally
	}

	return maxVal;
}


//Environment creator function
void makeEnviro() {
	int numCols = 4;
	int numRows = 3;
	State tmp;
	for(int i = 1; i <= numRows; i++) {	//push in row major order (1,1), (1,2), (1,3)...
		for(int j = 1; j <= numCols; j++) {
			if( !(i == 2 && j == 2) ) {	//don't include (2,2) block
				tmp.xLoc = j;
				tmp.yLoc = i;
				enviro.push_back(tmp);	//terminal states at [6] and [10]
			}
			else{
			}
		}
	}

}

//Value iteration function
vector<double> valueIteration(vector<State> states, vector<char> actions, vector<vector<vector<double>>> matrix, vector<double> rewards, double discount) {
	vector<double> u{ 0.0, 0.0, 0.0, 0.0,		//holds previous/prior utilities for states
			  0.0,      0.0,-1.0,
			  0.0, 0.0, 0.0, 1.0 };		//+/-1 terminal state utilities ([6] and [10]) NEVER change!
	
	vector<double> uPrime{ 0.0, 0.0, 0.0, 0.0,	//holds updated utilities for states
                               0.0,      0.0,-1.0,
                               0.0, 0.0, 0.0, 1.0 };	//+/-1 terminal state utilities ([6] and [10]) NEVER change!


	
	double termVal = (maxError * (1 - discount)) / discount;	//e(1 - r) / r
	double maxDelta = 100.0; 	//initially set to arbitrary value to enter while loop 
	double maxAction;
	double newUtility;
	double delta;
	while(maxDelta >= termVal) {		
		u = uPrime;		//update u
		maxDelta = 0.0;
		for(int i = 0; i < states.size(); i++) {	//loop through each state
			
			if((i == 6) || (i == 10)) { 		//do not change terminal utilities
			}
			else {					//for non-terminal states
				maxAction = maxCalc(i,u);
				newUtility = rewards[i] + (discount * maxAction);	//U'[s] = R(s) + r * max
				uPrime[i] = newUtility;
			}
			delta = abs(uPrime[i] - u[i]);		
			if( delta > maxDelta ) maxDelta = delta;	

		}
	}

	return u;
}

int main() {

	vector<double> stateRewards{ 0.0, 0.0, 0.0, 0.0,  //set of rewards
				     0.0,      0.0, -1.0,	  //grid shown is upside down
			             0.0, 0.0, 0.0,  1.0 }; //to be in row-major order
	double discFactor;
	double rewardVal;
	vector<double> finalU;

		
	//User input section
	cout << "Enter a discount value:" << endl;
	cin >> discFactor;

	cout << "Enter a reward value:" << endl;
	cin >> rewardVal;

	cout << "Enter a max error value:" << endl;
	cin >> maxError;

	for(int i = 0; i < stateRewards.size(); i++) {		//fill non-terminal states with rewardVal
		if(i == 6) stateRewards[i] = -1.0;
		else if (i == 10) stateRewards[i] = 1.0;
		else stateRewards[i] = rewardVal;
	}

	//Create environment and execture value iteration
	makeEnviro();
	finalU = valueIteration(enviro, actions, tMatrix, stateRewards, discFactor);

	//Display parameters and final utilities
	cout << "\nUtilities: " << endl;
	for(int i = 0; i < finalU.size(); i++) {
		cout << finalU[i] << endl;
	}
	
	//Display policy 
	int shift = 8;
	cout << "\nPolicy: " << endl;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 4; j++) {
			cout << '[' << policy[shift+j] << "] ";
		}
		cout << endl;
		shift = shift - 4;
	}

	return 0;
}
