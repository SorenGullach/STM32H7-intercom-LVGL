# STM32H7-intercom-LVGL
Based on the Riverdi RVT70HSSNWC00-B
This is my take on how to implement a shareddata between the CM7 and CM4 core on the STM32H7, It also uses LVGL and HAL_FDCAN.

The code is based on the Riverdi STM32CubeMX exsample (https://controllerstech.com/lvgl-on-riverdi-stm32-h7-display/#google_vignette), and imported into two VisualGDB projects.


Papers to read:
RM0399 https://www.st.com/resource/en/reference_manual/dm00176879-stm32h745755-and-stm32h747757-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
RM0433 https://www.st.com/resource/en/reference_manual/dm00314099-stm32h742-stm32h743-753-and-stm32h750-value-line-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf
AN5617 https://www.st.com/resource/en/application_note/an5617-stm32h745755-and-stm32h747757-lines-interprocessor-communications-stmicroelectronics.pdf
AN4838 https://www.st.com/resource/en/application_note/an4838-introduction-to-memory-protection-unit-management-on-stm32-mcus-stmicroelectronics.pdf
VsualGDB https://visualgdb.com/tutorials/arm/stm32/multicore/
How to use LVGL on Riverdi STM32-H7 based Display https://controllerstech.com/lvgl-on-riverdi-stm32-h7-display/#google_vignette
RVT70HSSNWC00-B https://download.riverdi.com/RVT70HSSNWC00-B/DS_RVT70HSSNWC00-B_Rev.1.1.pdf
