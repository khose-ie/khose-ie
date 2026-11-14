//! Module overview for the embedded driver.

use core::ptr::NonNull;

use crate::error::{ErrValue, RetValue};

/// Public module wrapper or handle type.
pub struct Module
{
    handle: NonNull<ModuleHandle>,
}

impl Module
{
    /// Creates a new module wrapper around an existing peripheral handle.
    pub fn new(handle: *mut ModuleHandle) -> RetValue<Self>
    {
        Ok(Self { handle: NonNull::new(handle).ok_or(ErrValue::Param)?, })
    }

    /// Reads the current status of the device.
    pub fn status(&self) -> RetValue<u32>
    {
        Ok(0)
    }

    /// Performs the main driver operation.
    pub fn operate(&self, data: &[u8], timeout_ms: u32) -> RetValue<()>
    {
        if data.is_empty() {
            return Err(ErrValue::Param);
        }

        // Use the HAL or peripheral API here.
        Ok(())
    }
}

/// Internal handle type exposed by a vendor or HAL layer.
pub struct ModuleHandle;

/// Module-local helper with narrow scope.
fn module_validate_data(data: &[u8]) -> Result<(), ErrValue>
{
    if data.is_empty() {
        return Err(ErrValue::Param);
    }

    Ok(())
}
