import serial
import time
import json

#sensor_arduino = serial.Serial('/dev/ttyACM0')

sensor_serial = serial.Serial('COM5', 9600, timeout=1)
sensor_serial.reset_input_buffer()

led_a_serial = serial.Serial('COM11', 9600, timeout=1)
led_a_serial.reset_input_buffer()

led_b_serial = serial.Serial('COM6', 9600, timeout=1)
led_b_serial.reset_input_buffer()

park_alani_A = "00000000000000"
park_alani_B = "00000000000000"
weather = ""
power = ""

enter_mode = False
park_alani_A_enter = ""
park_alani_B_enter = ""

while True:
    sensor_serial.write(b"PARK-SENSOR?\n\r")
    sensor_line = sensor_serial.readline().decode('utf-8').rstrip()

    park_alani_A = sensor_line[12:26]
    park_alani_B = sensor_line[32:46]

    print(park_alani_A)
    print(park_alani_B)

    sensor_serial.write(b"WEATHER-SENSOR?\n\r")
    weather_line = sensor_serial.readline().decode('utf-8').rstrip()
    
    weather = weather_line[15:]

    print(weather)

    sensor_serial.write(b"POWER-SENSOR?\n\r")
    power_line = sensor_serial.readline().decode('utf-8').rstrip()

    power = power_line[13:]

    print(power)

    try:
        dictionary = {
            "parkA": park_alani_A,
            "parkB": park_alani_B,
            "weather": weather,
            "power": power
        }

        json_object = json.dumps(dictionary, indent=4)

        with open("data.json", "w") as outfile:
            outfile.write(json_object)
    except Exception as e:
        print(e)

    try:
        with open('cmd.json', 'r') as openfile:
            cmd = json.load(openfile)

        print(cmd)
    except Exception as e:
        cmd = {"enter": False, "exit": False}
        print(e)
    

    if (cmd["enter"] == True):
        sensor_serial.write(b"GATE-ENTER\n\r")

        enter_mode = True
        park_alani_A_enter = park_alani_A
        park_alani_B_enter = park_alani_B

        cmd["enter"] = False

    if (cmd["exit"] == True):
        sensor_serial.write(b"GATE-EXIT\n\r")
        cmd["exit"] = False

    try:
        with open("cmd.json", "w") as outfile:
            json.dump(cmd, outfile)

    except Exception as e:
        print(e)

    if(enter_mode):
        if (park_alani_A != park_alani_A_enter or park_alani_B != park_alani_B_enter):
            enter_mode = False

        park_alani_A_enter_blink = park_alani_A.replace('0', '2')
        park_alani_B_enter_blink = park_alani_B.replace('0', '2')

        led_a_cmd_enter = f"LED-CMD:{park_alani_A_enter_blink};AAAA;\n\r"
        led_b_cmd_enter = f"LED-CMD:{park_alani_B_enter_blink[::-1]};AAAA;\n\r"

        led_a_serial.write(led_a_cmd_enter.encode('utf-8'))
        led_b_serial.write(led_b_cmd_enter.encode('utf-8'))

        led_a_line = led_a_serial.readline().decode('utf-8').rstrip()
        led_b_line = led_b_serial.readline().decode('utf-8').rstrip()

        print("enter mode")
        print(led_a_line)
        print(led_b_line)

    else:
        led_a_cmd = f"LED-CMD:{park_alani_A};AAAA;\n\r"
        led_b_cmd = f"LED-CMD:{park_alani_B[::-1]};AAAA;\n\r"

        led_a_serial.write(led_a_cmd.encode('utf-8'))
        led_b_serial.write(led_b_cmd.encode('utf-8'))


    """ park_alani_A = park_alani_A_block[0:14]
    park_alani_B = park_alani_B_block[0:14]

    print(park_alani_A)
    print(park_alani_B)

    led_a_cmd = f"LED-CMD:{park_alani_A};AAAA;\n\r"
    led_b_cmd = f"LED-CMD:{park_alani_B[::-1]};AAAA;\n\r"

    led_a_serial.write(led_a_cmd.encode('utf-8'))
    led_a_line = led_a_serial.readline().decode('utf-8').rstrip()

    led_b_serial.write(led_b_cmd.encode('utf-8'))
    led_b_line = led_b_serial.readline().decode('utf-8').rstrip()

    print(sensor_line) """
    #print(led_a_line)
    #print(led_b_line)
    time.sleep(0.5)