#include "User/Myuart.h"

void initUART0()
{
    //ʹ��UART����
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    //GPIOģʽ���� PA0--RX PA1--TX
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    //GPIO��UARTģʽ����
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    //UARTЭ������ ������115200 8λ 1ֹͣλ  ��У��λ
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));
    //UART����FIFO Ĭ��FIFO LevelΪ4/8 �Ĵ�����8�ֽں�����ж�
    //���ú����1λ�Ͳ����ж�
    UARTFIFODisable(UART0_BASE);
    //ʹ��UART0�ж�
    IntEnable(INT_UART0);
    //ʹ��UART0�����ж�
    UARTIntEnable(UART0_BASE,UART_INT_RX);
    //UART�жϵ�ַע��
    UARTIntRegister(UART0_BASE,UART0IntHandler);
    //ȫ���ж�ʹ��
    IntMasterEnable();
}
//UART7�жϺ���
void UART0IntHandler(void)
{
    //��ȡ�жϱ�־ ԭʼ�ж�״̬ �������жϱ�־
    //uint32_t flag = UARTIntStatus(UART0_BASE,0);
    //��ȡ�жϱ�־ ԭʼ�ж�״̬ �����жϱ�־
    uint32_t flag = UARTIntStatus(UART0_BASE,1);
    //����жϱ�־
    UARTIntClear(UART0_BASE,flag);
    if(flag&UART_INT_RX)
        //UARTCharsAvail()//�ж�FIFO�Ƿ�������
        while(UARTCharsAvail(UART0_BASE))
        {
            unsigned char data = UARTCharGet(UART0_BASE); //���汾�ν�������
            UARTCharPut(UART0_BASE,data);
        }
}
