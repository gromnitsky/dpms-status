# dpms-status

Get the
[DPMS](https://wiki.archlinux.org/index.php/Display_Power_Management_Signaling)
status of an X11 server. Handy for sh scripts.

Run `make` to compile.

## Why?

The output of `xset q` is meant for humans.

## Examples

Print the info from a diff server:

~~~
$ ./dpms-status $DISPLAY
dpms_status=1
dpms_monitor=on
dpms_standby=600
dpms_suspend=600
dpms_off=600
~~~

Get only the monitor status:

~~~
$ ./dpms-status | awk -F= '/monitor/ { print $2 }'
on
~~~

(May return one of: `on`, `standby`, `suspend`, `off`, `n/a`.)

Parse all the data simultaneously:

~~~
$ sh <<'E'
> eval `./dpms-status`
>
> echo dpms=$dpms_status
> echo monitor=$dpms_monitor
> echo standby=$dpms_standby
> echo suspend=$dpms_standby
> echo off=$dpms_off
> E
dpms=1
monitor=on
standby=600
suspend=600
off=600
~~~

## License

MIT.
