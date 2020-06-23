#include "wifi.h"
#include "tcp_socket.h"
#include "error.h"
#include "string.h"
#include "uart.h"
#include "uart_extra.h"
#include "irq.h"
#include "irq_extra.h"
#include "delay.h"
#include <stdio.h>
#include "debug.h"
#include "delay.h"

char wifi_ssid[] = "MyRoom";
char wifi_pass[] = "12348765";

int32_t	ret;

int8_t	*msg;
int32_t	len;
struct aducm_uart_init_param aducm_param = {
	.parity = UART_NO_PARITY,
	.stop_bits = UART_ONE_STOPBIT,
	.word_length = UART_WORDLEN_8BITS
};
struct uart_init_param		uart_param = {0,
		       BD_115200,//with 115200 we get overrun
		       //BD_9600,
		       &aducm_param
};
struct irq_init_param		irq_par = {0, 0};
struct wifi_init_param		wifi_param;

struct uart_desc		*udesc;
struct irq_ctrl_desc		*idesc;
struct wifi_desc		*wifi;
struct network_interface	*net;
struct socket_address		server;

int32_t init_wifi(struct wifi_desc **wifi) {
	ret = irq_ctrl_init(&idesc, &irq_par);
	ASSERT_AND_RET(ret, "Irq init failed\n");

	ret = uart_init(&udesc, &uart_param);
	ASSERT_AND_RET(ret, "Uart init failed\n");

	wifi_param.irq_desc = idesc;
	wifi_param.uart_desc = udesc;
	wifi_param.uart_irq_conf = udesc;
	wifi_param.uart_irq_id = ADUCM_UART_INT_ID;

	ret = wifi_init(wifi, &wifi_param);
	ASSERT_AND_RET(ret, "Wifi init failed\n");

	//ret = wifi_connect(*wifi, wifi_ssid, wifi_pass);
	ASSERT_AND_RET(ret, "Connect failed\n");

	return SUCCESS;
}


int32_t remove_wifi(struct wifi_desc *wifi)
{
	ret = wifi_remove(wifi);
	ASSERT_AND_RET(ret, "Wifi remove failed\n");

	ret = uart_remove(udesc);
	ASSERT_AND_RET(ret, "Uart remove failed\n");

	ret = irq_ctrl_remove(idesc);
	ASSERT_AND_RET(ret, "Irq remove failed\n");

	return ret;
}

void wifi_test(){
	struct wifi_desc *wifi;
	struct tcp_socket_init_param	init_param = {0};
	struct tcp_socket_desc			*sock;
	init_wifi(&wifi);

	wifi_get_network_interface(wifi, &init_param.net);


	while (1);
}
