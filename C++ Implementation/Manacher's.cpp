// A C++ program to implement Manacher's Algorithm 
#include <bits/stdc++.h> 
#include <fstream>
using namespace std; 

void findLongestPalindromicString(string text) 
{ 
	int N = text.length(); 
	if (N == 0) 
		return; 

	// Position count 
	N = 2 * N + 1; 

	// LPS Length Array 
	int L[N]; 
	L[0] = 0; 
	L[1] = 1; 

	// centerPosition 
	int C = 1; 

	// centerRightPosition 
	int R = 2; 

	// currentRightPosition 
	int i = 0; 

	// currentLeftPosition 
	int iMirror; 
	int expand = -1; 
	int diff = -1; 
	int maxLPSLength = 0; 
	int maxLPSCenterPosition = 0; 
	int start = -1; 
	int end = -1; 

	
	for (i = 2; i < N; i++) { 
		// Get currentLeftPosition iMirror 
		// for currentRightPosition i 
		iMirror = 2 * C - i; 

		// Reset expand - means no 
		// expansion required 
		expand = 0; 
		diff = R - i; 

		// If currentRightPosition i is 
		// within centerRightPosition R 
		if (diff >= 0) { 

			// Case 1 
			if (L[iMirror] < diff) 
				L[i] = L[iMirror]; 

			// Case 2 
			else if (L[iMirror] == diff && R == N - 1) 
				L[i] = L[iMirror]; 

			// Case 3 
			else if (L[iMirror] == diff && R < N - 1) { 
				L[i] = L[iMirror]; 

				// Expansion required 
				expand = 1; 
			} 

			// Case 4 
			else if (L[iMirror] > diff) { 
				L[i] = diff; 

				// Expansion required 
				expand = 1; 
			} 
		} 
		else { 
			L[i] = 0; 

			// Expansion required 
			expand = 1; 
		} 

		if (expand == 1) { 

			// Attempt to expand palindrome centered 
			// at currentRightPosition i. Here for odd 
			// positions, we compare characters and 
			// if match then increment LPS Length by ONE 
			// If even position, we just increment LPS 
			// by ONE without any character comparison 

			while (((i + L[i]) < N && (i - L[i]) > 0) 
				&& (((i + L[i] + 1) % 2 == 0) 
					|| (text[(i + L[i] + 1) / 2] 
						== text[(i - L[i] - 1) / 2]))) { 
				L[i]++; 
			} 
		} 

		// Track maxLPSLength 
		if (L[i] > maxLPSLength) { 
			maxLPSLength = L[i]; 
			maxLPSCenterPosition = i; 
		} 

		// If palindrome centered at 
		// currentRightPosition i expand 
		// beyond centerRightPosition R, 
		// adjust centerPosition C based 
		// on expanded palindrome. 
		if (i + L[i] > R) { 
			C = i; 
			R = i + L[i]; 
		} 

		
	} 

	start = (maxLPSCenterPosition - maxLPSLength) / 2; 
	end = start + maxLPSLength - 1; 


	cout << "LPS of string is " << text << " : "; 

	for (i = start; i <= end; i++) 
		cout << text[i]; 
	cout << endl; 
} 

int main()
{
    ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        cout << "Error opening the input file." << endl;
        return 1;
    }

    string text;
    while (getline(inputFile, text))
    {
        findLongestPalindromicString(text);
    }

    inputFile.close();
    return 0;
}
