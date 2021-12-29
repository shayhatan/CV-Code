//
// Created by USER on 10/11/2021.
//

#ifndef EX2_MTM_EXCEPTIONS_H
#define EX2_MTM_EXCEPTIONS_H

#include <exception>

namespace mtm {
    class Exceptions : public std::exception {
    };

class IllegalArgument : public mtm::Exceptions {
    public:
        const char *what() const noexcept override;
    };

    class IllegalCell : public mtm::Exceptions {
    public:
        const char *what() const noexcept override;
    };

    class CellEmpty : public mtm::Exceptions {
    public:
        const char *what() const noexcept override;
    };

    class MoveTooFar : public mtm::Exceptions {
    public:
        const char *what() const noexcept override;
    };

    class CellOccupied : public mtm::Exceptions {
    public:
        const char *what() const noexcept override;
    };

    class OutOfRange : public mtm::Exceptions {
    public:
        const char *what() const noexcept override;
    };

    class OutOfAmmo : public mtm::Exceptions {
    public:
        const char *what() const noexcept override;
    };

    class IllegalTarget : public mtm::Exceptions {
    public:
        const char *what() const noexcept override;
    };

}

#endif //EX2_MTM_EXCEPTIONS_H
