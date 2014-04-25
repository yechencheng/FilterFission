#!/usr/bin/perl
use Cwd;

local @Task=(
						#["beamformer", "BeamFormer1.str", "1000000"],
						#["bitonic-sort", "BitonicSort2.str", "100000"],
						#["des", "DES2.str", "1000000"],
						#["filterbank", "FilterBank6.str", "100000"],
						#["mpeg2","MPEGdecoder_nomessage_5_3.str", "1000000"],
						#["serpent_full", "Serpent_full.str", "1000000"],
						#["channelvocoder", "ChannelVocoder7.str", "100000"],
						#["dct","DCT2.str", "1000000" ],
						#["fft", "FFT5.str", "1000000"],
						#["fm", "FMRadio5.str", "10000000"],
						#["tde_pp", "tde_pp.str", "10"],
						["sar", "sar.str", "10"],
						);

local @list=("beamformer","bitonic-sort","des","filterbank","mpeg2","serpent_full","channelvocoder","dct","fft","fm");

my $pwd = getcwd;
local $log = "$pwd/LogProfAll";

unless(-e $log){
	system("touch $log");
}

for my $t (@Task){
	system("echo \"`date`\" >> $log");

	(my $path, my $src, my $itr)=@$t;

	chdir("$path/streamit/");
	#RunTest("$src", "-u 1", "$itr", " ", "--pages-as-heap=yes");
	RunTest("$src", "-u 1", "$itr", " ", "--stacks=yes --max-stackframe=8589934592 --main-stacksize=8589934592 ");
	#system("./CompileAll.perl");
	chdir("$pwd");
}

sub MoveTarget{
	my $folder="./$_[0]";
	unless(-e $folder){
		system("mkdir $folder");
	}
	system("mv $_[1] $folder");
}

sub CompileDirectlly{
	(my $src, my $flag, my $output)=@_;
	system("strc $src $flag -o $output");
}

sub CompileWithMakefile{
	(my $src, my $flag, my $output)=@_;
	#print "$flag\n";
	system("./CompileAll.perl \"$flag\" $output");
}

sub CompileCode{
	if(-e "Makefile"){
		CompileWithMakefile(@_);
	}
	else{
		CompileDirectlly(@_);
	}
}


sub PerfData{
	(my $flag, my $prog, my $progFlag, my $output)=@_;
	system("perf $flag ./$prog $progFlag > $output 2>&1");	
}

sub PerfCache{
	(my $prog, my $progFlag) =@_;
	for my $E (0 .. 2){
		my $flag="stat -B -e cache-references,cache-misses,cycles,instructions,branches,faults,migrations";
		my $output="$prog.E$E.perf";
		PerfData($flag, "./$prog", $progFlag, $output);	
	}
}

sub MassifData{
	(my $flag, my $prog, my $progFlag)=@_;
	#if(-e "massif.out.*"){
	#	system("rm massif.out.*");
	#}
	system("valgrind3.9 --tool=massif $flag ./$prog $progFlag");
}

sub RunTest{
	(my $src, my $Cflag, my $itr, my $Rflag, my $MassifFlag)=@_;

	#my $massifItr=$itr/10;
	for $C (1 .. 16){
		$output="C$C.out";
		system("echo \"`date`\t $src $output : BEGIN\" >> $log");
		
		CompileCode($src, "--cluster $C $Cflag", $output);
		
		if("--perf" ~~ @ARGV){
			print "perf detected\n";
			PerfCache($output, "-i $itr $Rflag");
		}
		if("--massif" ~~ @ARGV){
			print "Massif detected\n";
			MassifData($MassifFlag, $output, "-i $itr $Rflag");
		}
		system("echo \"`date`\t $src : END\" >> $log");
	}
}
