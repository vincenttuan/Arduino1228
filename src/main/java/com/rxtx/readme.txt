Arduino RXTX Java
下載位置 : http://fizzed.com/oss/rxtx-for-java
下載 RXTX-2-2-20081207	Windows-x64

Windows 下安裝 RXTX
複製 rxtxParallel.dll 到 C:\Program Files\java\openjdk-1.8.0.171\jre\bin
複製 rxtxSerial.dll 到 C:\Program Files\java\openjdk-1.8.0.171\jre\bin
複製 RXTXcomm.jar 到 C:\Program Files\java\openjdk-1.8.0.171\jre\lib\ext
說明頁 : https://blog.csdn.net/njchenyi/article/details/6361787

Sample Code
http://rxtx.qbang.org/wiki/index.php/Two_way_communcation_with_the_serial_port
注意 : 請改成 9600
serialPort.setSerialPortParams(9600,SerialPort.DATABITS_8,SerialPort.STOPBITS_1,SerialPort.PARITY_NONE);

