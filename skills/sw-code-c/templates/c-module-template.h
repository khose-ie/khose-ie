/**
 * @file c-module-template.h
 * @author Copilot
 * @date 2026-10-22
 * @brief Template header for an MCU C module interface.
 */
#ifndef _MODULE_NAME_H_
#define _MODULE_NAME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Default timeout value in milliseconds.
 */
#define MODULE_TIMEOUT_DEFAULT_MS 100U

/**
 * @brief Check whether a pointer is valid.
 * @param ptr Pointer to validate.
 * @return 1 when pointer is valid, 0 otherwise.
 */
#define module_is_pointer_valid(ptr) ((ptr) != NULL)

/**
 * @brief Check whether a length value is non-zero.
 * @param length Length value to validate.
 * @return 1 when length is valid, 0 otherwise.
 */
#define module_is_length_valid(length) (((length) > 0U) ? 1U : 0U)

/**
 * @brief Module return codes.
 */
typedef enum
{
    MODULE_RET_OK = 0,
    MODULE_RET_ERR_INVALID_ARG,
    MODULE_RET_ERR_TIMEOUT,
    MODULE_RET_ERR_IO
} moduleRet_t;

/**
 * @brief Module configuration.
 */
typedef struct
{
    uint32_t timeout_ms;
} moduleCfg_t;

/**
 * @brief Initialize the module.
 * @param cfg Module configuration.
 * @return moduleRet_t Module return code.
 */
moduleRet_t module_initialize(const moduleCfg_t* cfg);

/**
 * @brief Deinitialize the module.
 * @return moduleRet_t Module return code.
 */
moduleRet_t module_deinitialize(void);

/**
 * @brief Read data from the module.
 * @param buf Output data buffer.
 * @param len Buffer capacity in bytes.
 * @param out_len Number of bytes actually read.
 * @return moduleRet_t Module return code.
 */
moduleRet_t module_read(uint8_t* buf, size_t len, size_t* out_len);

/**
 * @brief Write data to the module.
 * @param buf Input data buffer.
 * @param len Input data length in bytes.
 * @return moduleRet_t Module return code.
 */
moduleRet_t module_write(const uint8_t* buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* _MODULE_NAME_H_ */
