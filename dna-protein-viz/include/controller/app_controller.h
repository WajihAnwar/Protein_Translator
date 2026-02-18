#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include <string>
#include "model/translator.h"
#include "model/fasta_parser.h"
#include "view/visualizer.h"

class AppController {
public:
    AppController();

    int runFile(const std::string& filepath, bool verbose, bool visualize) const;
    int runString(const std::string& dna, bool verbose, bool visualize) const;

private:
    Translator translator_;
    FastaParser parser_;
    Visualizer visualizer_;

    void processSequence(const Sequence& seq, bool verbose, bool visualize) const;
    void printSeparator() const;
};

#endif
