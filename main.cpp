//=======================================================================
// Copyright (c) 2017 Adrian Schneider
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#include <iostream>
#include <vector>
#include "mnist/mnist_reader.hpp"

using namespace std;

int distance(vector<uint8_t> const &image_a, vector<uint8_t> const &image_b) {
    int sum{0};
    for (int i = 0; i < 784; i++) {
        int tmp = (image_a[i] - image_b[i]);
        sum += tmp * tmp;
    }
    return sum;
}

int find_min_distance(vector<vector<uint8_t>> const &training_images, vector<uint8_t> const &test_image) {
    int min_distance{distance(training_images[0], test_image)}, index_with_min_distance{0};
    for (int i = 1; i < 60000; i++) {
        if (distance(training_images[i], test_image) < min_distance) {
            min_distance = distance(training_images[i], test_image);
            index_with_min_distance = i;
        }
    }
    return index_with_min_distance;
}

int main(int argc, char *argv[]) {
    // Load MNIST data
    auto dataset = mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>(MNIST_DATA_LOCATION);

    int success_count{0};
    for (int i = 0; i < 10000; i += 10) {
        int index = find_min_distance(dataset.training_images, dataset.test_images[i]);
        if (dataset.training_labels[index] == dataset.test_labels[i])
            success_count++;
    }
    cout << success_count << " / 1000" << endl;

    return 0;
}
