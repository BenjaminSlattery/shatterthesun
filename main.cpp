#include "masterheader.h"
#include <iostream>
#include <string>
#include <vector>
#include "screen.h"

using namespace std;

int main() {
    cout << "Hello, C++ Cloud IDE!" << endl;

    vector<string> features = {
        "Blazing fast cloud compilation",
        "Monaco Editor integration",
        "Live OpenGL virtual display",
        "Audio output (instant, no delay)"
    };

    Screen *screen = new Screen();
    //screen->Update();
    //screen->Print();

    int name;

    cin >> name;

    cout << name;

    return 0;
}