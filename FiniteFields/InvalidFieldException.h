//
// Created by Mikhail Kiselyov on 27.02.2023.
//

#ifndef FINITEFIELDS_MAIN_INVALIDFIELDEXCEPTION_H
#define FINITEFIELDS_MAIN_INVALIDFIELDEXCEPTION_H

#include <exception>

namespace FiniteFields {

    class InvalidFieldException : std::exception {
    public:
        const char *what() {
            return "cannot perform this operation on elements from different Finite Fields";
        }

    };

} // FiniteFields

#endif //FINITEFIELDS_MAIN_INVALIDFIELDEXCEPTION_H
