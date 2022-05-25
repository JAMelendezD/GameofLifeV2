# Game of Life (V2)

## Installation Unix

```
mkdir build
cd build
./config --prefix=/place/to/install
make; make check; make install
```
If you use the config without a prefix then you will probably need to do `sudo make install`.

## Execution

You can control and need to provide the number of rows, number of columns, frames and fps as follows:

`./gameoflife 50 50 500 10`

## Example

<p align="center">
  <img width="1000" src="images/animation.gif">
</p>