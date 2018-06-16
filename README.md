# atem_cli
simple console cli for atem

!! https://github.com/petersimonsson/libqatemcontrol must be installed!

# Build
```
qmake
make
```


# Usage
```
# ./atem_cli
usage: ../atem_cli_local/atem_cli <ip_address> read
usage: ../atem_cli_local/atem_cli <ip_address> program <1-8>
usage: ../atem_cli_local/atem_cli <ip_address> preview <1-8>
usage: ../atem_cli_local/atem_cli <ip_address> cut
usage: ../atem_cli_local/atem_cli <ip_address> auto
usage: ../atem_cli_local/atem_cli <ip_address> read_auto
usage: ../atem_cli_local/atem_cli <ip_address> auto_set <0-4>
auto_set effects: 0=Mix, 1=Dip, 2=Wipe, 3=Sting, 4=DVE
```

# Commands
```
read - read state
program - set output #
preview - set preview #
cut - change output
auto - change output with effect
read_auto - report auto effect
auto_set - set auto effect
```

# Examples
```
./atem_cli 1.2.3.4 read
./atem_cli 1.2.3.4 program 2
./atem_cli 1.2.3.4 preview 3
./atem_cli 1.2.3.4 cut
./atem_cli 1.2.3.4 read_auto
./atem_cli 1.2.3.4 auto_set 4
./atem_cli 1.2.3.4 auto
```

# Program will timeout and print error message if there is no connection after 1 second!
