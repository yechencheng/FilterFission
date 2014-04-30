#!/usr/bin/perl -w

#my $F=@ARGV[0];

(my $flag, my $target, my $F)=@ARGV;
if(!$F){
	$F="0";
}

print "$flag\n";
system("cp Makefile.bak Makefile");
system("sed -i \"s/MYFLAG/$flag/g\" Makefile");
system("sed -i \"s/MYTARGET/$target/g\" Makefile");

system("cp Statics.str.bak Statics.str");
system("sed -i \"s/MYFACTOR/$F/g\" Statics.str");

system("make clean");
system("make");


