#include <iostream>
#include <cstring>
#include "controller/app_controller.h"

static void printUsage(const char* programName) {
    std::cout << "Usage: " << programName << " <input.fasta> [options]\n"
              << "       " << programName << " -s <DNA_STRING> [options]\n\n"
              << "Options:\n"
              << "  -h, --help       Show this help message\n"
              << "  -v, --verbose    Show mRNA, GC content, and detailed stats\n"
              << "  -V, --viz        Show full ASCII visualization\n"
              << "  -s <STRING>      Translate a DNA string directly\n\n"
              << "Examples:\n"
              << "  " << programName << " sequences.fasta\n"
              << "  " << programName << " sequences.fasta -v\n"
              << "  " << programName << " -s ATGAAAGGG -V\n"
              << "  " << programName << " -s ATGAAAGGG -v -V\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    bool verbose = false;
    bool visualize = false;
    bool useString = false;
    const char* input = nullptr;

    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "-h") == 0 || std::strcmp(argv[i], "--help") == 0) {
            printUsage(argv[0]);
            return 0;
        }
        if (std::strcmp(argv[i], "-v") == 0 || std::strcmp(argv[i], "--verbose") == 0) {
            verbose = true;
            continue;
        }
        if (std::strcmp(argv[i], "-V") == 0 || std::strcmp(argv[i], "--viz") == 0) {
            visualize = true;
            continue;
        }
        if (std::strcmp(argv[i], "-s") == 0) {
            useString = true;
            if (i + 1 < argc) {
                input = argv[++i];
            } else {
                std::cerr << "Error: -s requires a DNA string argument\n";
                return 1;
            }
            continue;
        }
        if (input == nullptr) {
            input = argv[i];
        } else {
            std::cerr << "Error: unexpected argument '" << argv[i] << "'\n";
            return 1;
        }
    }

    if (input == nullptr) {
        std::cerr << "Error: no input provided\n";
        printUsage(argv[0]);
        return 1;
    }

    AppController controller;

    if (useString)
        return controller.runString(input, verbose, visualize);
    else
        return controller.runFile(input, verbose, visualize);
}
