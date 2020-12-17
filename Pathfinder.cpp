#include "Pathfinder.h"



bool Pathfinder::importMaze(string file_name){
	cout << "importMaze from "<<file_name<<endl;
		ifstream this_file (file_name.c_str());
		string check_lines;
		int num_lines = 0;
		if (this_file.is_open()) {
			while(!this_file.eof()){
				getline(this_file, check_lines);
				num_lines++;
			}
			num_lines = num_lines - 4;
			if(num_lines != 25){
				return false;
			}
		}
		
		ifstream my_maze (file_name.c_str());	
			for(int row = 0; row < ROW_SIZE; row++){
				for(int col = 0; col < COL_SIZE; col++){
					for(int flo = 0; flo < FLO_SIZE; flo++){
						string line;
						my_maze >> line;
						if(line != "0" && line != "1"){
							return false;
						}
						else{
							cout << "["<<flo<<"]["<<col<<"]"<< "[" << row << "]=" <<line<<endl;
							maze_grid[flo][col][row] = stoi(line);
						}
					}
				}
			}	
			
			if(maze_grid[0][0][0] == 0 || maze_grid[4][4][4] == 0){
				return false;
			}
			
		
	    return true;
}

	
	
string Pathfinder::toString() const
	{
	    stringstream ss;										
	    for(int row = 0; row < ROW_SIZE; row++) {				
	        for(int col = 0; col < COL_SIZE; col++) {
	        	for(int flo = 0; flo < FLO_SIZE; flo++){
	        		if(flo < 4){
	        			ss << maze_grid[flo][col][row] << " ";
	        		}
	        		else{
	        			ss << maze_grid[flo][col][row];
	        		}
	        	}
	        	ss << endl;
	        }
	        if (row < 4){
	        	ss << endl;
	        }
	        
	    }
	    return ss.str();
	}
	
void Pathfinder::createRandomMaze(){
	
	for (int row = 0; row < ROW_SIZE; row++){					
		for (int col = 0; col < COL_SIZE; col++){
			for (int flo = 0; flo < FLO_SIZE; flo++){
				maze_grid[flo][col][row] = rand() % 2;
			}
		}
	}
	maze_grid[0][0][0] = 1;
	maze_grid[4][4][4] = 1;
}

bool Pathfinder::find_maze_path(int grid[ROW_SIZE][COL_SIZE][FLO_SIZE], int r, int c, int f){
	if (r < 0 || r >= ROW_SIZE || c < 0 || c >= COL_SIZE || f < 0 || f >= FLO_SIZE){
		return false;
	}
	else if(grid[f][c][r] == 0 || grid[f][c][r] == 2){
		return false;
	}
	else if (grid[f][c][r] != BACKGROUND){											
		return false;
	}
	else if (r == ROW_SIZE - 1 && c == COL_SIZE - 1 && f == FLO_SIZE - 1){
		grid[f][c][r] = PATH;
		solution.push_back("("+to_string(f)+", "+to_string(c)+", "+to_string(r)+")");
		return true;
	}
	else{
		grid[f][c][r] = PATH;
		
		if (find_maze_path(grid, r - 1, c, f)
	        || find_maze_path(grid, r + 1, c, f)
	        || find_maze_path(grid, r, c - 1, f)
	        || find_maze_path(grid, r, c + 1, f)
	        || find_maze_path(grid, r, c, f + 1)
	        || find_maze_path(grid, r, c, f - 1)){
	        	solution.push_back("("+to_string(f)+", "+to_string(c)+", "+to_string(r)+")");
	        	return true;
	        }
	        else{
	        	grid[f][c][r] = TEMPORARY;
	        	return false;
	        }
	    	
	    }
}

vector<string> Pathfinder::solveMaze(){
	solution.clear();
	find_maze_path(maze_grid, 0,0,0);
		for(int row = 0; row < ROW_SIZE; row++) {				
	        for(int col = 0; col < COL_SIZE; col++) {
	        	for(int flo = 0; flo < FLO_SIZE; flo++){
	        		if (maze_grid[flo][col][row] == PATH || maze_grid[flo][col][row] == TEMPORARY){
	        			maze_grid[flo][col][row] = 1;
	        		}
	        	}
	        }
		}
		reverse(solution.begin(), solution.end());
	    return solution;
	
}