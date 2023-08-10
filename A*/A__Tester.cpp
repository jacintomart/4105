#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <queue>
#include <cmath>
#include <vector>
using namespace std;


class Node {
	public:
        int rowLoc;		//store node's coordinates
        int colLoc;
	int parentRow;		//store node's parent's coordinates
	int parentCol;
	int stepVal;
	double eucVal;		
        double fVal;		//f(n) = path cost + euclidean distance to goal
	int pathVal;
	Node() {}
        Node(int y, int x) {
        	rowLoc = y;
                colLoc = x;
        }

	void fSet() {fVal = pathVal + eucVal;}
};

bool operator== (const Node& n1, const Node& n2) {				//operators for comparing nodes
                return( (n1.rowLoc == n2.rowLoc) && (n1.colLoc == n2.colLoc) );
                }

bool operator!= (const Node& n1, const Node& n2) {
		return( (n1.rowLoc != n2.rowLoc) || (n1.colLoc != n2.colLoc) );
		}

bool operator<(const Node& n1, const Node& n2) {	//priority queue operator based on lowest f(n) 
                return n1.fVal > n2.fVal;
                }

Node existingNode;	//global node object

double eucCalc(int nodeRow, int nodeCol, const Node& goal) {	//euclidean distance calculation function
	int xDiff = nodeCol - goal.colLoc;
	int yDiff = nodeRow - goal.rowLoc;
	double hypot = sqrt( (xDiff*xDiff) + (yDiff*yDiff) );
	return hypot;
}

bool findNode(Node n, vector<Node>& list) {	//searches for particular node in vector
	bool found = false;
	for(int i = 0; i < list.size(); i++) {
		if(n == list.at(i)) {
			found = true;
			existingNode = list.at(i);
			break;
		}
	}
	return found;
}

void removeNode(Node existing, vector<Node>& list) {	//removes particular node in vector
	for(int i = 0; i < list.size(); i++) {
		if(existing == list.at(i)) {
			list.erase(list.begin() + i);
			break;
		}
	}
}

Node gridFind(int row, int col, vector<Node> closed) {	//locates particular node within grid
	Node match;
	for(int i = 0; i < closed.size(); i++) {
		if( (row == closed.at(i).rowLoc) && (col == closed.at(i).colLoc) ){
			match = closed.at(i);	
		}
	}
	return match;
}



