#ifndef __HW1_H__
#define __HW1_H__

#include <stdint.h>
#include "stm32f4xx_hal.h"

/* Device ID */
#define TIDS_DEVICE_ID_VALUE    0xA0

/* I2C slave addresses */
#define TIDS_I2C_ADDRESS_0      0x3F
#define TIDS_I2C_ADDRESS_1      0x38


/* Register address definitions */

// ****************************
// Part 1-1:
// Define the register address of the register DEVICE_ID and CTRL. Please refer
// to the register map in the manual. The naming of macro should be in the form
// TIDS_XXXX_REG.

#define TIDS_STATUS_REG         0x05    // STATUS register
#define xxx                     ...     // DEVICE_ID register
#define TIDS_CTRL_REG           ...     // CTRL register

// ****************************




/* Register type definitions using struct */
typedef struct
{
  uint8_t busy               : 1;   /**< BUSY: Temperature conversion status (0: data conversion complete; 1: data conversion in progress) */
  uint8_t upperLimitExceeded : 1;   /**< OVER_THL: Temperature upper limit status (0: temperature is below upper limit or disabled; 1: temperature exceeded high limit */
  uint8_t lowerLimitExceeded : 2;   /**< UNDER_TLL: Temperature lower limit status (0: temperature is above lower limit or disabled; 1: temperature exceeded low limit */
  uint8_t reserved01         : 5;   /**< Must be set to 0 */
} TIDS_status_t;


// ****************************
// Part 2-1:
// Please use struct to define each bit field of the CTRL register. The name of
// each bit field is given as follows. Please refer to the datasheet to fill in
// the bit width of each bit field.

typedef struct
{
  uint8_t oneShotBit      : ?;      /**< Trigger a single measurement by setting this bit to 1; Bit is automatically reset to 0 */
  uint8_t reserved01      : 1;      /**< Must be set to 0 */
  uint8_t freeRunBit      : ?;      /**< FREERUN: 1: Enable continuous mode, 0: Disable continuous mode */
  uint8_t autoAddIncr     : ?;      /**< IF_ADD_INC: Register address automatically incremented during a multiple byte access with I2C interface. Default value 1 (0: disable; 1: enable) */
  uint8_t outputDataRate  : ?;      /**< AVG[1:0]: Output data rate in continuous mode. Default '00' */
  uint8_t blockDataUpdate : ?;      /**< BDU: Block data update. 0: continuous update; 1: output registers are not updated until both MSB and LSB have been read */
  uint8_t reserved02      : 1;      /**< Must be set to 0 */
} TIDS_ctrl_t;

// ****************************




/* Definitions using enum */
typedef enum {                      // Refer to chapter 6.5.
    TIDS_PowerDown,
    TIDS_SingleConversion,
    TIDS_Continuous
} TIDS_operatingMode_t;


// ****************************
// Part 3-1:
// Define the enum for different output data rate. Please refer to the datasheet.

typedef enum {
    TIDS_outputDataRate_25Hz
    // ...
} TIDS_outputDataRate_t;

// ****************************


/* Class definitions */
class WSEN_TIDS
{
public:
    // Construtor
    WSEN_TIDS(I2C_HandleTypeDef* _i2c_handler, uint8_t SAO);

    HAL_StatusTypeDef getDeviceID(uint8_t *device_ID);
    HAL_StatusTypeDef setOperatingMode(TIDS_operatingMode_t mode);
    HAL_StatusTypeDef setOutputDataRate(TIDS_outputDataRate_t odr);

private:
    // I2C Interface
    I2C_HandleTypeDef* i2c_handler;
    uint8_t i2c_device_addr;
    const uint16_t i2cMemAddSize = I2C_MEMADD_SIZE_8BIT;

    // ReadReg(): Read register via I2C
    // - regAddr: The address of the register to be read
    // - numBytesToRead: The number of bytes to be read
    // - buf: A pointer to the buffer that records the read data. Note: the array size should be larger than numBytesToRead.
    inline HAL_StatusTypeDef ReadReg(uint16_t regAddr, uint16_t numBytesToRead, uint8_t *buf);

    // WriteReg(): Write register via I2C
    // - regAddr: The address of the register to be written
    // - numBytesToRead: The number of bytes to be written
    // - buf: A pointer to a buffer that records the data to be written
    inline HAL_StatusTypeDef WriteReg(uint16_t regAddr, uint16_t numBytesToWrite, uint8_t *data);
};

#endif