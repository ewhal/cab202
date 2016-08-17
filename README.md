# CAB202 Microprocessors and Digital Systems
All weekly workshop questions and AMS questions for CAB202 microprocessors and digital systems.

## Weekly activities
The week folders contain both workshop questions and weekly assessed questions.

## Assignment 1
Assignment 1 is a fully functional pong clone written in ncurses.

## Building
Most programs require the ZDK library.
```
cd ZDK
make
gcc ex1.c -std=gnu99 -L ../ZDK -I ../ZDK -lzdk -lncurses -lm 
```

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
