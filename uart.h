/* 
 * File:   uart.h
 * Author: MD. Faridul Islam
 * PIC16F18856 Hardware UART Library
 * Created on March 10, 2024, 4:07 PM
 */

void     UART_Config_GPIO(void);
void     UART_Config_Clock(void);
void     UART_Config_BAUD_Rate(uint32_t baud_rate);
void     UART_Config_Transmitter(void);
void     UART_Config_Receiver(void);
void     UART_Config_Receiver_Interrupt(void);
void     UART_Transmit_Byte(uint8_t val);
uint8_t  UART_Receive_Byte(void);
uint32_t UART_Reference_Time(void);
void     UART_Struct_Init(void);
void     UART_Transmit_Byte_Hex(uint32_t val);
void     UART_Transmit_Byte_Bin(uint32_t val);
void     UART_Transmit_New_Line(void);
void     UART_Transmit_Space(void);
void     UART_Transmit_Text(char *str);
void     UART_Transmit_Text_NL(char *str);
void     UART_Determine_Digit_Numbers(uint32_t num);
void     UART_Transmit_Number_Digits(void);
void     UART_Transmit_Number(int32_t num);
void     UART_Transmit_Number_NL(int32_t num);
void     UART_Transmit_Number_SP(int32_t num);
void     UART_Transmit_Fixed_Digit_Number(int32_t num, uint8_t digits);
void     UART_Print_Debug_Data(int *data_in);
uint8_t  UART_Read_From_Buffer(uint16_t index);
uint16_t UART_Current_Buffer_Index(void);
uint16_t UART_Current_Read_Index(void);
uint16_t UART_Bytes_Available_To_Read(void);
uint8_t  UART_Read(void);
uint8_t  UART_Last_Received_Byte(void);
void     UART_Flush_Buffer(void);
uint32_t UART_Last_Byte_Recevied_Time_Stamp(void);
void     UART_ISR_Executables(void);
void     UART_Init(uint32_t baud);
void     UART_ISR_Routine(void);

