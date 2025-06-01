#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using std::vector;
using std::abs;

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

int main()
{
    vector<int> occupiedPlaces = {1, 50, 100};
    int maxPossiblePlaces = 100;

    int res = findMostRemotePlace(occupiedPlaces, maxPossiblePlaces);
    std::cout << res << std::endl;
}
