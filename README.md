# Home LED

# Pre-requisites

- [nanopb](https://jpa.kapsi.fi/nanopb/download/)
  - Download and unzip to `src/ext`. Rename to `nanopb`
  - OSX: `sudo easy_install pip; and sudo python -m pip install protobuf`
- Setup [protocol buffers](https://developers.google.com/protocol-buffers/docs/gotutorial) for
go
  - [releases](https://github.com/protocolbuffers/protobuf/releases/tag/v3.10.1)

## Arduino IDE Setup

- Sketch -> Include Library -> Add .ZIP library
  - Select `nanopb` folder
- Sketch -> Include Library -> nanopb

# Development

## Proto

### Build test

`gcc -I ../ext/nanopb/ ../ext/nanopb/pb_decode.c ../ext/nanopb/pb_common.c led.pb.c proto.c proto_test.c`

### Use test

```
#!/bin/bash
./a.out $(echo 'led_string: {leds: {color: BLACK}}' | ./bin/protoc --encode ControlMessage led.proto)
```

```
echo 'led_string: {leds: {color: RED}, leds: {color: BLUE}}' | ./bin/protoc --encode ControlMessage led.proto | ./bin/protoc --decode ControlMessage led.proto
```



# Build

## Proto

While developing: `./bin/protoc led.proto -o led.pb`
  - Assuming protoc has been extracted in `proto` directory

For Arduino:
  - [source](https://github.com/nanopb/nanopb#using-the-protocol-buffers-compiler-protoc)
  - `python ext/nanopb/generator/nanopb_generator.py proto/led.pb`
    - Assuming nanopb is in ext/nanopb
