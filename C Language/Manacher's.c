#include <stdio.h>
#include <string.h>

void findLongestPalindromicString(char text[])
{
    int N = strlen(text);
    if (N == 0)
        return;
    N = 2 * N + 1; //Position count
    int L[N];      //LPS Length Array
    L[0] = 0;
    L[1] = 1;
    int C = 1; //centerPosition
    int R = 2; //centerRightPosition
    int i = 0; //currentRightPosition
    int iMirror; //currentLeftPosition
    int expand = -1;
    int diff = -1;
    int maxLPSLength = 0;
    int maxLPSCenterPosition = 0;
    int start = -1;
    int end = -1;

    
    for (i = 2; i < N; i++)
    {
        //get currentLeftPosition iMirror for currentRightPosition i
        iMirror = 2 * C - i;
        //Reset expand - means no expansion required
        expand = 0;
        diff = R - i;
        //If currentRightPosition i is within centerRightPosition R
        if (diff >= 0)
        {
            if (L[iMirror] < diff) // Case 1
                L[i] = L[iMirror];
            else if (L[iMirror] == diff && R == N - 1) // Case 2
                L[i] = L[iMirror];
            else if (L[iMirror] == diff && R < N - 1) // Case 3
            {
                L[i] = L[iMirror];
                expand = 1; // expansion required
            }
            else if (L[iMirror] > diff) // Case 4
            {
                L[i] = diff;
                expand = 1; // expansion required
            }
        }
        else
        {
            L[i] = 0;
            expand = 1; // expansion required
        }

        if (expand == 1)
        {
            //Attempt to expand palindrome centered at currentRightPosition i
            //Here for odd positions, we compare characters and
            //if match then increment LPS Length by ONE
            //If even position, we just increment LPS by ONE without
            //any character comparison
            while (((i + L[i]) < N && (i - L[i]) > 0) &&
                   (((i + L[i] + 1) % 2 == 0) ||
                    (text[(i + L[i] + 1) / 2] == text[(i - L[i] - 1) / 2])))
            {
                L[i]++;
            }
        }

        if (L[i] > maxLPSLength) // Track maxLPSLength
        {
            maxLPSLength = L[i];
            maxLPSCenterPosition = i;
        }

        // If palindrome centered at currentRightPosition i
        // expand beyond centerRightPosition R,
        // adjust centerPosition C based on expanded palindrome.
        if (i + L[i] > R)
        {
            C = i;
            R = i + L[i];
        }
        
    }
    //printf("\n");
    start = (maxLPSCenterPosition - maxLPSLength) / 2;
    end = start + maxLPSLength - 1;
    
    printf("LPS of string is %s : ", text);
    for (i = start; i <= end; i++)
        printf("%c", text[i]);
    printf("\n");
}

int main()
{
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL)
    {
        printf("Error opening the input file.");
        return 1;
    }

    char text[100];
    while (fgets(text, sizeof(text), inputFile))
    {
        // Remove newline character if present
        text[strcspn(text, "\n")] = '\0';
        findLongestPalindromicString(text);
    }

    fclose(inputFile);
    return 0;
}
