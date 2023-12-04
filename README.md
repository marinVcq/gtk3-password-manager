# Password Manager with GTK3 and C programming

## TODO

- Hide password in GUI
- Edit & Delete function
- Header row issue when user add pasword
- Make list box scrollable
- Encrypt user password and password records
- Export Feature
- Sorting feature
- Back button on create account page
- Design List Box ( increase header's font)
- Add Preference (color, font-size etc ..)
- Add Dumb Values


## Introduction

Welcome! The purpose of this repo is to create a basic password manager using GTK3 library and C programming. I separate the process in 3 parts for a better understanding of my workflow and each part will guide you through the process of how to build a functional application with C programming without any framework.This project is designed to run on Debian-based operating systems.

In the **part 1** we will setup the file structure and the codebase of the application. this is one of the most important part to maintain a scalable and clean project. 

The **part 2** drill into design and the gtk3 lib, apply some style but keep the GUI simple.

Finally the **part 3** is the heart of the application, include all database implementations using SQLite and maybe some encryption to keep integrity of data.

## Part 1: Project structure & codebase

### 1.1 Project initialization

- Organize project with several directories for maintainability.
- Initialize the Gtk project with `gtk_init(&argc, &argv); `
- Create the main window, specify `GTK_WINDOW_TOPLEVEL`
- Set window properties as you want (title, app size, width, etc...)
- Connect destroy signal
- Create a stack container to manage multiple pages (login, mainwindow, register page)

```
	GtkWidget *stack = gtk_stack_new();
	gtk_container_add(GTK_CONTAINER(window), stack);
```
- Initialize each page `login_init(stack);`
- Show the main window and start Gtk loop

### 1.2 Page Initialization

For example take a look on `login.c`, the logic remain the same for every page

- `void login_init(GtkWidget *stack)` This function called in `main.c` intialize the login page and will contain more complex design later (see **part 2**).
- Connect button to `void on_login_button_clicked(GtkButton *button, gpointer data)` This is the callback function containing the auth logic and if success set visible the child of the stack with the name 'main'.
- Add the login page to the stack (as child) by this way:
```
	/* Add a stack title to this page */ 
    	gtk_stack_add_titled(GTK_STACK(stack), vbox, "login", "Login Page");
```

### 1.3 Set the make file & Test navigation

- 


## Part 2: Designs and Views 

## Part 3: Database implementations

## Features

- User-friendly GUI using GTK and provide an easy navigation.
- SQLite database for secure storage of passwords.
- Login functionality with authentication checks.
- Simple and intuitive interface for managing passwords.

## Prerequisites

Make sure the following dependencies are installed on your system:

- GTK+3
- SQLite3
- Build tools (gcc, make)

```bash
sudo apt-get install libgtk-3-dev libsqlite3-dev build-essential
```
## compile command: 

```
gcc `pkg-config --cflags gtk+-3.0` -o prog main.c database.c login.c create_user.c mainwindow.c `pkg-config --libs gtk+-3.0` -lsqlite3
```
	
