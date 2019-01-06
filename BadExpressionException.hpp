
#ifndef BADEXPRESSIONEXCEPTION_HPP
#define BADEXPRESSIONEXCEPTION_HPP

#include <exception>
#include <iostream>
#include <sstream>

class BadExpressionException: public std::exception {

public:
    BadExpressionException(const char * Msg)
    {
        std::ostringstream oss;
        oss << "Expression impossible, " <<  Msg << std::endl;
        this->errorMsg = oss.str();
    }

    explicit BadExpressionException(const std::string& Msg)
    {
        std::ostringstream oss;
        oss << "Expression impossible, " <<  Msg << std::endl;
        this->errorMsg = oss.str();
    }

    virtual ~BadExpressionException() noexcept { }

    virtual const char * what() const noexcept
    {
        return this->errorMsg.c_str();
    }

private:
    std::string errorMsg;
};

#endif
