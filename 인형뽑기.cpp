#include <string>
#include <vector>
#include<stdio.h>
using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    vector<int> stack;

    for (int i = 0; i < moves.size(); i++)
    {
        for (int j = 0; j < board[moves[i] - 1].size(); j++)
        {
            if (board[j][moves[i] - 1] == 0)
                continue;

            stack.push_back(board[j][moves[i] - 1]);

            board[j][moves[i] - 1] = 0;

            if (stack.size() > 1)
            {
                if (stack.back() == stack.at(stack.size() - 2))
                {
                    stack.pop_back();
                    stack.pop_back();
                    answer += 2;
                }
            }
            break;
        }
    }
    return answer;
}