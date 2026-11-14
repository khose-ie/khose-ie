/**
 * @file c++-module-template.cpp
 * @author Copilot
 * @date 2026-10-27
 * @brief Strict template implementation for a deterministic MCU C++ module.
 */
#include "c++-module-template.hpp"

namespace module
{

static RetCode module_validate_config(const Config& config)
{
    if (config.timeout_ms == 0U)
    {
        return RetCode::error_invalid_argument;
    }

    return RetCode::ok;
}

RetCode Driver::initialize(const Config& config)
{
    const RetCode validation_result = module_validate_config(config);
    if (validation_result != RetCode::ok)
    {
        return validation_result;
    }

    initialized = config.enabled;
    timeout_ms = config.timeout_ms;

    return RetCode::ok;
}

RetCode Driver::deinitialize()
{
    if (!initialized)
    {
        return RetCode::error_not_initialized;
    }

    initialized = false;
    timeout_ms = module_default_timeout_ms;

    return RetCode::ok;
}

RetCode Driver::read(std::uint8_t* buffer,
                     std::size_t length,
                     std::size_t* bytes_read)
{
    if (buffer == nullptr)
    {
        return RetCode::error_invalid_argument;
    }

    if (length == 0U)
    {
        return RetCode::error_invalid_argument;
    }

    if (!initialized)
    {
        return RetCode::error_not_initialized;
    }

    if (bytes_read == nullptr)
    {
        return RetCode::error_invalid_argument;
    }

    *bytes_read = 0U;

    if (length > 0U)
    {
        buffer[0] = 0U;
        *bytes_read = 1U;
    }

    return RetCode::ok;
}

RetCode Driver::write(const std::uint8_t* buffer, std::size_t length)
{
    if (buffer == nullptr)
    {
        return RetCode::error_invalid_argument;
    }

    if (length == 0U)
    {
        return RetCode::error_invalid_argument;
    }

    if (!initialized)
    {
        return RetCode::error_not_initialized;
    }

    return RetCode::ok;
}

bool Driver::is_initialized() const noexcept
{
    return initialized;
}

} // namespace module
