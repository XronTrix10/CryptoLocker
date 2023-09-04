# CryptoLocker 🔐

This is a project of a digital locker based on ATM like otp based authentication mechanism.

## 👀 How it Works

- On Pressing *Star* (*) in the keypad, the Locker will send an OTP request to the server
- On server, an OTP will be generated and sent to the user via email and to the Locker via network
- On Entering Correct OTP, the servo motor will rotate and the locker will be unlocked
- Pressing *D* can remove the last entered digit while entering OTP
- There will be 3 chances to enter the specific OTP correctly. If that exceeds, the user has to request for a new OTP by
pressing *Star* (*)
- The locker can request for new OTP maximum 3 times from the Server within any 15 minutes. If that exceeds, the locker
will be banned by the server for more 15 minutes.
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

<pre>pip install Flask</pre>

- Keep the server code running in the computer

## 📌 Circuit Pin Diagram

<table>
    <thead>
        <tr>
            <th style="text-align:center">NodeMCU</th>
            <th style="text-align:center">Hex Keypad</th>
            <th style="text-align:center">Servo Motor</th>
            <th style="text-align:center">Details</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td style="text-align:center"><strong>D0</strong></td>
            <td style="text-align:center"></td>
            <td style="text-align:center"><strong>PWM Pin (Orange Wire)</strong></td>
            <td style="text-align:center">Sends PWM Signal to Rotate</td>
        </tr>
        <tr>
            <td style="text-align:center"><strong>D1</strong></td>
            <td style="text-align:center"><strong>Row Pin 1</strong></td>
            <td style="text-align:center"></td>
            <td style="text-align:center">Connects First Row </td>
        </tr>
        <tr>
            <td style="text-align:center"><strong>D2</strong></td>
            <td style="text-align:center"><strong>Row Pin 2</strong></td>
            <td style="text-align:center"></td>
            <td style="text-align:center">Connects Second Row</td>
        </tr>
        <tr>
            <td style="text-align:center"><strong>D3</strong></td>
            <td style="text-align:center"><strong>Row Pin 3</strong></td>
            <td style="text-align:center"></td>
            <td style="text-align:center">Connects Third Row</td>
        </tr>
        <tr>
            <td style="text-align:center"><strong>D4</strong></td>
            <td style="text-align:center"><strong>Row Pin 4</strong></td>
            <td style="text-align:center"></td>
            <td style="text-align:center">Connects Fourth Row</td>
        </tr>
        <tr>
            <td style="text-align:center"><strong>D5</strong></td>
            <td style="text-align:center"><strong>Col Pin 1</strong></td>
            <td style="text-align:center"></td>
            <td style="text-align:center">Connects First Coloumn </td>
        </tr>
        <tr>
            <td style="text-align:center"><strong>D6</strong></td>
            <td style="text-align:center"><strong>Col Pin 2</strong></td>
            <td style="text-align:center"></td>
            <td style="text-align:center">Connects Second Coloumn </td>
        </tr>
        <tr>
            <td style="text-align:center"><strong>D7</strong></td>
            <td style="text-align:center"><strong>Col Pin 3</strong></td>
            <td style="text-align:center"></td>
            <td style="text-align:center">Connects Third Coloumn </td>
        </tr>
        <tr>
            <td style="text-align:center"><strong>D8</strong></td>
            <td style="text-align:center"><strong>Col Pin 4</strong></td>
            <td style="text-align:center"></td>
            <td style="text-align:center">Connects Fourth Coloumn </td>
        </tr>
    </tbody>
</table>

* The NodeMCU and the Servo motor should be connected to a 5v supply

* NOTE: It's better to connect the servo motor with a high current supply ( ~1A )