#ifndef _BOOTSEL_REBOOT_HPP
#define _BOOTSEL_REBOOT_HPP

#define WATCHDOG_TIMEOUT 1000 // Milliseconds

bool __no_inline_not_in_flash_func(get_bootsel_button)();
void arm_watchdog();
void update_watchdog();
void check_bootsel_button();

#endif // _BOOTSEL_REBOOT_HPP
