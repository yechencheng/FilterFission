#!/usr/bin/perl
use Cwd;
use Getopt::Long;

GetOptions ("single=s{3}" => \@single, #src,thread,itr
			"batch" => \$batch,
			"help" => \$help,
			"perf" => \$perf,
			"massif" => \$massif,
			"nocompile" => \$nocompile,
			"time" => \$time
			);

if($batch){
	ProfAll(@_);
}
elsif(@single){
	ProfSingle(@_);
}
elsif($help){
	print("ProfAll [--batch | --single source thread itr ] [--perf] [--massif] [--nocompile]\n
			--batch : profile all apps\n
			--single : profile single apps\n
			--perf : profile cache miss\n
			--massif : profile memory\n
			--nocompile : do not carry compiling phase\n");
}

sub ProfSingle{
	if($single[1] == 0){
		for(my $C=16; $C >= 1; $C--){
			RunTestWithThread("$single[0]", "$C", "-u 1 -O0", "$single[2]", " ", "--stacks=yes --max-stackframe=8589934592 --main-stacksize=8589934592 ");
		}
	}
	else{
		RunTestWithThread("$single[0]", "$single[1]", "-u 1 -O0", "$single[2]", " ", "--stacks=yes --max-stackframe=8589934592 --main-stacksize=8589934592 ");
	}
}

sub ProfAll{
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
							["tde_pp", "tde_pp.str", "10"],
							#["sar", "sar.str", "10"],
							);

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

sub CompileWithPerl{
	(my $src, my $flag, my $output)=@_;
	#print "$flag\n";
	system("./CompileAll.perl \"$flag\" $output");
}

sub CompileCode{
	if(-e "CompileAll.perl"){
		CompileWithPerl(@_);
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
	print "@_ \n";
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
	system("valgrind --tool=massif $flag ./$prog $progFlag");
}

sub LogInfo{
	if($log){
		system(" echo \"@_\" >> $log");
	}
}

sub RunTestWithThread{
	(my $src, my $C, my $Cflag, my $itr, my $Rflag, my $MassifFlag)=@_;
	
	$output="C$C.out";
	LogInfo("`date`\t $src $output : BEGIN");

	unless($nocompile){
		CompileCode($src, "--cluster $C $Cflag", $output);	
	}

	if($perf){
		print "perf detected\n";
		PerfCache($output, "-i $itr $Rflag");
	}
	if($massif){
		print "Massif detected\n";
		MassifData($MassifFlag, $output, "-i $itr $Rflag");
	}
	if($time){
		if($single[1] == 0){
			system("echo $C >> time.txt");
			system("./$output -i $itr -t 2>> time.txt");
		}
		else{
			system("./$output -i $itr -t");
		}
	}
	LogInfo("`date`\t $src : END");
}

sub RunTest{
	(my $src, my @remain)=@_;

	for $C (1 .. 16){
		RunTestWithThread("$src $C @remain")
	}
}
