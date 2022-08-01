ESP WROVER Standalone project template and custom board with variety of kernel APIs feature exercised
###########

Overview
********

A simple sample that can be used off-tree. It includes a custom board called ESP_CUSTOM but is base don the ESP32 WROVER Kit V4 from Espressif

Demonstrates these kernel API features:
   * Timers
   * Mailboxes
   * Threads (compile time and runtime creation)
   * Some GPIO


Building and Running
********************

This application can be built and executed as follows:

First make sure the toolchain is installed and the toolchain env paths

From inside zephyrproject/zephyr:
.. code-block:: console
   >west update
   
   >west espressif update
   
   >west espressif install
   
Then you must add toolchain variables into the environment
.. code-block:: console

   >export ESPRESSIF_TOOLCHAIN_PATH=”/home/yourusername/.espressif/tools/zephyr”
   
   >export ESPRESSIF_TOOLCHAIN_VARIANT=”espressif”
   


To Build and run
=============

.. code-block:: console
   
   > west build -p -b esp_custom
   
   > west flash
   
   > west espressif monitor



  
Exit themonitor with  :kbd:`CTRL+]` 
