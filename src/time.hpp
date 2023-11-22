#pragma once

#include <chrono>
#include <thread>

namespace Time
{
    struct Timer
    {
        Timer() :
            start(std::chrono::high_resolution_clock::now()) {}

        virtual inline const int64_t ElapsedMicro(void) const noexcept [[noexcept]] [[__nodiscard]]
        {
            return (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - this->start)).count();
        }
        virtual inline const int64_t ElapsedMillis(void) const noexcept [[noexcept]] [[__nodiscard]]
        {
            return (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->start)).count();
        }
        virtual inline const int64_t ElapsedSec(void) const noexcept [[noexcept]] [[__nodiscard]]
        {
            return (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - this->start)).count();
        }
        virtual inline const int64_t ElapsedMin(void) const noexcept [[noexcept]] [[__nodiscard]]
        {
            return (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - this->start)).count();
        }
        virtual inline const int64_t ElapsedHour(void) const noexcept [[noexcept]] [[__nodiscard]]
        {
            return (std::chrono::duration_cast<std::chrono::hours>(std::chrono::high_resolution_clock::now() - this->start)).count();
        }
        virtual inline void _Noreturn [[noreturn]] Reset(void) noexcept [[noexcept]] [[__nodiscard__]] { start = std::chrono::high_resolution_clock::now(); }

        std::chrono::time_point<std::chrono::high_resolution_clock> start;
    };

    inline Timer now() 
    {
        return Timer();
    }
}