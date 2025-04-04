import tkinter as tk
from tkinter import messagebox
from tkinter import scrolledtext
import threading
import speech_recognition as sr
import serial
import time
# print(dir(serial))

class SpeechRecognizerApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Speech Recognizer")
        self.root.geometry("600x400")
        self.root.configure(bg="#2e3f4f")

        self.start_button = tk.Button(root, text="Start Recognition", command=self.start_recognition, width=20, height=2, font=("Arial", 14), bg="#4CAF50", fg="white")
        self.start_button.pack(pady=20)

        self.stop_button = tk.Button(root, text="Stop Recognition", command=self.stop_recognition, width=20, height=2, font=("Arial", 14), bg="#f44336", fg="white")
        self.stop_button.pack(pady=20)
        self.stop_button.config(state=tk.DISABLED)

        self.gate_status_button = tk.Button(root, text="get gate status", command=self.get_gate_status, width=20, height=2, font=("Arial", 14), bg="#4CAF50", fg="white")
        self.gate_status_button.pack(pady=20)

        self.output_text = scrolledtext.ScrolledText(root, wrap=tk.WORD, width=50, height=8, font=("Arial", 12), bg="#f0f0f0", fg="#333333")
        self.output_text.pack(pady=20)

        self.recognizer = sr.Recognizer()
        self.microphone = sr.Microphone()
        self.running = False
        self.recognition_thread = None
        self.serial_thread = None

        self.serial_port = serial.Serial('COM6', 9600, timeout=1)
        # self.serial_thread = threading.Thread(target=self.read_serial_data)
        # self.serial_thread.start()

    def recognize_speech(self):
        self.running = True
        while self.running:
            try:
                with self.microphone as source:
                    self.recognizer.adjust_for_ambient_noise(source, duration=0.5)
                    audio = self.recognizer.listen(source)

                    mytext = self.recognizer.recognize_google(audio)
                    mytext = mytext.lower()

                self.output_text.insert(tk.END, mytext + "\n")
                self.output_text.yview(tk.END)  # Scroll to the end of the text field

                if "open gate" in mytext:
                    self.serial_port.write(b'o')
                elif "close gate" in mytext:
                    self.serial_port.write(b'c')

            except sr.UnknownValueError:
                self.recognizer = sr.Recognizer()
                continue

    def start_recognition(self):
        self.start_button.config(state=tk.DISABLED)
        self.stop_button.config(state=tk.NORMAL)
        self.output_text.delete(1.0, tk.END)  # Clear the text field
        self.running = True
        self.recognition_thread = threading.Thread(target=self.recognize_speech)
        self.recognition_thread.start()

    def get_gate_status(self):
        self.start_button.config(state=tk.DISABLED)
        self.stop_button.config(state=tk.NORMAL)
        self.running = True
        self.serial_thread = threading.Thread(target=self.read_serial_data)
        self.serial_thread.start()

    def stop_recognition(self):
        self.running = False
        self.start_button.config(state=tk.NORMAL)
        self.stop_button.config(state=tk.DISABLED)

    def read_serial_data(self):
        self.running = True
        while self.running:
            try:
                if self.serial_port.in_waiting > 0:
                    data = self.serial_port.readline().decode('utf-8').strip()
                    if data[-7:] == "Welcome":
                        messagebox.showinfo("Gate -Status", "A car is on the entrance gate")
                    elif data[-3:] == "Bye":
                        messagebox.showinfo("Gate Status", "A car is on the exit gate")
            except serial.SerialException:
                # Handle serial port exceptions (e.g., if the port is closed or unavailable)
                # You might want to reconnect or show an error message
                pass
            except Exception as e:
                # Handle other exceptions
                print("Error reading serial data:", e)
        
        # Call this function again after a delay
        # if self.running:
        #     self.after(100, self.read_serial_data)  # 100 milliseconds (0.1 second)


if __name__ == "__main__":
    root = tk.Tk()
    app = SpeechRecognizerApp(root)
    root.mainloop()
