Juan David Contreras
# TCP - CLient / Server Communication

Python Client / Server Application

## Clone the repository

Clone or download this repository

```
$git clone https://gitlab.com/JDContreras1/agiletask.git
$cd agiletask
```

## Intalling dependencies

### Python

For python only Typer is required to be installed using pip, you can use the requirements.txt.

```
$cd python_client
$pip install -r requirements.txt
```
It is recommended to use a virtual environment.

### C++
For c++ side, we are using Asio, this comes in two variants boost.asio and independent asio. For the first version just install the boost set of libraries using:
```
$sudo apt-get install libboost-all-dev
```

For other installations follow instructions at https://think-async.com/Asio/AsioAndBoostAsio.html

## Create Executables

### Python
On Ubuntu, just run the following bash command, from the root directory of the project
```
$cd python_client
$cd scripts
$sudo chmod +x client.py
```

Whit this, you only need to execute the script from the console passing the required and optional arguments

First, try the --help argument to learn hoy to use the CLI, the pass son arguments (note: if the server is no running, it will catch an error)

```
$./client.py --help
$./client.py --reverse abcdefg
$./client.py --reverse abcdefg --endpoint 192.168.0.15
```

### C++
In the server side, the source code should be compiled using cmake:

```
$cd cpp_server
$mkdir build && cd build && cmake .. && make -j
$./server
```
the server will run and will wait for connections 

This server run just for una message. todo: create a keepalive connection (it is really easy)

## Unit Testing

I have no experience with testing, so I recognize that as a weakness and an opportunity to improve. 
I did not complete that requirement.


