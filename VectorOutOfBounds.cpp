#include <vector>

void VectorOutOfBounds() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    vec[0] = vec[5];
}
