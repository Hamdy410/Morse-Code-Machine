from serial import Serial
from time import sleep
from morse3 import Morse

replacements = {
    "   ": "/",
    "'s": " is",
    "'re": " are",
    "'m": " am",
    "'ll": " will",
    "'ve": " have",
    "'as": " has",
    "'d": " had",
    "'ld": " would",
    "can't": "cannot",
    "won't": "will not",
}

arduino = Serial("COM11", 9600)
sleep(2)


def main():
    try:
        while True:
            mode = check_mode()
            if mode is not None and "Encoder" in mode:
                arduino.flushInput()
                handle_encoder_mode()

            elif mode is not None and "Decoder" in mode:
                handle_decoder_mode()
    except ValueError as e:
        print("An error occurred: ", e)
        close()

    finally:
        print("\nClosing Program...")
        sleep(0.5)
        close()


def close():
    arduino.close()
    exit(0)


def check_mode():
    sleep(0.5)
    if arduino.in_waiting:
        raw_line = arduino.readline()
        try:
            mode = raw_line.decode("utf-8", "ignore").rstrip()
            if mode is not None:
                return mode
        except UnicodeDecodeError:
            print("Failed to decode: ", mode)
            arduino.close()
            exit(0)
    else:
        return None


def handle_encoder_mode():
    print("\n======================================")
    print("Encoder Mode\n")
    print(
        "Note: When required to terminate this mode, you would be required to send two successive empty inputs."
    )
    print(
        "It would be required to wait from 30 to 50 seconds then pressing the push button to switch between the two modes\n"
    )
    string_to_send = input("Enter a string to send (0 to exit): ").lower()
    if string_to_send == "0":
        close()

    for old, new in replacements.items():
        string_to_send = string_to_send.replace(old, new)

    string_of_morse = Morse(string_to_send).stringToMorse()
    arduino.write(string_of_morse.encode())
    print("======================================")


def handle_decoder_mode():
    print("\n======================================")
    print("Decoder Mode\n")
    print(
        "Note: to terminate this mode you would be required to press the push button and wait between 30 to 50 seconds till the reload.\n"
    )
    while True:
        sleep(1)
        if arduino.in_waiting:
            raw_line = arduino.read_all()
            try:
                data = raw_line.decode("utf-8", "ignore").rstrip().replace("\r", "")
                print("Your message: ", end="")
                index_slash = data.find("/")
                morse_string = (data[index_slash:]).replace("r", "").replace("/", " ")
                print(Morse(morse_string).morseToString())
                print("======================================")
                if check_mode() is not None and "Encoder" in check_mode():
                    print("Decoder Mode Terminated")
                    break
            except ValueError as e:
                print(e)


main()
