#ifndef RELAY_H
#define RELAY_H

#include <stdint.h>

void relay_init(void);
void relay_on(uint8_t relay_num);
void relay_off(uint8_t relay_num);

#endif /* RELAY_H */
