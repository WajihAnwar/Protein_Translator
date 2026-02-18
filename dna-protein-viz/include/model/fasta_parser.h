#ifndef FASTA_PARSER_H
#define FASTA_PARSER_H

#include <string>
#include <vector>
#include "model/sequence.h"

class FastaParser {
public:

//Parse Fasta File or String into Sequence Objects
    std::vector<Sequence> parseFile(const std::string& filepath) const;
    Sequence parseString(const std::string& dna) const;

private:
    void parseHeader(const std::string& line,
                     std::string& name,
                     std::string& description) const;
};

#endif
