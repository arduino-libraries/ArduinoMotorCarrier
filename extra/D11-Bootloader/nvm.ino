/* Application starts from 1kB memory - Bootloader size is 1kB
Change the address if higher boot size is needed
good site for quick conversions.
http://www.binaryhexconverter.com/hex-to-decimal-converter */

#include "nvm.h"

/** If \c false, a page write command will be issued automatically when the
   page buffer is full. */
bool manual_page_write;

uint8_t data_8 = 1;
uint32_t file_size, i, dest_addr;
uint32_t volatile app_start_address;
uint8_t volatile data_from_flash;
uint32_t *flash_ptr;
uint8_t *flash_byte_ptr;

/* Flash page size is 64 bytes */
uint16_t PAGE_SIZE = (8 << NVMCTRL->PARAM.bit.PSZ); //used to read and write to flash.

void erase_all() {
  /* erase all */
  for (int i = APP_START; i < FLASH_SIZE; i = i + PAGE_SIZE)
  {
    nvm_erase_row(i, PAGE_SIZE);
  }
}

#define SKETCH_START (uint32_t*)(APP_START)

void boot_app() {
  // jump to the sketch
  __set_MSP(*SKETCH_START);

  //Reset vector table address
  SCB->VTOR = ((uint32_t)(SKETCH_START) & SCB_VTOR_TBLOFF_Msk);

  // address of Reset_Handler is written by the linker at the beginning of the .text section (see linker script)
  uint32_t resetHandlerAddress = (uint32_t) * (SKETCH_START + 1);
  // jump to reset handler
  asm("bx %0"::"r"(resetHandlerAddress));
}

void setup_ptrs()
{
  //set values, for flash pointers.
  dest_addr = APP_START;
  flash_ptr = (uint32_t*)APP_START;
  app_start_address = *flash_ptr;
  flash_byte_ptr = (uint8_t*)APP_START;
}

void nvm_erase_row(const uint32_t row_address, uint32_t PAGE_SIZE)
{
#if 0
  /* Check if the address to erase is not aligned to the start of a row */
  if (row_address > ((uint32_t)_nvm_dev.page_size * _nvm_dev.number_of_pages))
  {
    return 0;
  }

  /* Get a pointer to the module hardware instance */
  if (row_address & ((_nvm_dev.page_size * NVMCTRL_ROW_PAGES) - 1))
  {
    return 0;
  }
#endif

  /* Check if the module is busy */
  while (!NVMCTRL->INTFLAG.bit.READY);

  /* Clear error flags */
  NVMCTRL->STATUS.reg &= ~NVMCTRL_STATUS_MASK;

  while (!(NVMCTRL->INTFLAG.bit.READY));

  /* Set address and command */
  NVMCTRL->ADDR.reg = (uintptr_t)&NVM_MEMORY[row_address / 4];
  NVMCTRL->CTRLA.reg = NVMCTRL_CTRLA_CMDEX_KEY | NVMCTRL_CTRLA_CMD_ER;
  while (!(NVMCTRL->INTFLAG.bit.READY));

}

void nvm_write_buffer(uint32_t destination_address, const uint8_t *buffer, uint16_t length)
{
#if 0

  /* Check if the destination address is valid */
  if (destination_address >
      ((uint32_t)_nvm_dev.page_size * _nvm_dev.number_of_pages)) {
    return 0;
  }

  /* Check if the write address not aligned to the start of a page */
  if (destination_address & (_nvm_dev.page_size - 1)) {
    return 0;
  }

  /* Check if the write length is longer than a NVM page */
  if (length > _nvm_dev.page_size) {
    return 0;
  }
#endif

  /* Check if the module is busy */
  while (!NVMCTRL->INTFLAG.bit.READY);

  //set auto page writes
  NVMCTRL->CTRLB.bit.MANW = 0;

  /* Erase the page buffer before buffering new data */
  NVMCTRL->CTRLA.reg = NVMCTRL_CTRLA_CMD_PBC | NVMCTRL_CTRLA_CMDEX_KEY;

  /* Check if the module is busy */
  while (!NVMCTRL->INTFLAG.bit.READY);

  /* Clear error flags */
  NVMCTRL->STATUS.reg &= ~NVMCTRL_STATUS_MASK;

  uint32_t nvm_address = destination_address / 2;

  /* NVM _must_ be accessed as a series of 16-bit words, perform manual copy
     to ensure alignment */
  for (uint16_t k = 0; k < length; k += 2)
  {
    uint16_t data;

    /* Copy first byte of the 16-bit chunk to the temporary buffer */
    data = buffer[k];

    /* If we are not at the end of a write request with an odd byte count,
       store the next byte of data as well */
    if (k < (length - 1)) {
      data |= (buffer[k + 1] << 8);
    }
    /* Store next 16-bit chunk to the NVM memory space */
    NVM_MEMORY[nvm_address++] = data;
    NVMCTRL->CTRLA.reg = NVMCTRL_CTRLA_CMDEX_KEY | NVMCTRL_CTRLA_CMD_WP;

  }

  /* If automatic page write mode is enable, then perform a manual NVM
     write when the length of data to be programmed is less than page size
  */
  if ((manual_page_write == 0) && (length < NVMCTRL_PAGE_SIZE)) {
    NVMCTRL->CTRLA.reg = NVMCTRL_CTRLA_CMDEX_KEY | NVMCTRL_CTRLA_CMD_WP;
  }

  while (!NVMCTRL->INTFLAG.bit.READY);
}
