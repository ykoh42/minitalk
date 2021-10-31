# minitalk

> The purpose of this project is to code a small data exchange program using UNIX signals.

## Getting started

```bash
make
```

### server

```bash
./server
```

- A process id of server will appear.

### client

```bash
./client PID_FROM_SERVER "What you are going to send"
```

## Description

### server

- The server takes signals(`SIGUSR1`, `SIGUSR2`) sent from client.
- Translate a signal to one bit(`SIGUSR1` is `ON` and `SIGUSR2` is `OFF`) of one byte.
- Collect 8 signals(bits) and write them with one byte to STDOUT.

### client

- The client sends signals to process of server.
- Send one byte divided into 8 bits.
- One bit described with signal(`ON` bit is `SIGUSR1` and `OFF` bit is `SIGUSR2`).
- Send all bytes of string and then, send a `\0` charecter to notify that string is ended.
