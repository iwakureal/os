#include "pci.h"
#include "cpu/io.h"

uint16_t pci_read(uint8_t bus, uint8_t device, uint8_t func, uint8_t offset) {
	uint32_t lbus  = (uint32_t)bus;
	uint32_t ldev = (uint32_t)device;
	uint32_t lfunc = (uint32_t)func;

	outl(PCI_CONFIG_ADDR,
		(uint32_t)((lbus << 16) | (ldev << 11) |
		(lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000))
	);
	return (uint16_t)((inl(PCI_CONFIG_DATA) >> ((offset & 2) * 8)) & 0xFFFF);
}
