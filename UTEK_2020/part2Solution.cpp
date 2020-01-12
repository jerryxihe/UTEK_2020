#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    string originalWord;
    string desiredWord;

    // Opens file
    string inputFileName = argv[1];
    ifstream f;
    f.open(inputFileName.c_str());

    getline(f, originalWord);
    getline(f, desiredWord);

    originalWord.pop_back();

    cout << originalWord << '\n';
    // cout << originalWord.size() << '\n';
    cout << desiredWord << '\n';

    vector<vector<int>> dp(originalWord.size()+1, vector<int>(desiredWord.size()+1));
    dp[0][0] = 0;
    for(int i = 0; i < originalWord.size(); ++ i)
        dp[i+1][0] = i+1;
    for(int i = 0; i < desiredWord.size(); ++ i)
        dp[0][i+1] = i+1;
        
    for(int i = 0; i < originalWord.size(); ++ i){
        for(int j = 0; j < desiredWord.size(); ++ j){
            if(originalWord[i] == desiredWord[j]){
                dp[i+1][j+1] = dp[i][j];
            }
            else{
                dp[i+1][j+1] = min(dp[i][j], min(dp[i][j+1], dp[i+1][j])) + 1;
            }
        }
    }

    for (int i = 0; i < desiredWord.size()+1; ++i) {
        for (int j = 0; j < originalWord.size()+1; ++j) {
            if (dp[j][i] < 10) {
                cout << ' ';
            }
            if (dp[j][i] < 100) {
                cout << ' ';
            }
            if (dp[j][i] < 1000) {
                cout << ' ';
            }
            cout << dp[j][i] << ' ';
        }
        cout << '\n';
    }

    vector<vector<int>> path;

    int currentRow = originalWord.size();
    int currentCol = desiredWord.size();
    int currentLength = dp[originalWord.size()][desiredWord.size()];

    vector<int> lastElement;
    lastElement.push_back(3);
    lastElement.push_back(currentRow);
    lastElement.push_back(currentCol);
    path.push_back(lastElement);

    while (currentRow != 0 && currentCol != 0) {
        vector<int> element;
        if (currentRow == 0) {
            --currentCol;
            // element.push_back(dp[currentRow][currentCol]);
            element.push_back(2);   // Insert
            element.push_back(currentRow);
            element.push_back(currentCol);
            path.push_back(element);
        } else if (currentCol == 0) {
            --currentRow;
            // element.push_back(dp[currentRow][currentCol]);
            element.push_back(1);   // Delete
            element.push_back(currentRow);
            element.push_back(currentCol);
            path.push_back(element);
        } else {
            int smallest;
            smallest = min(dp[currentRow-1][currentCol], min(dp[currentRow][currentCol-1], dp[currentRow-1][currentCol-1]));
            if (dp[currentRow-1][currentCol-1] == smallest) {
                if (dp[currentRow-1][currentCol-1] == dp[currentRow][currentCol]) {
                    element.push_back(3);
                } else {
                    element.push_back(0);
                }
                --currentRow;
                --currentCol;
                // element.push_back(dp[currentRow][currentCol]);
                element.push_back(currentRow);
                element.push_back(currentCol);
                path.push_back(element);
            } else if (dp[currentRow-1][currentCol] == smallest) {
                --currentRow;
                // element.push_back(dp[currentRow][currentCol]);
                element.push_back(1);   // Delete
                element.push_back(currentRow);
                element.push_back(currentCol);
                path.push_back(element);
            } else {
                --currentCol;
                // element.push_back(dp[currentRow][currentCol]);
                element.push_back(2);   // Insert
                element.push_back(currentRow);
                element.push_back(currentCol);
                path.push_back(element);
            }
        }
    }
    for (int i = 0; i < path.size(); ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << path[i][j] << ' ';
        }
        cout << '\n';
    }

    //////////////////
    // vector<string> desiredWord = { "aah", "baa", "caaa", "daaa" };//test

	// vector<vector<int> > path(5, vector<int>(3));

	std::vector<std::vector<std::string>> output;
	std::vector<std::string>s(4);

	// for (int i = 0; i < 5; i++) {
	// 	for (int j = 0; j < 3; j++) {
	// 		path[i][j] = i;
	// 	}
	// }

	int position = 0;
	int index_val = 0;

	for (int i = path.size()-1; i >= 0; i--) {

		index_val = path[i][1] + position;

        cout << index_val << '\n';

		string operation;
		if (path[i][0] == 3) {
			continue;
		}
		else if (path[i][0] == 0) {
			operation = "Replace";
		}
		else if (path[i][0] == 1) {
			operation = "Delete";
		}
		else if (path[i][0] == 2) {
			operation = "Insert";
		}
		s[0] = operation;
		s[1] = to_string(index_val);
		s[2] = to_string(index_val);

		if (path[i][2] == 0 || path[i][2] == 2) {
			s[3] = desiredWord[i];
		}
		else {
			s[3] = "";
		}

        if (path[i][0] == 1) {
			position--;
            // cout << position << "\n";
		}
		else if (path[i][0] == 2) {
			position++;
            // cout << position << "blah\n";
		}

		if (output.size() != 0) {
			if (output[output.size() - 1][0] == s[0]) {
				if (s[0] == "Insert") {
					int idx1 = std::stoi(output[output.size() - 1][2]);
					int idx2 = std::stoi(s[1]);
					if (idx1 + 1 == idx2) {
						output[output.size() - 1][2] = s[1];
						output[output.size() - 1][3] = output[output.size() - 1][3] + " ";
                        int difference = stoi(output[output.size() - 1][2]) - stoi(output[output.size() - 1][1]);
                        cout << difference << "blah\n";
                        for (int j = difference; j >= 0; --j) {
                            output[output.size() - 1][3] = output[output.size() - 1][3] + desiredWord[path[i][1]-1-j];
                        }
					}
				}
				else if (s[0] == "Replace") {
					int idx1 = std::stoi(output[output.size() - 1][2]);
					int idx2 = std::stoi(s[1]);
					if (idx1 + 1 == idx2) {
						output[output.size() - 1][2] = s[1];
						output[output.size() - 1][3] = output[output.size() - 1][3] + " ";
                        int difference = stoi(output[output.size() - 1][2]) - stoi(output[output.size() - 1][1]);
                        cout << difference << "blah\n";
                        for (int j = difference; j >= 0; --j) {
                            output[output.size() - 1][3] = output[output.size() - 1][3] + desiredWord[path[i][1]-1-j];
                        }
					}
				}
				else if (s[0] == "Delete") {
					int idx1 = std::stoi(output[output.size() - 1][2]);
					int idx2 = std::stoi(s[1]);
					if (idx1 == idx2) {
						idx1 = idx1 + 1;
						output[output.size() - 1][2] = std::to_string(idx1);
					}
				}
				else {
					// output.push_back(s);
				}
			}
			else {
				output.push_back(s);
			}
		}
		else {
			output.push_back(s);
		}


	}


	std::ofstream myfile;
	myfile.open("output.out");


	std::string final_output;
	for (int i = 0; i < output.size(); i++) {
		if (output[i][0] == "Delete") {
			final_output = final_output + output[i][0] + " " + output[i][1] + "-" + output[i][2] + "\n";
		}
		else {
			final_output = final_output + output[i][0] + " " + output[i][1] + "-" + output[i][2] + ", " + output[i][3] + "\n";
		}
	}
	myfile << final_output;
	myfile.close();


}