
Flash algorithm for pyOCD run with i.mxRT106x QSPI flash

Introduction
*****************
    when you want to debug ARM MCU by pyOCD,you have to burn the firmware to the flash. So certain flash algorithm should be used for different MCU and flash. The MDK have integrated flash algorithm for MCU supported by them. such algorithm can be found in the DFP pack provided by MCU manufactor or ARM.The convenient method is use 'FlashAlgo'_ to generate the python blob . Then pyOCD can burn the flash. but when I try to do it. it is always failure, The pyOCD only provide blob python for the i.mxRT105x for QSPI flash. but it couldn't run on my boards. So I make this project and verified on my hardware platform，The MCU is i.mxRT1061CV5.The flash is winbond w25q32,4MB quad spi flash. the website is http://www.forlinx.net/products_detail/productId=94.html  ,you also can utilize pyOCD to debug gnu arm program on i.mxRT0161 platform. BTW. NXP use Freelink as emulator for their developement kit.but it is not popluar for most engineers.The DAP debugger may be good choice for us.

GetStarted
**********************
* **DAPLink**: DAP Link hardware debugger 'DAPLink Debugger'_
* **FlashAlgo**: Flash algorithm 'FlashAlgo'_   

.. _DAPLink Debugger:
.. _FlashAlgo: https://github.com/mbedmicro/FlashAlgo
