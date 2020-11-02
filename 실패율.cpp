#include <string>
#include <vector>
#include<algorithm>
using namespace std;

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;

    vector<double> missrate;
    double survivor = stages.size();
    int failure = 0;
    double beforeSurvivor = stages.size();

    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j < stages.size(); j++)
        {
            if (survivor == 0)
                break;

            if (stages.at(j) == i && survivor != 0)
            {
                survivor--;
                failure++;
            }
        }
        if (survivor == 0 && failure == 0)
        {
            missrate.push_back(0.000000);
            failure = 0;
        }
        else
        {
            missrate.push_back(failure / beforeSurvivor);
            failure = 0;
            beforeSurvivor = survivor;
        }
    }

    for (int i = 0; i < missrate.size(); i++)
    {

        answer.push_back(i + 1);
        //    printf("answer : %f answer : %d \n",answer.at(i),missrate.at(answer.at(i)-1));
       //    printf("answer : %d\n", answer.at(i));
    }

    for (int i = 0; i < missrate.size(); i++)
    {
        for (int j = i + 1; j < missrate.size(); j++)
        {
            if (missrate.at(i) > missrate.at(j))
            {
                int temp = answer.at(i);
                answer.at(i) = answer.at(j);
                answer.at(j) = temp;
            }
        }
        printf("answer : %f answer : %d \n", answer.at(i), missrate.at(answer.at(i) - 1));
    }

    reverse(answer.begin(), answer.end());

    for (int i = 0; i < missrate.size(); i++)
    {
        for (int j = i + 1; j < missrate.size(); j++)
        {
            if (answer.at(i) > answer.at(j) && missrate.at(answer.at(i) - 1) == missrate.at(answer.at(j) - 1) ||
                missrate.at(answer.at(i) - 1) < missrate.at(answer.at(j) - 1))
            {
                int temp = answer.at(i);
                answer.at(i) = answer.at(j);
                answer.at(j) = temp;

                //  temp = missrate.at(i);
                //  missrate.at(i) = missrate.at(j);
                //  missrate.at(j) = temp;
            }
        }

    }

    // for(int i =0;i<missrate.size();i++)
      //   printf("missrate : %f  answer : %d \n", missrate.at(answer.at(i)-1),answer.at(i));

    return answer;
}