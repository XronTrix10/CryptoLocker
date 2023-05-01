# CryptoLocker 🔐

This is a project of a digital locker based on ATM like otp based authentication mechanism.

## 👀 How it Works

- On Pressing *Star* (*) in the keypad, the Locker will send an OTP request to the server
- On server, an OTP will be generated and sent to the user via email and to the Locker via network
- On Entering Correct OTP, the servo motor will rotate and the locker will be unlocked
- Pressing *D* can remove the last entered digit while entering OTP
- There will be 3 chances to enter the specific OTP correctly. If that exceeds, the user has to request for a new OTP by pressing *Star* (*)
- The locker can request for new OTP maximum 3 times from the Server within any 15 minutes. If that exceeds, the locker will be banned by the server for more 15 minutes.
- After the Locker was unlocked, *Hash* (#) need to be pressed to Lock the locker again.

## ⚙️ Components Used

- NodeMCU Board
- Breadboard
- 4x4 Hex-keypad
- Jumperwires
- 5v Power Supply / Battery
- 5v Servo Motor
- A Computer/Laptop for setting up server

## 🤜 Setting up

- NodeMCU and the server Computer Both should be connected to the same Wifi 
- First Check the IP address of the server in the local network interface
- Put the IP address and all wifi credentials in the *CryptoLocker.ino* File at desired fields
- Install all required libraries in Arduino IDE
- Upload the code in NodeMCU
- Put the sender email credentials and a reciever email address in the *server.py* File at desired fields
- Install required libraries **(NOTE: Python should be pre-installed)**

    `pip install Flask`
- Keep the server code running in the computer

## 📌 Circuit Pin Diagram

|NodeMCU | Hex Keypad  | Servo Motor | Details
| :----- | :---------- | :------ | :------
|**D0** |  | **PWM Pin (Orange Wire)** | Sends PWM Signal to Rotate
|**D1** | **Row Pin 1** |   | Connects First Row   
|**D2** | **Row Pin 2** |  | Connects Second Row
|**D3** | **Row Pin 3** |   | Connects Third Row
|**D4** | **Row Pin 4** |  | Connects Fourth Row
|**D5** | **Col Pin 1** |   | Connects First Coloumn 
|**D6** | **Col Pin 2** |    | Connects Second Coloumn 
|**D7** | **Col Pin 3** |    |Connects Third Coloumn 
|**D8** | **Col Pin 4** |    |Connects Fourth Coloumn 

* The NodeMCU and the Servo motor should be connected to a 5v supply

* NOTE: It's better to connect the servo motor with a high current supply ( ~1A )