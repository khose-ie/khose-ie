/**
 * @file c++-module-template.hpp
 * @author Copilot
 * @date 2026-10-27
 * @brief Strict template header for a deterministic MCU C++ module interface.
 */
#ifndef _MODULE_NAME_HPP_
#define _MODULE_NAME_HPP_

#include <cstddef>
#include <cstdint>

namespace module
{

/**
 * @brief Operation status values for the module.
 */
enum class RetCode : std::uint8_t
{
    ok = 0U,
    error_invalid_argument,
    error_timeout,
    error_io,
    error_busy,
    error_not_initialized
};

/**
 * @brief Hardware and runtime configuration for the module.
 */
struct Config
{
    std::uint32_t timeout_ms = 100U;
    bool enabled = true;
};

/**
 * @brief Default timeout value in milliseconds.
 */
inline constexpr std::uint32_t module_default_timeout_ms = 100U;

/**
 * @brief Driver interface for the module.
 */
class Driver final
{
public:
    /**
     * @brief Construct a driver instance.
     */
    Driver() = default;

    /**
     * @brief Destroy the driver instance.
     */
    ~Driver() = default;

    /**
     * @brief Initialize the module with the provided configuration.
     * @param config Module configuration.
     * @return RetCode Operation status.
     */
    RetCode initialize(const Config& config);

    /**
     * @brief Deinitialize the module and release any hardware state.
     * @return RetCode Operation status.
     */
    RetCode deinitialize();

    /**
     * @brief Read data from the module into a caller-provided buffer.
     * @param buffer Output buffer for the read bytes.
     * @param length Capacity of the buffer in bytes.
     * @param bytes_read Number of bytes actually written to the buffer.
     * @return RetCode Operation status.
     */
    RetCode read(std::uint8_t* buffer,
                              std::size_t length,
                              std::size_t* bytes_read);

    /**
     * @brief Write data to the module from a caller-provided buffer.
     * @param buffer Input data buffer.
     * @param length Number of bytes to write.
     * @return RetCode Operation status.
     */
    RetCode write(const std::uint8_t* buffer, std::size_t length);

    /**
     * @brief Check whether the module is currently initialized.
     * @return true when initialized, false otherwise.
     */
    bool is_initialized() const noexcept;

private:
    /**
     * @brief Tracks whether the module has been initialized.
     */
    bool initialized = false;

    /**
     * @brief Current timeout value in milliseconds.
     */
    std::uint32_t timeout_ms = module_default_timeout_ms;
};

} // namespace module

#endif // _MODULE_NAME_HPP_