int main () {
	
	ifstream inputFile;
	string line;
	vector<string> grid;
	vector<Node> closedList;
	Node currNode;
	priority_queue<Node> openList;
	vector<Node> openCopy;		//copy of openList for searching operations
	int expCount = 1;	//number of expanded nodes
	int startRow;	//start and goal node coordinates
	int startCol;
	int goalRow;
	int goalCol;
	vector<Node> children;
	Node nodeB;	//child to right of current node
	Node nodeC;	//child above current node
	Node nodeD;	//child to left of current node
	Node nodeE; 	//child below current node
	double distance;	//euclidean distance to goal node
	Node parent;
	int oldPath;	//existing known path cost to certain node
	int newPath;	//newly discovered path cost to certain node
	int stepCost;
	int pathCost = 0;
	vector<Node> path;
	ofstream outputFile;

//read grid from grid.txt and save as vector of strings (aka rows)
	inputFile.open("grid.txt");
	while(getline(inputFile, line)) {
		grid.push_back(line);
	}
	inputFile.close();


// first iteration to start search process
	cout << "Enter the row of the start point:" << endl;
	cin >> startRow;
	cout << "Enter the column of the start point:" << endl;
	cin >> startCol;
	
	cout << "Enter the row of the goal point:" << endl;
        cin >> goalRow;
        cout << "Enter the column of the goal point:" << endl;
        cin >> goalCol;

	Node startNode(startRow, startCol);
	Node goalNode(goalRow, goalCol);

	openList.push(startNode);	
	openCopy.push_back(startNode);	//openCopy copies openList's actions
	

// big while loop begins here
	while(currNode != goalNode) { 

		if(openList.empty() == true) break;	//stop if no more available nodes
		currNode = openList.top();	//current node set to lowest f(n) value node
		openList.pop();
		removeNode(currNode, openCopy);		//remove popped node

		if(currNode == goalNode) break;		//stop search if goal node found
		closedList.push_back(currNode);
		expCount++;

		/*look around to create valid neighbor/children nodes
	  	if the statement is entered, then the index was valid*/
		if( (currNode.colLoc + 1) <= ((grid[0]).size() - 1) ) {	    	//look right

			stepCost = grid[currNode.rowLoc][(currNode.colLoc + 1)] - '0'; //convert char value to int
			if( stepCost != 0) {	//avoid 0's in grid
			
				nodeB.rowLoc = currNode.rowLoc;		//store right child coordinates
				nodeB.colLoc = currNode.colLoc + 1;
				nodeB.parentRow = currNode.rowLoc;	//store child's parent's coordinates
				nodeB.parentCol = currNode.colLoc;
				children.push_back(nodeB);
			}
		}

		if((currNode.rowLoc - 1) >= 0) {	//look up	

			stepCost = grid[(currNode.rowLoc - 1)][currNode.colLoc] - '0';
			if( stepCost != 0) {
			
				nodeC.rowLoc = currNode.rowLoc - 1;
				nodeC.colLoc = currNode.colLoc;
				nodeC.parentRow = currNode.rowLoc;
				nodeC.parentCol = currNode.colLoc;
				children.push_back(nodeC);
			}
		}

		if((currNode.colLoc - 1) >= 0) {	//look left	

			stepCost = grid[currNode.rowLoc][(currNode.colLoc - 1)] - '0';
			if( stepCost != 0) {
				
				nodeD.rowLoc = currNode.rowLoc;
				nodeD.colLoc = currNode.colLoc - 1;
				nodeD.parentRow = currNode.rowLoc;
				nodeD.parentCol = currNode.colLoc;
				children.push_back(nodeD);
			}
		}

		if( (currNode.rowLoc + 1) <= (grid.size() - 1) ) { 	//look down

			stepCost = grid[(currNode.rowLoc + 1)][currNode.colLoc] - '0';
			if( stepCost != 0) {
	
				nodeE.rowLoc = currNode.rowLoc + 1;
				nodeE.colLoc = currNode.colLoc;
				nodeE.parentRow = currNode.rowLoc;
				nodeE.parentCol = currNode.colLoc;
				children.push_back(nodeE);
			}
		}

		//loop for setting child Vals and doing big if statement
		for(int i = 0; i < children.size(); i++) {
		
			stepCost = grid[(children.at(i)).rowLoc][(children.at(i)).colLoc] - '0'; //set child's step cost
			(children.at(i)).stepVal = stepCost;
			
			distance = eucCalc( (children.at(i)).rowLoc, (children.at(i)).colLoc, goalNode ); //set child's euclidean
			(children.at(i)).eucVal = distance;
			
			parent = gridFind( (children.at(i)).parentRow, (children.at(i)).parentCol, closedList ); //go to parent
			if(parent != startNode) {
			     (children.at(i)).pathVal = parent.pathVal + (children.at(i)).stepVal; //set child's path cost
			}
			else{
				(children.at(i)).pathVal = (children.at(i)).stepVal;	//only for startNode's children
			}

			(children.at(i)).fSet();	//set child's f(n) value

			if(findNode(children.at(i), openCopy) == true) {	//aka openList.contains(child)
				newPath = children.at(i).pathVal;
				oldPath = existingNode.pathVal;

				if(newPath < oldPath) {				   //openList.remove in steps 1-3
			        	removeNode(existingNode, openCopy);	   //1) remove child from openCopy
					while(!openList.empty()) {		   //2) empty openList
						openList.pop();
					}
					for(int j = 0; j < openCopy.size(); j++) { //3) re-fill openList 
						openList.push(openCopy.at(j));	   //   with openCopy's content	
					}
				
					openList.push(children.at(i));		//openList.add(child)
					openCopy.push_back(children.at(i));
		
					if(findNode(children.at(i), closedList) == true) { //closedList.contains(child)
						removeNode(children.at(i), closedList);
					}	
				}
				
			}
			else if(findNode(children.at(i), closedList) == false) { //aka closedList.contains(child)

				openList.push(children.at(i));			//openList.add(child)
				openCopy.push_back(children.at(i));
		
			}
	
		}// end of for children loop

		children.clear();		//empty children vector for the next node

	}//end of big while loop

	pathCost = currNode.pathVal;	//solution path cost = goalNode's pathVal

	//follow goalNode's ancestors to stitch solution path together
	while(currNode!=startNode) {
		grid[currNode.rowLoc][currNode.colLoc] = '*';
		path.push_back(currNode);
		currNode = gridFind(currNode.parentRow, currNode.parentCol, closedList);
	}
	path.push_back(startNode);	//add startNode to solution path
	grid[startNode.rowLoc][startNode.colLoc] = '*';

	//write solution path grid to path.txt
	outputFile.open("path.txt");
	for(int i = 0; i < grid.size(); i++) {
		outputFile << grid.at(i) << endl;
	}
	outputFile.close();

	//output search results to console	
	cout << "----Final path----" << endl;
	for(int i = 0; i < path.size(); i++) {
		cout << "Row " << path.at(i).rowLoc << ", Col " << path.at(i).colLoc << endl;
	}
	cout << "Path cost: " << pathCost << endl;
	cout << "Total nodes expanded: " << expCount << endl;

	return 0;
}
