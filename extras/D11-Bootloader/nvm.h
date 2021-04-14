#define APP_START  0x00001000 //This gives 1536 bytes of bootloader space.
//#define FLASH_SIZE  0x00004000 //This gives 1536 bytes of bootloader space.

/* Target application size can be 15 kB */
/* APP_SIZE is the application section size in kB */
/* Change as per APP_START */
#define APP_SIZE  5 //This is how much flash memory is left for the application.

/* Memory pointer for flash memory */
#define NVM_MEMORY      ((volatile uint16_t *)FLASH_ADDR)
