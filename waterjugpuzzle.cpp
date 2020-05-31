/*******************************************************************************
 * Name    : waterjugpuzzle.cpp
 * Author  : Marjan Chowdhury
 * Description : Solves the water jug puzzle given 3 capacities and goals using BFS.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c; // a b and c are the current volumes of water in each jug
    vector<string> directions; // for example "Pour 3 from A to B"
    
    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
    vector<string> get_directions(){
      return directions;
    }
};

//Checks to see if a pour from one jug to another can be made
bool can_pour(int from, int to, int capFrom, int capTo){
  if(to == capTo ){ // the jug you are trying to fill is full
    return false;
  }
  if(from == 0){ // the jug to pour from has no water
    return false;
  }else{
    return true;
  }
}

//function that pours water from one jug to another
//checks and does all 6 pours and returns a vector of states that come from each pour
//possible states made from pouring have their directions vector updated
vector<State> pour(State current, int capA, int capB, int capC){
  vector<State> result; //initialize vector holding resulting states
  // 1) Pour from C to A
  if (can_pour(current.c, current.a, capC, capA))
  {
    int poured, newA, newC;
    if (capA - current.a >= current.c){ // the case that we can fit all of c in the space left in a 
      newA = current.a + current.c;
      newC = 0;
      poured = current.c;
    }
    else{ // the case that we can fit some but not all of c in a
      newA = capA;
      newC = current.c - (capA - current.a);
      poured = capA - current.a;
    }
    State newstate(newA, current.b, newC);
    ostringstream oss;
    if(poured == 1){ 
      oss << "Pour " << poured << " gallon from C to A. " << newstate.to_string();
    }else{
      oss << "Pour " << poured << " gallons from C to A. " << newstate.to_string();
    }
    vector<string> prev_directions = current.directions;
    for (long unsigned int i = 0; i < prev_directions.size(); ++i){ 
      newstate.directions.push_back(prev_directions[i]);
    }
    newstate.directions.push_back(oss.str());
    result.push_back(newstate);
  }
  
  
  // 2) Pour from B to A
  if (can_pour(current.b, current.a, capB, capA)){
    int poured, newA, newB;

    if (capA - current.a >= current.b){ 
      newA = current.a + current.b;
      newB = 0;
      poured = current.b;
    }
    else{ 
      newA = capA;
      newB = current.b - (capA - current.a);
      poured = capA - current.a;
    }
    State newstate(newA, newB, current.c);
    ostringstream oss;
    if (poured == 1){
      oss << "Pour " << poured << " gallon from B to A. " << newstate.to_string();
    }
    else{
      oss << "Pour " << poured << " gallons from B to A. " << newstate.to_string();
    }
    vector<string> prev_directions = current.directions;
    for (long unsigned int i = 0; i < prev_directions.size(); ++i)
    {
      newstate.directions.push_back(prev_directions[i]);
    }
    newstate.directions.push_back(oss.str());
    result.push_back(newstate);
  }
  
  // 3) Pour from C to B
  if (can_pour(current.c, current.b, capC, capB)){
    //int poured, newA, newB;
    int poured, newB, newC;

    if (capB - current.b >= current.c)
    {
      newB = current.b + current.c;
      newC = 0;
      poured = current.c;
    }
    else
    {
      newB = capB;
      newC = current.c - (capB - current.b);
      poured = capB - current.b;
    }
    State newstate(current.a, newB, newC);
    ostringstream oss;
    if (poured == 1)
    {
      oss << "Pour " << poured << " gallon from C to B. " << newstate.to_string();
    }
    else
    {
      oss << "Pour " << poured << " gallons from C to B. " << newstate.to_string();
    }
    vector<string> prev_directions = current.directions;
    for (long unsigned int i = 0; i < prev_directions.size(); ++i)
    {
      newstate.directions.push_back(prev_directions[i]);
    }
    newstate.directions.push_back(oss.str());
    result.push_back(newstate);
  }
  
  // 4) Pour from A to B
  if (can_pour(current.a, current.b, capA, capB)){
    int poured, newB, newA;

    if (capB - current.b >= current.a)
    {
      newB = current.a + current.b;
      newA = 0;
      poured = current.a;
    }
    else
    {
      newB = capB;
      newA = current.a - (capB - current.b);
      poured = capB - current.b;
    }
    State newstate(newA, newB, current.c);
    ostringstream oss;
    if (poured == 1)
    {
      oss << "Pour " << poured << " gallon from A to B. " << newstate.to_string();
    }
    else
    {
      oss << "Pour " << poured << " gallons from A to B. " << newstate.to_string();
    }
    vector<string> prev_directions = current.directions;
    for (long unsigned int i = 0; i < prev_directions.size(); ++i)
    {
      newstate.directions.push_back(prev_directions[i]);
    }
    newstate.directions.push_back(oss.str());
    result.push_back(newstate);
  }
  
  // 5) Pour from B to C
  if (can_pour(current.b, current.c, capB, capC)){
    int poured, newC, newB;

    if (capC - current.c >= current.b)
    {
      newC = current.c + current.b;
      newB = 0;
      poured = current.b;
    }
    else
    {
      newC = capC;
      newB = current.b - (capC - current.c);
      poured = capC - current.c;
    }
    State newstate(current.a, newB, newC);
    ostringstream oss;
    if (poured == 1)
    {
      oss << "Pour " << poured << " gallon from B to C. " << newstate.to_string();
    }
    else
    {
      oss << "Pour " << poured << " gallons from B to C. " << newstate.to_string();
    }
    vector<string> prev_directions = current.directions;
    for (long unsigned int i = 0; i < prev_directions.size(); ++i)
    {
      newstate.directions.push_back(prev_directions[i]);
    }
    newstate.directions.push_back(oss.str());
    result.push_back(newstate);
  }
 
  // 6) Pour from A to C
  if (can_pour(current.a, current.c, capA, capC)){
    int poured, newC, newA;

    if (capC - current.c >= current.a)
    {
      newC = current.c + current.a;
      newA = 0;
      poured = current.a;
    }
    else
    {
      newC = capC;
      newA = current.a - (capC - current.c);
      poured = capC - current.c;
    }
    State newstate(newA, current.b, newC);
    ostringstream oss;
    if (poured == 1)
    {
      oss << "Pour " << poured << " gallon from A to C. " << newstate.to_string();
    }
    else
    {
      oss << "Pour " << poured << " gallons from A to C. " << newstate.to_string();
    }
    vector<string> prev_directions = current.directions;
    for (long unsigned int i = 0; i < prev_directions.size(); ++i)
    {
      newstate.directions.push_back(prev_directions[i]);
    }
    newstate.directions.push_back(oss.str());
    result.push_back(newstate);
  }

  return result;

}

// displays the solution provided by bfs
void display(State result){
  vector<string> paths = result.get_directions();
  for(unsigned int i = 0; i < paths.size(); ++i){
    cout << paths[i] << endl;
  }
}

//checks to see if the current state is the goal state
bool goal_check(State current, State goal){
  return (current.a == goal.a) && (current.b == goal.b) && (current.c == goal.c);
}

void bfs(int capA, int capB, int capC, int goalA, int goalB, int goalC){
  vector<vector<State>> matrix; // initialize matrix
  for (int i = 0; i < capA + 1; ++i){
    vector<State> row;
    for (int j = 0; j < capB + 1; ++j){
      State item(-1,-1,-1);
      row.push_back(item); // fill the matrix with dummy states
    }
    matrix.push_back(row);
  }
  queue<State> q; //initalize queue
  State start(0,0,capC); 
  State goal(goalA, goalB, goalC);
  bool foundSolution = goal_check(start, goal); // if a solution is found
  vector<string> temp = start.get_directions();
  temp.push_back("Initial state. " + start.to_string()); // add inital state statement into start state's directions vector
  start.directions = temp;
  q.push(start); //push start state into queue and begin bfs
  State current_state = start;
  while (!q.empty() && !foundSolution)
  {
    current_state = q.front();
    //cout << current_state.to_string() << ", ";
    q.pop();
    if(goal_check(current_state,goal)){ // if current_state matches the goal state the algorithm is done and is printed out
      foundSolution = true;
      //break;
    }else{
      matrix[current_state.a][current_state.b] = current_state; // current_state is stored in the matrix
      vector<State> pours = pour(current_state,capA,capB,capC); // the 6 pours are done and resulting states from possible pours are returned as a vector
      for(unsigned int i = 0; i < pours.size(); ++i){ //iterate through the vector to see if the resulting states have been stored in the matrix
        State thisState = pours[i];
        State nullstate(-1,-1,-1);
        int thisA = thisState.a;
        int thisB = thisState.b;
        State thisStateInMatrix = matrix[thisA][thisB];
        if (thisStateInMatrix.a == -1)
        { //the state has not been visited and stored
          matrix[thisState.a][thisState.b] = thisState;       // store it in the matrix
          q.push(thisState);                                // add it to the queue
        } 
      }

    }
  }
  if(!foundSolution){ //if queue is empty then no solution was found
    cout << "No solution." << endl;
  } else {
    display(current_state);
  }
  
}



int main(int argc, char * const argv[]){
    istringstream iss;
    int ca, cb, cc, ga, gb, gc;

    //incorrect number or arguements
    if (argc != 7) {
      cout << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
      return 1;
    }

    //check input on each jug
    iss.str(argv[1]);
    if (!(iss >> ca) || ca < 0) {
      cout << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
      return 1;
    }
    iss.clear();

    iss.str(argv[4]);
    if (!(iss >> ga) || ga < 0) {
      cout << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
      return 1;
    }
    iss.clear();

    iss.str(argv[2]);
    if (!(iss >> cb) || cb < 0) {
      cout << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
      return 1;
    }
    iss.clear();

    iss.str(argv[5]);
    if (!(iss >> gb) || gb < 0) {
      cout << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
      return 1;
    }
    iss.clear();

    iss.str(argv[3]);
    if (!(iss >> cc) || cc <= 0) {
      cout << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
      return 1;
    }
    iss.clear();

    iss.str(argv[6]);
    if (!(iss >> gc) || gc < 0) {
      cout << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
      return 1;
    }
    iss.clear();

    //checking if the goal exceeds the capcity
    if (ga > ca) {
      cout << "Error: Goal cannot exceed capacity of jug A." << endl;
      return 1;
    }

    if (gb > cb) {
      cout << "Error: Goal cannot exceed capacity of jug B." << endl;
      return 1;
    }

    if (gc > cc) {
      cout << "Error: Goal cannot exceed capacity of jug C." << endl;
      return 1;
    }

    //checking total water with jug C capacity
    if (cc != ga + gb + gc) {
      cout << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
      return 1;
    }

    // No command line errors so regular process
    bfs(ca,cb,cc,ga,gb,gc);
    return 0;
}