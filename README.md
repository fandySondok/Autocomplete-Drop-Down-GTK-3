# Autocomplete Drop-Down GTK

## Description

Autocomplete dropdown yang banyak digunakan untuk `entry widget`. Secara konsep, hal ini dapat berfungsi dengan menggunakan signal `changed` pada `entry widget` untuk mengetahui setiap perubahan text dalam widget tersebut. Lalu membandingkan setiap perubahan text tersebut dengan array country name, kemudian jika susunan karakternya sama, country name tersebut akan dimasukan dalam `list store` yang kemudian ditambahkan/show ke dalam container yang tepat berada dibawah `entry widget`.

![Pic 1](/docs/img/pic1.png?raw=true 'Pic 1')
![Pic 2](/docs/img/pic2.png?raw=true 'Pic 2')
![Pic 3](/docs/img/pic3.png?raw=true 'Pic 3')

## Prerequisites

- `gcc` (C Compiler)
- `gtk+3.0 library` (GTK Lib)

```sh
$ sudo apt-get update
$ sudo apt-get install build-essential
$ sudo apt-get install libgtk-3-dev
```

## Compiling

```bash
$ gcc main.c -o main `pkg-config --cflags --libs gtk+-3.0`
```

## Usage

```bash
$ ./main
```
