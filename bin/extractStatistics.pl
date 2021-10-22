#!/bin/perl

print "Module, Statistic, Unit, Title, Record, Source\n";

while (<>)
{
  $_ =~ s/.*\/(.*?).ned.*@statistic\[(.*)\](.*)//;
  $module = $1;
  $name = $2;
  $unit = $3;
  $title = $3;
  $source = $3;
  $record = $3;
  $unit =~ s/.*unit=([\w]+).*/$1/ or $unit = "";
  $title =~ s/.*title=(.*?);.*/$1/ or $title = "";
  $source =~ s/.*source=(.*?);.*/$1/ or $source = "";
  $record =~ s/.*record=(.*?);.*/$1/ or $record = "";
  print "$module, $name, $unit, $title, \"$record\", \"$source\"\n"
}
