I needed to comment a lot of code to figure out how it works, but i noticed that typing "//" on every line takes a long time. So its my utility for that.

It turns this:
```
type function()
{
  the;
  body;
  of;
  the;
  function;
}
```
To this:
```
type function() //
{
  the;          //
  body;         //
  of;           //
  the;          //
  function;     //
}
```
And then you can comment what you need much faster!

Usage:
```
commentator test.txt
```
or
```
commentator test.txt -o new.txt
```
or
```
commentator test.txt -o new.txt -m 5
```
-o is the parameter for output file

-m is the parameter for minimal number of symbols in line to comment
