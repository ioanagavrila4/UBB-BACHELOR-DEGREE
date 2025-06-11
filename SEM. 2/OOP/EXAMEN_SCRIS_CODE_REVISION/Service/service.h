//
// Created by Ioana Gavrila on 09.06.2025.
//

#pragma once
#include "../Domain/domain.h"
#include <vector>
#include <string>
#include <fstream>
#include <map>

using namespace std;

class CodeRevisionService {
private:
    vector<Member> members;
    vector<SourceFile> sourceFiles;
    string membersFileName;
    string sourceFilesFileName;

    // Helper methods
    void loadMembersFromFile();
    void loadSourceFilesFromFile();
    void saveMembersToFile();
    void saveSourceFilesToFile();
    Member* findMemberByName(string& name);
    int findMemberIndexByName(string& name);

public:
    CodeRevisionService(const string& membersFile, const string& sourceFilesFile);
    ~CodeRevisionService();

    // File operations
    void loadData();
    void saveData();

    // Member operations
    vector<Member> getAllMembers();
    Member getMemberByName(string& name);
    bool memberExists(string& name);

    // Source file operations
    vector<SourceFile> getAllSourceFiles();
    vector<SourceFile> getSourceFilesByCreator(string& creator);
    bool addSourceFile(string& fileName, string& creator);
    bool sourceFileExists(string& fileName);

    // Revision operations
    bool canReviseFile(string& fileName, string& revisingProgrammer);
    bool reviseFile(string& fileName, string& revisingProgrammer);

    // Statistics
    map<string, pair<int, int>> getProgrammerStatistics(); // name -> (revised, total)
    vector<string> getCompletedProgrammers();

    // Observer pattern - notify when changes occur
    void notifyObservers();
};