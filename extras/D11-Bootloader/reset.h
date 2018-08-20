enum system_reset_cause {
  /** The system was last reset by a software reset. */
  SYSTEM_RESET_CAUSE_SOFTWARE       = PM_RCAUSE_SYST,
  /** The system was last reset by the watchdog timer. */
  SYSTEM_RESET_CAUSE_WDT            = PM_RCAUSE_WDT,
  /** The system was last reset because the external reset line was pulled low. */
  SYSTEM_RESET_CAUSE_EXTERNAL_RESET = PM_RCAUSE_EXT,
  /** The system was last reset by the BOD33. */
  SYSTEM_RESET_CAUSE_BOD33          = PM_RCAUSE_BOD33,
  /** The system was last reset by the BOD12. */
  SYSTEM_RESET_CAUSE_BOD12          = PM_RCAUSE_BOD12,
  /** The system was last reset by the POR (Power on reset). */
  SYSTEM_RESET_CAUSE_POR            = PM_RCAUSE_POR,
};

static inline enum system_reset_cause system_get_reset_cause(void)
{
  return (enum system_reset_cause)PM->RCAUSE.reg;
}
