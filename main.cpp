#include "Runtime.h"
#include "Compare.h"
#include "CreateEle.h"
#include "GenData.h"
#include "Mode.h"

int main(int argc, char* argv[]) {

    string mode = argv[1];
    if (mode == "-a") {
        RunAlgorithmMode(argc, argv);
    }
    else if (mode == "-c") {
        RunComparisonMode(argc, argv);
    }
    else {
        cout << "Unknown mode: " << mode << endl;
        return 1;
    }

    return 0;
}


