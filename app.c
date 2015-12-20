#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

static void gpio_setup(void) {
    /* Enable GPIOA clock. */
    /* Manually: */
    /*RCC_AHB1ENR |= RCC_AHB1ENR_IOPAEN; */
    /* Using API functions: */
    rcc_periph_clock_enable(RCC_GPIOA);

    /* Set GPIO5 (in GPIO port A) to 'output push-pull'. */
    /* Manually: */
    /*GPIOA_CRH = (GPIO_CNF_OUTPUT_PUSHPULL << (((8 - 8) * 4) + 2)); */
    /*GPIOA_CRH |= (GPIO_MODE_OUTPUT_2_MHZ << ((8 - 8) * 4)); */
    /* Using API functions: */
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
}

int main(void)
{
    int i;

    gpio_setup();
    gpio_toggle(GPIOA, GPIO5);  /* LED on/off */

    /* Blink the LED (PC8) on the board. */
    while (1) {
        /* Manually: */
        /* GPIOA_BSRR = GPIO5; */       /* LED off */
        /* for (i = 0; i < 1000000; i++) */ /* Wait a bit. */
        /*  __asm__("nop"); */
        /* GPIOA_BRR = GPIO5; */        /* LED on */
        /* for (i = 0; i < 1000000; i++) */ /* Wait a bit. */
        /*  __asm__("nop"); */

        /* Using API functions gpio_set()/gpio_clear(): */
        /* gpio_set(GPIOA, GPIO5); */   /* LED off */
        /* for (i = 0; i < 1000000; i++) */ /* Wait a bit. */
        /*  __asm__("nop"); */
        /* gpio_clear(GPIOA, GPIO5); */ /* LED on */
        /* for (i = 0; i < 1000000; i++) */ /* Wait a bit. */
        /*  __asm__("nop"); */

        /* Using API function gpio_toggle(): */
        gpio_toggle(GPIOA, GPIO5);  /* LED on/off */
        for (i = 0; i < 2500000; i++) { /* Wait a bit. */
            __asm__("nop");
        }
        gpio_toggle(GPIOA, GPIO5);  /* LED on/off */
        for (i = 0; i < 500000; i++) { /* Wait a bit. */
            __asm__("nop");
        }
    }

    return 0;
}
