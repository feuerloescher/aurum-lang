/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "CodeLocation.hpp"

using namespace AST;

CodeLocation CodeLocation::none = {"", 0, 0, 0};

CodeLocation::CodeLocation(std::string filename, unsigned int line,
    unsigned int beginChar, unsigned int endChar)
    : filename(filename), line(line), beginChar(beginChar), endChar(endChar) {
}

std::string CodeLocation::getFilename() {
    return filename;
}

unsigned int CodeLocation::getLine() {
    return line;
}

unsigned int CodeLocation::getBeginChar() {
    return beginChar;
}

unsigned int CodeLocation::getEndChar() {
    return endChar;
}
