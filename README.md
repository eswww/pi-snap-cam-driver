# pi-snap-cam-driver

## Introduction

Character device driver for `pi-snap` core parts 

## Parts list

- Pi Camera
- Lights sensor
- Switch(Button)

## Kernel directory path

```
~/linux-rpi
```

## How to use

### 1. Build

#### ../pi-snap-cam-driver/button/

```bash
$ make
```

### 2. Load device driver

#### ../pi-snap-cam-driver/button/

```bash
$ insmod button_driver.ko
$ sh mknod.sh
```
