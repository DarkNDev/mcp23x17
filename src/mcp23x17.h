#ifndef MCP23X17_H
#define MCP23X17_H

// MCP23017 (I2C) / MCP23S17 (SPI) 16-bit I/O expander: register map.

/*
Two 8-bit ports: A (GPA0-7) and B (GPB0-7). Each register exists once per port.
Define MCP_BANK_MODE only if you set IOCON.BANK = 1. Default is BANK = 0.
*/

#ifdef MCP_BANK_MODE
/* ---- IOCON.BANK = 1: port A registers first, then port B ---- */

#define MCP_IODIRA 0x00   // A direction: 1 = input, 0 = output
#define MCP_IPOLA 0x01    // A input polarity: 1 = inverted
#define MCP_GPINTENA 0x02 // A interrupt-on-change enable
#define MCP_DEFVALA 0x03  // A default value for interrupt compare
#define MCP_INTCONA 0x04  // A interrupt control: 1 = compare to DEFVAL
#define MCP_IOCON 0x05    // chip configuration (also at 0x15)
#define MCP_GPPUA 0x06    // A 100k pull-up enable
#define MCP_INTFA 0x07    // A interrupt flag (read only)
#define MCP_INTCAPA 0x08  // A pin state captured at interrupt
#define MCP_GPIOA 0x09    // A read pins / write outputs
#define MCP_OLATA 0x0A    // A output latch
#define MCP_IODIRB 0x10
#define MCP_IPOLB 0x11
#define MCP_GPINTENB 0x12
#define MCP_DEFVALB 0x13
#define MCP_INTCONB 0x14 // IOCON also at 0x15
#define MCP_GPPUB 0x16
#define MCP_INTFB 0x17
#define MCP_INTCAPB 0x18
#define MCP_GPIOB 0x19
#define MCP_OLATB 0x1A

#else
/* ---- IOCON.BANK = 0 (default): A and B registers paired ---- */

#define MCP_IODIRA 0x00   // A direction: 1 = input, 0 = output
#define MCP_IODIRB 0x01   // B direction
#define MCP_IPOLA 0x02    // A input polarity: 1 = inverted
#define MCP_IPOLB 0x03    // B input polarity
#define MCP_GPINTENA 0x04 // A interrupt-on-change enable
#define MCP_GPINTENB 0x05 // B interrupt-on-change enable
#define MCP_DEFVALA 0x06  // A default value for interrupt compare
#define MCP_DEFVALB 0x07  // B default value for interrupt compare
#define MCP_INTCONA 0x08  // A interrupt control: 1 = compare to DEFVAL
#define MCP_INTCONB 0x09  // B interrupt control
#define MCP_IOCON 0x0A    // chip configuration (also at 0x0B)
#define MCP_GPPUA 0x0C    // A 100k pull-up enable
#define MCP_GPPUB 0x0D    // B 100k pull-up enable
#define MCP_INTFA 0x0E    // A interrupt flag (read only)
#define MCP_INTFB 0x0F    // B interrupt flag (read only)
#define MCP_INTCAPA 0x10  // A pin state captured at interrupt
#define MCP_INTCAPB 0x11  // B pin state captured at interrupt
#define MCP_GPIOA 0x12    // A read pins / write outputs
#define MCP_GPIOB 0x13    // B read pins / write outputs
#define MCP_OLATA 0x14    // A output latch
#define MCP_OLATB 0x15    // B output latch
#endif                    /* MCP_BANK_MODE */

/* ---- IOCON bits ---- */

#define MCP_IOCON_BANK (1u << 7)   // 1 = ports segregated (BANK=1 map)
#define MCP_IOCON_MIRROR (1u << 6) // 1 = INTA and INTB internally connected
#define MCP_IOCON_SEQOP (1u << 5)  // 1 = address auto-increment disabled
#define MCP_IOCON_DISSLW (1u << 4) // 1 = SDA slew rate disabled (I2C only)
#define MCP_IOCON_HAEN (1u << 3)   // 1 = hardware address pins used (S17 only)
#define MCP_IOCON_ODR (1u << 2)    // 1 = INT pins open-drain (overrides INTPOL)
#define MCP_IOCON_INTPOL (1u << 1) // 1 = INT pins active-high

// ---- Pin bit masks (same for port A and port B) ----

#define MCP_GP0 (1u << 0) // GPA0 / GPB0
#define MCP_GP1 (1u << 1) // GPA1 / GPB1
#define MCP_GP2 (1u << 2) // GPA2 / GPB2
#define MCP_GP3 (1u << 3) // GPA3 / GPB3
#define MCP_GP4 (1u << 4) // GPA4 / GPB4
#define MCP_GP5 (1u << 5) // GPA5 / GPB5
#define MCP_GP6 (1u << 6) // GPA6 / GPB6
#define MCP_GP7 (1u << 7) // GPA7 / GPB7

// ---- Bus addressing ----

// MCP23017 I2C 7-bit address: 0100 A2 A1 A0 (0x20..0x27).
// For 8-bit address bytes, shift left by 1 (0x40 for a = 0).
#define MCP23017_I2C_ADDR(a) (0x20u | ((a) & 7u))

// MCP23S17 SPI control byte: 0100 A2 A1 A0 R/W
#define MCP23S17_SPI_WRITE_ADDR(a) ((uint8_t)(0x40u | (((a) & 7u) << 1)))
#define MCP23S17_SPI_READ_ADDR(a) ((uint8_t)(0x41u | (((a) & 7u) << 1)))

// a = 0: write = 0x40, read = 0x41. Address bits are ignored unless HAEN = 1.
#define MCP23S17_SPI_WRITE ((uint8_t)(0x40u))
#define MCP23S17_SPI_READ ((uint8_t)(0x41u))

#endif /* MCP23X17_H */