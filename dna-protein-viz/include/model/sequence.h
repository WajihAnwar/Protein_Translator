#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>

class Sequence {
public:
    Sequence(const std::string& dna,
             const std::string& name = "",
             const std::string& description = "");
    Sequence();

    std::string getDNA() const;
    std::string getProtein() const;
    std::string getName() const;
    std::string getDescription() const;
    int getLength() const;

    void setProtein(const std::string& protein);
    void setDNA(const std::string& dna);

    bool isValid() const;

private:
    std::string dna_;
    std::string protein_;
    std::string name_;
    std::string description_;
};

#endif
