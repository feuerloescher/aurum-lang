/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_CODELOCATION_HPP
#define AUC_CODELOCATION_HPP

#include "common.hpp"

#include <string>

namespace AST {

class CodeLocation {

protected:
    std::string filename;
    unsigned int line;
    unsigned int beginChar, endChar;

public:
    CodeLocation(std::string filename, unsigned int line,
            unsigned int beginChar, unsigned int endChar);
    virtual ~CodeLocation() {};

    std::string getFilename();
    unsigned int getLine();
    unsigned int getBeginChar();
    unsigned int getEndChar();

    static CodeLocation none;

}; // class CodeLocation

} // namespace AST

#endif // AUC_CODELOCATION_HPP
