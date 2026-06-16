#pragma once

#include <iostream>

#include "misc.hpp"

namespace TheeCode {
    enum class ErrorType {

        SyntaxError,
        MathError,
        TypeError,

        PreruntimeError,
        UnimplementedError, // Will likely be used a lot at this stage

        CannotOpenFileError,
    };

    inline std::string errortype_to_string(ErrorType err) {
        switch (err) {
            case ErrorType::SyntaxError: return "[TheeCode].SyntaxError";
            case ErrorType::MathError: return "[TheeCode].MathError";
            case ErrorType::TypeError: return "[TheeCode].TypeError";
            case ErrorType::CannotOpenFileError: return "[TheeCode].CannotOpenFileError";
            case ErrorType::PreruntimeError: return "[TheeCode].PreruntimeError";
            default:
                return "[TheeCode].UndefinedError";
        }
    }

    inline void raise_error(ErrorType err, std::string message) {

        std::cerr << RED << errortype_to_string(err) << ": " << message << RESET << std::endl;
        std::_Exit(1);

    }
}