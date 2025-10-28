//
// Created by admin on 28/10/2025.
//

#include "exceptions.hpp"

Exceptions::Exceptions(Type type, const std::string& message) : type_(type), message(message)
{}

const char * Exceptions::what() const noexcept
{
    return message.c_str();
}

Exceptions::Type Exceptions::type() const noexcept
{
    return type_;
}