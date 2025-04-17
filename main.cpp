#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

using Image = vector<double>;
using Model = vector<vector<double>>;

Model getTestData(const string& filename, vector<int>& labels) {
    Model images;

    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        getline(ss, token, ',');
        labels.push_back(stoi(token));

        Image image;
        while (getline(ss, token, ',')) {
            image.push_back(stod(token));
        }

        if (image.size() != 784) {
            cerr << "Ошибка: найдено " << image.size() << " пикселей вместо 784." << endl;
            exit(1);
        }

        images.push_back(move(image));
    }

    return images;
}

Model loadModel(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла модели: " << filename << endl;
        exit(1);
    }

    Model model;
    string line;
    int line_num = 0;

    while (getline(file, line)) {
        line_num++;
        replace(line.begin(), line.end(), ',', ' ');

        stringstream ss(line);
        vector<double> row;
        double value;

        while (ss >> value) {
            row.push_back(value);
        }

        if (row.size() != 785) {
            cerr << "Ошибка: строка модели #" << line_num << " содержит " << row.size() << " значений, ожидается 785." << endl;
            exit(1);
        }

        model.push_back(move(row));
    }

    return model;
}

int predict(const vector<double>& image, const Model model) {
    vector<double> extendedImage(785);
    vector<double> scores(10, 0.0);
    extendedImage[0] = 1.0;

    for (int i = 0; i < 784; ++i) {
        extendedImage[i + 1] = image[i];
    }

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 785; ++j) {
            scores[i] += model[i][j] * extendedImage[j];
        }
    }

    return max_element(scores.begin(), scores.end()) - scores.begin();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <test.csv> <model>" << endl;
        return 1;
    }

    string testFile = argv[1];
    string modelFile = argv[2];

    vector<int> labels;

    Model images = getTestData(testFile, labels);
    Model model = loadModel(modelFile);

    int correctPredictions = 0;

    for (size_t i = 0; i < images.size(); ++i) {
        int predictedClass = predict(images[i], model);
        if (predictedClass == labels[i]) {
            correctPredictions++;
        }
    }

    double accuracy = static_cast<double>(correctPredictions) / labels.size();
    cout << accuracy << endl;

    return 0;
}