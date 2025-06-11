//
// Created by Ioana Gavrila on 09.06.2025.
//

#include "service.h"
#include <sstream>
#include <algorithm>
#include <iostream>

CodeRevisionService::CodeRevisionService(const string& membersFile, const string& sourceFilesFile)
    : membersFileName(membersFile), sourceFilesFileName(sourceFilesFile) {
    loadData();
}

CodeRevisionService::~CodeRevisionService() {
    saveData();
}

void CodeRevisionService::loadData() {
    loadMembersFromFile();
    loadSourceFilesFromFile();
}

void CodeRevisionService::saveData() {
    saveMembersToFile();
    saveSourceFilesToFile();
}

void CodeRevisionService::loadMembersFromFile() {
    ifstream file(membersFileName);
    if (!file.is_open()) {
        return; // File doesn't exist, start with empty list
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string name;
        int no_rev_f, total;

        if (iss >> name >> no_rev_f >> total) {
            members.push_back(Member(name, no_rev_f, total));
        }
    }
    file.close();
}

void CodeRevisionService::loadSourceFilesFromFile() {
    ifstream file(sourceFilesFileName);
    if (!file.is_open()) {
        return; // File doesn't exist, start with empty list
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string name, status, creator, reviewer;

        if (iss >> name >> status >> creator >> reviewer) {
            // Handle case where reviewer might be empty
            if (reviewer == "none") {
                reviewer = "";
            }
            sourceFiles.push_back(SourceFile(name, status, creator, reviewer));
        }
    }
    file.close();
}

void CodeRevisionService::saveMembersToFile() {
    ofstream file(membersFileName);
    if (!file.is_open()) {
        return;
    }

    for (auto& member : members) {
        file << member.get_name() << " " << member.get_no_rev_f() << " " << member.get_total() << endl;
    }
    file.close();
}

void CodeRevisionService::saveSourceFilesToFile() {
    ofstream file(sourceFilesFileName);
    if (!file.is_open()) {
        return;
    }

    for (auto& sourceFile : sourceFiles) {
        string reviewer = sourceFile.get_reviewer().empty() ? "none" : sourceFile.get_reviewer();
        file << sourceFile.get_name() << " " << sourceFile.get_status() << " "
             << sourceFile.get_creator() << " " << reviewer << endl;
    }
    file.close();
}

Member* CodeRevisionService::findMemberByName(string& name) {
    for (auto& member : members) {
        if (member.get_name() == name) {
            return &member;
        }
    }
    return nullptr;
}

int CodeRevisionService::findMemberIndexByName(string& name) {
    for (size_t i = 0; i < members.size(); i++) {
        if (members[i].get_name() == name) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

vector<Member> CodeRevisionService::getAllMembers() {
    return members;
}

Member CodeRevisionService::getMemberByName(string& name) {
    for (auto& member : members) {
        if (member.get_name() == name) {
            return member;
        }
    }
    return Member(); // Return empty member if not found
}

bool CodeRevisionService::memberExists(string& name) {
    return findMemberIndexByName(name) != -1;
}

vector<SourceFile> CodeRevisionService::getAllSourceFiles() {
    return sourceFiles;
}

vector<SourceFile> CodeRevisionService::getSourceFilesByCreator(string& creator) {
    vector<SourceFile> result;
    for (auto& file : sourceFiles) {
        if (file.get_creator() == creator) {
            result.push_back(file);
        }
    }

    // Sort by file name
    sort(result.begin(), result.end(), [](SourceFile& a, SourceFile& b) {
        return a.get_name() < b.get_name();
    });

    return result;
}

bool CodeRevisionService::addSourceFile(string& fileName, string& creator) {
    // Check if file name is empty
    if (fileName.empty()) {
        return false;
    }

    // Check if file already exists
    if (sourceFileExists(fileName)) {
        return false;
    }

    // Check if creator exists as a member
    if (!memberExists(creator)) {
        return false;
    }

    // Add the new file with status "not_revised"
    sourceFiles.push_back(SourceFile(fileName, "not_revised", creator, ""));

    // Save to file
    saveSourceFilesToFile();

    return true;
}

bool CodeRevisionService::sourceFileExists(string& fileName) {
    for (auto& file : sourceFiles) {
        if (file.get_name() == fileName) {
            return true;
        }
    }
    return false;
}

bool CodeRevisionService::canReviseFile(string& fileName, string& revisingProgrammer) {
    // Find the file
    for (auto& file : sourceFiles) {
        if (file.get_name() == fileName) {
            // Check if file is not revised and revising programmer is not the creator
            return (file.get_status() == "not_revised" && file.get_creator() != revisingProgrammer);
        }
    }
    return false;
}

bool CodeRevisionService::reviseFile(string& fileName, string& revisingProgrammer) {
    if (!canReviseFile(fileName, revisingProgrammer)) {
        return false;
    }

    // Find and update the file
    for (auto& file : sourceFiles) {
        if (file.get_name() == fileName) {
            file.set_status("revised");
            file.set_reviewer(revisingProgrammer);

            // Update the revising programmer's statistics
            Member* member = findMemberByName(revisingProgrammer);
            if (member != nullptr) {
                member->increment_revised();
            }

            // Save changes
            saveData();

            // Notify observers
            notifyObservers();

            return true;
        }
    }
    return false;
}

map<string, pair<int, int>> CodeRevisionService::getProgrammerStatistics() {
    map<string, pair<int, int>> stats;

    for (auto& member : members) {
        stats[member.get_name()] = make_pair(member.get_no_rev_f(), member.get_total());
    }

    return stats;
}

vector<string> CodeRevisionService::getCompletedProgrammers() {
    vector<string> completed;

    for (auto& member : members) {
        if (member.is_complete()) {
            completed.push_back(member.get_name());
        }
    }

    return completed;
}

void CodeRevisionService::notifyObservers() {
    // This method would notify UI observers about changes
    // Implementation depends on the specific observer pattern used
    // For now, it's a placeholder for the UI to hook into
}