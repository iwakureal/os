#ifndef PCI_H
#define PCI_H

#include <stdint.h>

#define PCI_CONFIG_ADDR 0xCF8
#define PCI_CONFIG_DATA 0xCFC

uint16_t pci_read(uint8_t bus, uint8_t device, uint8_t func, uint8_t offset);

#endif
