#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    cout << "Hello, C++ Cloud IDE!" << endl;

    vector<string> features = {
        "Blazing fast cloud compilation",
        "Monaco Editor integration",
        "Live OpenGL virtual display",
        "Audio output (instant, no delay)"
    };

    cout << "\nFeatures:" << endl;
    for (size_t i = 0; i < features.size(); i++) {
        cout << i + 1 << ". " << features[i] << endl;
    }

    return 0;
}