/*******************************************************************************
 * Copyright 2019-2021 Microchip FPGA Embedded Systems Solutions.
 *
 * SPDX-License-Identifier: MIT
 *
 * Application code running on U54_1
 *
 * Example project demonstrating the use of polled and interrupt driven
 * transmission and reception over MMUART. Please refer README.md in the root
 * folder of this example project
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "mpfs_hal/mss_hal.h"
#include "drivers/mss/mss_mmuart/mss_uart.h"
#include "inc/common.h"
#include "inc/string_t.h"
#include "inc/pptlang.h"

/******************************************************************************
 * Instruction message. This message will be transmitted over the UART when
 * the program starts.
 *****************************************************************************/

const uint8_t g_message1[] = "POLARFIRE SOC MSS MMUART PPL REPL\r\n\r\n";

const uint8_t g_message2[] =
        "This program is run from u54_1\r\n\
        \r\n\
Type 0  Show hart 1 debug message\r\n\
Type 1  Show this menu\r\n\
Type 2  Send message using polled method\r\n\
Type 3  send message using interrupt method\r\n\
";

const uint8_t polled_message[] =
        "This message has been transmitted using polled method. \r\n";

const uint8_t intr_message[] =
        " This message has been transmitted using interrupt method. \r\n";


#define RX_BUFF_SIZE    64U
uint8_t g_rx_buff[RX_BUFF_SIZE] = { 0 };
volatile uint32_t count_sw_ints_h1 = 0U;
volatile uint8_t g_rx_size = 0U;
static volatile uint32_t irq_cnt = 0;

ppl_t   g_ppl_vm;
string_t g_line;
string_t g_msg;

bool g_line_ready = false;
bool g_echo = true;



void string_print(string_t *str)
{
    if (str == NULL || str->len == 0) return;
    MSS_UART_polled_tx(&g_mss_uart1_lo, str->txt, str->len);
}


// =====================================================================
// =====================================================================

void rx_append(void) {
    string_append(&g_line, g_rx_buff, g_rx_size);
    if (g_rx_buff[0] == '\n' || g_rx_buff[0] == '\r') {
        g_line_ready = true;
    }
}


void rx_echo(void) {
    if (g_echo && g_rx_size) {
        MSS_UART_polled_tx(&g_mss_uart1_lo, &g_rx_buff[g_rx_size-1], 1);
    }
}


/* This is the handler function for the UART RX interrupt.
 * In this example project UART0 local interrupt is enabled on hart0.
 */
void uart1_rx_handler(mss_uart_instance_t *this_uart) {
    static int prev_rx_size = 0;
    uint32_t hart_id = read_csr(mhartid);
    int8_t info_string[50];

    /* This will execute when interrupt from hart 1 is raised */
    g_rx_size = MSS_UART_get_rx(this_uart, g_rx_buff, sizeof(g_rx_buff));
    rx_echo();
    rx_append();
    irq_cnt++;
    // sprintf(info_string, "UART1 Interrupt count = 0x%x \r\n\r\n", irq_cnt);
    // MSS_UART_polled_tx(&g_mss_uart1_lo, info_string, strlen(info_string));
}


/* Main function for the hart1(U54 processor).
 * Application code running on hart1 is placed here.
 * MMUART1 local interrupt is enabled on hart1.
 * In the respective U54 harts, local interrupts of the corresponding MMUART
 * are enabled. e.g. in U54_1.c local interrupt of MMUART1 is enabled. */

