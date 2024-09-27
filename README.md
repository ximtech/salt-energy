# salt-energy

## Introduction

This project provides practical solutions for repurposing disposable vape batteries to power devices like power banks and other rechargeable electronics. 
By transforming these short-lived products into useful, long-lasting devices, we aim to reduce electronic waste and extend the life cycle of valuable components.

<img src="assets/waste-vapes.jpg" width="800" height="800" alt="waste">

Through this project, you'll learn how to convert the batteries from disposable vapes into reliable power sources, contributing to a more sustainable future. 
Whether you're an eco-conscious creator or a DIY enthusiast, this guide offers straightforward solutions for reducing waste and promoting energy efficiency.

## Vape batteries

Each device contains `li-ion` battery that in most cases can be categorized as follows:

### 1. Flat battery

<img src="assets/battery_a.jpg" width="200" alt="battery_a">

- Cell Model: unknown
- Size: 80mm x 14mm x 37mm
- Li-ion 3.7V 400mAh

### 2. Round big battery

<img src="assets/battery_b.jpg" width="200" alt="battery_b">

- Cell Model: 13400
- Size: 13mm x 40mm
- Li-ion 3.7V 550mAh

### 3. Round small battery

<img src="assets/battery_c.jpg" width="200" alt="battery_c">

- Cell Model: 13300
- Size: 13mm x 30mm
- Li-ion 3.7V 400mAh

All project utilize one or many of this batteries

## Table of Contents

- [Pika AA Battery](#pika-aa-battery)
- [Ptero Power Bank](#ptero-power-bank)


## Pika AA Battery

TODO: In progress

---

## Ptero Power Bank

Cheap and powerful power bank with quick charge support

<img src="powerbank-ptero/assets/ptero_1.jpg" width="600" alt="ptero_1">

### Specification

- Size: 165mm x 74mm x 22mm
- Capacity: 9200 mAh
- Battery count: 23
- Battery type: [Flat battery](#1-flat-battery)

Based on the popular power bank charging module:

<img src="powerbank-ptero/assets/pb_pcb_1.jpg" width="250" alt="pb_pcb_1">
<img src="powerbank-ptero/assets/pb_pcb_2.jpg" width="250" alt="pb_pcb_2">

Can be found in `Aliexpress` or `Amazon` by number: `H961-U` or by description: `Dual USB 5V 2.4A Micro/Type-C USB Mobile`

### Prerequisites

<img src="powerbank-ptero/assets/ptero_prereq.jpg" width="300" alt="ptero_prereq">

The project contains `SolidWorks` source models and `stl` directory with all required models for 3D printing.
All that needs to assembly single device:
- 23x - Batteries (see [Specification](#specification))
- 1x - Power Bank PCB
- 6x - M3 bolts 10-14mm
- 6x - M3 brass inserts (4-6mm x 4.2mm)
- 1x -`body_top.STL` -> ***Resolution: 0.2, Walls: 2–3, Infill: 50%+, Supports: No, Filament material: PLA***
- 1x -`body_bottom.STL` -> ***Resolution: 0.2, Walls: 2–3, Infill: 50%+, Supports: Yes, Filament material: PLA***
- 2x -`battery_holder_8x.STL` -> ***Resolution: 0.2, Walls: 1, Infill: 100%, Supports: No, Filament material: PLA***
- 1x -`battery_holder_7x.STL` -> ***Resolution: 0.2, Walls: 1, Infill: 100%, Supports: Yes, Filament material: PLA***
- 1x -`display_glass.STL` -> ***Resolution: 0.12, Walls: 2, Infill: 2%, Supports: No, Filament material: Transparent PLA***
- 1x -`button.STL` -> ***Resolution: 0.12, Walls: 2, Infill: 100%, Supports: No, Filament material: PLA***

***Additional:*** Nickel plated strip (0.1mm x 6-10mm) and some wires to solder batteries

### Assembly

#### 1. Place batteries in holders and solder them in parallel

<img src="powerbank-ptero/assets/pb_asm_bat_1.jpg" width="300" alt="batt_asm"><br/>

<img src="powerbank-ptero/assets/pb_asm_bat_2.jpg" width="300" alt="batt_asm"><br/>
***Note:*** It's better to use copper wire from UTP internet cable to connect batteries

<img src="powerbank-ptero/assets/pb_asm_bat_3.jpg" width="300" alt="batt_asm"><br/>
***Note:*** Do not forget to isolate contacts as in photo, or as alternative hot glue can be used

#### 2. Set brass inserts to the top lid

<img src="powerbank-ptero/assets/brass_inserts.jpg" width="300" alt="inserts_asm"><br/>

#### 3. Place display glass

<img src="powerbank-ptero/assets/glass_install.jpg" width="300" alt="display_asm"><br/>

***Note:*** No need of any glue.

#### 4. Insert button to the place

<img src="powerbank-ptero/assets/button_set.jpg" width="300" alt="button_asm"><br/>

#### 5. Place PCB board as follows

<img src="powerbank-ptero/assets/pcb_set.jpg" width="300" alt="pcb_asm"><br/>
<img src="powerbank-ptero/assets/pcb_set_2.jpg" width="300" alt="pcb_next_asm"><br/>

***Note:*** Check button by clicking on it several times

#### 6. Place prepared batteries

<img src="powerbank-ptero/assets/batteries_set.jpg" width="300" alt="inserts_asm"><br/>

#### 7. Solder wires to nickel strip

<img src="powerbank-ptero/assets/strip_1.jpg" width="300" alt="nickel_strip_1"><br/>
<img src="powerbank-ptero/assets/strip_2.jpg" width="300" alt="nickel_strip_2"><br/>

***Note:*** Cut strip with additional 0.5cm at the end, for better fixation melt it a little with soldering iron to the holder case

<img src="powerbank-ptero/assets/strip_soldered.jpg" width="400" alt="nickel_strip_soldered"><br/>

#### 8. Place and screw up the lid

<img src="powerbank-ptero/assets/bottom_lid.jpg" width="400" alt="bottom_lid"><br/>

Charge and check the capacity. Then your device is ready

---
