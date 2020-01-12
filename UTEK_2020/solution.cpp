#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

int main(int argc, char* argv[]) {
    string lineToAdd;
    string firstLine;
    vector<string> originalOrder;
    vector<string> desiredOrder;

    // Opens file
    string inputFileName = argv[1];
    ifstream f;
    f.open(inputFileName.c_str());

    getline(f, lineToAdd);

    // Add original to vector
    while (getline(f, lineToAdd)) {
        if (!lineToAdd.find("Desired: ")) {
            originalOrder.pop_back();
            break;
        }
        originalOrder.push_back(lineToAdd);
    }

    // Add desired to vector
    while (getline(f, lineToAdd)) {
        desiredOrder.push_back(lineToAdd);
    }
    f.close();

    // cout << "Original vector\n";
    // for (unsigned int i = 0; i < originalOrder.size(); ++i) {
    //     cout << i << ' ' << originalOrder[i] << '\n';
    // }
    // cout << '\n';
    // cout << "Desired vector\n";
    // for (unsigned int i = 0; i < desiredOrder.size(); ++i) {
    //     cout << i << ' ' << desiredOrder[i] << '\n';
    // }
    // cout << '\n';

    vector<vector<int>> dp(originalOrder.size()+1, vector<int>(desiredOrder.size()+1));
    dp[0][0] = 0;
    for(int i = 0; i < originalOrder.size(); ++ i)
        dp[i+1][0] = i+1;
    for(int i = 0; i < desiredOrder.size(); ++ i)
        dp[0][i+1] = i+1;
        
    for(int i = 0; i < originalOrder.size(); ++ i){
        for(int j = 0; j < desiredOrder.size(); ++ j){
            if(originalOrder[i] == desiredOrder[j]){
                dp[i+1][j+1] = dp[i][j];
            }
            else{
                dp[i+1][j+1] = min(dp[i][j], min(dp[i][j+1], dp[i+1][j])) + 1;
            }
        }
    }

    // for (int i = 0; i < originalOrder.size()+1; ++i) {
    //     for (int j = 0; j < desiredOrder.size()+1; ++j) {
    //         if (dp[i][j] < 10) {
    //             cout << ' ';
    //         }
    //         if (dp[i][j] < 100) {
    //             cout << ' ';
    //         }
    //         if (dp[i][j] < 1000) {
    //             cout << ' ';
    //         }
    //         cout << dp[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

    vector<vector<int>> path;

    int currentRow = originalOrder.size();
    int currentCol = desiredOrder.size();
    int currentLength = dp[originalOrder.size()][desiredOrder.size()];

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
    // for (int i = 0; i < path.size(); ++i) {
    //     for (int j = 0; j < 3; ++j) {
    //         cout << path[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

    //////////////////
    // vector<string> desiredOrder = { "aah", "baa", "caaa", "daaa" };//test

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

        // cout << index_val << '\n';

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

		if (path[i][0] == 0 || path[i][0] == 2) {
            desiredOrder[i].pop_back();
			s[3] = "\"" + desiredOrder[i] + "\"";
		}
		else {
			s[3] = "";
		}

        // cout << s[0] << ' ' << s[1] << ' ' << s[2] << ' ' << s[3] << '\n';

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
						output[output.size() - 1][3] = output[output.size() - 1][3] + ", " + s[3];
					}
				}
				else if (s[0] == "Replace") {
					int idx1 = std::stoi(output[output.size() - 1][2]);
					int idx2 = std::stoi(s[1]);
					if (idx1 + 1 == idx2) {
						output.back()[2] = s[1];
						output[output.size() - 1][3] = output[output.size() - 1][3] + ", " + s[3];
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
				// else {
				// 	output.push_back(s);
				// }
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
            // cout << output[i][0] << "blah\n";
			final_output = final_output + output[i][0] + " " + output[i][1] + "-" + output[i][2] + ", " + output[i][3] + "\n";
		}
	}
	myfile << final_output;
	myfile.close();


}
