#!/usr/bin/perl

use warnings;
use strict;

my @conf_files = `ls *.conf`;
my $prog_dir = "../../build";
my $out_dir = "benchs";
my $m2s_cmd = "m2s --mem-config ../base-mem-config.conf --x86-sim detailed --x86-config ";
`mkdir -p $out_dir`;

foreach my $conf_file (@conf_files) {
    chomp $conf_file;
    my $fullname = $conf_file;
    $conf_file =~ s{\.[^.]+$}{}; # removes extension
        foreach my $prog (`ls $prog_dir`) {
            chomp $prog;
            my $out_filename = $out_dir . "/" . $prog . "-" . $conf_file .
                               ".sim";
            print "processando $out_filename\n";
            my $full_cmd = $m2s_cmd . $fullname .
                           " ${prog_dir}/$prog" .
                           " $out_filename";
            `$full_cmd`;c
        }
}
