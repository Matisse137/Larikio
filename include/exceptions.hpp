//
// Created by admin on 28/10/2025.
//

#ifndef LANGUAGES_EXCEPTIONS_HPP
#define LANGUAGES_EXCEPTIONS_HPP
#include <exception>
#include <string>

class Exceptions : public std::exception
{
    public:
        enum Type
        {
            NOT_SINGLE,
            FILE_NOT_FIND,
            UNKNOWN
        };

        Exceptions(Type type, const std::string& message);

        const char* what() const noexcept override;

        Type type() const noexcept;

    private:
        Type type_;
        const std::string& message;
};


#endif //LANGUAGES_EXCEPTIONS_HPP