//
// Created by Ioana Gavrila on 09.06.2025.
//

#pragma once
#include <string>
#include <vector>
using namespace std;

class Member {
private:
    string name;
    int no_rev_f;  // number of revised files
    int total;     // total number of files they must revise

public:
    Member();
    Member(string name, int no_rev_f, int total) : name(name), no_rev_f(no_rev_f), total(total) {};
    ~Member() {}

    string get_name() {
        return name;
    }

    int get_no_rev_f() {
        return no_rev_f;
    }

    int get_total() {
        return total;
    }

    void set_no_rev_f(int no_rev_f) {
        this->no_rev_f = no_rev_f;
    }

    void set_total(int total) {
        this->total = total;
    }

    // Increment revised files count
    void increment_revised() {
        no_rev_f++;
    }

    // Check if member has completed all revisions
    bool is_complete() {
        return no_rev_f >= total;
    }

    // Get remaining files to revise
    int get_remaining() {
        return total - no_rev_f;
    }

    string to_string() {
        string new_s = name + " " + ::to_string(no_rev_f) + " " + ::to_string(total);
        return new_s;
    }
};

class SourceFile {
private:
    string name;
    string status;    // "revised" or "not_revised"
    string creator;
    string reviewer;

public:
    SourceFile();
    SourceFile(string name, string status, string creator, string reviewer)
        : name(name), status(status), creator(creator), reviewer(reviewer) {};
    ~SourceFile() {}

    string get_name() {
        return name;
    }

    string get_status() {
        return status;
    }

    string get_creator() {
        return creator;
    }

    string get_reviewer() {
        return reviewer;
    }

    void set_status(string status) {
        this->status = status;
    }

    void set_reviewer(string reviewer) {
        this->reviewer = reviewer;
    }

    // Check if file is revised
    bool is_revised() {
        return status == "revised";
    }

    // Check if file is unrevised (for bold display)
    bool is_unrevised() {
        return status == "not_revised";
    }
};