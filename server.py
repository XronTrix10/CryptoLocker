import smtplib
import random
import os
import time
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from flask import Flask, jsonify, request

# Text Colors
class clr:
    reset = "\033[0m"
    bold = "\033[01m"

    red = "\033[31m"
    lightred = "\033[91m"
    green = "\033[32m"
    orange = "\033[33m"
    blue = "\033[34m"
    lightgreen = "\033[92m"
    yellow = "\033[93m"

app = Flask(__name__)

# Sender email credentials and server information
email_sender = ""
email_password = ""
smtp_server = "" # Example: smtp.gmail.com if Sender is Gmail
smtp_port = 587
# Email receiver's address
email_receiver = ""

ip_request_count = {}  # Store the count and timestamp of the first request

def n_activate():
    print(clr.orange, "\t\tLocker 01\tLocker 02\tLocker 03\tLocker 04")
    print(clr.lightgreen, "\n\t\tOnline" + clr.red, "\t\tOffline\t\tOffline\t\tOffline")

@app.route("/get_otp", methods=["GET"])
def get_otp():

    os.system("cls")

    ip = request.remote_addr

    if ip not in ip_request_count or (time.time() - ip_request_count[ip][1]) > (15 * 60):
        ip_request_count[ip] = [0, time.time()]

    if ip_request_count[ip][0] < 3:
        ip_request_count[ip][0] += 1
    else:
        print(f"\nForbidden Request from {ip} for 15 minutes !\n",end="\n\nLocker 01: ")
        return jsonify({"error": "Request limit exceeded"}), 429

    # print(ip_request_count)

    # Generate a new OTP for each request
    OTP = "".join([str(random.randint(0, 9)) for i in range(6)])
    n_activate()
    print(
        clr.blue,
        "\n\nOTP: " + clr.bold,
        clr.lightred,
        f"{OTP}",
        clr.reset,
        clr.orange,
        end="\n\nLocker 01: " + clr.yellow,
    )

    # Create the message object
    msg = MIMEMultipart()
    msg["From"] = email_sender
    msg["To"] = email_receiver
    msg["Subject"] = "CryptoLocker Code"


    body = f"""

    <html>
    <head>
    <style>
        body {{
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
        }}
        h1 {{
            color: rgb(100, 16, 16);
            padding: 20px;
            margin: 0;
        }}
        p {{
            font-size: 16px;
            color: #333;
            margin: 12px 0;`
            
        }}
        .heading {{
            height: auto;
            width: 100vw;
            background-color: burlywood;
            text-align: center;
        }}
        .otp {{
            display: inline-block;
            font-weight: bold;
            color: #e01c1c;
            font-size: 20px;
            background-color: #e8f4fd;
            padding: 10px;
            border-radius: 5px;
            margin: 0;
        }}

        .master {{
            max-width: 600px;
            padding: 24px;
            margin: 0 auto;
            background-color: bisque;
            height: 100vh;
        }}
    </style>
    </head>
    <body>
    <header>
    <div class="heading">
    <h1>CryptoLocker</h1>
    </div>
    </header>
    <main>
    <div class="master">
    <p>Hello CryptoLocker user,</p>
    <p>Your One Time Password (OTP) is:</p>
    <p class="otp">{OTP}</p>
    <p>PLEASE DON'T SHARE THIS OTP TO ANYONE !!</p>
    <p>Thank you for using our service !</p>
    </div>
    </main>
    </body>
    </html>
    
    """

    msg.attach(MIMEText(body, "html"))

    try:
        with smtplib.SMTP(smtp_server, smtp_port) as server:
            server.starttls()
            server.login(email_sender, email_password)
            text = msg.as_string()
            server.sendmail(email_sender, email_receiver, text)
            print("Email sent successfully.")
    except Exception as e:
        print(f"Error occurred: {e}")
    return jsonify({"otp": OTP}), 200


if __name__ == "__main__":

    app.run(host="0.0.0.0", port=3000)
