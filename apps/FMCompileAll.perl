#!/usr/bin/perl

($output)=$ARGV[0];
unless ($output) {
	$output="a.out";
}
my $org="global.h";
my $tmp="global.tmp.h";

my $str="";
for my $C (1 .. 10){
	my $X=$C+9;
	$str.="int streamItVar$C = 0; \\n";
}


system("sed -i '10 a $str' $org");
system("g++ -O3 -I/home/ycc/Software/streamit/streams//library/cluster -c -o combined_threads.o combined_threads.cpp");
system("g++ -O3 -o $output combined_threads.o -L/home/ycc/Software/streamit/streams//library/cluster -lpthread -lcluster -lstdc++");