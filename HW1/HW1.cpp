#include "HW1.h"

static const uint32_t I2C_TIMEOUT = 100;

WSEN_TIDS::WSEN_TIDS(I2C_HandleTypeDef* _i2c_handler, uint8_t SAO): i2c_handler(_i2c_handler)
{
    i2c_device_addr = (SAO == 0) ? TIDS_I2C_ADDRESS_0 : TIDS_ADDRESS_I2C_1;
}

HAL_StatusTypeDef WSEN_TIDS::getDeviceID(uint8_t *device_ID)
{
    // ****************************
    // Part 1-2:
    // Complete this function using the provided function ReadReg(). Please 
    // refer to the declaration and implementation of ReadReg(). Also, you can
    // take a look at part 2-2.



    // ****************************
}

HAL_StatusTypeDef WSEN_TIDS::setOperatingMode(TIDS_operatingMode_t mode)
{
    // ****************************
    // Part 2-2:
    // Complete this function using the provided functions ReadReg() and
    // WriteReg(). Please refer to the definition of TIDS_operatingMode_t and
    // chapter 6 in the datasheet. For coding, you can refer to the code in the
    // following, my code on our github, or sensorSDK of WE.

    TIDS_ctrl_t ctrl_reg;
    HAL_StatusTypeDef status;

    switch (mode)
    {
        case TIDS_PowerDown: {              // Power-down mode
            status = ReadReg(TIDS_CTRL_REG, 1, (uint8_t *) &ctrl_reg);
            if (status != HAL_OK)
                return status;
            ctrl_reg.freeRun = 0;
            return WriteReg(TIDS_CTRL_REG, 1, (uint8_t *) &ctrl_reg);
        } break;

        case TIDS_SingleConversion: {       // Single conversion mode
            
            // Please complete this block.

        } break;

        case TIDS_Continuous: {             // Continuous mode

            // Please complete this block.

        } break;


        default: return HAL_ERROR;
    }

    // ****************************
}

HAL_StatusTypeDef WSEN_TIDS::setOutputDataRate(TIDS_outputDataRate_t odr)
{
    // ****************************
    // Part 3-2: Complete this function. It is similar to part 2.




    // ****************************
}


inline HAL_StatusTypeDef WSEN_TIDS::ReadReg(uint16_t regAddr, uint16_t numBytesToRead, uint8_t *buf)
{
    return HAL_I2C_Mem_Read(i2c_handler, i2c_device_addr, regAddr, i2cMemAddSize, buf, numBytesToRead, I2C_TIMEOUT);
}

inline HAL_StatusTypeDef WSEN_TIDS::WriteReg(uint16_t regAddr, uint16_t numBytesToWrite, uint8_t *data)
{
    return HAL_I2C_Mem_Write(i2c_handler, i2c_device_addr, regAddr, i2cMemAddSize, data, numBytesToWrite, I2C_TIMEOUT);
}

// I recommend you to read the reference to understand how to use HAL_I2C_Mem_Read()/HAL_I2C_Mem_Write().


