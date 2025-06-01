## 1. Find the most remote place

You are given a locker room with a total of maxPossiblePlace places, numbered from 1 to maxPossiblePlace. Some of these places are already occupied, and their indices are given in the array occupiedPlaces.

Your task is to find the place number where a new person can sit so that the distance to the nearest occupied place is maximized. 

**Example 1**:
```c++
Input: occupiedPlaces = [3, 7], maxPossiblePlace = 10
Output: 10
Explanation:
- The places 3 and 7 are occupied.
- The furthest place from both is 10, which is the rightmost available place.
```

**Example 2**:
```c++
Input: occupiedPlaces = [], maxPossiblePlace = 5
Output: 1
Explanation:
- if occupiedPlaces is empty, you must return the first place
```

**Example 3**:
```c++
Input: occupiedPlaces = [1, 50, 100], maxPossiblePlace = 100
Output: 75
Explanation:
- The most remote places is 75
```

**Solution**

The idea is to find the most remote place by considering three main components:
1. Distance Between Neighboring Occupied Places:

Calculate the distances between all pairs of neighboring occupied places in the occupiedPlaces array. For each pair, the maximum distance to a potential new place is half the distance between them. This is because the most remote place will be located in the middle of the gap between two occupied places.

2) Distance from the Left Boundary:

Compute the distance from the left boundary (position 1) to the first occupied place in the occupiedPlaces array. This distance represents the potential maximum distance for a new place if it is located at the very beginning of the locker room.

3) Distance from the Right Boundary:

Calculate the distance from the right boundary (position maxPossiblePlace) to the last occupied place in the occupiedPlaces array. This distance represents the potential maximum distance for a new place if it is located at the very end of the locker room.

**Note!**

Before performing the calculations, we should sort the input array of occupied places. This is essential because it allows us to accurately compute the distances between neighboring occupied places and ensures that we are considering the correct order of places.

```c++
int findMostRemotePlace(vector<int> &occupiedPlaces, int maxPossiblePlaces)
{
    if (occupiedPlaces.empty()) {
        return 1;
    }

    std::sort(occupiedPlaces.begin(), occupiedPlaces.end());

    int maxDistance = 0;
    int mostRemotePlace = -1;

    int leftDistance = occupiedPlaces[0] - 1;
    if (leftDistance > maxDistance) {
        maxDistance = leftDistance;
        mostRemotePlace = 1;
    }

    int rightDistance = maxPossiblePlaces - occupiedPlaces.back();
    if (rightDistance > maxDistance) {
        maxDistance = rightDistance;
        mostRemotePlace = maxPossiblePlaces;
    }

    int curDistance = 0;
    for (int i = 0; i < occupiedPlaces.size() - 1; ++i) {
        curDistance = (occupiedPlaces[i + 1] - occupiedPlaces[i]) / 2;
        if (curDistance > maxDistance) {
            maxDistance = curDistance;
            mostRemotePlace = occupiedPlaces[i] + curDistance;
        }
    }

    return mostRemotePlace;
}
```

## 2. Calculate Workout Tonnage

You are given a string representing a workout log, which contains various exercises and their corresponding weights and repetitions. The format of the log includes sections for warm-up sets and main sets, with weights and repetitions specified in the following format: weight * reps. Your task is to calculate the total tonnage lifted during the main sets of the workout and return the result as string.

**Note!**

You must return answer without extra zeros

```
1000.500 -> 1000.5
550.0 -> 550 
```

**Example 1**:
```c++
/// use raw strings to avoid special characters (you don't need to specify \n text transfer)
Input: workoutStr = R"(
Main sets:
(1)
75 * 5 (easy)

(2)
75 * 5 (made a bad bridge)

(3)
72.5 * 5 (harder)
)"
Output: 1112,5
Explanation:
- The weights lifted in the main sets are 75, 75, and 72.5, with each lifted for 5 repetitions.
- Total tonnage = (75 * 5) + (75 * 5) + (72.5 * 5) = 1112,5.
```

**Example 2**:
```c++
Input: workoutStr = R"(
Main sets:
(1)
100 * 3 (heavy)

(2)
50 * 10 (light)
)"
Output: 800
Explanation:
- The weights lifted in the main sets are 100 and 50, with repetitions of 3 and 10 respectively.
- Total tonnage = (100 * 3) + (50 * 10) = 800.
```

Use this test case for solving
```c++
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
```

**Solution**

Firstly, we don't need to iterate all over the string, let's trim our input string from the phrase: "Main sets:"

```c++
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
```

Secondly, we need to replace all commas with dots (for correct cast string to double)

```c++
std::replace(workoutStr.begin(), workoutStr.end(), ',', '.');
```

Now, let's make a pattern, to get all main sets

```c++
std::regex pattern(R"(\b(\d+(\.\d+)?)\s*\*\s*(\d+)\b)");
```

With raw string: \b (directly)

Without: \\\b (must indicate that it is a special symbol)

Explicit indication of boundaries for pattern: \b(template)\b is a good practice

For example:

```c++
  std::regex pattern(R"(\bcat\b)");
  std::string text = "The catalog is on the roof.";
  std::smatch matches;

  if (std::regex_search(text, matches, pattern)) {
      std::cout << "Found: " << matches[0] << std::endl; 
  } else {
      std::cout << "Not found" << std::endl; // Output: Not found 
  }
```

```c++
  std::regex pattern(R"(cat)");
  std::string text = "The catalog is on the roof.";
  std::smatch matches;

  if (std::regex_search(text, matches, pattern)) {
      std::cout << "Found: " << matches[0] << std::endl; // Output: Found: cat
  }
```

```
\d+(\.\d+)?) - double num with optional fractional part
```

```
\s*\*\s* - ignore count of space character and find symbol '*'
```

```
(\d+) - reps count like int
```

Making an object to hold all matches
```c++
std::smatch matches;
```

Iterate and calc set tonnage
```c++
    auto it = workoutStr.cbegin();
    while (std::regex_search(it, workoutStr.cend(), matches, pattern)) {
        std::string weightStr = matches[1].str();
        std::string reps = matches[3].str();

        double setTonnage = std::stod(weightStr) * std::stoi(reps);
        workoutTonnage += setTonnage;

        it = matches[0].second;
    }
```

Remember that you also need to remove extra zeros

```c++
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
```

Full solution
```c++
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
```