void u54_1(void) {
    uint64_t mcycle_start = 0U;
    uint64_t mcycle_end = 0U;
    uint64_t delta_mcycle = 0U;
    uint64_t hartid = read_csr(mhartid);

    string_init(&g_line, "");

    clear_soft_interrupt();
    set_csr(mie, MIP_MSIP);

#if (IMAGE_LOADED_BY_BOOTLOADER == 0)

    /* Put this hart in WFI. */
    do
    {
        __asm("wfi");
    }while(0 == (read_csr(mip) & MIP_MSIP));

    /* The hart is now out of WFI, clear the SW interrupt. Here onwards the
     * application can enable and use any interrupts as required */

    clear_soft_interrupt();

#endif

    __enable_irq();

    /* Bring all the MMUARTs out of Reset */
    (void) mss_config_clk_rst(MSS_PERIPH_MMUART1, (uint8_t) 1, PERIPHERAL_ON);
    (void) mss_config_clk_rst(MSS_PERIPH_MMUART2, (uint8_t) 1, PERIPHERAL_ON);
    (void) mss_config_clk_rst(MSS_PERIPH_MMUART3, (uint8_t) 1, PERIPHERAL_ON);
    (void) mss_config_clk_rst(MSS_PERIPH_MMUART4, (uint8_t) 1, PERIPHERAL_ON);
    (void) mss_config_clk_rst(MSS_PERIPH_CFM, (uint8_t) 1, PERIPHERAL_ON);

    /* All clocks ON */

    MSS_UART_init(&g_mss_uart1_lo,
    MSS_UART_115200_BAUD,
    MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
    MSS_UART_set_rx_handler(&g_mss_uart1_lo, uart1_rx_handler, MSS_UART_FIFO_SINGLE_BYTE);

    MSS_UART_enable_local_irq(&g_mss_uart1_lo);

    /* Demonstrating polled MMUART transmission */
    // MSS_UART_polled_tx(&g_mss_uart1_lo,g_message1, sizeof(g_message1));
    MSS_UART_polled_tx(&g_mss_uart1_lo,"PPL Command Interface\r\n", 23);

    /* Demonstrating interrupt method of transmission */
//    MSS_UART_irq_tx(&g_mss_uart1_lo, g_message2, sizeof(g_message2));

    /* Makes sure that the previous interrupt based transmission is completed
     * Alternatively, you could register TX complete handler using
     * MSS_UART_set_tx_handler() */
//    while (0u == MSS_UART_tx_complete(&g_mss_uart1_lo)) {
//        ;
//    }

    mcycle_start = readmcycle();

    // WRITE AND READ AXI FABRIC
    uint64_t * const fabric_base_addr = (uint64_t *)0x61000000U;
    MSS_UART_polled_tx(&g_mss_uart1_lo, "START MEMORY TEST\r\n", 17);
    SYSREG->SOFT_RESET_CR &= ~(SOFT_RESET_CR_FIC0_MASK | SOFT_RESET_CR_FPGA_MASK);
    SYSREG->SUBBLK_CLOCK_CR = 0xffffffff;
    for (uint64_t x = 0; x < 0xf; x++) {
        fabric_base_addr[x] = x;
    }

    for (volatile uint64_t data = 0, x = 0; x < 0xf; x++) {
        data = fabric_base_addr[x];
        if (data == x) {
            MSS_UART_polled_tx(&g_mss_uart1_lo, "p", 1);
        } else {
            MSS_UART_polled_tx(&g_mss_uart1_lo, "F", 1);
       }
    }
    MSS_UART_polled_tx(&g_mss_uart1_lo, "\r\nEND MEMORY TEST\r\n", 19);
    MSS_UART_polled_tx(&g_mss_uart1_lo, "=> ", 3);

    while (1u) {
        if (g_line_ready) {
            g_line_ready = false;
            uint8_t err_code = ppl_compile_line(&g_ppl_vm, &g_line, &g_msg);
            string_init(&g_line, "");
            if (g_msg.len > 0U) {
                string_print(&g_msg);
            }
            MSS_UART_polled_tx(&g_mss_uart1_lo, "=> ", 3);

//            switch (g_rx_buff[0u]) {
//
//            case '0':
//                mcycle_end = readmcycle();
//                delta_mcycle = mcycle_end - mcycle_start;
//                sprintf(info_string, "hart %ld, %ld delta_mcycle \r\n", hartid,
//                        delta_mcycle);
//                MSS_UART_polled_tx(&g_mss_uart1_lo, info_string,
//                        strlen(info_string));
//                break;
//            case '1':
//                /* show menu */
//                MSS_UART_irq_tx(&g_mss_uart1_lo, g_message2,
//                        sizeof(g_message2));
//                break;
//            case '2':
//
//                /* polled method of transmission */
//                MSS_UART_polled_tx(&g_mss_uart1_lo, polled_message,
//                        sizeof(polled_message));
//
//                break;
//            case '3':
//
//                /* interrupt method of transmission */
//                MSS_UART_irq_tx(&g_mss_uart1_lo, intr_message,
//                        sizeof(intr_message));
//                break;
//
//            default:
//                // MSS_UART_polled_tx(&g_mss_uart1_lo, g_rx_buff, g_rx_size);
//                break;
//            }
//
//            g_rx_size = 0u;
        }
    }
}

/* hart1 Software interrupt handler */

void Software_h1_IRQHandler(void) {
    uint64_t hart_id = read_csr(mhartid);
    count_sw_ints_h1++;
}
