
#include <QtWidgets/QApplication>
#include "./UI/ui.h"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        string membersFile = "/Users/ioanagavrila/CLionProjects/EXAMEN_SCRIS_CODE_REVISION/members.txt";
        string sourceFilesFile = "/Users/ioanagavrila/CLionProjects/EXAMEN_SCRIS_CODE_REVISION/sourcefiles.txt";

        CodeRevisionApp app(argc, argv, membersFile, sourceFilesFile);

        return app.run();
    }
    catch (...) {
        std::cerr << "Error occurred" << std::endl;
        return -1;
    }
}