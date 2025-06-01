#include <iostream>
#include <string>
#include <regex>
#include <list>

std::string trimStrToBaseSets(const std::string &workoutStr)
{
    std::string startKey = "Main sets:";
    size_t startKeyPosition = workoutStr.find(startKey);

    if (startKeyPosition == std::string::npos) {
        std::cout << "Main sets missed" << std::endl;
        return std::string();
    }

    return workoutStr.substr(startKeyPosition, workoutStr.size() - startKeyPosition);
}

double calcWorkoutTonnage(std::string &workoutStr)
{
    double workoutTonnage = 0.0;

    std::replace(workoutStr.begin(), workoutStr.end(), ',', '.');

    std::regex pattern(R"(\b(\d+(\.\d+)?)\s*\*\s*(\d+)\b)");
    std::smatch matches;

    auto it = workoutStr.cbegin();
    while (std::regex_search(it, workoutStr.cend(), matches, pattern)) {
        std::string weightStr = matches[1].str();
        std::string reps = matches[3].str();

        double setTonnage = std::stod(weightStr) * std::stoi(reps);
        workoutTonnage += setTonnage;

        it = matches[0].second;
    }

    return workoutTonnage;
}

std::string removeZerosFromDouble(double &val)
{
    std::string stringVal = std::to_string(val);
    for (int i = stringVal.size() - 1; i > 0; --i) {
        if (stringVal[i] == '0' && stringVal[i - 1] == '.')
        {
            stringVal.pop_back();
            stringVal.pop_back();
            return stringVal;
        }
        else if (stringVal[i] == '0')
        {
            stringVal.pop_back();
        }
        else {
            break;
        }
    }

    return stringVal;
}

int main()
{
    std::string workout =
            R"(
01.05.2025
20:35

Bench press

Warm-up sets:

barbell * 10
50 * 5
60 * 5

Main sets:

(1)
75 * 5 (easy)

(2)
75 * 5 (made a bad bridge)

(3)
72,5 * 5 (harder)

(4)
72,5 * 5

(5)
65 * 5 (with the reserve)

(6)
62,5 * 5 (with the reserve)
)";

    std::string trimmedWorkoutStr = trimStrToBaseSets(workout);
    double res = calcWorkoutTonnage(trimmedWorkoutStr);

    std::string resStr = removeZerosFromDouble(res);
    std::cout << resStr << std::endl;


    return 0;
}
