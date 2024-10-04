# salt-energy

## Introduction

This project provides practical solutions for repurposing disposable vape batteries to power devices like power banks and other rechargeable electronics. 
By transforming these short-lived products into useful, long-lasting devices, we aim to reduce electronic waste and extend the life cycle of valuable components.

<img src="assets/waste-vapes.jpg" width="600" height="600" alt="waste">

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

- [Salt AA Battery](#salt-aa-battery)
- [Ptero Power Bank](#ptero-power-bank)


## Salt AA Battery

Rechargeable rectangular AA battery, with discharge current up to 2A and quiescent current <25uA

<img src="" width="600" alt="">

### Specification

- Size: mm x mm x mm
- Capacity: 400 mAh
- Battery count: 1
- Battery type: [Flat battery](#1-flat-battery)

#### Battery PCB

The heart of this battery is custom designed board with charger(`TP4057`), protection(`XB7608A`) and step-down converter(`TPS62A02`).

<img src="salt-battery/assets/pcb_3d.jpg" width="250" alt="pcb_3d">

#### USB type C PCB

<img src="salt-battery/assets/pcb_usb_3d.jpg" width="250" alt="pcb_usb_3d">

#### JLCPCB quote example

<img src="salt-battery/assets/jlcpcb_quote.jpg" width="250" alt="pcb_quote_1"><br/>
<img src="salt-battery/assets/jlcpcb_quote_usb.jpg" width="250" alt="pcb_quote_1"><br/>

***Note:*** All required fabrication and BOM can be found in `altium` directory.

### Prerequisites

<img src="salt-battery/assets/prereq.jpg" width="300" alt="battery_prereq">

The project contains `solidworks` source models and `stl` directory with all required models for 3D printing.
All that needs to assembly single device:
- 1x - Battery (see [Specification](#specification))
- 2x - Battery contacts (***Only positive contact required***). Can be found in `Aliexpress`, `Ebay` or `Amazon` by description: `Battery AA AAA Battery Positive to Negative Spring Plate Set`
    - Material: Metal 
    - Fit for: AA, AAA Batteries
    - Length: 9mm（0.35in, Wide: 8mm（0.31in）
- 1x -`main-board` -> ***Soldered***
- 1x -`usb-board` -> ***Soldered***
- 1x -`battery_aa_case.STL` -> ***Resolution: 0.1, Walls: 1, Infill: 100%, Supports: Yes, Filament material: PLA***
- 1x -`battery_aa_lid.STL` -> ***Resolution: 0.1, Walls: 1, Infill: 100%, Supports: Yes, Filament material: PLA***
  
***Additional:*** Some wires and epoxy or adhesive(B-7000) glue required

### Assembly

#### 1. Prepare Battery Contacts And Solder USB Wires

<img src="salt-battery/assets/prepare_usb_poles.jpg" width="300" alt="prepare_usb_poles">

#### 2. Solder Main PCB To Battery

<img src="salt-battery/assets/main_solder.jpg" width="300" alt="main_solder">

***Note:*** Do not forget to put isolator between battery terminals

<img src="salt-battery/assets/main_isolator.jpg" width="300" alt="main_isolator">

#### 3. Set USB PCB To The Case

<img src="salt-battery/assets/usb_insert_1.jpg" width="300" alt="usb_insert_1"><br/>
<img src="salt-battery/assets/usb_insert_2.jpg" width="300" alt="usb_insert_2"><br/>

#### 4. Insert Battery And Board To The Case

- <img src="salt-battery/assets/pcb_insert_1.jpg" width="300" alt="pcb_insert_1">
- <img src="salt-battery/assets/pcb_insert_2.jpg" width="300" alt="pcb_insert_2">

#### 5. Glue Up Positive And Negative Contacts

- <img src="salt-battery/assets/pole_glue_1.jpg" width="300" alt="pole_glue_1">
- <img src="salt-battery/assets/pole_glue_2.jpg" width="300" alt="pole_glue_2">
- <img src="salt-battery/assets/pole_glue_3.jpg" width="300" alt="pole_glue_3">

#### 6. Solder Positive, Negative And USB Contacts To Battery PCB

<img src="salt-battery/assets/conn_soldering.jpg" width="300" alt="conn_soldering">

#### 7. Check That Charger Works And Battery Output 1.5V

- <img src="salt-battery/assets/test.jpg" width="300" alt="test">
- <img src="salt-battery/assets/charge.jpg" width="300" alt="charge">

#### 8. Glue Up Battery Lid

- <img src="salt-battery/assets/glue_1.jpg" width="300" alt="glue_1">
- <img src="salt-battery/assets/glue_2.jpg" width="300" alt="glue_2">

#### 9. Fully Charge Battery

---

## Ptero Power Bank

Cheap and powerful power bank with quick charge support

<img src="ptero-powerbank/assets/ptero_1.jpg" width="600" alt="ptero_1">

### Specification

- Size: 165mm x 74mm x 22mm
- Capacity: 9200 mAh
- Battery count: 23
- Battery type: [Flat battery](#1-flat-battery)

Based on the popular power bank charging module:

<img src="ptero-powerbank/assets/pb_pcb_1.jpg" width="250" alt="pb_pcb_1">
<img src="ptero-powerbank/assets/pb_pcb_2.jpg" width="250" alt="pb_pcb_2">

Can be found in `Aliexpress` or `Amazon` by number: `H961-U` or by description: `Dual USB 5V 2.4A Micro/Type-C USB Mobile`

### Prerequisites

<img src="ptero-powerbank/assets/ptero_prereq.jpg" width="300" alt="ptero_prereq">

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

<img src="ptero-powerbank/assets/pb_asm_bat_1.jpg" width="300" alt="batt_asm"><br/>

<img src="ptero-powerbank/assets/pb_asm_bat_2.jpg" width="300" alt="batt_asm"><br/>
***Note:*** It's better to use copper wire from UTP internet cable to connect batteries

<img src="ptero-powerbank/assets/pb_asm_bat_3.jpg" width="300" alt="batt_asm"><br/>
***Note:*** Do not forget to isolate contacts as in photo, or as alternative hot glue can be used

#### 2. Set brass inserts to the top lid

<img src="ptero-powerbank/assets/brass_inserts.jpg" width="300" alt="inserts_asm"><br/>

#### 3. Place display glass

<img src="ptero-powerbank/assets/glass_install.jpg" width="300" alt="display_asm"><br/>

***Note:*** No need of any glue.

#### 4. Insert button to the place

<img src="ptero-powerbank/assets/button_set.jpg" width="300" alt="button_asm"><br/>

#### 5. Place PCB board as follows

<img src="ptero-powerbank/assets/pcb_set.jpg" width="300" alt="pcb_asm"><br/>
<img src="ptero-powerbank/assets/pcb_set_2.jpg" width="300" alt="pcb_next_asm"><br/>

***Note:*** Check button by clicking on it several times

#### 6. Place prepared batteries

<img src="ptero-powerbank/assets/batteries_set.jpg" width="300" alt="inserts_asm"><br/>

#### 7. Solder wires to nickel strip

<img src="ptero-powerbank/assets/strip_1.jpg" width="300" alt="nickel_strip_1"><br/>
<img src="ptero-powerbank/assets/strip_2.jpg" width="300" alt="nickel_strip_2"><br/>

***Note:*** Cut strip with additional 0.5cm at the end, for better fixation melt it a little with soldering iron to the holder case

<img src="ptero-powerbank/assets/strip_soldered.jpg" width="400" alt="nickel_strip_soldered"><br/>

#### 8. Place and screw up the lid

<img src="ptero-powerbank/assets/bottom_lid.jpg" width="400" alt="bottom_lid"><br/>

Charge and check the capacity. Then your device is ready

---
