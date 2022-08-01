#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <drivers/gpio.h>

#define LED         DT_ALIAS(led0)
#define RED_LED     DT_ALIAS(led1)
#define GREEN_LED   DT_ALIAS(led2)
#define BLUE_LED    DT_ALIAS(led3)

K_MBOX_DEFINE(my_mailbox);

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED, gpios);

static const struct gpio_dt_spec rgb_r = GPIO_DT_SPEC_GET(RED_LED, gpios);
static const struct gpio_dt_spec rgb_g = GPIO_DT_SPEC_GET(GREEN_LED, gpios);
static const struct gpio_dt_spec rgb_b = GPIO_DT_SPEC_GET(BLUE_LED, gpios);

#define RED     1
#define GREEN   2
#define BLUE    3


void flash_red(struct k_timer* dummy)
{
	struct k_mbox_msg send_msg;

	send_msg.info = RED;
	send_msg.size = 0;
	send_msg.tx_data = NULL;
	send_msg.tx_block.data = NULL;
	send_msg.tx_target_thread = K_ANY;

	k_mbox_put(&my_mailbox, &send_msg, K_NO_WAIT);
}

void flash_green(struct k_timer* dummy)
{
	struct k_mbox_msg send_msg;

	send_msg.info = GREEN;
	send_msg.size = 0;
	send_msg.tx_data = NULL;
	send_msg.tx_block.data = NULL;
	send_msg.tx_target_thread = K_ANY;

	k_mbox_put(&my_mailbox, &send_msg, K_NO_WAIT);
}

void flash_blue(struct k_timer* dummy)
{
	struct k_mbox_msg send_msg;

	send_msg.info = BLUE;
	send_msg.size = 0;
	send_msg.tx_data = NULL;
	send_msg.tx_block.data = NULL;
	send_msg.tx_target_thread = K_ANY;

	k_mbox_put(&my_mailbox, &send_msg, K_NO_WAIT);
}

K_TIMER_DEFINE(red_timer, flash_red, NULL);
K_TIMER_DEFINE(green_timer, flash_green, NULL);
K_TIMER_DEFINE(blue_timer, flash_blue, NULL);

void mail(void)
{
	struct k_mbox_msg recv_msg;
	
	while(1)
	{
		if(k_mbox_get(&my_mailbox, &recv_msg, NULL, K_FOREVER) == 0)
		{
			if(recv_msg.info == RED)
			{
				gpio_pin_toggle_dt(&rgb_r);
			}
			else if(recv_msg.info == GREEN)
			{
				gpio_pin_toggle_dt(&rgb_g);
			}
			else if(recv_msg.info == BLUE)
			{
				gpio_pin_toggle_dt(&rgb_b);
			}
		}
	}
}

K_THREAD_STACK_DEFINE(mail_stack, 2048);
struct k_thread mail_thread_data;

void init_thread(void)
{
	gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
	gpio_pin_configure_dt(&rgb_r, GPIO_OUTPUT_INACTIVE);
	gpio_pin_configure_dt(&rgb_b, GPIO_OUTPUT_INACTIVE);
	gpio_pin_configure_dt(&rgb_g, GPIO_OUTPUT_INACTIVE);

	k_timer_start(&red_timer, K_SECONDS(1), K_SECONDS(1));
	k_timer_start(&green_timer, K_MSEC(600), K_MSEC(600));
	k_timer_start(&blue_timer, K_MSEC(2000), K_MSEC(2000));
	

k_tid_t my_tid = k_thread_create(&mail_thread_data, mail_stack,
                                 K_THREAD_STACK_SIZEOF(mail_stack),
                                 mail,
                                 NULL, NULL, NULL,
                                 7, 0, K_NO_WAIT);
}

K_THREAD_DEFINE(init_thread_id, 1024, init_thread, NULL, NULL, NULL, -7, 0, 0);

 
