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
Output: 1
Explanation:
- the most remote places are 25 and 75, return any of them
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