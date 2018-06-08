import os
import time
import spidev


# Open SPI bus
spi = spidev.SpiDev()
spi.open(0, 0)
spi.max_speed_hz=1000000

# Read SPI data from MCP3208
# Channel range: 0 ~ 7
def read_channel(channel):
    adc = spi.xfer2([1, (8 + channel) << 4, 0])
    data = ((adc[1] & 3) << 8) + adc[2]
    return data

# Convert data to voltage level,
def convert_volts(data,places):
    volts = (data * 3.3) / float(1023)
    volts = round(volts, places)
    return volts


if __name__ == '__main__':
    # Sensor channel
    light_channel = 0

    # delay time (sec)
    delay = 5

    while True:
        # Read the light sensor data
        light_level = read_channel(light_channel)
        light_volts = convert_volts(light_level, 2)
        
        # Print out results
        print("[Light Sensor] {} ({}V)".format(light_level, light_volts))
        
        # Wait before repeating loop
        time.sleep(delay)
