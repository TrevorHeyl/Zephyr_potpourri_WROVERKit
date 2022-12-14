ESP32 WROVER Standalone project template and custom board with variety of kernel APIs exercised
###########

Overview
********

A simple sample that can be used off-tree. It includes a custom board called ESP_CUSTOM but is based on the ESP32 WROVER Kit V4 from Espressif

Demonstrates these kernel API features:
   * Timers
   * Mailboxes
   * Threads (compile time and runtime creation)
   * Some GPIO

This example uses 4 LEDs, the colours of whch can be mapped in the app.overlay file. the defualt is:

  * RED LED GPIO 22
  * GREEN LED GPIO 21
  * BLUE LED GPIO 23
  * Generic LED GPIO 19


Building and Running
********************

This application can be built and executed as follows:

First make sure the toolchain is installed

From inside zephyrproject/zephyr:

.. code-block:: console

   >west update
   
   >west espressif update
   
   >west espressif install
   
Then you must add toolchain variables into the environment:

.. code-block:: console

   >export ESPRESSIF_TOOLCHAIN_PATH=”/home/yourusername/.espressif/tools/zephyr”
   
   >export ESPRESSIF_TOOLCHAIN_VARIANT=”espressif”
   


To Build and run
=============

.. code-block:: console

  >source ~/zephyrproject/zephyr/zephyr-env.sh
  
  >west build -p -b esp_custom
   
  >west flash
   
  >west espressif monitor



  
Exit themonitor with  :kbd:`CTRL+]` 
