#!/bin/perl

while (<>)
{
  $_ =~ s/.*\/(.*?).ned.*@signal\[(.*)\](.*)//;
  $module = $1;
  $name = $2;
  $properties = $3;
  $properties =~ s/type=(inet::)?([\w]+)//;
  $type = $2;
  print "$module, $name, $type\n"
}
