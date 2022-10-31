#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/*
 * Longest Common Subsequence:
 * Given two text strings, return the length of their longest common subsequence.
 * A DP problem. O(n * m) for both memory and time.
 */

// Supplementary function to print 2d vectors
template <typename T> 
void printv2d(const std::vector<std::vector<T>>& v) {
    for (int row{}; row < v.size(); ++row) {
        for (int col{}; col < v[row].size(); ++col) {
	    std::cout << v[row][col] << ' ';
	}
	std::cout << '\n';
    }
}


int lcs(const std::string& text1, const std::string& text2) {
    std::vector<std::vector<int>> dp (text1.size() + 1, std::vector<int>(text2.size() + 1, 0));
    // make an empty matrix of text1.size() + 1 rows and text2.size() + 1 columns
    const long rows = text1.size() + 1, cols = text2.size() + 1 ;
    // unsigned here breaks the whole code since overflow happens

    // fill the whole array
    // To understand why it is rows - 2 and cols - 2, consider the table
    //   A C E ""
    // A        0
    // B        0
    // C        0
    // D        0
    // E        0
    // "" 0 0 0 0
    for (auto row {rows - 2}; row >= 0; --row) {
        for (auto col {cols - 2}; col >= 0; --col) {
	    if (text1[row] == text2[col])
	        dp[row][col] = 1 + dp[row + 1][col + 1];
	    else 
		dp[row][col] = std::max(dp[row][col + 1], dp[row + 1][col]);
	}
    }

    return dp[0][0];
}

int main() {
    std::string text1{}, text2{};
    std::getline(std::cin, text1);
    std::getline(std::cin, text2);

    int lcs_len = lcs(text1, text2);
    std::cout << lcs_len << '\n';

    return 0;
}
