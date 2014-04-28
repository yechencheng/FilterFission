#!/usr/bin/perl

(my $src, my $flag, my $output)=@ARGV;

unless ($output) {
	$output="a.out";
}

#compile as normal
system("strc $src $flag -o $output");

#get compiling error, turns to fix bug and continue compiling
my $org="global.h";
my $tmp="global.tmp.h";

my $str="";
for my $C (1 .. 10){
	my $X=$C+9;
	$str.="int streamItVar$C = 0; \\n";
}


system("sed -i '10 a $str' $org");
system("g++ -O3 -I\$STREAMIT_HOME/library/cluster -c -o combined_threads.o combined_threads.cpp");
system("g++ -O3 -o $output combined_threads.o -L\$STREAMIT_HOME/library/cluster -lpthread -lcluster -lstdc++");